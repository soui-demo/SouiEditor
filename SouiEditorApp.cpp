#include "stdafx.h"
#include "SouiEditorApp.h"

BOOL g_bHookCreateWnd = FALSE;

long g_nUIElmIndex = 0;			//用来给设计器中的控件一个索引, 以便查找

long GetUIElmIndex()
{
	return ++g_nUIElmIndex;
}

SouiEditorApp::SouiEditorApp(IRenderFactory *pRendFactory, HINSTANCE hInst, LPCTSTR pszHostClassName /*= _T("SOUIHOST")*/) : SApplication(pRendFactory, hInst, pszHostClassName)
{
	InitEnv();
}

SWindow * SouiEditorApp::CreateWindowByName(LPCWSTR pszWndClass) const
{
	if (!g_bHookCreateWnd)
		return (SWindow*)CreateObject(SObjectInfo(pszWndClass, Window));
	else
	{
		SStringT wndClassname = pszWndClass;
		if (wndClassname.CompareNoCase(_T("realwnd")) == 0)
			wndClassname = _T("ui_window");

		SWindow *pChild = (SWindow*)CreateObject(SObjectInfo(wndClassname, Window));
		if (!pChild)
		{
			if (wndClassname.CompareNoCase(L"template") != 0)
				pChild = (SWindow*)CreateObject(SObjectInfo(_T("ui_window"), Window));
		}

		if (pChild)
		{
			m_wnd2Index[pChild] = GetUIElmIndex();
		}
		return pChild;
	}
}

long SouiEditorApp::GetWindowIndex(void * pWnd) const
{
	const SMap<void*,long>::CPair *p = m_wnd2Index.Lookup(pWnd);
	if(!p) return -1;
	return p->m_value;
}

void SouiEditorApp::InitEnv()
{
	g_nUIElmIndex = 0;
	m_wnd2Index.RemoveAll();
}
