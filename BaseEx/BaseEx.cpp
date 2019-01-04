
// BaseEx.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "BaseEx.h"
#include "BaseExDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBaseExApp

BEGIN_MESSAGE_MAP(CBaseExApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBaseExApp 构造

CBaseExApp::CBaseExApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CBaseExApp 对象

CBaseExApp theApp;


// CBaseExApp 初始化

BOOL CBaseExApp::InitInstance()
{
	CWinApp::InitInstance();


	// -------------------------------------------------------------------
	// 初始化网络
	// -------------------------------------------------------------------
	if (!AfxSocketInit())
	{
		CString Log;
		Log.Format(_T("Error: %d - 初始化网络失败,请查看帮助文档!"), GetLastError());
		AfxMessageBox(Log);
		return FALSE;
	}



	// -------------------------------------------------------------------
	// 初始化环境
	// -------------------------------------------------------------------
	if (!SUCCEEDED(::CoInitializeEx(NULL, 0)))
	{
		CString Log;
		Log.Format(_T("Error: %d - 初始化设备环境失败,请看帮助文档!"), GetLastError());
		AfxMessageBox(Log);
		return FALSE;
	}



	// -------------------------------------------------------------------
	// 注册表
	// -------------------------------------------------------------------
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));



	// -------------------------------------------------------------------
	// 注册大漠插件 | 启动窗口
	// -------------------------------------------------------------------
	do 
	{
		// ------------------------------------------------
		// 禁止多开
		// ------------------------------------------------
#if 禁止多开
		if (!CBaseExApi::IsSingleObject())
		{
			AfxMessageBox(_T("禁止多开"));
			break;
		}
#endif


		// ------------------------------------------------
		//  @ 免注册大漠插件
		// ------------------------------------------------
		bool bReg = RegisterDmInterFace(CBaseExApi::GetAppDirectory() + _T("dm.dll"), __uuidof(dmsoft), __uuidof(Idmsoft), (LPVOID*)&CBaseExApi::RegDM);
		if (bReg == false)
		{
			CString Log;
			Log.Format(_T("Error: %d - 注册组件失败,请查看帮助文档!"), GetLastError());
			AfxMessageBox(Log);
			break;
		}


		// ------------------------------------------------
		// @ 注册大漠会员
		// ------------------------------------------------
		long iRet = CBaseExApi::RegDM->Reg(注册码, 附加码);
		if (iRet != 1)
		{
			CString Log;
			Log.Format(_T("Error: %d - 大漠插件注册失败,请查看帮助文档!"), iRet);
			AfxMessageBox(Log);
			break;
		}


		// ------------------------------------------------
		// @ 运行主窗口
		// ------------------------------------------------
		try {
			CBaseExDlg dlg;
			m_pMainWnd = &dlg;
			dlg.DoModal();
		}
		catch (...) {
			CString Log;
			Log.Format(_T("Error: %d - 哦哦,进程崩溃!!!!"), GetLastError());
			AfxMessageBox(Log);
		}


	} while (false);
	


	// -------------------------------------------------------------------
	// 卸载环境
	// -------------------------------------------------------------------
	::CoUninitialize();

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

