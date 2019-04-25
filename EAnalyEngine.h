#pragma once

#include "E-Debug.h"



typedef struct sectionAlloc		//�ڴ濽��
{
	UCHAR* SectionAddr;  //������ڴ�ռ��ַ,��ʽ�趨ΪUCHAR* ����һ��
	ULONG  dwBase;       //ԭʼ�������εĻ�ַ
	ULONG  dwSize;       //ԭʼ�������εĴ�С
}*psectionAlloc;

typedef struct _ENTRYINFO // �����������Ϣ
{
	DWORD	dwMagic;		//<- δ֪
	DWORD	dwUnkown1;		//+4 δ֪
	DWORD	dwUnkown2;		//+8 δ֪
	DWORD	dwUserCodeStart;//+c �û����뿪ʼ
	DWORD	dwEString;		//+10 �ַ��� ��Դ       ���û���ַ�����Դ,��Ϊ0
	DWORD	dwEStringSize;	//+14 �ַ��� ��Դ��С   ���û���ַ�����Դ,��Ϊ0
	DWORD	dwEWindow;		//+18 ���������Ϣ      �������ڡ���ǩ�ȿؼ�
	DWORD	dwEWindowSize;	//+1c ��С
	DWORD	dwLibNum;		//+20 ֧�ֿ�����
	DWORD	pLibEntey;		//+24 ֧�ֿ���Ϣ���
	DWORD	dwApiCount;     //+28 Api����
	DWORD	pLibName;		//+2C ָ�������
	DWORD	pApiName;		//+30 ָ��Api����
}*PEENTRYINFO;



class EAnalysis
{
public:
	EAnalysis(ULONG dwVBase);
	~EAnalysis();
	
	UINT AnalysisMode;

	BOOL EStaticLibInit();     //��̬����--��ʼ��
	BOOL GetUserEntryPoint();  //��̬����--ȡ�û�������ַ

	INT FindOriginSection(ULONG addr);		//Ѱ�ҵ�ַ�Ƿ������α���,����index
	INT FindVirutalSection(ULONG addr);	//Ѱ�ҵ�ַ�Ƿ�������ĵ�ַ��,����index

	INT MakeSureInValidSection(ULONG referaddr,ULONG virtualaddr);		//ȷ���õ��ĵ�ַ�ںϷ�������
		
	INT UpdateSection(ULONG addr);	
	INT AddSection(ULONG addr);  //�ڴ濽��������������,�����µ�index

	DWORD   Search_BinEx(byte *pSrc, byte *pTrait, int nSrcLen, int nTraitLen);
	ULONG	O2V(ULONG dwVaddr, UINT index);		//ԭʼ��ַת��Ϊ�����ַ
	ULONG	V2O(ULONG dwOaddr, UINT index);		//�����ַת��Ϊԭʼ��ַ


	DWORD	GetPoint(DWORD dwAddr);
	DWORD	GetOriginPoint(DWORD dwAddr, UINT index);
	DWORD dwUsercodeStart; //�û��������ʼ��ַ
	DWORD dwUsercodeEnd;   //�û�����Ľ�����ַ

	vector<sectionAlloc> SectionMap;    //ά��һ���ڴ濽����

	ULONG DLLCALL = 0;					//����DLL_CALL��ַ,�ڲ���DLL�����ʱ����õ�
	ULONG KRNLNFUNCTION = 0;			//����Krn�������õ�ַ,�ڲ���Krn��������ʱ����õ�

	PEENTRYINFO pEnteyInfo; // entry info

	_ENTRYINFO _EnteyInfo; // entry info
private:
protected:
};