/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef QUATERNARY_OBJECT_FUNCTION_H
#define QUATERNARY_OBJECT_FUNCTION_H

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
         class PARAM_4>
class IQuaternaryFunction : public IFunction
{
public:

    // Default constructor.
    IQuaternaryFunction() {}

    // Copy constructor.
    IQuaternaryFunction(const IQuaternaryFunction & orig) {}

    // Destructor.
    virtual ~IQuaternaryFunction() {}

    // Executes the function.
    virtual RETURN_TYPE operator()(PARAM_1 value_1,
                                   PARAM_2 value_2,
                                   PARAM_3 value_3,
                                   PARAM_4 value_4) const = 0;
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
         class PARAM_4>

class QuaternaryObjectFunction :

    public IQuaternaryFunction<RETURN_TYPE, PARAM_1, PARAM_2, PARAM_3, PARAM_4>,
    public ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>
{
public:

    // Default constructor.
    QuaternaryObjectFunction() {}

    // Constructor.
    QuaternaryObjectFunction(OBJECT_TYPE * pNewObj, FUNCTION_TYPE pNewFunc) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(pNewObj, pNewFunc) {}

    // Copy constructor.
    QuaternaryObjectFunction(const QuaternaryObjectFunction & orig) :
        ObjectFunction<OBJECT_TYPE, FUNCTION_TYPE>(orig.GetObjFunc().pObj,
                                                   orig.GetObjFunc().pFunc){}

    // Destructor.
    virtual ~QuaternaryObjectFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new QuaternaryObjectFunction<OBJECT_TYPE,
                                                        FUNCTION_TYPE,
                                                        RETURN_TYPE,
                                                        PARAM_1,
                                                        PARAM_2,
                                                        PARAM_3,
                                                        PARAM_4>(*this);

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
        const QuaternaryObjectFunction * pSafe =
            dynamic_cast<const QuaternaryObjectFunction *>(&rhs);

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
                           PARAM_4 value_4) const
    {
        // This is a situation where we cannot execute the function.
        if(!this->GetObjFunc().IsValid()) throw ObjectFunctionException();

        // Execute the function.
        return (this->GetObjFunc().pObj->*(this->GetObjFunc().pFunc))(value_1,
                                                                      value_2,
                                                                      value_3,
                                                                      value_4);
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
         class PARAM_4>
class ConstQuaternaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1,
                                                 PARAM_2,
                                                 PARAM_3,
                                                 PARAM_4) const;

    // Unary object function templated type.
    typedef QuaternaryObjectFunction<OBJECT_TYPE,
                                     TFuncPtr,
                                     RETURN_TYPE,
                                     PARAM_1,
                                     PARAM_2,
                                     PARAM_3,
                                     PARAM_4> TFuncObj;

public:

    // Constructor.
    ConstQuaternaryObjectFactory() {}

    // Destructor.
    virtual ~ConstQuaternaryObjectFactory() {}

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
         class PARAM_4>
class QuaternaryObjectFactory
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (OBJECT_TYPE::*TFuncPtr)(PARAM_1,
                                                 PARAM_2,
                                                 PARAM_3,
                                                 PARAM_4);

    // Unary object function templated type.
    typedef QuaternaryObjectFunction<OBJECT_TYPE,
                                     TFuncPtr,
                                     RETURN_TYPE,
                                     PARAM_1,
                                     PARAM_2,
                                     PARAM_3,
                                     PARAM_4> TFuncObj;

public:

    // Constructor.
    QuaternaryObjectFactory() {}

    // Destructor.
    virtual ~QuaternaryObjectFactory() {}

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
         class PARAM_4>

class QuaternaryStaticFunction :

