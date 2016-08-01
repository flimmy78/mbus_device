#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "user.h"
#include "base.h"


#define METER_ADDR_LEN	7//�Ǳ��ַ����, 7λBCD��

#define PROTOCOL_STANDARD_CJ188	0//CJ188Э��
#define PROTOCOL_STANDARD_26831	1//26831Э��


#pragma pack(push)
#pragma pack(1)

typedef struct {//�Ǳ���֡ʱ�õ�����Ϣ, Ϊ�˷���Ľ���Ӧ��֡, ���ܸı��Ա�����Ĵ���
	U8	protoType;			//Э������, 0 - CJ188; 1 - 26831
	U8	prefix;				//ǰ����
	U16	prefixCnt;			//ǰ��������
	U8	startChar;			//��ʼ��
	U8	meterType;			//�Ǳ�����, 20-�ȱ�;B0-����;
	U8	meterAddr[METER_ADDR_LEN];//�Ǳ��ַ, ���֧��7λ, ��14λBCD��
	U8	ctlCode;			//���Ʒ�
	U8	dataLen;			//�����򳤶�
	U16	dataIdentify;		//���ݱ�ʶ
	U8	seq;				//���к�
	U8	endChar;			//������
	U8	busType;			//��������, 0 - RS485; 1 - MBUS
	U8	addrLen;			//�Ǳ��ַ����
	U8	radioAddr;			//�㲥����ʱ���ַ�
	U8*	pMsg;				//������ָ��, ָ�����ݱ�ʶ��
} meter_frame_info_str;
typedef meter_frame_info_str* meter_frame_info_ptr;

typedef struct {
	U8	startChar;			//��ʼ��
	U8	meterType;			//�Ǳ�����, 20-�ȱ�;B0-����;
	U8	meterAddr[METER_ADDR_LEN];//�Ǳ��ַ
	U8	ctlCode;			//���Ʒ�
	U8	dataLen;		//�����򳤶�
	U16	dataIdentify;	//���ݱ�ʶ
	U8*	pMsg;			//������ָ��, ָ�����ݱ�ʶ��
	U8	cs;				//�ۼӺ�
	U8	endChar;		//������
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
