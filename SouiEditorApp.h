#pragma once

class SouiEditorApp :public SApplication 
{
public:
	SouiEditorApp::SouiEditorApp(IRenderFactory *pRendFactory, HINSTANCE hInst, LPCTSTR pszHostClassName = _T("SOUIHOST"));

	virtual SWindow * CreateWindowByName(LPCWSTR pszWndClass) const;

	long GetWindowIndex(void * pWnd) const;

	void InitEnv();
private:
	mutable SMap<void*, long> m_wnd2Index;	//SWindow * <=> index
};

extern BOOL g_bHookCreateWnd;