    public IQuaternaryFunction<RETURN_TYPE,
                               PARAM_1,
                               PARAM_2,
                               PARAM_3,
                               PARAM_4>
{
public:

    // Function pointer type.
    typedef RETURN_TYPE (*TFuncPtr)(PARAM_1, PARAM_2, PARAM_3, PARAM_4);

public:

    // Constructor.
    QuaternaryStaticFunction(TFuncPtr pFunc)
    {
        pFunction = pFunc;
    }

    // Copy constructor.
    QuaternaryStaticFunction(const QuaternaryStaticFunction & orig)
    {
        pFunction = orig.pFunction;
    }

    // Destructor.
    virtual ~QuaternaryStaticFunction() {}

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const
    {
        // If we are invalid, do not clone ourselves.
        if(!IsValid()) return NULL;

        IFunction * pPtr = new QuaternaryStaticFunction<RETURN_TYPE,
                                                        PARAM_1,
                                                        PARAM_2,
                                                        PARAM_3,
                                                        PARAM_4>(*this);
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
        const QuaternaryStaticFunction * pSafe =
            dynamic_cast<const QuaternaryStaticFunction *>(&rhs);

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
                                   PARAM_4 value_4) const
    {
        return (*pFunction)(value_1, value_2, value_3, value_4);
    }

private:

    // Default constructor.
    QuaternaryStaticFunction() {}

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
         class PARAM_4>

class Delegate<RETURN_TYPE (PARAM_1, PARAM_2, PARAM_3, PARAM_4)> :

    public IFunctionDelegate< IQuaternaryFunction<RETURN_TYPE,
                                                  PARAM_1,
                                                  PARAM_2,
                                                  PARAM_3,
                                                  PARAM_4> >
{
public:

    // Constructor.
    Delegate() {}

    // Copy constructor.
    Delegate(
        const typename IFunctionDelegate< IQuaternaryFunction<
                                              RETURN_TYPE,
                                              PARAM_1,
                                              PARAM_2,
                                              PARAM_3,
                                              PARAM_4> >
        ::TFuncType & newFunc)
    {
        Add(newFunc);
    }

    // Static function constructor.
    Delegate(RETURN_TYPE (*pFunc)(PARAM_1, PARAM_2, PARAM_3, PARAM_4))
    {
        typedef QuaternaryStaticFunction<RETURN_TYPE, PARAM_1, PARAM_2, PARAM_3,
                                         PARAM_4> TFunc;

        TFunc obj = TFunc(pFunc);
        Add(obj);
    }

    // Object function constructor.
    template<class OBJECT_TYPE>
    Delegate(OBJECT_TYPE * pObj,
             RETURN_TYPE (OBJECT_TYPE::*pFunc)(PARAM_1, PARAM_2, PARAM_3,
                                               PARAM_4))
    {
        typedef QuaternaryObjectFactory<OBJECT_TYPE, RETURN_TYPE, PARAM_1,
                                        PARAM_2, PARAM_3, PARAM_4> TFact;
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
                                               PARAM_4) const)
    {
        typedef ConstQuaternaryObjectFactory<OBJECT_TYPE,
                                             RETURN_TYPE,
                                             PARAM_1,
                                             PARAM_2,
                                             PARAM_3,
                                             PARAM_4> TFact;
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
                           PARAM_4 value_4)
    {
        // Clean out invalids on Ftor calls.
        this->CleanOutInvalids();

        // Call this constant operator overload.
        const Delegate<RETURN_TYPE (PARAM_1,
                                    PARAM_2,
                                    PARAM_3,
                                    PARAM_4)> & obj = *this;

        obj(value_1, value_2, value_3, value_4);
    }

    // Operator override.
    RETURN_TYPE operator()(PARAM_1 value_1,
                           PARAM_2 value_2,
                           PARAM_3 value_3,
                           PARAM_4 value_4) const
    {
        // Throw an error if we are empty.
        if(this->size() == 0) throw ObjectFunctionException();

        // Instantiate the iterator.
        typename IFunctionDelegate< IQuaternaryFunction<RETURN_TYPE,
                                                        PARAM_1,
                                                        PARAM_2,
                                                        PARAM_3,
                                                        PARAM_4> >::
        TFuncVector::const_iterator iter;

        // Call all of our contained functions.
        for(iter = this->begin() ; iter != this->end() ; ++iter)
        {
            // Calculate the next iterator.
            typename IFunctionDelegate< IQuaternaryFunction<RETURN_TYPE,
                                                            PARAM_1,
                                                            PARAM_2,
                                                            PARAM_3,
                                                            PARAM_4> >::
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
                    (*(*iter))(value_1, value_2, value_3, value_4);
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
        return (*(*iter))(value_1, value_2, value_3, value_4);
    }
};
}

#endif
