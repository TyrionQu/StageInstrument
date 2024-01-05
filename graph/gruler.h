#ifndef __GRULER_H
#define __GRULER_H

#include "coords.h"

//FRuler object
class FRuler : public CWnd
{
protected:
	DECLARE_DYNCREATE(FRuler)

	// Attributes
public:
	LOGFONT MainFontRec;
	//	int MinShift,MaxShift;
	double MinValue, MaxValue;
	CString sUnit, sTitle;
	CToolTipCtrl tooltip;

	//Annie
	int zeroPosition; // 0: 0,1,2,3...  1:-1,0,1,2...   2:-2,-1,0,1...   3:-3,-2,-1,0...
	double unit_display_length;
	int minUnit_pix_length;//small grid
	int unit_divisor;//number of small grids
	CRect rect_has_drawn;
	//

	// Operations
public:
	int ConvertLogPixToRealPix(CDC* dest_dc, double log_pix_num, BOOL b_x_axis);
	virtual int Width(CDC* dest_dc) { return 0; };
	void SetMinMax(double minv, double maxv, BOOL bRedraw);
	void SetNewTitles(char* newUOM, char* newTitle);
	virtual int GetNMax(CDC* dc_to_draw, CRect rect_to_draw) { return 0; };
	virtual void DrawRuler(CDC* dc_to_draw, CRect rect_to_draw) {};
	virtual void DrawRulerX(CDC* dc_to_draw, CRect rect_to_draw) {};
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(FRuler)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//Annie
	void SetUnitAttributes(int izeroPosition, double iunit_display_length, int iminUnit_pix_length, int iunit_divisor);
	int GetUnitPix() { return minUnit_pix_length * unit_divisor; };
	// 
// Implementation
protected:
	FRuler();
	virtual ~FRuler();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(FRuler)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class FHRuler : public FRuler
{
	DECLARE_DYNAMIC(FHRuler)
public:
	FHRuler();
	virtual int Width(CDC* dest_dc);
	virtual int GetNMax(CDC* dc_to_draw, CRect rect_to_draw);
	virtual void DrawRuler(CDC* dc_to_draw, CRect rect_to_draw);
	virtual void DrawRulerEX(CDC* dc_to_draw, CRect rect_to_draw);
	BOOL NeedRedraw(CDC* dc_to_draw, CRect rect_to_draw);
protected:
	//{{AFX_MSG(FHRuler)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class FVRuler : public FRuler
{
	DECLARE_DYNAMIC(FVRuler)
public:
	FVRuler();
	virtual int Width(CDC* dest_dc);
	virtual int GetNMax(CDC* dc_to_draw, CRect rect_to_draw);
	virtual void DrawRuler(CDC* dc_to_draw, CRect rect_to_draw);
	virtual void DrawRulerEX(CDC* dc_to_draw, CRect rect_to_draw);
protected:
	//{{AFX_MSG(FVRuler)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

