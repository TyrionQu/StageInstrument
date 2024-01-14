#include "pch.h"
#include "ColorStatic.h"

CColorStatic::CColorStatic()
{
	const COLORREF rgbWhite = 0x00FFFFFF;
	m_Brush.CreateSolidBrush(rgbWhite);
	LOGBRUSH LogBrush;
	m_Brush.GetLogBrush(&LogBrush);
	m_BackColor = LogBrush.lbColor;
//	CPen Pen;
//	Pen.CreateStockObject(WHITE_PEN);
//	LOGPEN LogPen;
//	Pen.GetLogPen(&LogPen);
//	m_TextColor = LogPen.lopnColor;
}

CColorStatic::~CColorStatic()
{
}

BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	//HBRUSH hbr = CStatic::OnCtlColor(pDC, nCtlColor);
	pDC->SetBkColor(m_BackColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return (HBRUSH)m_Brush;
}
