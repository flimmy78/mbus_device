/***************************************************
**	ģ�鹦��:	�����û����潻��
**	ģ������:	interface.c
**	���ߣ�		�α���
****************************************************
*/

#include "db.h"
#include "protocol.h"
#include "logic.h"
#include "lib.h"
#include "interface.h"


/************************************************************************/
/* widget����Ⱥ                                                         */
/************************************************************************/
static const GUI_WIDGET_CREATE_INFO widgetMainFrame[] = {
	{ FRAMEWIN_CreateIndirect, "�Ǳ��뷧��", ID_FRAMEWIN_0, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "������", ID_BUTTON_0, 70, 35, 80, 50, 0, 0 },
	{ BUTTON_CreateIndirect, "����", ID_BUTTON_1, 70, 105, 80, 50, 0, 0 },
	{ BUTTON_CreateIndirect, "����", ID_BUTTON_2, 70, 175, 80, 50, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetMeterRelate[] = {
	{ FRAMEWIN_CreateIndirect, "�Ǳ����", ID_FRAMEWIN_1, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "���", ID_BUTTON_0, 10, 70, 80, 80, 0, 0 },
	{ BUTTON_CreateIndirect, "ʾֵ", ID_BUTTON_1, 130, 70, 80, 80, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetSetMeterErr[] = {
	{ FRAMEWIN_CreateIndirect, "�������", ID_FRAMEWIN_0, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "���", ID_BUTTON_0, 10, 10, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_0, 100, 10, 120, 20, 0, 0 },
	{ TEXT_CreateIndirect, "��", ID_TEXT_0, 10, 50, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�ж�", ID_TEXT_1, 10, 90, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "��һ", ID_TEXT_2, 10, 130, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "С", ID_TEXT_3, 10, 170, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_1, 110, 50, 100, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_2, 110, 90, 100, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_3, 110, 130, 100, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_4, 110, 170, 100, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", ID_BUTTON_1, 10, 255, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�޸�", ID_BUTTON_2, 130, 255, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetSetValve[] = {
	{ FRAMEWIN_CreateIndirect, "������Ϣ", ID_FRAMEWIN_0, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_0, 130, 10, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���ź�", ID_TEXT_0, 10, 10, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�����¶�", ID_TEXT_1, 10, 50, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_1, 130, 50, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����ʱ��", ID_TEXT_2, 10, 90, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", ID_EDIT_2, 130, 90, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "ǿ�ƹط�", ID_BUTTON_0, 10, 270, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "ǿ�ƿ���", ID_BUTTON_1, 130, 270, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "����", ID_BUTTON_2, 10, 140, 80, 20, 0, 0 },
	{ CHECKBOX_CreateIndirect, "", ID_CHECKBOX_0, 110, 140, 107, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetDeviceConfig[] = {
	{ FRAMEWIN_CreateIndirect, "�ֳֻ�����", ID_FRAMEWIN_3, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ TEXT_CreateIndirect, "�˿�", ID_TEXT_0, 10, 10, 60, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", ID_TEXT_1, 10, 40, 60, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����λ", ID_TEXT_2, 10, 70, 60, 20, 0, 0 },
	{ TEXT_CreateIndirect, "У��λ", ID_TEXT_3, 10, 100, 60, 20, 0, 0 },
	{ TEXT_CreateIndirect, "ֹͣλ", ID_TEXT_4, 10, 130, 60, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", ID_TEXT_5, 10, 160, 60, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", ID_TEXT_6, 10, 190, 60, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_0, 136, 10, 100, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_1, 135, 40, 100, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_2, 135, 70, 100, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_3, 135, 100, 100, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_4, 135, 130, 100, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_5, 135, 160, 100, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "", ID_DROPDOWN_6, 135, 190, 100, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", ID_BUTTON_0, 10, 265, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "����", ID_BUTTON_1, 135, 265, 80, 20, 0, 0 }
};

S8* gs8deviceStrArray[] = { "RS485","MBUS" };

U8	gu8deviceIntArray[] = { UART_DEVICE_RS485, UART_DEVICE_MBUS };

S8* gs8baudStrArray[] = { "1200","2400","4800","9600","19200","38400","57600","115200" };

U32 gu32baudIntArray[] = { 1200,2400,4800,9600,19200,38400,57600,115200 };

S8* gs8databitStrArray[] = { "8", "7", "9" };

S8* gs8parityStrArray[] = { "��", "��", "ż" };

S8* gs8stopStrArray[] = { "1" };

S8* gs8meterTypeStrArray[] = { "��³�������ȱ�", "��³��е�ȱ�"};

S8* gs8valveTypeStrArray[] = { "���ַǵ�³Э��", "���ֵ�³Э��", "��ů��" };

uart_mode_str	gUart_mode_strMap[] = {
	{ em_databit_7, em_parity_odd, em_stop_1 },
	{ em_databit_7, em_parity_even,em_stop_1 },
	{ em_databit_8, em_parity_none,em_stop_1 },
	{ em_databit_8, em_parity_odd, em_stop_1 },
	{ em_databit_8, em_parity_even,em_stop_1 },
	{ em_databit_9, em_parity_none,em_stop_1 } };


/************************************************************************/
/* Init����Ⱥ                                                           */
/************************************************************************/
//�Լ�����������������ʼ��
static void mainFrameInit(WM_HWIN hDlg)
{
	WM_HWIN pObj;
	pObj = WM_GetDialogItem(hDlg, GUI_ID_TEXT0);
	TEXT_SetTextAlign(pObj, GUI_TA_CENTER);
	TEXT_SetFont(pObj, GUI_GetFontAddress(24));
	WM_MakeModal(hDlg);                         //���öԻ���Ϊ��ռģʽ
	WM_SetFocus(hDlg);                          //��ϵͳ���㶨λ���Ի�����
}

static void setMeterErrInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;

	hItem = WM_GetDialogItem(hDlg, ID_TEXT_0);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

	hItem = WM_GetDialogItem(hDlg, ID_TEXT_1);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

	hItem = WM_GetDialogItem(hDlg, ID_TEXT_2);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

	hItem = WM_GetDialogItem(hDlg, ID_TEXT_3);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

	hItem = WM_GetDialogItem(hDlg, ID_EDIT_0);
	EDIT_SetMaxLen(hItem, EDIT_MAX_LEN);
}

static void setValveInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;

	hItem = WM_GetDialogItem(hDlg, ID_EDIT_0);
	EDIT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, ID_TEXT_0);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, ID_TEXT_1);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, ID_TEXT_2);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, ID_CHECKBOX_0);
	CHECKBOX_SetText(hItem, "16���Ƶ�ַ");
	CHECKBOX_SetState(hItem, 1);
}

static void deviceConfigInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U16 i = 0;
	sUART lComConfig;//com config
	U8 meterType = 0;
	U8 valveType = 0;
	U16 itemCnt = 0;

	db_getCongfig(config_com_para, (U8*)&lComConfig);
	db_getCongfig(config_meter_type, &meterType);
	db_getCongfig(config_valve_type, &valveType);

	for (i = ID_TEXT_0; i <= ID_TEXT_6; i++) {
		hItem = WM_GetDialogItem(hDlg, i);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	}

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_0);
	itemCnt = sizeof(gs8deviceStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8deviceStrArray[i]);
		if (gu8deviceIntArray[i] == lComConfig.device) {
			DROPDOWN_SetSel(hItem, i);
		}
	}

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_1);
	itemCnt = sizeof(gs8baudStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8baudStrArray[i]);
		if (gu32baudIntArray[i] == lComConfig.baud) {
			DROPDOWN_SetSel(hItem, i);
		}
	}

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_2);
	itemCnt = sizeof(gs8databitStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8databitStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, gUart_mode_strMap[lComConfig.mode - 1].databit);

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_3);
	itemCnt = sizeof(gs8parityStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8parityStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, gUart_mode_strMap[lComConfig.mode - 1].parity);

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_4);
	itemCnt = sizeof(gs8stopStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8stopStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, gUart_mode_strMap[lComConfig.mode - 1].stop);

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_5);
	itemCnt = sizeof(gs8meterTypeStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8meterTypeStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, meterType);

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_6);
	itemCnt = sizeof(gs8valveTypeStrArray) / sizeof(S8*);
	for (i = 0; i < itemCnt; i++) {
		DROPDOWN_AddString(hItem, gs8valveTypeStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, valveType);
}

