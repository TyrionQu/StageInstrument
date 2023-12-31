#pragma once


const double MAX_FORCE = 15.0;
const double MIN_FORCE = 0.1;

const UINT MIN_SAMPLE_LENGTH = 1;
// Finally this value should be modified by hardware
const UINT MAX_SAMPLE_LENGTH = 55000;

// CDigitalEdit

class CDigitalEdit : public CEdit
{
	DECLARE_DYNAMIC(CDigitalEdit)

public:
	CDigitalEdit();
	virtual ~CDigitalEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_nX;
	int m_nY;
	BOOL m_bWarning{ FALSE };
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};


