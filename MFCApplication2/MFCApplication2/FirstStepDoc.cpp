
// FirstStepDoc.cpp : FirstStepDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "FirstStepDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// FirstStepDoc

IMPLEMENT_DYNCREATE(FirstStepDoc, CDocument)

BEGIN_MESSAGE_MAP(FirstStepDoc, CDocument)
END_MESSAGE_MAP()


// FirstStepDoc ����/����

FirstStepDoc::FirstStepDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_pGrabber = new DShowLib::Grabber();  //5477
	ASSERT(m_pGrabber);

}

FirstStepDoc::~FirstStepDoc()
{
	delete m_pGrabber;//5477
}

BOOL FirstStepDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// FirstStepDoc ���л�

void FirstStepDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void FirstStepDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void FirstStepDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void FirstStepDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// FirstStepDoc ���

#ifdef _DEBUG
void FirstStepDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void FirstStepDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// FirstStepDoc ����


void FirstStepDoc::OnCloseDocument()
{
	// TODO: �ڴ����ר�ô����/����û���

	// Stop live mode.
	m_pGrabber->stopLive();

	// this call will also succeed if no device is open
	m_pGrabber->closeDev();



	CDocument::OnCloseDocument();

}
