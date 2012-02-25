#include "jsPrecompile.h"
//
#include "jsWindow.h"
///

int WINAPI WinMain(HINSTANCE __InstanceHandler,
                   HINSTANCE /*hPrevInstance*/,
                   LPSTR /*lpCmdLine*/,
                   int __CmdShow)
{
 TWindow wndObj; 
 WNDCLASSEX wndClassEx;
 MSG wndMsgBox;
 //
 if(wndObj.doInit(__InstanceHandler, wndClassEx))
 {
  return( wndObj.doExecute(__CmdShow, wndMsgBox) );
 }
 //
 return(0x0);
}