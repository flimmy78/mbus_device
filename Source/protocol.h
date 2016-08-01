#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "user.h"
#include "base.h"


#define METER_ADDR_LEN	7//仪表地址长度, 7位BCD码

#define PROTOCOL_STANDARD_CJ188	0//CJ188协议
#define PROTOCOL_STANDARD_26831	1//26831协议


#pragma pack(push)
#pragma pack(1)

typedef struct {//仪表组帧时用到的信息, 为了方便的解析应答帧, 不能改变成员变量的次序
	U8	protoType;			//协议类型, 0 - CJ188; 1 - 26831
	U8	prefix;				//前导符
	U16	prefixCnt;			//前导符数量
	U8	startChar;			//开始符
	U8	meterType;			//仪表类型, 20-热表;B0-阀控;
	U8	meterAddr[METER_ADDR_LEN];//仪表地址, 最大支持7位, 即14位BCD码
	U8	ctlCode;			//控制符
	U8	dataLen;			//数据域长度
	U16	dataIdentify;		//数据标识
	U8	seq;				//序列号
	U8	endChar;			//结束符
	U8	busType;			//总线类型, 0 - RS485; 1 - MBUS
	U8	addrLen;			//仪表地址长度
	U8	radioAddr;			//广播读表时的字符
	U8*	pMsg;				//数据域指针, 指向数据标识后
} meter_frame_info_str;
typedef meter_frame_info_str* meter_frame_info_ptr;

typedef struct {
	U8	startChar;			//开始符
	U8	meterType;			//仪表类型, 20-热表;B0-阀控;
	U8	meterAddr[METER_ADDR_LEN];//仪表地址
	U8	ctlCode;			//控制符
	U8	dataLen;		//数据域长度
	U16	dataIdentify;	//数据标识
	U8*	pMsg;			//数据域指针, 指向数据标识后
	U8	cs;				//累加和
	U8	endChar;		//结束符
}cj188_send_frame_str;
typedef cj188_send_frame_str* cj188_send_frame_ptr;




#pragma pack(pop)



typedef enum
{
	em_bus_rs485 = 0,
	em_bus_mbus
} em_busType_idx;




extern U8 protoR_radioMAddr(U8* buf, U16* bufSize, meter_frame_info_ptr pSendFrame);
extern U8 protoA_meterAddr(U8* buf, U16 bufSize, U8* meterAddr);

#endif
