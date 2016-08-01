#ifndef BASE_H
#define BASE_H

#define DEBUG
#define	FILE_LINE   __FILE__,__FUNCTION__,__LINE__
#define	PRINT_LINE()	Lib_printf("[%s][%s][%d]\n", FILE_LINE);
#define NO_ERR	0x00//�޴�
#define ERROR	0xEE//�д�
#define WM_USER_EXIT	-1//�����쳣����ֵ
#define EDIT_MAX_LEN	128
#define	FRAME_MAX_LEN	256

#define UART_WAIT_SHORT	2000//���ڵȴ�ʱ��-��-
#define UART_WAIT_MID	7000//���ڵȴ�ʱ��-��-
#define UART_WAIT_LONG	40000//���ڵȴ�ʱ��-��-

//�ֳֻ����õ�������, �����ݿ��е��к�Ҳ��˶�Ӧ
typedef enum {
	config_com_para = 0,//�˿���ز���
	config_meter_type,	//�Ǳ�����
	config_valve_type	//��������
}config_rowidx;


typedef enum {
	em_device_rs485 = 0,
	em_device_mbus
}em_device_idx;

typedef enum {
	em_baud_1200 = 0,
	em_baud_2400,
	em_baud_4800,
	em_baud_9600,
	em_baud_19200,
	em_baud_38400,
	em_baud_57600,
	em_baud_115200
} em_baud_idx;

typedef enum {
	em_databit_8 = 0,
	em_databit_7,
	em_databit_9
}em_databit_idx;

typedef enum {
	em_parity_none = 0,
	em_parity_odd,
	em_parity_even
}em_parity_idx;

typedef enum {
	em_stop_1 = 0,
	em_stop_2,
	em_stop_1_5
}em_stop_idx;

typedef struct {
	em_databit_idx	databit;
	em_parity_idx	parity;
	em_stop_idx		stop;
} uart_mode_str;

typedef enum {//�Ǳ���������
	em_mtype_deluUltro = 0,	//��³������������
	em_mtype_deluMachenical	//��³��еʽ������
} em_mtype_idx;

typedef enum {//������������
	em_vtype_yilin = 0,	//���ַ���, �ǵ�³Э��
	em_vtype_yilindelu,	//���ַ���, ��³Э��
	em_vtype_bainuan	//��ů��Э��
} em_vtype_idx;

#endif // ifndef BASE_H