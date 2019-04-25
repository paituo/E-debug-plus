#pragma once
#include "E-Debug.h"

// CPage3 �Ի���
typedef struct WindowInfo    //������Ϣ���ڴ�ռ�ֲ�
{
	DWORD WindowCount;            //���ڵĸ���
	vector<HTREEITEM> WindowId;   //���ڵ�ID,��������Ŵ��ڵĸ��ڵ�
	vector<DWORD> WindowAddr;     //�����ڴ��ַ,�ڱ��������ʱ�������ַ�Ѿ�ʧЧ��
	//vector<WindowPropery> Windows;
}*pWindowInfo;


/*typedef struct ButtonPropery
{
	DWORD ChildWindowId;  //�Ӵ���ID
	BYTE ZeroByte1[20];
	string name;  //��ť����
	BYTE ZeroByte2[5];
	DWORD left; //���
	DWORD top;  //����
	DWORD width; //���
	DWORD height;//�߶�
	BYTE ZeroByte3[12];
	DWORD Propery;  //3,4??

	DWORD Unknow3;
	string tag;         //���,���Ϊ��,��ռһ��NULL�ֽ�
	DWORD Unknow4;
	DWORD propery;      //�����Ƶ�һλΪ����,�ڶ�λΪ��ֹ,����λΪ��ͣ������.1Ϊ��,0Ϊ��
	DWORD focusorder;   //ͣ��˳��

	BYTE Unknow1[28];
	DWORD style;        //����,0Ϊͨ��,1ΪĬ��
	DWORD HorzAlign;    //������뷽ʽ,0Ϊ���,1Ϊ����,2Ϊ�ұ�
	DWORD VertAlign;    //������뷽ʽ,0Ϊ����,1Ϊ����,2Ϊ�ױ�

	DWORD picSize;  //ͼƬ��Դ��С   BYTE pic[picSize];

	DWORD fontSize; //������Դ��С  BYTE font[fontSize]; //����,���������Դ��СΪ0,���ֵ������

	DWORD captionSize;  //BYTE caption[captionSize];  //����,������ⳤ��Ϊ0,���ֵ������
};*/

