#ifndef _BASEEXAPI_H_
#define _BASEEXAPI_H_

class CBaseExApi
{
public:
	CBaseExApi();
	~CBaseExApi();





public:
	static IdmsoftPtr RegDM;
	static CString GetAppDirectory();
	static bool    IsSingleObject();
};
#endif


