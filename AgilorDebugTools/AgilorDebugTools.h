
// AgilorDebugTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAgilorDebugToolsApp: 
// �йش����ʵ�֣������ AgilorDebugTools.cpp
//

class CAgilorDebugToolsApp : public CWinApp
{
public:
	CAgilorDebugToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAgilorDebugToolsApp theApp;