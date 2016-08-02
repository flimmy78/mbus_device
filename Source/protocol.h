#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "user.h"
#include "base.h"


#define METER_ADDR_LEN	7//�Ǳ��ַ����, 7λBCD��

#define PROTOCOL_STANDARD_CJ188	0//CJ188Э��
#define PROTOCOL_STANDARD_26831	1//26831Э��


#pragma pack(push)
#pragma pack(1)

typedef struct {
	U16 bigErr;//���������
	U16 mid2Err;//�ж��������
	U16 mid1Err;//��һ�������
	U16 smallErr;//С�������
} flow_coe_str;
typedef flow_coe_str* flow_coe_ptr;

typedef struct {
	float bigErr;//���������float
	float mid2Err;//�ж��������float
	float mid1Err;//��һ�������float
	float smallErr;//С�������float
} flow_error_str;
typedef flow_error_str* flow_error_ptr;

typedef struct {
	U8 inTemp[2];//��ˮ�¶� 24.35C
	U8 pulseCnt[4];//�������
	U8 chkAccFlow[4];//�춨ʱ�ۻ�����, 
	U8 chkAccFlowUnit;//�춨ʱ�ۻ�������λ
	U8 chkAccHeat[4];//�춨ʱ�ۻ�����
	U8 chkAccHeatUnit;//�춨ʱ�ۻ�������λ
	U8 accWarnTime[3];//�ۻ�����ʱ��
	U8 meterDiam[2];//�ܾ�
	U8 diffAt0[4];//����ֵ
	U8 pulseWidth[3];//������
	U8 meterAddr[4];//���
	flow_coe_str flowErr;//�������
	U8 tempParam1[2]; //�¶Ȳ���1
	U8 tempParam2[2];//�¶Ȳ���2
	U8 meterParam[2];//�Ǳ����
	U8 outTemp[2];//��ˮ�¶�, 24.29��
	U8 misc;
	U8 date[4];//����2016�� 07�� 31��
	U8 st[2];//ST
} meter_ret_data_str;
typedef meter_ret_data_str* meter_ret_data_ptr;

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
extern U8 protoA_meterAddr(U8* buf, U16 bufSize, meter_frame_info_ptr pFrameInfo, flow_coe_ptr pFlowErr);

#endif
