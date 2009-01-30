/*******************************************************************************
 
    \file   kilometersperhour.h
 
    \brief  Class declaration for a unit of speed.
 
    \note   C Anilao 11/02/2006 Created.
 
*******************************************************************************/

#ifndef KILOMETERSPERHOUR_H
#define KILOMETERSPERHOUR_H

// General Dependancies.
#include "speed.h"
#include "kmpace.h"
#include "unit_math.h"
#include "kilometers.h"

namespace numeric
{
/*******************************************************************************
 
    \class  Class for a declaration for speed.
 
    \brief  Concrete class for a measurable speed unit.
 
*******************************************************************************/
class kilometersPerHour : public speed
{
public:

    // Constructor.
    kilometersPerHour();

    // Copy Constructor.
    kilometersPerHour(const kilometersPerHour & origkph);

    // Decimal number constructor.
    kilometersPerHour(const double & decimalNumber);

    // Base time constructor.
    kilometersPerHour(const speed & origBaseSpeed);

    // kilometer pace constructor.
    kilometersPerHour(const kmpace & kmPaceTime);

    // Destructor.
    virtual ~kilometersPerHour();

    // Conversion operator overload.
    virtual operator kmpace() const;

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

// Typedef for mph, a common description for miles per hour.
typedef kilometersPerHour kph;

/*******************************************************************************
 
    \brief  Constructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::kilometersPerHour()
{}

/*******************************************************************************
 
    \brief  Copy constructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::kilometersPerHour(const kilometersPerHour & origkph)
    : speed(origkph)
{}

/*******************************************************************************
 
    \brief  Decimal constructor.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::kilometersPerHour(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************
 
    \brief  Base time constructor.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::kilometersPerHour(const speed & origBaseSpeed) :
    speed(origBaseSpeed)
{}

/*******************************************************************************
 
    \brief  Pace time constructor.
 
    \note   C Anilao 11/10/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::kilometersPerHour(const kmpace & kmPaceTime)
{
    // We have time per kilometer.  We need kilometer per time for speed.
    (*this) = (kilometers(1) / kmPaceTime);
}

/*******************************************************************************
 
    \brief  Destructor
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::~kilometersPerHour()
{}

/*******************************************************************************
 
    \brief  The child class must define this for conversions.
 
    \note   C Anilao 11/01/2006 Created.
 
*******************************************************************************/
inline double kilometersPerHour::GetCoreUnitConversion() const
{
    const double mmInAkm = 1000000.0;
    const double secondsInAnHour = 3600.0;

    // Convert km per hour to mm per second (our core point of reference)
    //
    //   mm         1 km      3600 seconds     km
    // ------ * ----------- * ------------- = ----
    // second    1000000 mm      1 hour       hour
    //
    double convTokmPerHour = (1.0 / mmInAkm) * secondsInAnHour;

    // We still need "core units" per "kilometers per hour"
    //
    //        CORE UNITS           CORE UNITS
    // ------------------------- = ----------
    //  mm/sec * convTokmPerHour    km/hour
    return CORE_UNITS_TO_MM_PER_SECOND * (1.0 / convTokmPerHour);
}

/*******************************************************************************
 
    \brief  Conversion operator overload.
 
    \return kmpace - kmpace representation of this object.
 
    \note   C Anilao 11/10/2006 Created.
 
*******************************************************************************/
inline kilometersPerHour::operator kmpace() const
{
    // Making this static const, means less run time operations.
    static const kilometers oneKm = kilometers(1);

    // length
    // ------ = time
    // speed
    return kmpace(oneKm / (*this));
}
}

#endif

