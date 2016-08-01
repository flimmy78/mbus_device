/***************************************************
**	ģ�鹦��:	����ҵ���߼�
**	ģ������:	logic.c
**	���ߣ�		�α���
****************************************************
*/

#include "db.h"
#include "lib.h"
#include "protocol.h"
#include "logic.h"

extern sUART* gpu;
/*
**	�򴮿ڶ�д����.
**	@buf:		������������ݻ�����
**	@bufSize:	����������
*/
U8 logic_sendAndRead(U8* buf, U16* bufSize, U32 timeout)
{
	UartWrite(buf, *bufSize, timeout, gpu);
	*bufSize = UartRead(buf, 100, timeout, gpu);
	if (*bufSize == 0) {//�����ʱ��û�ж�������, ���ش���
		return ERROR;
	}
	return NO_ERR;
}

U8 logic_saveConfig(U8  device, U32 baud, U8  mode, U8 meterType, U8  valveType)
{
	if (db_setComConfig(device, baud, mode) == ERROR) {
		return ERROR;
	}
	db_meterValveType(meterType, valveType);
	return db_writeConfig();
}

U8 logic_radioMeterAddr(U8* meterAddr)
{
	db_mFrame_str dbFrameStr = { 0 };
	meter_frame_info_str protoStr = { 0 };
	U32 infoIdx = 0;
	//U8	buf[FRAME_MAX_LEN] = { 0 };
	//U16	bufSize = 0;
	U8	buf[] = { 0xFE, 0xFE, 0xFE, 0xFE, 0x68, 0x20, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x01, 0x03, 0x3F, 0x90, 0x03, 0x04, 0x16 };
	U16	bufSize = sizeof(buf);
	U8	meterAddrBin[METER_ADDR_LEN] = { 0 };

	//db_getCongfig(config_meter_type, (U8*)&infoIdx);
	//if (db_getFrameInfo(infoIdx, &dbFrameStr) == ERROR) {
	//	return ERROR;
	//}
	//dbFrameToProto(&dbFrameStr, &protoStr);
	//protoR_radioMAddr(buf, &bufSize, &protoStr);
	//printBuf(buf, bufSize, FILE_LINE);
	printBuf(buf, bufSize, FILE_LINE);
	if (logic_sendAndRead(buf, &bufSize, UART_WAIT_SHORT) == ERROR) {
		Lib_printf("no response from device\n");
		return ERROR;
	}
	printBuf(buf, bufSize, FILE_LINE);
	if (protoA_meterAddr(buf, bufSize, meterAddrBin) == ERROR) {
		return ERROR;
	}
	binAddrToStr(meterAddrBin, meterAddr);
	return NO_ERR;
}








