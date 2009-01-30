/*******************************************************************************

    \file   days.h

    \brief  Class declaration for a unit of time.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef DAYS_H
#define DAYS_H

// General Dependancies.
#include "time.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for days.

    \brief  Concrete class for a measurable mass unit.

*******************************************************************************/
class days : public time
{
public:

    // Constructor.
    days();

    // Copy Constructor.
    days(const days & origDays);

    // Decimal number constructor.
    days(const double & decimalNumber);

    // Base time constructor.
    days(const time & origBaseTime);

    // Destructor.
    virtual ~days();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline days::days()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline days::days(const days & origDays) : time(origDays)
{}

/*******************************************************************************

   \brief   Decimal constructor.

   \note    C Anilao 11/01/2006 Created.

 ******************************************************************************/
inline days::days(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base time constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline days::days(const time & origBaseTime) : time(origBaseTime)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline days::~days()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline double days::GetCoreUnitConversion() const
{
    const double millisecondsInADay= 86400000.0;

    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MILLISECOND * millisecondsInADay);
}
}

#endif

