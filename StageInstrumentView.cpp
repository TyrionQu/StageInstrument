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
