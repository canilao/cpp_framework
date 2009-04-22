/******************************************************************************/
// 
/*! \file
 
    \brief
 
    \note
 
*******************************************************************************/

#ifndef QUINARY_OBJECT_FUNCTION_H
#define QUINARY_OBJECT_FUNCTION_H

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
         class PARAM_5>
class IQuinaryFunction : public IFunction
{
public:

    // Default constructor.
    IQuinaryFunction() {}

    // Copy constructor.
    IQuinaryFunction(const IQuinaryFunction & orig) {}

    // Destructor.
    virtual ~IQuinaryFunction() {}

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1,
                                   PARAM_2 value_2,
                                   PARAM_3 value_3,
                                   PARAM_4 value_4,
                                   PARAM_5 value_5) const = 0;
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
         class PARAM_5>

class QuinaryObjectFunction :

    public IQuinaryFunction<RETURN_TYPE,
                            PARAM_1,
                            PARAM_2,
                            PARAM_3,
                            PARAM_4,
                            PARAM_5>,
    public ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>
{
public:

    // Default constructor.
    QuinaryObjectFunction() {}

    // Constructor.
    QuinaryObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE pNewFunc) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(pNewObj, pNewFunc) {}

    // Copy constructor.
    QuinaryObjectFunction(const QuinaryObjectFunction & orig) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(orig.GetObjFunc().pObj,
                                                   orig.GetObjFunc().pFunc){}

    // Destructor.
    virtual ~QuinaryObjectFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new QuinaryObjectFunction<OBJECT_TYPE,
                                                     FUNCTION_TYPE,
                                                     RETURN_TYPE,
                                                     PARAM_1,
                                                     PARAM_2,
                                                     PARAM_3,
                                                     PARAM_4,
                                                     PARAM_5>(*this);

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
        const QuinaryObjectFunction * pSafe =
            dynamic_cast<const QuinaryObjectFunction *>(&rhs);

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
                           PARAM_5 value_5) const
    {
        // This is a situation where we cannot execute the function.
        if(!this->GetObjFunc().IsValid()) throw ObjectFunctionException();

        // Execute the function.
        return (this->GetObjFunc().pObj->*(this->GetObjFunc().pFunc))(value_1,
                                                                      value_2,
                                                                      value_3,
                                                                      value_4,
                                                                      value_5);
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
         class PARAM_5>
class ConstQuinaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1,
                                                 PARAM_2,
                                                 PARAM_3,
                                                 PARAM_4,
                                                 PARAM_5) const;

    // Unary object function templated type.
    typedef QuinaryObjectFunction<OBJECT_TYPE,
                                  TFuncPtr,
                                  RETURN_TYPE,
                                  PARAM_1,
                                  PARAM_2,
                                  PARAM_3,
                                  PARAM_4,
                                  PARAM_5> TFuncObj;

public:

    // Constructor.
    ConstQuinaryObjectFactory() {}

    // Destructor.
    virtual ~ConstQuinaryObjectFactory() {}

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
template<class OBJECT_TYPE,
         class RETURN_TYPE,
         class PARAM_1,
         class PARAM_2,
         class PARAM_3,
         class PARAM_4,
         class PARAM_5>
class QuinaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1,
                                                 PARAM_2,
                                                 PARAM_3,
                                                 PARAM_4,
                                                 PARAM_5);

    // Unary object function templated type.
    typedef QuinaryObjectFunction<OBJECT_TYPE,
                                  TFuncPtr,
                                  RETURN_TYPE,
                                  PARAM_1,
                                  PARAM_2,
                                  PARAM_3,
                                  PARAM_4,
                                  PARAM_5> TFuncObj;

public:

    // Constructor.
    QuinaryObjectFactory() {}

    // Destructor.
    virtual ~QuinaryObjectFactory() {}

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
         class PARAM_5>

class QuinaryStaticFunction :

    public IQuinaryFunction<RETURN_TYPE,
                            PARAM_1,
                            PARAM_2,
                            PARAM_3,
                            PARAM_4,
                            PARAM_5>
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (*TFuncPtr)(PARAM_1, PARAM_2, PARAM_3, PARAM_4, PARAM_5);

