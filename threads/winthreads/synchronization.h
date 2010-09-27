/******************************************************************************/
//
/*! \brief  Utility for synchronizing threads in windows applications, 
            using CRITICAL_SECTION.  To use, create a mutex object like you
            would when you create a critical section.  Then, when thread 
            critical operations occur, use the lock object to enter the 
            critical section.  This method lowers the number of lines of code 
            that needs to be written to use CRITICAL_SECTION and to make 
            synchronization simpler.

            See below for an example:

            // Here is some memory that needs to be thread safe. 
            int Variable = 0;

            // Some where in code, create a Mutex object that will exist for
            // as long as it is needed.

            Mutex MyVariableMutex;

            ... Some where else in the code.

            // Some thread critical operations are going to occur so lock our
            // associated mutex.  Using brackets makes it easy to visualize
            // when the lock starts and when it ends.

            {
               Lock lockObj(MyVariableMutex);

               ++Variable;
            }

    \note   C Anilao    07/22/2010  Added header.

*******************************************************************************/

#pragma once

#include <windows.h>
#include <exception>

/******************************************************************************/
//
/*! \namespace  Ftor

    \brief      Included with the functor namespace.

*******************************************************************************/
namespace WinThread
{
/******************************************************************************/
//
/*! \class  Mutex

    \brief  It is equivalent to the CRITICAL_SECTION object.  To use, just 
            instantiate Mutex to aquire a CRITICAL_SECTION. 

*******************************************************************************/
class Mutex
{
   friend class Lock;

public:

   // Constructor.
   Mutex () 
   { 
      InitializeCriticalSection (& _critSection); 
   }

   // Destructor.
   ~Mutex () 
   { 
      if(!IsCriticalSectionValid()) throw std::exception("Destructor Failed.");

      DeleteCriticalSection (& _critSection); 
   }

private:

   // This is called when the critical section is needed to be locked.
   void Acquire ()
   {
      if(!IsCriticalSectionValid()) throw std::exception("Acquire Failed.");
      
      EnterCriticalSection (& _critSection);
   }

   // This is called when the critical section is needed to be released.
   void Release ()
   {
      if(!IsCriticalSectionValid()) throw std::exception("Release Failed.");

      LeaveCriticalSection (& _critSection);
   }

   // Checks to see if the critical section is valid.
   bool IsCriticalSectionValid()
   {
      CRITICAL_SECTION testMem;

      memset(&testMem, 0, sizeof(testMem));
      
      return memcmp(&testMem, & _critSection, sizeof(testMem)) != 0;
   }

   CRITICAL_SECTION _critSection;
};

/******************************************************************************/
//
/*! \class  Lock

    \brief  This object is a mechanism for locking a CRITICAL_SECTION.  To use
            just instantiate the object, with the corresponding Mutex in the 
            as the parameter in the constructor.  This will automatically lock.
            When the lock object is destroyed, then the CRITICAL_SECTION is 
            released.

*******************************************************************************/
class Lock
{
public:

   // Acquire the state of the semaphore
   Lock ( Mutex & mutex )
      : _mutex(mutex)
   {
      _mutex.Acquire();
   }

   // Release the state of the semaphore
   ~Lock ()
   {
      _mutex.Release();
   }

private:

   // Mutex passed in the constructor.
   Mutex & _mutex;
};
}
