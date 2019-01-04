#include "stdafx.h"
#include "DmFreeReg.h"

typedef HRESULT(__stdcall *GETCLASS_PROC)(REFCLSID, REFIID, LPVOID*);

bool RegisterDmInterFace(LPCTSTR lpDllName, REFCLSID rclsid, REFIID riid, LPVOID * ppv)
{
	(*ppv) = NULL;
	HINSTANCE hDll = LoadLibrary(lpDllName);
	if (NULL == hDll)
		return false;

	GETCLASS_PROC procGetClassObject = (GETCLASS_PROC)GetProcAddress(hDll, "DllGetClassObject");
	if (procGetClassObject)
	{
		IClassFactory* pFactory = NULL;
		HRESULT hr = procGetClassObject(rclsid, IID_IClassFactory, (void**)&pFactory);
		if (SUCCEEDED(hr) && (pFactory != NULL))
		{
			hr = pFactory->CreateInstance(NULL, riid, ppv);
			if ((SUCCEEDED(hr) && ((*ppv) != NULL)) == FALSE)
			{
				return NULL;
			}
			pFactory->Release();
			pFactory = NULL;
			return true;
		}
	}

	return false;
}