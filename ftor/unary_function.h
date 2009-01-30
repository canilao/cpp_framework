/*******************************************************************************
 *
 *  \file
 *
 *  \brief
 *
 *  \note
 *
 ******************************************************************************/

#ifndef UNARY_OBJECT_FUNCTION_H
#define UNARY_OBJECT_FUNCTION_H

// General dependencies.
#include "i_function.h"
#include "object_function.h"
#include "i_function_delegate.h"
#include "object_function_exception.h"

/*******************************************************************************
 *
 *  \namespace
 *
 *  \brief
 *
 ******************************************************************************/
namespace Ftor
{
/*******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 ******************************************************************************/
template<class RETURN_TYPE, class PARAM_1>
class IUnaryFunction : public IFunction
{
public:

    // Default constructor.
    IUnaryFunction() {}

    // Copy constructor.
    IUnaryFunction(const IUnaryFunction & orig) {}

    // Destructor.
    virtual ~IUnaryFunction() {}

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1) const = 0;
};

/*******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 ******************************************************************************/
template<class OBJECT_TYPE,
         class FUNCTION_TYPE,
         class RETURN_TYPE,
         class PARAM_1>

class UnaryObjectFunction :

    public IUnaryFunction<RETURN_TYPE, PARAM_1>,
    public ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>
{
public:

    // Default constructor.
    UnaryObjectFunction() {}

    // Constructor.
    UnaryObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE pNewFunc) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(pNewObj, pNewFunc) {}

    // Copy constructor.
    UnaryObjectFunction(const UnaryObjectFunction & orig) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(orig.GetObjFunc().pObj,
                                                   orig.GetObjFunc().pFunc) {}

    // Destructor.
    virtual ~UnaryObjectFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new UnaryObjectFunction<OBJECT_TYPE,
                                                   FUNCTION_TYPE,
                                                   RETURN_TYPE,
                                                   PARAM_1>(*this);
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
        const UnaryObjectFunction * pSafe =
            dynamic_cast<const UnaryObjectFunction *>(&rhs);

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
    RETURN_TYPE operator()(PARAM_1 value_1) const
    {
        // This is a situation where we cannot execute the function.
        if(!this->GetObjFunc().IsValid()) throw ObjectFunctionException();

        // Execute the function.
        return (this->GetObjFunc().pObj->*(this->GetObjFunc().pFunc))(value_1);
    }
};

/*******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 ******************************************************************************/
template<class OBJECT_TYPE, class RETURN_TYPE, class PARAM_1>
class UnaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1);

    // Unary object function templated type.
    typedef UnaryObjectFunction<OBJECT_TYPE,
                                TFuncPtr,
                                RETURN_TYPE,
                                PARAM_1> TFuncObj;

public:

    // Constructor.
    UnaryObjectFactory() {}

    // Destructor.
    virtual ~UnaryObjectFactory() {}

    // Builds a function object.
    TFuncObj Create(OBJECT_TYPE * pNewObj, TFuncPtr pNewFunc) const
    {
        return TFuncObj(pNewObj, pNewFunc);
    }
};

/*******************************************************************************
 *
 *   \class
 *
 *   \brief
 *
 ******************************************************************************/
template<class RETURN_TYPE, class PARAM_1>
class UnaryStaticFunction : public IUnaryFunction<RETURN_TYPE, PARAM_1>
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (*TFuncPtr)(PARAM_1);

public:

    // Constructor.
    UnaryStaticFunction(TFuncPtr pFunc)
    {
        pFunction = pFunc;
    }

    // Copy constructor.
    UnaryStaticFunction(const UnaryStaticFunction & orig)
    {
        pFunction = orig.pFunction;
    }

    // Destructor.
    virtual ~UnaryStaticFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new UnaryStaticFunction<RETURN_TYPE,
                                                   PARAM_1>(*this);
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
        const UnaryStaticFunction * pSafe =
            dynamic_cast<const UnaryStaticFunction *>(&rhs);

        // Only execute if they cast succeeded.
        if(retVal &= (pSafe != NULL))
        {
            // Get the underlying pointers and check if they match with rhs.
            retVal &= (pFunction == pSafe->pFunction);
        }

        return retVal;
    }

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1) const
    {
        return (*pFunction)(value_1);
    }

private:

    // Default constructor.
    UnaryStaticFunction() {}

private:

    // The function pointer.
    TFuncPtr pFunction;
};

// Must forward declare the class type so that the actual template can deduce.
template <class Signature> class Delegate;

/*******************************************************************************
 *
 *   \class
 *
 *   \brief
 *
 ******************************************************************************/
template<class RETURN_TYPE, class PARAM_1>
class Delegate<RETURN_TYPE (PARAM_1)> :
    public IFunctionDelegate< IUnaryFunction<RETURN_TYPE, PARAM_1> >
{
public:

    // Constructor.
    Delegate() {}

    // Copy constructor.
    Delegate(const typename IFunctionDelegate< IUnaryFunction<RETURN_TYPE,
                                                              PARAM_1> >::
             TFuncType & newFunc)
    {
        Add(newFunc);
    }

    // Static function constructor.
    Delegate(RETURN_TYPE (*pFunc)(PARAM_1))
    {
        typedef UnaryStaticFunction<RETURN_TYPE, PARAM_1> TFunc;
        TFunc obj = TFunc(pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj, RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1))
    {
        typedef UnaryObjectFactory<OBJECT_TYPE, RETURN_TYPE, PARAM_1> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Destructor.
    virtual ~Delegate() {}

    // Operator override.
    RETURN_TYPE operator()(PARAM_1 value_1)
    {
        // Clean out invalids on Ftor calls.
        this->CleanOutInvalids();

        // Throw an error if we are empty.
        if(this->size() == 0) throw ObjectFunctionException();

        // Instantiate the iterator.
        typename IFunctionDelegate< IUnaryFunction<RETURN_TYPE,
                                                   PARAM_1> >::TFuncVector::
        const_iterator iter;

        // Call all of our contained functions.
        for(iter = this->begin() ; iter != this->end() ; ++iter)
        {
            // Calculate the next iterator.
            typename IFunctionDelegate< IUnaryFunction<RETURN_TYPE,
                                                       PARAM_1> >::TFuncVector
            ::const_iterator nextIter = iter;
            ++nextIter;

            if(nextIter == this->end())
            {
                break;
            }
            else
            {
                if((*iter)->IsValid())
                {
                    (*(*iter))(value_1);
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
        return (*(*iter))(value_1);
    }
};
}

#endif
