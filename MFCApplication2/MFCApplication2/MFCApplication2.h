
// MFCApplication2.h : MFCApplication2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// FirstStepApp:
// �йش����ʵ�֣������ MFCApplication2.cpp
//

class FirstStepApp : public CWinApp
{
public:
	FirstStepApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern FirstStepApp theApp;
