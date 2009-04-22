/******************************************************************************/
//
/*! \file   binary_funciton.h
  
    \brief  This defines a function for a funciton object that has two 
            parameters
  
    \note   C Anilao    04/19/2009  Added header.
  
*******************************************************************************/

#ifndef BINARY_OBJECT_FUNCTION_H
#define BINARY_OBJECT_FUNCTION_H

// General dependencies.
#include "i_function.h"
#include "object_function.h"
#include "i_function_delegate.h"
#include "object_function_exception.h"

/******************************************************************************/
//
/*! \namespace  Ftor

    \brief      Included with the functor namespace.

*******************************************************************************/
namespace Ftor
{
/******************************************************************************/
//
/*! \class  IBinaryFunction
  
    \brief  Function object interface.  Contains two parameters.
  
*******************************************************************************/
template<class RETURN_TYPE, class PARAM_1, class PARAM_2>
class IBinaryFunction : public IFunction
{
public:

    // Default constructor.
    IBinaryFunction() {}

    // Copy constructor.
    IBinaryFunction(const IBinaryFunction & orig) {}

    // Destructor.
    virtual ~IBinaryFunction() {}

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1, PARAM_2 value_2) const = 0;
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
         class PARAM_2>

class BinaryObjectFunction :

    public IBinaryFunction<RETURN_TYPE, PARAM_1, PARAM_2>,
    public ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>
{
public:

    // Default constructor.
    BinaryObjectFunction() {}

    // Constructor.
    BinaryObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE pNewFunc) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(pNewObj, pNewFunc) {}

    // Copy constructor.
    BinaryObjectFunction(const BinaryObjectFunction & orig) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(orig.GetObjFunc().pObj,
                                                   orig.GetObjFunc().pFunc){}

    // Destructor.
    virtual ~BinaryObjectFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new BinaryObjectFunction<OBJECT_TYPE,
                                                    FUNCTION_TYPE,
                                                    RETURN_TYPE,
                                                    PARAM_1,
                                                    PARAM_2>(*this);
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
        const BinaryObjectFunction * pSafe =
            dynamic_cast<const BinaryObjectFunction *>(&rhs);

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
    RETURN_TYPE operator()(PARAM_1 value_1, PARAM_2 value_2) const
    {
        // This is a situation where we cannot execute the function.
        if(!this->GetObjFunc().IsValid()) throw ObjectFunctionException();

        // Execute the function.
        return (this->GetObjFunc().pObj->*(this->GetObjFunc().pFunc))(value_1,
                                                                      value_2);
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
         class PARAM_2>
class ConstBinaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1, PARAM_2) const;

    // Binary object function templated type.
    typedef BinaryObjectFunction<OBJECT_TYPE,
                                 TFuncPtr,
                                 RETURN_TYPE,
                                 PARAM_1,
                                 PARAM_2> TFuncObj;

public:

    // Constructor.
    ConstBinaryObjectFactory() {}

    // Destructor.
    virtual ~ConstBinaryObjectFactory() {}

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
         class PARAM_2>
class BinaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1, PARAM_2);

    // Binary object function templated type.
    typedef BinaryObjectFunction<OBJECT_TYPE,
                                 TFuncPtr,
                                 RETURN_TYPE,
                                 PARAM_1,
                                 PARAM_2> TFuncObj;

public:

    // Constructor.
    BinaryObjectFactory() {}

    // Destructor.
    virtual ~BinaryObjectFactory() {}

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
template<class RETURN_TYPE, class PARAM_1, class PARAM_2>

class BinaryStaticFunction :

    public IBinaryFunction<RETURN_TYPE,
                           PARAM_1,
                           PARAM_2>
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (*TFuncPtr)(PARAM_1, PARAM_2);

public:

    // Constructor.
    BinaryStaticFunction(TFuncPtr pFunc)
    {
        pFunction = pFunc;
    }

    // Copy constructor.
    BinaryStaticFunction(const BinaryStaticFunction & orig)
    {
        pFunction = orig.pFunction;
    }

    // Destructor.
    virtual ~BinaryStaticFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new BinaryStaticFunction<RETURN_TYPE,
                                                    PARAM_1,
                                                    PARAM_2>(*this);
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
        const BinaryStaticFunction * pSafe =
            dynamic_cast<const BinaryStaticFunction *>(&rhs);

        // Only execute if they cast succeeded.
        if(retVal &= (pSafe != NULL))
        {
            // Get the underlying pointers and check if they match with rhs.
            retVal &= (pFunction == pSafe->pFunction);
        }

        return retVal;
    }

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1, PARAM_2 value_2) const
    {
        return (*pFunction)(value_1, value_2);
    }

private:

    // Default constructor.
    BinaryStaticFunction() {}

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
template<class RETURN_TYPE, class PARAM_1, class PARAM_2>
class Delegate<RETURN_TYPE (PARAM_1, PARAM_2)> :
    public IFunctionDelegate< IBinaryFunction<RETURN_TYPE, PARAM_1, PARAM_2> >
{
public:

    // Constructor.
    Delegate() {}

    // Copy constructor.
    Delegate(const typename IFunctionDelegate< IBinaryFunction<RETURN_TYPE,
                                                               PARAM_1,
                                                               PARAM_2> >::
             TFuncType & newFunc)
    {
        Add(newFunc);
    }

    // Static function constructor.
    Delegate(RETURN_TYPE (*pFunc)(PARAM_1, PARAM_2))
    {
        typedef BinaryStaticFunction<RETURN_TYPE, PARAM_1, PARAM_2> TFunc;

        TFunc obj = TFunc(pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj,
             RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1, PARAM_2))
    {
        typedef BinaryObjectFactory<OBJECT_TYPE, RETURN_TYPE, PARAM_1,
                                    PARAM_2> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Const object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj,
             RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1, PARAM_2) const)
    {
        typedef ConstBinaryObjectFactory<OBJECT_TYPE, 
                                         RETURN_TYPE, 
                                         PARAM_1,
                                         PARAM_2> TFact;
        TFact fact;

        typename TFact::TFuncObj obj = fact.Create(pObj, pFunc);
        Add(obj);
    }

    // Destructor.
    virtual ~Delegate() {}

    // Operator override.
    RETURN_TYPE operator()(PARAM_1 value_1, PARAM_2 value_2)
    {
        // Clean out invalids on Ftor calls.
        this->CleanOutInvalids();

        // Throw an error if we are empty.
        if(this->size() == 0) throw ObjectFunctionException();

        // Instantiate the iterator.
        typename IFunctionDelegate< IBinaryFunction<RETURN_TYPE, PARAM_1,
                                                    PARAM_2> >::TFuncVector::
        const_iterator iter;

        // Call all of our contained functions.
        for(iter = this->begin() ; iter != this->end() ; ++iter)
        {
            // Calculate the next iterator.
            typename IFunctionDelegate< IBinaryFunction<RETURN_TYPE, PARAM_1,
                                                        PARAM_2> >::
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
                    (*(*iter))(value_1, value_2);
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
        return (*(*iter))(value_1, value_2);
    }
};
}

#endif
