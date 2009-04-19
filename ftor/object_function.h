/******************************************************************************/
//
/*! \file   object_function.h 
  
    \brief  Header for concrete object functions.  At this level, the class and 
            the function pointer is known.  The user only has to supply the 
            types in the template parameters.  The real purpose at this level 
            in the class heirarchy is to hold the object pointer and the 
            function pointer.  Developers are not to use this function in 
            practice.  

    \note   C Anilao    11/26/2008  Created
  
*******************************************************************************/

#ifndef OBJECT_FUNCTION_H
#define OBJECT_FUNCTION_H

// Standard library dependencies.
#include <vector>
#include <algorithm>

// General dependencies.
#include "i_object_function.h"

/******************************************************************************/
//
/*! \namespace  Ftor
  
    \brief  Namespace containing the object function library.
  
*******************************************************************************/
namespace Ftor
{
/******************************************************************************/
//
/*! \class
  
    \brief
  
*******************************************************************************/
template<class OBJECT_TYPE, class FUNCTION_TYPE_PTR>
class ObjectFunction : public IObjectFunction
{
public:

    // Structure that holds both the object and the function ptr.
    struct ClassFunction
    {
        // Constructor.
        ClassFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE_PTR pNewFunc) :
            pObj(pNewObj), pFunc(pNewFunc) {}

        // Clears the structure.
        void clear()
        {
            pObj = NULL; pFunc = NULL;
        }

        // Checks to see if the structure has valid data.
        virtual bool IsValid() const
        {
            return ((pObj != NULL) && (pFunc != NULL));
        }

        // Object ptr.
        OBJECT_TYPE * pObj;

        // Function ptr.
        FUNCTION_TYPE_PTR pFunc;
    };

public:

    // Default constructor.
    ObjectFunction() : objFuncPtr(NULL, NULL) {}

    // Constructor.
    ObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE_PTR pNewFunc) :
        IObjectFunction(pNewObj),
        objFuncPtr(pNewObj, pNewFunc) {}

    // Default copy constructor.
    ObjectFunction(const ObjectFunction & origObj) :
        IObjectFunction(origObj.pOwner),
        objFuncPtr(origObj.objFuncPtr) {}

    // Destructor.
    virtual ~ObjectFunction()
    {
        InvalidateInOwner();
    }

    // Checks to see if the pointers are clear.
    virtual bool IsValid() const
    {
        return (objFuncPtr.IsValid());
    }

    // Accessor for the object function pointers.
    const ClassFunction & GetObjFunc() const
    {
        return objFuncPtr;
    }

    const ObjectFunction & operator=(const ObjectFunction & rhs)
    {
        // Copy parent data.
        CopyData(dynamic_cast<const IObjectFunction *>(&rhs));

        // Copy the rhs to our class.
        this->objFuncPtr = rhs.objFuncPtr;

        // Return a reference to ourself.
        return *this;
    }

protected:

    // Clears out the function that this object points to.
    virtual void InvalidateFunction()
    {
        objFuncPtr.clear();
    }

private:

    // The object pointer and the function pointer structure.
    ClassFunction objFuncPtr;
};
}

#endif
