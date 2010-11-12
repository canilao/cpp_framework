/******************************************************************************/
//
/*! \file   property.h 
 
    \brief  Implementation of Property templated class.  This class is used
            to manage a piece of data that needs to be monitored for changes.
 
    \note   C Anilao    04/18/2009  Created
 
*******************************************************************************/

#ifndef PROPERTY_H
#define PROPERTY_H

// General dependancies.
#include "unary_function.h"
#include "i_object_function.h"

/******************************************************************************/
//
/*! \namespace  Ftor

    \brief      Included with the functor namespace.

*******************************************************************************/
namespace Ftor
{
/******************************************************************************/
//
/*! \class  Property 
  
    \brief  This class allows a client to moniter when a piece of data is 
            modified.  A client can be notifed right before data is written and 
            after it is written.  The client can also set a filter to check for
            unwanted data that is attempted to be set.
  
*******************************************************************************/
template<class TYPE>
class Property : public ObjectFunctionOwner
{
private:

    // Data that is owned by this class.
    TYPE data;

    // Allows a client to add logic to filter the data that will be set.
    Delegate<TYPE (const TYPE &)> filter_delegate;

    // Allows a client handle changes before the data is written. 
    Delegate<void (const TYPE &)> pre_change_delegate;

    // Allows a client handle changes after the data is written. 
    Delegate<void (const TYPE &)> post_change_delegate;

public:

    // Constructor.
    Property(const TYPE & initialData)
    {
        data = initialData;
    }

    // Destructor.
    virtual ~Property() {}

    // Assignment operator overload.
    void operator=(const TYPE & rhs)
    {
        if(pre_change_delegate.IsValid())
            pre_change_delegate(rhs);

        if(filter_delegate.IsValid())
            data = filter_delegate(rhs);
        else
            data = rhs; 

        if(post_change_delegate.IsValid())
            post_change_delegate(data);
    }

    // Conversion operator overload.
    operator TYPE() const {return data;}

    // Set the change filter delegate.
    void SetChangeFilterDelegate(Delegate<TYPE (const TYPE &)> filter)
    {
        filter_delegate = filter;
    }

    // Unsets the change filter delegate.
    void UnsetChangeFilterDelegate()
    {
        filter_delegate.clear();
    }

    // Add a change filter.
    void AddPreChangeListener(Delegate<void (const TYPE &)> ls)
    {
        pre_change_delegate += ls;
    }

    // Remove a change filter.
    void RemovePreChangeListener(Delegate<void (const TYPE &)> ls)
    {
        pre_change_delegate -= ls;
    }

    // Add a change filter.
    void AddPostChangeListener(Delegate<void (const TYPE &)> ls)
    {
        post_change_delegate += ls;
    }

    // Remove a change filter.
    void RemovePostChangeListener(Delegate<void (const TYPE &)> ls)
    {
        post_change_delegate -= ls;
    }
};
}

#endif
