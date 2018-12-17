
// FirstStepView.cpp : FirstStepView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// FirstStepView ����/����

FirstStepView::FirstStepView()
{
	// TODO: �ڴ˴���ӹ������

}

FirstStepView::~FirstStepView()
{
}

BOOL FirstStepView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// FirstStepView ����

void FirstStepView::OnDraw(CDC* /*pDC*/)
{
	FirstStepDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// FirstStepView ���

#ifdef _DEBUG
void FirstStepView::AssertValid() const
{
	CView::AssertValid();
}

void FirstStepView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

FirstStepDoc* FirstStepView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(FirstStepDoc)));
	return (FirstStepDoc*)m_pDocument;
}
#endif //_DEBUG


// FirstStepView ��Ϣ�������


void FirstStepView::OnInitialUpdate()
{
	

	// TODO: �ڴ����ר�ô����/����û���
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
