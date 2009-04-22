/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef NULLARY_OBJECT_FUNCTION_H
#define NULLARY_OBJECT_FUNCTION_H

// General dependencies.
#include "i_function.h"
#include "object_function.h"
#include "i_function_delegate.h"
#include "object_function_exception.h"

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
template<class RETURN_TYPE>
class INullaryFunction : public IFunction
{
public:

    // Default constructor.
    INullaryFunction() {}

    // Copy constructor.
    INullaryFunction(const INullaryFunction & orig) {}

    // Destructor.
    virtual ~INullaryFunction() {}

    // Executes the function.
    virtual RETURN_TYPE operator()() const = 0;
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
template<class OBJECT_TYPE,
         class FUNCTION_TYPE,
         class RETURN_TYPE>

class NullaryObjectFunction :

    public INullaryFunction<RETURN_TYPE>,
    public ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>
{
public:

    // Default constructor.
    NullaryObjectFunction() {}

    // Constructor.
    NullaryObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE pNewFunc) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(pNewObj, pNewFunc) {}

    // Copy constructor.
    NullaryObjectFunction(const NullaryObjectFunction & orig) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(orig.GetObjFunc().pObj,
                                                   orig.GetObjFunc().pFunc) {}

    // Destructor.
    virtual ~NullaryObjectFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new NullaryObjectFunction<OBJECT_TYPE,
                                                     FUNCTION_TYPE,
                                                     RETURN_TYPE>(*this);
        return pPtr;
    }

    // Checks to see if the pointers are clear.
    virtual bool IsValid() const
    {
        return ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>::IsValid();
    }

    // Equality operator.
    virtual bool operator==(const IFunction & rhs)
    {
        bool retVal = true;

        // We need to check to see if it is one of ours.
        const NullaryObjectFunction * pSafe =
            dynamic_cast<const NullaryObjectFunction *>(&rhs);

        // Only execute if they cast succeeded.
        if(retVal &= (pSafe != NULL))
        {
            // Get the underlying pointers and check if they match with rhs.
            retVal &= (this->GetObjFunc().pObj == pSafe->GetObjFunc().pObj);
            retVal &= (this->GetObjFunc().pFunc == pSafe->GetObjFunc().pFunc);
        }

        return retVal;
    }

    // Executes the function.
    RETURN_TYPE operator()() const
    {
        // This is a situation where we cannot execute the function.
        if(!this->GetObjFunc().IsValid()) throw ObjectFunctionException();

        // Execute the function.
        return (this->GetObjFunc().pObj->*(this->GetObjFunc().pFunc))();
    }
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
template<class OBJECT_TYPE, class RETURN_TYPE>
class ConstNullaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)() const;

    // Nullary object function templated type.
    typedef NullaryObjectFunction<OBJECT_TYPE,
                                  TFuncPtr,
                                  RETURN_TYPE> TFuncObj;

public:

    // Constructor.
    ConstNullaryObjectFactory() {}

    // Destructor.
    virtual ~ConstNullaryObjectFactory() {}

    // Builds a function object.
    TFuncObj Create(OBJECT_TYPE * pNewObj, TFuncPtr pNewFunc) const
    {
        return TFuncObj(pNewObj, pNewFunc);
    }
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
template<class OBJECT_TYPE, class RETURN_TYPE>
class NullaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)();

    // Nullary object function templated type.
    typedef NullaryObjectFunction<OBJECT_TYPE,
                                  TFuncPtr,
                                  RETURN_TYPE> TFuncObj;

public:

    // Constructor.
    NullaryObjectFactory() {}

    // Destructor.
    virtual ~NullaryObjectFactory() {}

    // Builds a function object.
    TFuncObj Create(OBJECT_TYPE * pNewObj, TFuncPtr pNewFunc) const
    {
        return TFuncObj(pNewObj, pNewFunc);
    }
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
template<class RETURN_TYPE>
class NullaryStaticFunction : public INullaryFunction<RETURN_TYPE>
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (*TFuncPtr)();

