#include "jsPrecompile.h"
//
#include "jsWindow.h"
//

std::wstring TWindow::stWsResult = _T("UNKNOWN");
//
//method-wrapper return std::wstring value of window bar title
std::wstring TWindow::stGetWStringBarTitle(HWND __wndHandler)
{
 int result=0x0;
 //remember window text length
 result = GetWindowTextLengthW(__wndHandler);
 //
 //if gotten value is bigger than zero
 if(0x0 < result)
 {
  //create an std::wstring that will be an output
  //result
  std::wstring wsStrResult( _T("UNKNOWNout") );
  const int strLenght = result;
  //create a temporary array for our result
  LPWSTR wsString = new WCHAR[strLenght+1];
  //
  //get string of LPWSTR type that has a bar title value
  result = GetWindowTextW(__wndHandler, wsString, strLenght+1);
  //using overloaded operator '=' of std::wstring class
  //storage our result in std::wstring type variable
  wsStrResult = wsString;
  //
  //free memory from under our temporary 
  //variable(wsString)
  delete [] wsString;
  //set wsString pointer in default value
  wsString = NULL;
  //
  return(wsStrResult);
 }
 ////
 return(_T("UNKNOWNout"));
}
//

//********************************************************************
//Window wrapper constructor
TWindow::TWindow(std::wstring __className, std::wstring __barTitle):
FWndHandler(NULL),
//saving class name of window
FClassName(__className),
//saving bar title of window
FBarTitle(__barTitle),
bInitState(false),
FTChClassName(NULL),
FTChBarTitle(NULL)
{
 //use a standard type cast 
 //get wchar_t pointers to class name and bar title
 //of our window
 FTChClassName = (wchar_t* )(FClassName.c_str());
 FTChBarTitle = (wchar_t* )(FBarTitle.c_str());
}
//
//doInit has standard initialized operations for Win API window instance
bool TWindow::doInit(HINSTANCE __InstanceHandler, WNDCLASSEX& __WcEx, WNDPROC __wndLoop)
{
 __WcEx.cbSize = sizeof(WNDCLASSEX);
 __WcEx.style          = CS_HREDRAW | CS_VREDRAW;
 __WcEx.lpfnWndProc    = __wndLoop;
 __WcEx.cbClsExtra     = 0;
 __WcEx.cbWndExtra     = 0;
 __WcEx.hInstance      = __InstanceHandler;
 __WcEx.hIcon          = LoadIcon(__InstanceHandler, MAKEINTRESOURCE(IDI_APPLICATION));
 __WcEx.hCursor        = LoadCursor(NULL, IDC_ARROW);
 __WcEx.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
 __WcEx.lpszMenuName   = NULL;
 __WcEx.lpszClassName  = FTChClassName;
 __WcEx.hIconSm        = LoadIcon(__WcEx.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
 //if failed registration set our state in false
 if (!RegisterClassEx(&__WcEx))
 {
  return(bInitState = false);
 }

 hInst = __InstanceHandler; // Store instance handle in our global variable

 // The parameters to CreateWindow explained:
 // FTChClassName: the name of the application
 // FTChBarTitle: the text that appears in the title bar
 // WS_OVERLAPPEDWINDOW: the type of window to create
 // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
 // 500, 100: initial size (width, length)
 // NULL: the parent of this window
 // NULL: this application does not have a menu bar
 // hInstance: the first parameter from WinMain
 // NULL: not used in this application
 FWndHandler = CreateWindow(
  FTChClassName,
  FTChBarTitle,
  WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT, CW_USEDEFAULT,
  500, 100,
  NULL,
  NULL,
  __InstanceHandler,
  NULL
  );

 if (!FWndHandler)
 {
  return(bInitState = false);
 }
 ////
 return(bInitState = true);
}
//
// __CmdShow: the fourth parameter from WinMain
// __WndMsg - Main message loop:
int TWindow::doExecute(int __CmdShow, MSG& __WndMsg)
{
 if(!initState())
  return(-1);
    // The parameters to ShowWindow explained:
   // getHandler(): the value returned from CreateWindow
   ShowWindow(getHandler(),
       __CmdShow);
   UpdateWindow(getHandler());
   //window message loop
   while (GetMessage(&__WndMsg, NULL, 0, 0))
   {
       TranslateMessage(&__WndMsg);
       DispatchMessage(&__WndMsg);
   }
   //
   return((int) __WndMsg.wParam);
}
//

TWindow::~TWindow(void )
{
 FWndHandler = NULL;
}

//*******************************
//static method, window message processing
LRESULT CALLBACK TWindow::wndLoop(HWND __wndHanlder, UINT __wndMsg, 
                                  WPARAM __wParam, LPARAM __lParam)
{
 PAINTSTRUCT ps;
 HDC hdc;
 TCHAR greeting[] = _T("Hello, World!");
 //

 switch (__wndMsg)
 {
 case WM_CREATE:
  //as soon as window was created we calculate our std::wstring value
  //of bar title
  TWindow::setResult(TWindow::stGetWStringBarTitle(__wndHanlder));    
 break;

 case WM_PAINT:
  hdc = BeginPaint(__wndHanlder, &ps);

  // Here your application is laid out.
  // For this introduction, we just print out "Hello, World!"
  // in the top left corner.
  TextOut(hdc,
   5, 5,
   greeting, _tcslen(greeting));
  // End application specific layout section.

  EndPaint(__wndHanlder, &ps);
  break;

 case WM_DESTROY:
  PostQuitMessage(0);
  break;

 default:
  return DefWindowProc(__wndHanlder, __wndMsg, __wParam, __lParam);
  break;
 }

 return 0;
}