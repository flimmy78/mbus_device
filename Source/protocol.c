/***************************************************
**	ģ�鹦��:	��֯�Լ�����Э��
**	ģ������:	protocol.c
**	���ߣ�		�α���
**	ǰ׺proto��ΪЭ���ģ��ĺ���;
****************************************************
*/

#include "lib.h"
#include "protocol.h"

void createFrameCJ188(U8* buf, U16* bufSize, meter_frame_info_ptr pSendFrame)
{
	U8*	pBuf = buf;
	U8*	pCsStart = NULL;

	*bufSize = 0;

	//ǰ����
	memset(pBuf, pSendFrame->prefix, pSendFrame->prefixCnt);
	pBuf += pSendFrame->prefixCnt;
	(*bufSize) += pSendFrame->prefixCnt;
	//��ʼ��
	*pBuf = pSendFrame->startChar;
	pCsStart = pBuf;
	pBuf++;
	(*bufSize) += 1;
	//������
	*pBuf = pSendFrame->meterType;
	pBuf++;
	(*bufSize) += 1;
	//���ַ
	memcpy(pBuf, pSendFrame->meterAddr, pSendFrame->addrLen);
	pBuf += pSendFrame->addrLen;
	(*bufSize) += pSendFrame->addrLen;
	//������
	*pBuf = pSendFrame->ctlCode;
	pBuf++;
	(*bufSize) += 1;
	//���ݳ���
	*pBuf = pSendFrame->dataLen;
	pBuf++;
	(*bufSize) += 1;
	//������
	memcpy(pBuf, pSendFrame->pMsg, pSendFrame->dataLen);
	pBuf += pSendFrame->dataLen;
	(*bufSize) += pSendFrame->dataLen;
	//У���
	*pBuf = countCheck(pCsStart, *bufSize - pSendFrame->prefixCnt);
	pBuf++;
	(*bufSize) += 1;
	//������
	*pBuf = pSendFrame->endChar;
	(*bufSize) += 1;
}

U8 protoR_radioMAddr(U8* buf, U16* bufSize, meter_frame_info_ptr pSendFrame)
{
	U8 data[FRAME_MAX_LEN] = { 0 };
	memset(pSendFrame->meterAddr, pSendFrame->radioAddr, pSendFrame->addrLen);
	pSendFrame->seq = 0;

	memcpy(data, (U8*)&(pSendFrame->dataIdentify), sizeof(U16));
	memcpy(data + sizeof(U16), &pSendFrame->seq, sizeof(U8));
	pSendFrame->pMsg = data;
	if (pSendFrame->protoType == PROTOCOL_STANDARD_CJ188) {
		createFrameCJ188(buf, bufSize, pSendFrame);
	}

	return NO_ERR;
}

U8 protoA_meterAddr(U8* buf, U16 bufSize, U8* meterAddr)
{

	return NO_ERR;
}















