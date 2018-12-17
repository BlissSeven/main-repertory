
// FirstStepView.cpp : CFirstStepView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CFirstStepView ����/����

CFirstStepView::CFirstStepView()
{
	// TODO: �ڴ˴���ӹ������

}

CFirstStepView::~CFirstStepView()
{
}

BOOL CFirstStepView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFirstStepView ����

void CFirstStepView::OnDraw(CDC* /*pDC*/)
{
	CFirstStepDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CFirstStepView ���

#ifdef _DEBUG
void CFirstStepView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstStepView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstStepDoc* CFirstStepView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstStepDoc)));
	return (CFirstStepDoc*)m_pDocument;
}
#endif //_DEBUG


// CFirstStepView ��Ϣ�������
