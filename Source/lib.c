#include "limits.h"
#include "lib.h"

void printBuf(U8* buf, U16 bufSize, const char* file, const char* func, U32 line)
{
	U8	strBuf[2048] = { 0 };
#ifdef DEBUG
	U16 i = 0;
	Lib_printf("[%s][%s][%d]buf: ", file, func, line);
	for (i = 0; i < bufSize; i++)
		Lib_printf("%02X ", buf[i]);
	Lib_printf("\n");
#endif // DEBUG
	bytesToStr(buf, bufSize, strBuf, file, func, line);
	writeByteToFile(strBuf, strlen((const char*)strBuf), "log.txt");
}

//读取系统时间
U8 readSysTime(sys_time_ptr pTime)
{
	RtcGetDate(&(pTime->u8year), &(pTime->u8month), &(pTime->u8day));
	RtcGetTime(&(pTime->u8hour), &(pTime->u8minute), &(pTime->u8second));

	pTime->u8year = HEX_TO_BCD(pTime->u8year);
	pTime->u8month = HEX_TO_BCD(pTime->u8month);
	pTime->u8day = HEX_TO_BCD(pTime->u8day);
	pTime->u8hour = HEX_TO_BCD(pTime->u8hour);
	pTime->u8minute = HEX_TO_BCD(pTime->u8minute);
	pTime->u8second = HEX_TO_BCD(pTime->u8second);

	return 0;
}

//校验, 累加和
U8 countCheck(U8 *data, U16 len)
{
	U8 cs = 0;
	U16 i;
	for (i = 0; i < len; i++, data++)
		cs += *data;

	return cs;
}

/*
**	去掉字符串中的空格.
**	@s:		字符串
**	@len:	字符串长度
*/
U8 trimSpace(U8* s, U16 len)
{
	U8* p = s;
	U8	buf[256] = { 0 };
	U16 i = 0, j = 0;
	for (i = 0, j = 0; i < len; p++, i++) {
		if (!isspace(*p)) {
			buf[j] = *p;
			j++;
		}
	}
	memset(s, 0x00, len);
	memcpy(s, buf, j + 1);
	return NO_ERR;
}

/*
**	检查字符串是否都是数字.
**	@s:		字符串
**	@len:	字符串长度
*/
U8 isNumber(U8* s, U16 len)
{
	U16 i = 0;
	if (len == 0) {
		return ERROR;
	}
	for (i = 0; i < len; s++, i++) {
		if (!isdigit(*s)) {
			return ERROR;
		}
	}

	return NO_ERR;
}

/*
**	反序输入的字符串至BCD码.
**	@s:		源字符串
**	@sLen:	源字符串长度
**	@t:		目标字符串
**	@tLen:	目标字符串长度
*/
U8 inverseStrToBCD(U8* s, U16 sLen, U8* t, U16 tLen)
{
	U16 i = 0;

	if (sLen % 2)
		return ERROR;

	for (i = 0; i < sLen / 2; i++, s += 2) {//convert ascii to hex each two chars
		t[i] = (ASCII_TO_HEX(s[0]) << 4 | ASCII_TO_HEX(s[1]));
	}

	inverseArray(t, i);
	return NO_ERR;
}

void inverseArray(U8* buf, U16 bufSize)
{
	U16 i = 0;
	for (i = 0; i < bufSize / 2; i++) {//swap two symmetric elements
		buf[i] = buf[i] ^ buf[bufSize - i - 1];
		buf[bufSize - i - 1] = buf[i] ^ buf[bufSize - i - 1];
		buf[i] = buf[i] ^ buf[bufSize - i - 1];
	}
}

/*
**	将数字字符串的最前面的'0'去掉.
**	@buf:		字符串
**	@bufSize:	字符串长度
*/
void trimZero(U8* buf, U8 bufSize)
{
	U16 i = 0;
	U8* lu8pBuf = buf;
	U8 tmpBuf[512] = { 0 };
	while (i < bufSize && (*lu8pBuf == '0')) {
		i++;
		lu8pBuf++;
	}
	memcpy(tmpBuf, lu8pBuf, bufSize - i);
	memset(buf, 0, bufSize);
	memcpy(buf, tmpBuf, bufSize - i);
}

