
// FirstStepView.h : CFirstStepView ��Ľӿ�
//

#pragma once


class CFirstStepView : public CView
{
protected: // �������л�����
	CFirstStepView();
	DECLARE_DYNCREATE(CFirstStepView)

// ����
public:
	CFirstStepDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CFirstStepView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FirstStepView.cpp �еĵ��԰汾
inline CFirstStepDoc* CFirstStepView::GetDocument() const
   { return reinterpret_cast<CFirstStepDoc*>(m_pDocument); }
#endif

