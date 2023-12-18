// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// StageInstrumentView.cpp : implementation of the CStageInstrumentView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "StageInstrument.h"
#endif

#include "StageInstrumentDoc.h"
#include "StageInstrumentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStageInstrumentView

IMPLEMENT_DYNCREATE(CStageInstrumentView, CView)

BEGIN_MESSAGE_MAP(CStageInstrumentView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CStageInstrumentView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CStageInstrumentView construction/destruction

CStageInstrumentView::CStageInstrumentView() noexcept
{
	// TODO: add construction code here

}

CStageInstrumentView::~CStageInstrumentView()
{
}

BOOL CStageInstrumentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CStageInstrumentView drawing

void CStageInstrumentView::OnDraw(CDC* /*pDC*/)
{
	CStageInstrumentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CStageInstrumentView printing


void CStageInstrumentView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CStageInstrumentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStageInstrumentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStageInstrumentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CStageInstrumentView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStageInstrumentView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CStageInstrumentView diagnostics

#ifdef _DEBUG
void CStageInstrumentView::AssertValid() const
{
	CView::AssertValid();
}

void CStageInstrumentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStageInstrumentDoc* CStageInstrumentView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStageInstrumentDoc)));
	return (CStageInstrumentDoc*)m_pDocument;
}
#endif //_DEBUG


// CStageInstrumentView message handlers


void CStageInstrumentView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}


#define BUFSIZE 4096
#define MARGIN_SIZE 40

void CStageInstrumentView::OnPaint()
{
#if 0
	CPaintDC dc(this); // device context for painting

	int i, nUnitX, nUnitY, nLength;
	CRect curRect;
	GetClientRect(&curRect);
	dc.MoveTo(MARGIN_SIZE, 5);
	CPoint drawLT(MARGIN_SIZE, MARGIN_SIZE), drawRB(curRect.Height() - MARGIN_SIZE, curRect.Width() - MARGIN_SIZE);

	dc.LineTo(MARGIN_SIZE, curRect.bottom - MARGIN_SIZE);
	nUnitY = (curRect.bottom - 2 * MARGIN_SIZE) / 10;
	dc.TextOut(MARGIN_SIZE, curRect.bottom - 30, L"0");
	dc.TextOut(MARGIN_SIZE + 2, 5, L"高度(ms)");
	nLength = curRect.bottom - MARGIN_SIZE;
	nUnitX = (curRect.right - 2 * MARGIN_SIZE) / 15;

	for (i = 0; i < 10; i++)
	{
		CString strUnit;
		double nIndex = 0.25 * (i - 4);
		strUnit.Format(L"%0.2f", nIndex);
		nLength -= nUnitY;
		if (nIndex < 10)
		{
			dc.TextOut(4, nLength - 5, strUnit);
		}
		else if (nIndex < 100)
		{
			dc.TextOut(10, nLength - 5, strUnit);
		}
		else if (nIndex < 1000)
		{
			dc.TextOut(4, nLength - 5, strUnit);
		}
		else
		{
			dc.TextOut(10, nLength - 5, strUnit);
		}
		dc.MoveTo(MARGIN_SIZE, nLength);
		dc.LineTo(MARGIN_SIZE + nUnitX * 14, nLength); // 14 is the second value of  the following for loop
	}
	dc.MoveTo(MARGIN_SIZE, curRect.bottom - MARGIN_SIZE);
	dc.LineTo(curRect.right - MARGIN_SIZE, curRect.bottom - MARGIN_SIZE);

	nLength = nUnitX;
	for (i = 1; i < 15; i++)
	{
		CString strUnit;
		strUnit.Format(L"%d", (int)(i*100));
		dc.MoveTo(nLength + MARGIN_SIZE, curRect.bottom - MARGIN_SIZE);
		dc.LineTo(nLength + MARGIN_SIZE, curRect.bottom - nUnitY * 10 - MARGIN_SIZE);  // 10 is the second value of the above for loop
		dc.TextOut(nLength + MARGIN_SIZE - 2 * i, curRect.bottom - 28, strUnit);
		nLength += nUnitX;
	}
	dc.TextOut(nLength - 40, curRect.bottom - 50, L"测量进度");

//	CRect drawRect(drawLT, drawRB);
//	CBrush greyBrush(RGB(192, 192, 192));
//	dc.FillRect(&drawRect, &greyBrush);
#endif
}


int CStageInstrumentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(rect);
	m_wndDrawing.Create(_T("Graph Window"), rect, this, 11000);

	return 0;
}


void CStageInstrumentView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_wndDrawing.MoveWindow(0, 0, cx, cy);
}
