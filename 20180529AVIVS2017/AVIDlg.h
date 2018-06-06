// AVIDlg.h : header file
//
#include "FrameProcess.h"

#if !defined(AFX_AVIDLG_H__0D263936_89EE_4649_B4F0_9DBD2E1FD0F2__INCLUDED_)
#define AFX_AVIDLG_H__0D263936_89EE_4649_B4F0_9DBD2E1FD0F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg dialog

class CAVIDlg : public CDialog
{
// Construction
public:
	CAVIDlg(CWnd* pParent = NULL);	// standard constructor

	CString strAviFilePath;
	CMenu m_Menu;
	LONG lImgWidth;
	LONG lImgHeight;
	LONG lImgLength;
	bool bImgPro;
	CWinThread* ImgProThreadProc;
	static UINT lpImgProThreadProc(LPVOID lpParam);
	static int startxDest;
	static int startyDest;
	static double scale;
	static int flag;
	static int sleeptime;
	CStatic m_current_frame;
	CStatic m_total_frame;
	CStatic m_now_time;
	CString getNowTime();
	static int isChanged;
	/*
	-1 -	不做处理
	0  -	水印处理
	1  -	灰度化处理
	2  -	垂直镜像
	3  -	水平镜像
	4  -	高斯模糊
	*/
	static int imageOpe;
	static int WMx;
	static int WMy;
	static int sigma;


// Dialog Data
	//{{AFX_DATA(CAVIDlg)
	enum { IDD = IDD_AVI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAVIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenBtn();
	afx_msg void OnProBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditYget();
	afx_msg void OnEnChangeEditCget();
	afx_msg void OnEnChangeEditSigma();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIDLG_H__0D263936_89EE_4649_B4F0_9DBD2E1FD0F2__INCLUDED_)
