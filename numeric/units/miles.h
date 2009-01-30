/*******************************************************************************

    \file  miles.h

    \brief Class declaration for a mile of length.

    \note  C Anilao 10/05/2006 Created.

*******************************************************************************/

#ifndef MILES_H
#define MILES_H

// General Dependancies.
#include "length.h"

// Exactly how many inches are in a mile.
#define INCHES_IN_A_MILE 63360ULL

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for a mile.

    \brief  Concrete class for measurable length units.

*******************************************************************************/
class miles : public length
{
public:

    // Constructor.
    miles();

    // Copy Constructor.
    miles(const miles & origMiles);

    // Decimal number constructor.
    miles(const double & decimalNumber);

    // Base length number constructor.
    miles(const length & origBaseLength);

    // Destructor.
    virtual ~miles();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief Constructor

    \note  C Anilao 10/05/2006 Created.

*******************************************************************************/
inline miles::miles()
{}

/*******************************************************************************

    \brief Constructor

    \note  C Anilao 10/05/2006 Created.

*******************************************************************************/
inline miles::miles(const miles & origMiles) : length(origMiles)
{}

/*******************************************************************************

    \brief Decimal constructor.

    \note  C Anilao 10/05/2006 Created.

*******************************************************************************/
inline miles::miles(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief Base length constructor.

    \note  C Anilao 10/05/2006 Created.

*******************************************************************************/
inline miles::miles(const length & origBaseLength) : length(origBaseLength)
{}

/*******************************************************************************

    \brief Destructor

    \note  C Anilao 10/05/2006 Created.

*******************************************************************************/
inline miles::~miles()
{}

/*******************************************************************************

    \brief The child class must define this for conversions.

    \note  C Anilao 10/25/2006 Created.

*******************************************************************************/
inline double miles::GetCoreUnitConversion() const
{
    // Return our conversion.
    return (INCHES_IN_A_MILE * CORE_UNITS_TO_ONE_INCH);
}
}

#endif
