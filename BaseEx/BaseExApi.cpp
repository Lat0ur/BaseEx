#include "stdafx.h"
#include "BaseExApi.h"



IdmsoftPtr CBaseExApi::RegDM = NULL;


CBaseExApi::CBaseExApi()
{
}


CBaseExApi::~CBaseExApi()
{
	
}


CString CBaseExApi::GetAppDirectory()
{
	static TCHAR szFileName[MAX_PATH] = { 0 };
	static bool  bGetFirsted = true;

	do 
	{
		if (bGetFirsted == false)
			break;
		
		::GetModuleFileName(NULL, szFileName, MAX_PATH);

		// 'C:\' 至少三个字节.如果小于3个字节就说明路径是错误的
		if (_tcslen(szFileName) < 8)
			break;

		if (szFileName[_tcslen(szFileName) - 1] != _T('e'))
			break;

		if (szFileName[_tcslen(szFileName) - 2] != _T('x'))
			break;

		if (szFileName[_tcslen(szFileName) - 3] != _T('e'))
			break;

		for (unsigned int it = _tcslen(szFileName); it > 0; it--)
		{
			if (szFileName[it] == _T('\\'))
				break;
			
			szFileName[it] = 0;		
		}

		bGetFirsted = false;

	} while (false);


	return szFileName;
}

bool CBaseExApi::IsSingleObject()
{
	static TCHAR szMutexChar[] = _T("6C4F145A-7B8E-4AE6-97F4-428951651700");

	HANDLE hMutex = ::CreateMutex(NULL, FALSE, szMutexChar);

	if (GetLastError() == ERROR_ALREADY_EXISTS){
		return false;
	}

	return true;
}
