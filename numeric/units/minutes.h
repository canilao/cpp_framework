/*******************************************************************************
 
    \file   minutes.h
 
    \brief  Class declaration for a unit of time.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/

#ifndef MINUTES_H
#define MINUTES_H

// General Dependancies.
#include "time.h"

namespace numeric
{
/*******************************************************************************
 
    \class  Class for a declaration for minutes.
 
    \brief  Concrete class for a measurable mass unit.
 
*******************************************************************************/
class minutes : public time
{
public:

    // Constructor.
    minutes();

    // Copy Constructor.
    minutes(const minutes & origMinutes);

    // Decimal number constructor.
    minutes(const double & decimalNumber);

    // Base time constructor.
    minutes(const time & origBaseTime);

    // Destructor.
    virtual ~minutes();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************
 
    \brief  Constructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline minutes::minutes()
{}

/*******************************************************************************
 
    \brief  Copy constructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline minutes::minutes(const minutes & origMinutes) : time(origMinutes)
{}

/*******************************************************************************
 
    \brief  Decimal constructor.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline minutes::minutes(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************
 
    \brief  Base time constructor.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline minutes::minutes(const time & origBaseTime) : time(origBaseTime)
{}

/*******************************************************************************
 
    \brief  Destructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline minutes::~minutes()
{}

/*******************************************************************************
 
    \brief  The child class must define this for conversions.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline double minutes::GetCoreUnitConversion() const
{
    const double millisecondsInAMinute = 60000.0;

    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MILLISECOND * millisecondsInAMinute);
}
}

#endif

