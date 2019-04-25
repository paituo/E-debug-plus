// Page3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "E-Debug.h"
#include "Page3.h"
#include "MainWindow.h"
#include "EAnalyEngine.h"




// CPage3 �Ի���

IMPLEMENT_DYNAMIC(CPage3, CDialog)



HTREEITEM hroot;

CPage3::CPage3(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PAGE3, pParent)
{

}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_STATIC_BOX, ControlType);
	DDX_Control(pDX, IDC_EDIT_WINDOWNAME, WindowName);
	DDX_Control(pDX, IDC_EDIT_WINDOWID, WindowID);
	DDX_Control(pDX, IDC_EDIT_CONTROLNAME, ControlName);
	DDX_Control(pDX, IDC_EDIT_CONTROLID, ControlID);
	DDX_Control(pDX, IDC_EDIT_CONTROLCLASS, ControlClass);
}

CDialog* CPage3::GetHwnd() {
	return this;
}

BEGIN_MESSAGE_MAP(CPage3, CDialog)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, &CPage3::OnTvnItemexpandingTree1)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE1, &CPage3::OnTvnSelchangingTree1)
END_MESSAGE_MAP()


// CPage3 ��Ϣ�������

BOOL CPage3::OnInitDialog() {
	CDialog::OnInitDialog();


	m_Tree.SetLineColor(RGB(0, 0, 255));

	hroot=m_Tree.InsertItem(_T("�����Դ���"));

	
	m_ICO.Create(16,16,ILC_COLOR32,255,255);
	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_UnKnow));  //Ĭ��ͼ��

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Window));  //����  1

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_EDIT));   //�༭�� 2

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Pic));    //ͼƬ�� 3 

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ShapeBox));    //���ο� 4

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_DrawPanel));    //���� 5

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_GroupBox));    //����� 6

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Label));   //��ǩ 7

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_BUTTON));  //��ť 8

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_CheckBox));  //ѡ��� 9

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_RadioBox));  //��ѡ�� 10

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ComboBox));  //��Ͽ� 11

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ListBox));  //�б�� 12
	
	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ChkListBox));  //ѡ���б�� 13

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_HScrollBar));  //��������� 14

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_VScrollBar));  //��������� 15

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ProcessBar));  //������ 16

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_SliderBar));  //������ 17

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Tab));  //ѡ��� 18

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_AnimateBox));  //Ӱ��� 19

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_DatePicker));  //���ڿ� 20

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_MonthCalendar));  //���� 21

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_DriverBox));  //�������� 22

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_DirBox));  //Ŀ¼�� 23

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_FileBox));  //�ļ��� 24

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ColorPicker));  //��ɫѡ���� 25

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_HyperLinker));  //�������ӿ� 26

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Spin));  //������ 27

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_CommonDlg));  //ͨ�öԻ��� 28

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Timer));  //ʱ�� 29

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_printer));  //��ӡ�� 30

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_UDP));  //���ݱ� 31

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Client));  //�ͻ� 32

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Server));  //������ 33

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_SerialPort));  //�˿� 34

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_Grid));  //��� 35

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_DataSrc));  //����Դ 36
	
	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_NProvider));  //ͨ���ṩ�� 37

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_DBProvider));  //���ݿ��ṩ�� 38

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_PicBtn));  //ͼ�ΰ�ť 39

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ODBCDB));  //�ⲿ���ݿ� 40

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ODBCProvider));  //�ⲿ���ݿ��ṩ�� 41

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_StatusBar));  //״̬�� 42

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ToolBar));  //������ 43

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_ListView));  //�����б�� 44

	m_ICO.Add(AfxGetApp()->LoadIcon(IDI_ICON_TransLabel));  //͸����ǩ 45

	m_Tree.SetImageList(&m_ICO,TVSIL_NORMAL);

	//��������������������������������
	WindowInfo m_WindowInfo;
	DWORD EipAddr = pEAnalysisEngine->pEnteyInfo->dwEWindow; //Eip��ַΪ��ǰ������ַ
	if (EipAddr == 0) {
		return TRUE;
	}

	UINT r_index = pEAnalysisEngine->FindOriginSection(EipAddr);
	if (r_index == -1) {
		r_index = pEAnalysisEngine->AddSection(EipAddr);
	}

	m_WindowInfo.WindowCount =*(unsigned long*)pEAnalysisEngine->O2V(EipAddr,r_index)>>3;
	if (m_WindowInfo.WindowCount == 0) {
		return TRUE;
	}


	CString WinID;
	CString ControlID;

	
	for (UINT i = 0;i < m_WindowInfo.WindowCount;i++) {
		EipAddr = EipAddr + 4;
		WinID.Format(L"0x%X", *(DWORD*)(pEAnalysisEngine->O2V(EipAddr,r_index)));
		HTREEITEM temp = m_Tree.InsertItem(WinID, hroot);
		m_WindowInfo.WindowId.push_back(temp);
		m_Tree.SetItemData(temp, i); //���洰��index
	}

	EipAddr = EipAddr + 4 * (m_WindowInfo.WindowCount+1); //����WindowAddr

	WindowPropery m_WindowPropery = {};

	//��������������������������������������������������������������������

	

	DWORD NextWindowProery = EipAddr + 24; //������ʼ��ַ


	for (UINT i = 0;i < m_WindowInfo.WindowCount;i++) {      //��������
		Window.push_back(m_WindowPropery);
		EipAddr = EipAddr + 16;

		Window[i].ControlCount = *(unsigned long*)pEAnalysisEngine->O2V(EipAddr,r_index);  //�õ��ؼ�����
		
		if (Window[i].ControlCount == 0) {
			return true;
		}
		
		EipAddr = EipAddr + 4;
		Window[i].ControlSize= *(unsigned long*)pEAnalysisEngine->O2V(EipAddr,r_index);   //�õ��ؼ��ܴ�С
		
		for (UINT j = 0;j < Window[i].ControlCount;j++) {
			EipAddr = EipAddr + 4;
			ControlID.Format(L"0x%X", *(unsigned long*)pEAnalysisEngine->O2V(EipAddr, r_index));
			Window[i].ControlID.push_back(m_Tree.InsertItem(ControlID, m_WindowInfo.WindowId[i])); //����ؼ�ID
		}
		
		for (UINT t = 0;t < Window[i].ControlCount;t++) {          //�����ؼ�
			EipAddr = EipAddr + 4;
			Window[i].Controloffset.push_back(*(unsigned long*)pEAnalysisEngine->O2V(EipAddr, r_index));
			
		}



		DWORD ControlStartAddr = EipAddr + 8;  //��ʼ���ؼ���ַ

		for (UINT t = 0;t < Window[i].ControlCount;t++) {

			EipAddr = ControlStartAddr+ Window[i].Controloffset[t];
			Window[i].ChildWindowId = *(unsigned long*)pEAnalysisEngine->O2V(EipAddr, r_index);

			m_Tree.SetItemData(Window[i].ControlID[t],t); //����ؼ�˳��

			switch (Window[i].ChildWindowId)
			{
			case 0x10001:  //����
				Window[i].ControlType.push_back("����");
				m_Tree.SetItemImage(Window[i].ControlID[t], 1, 1);
				break;
			case 0x10005: //�༭��
				Window[i].ControlType.push_back("�༭��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 2, 2);
				break;
			case 0x10006: //ͼƬ��
				Window[i].ControlType.push_back("ͼƬ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 3, 3);
				break;
			case 0x10007: //���ο�
				Window[i].ControlType.push_back("���ο�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 4, 4);
				break;
			case 0x10008: //����
				Window[i].ControlType.push_back("����");
				m_Tree.SetItemImage(Window[i].ControlID[t], 5, 5);
				break;
			case 0x10009: //�����
				Window[i].ControlType.push_back("�����");
				m_Tree.SetItemImage(Window[i].ControlID[t], 6, 6);
				break;
			case 0x1000A: //��ǩ
				Window[i].ControlType.push_back("��ǩ");
				m_Tree.SetItemImage(Window[i].ControlID[t], 7, 7);
				break;
			case 0x1000B: //��ť
				Window[i].ControlType.push_back("��ť");
				m_Tree.SetItemImage(Window[i].ControlID[t], 8, 8);
				break;
			case 0x1000C: //ѡ���
				Window[i].ControlType.push_back("ѡ���");
				m_Tree.SetItemImage(Window[i].ControlID[t], 9, 9);
				break;
			case 0x1000D://��ѡ��
				Window[i].ControlType.push_back("��ѡ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 10, 10);
				break;
			case 0x1000E://��Ͽ�
				Window[i].ControlType.push_back("��Ͽ�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 11, 11);
				break;
			case 0x1000F://�б��
				Window[i].ControlType.push_back("�б��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 12, 12);
				break;
			case 0x10010://ѡ���б��
				Window[i].ControlType.push_back("ѡ���б��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 13, 13);
				break;
			case 0x10011://���������
				Window[i].ControlType.push_back("���������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 14, 14);
				break;
			case 0x10012://���������
				Window[i].ControlType.push_back("���������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 15, 15);
				break;
			case 0x10013:
				Window[i].ControlType.push_back("������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 16, 16);
				break;
			case 0x10014:
				Window[i].ControlType.push_back("������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 17, 17);
				break;
			case 0x10015:
				Window[i].ControlType.push_back("ѡ���");
				m_Tree.SetItemImage(Window[i].ControlID[t], 18, 18);
				break;
			case 0x10016:
				Window[i].ControlType.push_back("Ӱ���");
				m_Tree.SetItemImage(Window[i].ControlID[t], 19, 19);
				break;
			case 0x10017:
				Window[i].ControlType.push_back("���ڿ�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 20, 20);
				break;
			case 0x10018:
				Window[i].ControlType.push_back("����");
				m_Tree.SetItemImage(Window[i].ControlID[t], 21, 21);
				break;
			case 0x10019:
				Window[i].ControlType.push_back("��������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 22, 22);
				break;
			case 0x1001A:
				Window[i].ControlType.push_back("Ŀ¼��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 23, 23);
				break;
			case 0x1001B:
				Window[i].ControlType.push_back("�ļ���");
				m_Tree.SetItemImage(Window[i].ControlID[t], 24, 24);
				break;
			case 0x1001C:
				Window[i].ControlType.push_back("��ɫѡ����");
				m_Tree.SetItemImage(Window[i].ControlID[t], 25, 25);
				break;
			case 0x1001D:
				Window[i].ControlType.push_back("�������ӿ�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 26, 26);
				break;
			case 0x1001E:
				Window[i].ControlType.push_back("������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 27, 27);
				break;
			case 0x1001F:
				Window[i].ControlType.push_back("ͨ�öԻ���");
				m_Tree.SetItemImage(Window[i].ControlID[t], 28, 28);
				break;
			case 0x10020:
				Window[i].ControlType.push_back("ʱ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 29, 29);
				break;
			case 0x10021:
				Window[i].ControlType.push_back("��ӡ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 30, 30);
				break;
			case 0x10024:
				Window[i].ControlType.push_back("���ݱ�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 31, 31);
				break;
			case 0x10025:
				Window[i].ControlType.push_back("�ͻ�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 32, 32);
				break;
			case 0x10026:
				Window[i].ControlType.push_back("������");
				m_Tree.SetItemImage(Window[i].ControlID[t], 33, 33);
				break;
			case 0x10027:
				Window[i].ControlType.push_back("�˿�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 34, 34);
				break;
			case 0x10029:
				Window[i].ControlType.push_back("���");
				m_Tree.SetItemImage(Window[i].ControlID[t], 35, 35);
				break;
			case 0x1002A:
				Window[i].ControlType.push_back("����Դ");
				m_Tree.SetItemImage(Window[i].ControlID[t], 36, 36);
				break;
			case 0x1002B:
				Window[i].ControlType.push_back("ͨ���ṩ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 37, 37);
				break;
			case 0x1002C:
				Window[i].ControlType.push_back("���ݿ��ṩ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 38, 38);
				break;
			case 0x1002D:
				Window[i].ControlType.push_back("ͼ�ΰ�ť");
				m_Tree.SetItemImage(Window[i].ControlID[t], 39, 39);
				break;
			case 0x1002E:
				Window[i].ControlType.push_back("�ⲿ���ݿ�");
				m_Tree.SetItemImage(Window[i].ControlID[t], 40, 40);
				break;
			case 0x1002F:
				Window[i].ControlType.push_back("�ⲿ���ݿ��ṩ��");
				m_Tree.SetItemImage(Window[i].ControlID[t], 41, 41);
				break;
			default:
				Window[i].ControlType.push_back("δ֪");
				//pMaindlg->outputInfo("%X", Window[i].ChildWindowId);
				break;
			}
		}

		NextWindowProery = NextWindowProery + Window[i].ControlSize +24;
		EipAddr = NextWindowProery -24 ;
	}

	
	for (UINT i = 0;i < m_WindowInfo.WindowCount;i++) {
		m_Tree.Expand(m_WindowInfo.WindowId[i],TVE_EXPAND);
	}
	m_Tree.Expand(hroot,TVE_EXPAND);
	
	return TRUE;
}



void CPage3::OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult)   //��������Դ��ڵ�ʱ��,��������
{
	USES_CONVERSION;
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if (pNMTreeView->itemNew.hItem == hroot && pNMTreeView->action==TVE_COLLAPSE) {
		*pResult = TRUE;
	}
	else {
		*pResult = 0;
	}
}


void CPage3::OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult)  //�ؼ�������
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	if (m_Tree.GetChildItem(pNMTreeView->itemNew.hItem) == 0) {   //˵��Ϊ�ؼ�
		
		DWORD m_ParentIndex = m_Tree.GetItemData(m_Tree.GetParentItem(pNMTreeView->itemNew.hItem));
		DWORD n_index = m_Tree.GetItemData(pNMTreeView->itemNew.hItem);
		
		//if (!Window[m_index].ControlType[n_index].empty()) {
			// ControlType.SetWindowText(A2W(Window[m_index].ControlType[n_index].c_str()));

		//WindowName.SetWindowText(str);
		WindowID.SetWindowText(m_Tree.GetItemText(m_Tree.GetParentItem(pNMTreeView->itemNew.hItem)));
		//ControlName.SetWindowText(A2W(Window[m_ParentIndex].ControlType[n_index].c_str()));
		ControlID.SetWindowText(m_Tree.GetItemText(pNMTreeView->itemNew.hItem));
		ControlClass.SetWindowText(A2W(Window[m_ParentIndex].ControlType[n_index].c_str()));

		//}
	}

	*pResult = 0;
}
