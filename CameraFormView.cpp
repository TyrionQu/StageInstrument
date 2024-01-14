// CameraFormView.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "CameraFormView.h"
#include "StageInstrumentDoc.h"

#include <Vfw.h>

// CCameraFormView
using namespace cv;

IMPLEMENT_DYNCREATE(CCameraFormView, CFormView)
#define CAMERA_TIMER_ID	IDD_CAMERA_FORMVIEW

CCameraFormView::CCameraFormView()
	: CFormView(IDD_CAMERA_FORMVIEW)
{
	m_capture.open(0);

	if (!m_capture.isOpened())
	{
		AfxMessageBox(_T("can't open camera"));
		TRACE("can't open camera");
		return;
	}

}

CCameraFormView::~CCameraFormView()
{
}

void CCameraFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INTENSITY, m_editIntensity);
	std::vector<CameraButtonParamInfo> buttonParamInfos = {
	{ IDC_BTN_SAMPLE_1, IDB_TOWER_DOWN, _T("Tower up") },
	{ IDC_BTN_SAMPLE_2, IDB_TOWER_UP, _T("Tower down") },
	{ IDC_BTN_SAMPLE_3, IDB_TOWER_HOME, _T("Tower home") },
	{ IDC_BTN_SAMPLE_4,IDB_LOAD_SAMPLE, _T("Load sample") },
	{ IDC_BTN_SAMPLE_5, IDB_UNLOAD_SAMPLE, _T("Unload sample") },
	{ IDC_BTN_SAMPLE_6, IDB_MAKE_HORIZONTAL, _T("Make horizontal")}
	};
	for (const auto& item : buttonParamInfos) {
		CameraButtonInfo buttonInfo(item);
		m_buttonInfos.emplace_back(buttonInfo);
	}
	for (auto& item : m_buttonInfos) {
		if (item.m_pBtn.get()) {
			DDX_Control(pDX, item.m_param.m_btnID, *item.m_pBtn.get());
		}
	}
	DDX_Control(pDX, IDC_CAMERA_DISPLAY, m_CameraDisplay);
}

BEGIN_MESSAGE_MAP(CCameraFormView, CFormView)
	ON_BN_CLICKED(IDC_BTN_SAMPLE_1, &CCameraFormView::OnBnClickedBtnSample1)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CCameraFormView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == CAMERA_TIMER_ID)
	{
		DrawImage();
	}

	CFormView::OnTimer(nIDEvent);
}

void CCameraFormView::DrawLine(Mat& image)
{

	int centerX = image.cols / 2;
	int centerY = image.rows / 2;

	// draw green lines
	int crossLength = image.cols / 4;
	int crossHeight = image.rows / 4;
	cv::line(image, cv::Point(centerX - crossLength / 2, centerY),
		cv::Point(centerX + crossLength / 2, centerY),
		cv::Scalar(0, 255, 0), 1);
	cv::line(image, cv::Point(centerX, centerY - crossHeight / 2),
		cv::Point(centerX, centerY + crossHeight / 2),
		cv::Scalar(0, 255, 0), 1);

	// draw red lines
	int centerX_new = image.cols * 13 / 16 + image.cols / 2 /20;
	int centerY_new = image.rows / 2 - image.rows / 2 / 20;
	int crossLength_new = (image.cols / 2 - crossLength / 2);
	crossLength_new = (crossLength_new / 10) * 10;
	int crossHeight_new = image.rows / 2;
	crossHeight_new = (crossHeight_new / 10) * 10;
	cv::line(image, cv::Point(centerX_new - crossLength_new / 2, centerY_new),
		cv::Point(centerX_new + crossLength_new / 2, centerY_new),
		cv::Scalar(0, 0, 255), 1);
	cv::line(image, cv::Point(centerX_new, centerY_new - crossHeight_new / 2),
		cv::Point(centerX_new, centerY_new + crossHeight_new / 2),
		cv::Scalar(0, 0, 255), 1);

	int divisionsHorizontal = 10;
	int lineLenghtHorizontal = crossHeight_new / 5;
	int divisionLengthHorizontal = crossLength_new / divisionsHorizontal;
	for (int i = 0; i <= divisionsHorizontal; ++i) {
		int x = centerX_new - crossLength_new / 2 + i * divisionLengthHorizontal;
		cv::line(image, cv::Point(x, centerY_new - lineLenghtHorizontal/2), cv::Point(x, centerY_new + lineLenghtHorizontal/2),
			cv::Scalar(0, 0, 255), 1);
	}

	int divisionsVertical = 10;
	int lineLenghtVertical = crossLength_new / 5;
	int divisionLengthVertical = crossHeight_new / divisionsVertical;
	for (int i = 0; i <= divisionsVertical; ++i) {
		int y = centerY_new - crossHeight_new / 2 + i * divisionLengthVertical;
		cv::line(image, cv::Point(centerX_new - lineLenghtVertical/2, y), cv::Point(centerX_new + lineLenghtVertical/2, y),
			cv::Scalar(0, 0, 255), 1);
	}

}

