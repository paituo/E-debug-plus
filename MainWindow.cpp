/*��������������������������������������������������������
E-debug   �������潻���Ľӿ�
��������������������������������������������������������*/
#include "stdafx.h"
#include "E-Debug.h"
#include "MainWindow.h"
#include "EAnalyEngine.h"
#include <windows.h>

CMainWindow *pMaindlg;		//һ�ݴ��ڶ�Ӧһ�ݴ���ָ��
vector<CDialog*> Tab_HWND;	//���ڿؼ�ָ��,�������Դ��ݵ���������

IMPLEMENT_DYNAMIC(CMainWindow, CDialog)

CMainWindow::CMainWindow(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MainWindow, pParent)
{
	
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_LOG, m_output);
}


BEGIN_MESSAGE_MAP(CMainWindow, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainWindow::OnTcnSelchangeTab1)
	ON_LBN_SELCHANGE(IDC_LOG, &CMainWindow::OnLbnSelchangeLog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMainWindow ��Ϣ�������


BOOL CMainWindow::OnInitDialog() {
	CDialog::OnInitDialog();
	
	pMaindlg = this;   //���洰��ָ��
	g_hInstace = AfxGetInstanceHandle();  //����ʵ��,���Ժ���

	HICON hIcon = LoadIcon(g_hInstace, MAKEINTRESOURCE(IDI_ICON));	//���ô���ͼ��
	SetIcon(hIcon, FALSE);
	SetIcon(hIcon, TRUE);

	CRect rc;
	m_Tab.GetClientRect(&rc);
	rc.top += 26;
	rc.left += 4;
	rc.right -= 6;
	rc.bottom -= 6;

	ULONG uBase, uSize;
	Getdisassemblerrange(&uBase, &uSize);
	outputInfo("->��ʼ������ǰ����....  ������ַ: % 08X  �ڴ��С: % 08X", uBase, uSize);

	pEAnalysisEngine = new EAnalysis(uBase);   //��ʼ���ڴ�
	
	Tab_HWND.clear();
	m_Tab.InsertItem(0, _T("������"));	//��ʼ�������ⴰ��
	m_page0.Create(IDD_PAGE0, &m_Tab);	
	m_page0.MoveWindow(&rc);
	Tab_HWND.push_back(m_page0.GetHwnd());		//��һ�����ڱض�Ϊ������

	m_Tab.InsertItem(1, _T("����ʶ��")); //��ʼ������ʶ�𴰿�
	m_page1.Create(IDD_PAGE1, &m_Tab);
	m_page1.MoveWindow(&rc);
	m_page1.ShowWindow(SW_SHOW);
	Tab_HWND.push_back(m_page1.GetHwnd());		//�ڶ������ڱض�Ϊ����ʶ��

	if (pEAnalysisEngine->AnalysisMode == StaticMode) {
		m_Tab.InsertItem(2, _T("API����"));
		m_page2.Create(IDD_PAGE2, &pMaindlg->m_Tab);
		m_page2.MoveWindow(&rc);
		Tab_HWND.push_back(m_page2.GetHwnd());
	}

	m_Tab.InsertItem(3, _T("����ʶ��")); //��ʼ������ʶ�𴰿�
	m_page3.Create(IDD_PAGE3, &m_Tab);
	m_page3.MoveWindow(&rc);
	Tab_HWND.push_back(m_page3.GetHwnd());		//���������ڱض�Ϊ����ʶ��

	
	m_Tab.SetCurSel(1);
	return true;
	INT nPos;

		m_Tab.SetCurSel(1);
		m_page1.ShowWindow(true);
	//}
	//else if (AnalysisMode == CMode)
	{
		m_Tab.InsertItem(0, _T("����"));
		m_Tab.InsertItem(1, _T("������"));

		MessageBoxA(NULL, "To Be Continued", "����",MB_ICONINFORMATION);
		return true;
		//m_page1.Create(IDD_PAGE1, &m_Tab);
		//m_page1.MoveWindow(&rc);
	}
	
}

void CMainWindow::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCursel = m_Tab.GetCurSel();
	
	for (UINT n = 0;n < Tab_HWND.size();n++) {
		Tab_HWND[n]->ShowWindow(SW_HIDE);
	}
	Tab_HWND[nCursel]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

int CMainWindow::outputInfo(char *formatText, ...)
{
	USES_CONVERSION;
	char buf[10000] = { 0 };
	va_list st;
	va_start(st, formatText);
	vsprintf_s(buf, formatText, st);
	va_end(st);
	return m_output.InsertString(-1, A2W(buf));
}


void CMainWindow::OnLbnSelchangeLog()
{
	int		nCurSel;
	DWORD	dwItemData;
	nCurSel = m_output.GetCurSel();
	dwItemData = m_output.GetItemData(nCurSel);
	if (dwItemData != 0)
	{
		Setcpu(NULL, dwItemData, NULL, NULL, CPU_NOFOCUS);
	}
}




void CMainWindow::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (MessageBox(L"ȷ��Ҫ�˳�����������", L"�˳���ʾ", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		return; 

	CDialog::OnClose();
}
