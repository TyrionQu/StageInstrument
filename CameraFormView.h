#pragma once
#include <vector>
#include <memory>
#include "DigitalEdit.h"
#include <opencv2/opencv.hpp>

// CCameraFormView form view

struct CameraButtonParamInfo {
	int m_btnID;
	int m_bmpID;
	CString m_tooltipText;
};

struct CameraButtonInfo {
	CameraButtonInfo(const CameraButtonParamInfo& param)
		: m_param(param),
		m_pBtn(std::make_shared<CBitmapButton>()),
		m_pToolTip(std::make_shared<CToolTipCtrl>()) {
	};
	CameraButtonInfo(CameraButtonInfo& other)
		: m_param(other.m_param),
		m_pBtn(other.m_pBtn),
		m_pToolTip(other.m_pToolTip), 
		m_bmp() {
		m_bmp.Attach(other.m_bmp.Detach());
	};
	CameraButtonParamInfo m_param;
	std::shared_ptr<CBitmapButton> m_pBtn;
	std::shared_ptr<CToolTipCtrl> m_pToolTip;
	CBitmap m_bmp;

};

class CCameraFormView : public CFormView
{
	DECLARE_DYNCREATE(CCameraFormView)

protected:
	CCameraFormView();           // protected constructor used by dynamic creation
	virtual ~CCameraFormView();
	CDigitalEdit m_editIntensity;
	std::vector<CameraButtonInfo> m_buttonInfos;
	cv::VideoCapture m_capture;
	CStatic m_CameraDisplay;

	void DrawLine(cv::Mat& image);
	void MatToCImage(cv::Mat& mat, CImage& cImage);
	void DrawImage();
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnSample1();
};


