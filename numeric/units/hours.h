/*******************************************************************************
 
    \file   hours.h
 
    \brief  Class declaration for a unit of time.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/

#ifndef HOURS_H
#define HOURS_H

// General Dependancies.
#include "time.h"

namespace numeric
{
/*******************************************************************************
 
    \class  Class for a declaration for hours.
 
    \brief  Concrete class for a measurable mass unit.
 
*******************************************************************************/
class hours : public time
{
public:

    // Constructor.
    hours();

    // Copy Constructor.
    hours(const hours & origHours);

    // Decimal number constructor.
    hours(const double & decimalNumber);

    // Base time constructor.
    hours(const time & origBaseTime);

    // Destructor.
    virtual ~hours();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************
 
    \brief  Constructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline hours::hours()
{}

/*******************************************************************************
 
    \brief  Copy constructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline hours::hours(const hours & origHours) : time(origHours)
{}

/*******************************************************************************
 
    \brief  Decimal constructor.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline hours::hours(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************
 
    \brief  Base time constructor.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline hours::hours(const time & origBaseTime) : time(origBaseTime)
{}

/*******************************************************************************
 
    \brief  Destructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline hours::~hours()
{}

/*******************************************************************************
 
    \brief  The child class must define this for conversions.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline double hours::GetCoreUnitConversion() const
{
    const double millisecondsInAnHour = 3600000.0;

    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MILLISECOND * millisecondsInAnHour);
}
}

#endif

