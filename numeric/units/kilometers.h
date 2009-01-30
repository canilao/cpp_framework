/*******************************************************************************

    \file   kilometers.h

    \brief  Class declaration for a centimeter of length.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/

#ifndef KILOMETERS_H
#define KILOMETERS_H

// General Dependancies.
#include "length.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for a centimeter.

    \brief  Concrete class for measurable length units.

*******************************************************************************/
class kilometers : public length
{
public:

    // Constructor.
    kilometers();

    // Copy Constructor.
    kilometers(const kilometers & origMeters);

    // Decimal number constructor.
    kilometers(const double & decimalNumber);

    // Base length number constructor.
    kilometers(const length & origBaseLength);

    // Destructor.
    virtual ~kilometers();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

// Typedef for km, a common description for kilometers.
typedef kilometers km;

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline kilometers::kilometers()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline kilometers::kilometers(const kilometers & origKilometers) : length(
        origKilometers)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline kilometers::kilometers(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base length constructor.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline kilometers::kilometers(const length & origBaseLength) : length(
        origBaseLength)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline kilometers::~kilometers()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline double kilometers::GetCoreUnitConversion() const
{
    // Number of millimeters in a kilometer.
    const unsigned int mmInAKilometer = 1000000;

    // Return our conversion.
    return CORE_UNITS_TO_ONE_MM * mmInAKilometer;
}
}

#endif
