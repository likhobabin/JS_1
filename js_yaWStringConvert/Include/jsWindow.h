#ifndef __JSWINDOWS_H__
#define __JSWINDOWS_H__
//
#include <string>
////
//Window Wrapper based on Win API
class TWindow
{
public:
 TWindow(std::wstring __className=_T("WindowName"), std::wstring __barTitle=_T("BarTitle"));
 //
 //General initialized method 
 //one of the specificity is capability to receive pointer to function of message receiver
 //of window:__wndLoop
 bool doInit(HINSTANCE /*__InstanceHandler*/ , WNDCLASSEX& /*__WcEx*/,
             WNDPROC __wndLoop=TWindow::wndLoop);
 //
 //Run message cycle of window
 virtual int doExecute(int /*__CmdShow*/, MSG& /*__WndMsg*/);
 //
 //accessor-method
 //success or failed initialization into doInit method  
 bool initState(void ) const 
 {
  return(bInitState);
 }
 //
 //accessor-method
 //returns window handler
 HWND getHandler(void ) 
 {
  return(FWndHandler);
 }
 //
 //accessor-method
 //the same as a previous method but returns 
 //const handler
 //and it is too const method
 const HWND getHandler(void ) const 
 {
  return(FWndHandler);
 }
 //

 ~TWindow(void );
 //

 static void setResult(const std::wstring& __wsResult)
 {
  stWsResult = __wsResult;
 }
 //
 //method-wrapper return std::wstring value of window bar title
 static std::wstring stGetWStringBarTitle(HWND /*__wndHandler*/);
 //

private:
 HWND FWndHandler; 
 // 
 static std::wstring stWsResult;
 //
 std::wstring FClassName;
 //
 std::wstring FBarTitle;
 //
 // The main window class name.
 TCHAR* FTChClassName;
 //
 // The string that appears in the application's title bar.
 TCHAR* FTChBarTitle;
 //
 HINSTANCE hInst;
 //
 bool bInitState;
 //
 //static message function of window
 static LRESULT CALLBACK wndLoop(HWND /*hWnd*/, UINT /*message*/, 
                                 WPARAM /*wParam*/, LPARAM /*lParam*/);
 //
};

////
#endif // __JSWINDOWS_H__