#ifndef __CUSTOMCLIENTSITEH__
#define __CUSTOMCLIENTSITEH__

#include <mshtmhst.h>

class CCustomControlSite:public COleControlSite
{
public:
	CCustomControlSite(COleControlContainer *pCnt):COleControlSite(pCnt){}

protected:

DECLARE_INTERFACE_MAP();

BEGIN_INTERFACE_PART(DocHostUIHandler, IDocHostUIHandler)

	STDMETHODIMP ShowContextMenu(
		/* [in ] */		DWORD dwID,
		/* [in ] */		POINT __RPC_FAR *ppt,
		/* [in ] */		IUnknown __RPC_FAR *pcmdtReserved,
		/* [in ] */		IDispatch __RPC_FAR *pdispReserved
		);

	STDMETHODIMP GetHostInfo( 
		/* [out][in] */	DOCHOSTUIINFO __RPC_FAR *pInfo
		);

	STDMETHODIMP ShowUI( 
		/* [in ] */		DWORD dwID,
		/* [in ] */		IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
		/* [in ] */		IOleCommandTarget __RPC_FAR *pCommandTarget,
		/* [in ] */		IOleInPlaceFrame __RPC_FAR *pFrame,
		/* [in ] */		IOleInPlaceUIWindow __RPC_FAR *pDoc
		);

	STDMETHODIMP HideUI(
						void
		);

	STDMETHODIMP UpdateUI(
						void
		);

	STDMETHODIMP EnableModeless(
		/* [in ] */		BOOL fEnable
		);

	STDMETHODIMP OnDocWindowActivate(
		/* [in ] */		BOOL fEnable
		);

	STDMETHODIMP OnFrameWindowActivate(
		/* [in ] */		BOOL fEnable
		);

	STDMETHODIMP ResizeBorder(
		/* [in ] */		LPCRECT prcBorder,
		/* [in ] */		IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
		/* [in ] */		BOOL fRameWindow
		);

	STDMETHODIMP TranslateAccelerator( 
		/* [in ] */		LPMSG lpMsg,
		/* [in ] */		const GUID __RPC_FAR *pguidCmdGroup,
		/* [in ] */		DWORD nCmdID
		);

	STDMETHODIMP GetOptionKeyPath( 
		/* [out] */		LPOLESTR __RPC_FAR *pchKey,
		/* [in ] */		DWORD dw
		);

	STDMETHODIMP GetDropTarget(
		/* [in ] */		IDropTarget __RPC_FAR *pDropTarget,
		/* [out] */		IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget
		);

	STDMETHODIMP GetExternal( 
		/* [out] */		IDispatch __RPC_FAR *__RPC_FAR *ppDispatch
		);

	STDMETHODIMP TranslateUrl( 
		/* [in ] */		DWORD dwTranslate,
		/* [in ] */		OLECHAR __RPC_FAR *pchURLIn,
		/* [out] */		OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut
		);

	STDMETHODIMP FilterDataObject( 
		/* [in ] */		IDataObject __RPC_FAR *pDO,
		/* [out] */		IDataObject __RPC_FAR *__RPC_FAR *ppDORet
		);

END_INTERFACE_PART(DocHostUIHandler)


BEGIN_INTERFACE_PART(DocHostShowUI, IDocHostShowUI)

	STDMETHODIMP ShowHelp(
		/* [in ] */		HWND hwnd,
		/* [in ] */		LPOLESTR pszHelpFile,
		/* [in ] */		UINT uCommand,
		/* [in ] */		DWORD dwData,
		/* [in ] */		POINT ptMouse,
		/* [out] */		IDispatch __RPC_FAR *pDispatchObjectHit
		);

	STDMETHODIMP ShowMessage(
		/* [in ] */		HWND hwnd,
		/* [in ] */		LPOLESTR lpstrText,
		/* [in ] */		LPOLESTR lpstrCaption,
		/* [in ] */		DWORD dwType,
		/* [in ] */		LPOLESTR lpstrHelpFile,
		/* [in ] */		DWORD dwHelpContext,
		/* [out] */		LRESULT __RPC_FAR *plResult
		);

END_INTERFACE_PART(DocHostShowUI)

};


class CCustomOccManager :public COccManager
{
public:
	CCustomOccManager()
	{
		// empty constructor
	}

	COleControlSite* CreateSite(COleControlContainer* pCtrlCont)
	{
		CCustomControlSite *pSite = new CCustomControlSite(pCtrlCont);
		return pSite;
	}
};

#endif // #ifdef __CUSTOMCLIENTSITEH__