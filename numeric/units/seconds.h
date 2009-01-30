/*******************************************************************************

    \file   seconds.h

    \brief  Class declaration for a unit of time.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef SECONDS_H
#define SECONDS_H

// General Dependancies.
#include "time.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for seconds.

    \brief  Concrete class for a measurable mass unit.

*******************************************************************************/
class seconds : public time
{
public:

    // Constructor.
    seconds();

    // Copy Constructor.
    seconds(const seconds & origSeconds);

    // Decimal number constructor.
    seconds(const double & decimalNumber);

    // Base length number constructor.
    seconds(const time & origBaseTime);

    // Destructor.
    virtual ~seconds();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline seconds::seconds()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline seconds::seconds(const seconds & origSeconds) : time(origSeconds)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline seconds::seconds(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base time constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline seconds::seconds(const time & origBaseSeconds) : time(origBaseSeconds)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline seconds::~seconds()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline double seconds::GetCoreUnitConversion() const
{
    const double millisecondsInASecond = 1000.0;

    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MILLISECOND * millisecondsInASecond);
}
}

#endif

