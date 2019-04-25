/*��������������������������������������������������������
E-debug   Ϊ���������Խṹ���ṩ֧�ֵķ�������
��������������������������������������������������������*/
#include "stdafx.h"
#include "E-Debug.h"
#include "MainWindow.h"
#include "EAnalyEngine.h"

extern CMainWindow *pMaindlg;
extern map<string, LIBMAP> m_LibMap;
EAnalysis	*pEAnalysisEngine;

INT EAnalysis::MakeSureInValidSection(ULONG referaddr,ULONG virtualaddr){
	int index = FindVirutalSection(referaddr);	//ȡ�õ�ǰ���������index

	ULONG oaddr = V2O(virtualaddr, index);
	if (FindOriginSection(oaddr) == -1) {		//ת��Ϊʵ�ʵ�ַ�����ж�
		return AddSection(oaddr);	
	}
	return index;	
}

INT EAnalysis::FindVirutalSection(ULONG addr) {		//����
	for (UINT i = 0;i < SectionMap.size();i++) {
		if (addr >= (ULONG)SectionMap[i].SectionAddr && addr < ((ULONG)SectionMap[i].SectionAddr + SectionMap[i].dwSize)) {
			return i;
		}
	}
	return -1;
}

INT EAnalysis::FindOriginSection(ULONG addr) {
	for (UINT i = 0;i < SectionMap.size();i++) {
		if (addr >= SectionMap[i].dwBase && addr < (SectionMap[i].dwBase + SectionMap[i].dwSize)) {
			return i;
		}
	}
	return -1;
}

INT EAnalysis::UpdateSection(ULONG addr) {
	INT index = FindOriginSection(addr);
	t_memory* T_memory;
	if (index != -1) {		//�Ѿ�������һ��ҳ��ҲҪ���¿���һ��
		VirtualFree(SectionMap[index].SectionAddr, 0, MEM_RELEASE);
		T_memory = Findmemory(addr);
		if (!T_memory) {
			//pMaindlg->outputInfo("��ѯ�ڴ�ʧ��!");
			return -1;
		}
		SectionMap[index].dwBase = T_memory->base;
		SectionMap[index].dwSize = T_memory->size;
		SectionMap[index].SectionAddr = (UCHAR *)VirtualAlloc(NULL, SectionMap[index].dwSize, MEM_COMMIT, PAGE_READWRITE);
		if (!SectionMap[index].SectionAddr) {
			pMaindlg->outputInfo("�����ڴ�ʧ��!");
			return -1;
		}
		ULONG Rsize = Readmemory(SectionMap[index].SectionAddr, SectionMap[index].dwBase, SectionMap[index].dwSize, MM_RESILENT);
		if (Rsize != SectionMap[index].dwSize) {
			pMaindlg->outputInfo("��ȡ�ڴ��С��ͬ��");
			return -1;
		}
		return index;
	}
	return AddSection(addr);
}

