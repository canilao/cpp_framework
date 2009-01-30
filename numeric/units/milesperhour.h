/*******************************************************************************

    \file   milesperhour.h

    \brief  Class declaration for a unit of time.

    \note   C Anilao 11/02/2006 Created.

*******************************************************************************/

#ifndef MILESPERHOUR_H
#define MILESPERHOUR_H

// General Dependancies.
#include "miles.h"
#include "speed.h"
#include "milepace.h"
#include "unit_math.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for speed.

    \brief  Concrete class for a measurable speed unit.

*******************************************************************************/
class milesPerHour : public speed
{
public:

    // Constructor.
    milesPerHour();

    // Copy Constructor.
    milesPerHour(const milesPerHour & origMilesPerHour);

    // Decimal number constructor.
    milesPerHour(const double & decimalNumber);

    // Base time constructor.
    milesPerHour(const speed & origBaseSpeed);

    // kilometer pace constructor.
    milesPerHour(const milepace & milePaceTime);

    // Destructor.
    virtual ~milesPerHour();

    // Conversion operator overload.
    virtual operator milepace() const;

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

// Typedef for mph, a common description for miles per hour.
typedef milesPerHour mph;

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milesPerHour::milesPerHour()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milesPerHour::milesPerHour(const milesPerHour & origMilesPerHour) :
    speed(origMilesPerHour)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milesPerHour::milesPerHour(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base time constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milesPerHour::milesPerHour(const speed & origBaseSpeed) : speed(
        origBaseSpeed)
{}

/*******************************************************************************

    \brief  Pace time constructor.

    \note   C Anilao 11/10/2006 Created.

*******************************************************************************/
inline milesPerHour::milesPerHour(const milepace & milePaceTime)
{
    // We have time per miles.  We need miles per time for speed.
    (*this) = (miles(1) / milePaceTime);
}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milesPerHour::~milesPerHour()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline double milesPerHour::GetCoreUnitConversion() const
{
    const double inchesInAMile= 63360.0;
    const double secondsInAnHour = 3600.0;

    // Convert miles per hour to inches per second (our core point of reference)
    //
    // inches      1 mile        3600 seconds    miles
    // ------ * ------------- *  ------------- = ------
    // second    63360 inches       1 hour       hour
    //
    double convToMilesPerHour = (1.0 / inchesInAMile) * secondsInAnHour;

    // We still need "core units" per "miles per hour"
    //
    //          CORE UNITS              CORE UNITS
    // ------------------------------ = ----------
    //  inch/sec * convToMilesPerHour   miles/hour
    return CORE_UNITS_TO_INCH_PER_SECOND * (1.0 / convToMilesPerHour);
}

/*******************************************************************************

    \brief  Conversion operator overload.

    \return milepace - milepace representation of this object.

    \note   C Anilao 11/10/2006 Created.

*******************************************************************************/
inline milesPerHour::operator milepace() const
{
    // Making this static const, means less run time operations.
    static const miles oneMile = miles(1);

    // length
    // ------ = time
    // speed
    return milepace(oneMile / (*this));
}
}

#endif
