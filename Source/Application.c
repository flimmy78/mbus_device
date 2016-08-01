/***************************************************
**	ģ�鹦��:	������
**	ģ������:	application.c
**	���ߣ�		�α���
****************************************************
*/

#include "limits.h"
#include "GUI.h"
#include "EDIT.h"
#include "user.h"
#include "db.h"
#include "interface.h"

sUART *gpu;//ָ�򴮿ڵ�ָ��global_pointer_uart

int main(void) {
	sUART comConfig;

	/*
	**	��Mbus���ڵĶ���Ҫ����main�����вſ��Գ���,
	**	�����ܷ���logic_sendAndRead()��.
	**	ԭ����.
	*/
	db_readAllConfig();
	db_getCongfig(config_com_para, (U8*)&comConfig);
	gpu = UartOpen(comConfig.baud, comConfig.mode, comConfig.device);//�򿪴���
	if (!gpu) {
		GUI_MessageBox("\n�򿪴���ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return ERROR;
	}
	LcdClear();
	maingui();
	UartClose(gpu);
	return 0;
}