public:

    // Constructor.
    QuinaryStaticFunction(TFuncPtr pFunc)
    {
        pFunction = pFunc;
    }

    // Copy constructor.
    QuinaryStaticFunction(const QuinaryStaticFunction & orig)
    {
        pFunction = orig.pFunction;
    }

    // Destructor.
    virtual ~QuinaryStaticFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new QuinaryStaticFunction<RETURN_TYPE,
                                                     PARAM_1,
                                                     PARAM_2,
                                                     PARAM_3,
                                                     PARAM_4,
                                                     PARAM_5>(*this);
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
        const QuinaryStaticFunction * pSafe =
            dynamic_cast<const QuinaryStaticFunction *>(&rhs);

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
                                   PARAM_5 value_5) const
    {
        return (*pFunction)(value_1, value_2, value_3, value_4, value_5);
    }

private:

    // Default constructor.
    QuinaryStaticFunction() {}

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
         class PARAM_5>

class Delegate<RETURN_TYPE (PARAM_1, PARAM_2, PARAM_3, PARAM_4, PARAM_5)> :

    public IFunctionDelegate< IQuinaryFunction<RETURN_TYPE,
                                               PARAM_1,
                                               PARAM_2,
                                               PARAM_3,
                                               PARAM_4,
                                               PARAM_5> >
{
public:

    // Constructor.
    Delegate() {}

    // Copy constructor.
    Delegate(const typename IFunctionDelegate< IQuinaryFunction<RETURN_TYPE,
                                                                PARAM_1,
                                                                PARAM_2,
                                                                PARAM_3,
                                                                PARAM_4,
                                                                PARAM_5> >::
             TFuncType & newFunc)
    {
        Add(newFunc);
    }

    // Static function constructor.
    Delegate(RETURN_TYPE (*pFunc)(PARAM_1, PARAM_2, PARAM_3, PARAM_4, PARAM_5))
    {
        typedef QuinaryStaticFunction<RETURN_TYPE, PARAM_1, PARAM_2, PARAM_3,
                                      PARAM_4, PARAM_5> TFunc;

        TFunc obj = TFunc(pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj,
             RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1, PARAM_2, PARAM_3,
                                               PARAM_4,
                                               PARAM_5))
    {
        typedef QuinaryObjectFactory<OBJECT_TYPE, RETURN_TYPE, PARAM_1, PARAM_2,
                                     PARAM_3, PARAM_4, PARAM_5> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj,
             RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1, 
                                               PARAM_2, 
                                               PARAM_3,
                                               PARAM_4,
                                               PARAM_5) const)
    {
        typedef ConstQuinaryObjectFactory<OBJECT_TYPE, 
                                          RETURN_TYPE, 
                                          PARAM_1, 
                                          PARAM_2,
                                          PARAM_3, 
                                          PARAM_4, 
                                          PARAM_5> TFact;
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
                           PARAM_5 value_5)
    {
        // Clean out invalids on Ftor calls.
        this->CleanOutInvalids();

        // Throw an error if we are empty.
        if(this->size() == 0) throw ObjectFunctionException();

        // Instantiate the iterator.
        typename IFunctionDelegate< IQuinaryFunction<RETURN_TYPE,
                                                     PARAM_1,
                                                     PARAM_2,
                                                     PARAM_3,
                                                     PARAM_4,
                                                     PARAM_5> >::TFuncVector::
        const_iterator iter;

        // Call all of our contained functions.
        for(iter = this->begin() ; iter != this->end() ; ++iter)
        {
            // Calculate the next iterator.
            typename IFunctionDelegate< IQuinaryFunction<RETURN_TYPE,
                                                         PARAM_1,
                                                         PARAM_2,
                                                         PARAM_3,
                                                         PARAM_4,
                                                         PARAM_5> >::
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
                    (*(*iter))(value_1, value_2, value_3, value_4, value_5);
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
        return (*(*iter))(value_1, value_2, value_3, value_4, value_5);
    }
};
}

#endif
