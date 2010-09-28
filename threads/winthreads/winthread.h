/******************************************************************************/
//
/*! \brief  

    \note   C Anilao    07/22/2010  Added header.

*******************************************************************************/

#pragma once

#include <windows.h>
#include "synchronization.h" 

/******************************************************************************/
//
/*! \namespace  Ftor

    \brief      Included with the functor namespace.

*******************************************************************************/
namespace WinThread
{
/******************************************************************************/
//
/*! \class  Thread  

    \brief  

*******************************************************************************/
class Thread
{
public:

   Thread (DWORD (WINAPI * pFun)(void * arg))
   {
      _handle = CreateThread (
         0,    // Security attributes
         0,    // Stack size
         pFun,
         reinterpret_cast<void *>(this),
         CREATE_SUSPENDED,
         &_tid);

      executionCompleteEvent = CreateEvent(NULL, 
                                           FALSE, 
                                           FALSE, 
                                           "ExecutionCompleteEvent");
   }

   Thread (DWORD (WINAPI * pFun)(void * arg), void * pArg)
   {
      _handle = CreateThread (
         0,    // Security attributes
         0,    // Stack size
         pFun,
         pArg,
         CREATE_SUSPENDED,
         &_tid);

      executionCompleteEvent = CreateEvent(NULL, 
                                           FALSE, 
                                           FALSE, 
                                           "ExecutionCompleteEvent");
   }

   ~Thread ()
   {
      // Delete the thread handle.
      CloseHandle (_handle);
	  
	  // Delete the event.
      CloseHandle (executionCompleteEvent);
   }

   void Resume ()
   {
      ResumeThread (_handle);
   }

   void SetExecutionCompleteEvent ()
   {
      SetEvent (executionCompleteEvent);
   }

   void WaitForThreadToDie ()
   {
      if(IsThreadActive())
      {
         WaitForSingleObject (executionCompleteEvent, INFINITE);     

         // Wait for the thread to die.
         do 
         { 
            Sleep(100); 
         } while(IsThreadActive());
      }
   }

   void TerminateThread (DWORD exitCode)
   {
      ::TerminateThread(_handle, exitCode);
   }
   
   bool IsThreadActive ()
   {
      DWORD exitCode;
      BOOL retVal = GetExitCodeThread(_handle, &exitCode);

      return exitCode == STILL_ACTIVE;
   }

private:
   
   HANDLE _handle;   
   
   // thread id.
   DWORD _tid;

   HANDLE executionCompleteEvent;

   Mutex thread_locker;
};
}
