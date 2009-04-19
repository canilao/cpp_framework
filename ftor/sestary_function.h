/******************************************************************************/
// 
/*! \file
 
    \brief
 
    \note
 
*******************************************************************************/

#ifndef SESTARY_OBJECT_FUNCTION_H
#define SESTARY_OBJECT_FUNCTION_H

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
template<class RETURN_TYPE,
         class PARAM_1,
         class PARAM_2,
         class PARAM_3,
         class PARAM_4,
         class PARAM_5,
         class PARAM_6>
class ISestaryFunction : public IFunction
{
public:

    // Default constructor.
    ISestaryFunction() {}

    // Copy constructor.
    ISestaryFunction(const ISestaryFunction & orig) {}

    // Destructor.
    virtual ~ISestaryFunction() {}

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1,
                                   PARAM_2 value_2,
                                   PARAM_3 value_3,
                                   PARAM_4 value_4,
                                   PARAM_5 value_5,
                                   PARAM_6 value_6) const = 0;
};

/******************************************************************************/
// 
/*! \class
 
    \brief
 
*******************************************************************************/
template<class OBJECT_TYPE,
         class FUNCTION_TYPE,
         class RETURN_TYPE,
         class PARAM_1,
         class PARAM_2,
         class PARAM_3,
         class PARAM_4,
         class PARAM_5,
         class PARAM_6>

class SestaryObjectFunction :

    public ISestaryFunction<RETURN_TYPE,
                            PARAM_1,
                            PARAM_2,
                            PARAM_3,
                            PARAM_4,
                            PARAM_5,
                            PARAM_6>,
    public ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>
{
public:

    // Default constructor.
    SestaryObjectFunction() {}

    // Constructor.
    SestaryObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE pNewFunc) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(pNewObj, pNewFunc) {}

    // Copy constructor.
    SestaryObjectFunction(const SestaryObjectFunction & orig) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(orig.GetObjFunc().pObj,
                                                   orig.GetObjFunc().pFunc){}

    // Destructor.
    virtual ~SestaryObjectFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new SestaryObjectFunction<OBJECT_TYPE,
                                                     FUNCTION_TYPE,
                                                     RETURN_TYPE,
                                                     PARAM_1,
                                                     PARAM_2,
                                                     PARAM_3,
                                                     PARAM_4,
                                                     PARAM_5,
                                                     PARAM_6>(*this);

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
        const SestaryObjectFunction * pSafe =
            dynamic_cast<const SestaryObjectFunction *>(&rhs);

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
    RETURN_TYPE operator()(PARAM_1 value_1,
                           PARAM_2 value_2,
                           PARAM_3 value_3,
                           PARAM_4 value_4,
                           PARAM_5 value_5,
                           PARAM_6 value_6) const
    {
        // This is a situation where we cannot execute the function.
        if(!this->GetObjFunc().IsValid()) throw ObjectFunctionException();

        // Execute the function.
        return (this->GetObjFunc().pObj->*(this->GetObjFunc().pFunc))(value_1,
                                                                      value_2,
                                                                      value_3,
                                                                      value_4,
                                                                      value_5,
                                                                      value_6);
    }
};

/******************************************************************************/
// 
/*! \class
 
    \brief
 
*******************************************************************************/
template<class OBJECT_TYPE,
         class RETURN_TYPE,
         class PARAM_1,
         class PARAM_2,
         class PARAM_3,
         class PARAM_4,
         class PARAM_5,
         class PARAM_6>
class SestaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1,
                                                 PARAM_2,
                                                 PARAM_3,
                                                 PARAM_4,
                                                 PARAM_5,
                                                 PARAM_6);

    // Unary object function templated type.
    typedef SestaryObjectFunction<OBJECT_TYPE,
                                  TFuncPtr,
                                  RETURN_TYPE,
                                  PARAM_1,
                                  PARAM_2,
                                  PARAM_3,
                                  PARAM_4,
                                  PARAM_5,
                                  PARAM_6> TFuncObj;

public:

    // Constructor.
    SestaryObjectFactory() {}

    // Destructor.
    virtual ~SestaryObjectFactory() {}

    // Builds a function object.
    TFuncObj Create(OBJECT_TYPE * pNewObj, TFuncPtr pNewFunc)
    {
        return TFuncObj(pNewObj, pNewFunc);
    }
};

/******************************************************************************/
// 
/*! \class
 
    \brief
 
*******************************************************************************/
template<class RETURN_TYPE,
         class PARAM_1,
         class PARAM_2,
         class PARAM_3,
         class PARAM_4,
         class PARAM_5,
         class PARAM_6>

class SestaryStaticFunction :

    public ISestaryFunction<RETURN_TYPE,
                            PARAM_1,
                            PARAM_2,
                            PARAM_3,
                            PARAM_4,
                            PARAM_5,
                            PARAM_6>
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (*TFuncPtr)(PARAM_1,
                                    PARAM_2,
                                    PARAM_3,
                                    PARAM_4,
                                    PARAM_5,
                                    PARAM_6);