public:

    // Constructor.
    NullaryStaticFunction(TFuncPtr pFunc)
    {
        pFunction = pFunc;
    }

    // Copy constructor.
    NullaryStaticFunction(const NullaryStaticFunction & orig)
    {
        pFunction = orig.pFunction;
    }

    // Destructor.
    virtual ~NullaryStaticFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new NullaryStaticFunction<RETURN_TYPE>(*this);
        return pPtr;
    }

    // Checks to see if the pointers are clear.
    virtual bool IsValid() const
    {
        return true;
    }

    // Equality operator.
    virtual bool operator==(const IFunction & rhs)
    {
        bool retVal = true;

        // We need to check to see if it is one of ours.
        const NullaryStaticFunction * pSafe =
            dynamic_cast<const NullaryStaticFunction *>(&rhs);

        // Only execute if they cast succeeded.
        if(retVal &= (pSafe != NULL))
        {
            // Get the underlying pointers and check if they match with rhs.
            retVal &= (pFunction == pSafe->pFunction);
        }

        return retVal;
    }

    // Executes the function.
    virtual RETURN_TYPE operator()() const
    {
        return (*pFunction)();
    }

private:

    // Default constructor.
    NullaryStaticFunction() {}

private:

    // The function pointer.
    TFuncPtr pFunction;
};

// Must forward declare the class type so that the actual template can deduce.
template <class Signature> class Delegate;

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
template<class RETURN_TYPE>
class Delegate<RETURN_TYPE ()> :
    public IFunctionDelegate< INullaryFunction<RETURN_TYPE> >
{
public:

    // Constructor.
    Delegate() {}

    // Copy constructor.
    Delegate(
        const typename IFunctionDelegate< INullaryFunction<RETURN_TYPE> >::
        TFuncType
        & newFunc)
    {
        Add(&newFunc);
    }

    // Static function constructor.
    Delegate(RETURN_TYPE (*pFunc)())
    {
        typedef NullaryStaticFunction<RETURN_TYPE> TFunc;
        TFunc obj = TFunc(pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj, RETURN_TYPE (OBJECT_TYPE::*pFunc)())
    {
        typedef NullaryObjectFactory<OBJECT_TYPE, RETURN_TYPE> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Constant object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj, RETURN_TYPE (OBJECT_TYPE::*pFunc)() const)
    {
        typedef ConstNullaryObjectFactory<OBJECT_TYPE, RETURN_TYPE> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Destructor.
    virtual ~Delegate() {}

    // Operator override.
    RETURN_TYPE operator()()
    {
        // Clean out invalids on Ftor calls.
        this->CleanOutInvalids();

        // Call this constant operator overload.
        const Delegate<RETURN_TYPE ()> & obj = *this;

        return obj();
    }

    // Operator override.
    RETURN_TYPE operator()() const
    {
        // Throw an error if we are empty.
        if(this->size() == 0) throw ObjectFunctionException();

        // Instantiate the iterator.
        typename IFunctionDelegate< INullaryFunction<RETURN_TYPE> >::
        TFuncVector::const_iterator iter;

        // Call all of our contained functions.
        for(iter = this->begin() ; iter != this->end() ; ++iter)
        {
            // Calculate the next iterator.
            typename IFunctionDelegate< INullaryFunction<RETURN_TYPE> >::
            TFuncVector::const_iterator nextIter = iter;
            ++nextIter;

            if(nextIter == this->end())
            {
                break;
            }
            else
            {
                if((*iter)->IsValid())
                {
                    (*(*iter))();
                }
            }
        }

        // Special situation where the very last function is invalid.
        if(!(*iter)->IsValid())
        {
            // If this one is invalid we have to throw because we have
            // nothing to return.
            throw ObjectFunctionException();
        }

        // Calls the last function and returns its value.
        return (*(*iter))();
    }
};
}

#endif
