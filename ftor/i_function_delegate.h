/*******************************************************************************
 *
 *  \file
 *
 *  \brief
 *
 *  \note
 *
 ******************************************************************************/

#ifndef I_FUNCTION_DELEGATE_H
#define I_FUNCTION_DELEGATE_H

// Standard library dependencies.
#include <vector>
#include <algorithm>

// General dependencies.
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
template<class CHILD_TYPE>
class IFunctionDelegate : protected std::vector<CHILD_TYPE *>
{
public:

    // Contained object type define.
    typedef CHILD_TYPE TFuncType;

protected:

    // Declare our vector type.
    typedef std::vector<CHILD_TYPE *> TFuncVector;

public:

    // Default constructor.
    IFunctionDelegate() {}

    // Copy Constructor.
    IFunctionDelegate(const IFunctionDelegate & orig)
    {
        *this += orig;
    }

    // Destructor.
    virtual ~IFunctionDelegate()
    {
        // Clean up our class.
        this->ClearAll();
    }

    // Remove the pointer from our vector.
    void Remove(const TFuncType & newFunc)
    {
        typename TFuncVector::iterator iter = this->begin();

        // Go through each element and if it is a match, remove it.
        while(iter != this->end())
        {
            if((*(*iter)) == newFunc)
            {
                // Delete the pointer.
                delete *iter;

                // Remove from the vector.
                erase(iter);

                // There should not be any duplicates.
                break;
            }
            else
            {
                ++iter;
            }
        }
    }

    // Allows the client to add a function.
    void Add(const TFuncType & newFunc)
    {
        // Clean out any invalids.
        CleanOutInvalids();

        // Create a clone on the heap.
        IFunction * pClone = newFunc.Clone();

        // We know were are a of TFuncType * so its ok to downcast.
        TFuncType * pSafe = dynamic_cast<TFuncType *>(pClone);

        // If there is a problem, throw an exception.
        if(pSafe == NULL)
        {
            delete pClone;
            throw ObjectFunctionException();
        }

        // Go through each element and search for a match;
        bool anyMatches = false;
        for(typename TFuncVector::iterator iter = this->begin() ;
            iter != this->end() ;
            ++iter)
        {
            anyMatches |= ((*(*iter)) == newFunc);
        }

        // Only if there are no matches.
        if(!anyMatches)
        {
            // Insert into our vector.
            push_back(pSafe);
        }
        else
        {
            delete pSafe;
        }
    }

    // Clear out the vector.
    void ClearAll()
    {
        // Delete all of the pointers.
        for(typename TFuncVector::iterator iter = this->begin() ;
            iter != this->end() ;
            ++iter)
        {
            delete (*iter);
        }

        // Empty our vector.
        this->clear();
    }

    // Check to see if we have any valid functions.
    bool IsValid()
    {
        // Clean out any invalids.
        CleanOutInvalids();

        // Empty is invalid.
        bool retVal = !this->empty();

        // Go through each element and check for invalids.
        for(typename TFuncVector::iterator iter = this->begin() ;
            iter != this->end() ;
            ++iter)
        {
            // If it is not valid.
            retVal &= (*iter)->IsValid();
        }

        return retVal;
    }

    // Cleans out the container from invalid functions.
    void CleanOutInvalids()
    {
        typename TFuncVector::iterator iter = this->begin();

        // Go through each element and if it is a match, add to our vector.
        while(iter != this->end())
        {
            if(!(*iter)->IsValid())
            {
                // Delete the pointer.
                delete *iter;

                // Remove from the vector.
                erase(iter);

                // Start from the beginning again.
                iter = this->begin();
            }
            else
            {
                ++iter;
            }
        }
    }

    // Gets the number of elements.
    std::size_t Size() const
    {
        return this->size();
    }

    // Add operator.
    virtual const
    IFunctionDelegate & operator+=(const IFunctionDelegate & rhs)
    {
        // Instantiate the iterator.
        typename TFuncVector::const_iterator iter;

        // Copy all of the data locally.
        for(iter = rhs.begin() ; iter != rhs.end() ; ++iter)
        {
            Add(*(*iter));
        }

        return *this;
    }

    // Subtract operator.
    virtual const
    IFunctionDelegate & operator-=(const IFunctionDelegate & rhs)
    {
        // Remove all matching local data.
        for(size_t i = 0 ; i < rhs.size() ; ++i)
        {
            Remove(*(rhs[i]));
        }

        return *this;
    }

    // Assignment operator.
    virtual const IFunctionDelegate & operator=(const IFunctionDelegate & rhs)
    {
        // Clear out all of the function object to reassign our vector.
        ClearAll();

        // Copy all the data.
        for(size_t i = 0 ; i < rhs.size() ; ++i)
        {
            Add(*(rhs[i]));
        }

        // Return a reference to this object.
        return *this;
    }

    // Equality operator.
    virtual bool operator==(const IFunctionDelegate & rhs) const
    {
        bool retVal = false;

        // Check the size also.
        if(this->Size() != rhs.Size()) return retVal;

        // Copy all the data.
        for(size_t i = 0 ; i < rhs.size() ; ++i)
        {
            // Go through each element and search for a match.
            for(typename TFuncVector::const_iterator iter = this->begin() ;
                iter != this->end() ;
                ++iter)
            {
                // At least one has to match.
                retVal |= ((*(*iter)) == (*rhs[i])) ? true : false;
            }

            // Check to see if we have failed, break if we have.
            if(!retVal) 
            {
                break;
            }
            else
            {
                retVal = true;
            }
        }

        return retVal;
    }
};
}

#endif
