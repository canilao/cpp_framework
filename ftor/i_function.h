/******************************************************************************/
//
/*! \file

    \brief

 *******************************************************************************/

#ifndef I_FUNCTION_H
#define I_FUNCTION_H

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
class IFunction
{
public:

    // Default constructor.
    IFunction() {}

    // Copy constructor.
    IFunction(const IFunction & orig) {}

    // Destructor.
    virtual ~IFunction() {}

    // Checks to see if the structure has valid data.
    virtual bool IsValid() const = 0;

    // Equality operator.
    virtual bool operator==(const IFunction & rhs) = 0;

    // Allows the object to make a deep copy.
    virtual IFunction * Clone() const = 0;
};
}

#endif