INT EAnalysis::AddSection(ULONG addr) {

	sectionAlloc addsection = { 0 };
	t_memory* T_memory;

	T_memory = Findmemory(addr);
	if (!T_memory) {
		//pMaindlg->outputInfo("��ѯ�ڴ�ʧ��!");
		return -1;
	}

	addsection.dwBase = T_memory->base;
	addsection.dwSize = T_memory->size;
	addsection.SectionAddr = (BYTE *)VirtualAlloc(NULL, addsection.dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (addsection.SectionAddr == NULL) {
		pMaindlg->outputInfo("�����ڴ�ʧ��!");
		return -1;
	}

	ULONG Rsize=Readmemory(addsection.SectionAddr, addsection.dwBase, addsection.dwSize, MM_RESILENT);
	if (Rsize != addsection.dwSize) {
		pMaindlg->outputInfo("��ȡ�ڴ��С��ͬ��");
		return -1;
	}
	SectionMap.push_back(addsection);
	//pMaindlg->outputInfo("ʵ�ʷ����ڴ��С:%X", T_memory->size);
	return SectionMap.size()-1;
}

EAnalysis::EAnalysis(ULONG dwVBase)
{
	for (UINT n = 0;n < SectionMap.size();n++) {
		VirtualFree(SectionMap[n].SectionAddr, 0, MEM_RELEASE);
	}
	m_LibMap.clear();
	SectionMap.clear();
	UpdateSection(dwVBase);
}

EAnalysis::~EAnalysis()
{

}

BOOL EAnalysis::EStaticLibInit() {    //�����Ծ�̬���� ʶ���ʼ��
	DWORD	dwResult;
	DWORD	dwCalc;

	BYTE SearchCode[17] = { 0x50,0x64,0x89,0x25,0x00,0x00,0x00,0x00,
						  0x81,0xEC,0xAC,0x01,0x00,0x00,0x53,0x56,0x57 };

	dwResult = Search_Bin(SectionMap[0].SectionAddr, SearchCode, SectionMap[0].dwSize, sizeof(SearchCode));

	if (dwResult == 0)
	{
		return FALSE;
	}


	dwCalc = dwResult + 0x26 + SectionMap[0].dwBase;
	
	DWORD EntryAddr = GetPoint(O2V(dwCalc,0));

	if (EntryAddr - SectionMap[0].dwBase > SectionMap[0].dwSize)  //�����ڵ�ַ����һ������,�����һ�ݱ�
	{
		int index = UpdateSection(EntryAddr);
		pEnteyInfo = (PEENTRYINFO)O2V(EntryAddr, index);
	}
	else {
		pEnteyInfo = (PEENTRYINFO)O2V(EntryAddr, 0);
	}

	// 2019-04-25 WYT ����������¸��½����ݶ����µ�pEnteyInfoָ����ЧBUG
	memcpy(&_EnteyInfo, pEnteyInfo, sizeof(_EnteyInfo));
	pEnteyInfo = &_EnteyInfo;

	dwUsercodeStart = pEnteyInfo->dwUserCodeStart;

	return TRUE;
}

BOOL EAnalysis::GetUserEntryPoint() {
	BYTE data[21] = {
		0x55, 0x8B, 0xEC, 0x51, 0x53, 0x56, 0x8B, 0xF1, 0x57, 0x8B, 0x4E, 0x68,
		0x8D, 0x86, 0xD8, 0x00, 0x00, 0x00, 0x50, 0x51, 0xE8 };

	DWORD	dwResult;
	DWORD	dwStartEntry;

	dwResult = Search_Bin(SectionMap[0].SectionAddr, data, SectionMap[0].dwSize, sizeof(data));
	if (dwResult == 0)
	{
		return false;
	}
	dwStartEntry = dwResult + 0x37 + SectionMap[0].dwBase; //call addr
	dwUsercodeEnd = GetPoint(O2V(dwStartEntry,0) + 1) + dwStartEntry + 5;

	return true;
}


ULONG EAnalysis::O2V(ULONG dwOaddr, UINT index)  //ʵ�ʵ�ַ�������ַ
{
	return dwOaddr + (ULONG)SectionMap[index].SectionAddr - SectionMap[index].dwBase;
}
ULONG EAnalysis::V2O(ULONG dwVaddr, UINT index) //�����ַ��ʵ�ʵ�ַ
{
	return dwVaddr + (ULONG)SectionMap[index].dwBase - (ULONG)SectionMap[index].SectionAddr;
}


DWORD EAnalysis::GetPoint(DWORD dwAddr)
{
	return *(DWORD*)dwAddr;
}
DWORD EAnalysis::GetOriginPoint(DWORD dwAddr,UINT index)
{
	DWORD	pDwData;
    pDwData = GetPoint(O2V(dwAddr, index));
	return pDwData;
}


DWORD EAnalysis::Search_BinEx(byte *pSrc, byte *pTrait, int nSrcLen, int nTraitLen) //��ȷ�汾,��ģ��ƥ��
{
	if (IsBadReadPtr(pSrc, 4) == TRUE)
	{
		return 0;
	}
	int i, j, k;
	for (i = 0; i <= (nSrcLen - nTraitLen); i++)
	{
		if (pSrc[i] == pTrait[0])
		{
			k = i;
			j = 0;
			while (j < nTraitLen)
			{
				k++; j++;
				if (pSrc[k] != pTrait[j])
				{
					break;
				}
			}

			if (j == nTraitLen)
			{
				return i;
			}

		}

	}
	return 0;
}

