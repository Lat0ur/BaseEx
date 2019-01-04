#ifndef _DM_REG_INTERFACE_H_
#define _DM_REG_INTERFACE_H_



//
// @ 导入大漠插件生成类库文件
//
#import "res/dm.dll"

using namespace dm;

//
// @ 注册大漠实例对象接口
// @ 参考调用方式 RegisterDmInterFace(L"dm.dll",__uuidof(dmsoft),__uuidof(Idmsoft),(LPVOID*)&m_dm);
//
bool RegisterDmInterFace(LPCTSTR lpDllName, REFCLSID rclsid, REFIID riid, LPVOID * ppv);




#endif // !_DM_REG_INTERFACE_H_

