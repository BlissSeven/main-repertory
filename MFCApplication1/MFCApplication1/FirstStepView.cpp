
// FirstStepView.cpp : CFirstStepView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "FirstStepDoc.h"
#include "FirstStepView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFirstStepView

IMPLEMENT_DYNCREATE(CFirstStepView, CView)

BEGIN_MESSAGE_MAP(CFirstStepView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFirstStepView 构造/析构

CFirstStepView::CFirstStepView()
{
	// TODO: 在此处添加构造代码

}

CFirstStepView::~CFirstStepView()
{
}

BOOL CFirstStepView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFirstStepView 绘制

void CFirstStepView::OnDraw(CDC* /*pDC*/)
{
	CFirstStepDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CFirstStepView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFirstStepView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFirstStepView 诊断

#ifdef _DEBUG
void CFirstStepView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstStepView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstStepDoc* CFirstStepView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstStepDoc)));
	return (CFirstStepDoc*)m_pDocument;
}
#endif //_DEBUG


// CFirstStepView 消息处理程序
