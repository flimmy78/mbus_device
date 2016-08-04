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
static	flow_coe_str gOldCoe;//���ڼ�¼��ȡ�Ǳ�ľ����
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

U8 logic_radioMeterAddr(U8* meterAddr, flow_err_string_ptr pError)
{
	db_mFrame_str dbFrameStr = { 0 };
	meter_frame_info_str protoStr = { 0 };
	flow_error_str flowErrFloatStr = { 0 };
	U32 infoIdx = 0;
	U8	buf[FRAME_MAX_LEN] = { 0 };
	U16	bufSize = 0;

	db_getCongfig(config_meter_type, (U8*)&infoIdx);
	if (db_getFrameInfo(infoIdx, &dbFrameStr) == ERROR) {
		return ERROR;
	}
	dbFrameToProto(&dbFrameStr, &protoStr);
	protoR_radioMAddr(buf, &bufSize, &protoStr);
	printBuf(buf, bufSize, FILE_LINE);
	if (logic_sendAndRead(buf, &bufSize, UART_WAIT_SHORT) == ERROR) {
		Lib_printf("no response from device\n");
		return ERROR;
	}
	printBuf(buf, bufSize, FILE_LINE);
	if (protoA_meterAddr(buf, bufSize, &protoStr, &gOldCoe) == ERROR) {
		return ERROR;
	}

	binAddrToStr(protoStr.meterAddr, meterAddr);
	coeToErr(&gOldCoe, &flowErrFloatStr);
	binErrToStr(&flowErrFloatStr, pError);

	return NO_ERR;
}

U8 logic_modifyCoe(U8* meterAddr, flow_err_string_ptr pError)
{
	db_mFrame_str dbFrameStr = { 0 };
	meter_frame_info_str protoStr = { 0 };
	flow_error_str flowErrFloatStr = { 0 };
	flow_coe_str flowCoeStr = { 0 };
	U32 infoIdx = 0;
	U8	buf[FRAME_MAX_LEN] = { 0 };
	U16	bufSize = 0;
	U8	lu8meterAddr[METER_ADDR_LEN] = { 0 };

	db_getCongfig(config_meter_type, (U8*)&infoIdx);
	if (db_getFrameInfo(infoIdx, &dbFrameStr) == ERROR) {
		return ERROR;
	}
	dbFrameToProto(&dbFrameStr, &protoStr);
	inverseStrToBCD(meterAddr, 2 * METER_ADDR_LEN, lu8meterAddr, METER_ADDR_LEN);
	stringErrToBin(pError, &flowErrFloatStr);
	ErrTocoe(&gOldCoe, &flowErrFloatStr, &flowCoeStr);
	protoW_ModifyCoe(buf, &bufSize, lu8meterAddr, &protoStr, &flowCoeStr);
	printBuf(buf, bufSize, FILE_LINE);
	logic_sendAndRead(buf, &bufSize, UART_WAIT_SHORT);

	return NO_ERR;
}






