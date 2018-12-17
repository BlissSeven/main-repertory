
// FirstStepView.cpp : FirstStepView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "FirstStepDoc.h"
#include "FirstStepView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// FirstStepView

IMPLEMENT_DYNCREATE(FirstStepView, CView)

BEGIN_MESSAGE_MAP(FirstStepView, CView)
END_MESSAGE_MAP()

// FirstStepView 构造/析构

FirstStepView::FirstStepView()
{
	// TODO: 在此处添加构造代码

}

FirstStepView::~FirstStepView()
{
}

BOOL FirstStepView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// FirstStepView 绘制

void FirstStepView::OnDraw(CDC* /*pDC*/)
{
	FirstStepDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// FirstStepView 诊断

#ifdef _DEBUG
void FirstStepView::AssertValid() const
{
	CView::AssertValid();
}

void FirstStepView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

FirstStepDoc* FirstStepView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(FirstStepDoc)));
	return (FirstStepDoc*)m_pDocument;
}
#endif //_DEBUG


// FirstStepView 消息处理程序


void FirstStepView::OnInitialUpdate()
{
	

	// TODO: 在此添加专用代码和/或调用基类
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	// Get the grabber from the document class.
	DShowLib::Grabber* pGrabber = GetDocument()->m_pGrabber;

	// Show the device page.
	pGrabber->showDevicePage();

	// Check if there is a valid device.
	if (pGrabber->isDevValid())
	{
		// Set the window that should display the live video.
		pGrabber->setHWND(m_hWnd);
		// Start the live video.
		pGrabber->startLive();
	}
	else
	{
		AfxMessageBox(TEXT("No device was selected."));
	}
	CView::OnInitialUpdate();
}