/*
**	将数字字符串转为长整数.
**	参考: http://opensource.apple.com//source/xnu/xnu-1456.1.26/bsd/libkern/strtol.c
**	@nptr:		数字字符串
**	@endptr:	字符串长度
**	@base:		基数
**	return:		返回转换的整数
*/
U32 stringToL(const char* nptr, char **endptr, U8 base)
{
	const char *s = nptr;
	unsigned long acc;
	int c;
	unsigned long cutoff;//限度的绝对值
	int cutlim;
	int neg = 0, any;

	do {//略过空白
		c = *s++;
	} while (isspace(c));

	if (c == '-') {//符号位
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;

	if ((base == 0 || base == 16) && \
		c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	} else if ((base == 0 || base == 2) && \
		c == '0' && (*s == 'b' || *s == 'B')) {
		c = s[1];
		s += 2;
		base = 2;
	}

	if (base == 0)
		base = c == '0' ? 8 : 10;

	/*
	**	为了不超过长整数的范围, 
	**	设置cutoff为比不带符号的最大整数少1位.
	**	如果下一个字符的数字值比cutlim还大时,
	**	就不能继续计算了.
	**	比如输入的字符串为"-2147483649"
	**	base为10
	**	当计算到cutoff=214748364时, 
	**	字串的下一个字符为9, 大于cutlim
	**	(此时为8), 就不能再往下计算了
	*/
	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;

	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= (isupper(c) ? ('A' - 10) : ('a' - 10));
		else
			break;

		if (c >= base)
			break;

		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)//超限, 不计算
			any = -1;
		else {//没超限
			any = 1;
			acc *= base;
			acc += c;
		}
	}

	if (any < 0) {//超限, 返回极限值
		acc = neg ? LONG_MIN : LONG_MAX;
	} else if (neg)//未超限, 但为负数
		acc = -acc;

	if (endptr != NULL)
		*endptr = (char *)(any ? s - 1 : nptr);

	return (acc);
}

U8 dbFrameToProto(db_mFrame_ptr pDbFrame, meter_frame_info_ptr pProtoFrame)
{
	pProtoFrame->protoType = Lib_atoi((const char*)pDbFrame->prototype);
	pProtoFrame->meterType = ASCSTR_TO_HEX(pDbFrame->metertype);
	pProtoFrame->prefix = ASCSTR_TO_HEX(pDbFrame->prefix);
	pProtoFrame->prefixCnt = Lib_atoi((const char*)pDbFrame->prefixcnt);
	pProtoFrame->startChar = ASCSTR_TO_HEX(pDbFrame->startchar);
	pProtoFrame->endChar = ASCSTR_TO_HEX(pDbFrame->endchar);
	pProtoFrame->ctlCode= ASCSTR_TO_HEX(pDbFrame->controcode);
	pProtoFrame->dataIdentify= ASCSTR_TO_HEX(pDbFrame->dataid);
	pProtoFrame->dataLen= Lib_atoi((const char*)pDbFrame->datalen);
	pProtoFrame->busType= Lib_atoi((const char*)pDbFrame->bustype);
	pProtoFrame->addrLen= Lib_atoi((const char*)pDbFrame->addresslen);
	pProtoFrame->radioAddr= ASCSTR_TO_HEX(pDbFrame->radioaddr);

	return NO_ERR;
}

U8 binAddrToStr(U8* binAddr, U8* strAddr)
{
	Lib_sprintf((char*)strAddr, "%02x%02x%02x%02x%02x%02x%02x", \
		binAddr[6], binAddr[5], binAddr[4], binAddr[3], \
		binAddr[2], binAddr[1], binAddr[0]);
	return NO_ERR;
}

U8 binErrToStr(flow_error_ptr pBinErr, flow_err_string_ptr pStrErr)
{
	Lib_sprintf((S8*)pStrErr->bigErr, "%d", pBinErr->bigErr);
	Lib_sprintf((S8*)pStrErr->mid2Err, "%d", pBinErr->mid2Err);
	Lib_sprintf((S8*)pStrErr->mid1Err, "%d", pBinErr->mid1Err);
	Lib_sprintf((S8*)pStrErr->smallErr, "%d", pBinErr->smallErr);
	return NO_ERR;
}

U8 bytesToStr(U8* buf, U16 bufSize, U8* strBuf, const char* file, const char* func, U32 line)
{
	U16	i = 0;
	S8	tmpStr[4] = { 0 };
	sys_time_str timeStr;

	if (bufSize == 0) {
		return NO_ERR;
	}
	readSysTime(&timeStr);

	Lib_sprintf((S8*)strBuf, "[20%02X-%02X-%02X %02X:%02X:%02X][%s, %s, %d]", \
		timeStr.u8year, timeStr.u8month, timeStr.u8day, \
		timeStr.u8hour, timeStr.u8minute, timeStr.u8second, file, func, line);
	for (i = 0; i < bufSize-1;i++) {
		Lib_sprintf(tmpStr, "%02X ", buf[i]);
		strcat((S8*)strBuf, (const char*)tmpStr);
	}

	Lib_sprintf(tmpStr, "%02X\n", buf[i]);
	strcat((S8*)strBuf, (const char*)tmpStr);
	return NO_ERR;
}

U8 writeByteToFile(U8* buf, U16 bufSize, S8* fileName)
{
	sFILE *fp = FileOpen(fileName, "war");

	if (fp == NULL) {
		return ERROR;
	}
	FileWrite(buf, bufSize, fp);
	FileClose(fp);
	return NO_ERR;
}















