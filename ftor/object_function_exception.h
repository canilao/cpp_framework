/******************************************************************************/
//
/*! \file

    \brief

*******************************************************************************/

#ifndef OBJECT_FUNCTION_EXCEPTION_H
#define OBJECT_FUNCTION_EXCEPTION_H

// Standard library dependencies.
#include <exception>

/******************************************************************************/
//
/*! \namespace

    \brief

*******************************************************************************/
namespace Ftor
{
/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class ObjectFunctionException : public std::exception
{
public:

    // Constructor.
    ObjectFunctionException() {}

    // Destructor.
    virtual ~ObjectFunctionException() throw () {}
};
}

#endif
