/*******************************************************************************

    \file   kilograms.h

    \brief  Class declaration for a unit of mass.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef KILOGRAMS_H
#define KILOGRAMS_H

// General Dependancies.
#include "mass.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for kilograms.

    \brief  Concrete class for a measurable mass unit.

*******************************************************************************/
class kilograms : public mass
{
public:

    // Constructor.
    kilograms();

    // Copy Constructor.
    kilograms(const kilograms & origKilograms);

    // Decimal number constructor.
    kilograms(const double & decimalNumber);

    // Base length number constructor.
    kilograms(const mass & origBaseMass);

    // Destructor.
    virtual ~kilograms();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kilograms::kilograms()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kilograms::kilograms(const kilograms & origKilograms) : mass(
        origKilograms)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kilograms::kilograms(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base length constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kilograms::kilograms(const mass & origBaseKilograms) : mass(
        origBaseKilograms)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kilograms::~kilograms()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline double kilograms::GetCoreUnitConversion() const
{
    // Number of micrograms in a kilogram.
    const long double ugToKg = 1000000000.0L;

    // Return our conversion.
    return ((long double) CORE_UNITS_TO_ONE_MICROGRAM * ugToKg);
}
}

#endif