typedef struct WindowPropery  //��������
{
	DWORD WindowDataAddr;		  //���ڱ��븽�ӵ���������?
	DWORD ControlDataAddr;		  //�ؼ����븽�ӵ���������?
	DWORD ZeroByte1;			  //0x00000000
	DWORD ZeroByte2;			  //0x00000000
	DWORD ControlCount;			  //�ؼ��ĸ���
	DWORD ControlSize;			  //�������ռ�ռ��ܴ�С
	vector<HTREEITEM> ControlID;   //�ؼ���ID,��������ſؼ��ĸ��ڵ�

	DWORD ZeroByte3;			  //0x00000000
	vector<DWORD> Controloffset;  //�ؼ��ռ��С


	DWORD ChildWindowId;  //�Ӵ��ڵ�ID,ע:ÿ��������Ӵ���Ĭ��Ϊ0x10001 
	vector<string> ControlType;   //�ؼ�����,Ϊ�����������ӵģ�ԭ��������
	BYTE ZeroByte[26];    //�հ��ֽ�

	DWORD left; //���
	DWORD top;  //����
	DWORD width; //���
	DWORD height; //�߶�
	BYTE UnknowByte1[12]; //�в����
	DWORD MousePointerSize; //�Զ������ָ����ռ�ֽڼ��Ĵ�С,�����ѡ���е����ָ��,��Ϊ4
	DWORD MousePointer;  //ѡ���е����ָ������ֵ,���Ϊ�Զ������ָ��,��Ϊ-1,Ĭ����Ϊ0    //BYTE customMousePointer[MousePointerSize]; //�Զ������ָ���ֽڼ�,���Ϊѡ���е����ָ��,���ֵ������
	                     //��׼��ͷ�� 0x7F00,ʮ����0x7F03
						 //�ı��༭�� 0x7F01,ɳ©��0x7F02
						 //��ͷ���ʺ��� 0x7F8B,��ͷ��ɳ©��0x7F8A
					     //��ֹ����0x7F88,�����ͷ��0x7F86
						 //��<->����ͷ��0x7F83,��<->�ϼ�ͷ��0x7F85
						 //��<->����ͷ��0x7F82,��<->����ͷ��0x7F84
						 //���ϼ�ͷ��0x7F04,����0x7F89
	                     
	
	//string tag;   //���,���Ϊ��,��ռһ��NULL�ֽ�
	DWORD ZeroByte4;  //Ϊ0
	DWORD visible_disable;  //�����Ƶ�һλΪ����,1Ϊ��,0Ϊ��;�ڶ�λΪ��ֹ,1Ϊ��,0Ϊ��
	BYTE UnknowByte2[40]; //�в����
	DWORD border;   //0Ϊ�ޱ߿�,1Ϊ��ͨ�ɵ��߿�,2Ϊ��ͨ�̶��߿�,3Ϊխ����ɵ��߿�,4Ϊխ����̶��߿�,5Ϊ����ʽ�ɵ��߿�,6Ϊ����ʽ�̶��߿�
	DWORD BackPicMode;  //0ΪͼƬ������,1ΪͼƬƽ��,2ΪͼƬ����,3Ϊ����ͼƬ
	DWORD BackColor; //0xFF000000����Ĭ�ϵ�ɫ,����ΪR<<6||G<<4||B<<2||0;

	DWORD MaxBtn; //��󻯰�ť,1Ϊ��,0Ϊ��
	DWORD MinBtn; //��С����ť,1Ϊ��,0Ϊ��
	DWORD CtrlBtn;  //���ư�ť,1Ϊ��,0Ϊ��
	DWORD pos;   //λ��,0Ϊͨ��,1Ϊ����,2Ϊ��С��,3Ϊ���

	DWORD CanMove;//�ɷ��ƶ�,1Ϊ��,0Ϊ��
	DWORD PlayCount;  //���Ŵ���,0Ϊѭ������,1Ϊ������1��,2Ϊ������
	DWORD EnterToNext; //�س����ƽ���,1Ϊ��,0Ϊ��
	DWORD EscClose;  //Esc���ر�,1Ϊ��,0Ϊ��

	DWORD F1OpenHelp; //F1���򿪰���,1Ϊ��,0Ϊ��
	DWORD HelpContext; //������־ֵ
	DWORD ShowInTaskBar; //������������ʾ,1Ϊ��,0Ϊ��
	DWORD HitMove; //�����ƶ�,1Ϊ��,0Ϊ��

	DWORD shape; //����,ȡֵ��ΧΪ0-29
	DWORD Topmost; //������ǰ,1Ϊ��,0Ϊ��
	DWORD KeepTitleBarActive;//���ֱ���������,1Ϊ��,0Ϊ��
	DWORD ClassNameSize; //������������                        //BYTE ClassName[ClassNameSize];  //��������,��������������Ϊ0,���ֵ������

	DWORD BackPicSize;   //��ͼ��С,0��ʾ�޵�ͼ            //DWORD BackPic[BackPicSize];  ��ͼͼƬ,�����ͼ��СΪ0,���ֵ������
	DWORD iconSize;     //ͼ���С                         //BYTE icon[iconSize]; //ͼ��,���ͼ���СΪ0,���ֵ������
	DWORD BackMusicSize;  //�������ִ�С                   //BYTE BackMusic[BackMusicSize];  //��������,����������ִ�СΪ0,���ֵ������
	DWORD captionSize;   //���ⳤ��                        //BYTE caption[captionSize];  //����,������ⳤ��Ϊ0,���ֵ������
	DWORD HelpFileNameSize;  //�����ļ�������              //BYTE HelpFileName[HelpFileNameSize]; //�����ļ���,��������ļ�������Ϊ0,���ֵ������
}*pWindowPropery;



class CPage3 : public CDialog
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage3();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDialog* GetHwnd();

	virtual BOOL OnInitDialog();
	CTreeCtrl m_Tree;
	CImageList m_ICO;
	CStatic ControlType;
	CEdit WindowName;
	CEdit WindowID;
	CEdit ControlName;
	CEdit ControlID;
	CEdit ControlClass;

	vector<WindowPropery> Window;

	afx_msg void OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
