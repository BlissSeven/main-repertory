
// FirstStepView.h : FirstStepView 类的接口
//

#pragma once


class FirstStepView : public CView
{
protected: // 仅从序列化创建
	FirstStepView();
	DECLARE_DYNCREATE(FirstStepView)

// 特性
public:
	FirstStepDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~FirstStepView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // FirstStepView.cpp 中的调试版本
inline FirstStepDoc* FirstStepView::GetDocument() const
   { return reinterpret_cast<FirstStepDoc*>(m_pDocument); }
#endif

