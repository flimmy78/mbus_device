#include <math.h>
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

//��ȡϵͳʱ��
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

//У��, �ۼӺ�
U8 countCheck(U8 *buf, U16 bufSize)
{
	U8 cs = 0;
	U16 i;
	for (i = 0; i < bufSize; i++, buf++)
		cs += *buf;

	return cs;
}

//���ּҵ�Э��У�鷽ʽ
U8 chkElsonic(U8 *buf, U16 bufSize)
{
	return (countCheck(buf, bufSize) ^ ELSONIC_CHK_CODE);
}

/*
**	ȥ���ַ����еĿո�.
**	@s:		�ַ���
**	@len:	�ַ�������
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
**	����ַ����Ƿ�������.
**	@s:		�ַ���
**	@len:	�ַ�������
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
**	����ַ����Ƿ���16�����ַ�.
**	@s:		�ַ���
**	@len:	�ַ�������
*/
U8 isHex(U8* s, U16 len)
{
	U16 i = 0;
	if (len == 0) {
		return ERROR;
	}
	for (i = 0; i < len; s++, i++) {
		if (!ishex(*s)) {
			return ERROR;
		}
	}

	return NO_ERR;
}

/*
**	����������ַ�����BCD��.
**	@s:		Դ�ַ���
**	@sLen:	Դ�ַ�������
**	@t:		Ŀ���ַ���
**	@tLen:	Ŀ���ַ�������
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
**	������14λ�ı��ǰ�油��.
**	@data:	�û�����ļ�������
*/
void supplementAddr(U8* data)
{
	U8 lu8tmpStr[EDIT_MAX_LEN] = { 0 };
	U8 lu8InputLen = 0;

	//supplement '0' before data, if lu8InputLen < 2 * GATEWAY_OADD_LEN
	lu8InputLen = STRLEN(data);
	//we use 2 chars to represent a byte, so the mod is 2.
	if (lu8InputLen % 2) {//if lu8InputLen is Odd, lu8InputLen must <= (2 * GATEWAY_OADD_LEN - 1)
		if (lu8InputLen > 2 * METER_ADDR_LEN - 1)
			return;
	}
	else {//if lu8InputLen is Even, lu8InputLen must <= 2 * GATEWAY_OADD_LEN
		if (lu8InputLen > 2 * METER_ADDR_LEN)
			return;
	}
	memset(lu8tmpStr, '0', 2 * METER_ADDR_LEN - lu8InputLen);
	memcpy(lu8tmpStr + (2 * METER_ADDR_LEN - lu8InputLen), data, lu8InputLen);
	memcpy(data, lu8tmpStr, 2 * METER_ADDR_LEN);
}

/*
**	�������ַ�������ǰ���'0'ȥ��.
**	@buf:		�ַ���
**	@bufSize:	�ַ�������
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
**	�������ַ���תΪ������.
**	�ο�: http://opensource.apple.com//source/xnu/xnu-1456.1.26/bsd/libkern/strtol.c
**	@nptr:		�����ַ���
**	@endptr:	�ַ�������
**	@base:		����
**	return:		����ת��������
*/
U32 stringToL(const char* nptr, char **endptr, U8 base)
{
	const char *s = nptr;
	unsigned long acc;
	int c;
	unsigned long cutoff;//�޶ȵľ���ֵ
	int cutlim;
	int neg = 0, any;

	do {//�Թ��հ�
		c = *s++;
	} while (isspace(c));

	if (c == '-') {//����λ
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
	**	Ϊ�˲������������ķ�Χ, 
	**	����cutoffΪ�Ȳ������ŵ����������1λ.
	**	�����һ���ַ�������ֵ��cutlim����ʱ,
	**	�Ͳ��ܼ���������.
	**	����������ַ���Ϊ"-2147483649"
	**	baseΪ10
	**	�����㵽cutoff=214748364ʱ, 
	**	�ִ�����һ���ַ�Ϊ9, ����cutlim
	**	(��ʱΪ8), �Ͳ��������¼�����
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

		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)//����, ������
			any = -1;
		else {//û����
			any = 1;
			acc *= base;
			acc += c;
		}
	}

	if (any < 0) {//����, ���ؼ���ֵ
		acc = (neg ? LONG_MIN : LONG_MAX);
	} else if (neg)//δ����, ��Ϊ����
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

