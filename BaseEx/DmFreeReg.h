#ifndef _DM_REG_INTERFACE_H_
#define _DM_REG_INTERFACE_H_



//
// @ �����Į�����������ļ�
//
#import "res/dm.dll"

using namespace dm;

//
// @ ע���Įʵ������ӿ�
// @ �ο����÷�ʽ RegisterDmInterFace(L"dm.dll",__uuidof(dmsoft),__uuidof(Idmsoft),(LPVOID*)&m_dm);
//
bool RegisterDmInterFace(LPCTSTR lpDllName, REFCLSID rclsid, REFIID riid, LPVOID * ppv);




#endif // !_DM_REG_INTERFACE_H_