void CCameraFormView::MatToCImage(cv::Mat& mat, CImage& cImage)
{
	//create new CImage  
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy(); //clear  
	cImage.Create(width, height, 8 * channels);  

	//copy values  
	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); 
	int step = cImage.GetPitch();

	for (int i = 0; i < height; ++i)
	{
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j)
		{
			if (channels == 1) //gray  
			{
				*(pimg + i * step + j) = ps[j];
			}
			else if (channels == 3) //color  
			{
				for (int k = 0; k < 3; ++k)
				{
					*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
}

void CCameraFormView::DrawImage()
{
	Mat frame;
	m_capture.read(frame);

	if (!frame.empty())
	{
		cv::Mat resizedFrame;

		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_CAMERA_DISPLAY);
		CRect rect;
		pWnd->GetClientRect(&rect);

		cv::resize(frame, resizedFrame, cv::Size(rect.Width(), rect.Height()));
		DrawLine(resizedFrame);
		CImage image;

		// Copy the frame data to the CImage object
		MatToCImage(resizedFrame, image);

		// Draw the image on the dialog
		CDC* pDC = pWnd->GetDC();
		image.BitBlt(pDC->m_hDC, 0, 0);
		ReleaseDC(pDC);
	
	}
}

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

static void ShowBitmapForCameraButton(std::shared_ptr<CBitmapButton> button, CBitmap& bmp)
{
	if (!button.get()) {
		return;
	}
	// CRect rectButton;
	// button.GetClientRect(&rectButton);
	//TRACE("Button Size - Width: %d, Height: %d\n", rectButton.Width(), rectButton.Height());
	button->ModifyStyle(0, BS_BITMAP);
	button->SetBitmap(bmp);
	BITMAP bm;
	bmp.GetBitmap(&bm);
	button->SetWindowPos(nullptr, 0, 0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
	// TRACE("Bmp Size - Width: %d, Height: %d\n", bm.bmWidth, bm.bmWidth);
}


// CCameraFormView message handlers

void CCameraFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_pDocument->SetTitle(L"ÊµÊ±ÊÓÆµ");
	for (auto& buttonInfo : m_buttonInfos) {
		buttonInfo.m_bmp.LoadBitmap(buttonInfo.m_param.m_bmpID);
		buttonInfo.m_pBtn->SetBitmap(buttonInfo.m_bmp);
		ShowBitmapForCameraButton(buttonInfo.m_pBtn, buttonInfo.m_bmp);
		buttonInfo.m_pToolTip->Create(this);
		buttonInfo.m_pToolTip->AddTool(GetDlgItem(buttonInfo.m_param.m_btnID),
			buttonInfo.m_param.m_tooltipText);
	}

	m_CameraDisplay.ModifyStyle(0, WS_CHILD | WS_VISIBLE, SWP_NOZORDER);
	// start timer
	SetTimer(CAMERA_TIMER_ID, 33, nullptr);
}

void CCameraFormView::OnFinalRelease()
{
	CFormView::OnFinalRelease();
}


void CCameraFormView::OnBnClickedBtnSample1()
{
	// TODO: Add your control notification handler code here
}

BOOL CCameraFormView::PreTranslateMessage(MSG* pMsg)
{
	for (auto& item : m_buttonInfos) {
		item.m_pToolTip->RelayEvent(pMsg);
	}

	return CFormView::PreTranslateMessage(pMsg);
}