/*
**	�����ֽ�4λ����, 12λС��
**	�Ķ�����, ת��Ϊ��������ʾ
**	�İٷֱ����
*/
float getErrByCoe(U16 coe)
{
	/*
	 *	�ϱ����ʹ��2�ֽڱ�ʾ���,
	 *	���ֽڵĸ���λ��ʾ����,
	 *	���ֽڵĵ���λ�͵��ֽڵ�8λ
	 *	��12λ��ʾС��,
	 *	���Եõ���2�ֽ��޷�������Ҫ��С����
	 *	�����ƶ�12λ, ������2^12 = 4096
	 *	�ſ��Եõ�ԭ��
	 *	ϵ�������֮��Ĺ�ϵ:
	 *	����VcΪ�Ǳ����õ���ֵ, VdΪ�Ǳ�ʾֵ
	 *	VsΪʵ��ֵ, CoeΪ����ϵ��
	 *	��ʱ��ΪVc*Coe=Vs=Vd
	 *	�� Err = (V1-V0)/V0
	 *	��������, V1*Coe = V0
	 *	ͨ����ʽ��ȥV1, V0
	 *	��:
	 *	Coe = 1/(1+Err)
	 *	Ҳ��:
	 *	Err = ((1/Coe) -1)
	 *	����100, �õ��ٷֱ�
	 *	ע��: ���Եõ������, ����Ϊ��ʱ���ȱ�ʾֵ
	 *	���׼ֵ���(��Ϊ��ǰ��Ϊ�������������
	 *	�ȱ�, �õ���ʾֵ���Ǳ�׼ֵ)
	 */
	printBuf((U8*)&coe, sizeof(U16), FILE_LINE);
	if (coe>0) {
		return (4096.0 / coe - 1.0)*100.0;
	} else {//���ԭϵ����0, �����Ϊ�����, Ϊ��ʾ���û��ͼ��㷽��, ȡ100%
		return 100.0;
	}
}

/*
**	����������ʾ�İٷֱ����
**	ת��Ϊ���ֽ�4λ����, 12λС��
**	�Ķ�����
*/
U16 getCoeByPercentErr(float percentErr, U16 oldCoe)
{
	/*
	 *	����VcΪ�Ǳ����õ���ֵ,
	 *	CoeOΪ�ϵ�ϵ��, ErrNΪ�����
	 *	CoeNΪ�µ�ϵ��,
	 *	VdΪ�Ǳ�ʾֵ, 
	 *	V0Ϊʵ��ֵ, 
	 *	��Vd = Vc*CoeO, 1
	 *	��V0 = Vc*CoeN, 2
	 *	��ErrN = (Vd-V0)/V0, 3, �ɵ� Vd/V0 = (1+ErrN), 4
	 *	ʽ2 ���� ʽ1 ��, CoeN/CoeO = V0/Vd, 5
	 *	�ʶ� CoeN = CoeO*(V0/Vd) = CoeO/(1+ErrN)
	 */
	U16 newCoeFix = 0;
	float newCoeFoat = 0.0;
	float oldCoeFloat = (oldCoe == 0 ? 1.0 : (oldCoe / 4096.0));

	newCoeFoat = (oldCoeFloat / (1.0 + percentErr / 100.0));
	newCoeFix = (int)(newCoeFoat * 4096.0);
	printBuf((U8*)&newCoeFix, sizeof(U16), FILE_LINE);
	return newCoeFix;
}

U8 coeToErr(flow_coe_ptr pCoe, flow_error_ptr pFloatErr)
{
	pFloatErr->bigErr = getErrByCoe(pCoe->bigErr);
	pFloatErr->mid2Err = getErrByCoe(pCoe->mid2Err);
	pFloatErr->mid1Err = getErrByCoe(pCoe->mid1Err);
	pFloatErr->smallErr = getErrByCoe(pCoe->smallErr);
	return NO_ERR;
}

