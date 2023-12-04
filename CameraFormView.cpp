// CameraFormView.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "CameraFormView.h"
#include "StageInstrumentDoc.h"

#include <Vfw.h>

// CCameraFormView

IMPLEMENT_DYNCREATE(CCameraFormView, CFormView)

CCameraFormView::CCameraFormView()
	: CFormView(IDD_CAMERA_FORMVIEW)
{
	m_hCamera = 0;
}

CCameraFormView::~CCameraFormView()
{
}

void CCameraFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INTENSITY, m_editIntensity);
}

BEGIN_MESSAGE_MAP(CCameraFormView, CFormView)
END_MESSAGE_MAP()


// CCameraFormView diagnostics

#ifdef _DEBUG
void CCameraFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraFormView message handlers


void CCameraFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_pDocument->SetTitle(L"实时视频");

	// 12345 is just temp ID, latterly we should define one constant to handle related mess
	m_hCamera = capCreateCaptureWindow(TEXT("监控摄像头窗口"), WS_CHILD | WS_VISIBLE, 10, 100, 640, 480, this->m_hWnd, 12345);
	if (capDriverConnect(m_hCamera, 0) == FALSE)
	{
		MessageBox(L"监控摄像头没有正确连接！");
		return;
	}

	capPreviewRate(m_hCamera, 66);
	capPreview(m_hCamera, TRUE);
}


void CCameraFormView::OnFinalRelease()
{
	// TODO: Add your specialized code here and/or call the base class

	CFormView::OnFinalRelease();
}
