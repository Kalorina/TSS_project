
// TSS_cviko1Dlg.h : header file
//

#pragma once


// CTSScviko1Dlg dialog
class CTSScviko1Dlg : public CDialogEx
{
// Construction
public:
	CTSScviko1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TSS_CVIKO1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult);

	CRect m_rect;

	CRect m_rectFileList;
	CRect m_rectStaticHistogram;
	CRect m_rectStaticImage;

	CListCtrl m_fileList;
	CStatic m_staticHistogram;
	CStatic m_staticImage;

	afx_msg void OnFileOpen32771();
	afx_msg void OnFileClose32772();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