U8 ErrTocoe(flow_coe_ptr pOldCoe, flow_error_ptr pFloatErr, flow_coe_ptr pNewCoe)
{
	pNewCoe->bigErr = getCoeByPercentErr(pFloatErr->bigErr, pOldCoe->bigErr);
	pNewCoe->mid2Err = getCoeByPercentErr(pFloatErr->mid2Err, pOldCoe->mid2Err);
	pNewCoe->mid1Err = getCoeByPercentErr(pFloatErr->mid1Err, pOldCoe->mid1Err);
	pNewCoe->smallErr = getCoeByPercentErr(pFloatErr->smallErr, pOldCoe->smallErr);
	return NO_ERR;
}

U8 binErrToStr(flow_error_ptr pBinErr, flow_err_string_ptr pStrErr)
{
	Lib_sprintf((S8*)pStrErr->bigErr, "%1.3f", pBinErr->bigErr);
	Lib_sprintf((S8*)pStrErr->mid2Err, "%1.3f", pBinErr->mid2Err);
	Lib_sprintf((S8*)pStrErr->mid1Err, "%1.3f", pBinErr->mid1Err);
	Lib_sprintf((S8*)pStrErr->smallErr, "%1.3f", pBinErr->smallErr);
	return NO_ERR;
}

U8 stringErrToBin(flow_err_string_ptr pStrErr, flow_error_ptr pBinErr)
{
	pBinErr->bigErr = Lib_atof((const char*)pStrErr->bigErr);
	pBinErr->mid2Err = Lib_atof((const char*)pStrErr->mid2Err);
	pBinErr->mid1Err = Lib_atof((const char*)pStrErr->mid1Err);
	pBinErr->smallErr = Lib_atof((const char*)pStrErr->smallErr);
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

/*
**	�ж�һ���ַ����Ƿ��Ǹ�����
**	@buf		�ַ�������
**	@bufSize	�ַ������泤��
*/
U8 isFloat(U8* buf, U16 bufSize)
{
	em_float_state state = float_state_init;
	S8 c;
	S8 flag = 0;
	U16 i = 0;

	for (i = 0; i < bufSize; i++) {
		c = buf[i];
		switch (state) {
		case float_state_init://��ʼ״ֻ̬���ܷ��Ż�����
			if (c == '+' || c == '-') {
				state = float_state_sign;
			}
			else if (isdigit(c)) {
				state = float_state_digit;
			} else {
				state = float_state_err;
				goto result;
			}
			break;
		case float_state_sign://����״ֻ̬��������
			if (isdigit(c)) {
				state = float_state_digit;
			} else {
				state = float_state_err;
				goto result;
			}
			break;
		case float_state_digit://����״ֻ̬�������ֺ�С����
			if (c == '.') {
				if (flag == 0) {//���û�н��չ�С����, ����ת��С����״̬;
					flag = 1;
					state = float_state_dec_point;
				} else {//������ܹ�С����, ��ֱ����ת������״̬
					state = float_state_err;
					goto result;
				}
			} else if ((c != '.') && !isdigit(c)) {
				state = float_state_err;
			}
			break;
		case float_state_dec_point://С����״ֻ̬��������
			if (isdigit(c)) {
				state = float_state_digit;
			} else {
				state = float_state_err;
				goto result;
			}
			break;
		default:
			state = float_state_err;
			goto result;
		}
	}
result:
	//float_state_digit ��Ψһ�Ľ���״̬
	return ((state == float_state_digit) ? NO_ERR : ERROR);
}

/*
**	��һ��BCD���ʾ���ֽ�����ת��Ϊ����������
**	@BCD		BCD�ֽڻ���, С��
**	@byteCnt	�ֽڻ��泤��
*/
U32 BCDtoHex(U8* BCD, U8 byteCnt)
{
	U32 hex = 0;
	U16 i = 0;

	for (i = 0; i < byteCnt; i++) {
		hex += BCD_TO_HEX(BCD[i]) * pow(100, i);
	}
	return hex;
}

U8 openTimeToStr(vElsonic_vopen_frame_ptr pOpenTime, U8* buf)
{
	U32 hex = BCDtoHex(pOpenTime->openHour, ELSONIC_OPEN_HOUR_LEN);

	Lib_sprintf((S8*)buf, "%d:%d", hex, pOpenTime->openMin);
	return NO_ERR;
}














