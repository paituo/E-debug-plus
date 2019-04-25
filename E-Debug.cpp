/*��������������������������������������������������������
E-debug   DLL��OD�Ľ����ӿ�
��������������������������������������������������������*/


#include "stdafx.h"
#include "E-Debug.h"
#include "MainWindow.h"

HINSTANCE g_hInstace;		//һ��E-debug��Ӧһ��hInstace
vector<EsigInfo> EsigList;  //һ��E-debug��Ӧһ��EsigList


BOOL LoadSig(char* lpMapPath,char* Category) {		//��ȡ��Ϣ��EsigList
	HANDLE hFile = CreateFileA(lpMapPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD	dwHitSize = 0;
	DWORD	dwSize = GetFileSize(hFile, &dwHitSize);
	DWORD	dwReadSize = 0;
	char* pMap = (char*)malloc(dwSize);

	ReadFile(hFile, pMap, dwSize, &dwReadSize, NULL);	//��ȡ�ı����ڴ�

	string Sig = pMap;

	string Config = GetMidString(Sig, "******Config******\r\n", "******Config_End******", 0);
	string Name = GetMidString(Sig, "Name=", "\r\n", 0);
	string Description = GetMidString(Sig, "Description=", "\r\n", 0);

	if (!Name.size()) {
		return false;
	}
	
	EsigInfo saveinfo;
	saveinfo.Category = Category;
	saveinfo.Name = Name;
	saveinfo.Description = Description;
	saveinfo.Path = lpMapPath;
	
	EsigList.push_back(saveinfo);
	
	if (pMap) {
		free(pMap);
	}

	CloseHandle(hFile);
	return TRUE;
}

BOOL EnumEsig() {
	EsigList.clear();
	/*if (EsigList.size()) {		//ֻ��ȡһ�ξ͹���
		return true;
	}*/

	char path[256] = {};
	strcpy_s(path, DIRECTORY);strcat_s(path, "\\plugin\\esig\\*.*");
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA(path, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		MessageBoxA(NULL, "ö��esig�ļ�ʧ��", "����", MB_ICONINFORMATION);
		return false;
	}

	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			string strname = FindFileData.cFileName;
			if (strname != "." && strname != "..") {
				char path2[256] = {};
				strcpy_s(path2, DIRECTORY);strcat_s(path2, "\\plugin\\esig\\");strcat_s(path2, FindFileData.cFileName);strcat_s(path2, "\\*.esig");
				WIN32_FIND_DATAA FindFileData2;
				HANDLE hFind2 = FindFirstFileA(path2, &FindFileData2);
				if (hFind2) {
					do {
						char lpMapPath[256] = {};
						strcpy_s(lpMapPath, DIRECTORY);strcat_s(lpMapPath, "\\plugin\\esig\\");strcat_s(lpMapPath, FindFileData.cFileName);strcat_s(lpMapPath, "\\");
						strcat_s(lpMapPath,FindFileData2.cFileName);
						LoadSig(lpMapPath,FindFileData.cFileName);	
					} while (FindNextFileA(hFind2, &FindFileData2));
					FindClose(hFind2);
				}
			}
		}
	} while (FindNextFileA(hFind, &FindFileData));
	FindClose(hFind);
	
	return true;
}


extc int _export cdecl ODBG_Plugindata(char shortname[32])
{
	strcpy_s(shortname, 13, "E-Debug Plus");
	return PLUGIN_VERSION;
}

extc int _export cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, DWORD *features)
{
	char tmpbuffer[MAX_PATH] = {};
	
	
	GetModuleFileNameA(0, tmpbuffer, MAX_PATH);
	string temppath = tmpbuffer;
	temppath = temppath.substr(0, temppath.rfind("\\"));
	StrCpyA((char*)DIRECTORY, temppath.c_str());
	
	if (ollydbgversion < PLUGIN_VERSION)
	{
		Addtolist(0, 0, "��ʾ: ����汾��OD��ƥ��!");
		return -1;
	}
	Addtolist(0, 0, "%s", "E-Debug Plus 1.22");
	Addtolist(0, -1, "%s","  by:fjqisba");

	//�������޸�һ��OD ����ѡ��BUG
	int* Fix = (int*)34152;
	if (*(DWORD*)4647851 == 99688) {
		WriteProcessMemory(GetCurrentProcess(), (LPVOID)4647851, &Fix, 4, NULL);
	}
	return 0;
}

extc int _export cdecl ODBG_Pluginmenu(int origin, CHAR data[4096], VOID *item)
{
	if (origin == PM_MAIN)
	{
		strcpy(data, "0&��ʼ����|1&�������");
		return 1;
	}
	if (origin == PM_DISASM || origin == PM_CPUDUMP) {
		strcpy(data, "0 ������{0 ȡʮ������|1 ���ֽڼ�}");
		return 1;
	}
	return 1;
}

