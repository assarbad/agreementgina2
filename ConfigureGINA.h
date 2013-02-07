#if !defined(AFX_CONFIGUREGINA_H__24EC85F2_C566_41E7_A95D_54670BEEA4F3__INCLUDED_)
#define AFX_CONFIGUREGINA_H__24EC85F2_C566_41E7_A95D_54670BEEA4F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigureGINA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigureGINA dialog

class CConfigureGINA : public CDialog
{
// Construction
public:
	CConfigureGINA(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigureGINA)
	enum { IDD = IDD_CONFIGUREDLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigureGINA)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void SetOptionsChanged();
	void ResetOptionsChanged();
	void SetPasswordChanged();
	void ResetPasswordChanged();
	BOOL m_OptionsChanged;
	BOOL m_PasswordChanged;
	BOOL m_Inited;
	CString m_DlgTitle;
	GinaCfg m_TempConfig;
	void DialogToCfg(GinaCfg& cfg);
	void CfgToDialog(GinaCfg& cfg);
	CBrush m_PasswordsMatch;
	CBrush m_PasswordsDontMatch;
	CBrush m_Red;
	CBrush m_Green;
	CBrush m_Blue;
	CBrush m_White;
	CBrush m_Gray;
	CBrush m_LtBlue;
	BOOL m_pwmatch;
	BOOL m_nullport;
	BOOL m_nulltime;
	BOOL m_isAgreeURL;
	BOOL m_isNewsURL;
	BOOL m_isMaintenanceURL;
	CToolTipCtrl m_tooltip;
	void InitTooltips(CToolTipCtrl& tooltip);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigureGINA)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckShowtimer();
	afx_msg void OnCheckMaintenance();
	afx_msg void OnCheckNews();
	afx_msg void OnCheckLockwksta();
	afx_msg void OnCheckChangepass();
	afx_msg void OnCheckTaskman();
	afx_msg void OnCheckTaskman2();
	afx_msg void OnCheckOnlyguest();
	afx_msg void OnCheckAdminskips();
	afx_msg void OnDeltaposSpinPortnum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTimerduration(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditGuestuser();
	afx_msg void OnChangeEditGuestpassword();
	afx_msg void OnChangeEditPortnum();
	afx_msg void OnChangeEditYes();
	afx_msg void OnChangeEditNo();
	afx_msg void OnChangeEditCheckbox();
	afx_msg void OnChangeEditMaintenance();
	afx_msg void OnChangeEditNews();
	afx_msg void OnChangeEditAgreement();
	afx_msg void OnChangeEditTimerduration();
	afx_msg void OnChangeEditGuestpassword2();
	afx_msg void OnButtonSave();
	virtual void OnOK();
	afx_msg void OnButtonAbout();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnUpdateEditGuestpassword2();
	afx_msg void OnUpdateEditGuestpassword();
	afx_msg void OnUpdateEditTimerduration();
	afx_msg void OnUpdateEditPortnum();
	afx_msg void OnUpdateEditGuestuser();
	afx_msg void OnChangeEditGuestdomain();
	afx_msg void OnUpdateEditAgreement();
	afx_msg void OnUpdateEditNews();
	afx_msg void OnUpdateEditMaintenance();
	afx_msg void OnButtonAgreement();
	afx_msg void OnButtonNews();
	afx_msg void OnButtonMaintenance();
	afx_msg void OnButtonRepltaskman();
	afx_msg void OnChangeEditRepltaskman();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGUREGINA_H__24EC85F2_C566_41E7_A95D_54670BEEA4F3__INCLUDED_)
