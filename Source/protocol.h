#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "user.h"
#include "base.h"


#define METER_ADDR_LEN	7//�Ǳ��ַ����, 7λBCD��
#define ELSONIC_OPEN_HOUR_LEN	3//���ּҷ��صĿ���ʱ����Сʱ���ĳ���

#define PROTOCOL_STANDARD_CJ188	0//CJ188Э��
#define PROTOCOL_STANDARD_26831	1//26831Э��

#define OPEN_VALVE				0//�򿪷���
#define CLOSE_VALVE				1//�رշ���

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


#define ELSONIC_READ_VALUE	0xA0//���ּҷ���Э���ȡ����
#define ELSONIC_READ_VOPEN	0xA3//��ȡ�¿����ķ���ʱ��
#define ELSONIC_OPER_VALVE	0xA9//�������ַ�������
#define ELSONIC_CLOSE_VALVE	0x80//ǿ�ƹر����ַ���
#define ELSONIC_OPEN_VALVE	0x40//ǿ�ƿ������ַ���

#define	ELSONIC_FLAG_OPEN	0x01//��忪��
#define	ELSONIC_FLAG_LOAD_OPEN	0x02//����(����)ǿ�ƿ���
#define	ELSONIC_FLAG_PANEL_LOCK	0x04//�������
#define ELSONIC_CHK_CODE		0xA5//���ּ�У��͵������
typedef struct {//��д���ּҷ���Э��
	U8	cmd;	//��д����
	U16	addr;	//���ص�ַ
	U8	func;	//������, ���ػ�, �������Ȳ���
	U8	supTemp;//�����¶�
	U8	setTemp;//�ֶ��趨�¶�
	U8	rsv;	//����
	U8	cs;		//У��
} vElsonic_send_frame_str;
typedef vElsonic_send_frame_str* vElsonic_send_frame_ptr;

typedef struct {//���ּҷ��ط���֡�ṹ
	U8	aswcode;//Ӧ����, �̶�0x50
	U16	addr;	//���ص�ַ
	U8	func;	//������, ���ػ�, ��������״̬
	U8	supTemp;//�����¶�
	U8	setTemp;//�ֶ��趨�¶�
	U8	rsv;	//����
	U8	loadSt;	//����״̬
	U8	roomTemp;//�����¶�
	U8	inTemp;	//��ˮ�¶�
	U8	outTemp;//��ˮ�¶�
	U8	cs;		//У��
}vElsonic_asw_frame_str;
typedef vElsonic_asw_frame_str* vElsonic_asw_frame_ptr;

typedef struct {//���ּҷ���, ���ط���״̬��֡�ṹ
	U8	aswcode;	//Ӧ����, �̶�0x50
	U16	addr;		//���ص�ַ
	U8	openMin;	//����ʱ��, ����λ(HEX)
	U8	openHour[3];//����ʱ��Сʱ, С��(BCD)
	U8	energy[4];	//����, С��(BCD)
	U8	cs;			//У��
}vElsonic_vopen_frame_str;
typedef vElsonic_vopen_frame_str* vElsonic_vopen_frame_ptr;

typedef struct {
	U8	dOpen	: 1;//���ػ�, 0 -> �ػ�, 1->����
	U8	fOpen	: 1;//ǿ�ƿ������ر�־, 1->����ǿ�ƿ���, 0->������������
	U8	cLock	: 1;//�������, 0->����, 1->����
	U8	eDisp	: 1;//������ʾ, 1������, 0����ֹ
	U8	tDiff1	: 1;//�����²�(1��~5��)
	U8	tDiff2 : 1;//�����²�(1��~5��)
	U8	tDiff3 : 1;//�����²�(1��~5��)
	U8	fClose	: 1;//ǿ�ƹرո��ر�־, 1->����ǿ�ƹر�, 0->������������
}vElsonic_state;

#pragma pack(pop)



typedef enum
{
	em_bus_rs485 = 0,
	em_bus_mbus
} em_busType_idx;




extern U8 protoR_radioMAddr(U8* buf, U16* bufSize, meter_frame_info_ptr pSendFrame);
extern U8 protoA_meterAddr(U8* buf, U16 bufSize, meter_frame_info_ptr pFrameInfo, flow_coe_ptr pFlowErr);
extern U8 protoW_ModifyCoe(U8* buf, U16* bufSize, U8* meterAddr, meter_frame_info_ptr pSendFrame, flow_coe_ptr pFlowCoe);
extern U8 vprotoR_readValue(U8* buf, U16* bufSize, U8* valveAddr);
extern U8 vprotoA_readValue(U8* buf, U16 bufSize, vElsonic_asw_frame_ptr pElRetFrame);
extern U8 vprotoR_readOpenTime(U8* buf, U16* bufSize, U8* valveAddr);
extern U8 vprotoA_readOpenTime(U8* buf, U16 bufSize, vElsonic_vopen_frame_ptr pElRetFrame);
extern U8 vprotoX_operValue(U8* buf, U16* bufSize, U8* valveAddr, U8 openClose);
extern U8 vprotoA_operValue(U8* buf, U16 bufSize, U8 openClose);
#endif