extc void _export cdecl ODBG_Pluginaction(int origin, int action, VOID *item)
{
	if (origin == PM_MAIN) {
		if (action == 1) {
			CString szInfo;
			szInfo += "Plugin:E-Debug Plus\r\n";
			szInfo += "Verion:1.2\r\n";
			szInfo += "Author:fjqisba\r\n";
			szInfo += " Thanks to Xjun";
			MessageBox(NULL, szInfo, L"About", MB_ICONINFORMATION);
			return;
		}

		if (Getcputhreadid() == 0) {
			AfxMessageBox(L"δ�������������������ת�������������!");
			Flash("δ�������!");
			return;
		}

		EnumEsig();
		
		CMainWindow* pWindow = new CMainWindow;	//������ʱ�Ĵ���ָ��
		pWindow->Create(IDD_MainWindow, NULL);
		pWindow->ShowWindow(SW_SHOW);
		return;
	}

	//����������������
	HGLOBAL hClip;
	t_dump* DumpData;
	if (origin == PM_DISASM) {
		DumpData = (t_dump*)Plugingetvalue(VAL_CPUDASM);
	}
	else if(origin==PM_CPUDUMP)
	{
		DumpData = (t_dump*)Plugingetvalue(VAL_CPUDDUMP);
	}

	int len = DumpData->sel1 - DumpData->sel0;
	byte *buffer = new byte[len];
	memset(buffer, 0, len);
	Readmemory(buffer, DumpData->sel0, len, MM_RESILENT);
	if (!OpenClipboard(NULL)) {
		return;
	}

	EmptyClipboard();

	if (action == 0) {    //ȡʮ������
		hClip = GlobalAlloc(GMEM_MOVEABLE, len * 2 + 1);  //��������ı��ռ�
		char *buff;
		buff = (char*)GlobalLock(hClip);
		for (int n = 0;n < len;n++) {					//ʮ������ת��
			sprintf(buff + n * 2, "%02X", buffer[n]);
		}
		GlobalUnlock(hClip);
		SetClipboardData(CF_TEXT, hClip);
		CloseClipboard();
		delete[] buffer;
		return;
	}
	if (action == 1) {	  //���ֽڼ�
		hClip = GlobalAlloc(GMEM_MOVEABLE, len * 4 + 1);  //��������ı��ռ�
		char *buff = (char*)GlobalLock(hClip);
		memset(buff, 0, len * 4 + 1);
		string byteset;//�ֽڼ�
		byteset.append("{");
		for (int n = 0;n < len;n++) {					//ʮ������ת��
			sprintf(buff, "%d,", buffer[n]);
			byteset.append(buff);
		}
		byteset[byteset.length() - 1] = '}';
		strcpy(buff,byteset.c_str());
		GlobalUnlock(hClip);
		SetClipboardData(CF_TEXT, hClip);
		CloseClipboard();   //����Ҫʹ��GlobalFree,��Ϊ�ڴ��Ѿ��ɼ��а����й�
		delete[] buffer;
		return;
	}
}


//������������������������

HANDLE GethProcess() {          
	return (HANDLE)*(DWORD*)0x4D5A68;
}

UINT ByteToDec(char* HexCode) {
	static UCHAR BinMap[256] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,		//123456789
		0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,	//ABCDEF
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,	//abcdef
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	return BinMap[HexCode[0]] * 16 + BinMap[HexCode[1]];
}

void HexToBin(string& HexCode, UCHAR* BinCode) {		//ʮ����ʮ
	static UCHAR BinMap[256] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,		//123456789
		0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,	//ABCDEF
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,	//abcdef
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (UINT n = 0;n < HexCode.length() / 2;n++) {
		BinCode[n] = BinMap[HexCode[2 * n]] * 16 + BinMap[HexCode[2 * n + 1]];
	}
}

char* DecToByte(UINT DecCode) {
	static char* ByteMap[256] = {
		"00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F",
		"10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F",
		"20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F",
		"30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F",
		"40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F",
		"50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F",
		"60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F",
		"70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F",
		"80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F",
		"90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F",
		"A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF",
		"B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF",
		"C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF",
		"D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF",
		"E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF",
		"F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF"
	};
	return ByteMap[DecCode];
}

UCHAR HByteToBin(char HByte) {
	static UCHAR BinMap[256] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,		//123456789
		0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,	//ABCDEF
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,	//abcdef
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	return BinMap[HByte];
}

INT findstr(const char* Func, const char* find) {		//����Func��find�ľ�����,���δ�ҵ�����-1
	char *cp = (char*)Func;	//����Funcָ��,�õ�����ָ��cp
	char *s1, *s2;
	UINT ret = 0;
	while (*cp) {			//���Func��ΪNULL��һֱƥ��
		s1 = cp;			//s1Ϊ�Ա���1
		s2 = (char*)find;	//s2Ϊ�Ա���2
		while (*s2 && !(*s1 - *s2))	//����Ա���2������,���ж��������Ƿ����
			s1++, s2++;
		if (!*s2)					//�ڶԱ���2û����֮ǰ�Ѿ�����ѭ��,˵���Աȳɹ�
			return ret;
		cp++;
		ret++;
	}
	return -1;
}