/************************************************************************/
/* CallBack����Ⱥ                                                       */
/************************************************************************/
//������Ļص�����
void mainCb(WM_MESSAGE* pMsg)
{
	int NCode, Id, keyId;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		mainFrameInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode) {
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			GUI_EndDialog(hDlg, Id);
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		keyId = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
		switch (keyId) {
		case GUI_KEY_ESCAPE:
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			if (keyId >= GUI_KEY_NUM1 && keyId <= GUI_KEY_NUM3)
				GUI_EndDialog(hDlg, keyId + (ID_BUTTON_0 - GUI_KEY_NUM0) - 1);//�ð���"1"��Ӧbutton0
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

void setMeterCb(WM_MESSAGE* pMsg)
{
	int NCode, Id, keyId;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode) {
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			GUI_EndDialog(hDlg, Id);
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		keyId = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
		switch (keyId) {
		case GUI_KEY_ESCAPE:
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			if (keyId >= GUI_KEY_NUM1 && keyId <= GUI_KEY_NUM3)
				GUI_EndDialog(hDlg, keyId + (ID_BUTTON_0 - GUI_KEY_NUM0) - 1);//�ð���"1"��Ӧbutton0
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

void userRadioMeterId(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 meterAddr[2 * METER_ADDR_LEN + 1] = { 0 };
	flow_err_string_str flowErrStr;

	if (logic_radioMeterAddr(meterAddr, &flowErrStr)==ERROR) {
		GUI_MessageBox("\n�㲥��ȡ���ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		hItem = WM_GetDialogItem(hDlg, ID_EDIT_0);
		EDIT_SetText(hItem, (const char*)meterAddr);

		hItem = WM_GetDialogItem(hDlg, ID_EDIT_1);
		EDIT_SetText(hItem, (const char*)flowErrStr.bigErr);
		hItem = WM_GetDialogItem(hDlg, ID_EDIT_2);
		EDIT_SetText(hItem, (const char*)flowErrStr.mid2Err);
		hItem = WM_GetDialogItem(hDlg, ID_EDIT_3);
		EDIT_SetText(hItem, (const char*)flowErrStr.mid1Err);
		hItem = WM_GetDialogItem(hDlg, ID_EDIT_4);
		EDIT_SetText(hItem, (const char*)flowErrStr.smallErr);
	}
	WM_SetFocus(hDlg);
}

void userModifyCoe(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 meterAddr[2 * METER_ADDR_LEN + 1] = { 0 };
	flow_err_string_str flowErrStr = { 0 };

	hItem = WM_GetDialogItem(hDlg, ID_EDIT_0);
	EDIT_GetText(hItem, (S8*)meterAddr, 20);
	if (isNumber(meterAddr , STRLEN(meterAddr)) == ERROR) {
		GUI_MessageBox("\n���ڱ��ַ��������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	hItem = WM_GetDialogItem(hDlg, ID_EDIT_1);
	EDIT_GetText(hItem, (S8*)flowErrStr.bigErr, 20);
	if (isFloat(flowErrStr.bigErr, STRLEN(flowErrStr.bigErr)) == ERROR) {
		GUI_MessageBox("\n���ڴ���������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	hItem = WM_GetDialogItem(hDlg, ID_EDIT_2);
	EDIT_GetText(hItem, (S8*)flowErrStr.mid2Err, 20);
	if (isFloat(flowErrStr.mid2Err, STRLEN(flowErrStr.mid2Err)) == ERROR) {
		GUI_MessageBox("\n�����ж���������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	hItem = WM_GetDialogItem(hDlg, ID_EDIT_3);
	EDIT_GetText(hItem, (S8*)flowErrStr.mid1Err, 20);
	if (isFloat(flowErrStr.mid1Err, STRLEN(flowErrStr.mid1Err)) == ERROR) {
		GUI_MessageBox("\n������һ��������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	hItem = WM_GetDialogItem(hDlg, ID_EDIT_4);
	EDIT_GetText(hItem, (S8*)flowErrStr.smallErr, 20);
	if (isFloat(flowErrStr.smallErr, STRLEN(flowErrStr.smallErr)) == ERROR) {
		GUI_MessageBox("\n����С��������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	GUI_MessageBox("\n�뽫�ȱ�������²�״̬\n", "�²�", GUI_MESSAGEBOX_CF_MODAL);
	WM_SetFocus(hDlg);
	if (logic_modifyCoe(meterAddr, &flowErrStr) == ERROR) {
		GUI_MessageBox("\n�޸����ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n�����޸�����ɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void setMeterErrCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		setMeterErrInit(hDlg);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode) {
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case ID_BUTTON_0://�㲥��ȡ���
				userRadioMeterId(hDlg);
				break;
			case ID_BUTTON_1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case ID_BUTTON_2://�޸����
				userModifyCoe(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥��ȡ���
			userRadioMeterId(hDlg);
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://�޸����
			userModifyCoe(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, ID_BUTTON_0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, ID_BUTTON_0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void readValve(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 valeAddr[2 * METER_ADDR_LEN + 1] = { 0 };
	U8 roomTemp[12] = { 0 };//�����¶�
	U8 openTime[12] = { 0 };//����ʱ��
	U8 isHexAddr = ADDR_BCD;

	hItem = WM_GetDialogItem(hDlg, ID_EDIT_0);
	EDIT_GetText(hItem, (S8*)valeAddr, 2 * METER_ADDR_LEN);
	hItem = WM_GetDialogItem(hDlg, ID_CHECKBOX_0);
	isHexAddr = CHECKBOX_GetState(hItem);
	if (isHexAddr== ADDR_BCD? \
		(isNumber(valeAddr, STRLEN(valeAddr)) == ERROR):\
		(isHex(valeAddr, STRLEN(valeAddr)) == ERROR)) {
		GUI_MessageBox("\n���ڷ��ź���������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	if (logic_readValve(valeAddr, roomTemp, openTime) == ERROR) {
		GUI_MessageBox("\n��ȡ��������ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		hItem = WM_GetDialogItem(hDlg, ID_EDIT_1);
		EDIT_SetText(hItem, (const S8*)roomTemp);
		hItem = WM_GetDialogItem(hDlg, ID_EDIT_2);
		EDIT_SetText(hItem, (const S8*)openTime);
	}
	WM_SetFocus(hDlg);
}

void operateValve(WM_HWIN hDlg, U8 openClose)
{
	WM_HWIN hItem;
	U8 valeAddr[2 * METER_ADDR_LEN + 1] = { 0 };
	U8 isHexAddr = ADDR_BCD;
	U8 hint[256] = { 0 };
	U8 err = NO_ERR;

	hItem = WM_GetDialogItem(hDlg, ID_EDIT_0);
	EDIT_GetText(hItem, (S8*)valeAddr, 2 * METER_ADDR_LEN);
	hItem = WM_GetDialogItem(hDlg, ID_CHECKBOX_0);
	isHexAddr = CHECKBOX_GetState(hItem);
	if (isHexAddr == ADDR_BCD ? \
		(isNumber(valeAddr, STRLEN(valeAddr)) == ERROR) : \
		(isHex(valeAddr, STRLEN(valeAddr)) == ERROR)) {
		GUI_MessageBox("\n���ڷ��ź���������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	err = logic_operValve(valeAddr, openClose);
	Lib_sprintf((S8*)hint, "\n%s����%s\n", openClose == OPEN_VALVE ? "��" : "�ر�", err == ERROR ? "ʧ��" : "�ɹ�");
	GUI_MessageBox((const S8*)hint, err == ERROR ? "ʧ��" : "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	WM_SetFocus(hDlg);
}

void openValve(WM_HWIN hDlg)
{
	operateValve(hDlg, OPEN_VALVE);
}

void closeValve(WM_HWIN hDlg)
{
	operateValve(hDlg, CLOSE_VALVE);
}

void setValveCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		setValveInit(hDlg);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode) {
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case ID_BUTTON_0://�ط�
				closeValve(hDlg);
				break;
			case ID_BUTTON_1://����
				openValve(hDlg);
				break;
			case ID_BUTTON_2://��ȡ������Ϣ
				readValve(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�ط�
			closeValve(hDlg);
			break;
		case GUI_KEY_NUM2://����
			openValve(hDlg);
			break;
		case GUI_KEY_NUM3://��ȡ������Ϣ
			readValve(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, ID_BUTTON_0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, ID_BUTTON_0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

U8 getUartMode(em_databit_idx data, em_parity_idx parity, em_stop_idx stop)
{
	U8 i = 0;
	U8	modeCnt = sizeof(gUart_mode_strMap) / sizeof(uart_mode_str);
	for (i = 0; i < modeCnt; i++) {
		if (gUart_mode_strMap[i].databit == data  &&\
			gUart_mode_strMap[i].parity == parity &&\
			gUart_mode_strMap[i].stop == stop) {
			return (i + 1);
		}
	}
	return ERROR;
}

void userSaveConfig(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8  device;
	U32 baud;
	em_databit_idx	data;
	em_parity_idx	parity;
	em_stop_idx		stop;
	U8  mode;
	U8	meterType;
	U8	valveType;

	//�豸
	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_0);
	device = gu8deviceIntArray[DROPDOWN_GetSel(hItem)];
	//������
	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_1);
	baud = gu32baudIntArray[DROPDOWN_GetSel(hItem)];
	//����λ
	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_2);
	data = (em_databit_idx)DROPDOWN_GetSel(hItem);
	//У��λ
	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_3);
	parity = (em_parity_idx)DROPDOWN_GetSel(hItem);
	//ֹͣλ
	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_4);
	stop = (em_stop_idx)DROPDOWN_GetSel(hItem);
	mode = getUartMode(data, parity, stop);
	if (mode == ERROR) {
		GUI_MessageBox("\n�˴������ñ�ϵͳ��֧��\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
		return;
	}

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_5);
	meterType= (em_mtype_idx)DROPDOWN_GetSel(hItem);

	hItem = WM_GetDialogItem(hDlg, ID_DROPDOWN_6);
	valveType = (em_vtype_idx)DROPDOWN_GetSel(hItem);

	if (logic_saveConfig(device, baud, mode, meterType, valveType) == ERROR) {
		GUI_MessageBox("\n��������ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	}
	else {
		GUI_MessageBox("\n�������óɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void deviceConfigCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;
	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		deviceConfigInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case ID_BUTTON_0://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case ID_BUTTON_1://��������
				userSaveConfig(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM2://��������
			userSaveConfig(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, ID_BUTTON_0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, ID_BUTTON_0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/************************************************************************/
/* �������溯��Ⱥ                                                       */
/************************************************************************/

void setMeterErr()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetSetMeterErr, GUI_COUNTOF(widgetSetMeterErr), &setMeterErrCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void setMeterValue()
{
//	int iRet;
//	while (1) {
//		iRet = GUI_ExecDialogBox(widgetSetMeterValue, GUI_COUNTOF(widgetSetMeterValue), &setMeterValueCb, WM_HBKWIN, 0, 0);
//		if (iRet == WM_USER_EXIT)
//			return;
//	}
}

void setMeter()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetMeterRelate, GUI_COUNTOF(widgetMeterRelate), &setMeterCb, WM_HBKWIN, 0, 0);
		switch (iRet) {
		case ID_BUTTON_0:
			setMeterErr();
			break;
		case ID_BUTTON_1:
			setMeterValue();
			break;
		case WM_USER_EXIT:
			return;
		default:
			break;
		}
	}
}

void setValve()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetSetValve, GUI_COUNTOF(widgetSetValve), &setValveCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void configDevice()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetDeviceConfig, GUI_COUNTOF(widgetDeviceConfig), &deviceConfigCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void maingui(void)
{
	int iRet;

	while (1) {
		iRet = GUI_ExecDialogBox(widgetMainFrame, GUI_COUNTOF(widgetMainFrame), &mainCb, WM_HBKWIN, 0, 0);
		switch (iRet) {
		case ID_BUTTON_0:
			setMeter();
			break;
		case ID_BUTTON_1:
			setValve();
			break;
		case ID_BUTTON_2:
			configDevice();
			break;
		case -1:
			return;
		default:
			break;
		}
	}
}
