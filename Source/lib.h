#ifndef LIB_H
#define LIB_H

#include "user.h"
#include "base.h"
#include "protocol.h"
#include "db.h"


#define HEX_TO_BCD(x) (((x)/0x0A)*0x10+((x)%0x0A))
#define BCD_TO_HEX(x) (((x)/0x10)*0x0A+((x)%0x10))

#define ASCII_TO_HEX(c) ((c >='0' && c <='9')?(c-'0'):((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):0)))
#define ASCSTR_TO_HEX(str)	stringToL((const char*)(str), NULL, 16)//以16进制表示的字符串转化为16进制数

#define isspace(c)	(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\12' || c == '\0')
#define isdigit(c)	((unsigned) ((c)-'0') < 10)
#define isalpha(c)	((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
#define isupper(c)	(c >= 'A' && c <= 'Z')

#define IS_SPACE	0x01
#define NOT_SPACE	0x00

extern void printBuf(U8* buf, U16 bufSize, const char* file, const char* func, U32 line);
extern U8 readSysTime(sys_time_ptr pTime);
extern U8 countCheck(U8 *data, U16 len);
extern void inverseArray(U8* buf, U16 bufSize);
extern U8 dbFrameToProto(db_mFrame_ptr pDbFrame, meter_frame_info_ptr pProtoFrame);
extern U8 binAddrToStr(U8* binAddr, U8* strAddr);
extern U8 coeToErr(flow_coe_ptr pCoe, flow_error_ptr pFloatErr);
extern U8 binErrToStr(flow_error_ptr pBinErr, flow_err_string_ptr pStrErr);
extern U8 bytesToStr(U8* buf, U16 bufSize, U8* strBuf, const char* file, const char* func, U32 line);
extern U8 writeByteToFile(U8* buf, U16 bufSize, S8* fileName);

#endif
