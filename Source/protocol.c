/***************************************************
**	模块功能:	组织以及解析协议
**	模块名字:	protocol.c
**	作者：		宋宝善
**	前缀proto意为协议库模块的函数;
****************************************************
*/

#include "lib.h"
#include "protocol.h"

U8	gu8Seq = 0;
static const U8 gu8modifyErrFrame[] = { 0x36, 0x0C, 0xA0, 0x19, 0x06, 0x00 };
static const U8 gu8chkStateFrame[] = { 0xFE, 0xFE, 0xFE, 0xFE, 0x68, 0x20, \
0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x00, 0x61, 0x16 };
static const U8 gu8clearValueFrame[] = { 0xFE, 0xFE, 0xFE, 0xFE, 0x68, 0x20, \
0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x24, 0x03, 0xA0, 0x0E, 0x01, 0x04, 0x16 };

void createFrameCJ188(U8* buf, U16* bufSize, meter_frame_info_ptr pSendFrame)
{
	U8*	pBuf = buf;
	U8*	pCsStart = NULL;

	*bufSize = 0;

	//前导符
	memset(pBuf, pSendFrame->prefix, pSendFrame->prefixCnt);
	pBuf += pSendFrame->prefixCnt;
	(*bufSize) += pSendFrame->prefixCnt;
	//起始符
	*pBuf = pSendFrame->startChar;
	pCsStart = pBuf;
	pBuf++;
	(*bufSize) += 1;
	//表类型
	*pBuf = pSendFrame->meterType;
	pBuf++;
	(*bufSize) += 1;
	//表地址
	memcpy(pBuf, pSendFrame->meterAddr, pSendFrame->addrLen);
	pBuf += pSendFrame->addrLen;
	(*bufSize) += pSendFrame->addrLen;
	//控制码
	*pBuf = pSendFrame->ctlCode;
	pBuf++;
	(*bufSize) += 1;
	//数据长度
	*pBuf = pSendFrame->dataLen;
	pBuf++;
	(*bufSize) += 1;
	//数据域
	memcpy(pBuf, pSendFrame->pMsg, pSendFrame->dataLen);
	pBuf += pSendFrame->dataLen;
	(*bufSize) += pSendFrame->dataLen;
	//校验和
	*pBuf = countCheck(pCsStart, *bufSize - pSendFrame->prefixCnt);
	pBuf++;
	(*bufSize) += 1;
	//结束符
	*pBuf = pSendFrame->endChar;
	(*bufSize) += 1;
}

U8 protoR_radioMAddr(U8* buf, U16* bufSize, meter_frame_info_ptr pSendFrame)
{
	U8 data[FRAME_MAX_LEN] = { 0 };
	memset(pSendFrame->meterAddr, pSendFrame->radioAddr, pSendFrame->addrLen);
	pSendFrame->seq = gu8Seq++;

	memcpy(data, (U8*)&(pSendFrame->dataIdentify), sizeof(U16));
	memcpy(data + sizeof(U16), &pSendFrame->seq, sizeof(U8));
	pSendFrame->pMsg = data;
	if (pSendFrame->protoType == PROTOCOL_STANDARD_CJ188) {
		createFrameCJ188(buf, bufSize, pSendFrame);
	}

	return NO_ERR;
}

U8 protoA_meterAddr(U8* buf, U16 bufSize, meter_frame_info_ptr pFrameInfo, flow_coe_ptr pFlowErr)
{
	U8* p = buf;
	meter_ret_data_str retStr;
	U16	tmpLength = 0;
	while (*p == pFrameInfo->prefix) {
		p++;
	}
	tmpLength = ((U8*)&pFrameInfo->seq - (U8*)&pFrameInfo->startChar + 1);
	memcpy(&pFrameInfo->startChar, p, tmpLength);
	p += tmpLength;
	memcpy((U8*)&retStr, p, sizeof(meter_ret_data_str));
	memcpy((U8*)pFlowErr, (U8*)&retStr.flowErr, sizeof(flow_coe_str));
	return NO_ERR;
}

U8 protoW_ModifyCoe(U8* buf, U16* bufSize, U8* meterAddr, meter_frame_info_ptr pSendFrame, flow_coe_ptr pFlowCoe)
{
	U8 data[FRAME_MAX_LEN] = { 0 };
	memcpy(pSendFrame->meterAddr, meterAddr, pSendFrame->addrLen);
	memcpy(&pSendFrame->ctlCode, gu8modifyErrFrame, 2);//0x36, 0x0C
	memcpy(data, gu8modifyErrFrame + 2, sizeof(gu8modifyErrFrame) - 2);//0xA0, 0x19, 0x06, 0x00
	memcpy(data + sizeof(gu8modifyErrFrame) - 2, (U8*)pFlowCoe, sizeof(flow_coe_str));
	pSendFrame->pMsg = data;
	if (pSendFrame->protoType == PROTOCOL_STANDARD_CJ188) {
		createFrameCJ188(buf, bufSize, pSendFrame);
	}

	return NO_ERR;
}

U8 protoX_setEnterChk(U8* buf, U16* bufSize)
{
	memcpy(buf, gu8chkStateFrame, sizeof(gu8chkStateFrame));
	*bufSize = sizeof(gu8chkStateFrame);
	return NO_ERR;
}

U8 protoW_clearValue(U8* buf, U16* bufSize)
{
	memcpy(buf, gu8clearValueFrame, sizeof(gu8clearValueFrame));
	*bufSize = sizeof(gu8clearValueFrame);
	return NO_ERR;
}












