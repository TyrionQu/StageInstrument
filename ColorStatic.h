#pragma once
#include <afxwin.h>

class CColorStatic :
    public CStatic
{
public:
    CColorStatic();
    ~CColorStatic();
private:
    CBrush m_Brush;
    COLORREF m_BackColor, m_TextColor;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};

