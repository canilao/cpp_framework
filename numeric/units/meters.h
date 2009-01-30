/*******************************************************************************

    \file   meters.h

    \brief  Class declaration for a centimeter of length.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/

#ifndef METERS_H
#define METERS_H

// General Dependancies.
#include "length.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for a centimeter.

    \brief  Concrete class for measurable length units.

*******************************************************************************/
class meters : public length
{
public:

    // Constructor.
    meters();

    // Copy Constructor.
    meters(const meters & origMeters);

    // Decimal number constructor.
    meters(const double & decimalNumber);

    // Base length number constructor.
    meters(const length & origBaseLength);

    // Destructor.
    virtual ~meters();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline meters::meters()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline meters::meters(const meters & origMeters) : length(origMeters)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline meters::meters(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base length constructor.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline meters::meters(const length & origBaseLength) : length(origBaseLength)
{}

/*******************************************************************************

    \brief Destructor

    \note C Anilao 10/26/2006 Created.

*******************************************************************************/
inline meters::~meters()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline double meters::GetCoreUnitConversion() const
{
    // Number of millimeters in a meter.
    const unsigned int mmInAMeter = 1000;

    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MM * mmInAMeter);
}
}

#endif
