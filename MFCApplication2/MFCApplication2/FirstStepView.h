
// FirstStepView.h : FirstStepView ��Ľӿ�
//

#pragma once


class FirstStepView : public CView
{
protected: // �������л�����
	FirstStepView();
	DECLARE_DYNCREATE(FirstStepView)

// ����
public:
	FirstStepDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~FirstStepView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // FirstStepView.cpp �еĵ��԰汾
inline FirstStepDoc* FirstStepView::GetDocument() const
   { return reinterpret_cast<FirstStepDoc*>(m_pDocument); }
#endif

