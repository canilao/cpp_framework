/*******************************************************************************
 *
 *  \file
 *   i_object_function.h
 *
 *  \brief
 *   Header file for the interface class for all object function containers.
 *
 *  \note
 *   C Anilao       11/26/2008
 *   Created
 *
 ******************************************************************************/

#ifndef I_OBJECT_FUNCTION_H
#define I_OBJECT_FUNCTION_H

// Standard library dependencies.
#include <vector>
#include <algorithm>

/*******************************************************************************
 *
 *  \namespace
 *   Ftor
 *
 *  \brief
 *   Namespace containing the object function library.
 *
 ******************************************************************************/
namespace Ftor
{
// Forward class declarations.
class ObjectFunctionOwner;

/*******************************************************************************
 *
 *  \class
 *   IObjectFunction
 *
 *  \brief
 *   Abstract interface for all object functions.
 *
 ******************************************************************************/
class IObjectFunction
{
// ObjectFunctionOwner needs to operate on protected functions.
friend class ObjectFunctionOwner;

public:

    // Default constructor.
    IObjectFunction() : pOwner(NULL) {}

    // Constructor.
    IObjectFunction(ObjectFunctionOwner * pNewOwner);

    // Copy constructor.
    IObjectFunction(const IObjectFunction & origObj);

    // Destructor.
    virtual ~IObjectFunction() {}

    // Checks to see if a function is valid.
    virtual bool IsValid() const = 0;

protected:

    // Invalidate with the owner.
    void InvalidateInOwner();

    // Invalidates the function this object owns.
    virtual void InvalidateFunction() = 0;

    // Copies another IObject data locally.
    void CopyData(const IObjectFunction * pOrigObjectFunc);

private:

    // Save the function object owner.
    ObjectFunctionOwner * pOwner;
};

/*******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 ******************************************************************************/
class ObjectFunctionOwner
{
// IObject needs to operate on protected functions.
    friend class IObjectFunction;

public:

    // Constructor.
    ObjectFunctionOwner() {}

    // Destructor.
    virtual ~ObjectFunctionOwner();

protected:

    // Vector type for the list of function pointers.
    typedef std::vector<IObjectFunction *> TFuncVector;

protected:

    // Add function object.
    void AddFunctionObject(IObjectFunction * pClassFunction);

    // Remove function object.
    void InvalidateFunctionObject(const IObjectFunction * pClassFunction);

private:

    // Constructor.
    ObjectFunctionOwner(const ObjectFunctionOwner &);

private:

    // Vector of function object pointers.
    std::vector<IObjectFunction *> functionObjVector;
};

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline IObjectFunction::IObjectFunction(ObjectFunctionOwner * pNewOwner) :

    pOwner(pNewOwner)
{
    pOwner->AddFunctionObject(this);
}

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline IObjectFunction::IObjectFunction(const IObjectFunction & origObj) :
    pOwner(origObj.pOwner)
{
    pOwner->AddFunctionObject(this);
}

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline void IObjectFunction::InvalidateInOwner()
{
    // If we are valid, then we do not have to tell the owner we are deleting.
    if(IsValid() && (pOwner != NULL))
    {
        // We are being deleted, need to make sure the function that knows this.
        pOwner->InvalidateFunctionObject(this);
    }
}

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline
void IObjectFunction::CopyData(const IObjectFunction * pOrigObjectFunc)
{
    // First invalidate with our current owner.
    InvalidateInOwner();

    pOwner = pOrigObjectFunc->pOwner;

    // Do not allow bad owners to be referenced.
    if(pOwner != NULL)
    {
        // Let the new owner know of us.
        pOwner->AddFunctionObject(this);
    }
}

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline ObjectFunctionOwner::~ObjectFunctionOwner()
{
    // For all of the function objects, we need to clear out the funcs.
    for(TFuncVector::iterator iter = functionObjVector.begin() ;
        iter != functionObjVector.end() ;
        ++iter)
    {
        (*iter)->InvalidateFunction();
    }
}

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline
void ObjectFunctionOwner::AddFunctionObject(IObjectFunction * pClassFunction)
{
    // Locate pointer if it exists, we do not want to double add elements.
    TFuncVector::iterator iterLoc = find(functionObjVector.begin(),
                                         functionObjVector.end(),
                                         pClassFunction);

    // Add the pointer if it does exist.
    if(iterLoc == functionObjVector.end())
    {
        functionObjVector.push_back(pClassFunction);
    }
}

/*******************************************************************************
 *
 *  \brief
 *
 *  \history
 *
 ******************************************************************************/
inline void ObjectFunctionOwner::InvalidateFunctionObject(
    const IObjectFunction * pClassFunction)
{
    // Locate the pointer if it exists.
    TFuncVector::iterator iterLoc = find(functionObjVector.begin(),
                                         functionObjVector.end(),
                                         pClassFunction);

    // Remove the pointer if it does exist.
    if(iterLoc != functionObjVector.end())
    {
        functionObjVector.erase(iterLoc);
    }
}
}

#endif