public:

    // Constructor.
    SestaryStaticFunction(TFuncPtr pFunc)
    {
        pFunction = pFunc;
    }

    // Copy constructor.
    SestaryStaticFunction(const SestaryStaticFunction & orig)
    {
        pFunction = orig.pFunction;
    }

    // Destructor.
    virtual ~SestaryStaticFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new SestaryStaticFunction<RETURN_TYPE,
                                                     PARAM_1,
                                                     PARAM_2,
                                                     PARAM_3,
                                                     PARAM_4,
                                                     PARAM_5,
                                                     PARAM_6>(*this);
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
        const SestaryStaticFunction * pSafe =
            dynamic_cast<const SestaryStaticFunction *>(&rhs);

        // Only execute if they cast succeeded.
        if(retVal &= (pSafe != NULL))
        {
            // Get the underlying pointers and check if they match with rhs.
            retVal &= (pFunction == pSafe->pFunction);
        }

        return retVal;
    }

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1,
                                   PARAM_2 value_2,
                                   PARAM_3 value_3,
                                   PARAM_4 value_4,
                                   PARAM_5 value_5,
                                   PARAM_6 value_6) const
    {
        return (*pFunction)(value_1,
                            value_2,
                            value_3,
                            value_4,
                            value_5,
                            value_6);
    }

private:

    // Default constructor.
    SestaryStaticFunction() {}

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
template<class RETURN_TYPE,
         class PARAM_1,
         class PARAM_2,
         class PARAM_3,
         class PARAM_4,
         class PARAM_5,
         class PARAM_6>

class Delegate<RETURN_TYPE (PARAM_1, PARAM_2, PARAM_3, PARAM_4, PARAM_5,
                            PARAM_6)> :

    public IFunctionDelegate< ISestaryFunction<RETURN_TYPE,
                                               PARAM_1,
                                               PARAM_2,
                                               PARAM_3,
                                               PARAM_4,
                                               PARAM_5,
                                               PARAM_6> >
{
public:

    // Constructor.
    Delegate() {}

    // Copy constructor.
    Delegate(const typename IFunctionDelegate< ISestaryFunction<RETURN_TYPE,
                                                                PARAM_1,
                                                                PARAM_2,
                                                                PARAM_3,
                                                                PARAM_4,
                                                                PARAM_5,
                                                                PARAM_6> >::
             TFuncType & newFunc)
    {
        Add(newFunc);
    }

    // Static function constructor.
    Delegate(RETURN_TYPE (*pFunc)(PARAM_1, PARAM_2, PARAM_3, PARAM_4, PARAM_5,
                                  PARAM_6))
    {
        typedef SestaryStaticFunction<RETURN_TYPE, PARAM_1, PARAM_2, PARAM_3,
                                      PARAM_4, PARAM_5, PARAM_6> TFunc;

        TFunc obj = TFunc(pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj,
             RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1, PARAM_2, PARAM_3,
                                               PARAM_4,
                                               PARAM_5, PARAM_6))
    {
        typedef SestaryObjectFactory<OBJECT_TYPE, RETURN_TYPE, PARAM_1, PARAM_2,
                                     PARAM_3, PARAM_4, PARAM_5, PARAM_6> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Destructor.
    virtual ~Delegate() {}

    // Operator override.
    RETURN_TYPE operator()(PARAM_1 value_1,
                           PARAM_2 value_2,
                           PARAM_3 value_3,
                           PARAM_4 value_4,
                           PARAM_5 value_5,
                           PARAM_6 value_6)
    {
        // Clean out invalids on Ftor calls.
        this->CleanOutInvalids();

        // Throw an error if we are empty.
        if(this->size() == 0) throw ObjectFunctionException();

        // Instantiate the iterator.
        typename IFunctionDelegate< ISestaryFunction<RETURN_TYPE,
                                                     PARAM_1,
                                                     PARAM_2,
                                                     PARAM_3,
                                                     PARAM_4,
                                                     PARAM_5,
                                                     PARAM_6> >::TFuncVector::
        const_iterator iter;

        // Call all of our contained functions.
        for(iter = this->begin() ; iter != this->end() ; ++iter)
        {
            // Calculate the next iterator.
            typename IFunctionDelegate< ISestaryFunction<RETURN_TYPE,
                                                         PARAM_1,
                                                         PARAM_2,
                                                         PARAM_3,
                                                         PARAM_4,
                                                         PARAM_5,
                                                         PARAM_6> >::
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
                    (*(*iter))(value_1,
                               value_2,
                               value_3,
                               value_4,
                               value_5,
                               value_6);
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
        return (*(*iter))(value_1, value_2, value_3, value_4, value_5, value_6);
    }
};
}

#endif
