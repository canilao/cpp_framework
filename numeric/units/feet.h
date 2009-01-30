/*******************************************************************************

    \file   feet.h

    \brief  Class declaration for a foot of length.

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/

#ifndef FEET_H
#define FEET_H

// General Dependancies.
#include "length.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for a feet.

    \brief  Concrete class for all measurable length units.

*******************************************************************************/
class feet : public length
{
public:

    // Constructor.
    feet();

    // Copy Constructor.
    feet(const feet & origFeet);

    // Decimal number constructor.
    feet(const double & decimalNumber);

    // Base length number constructor.
    feet(const length & origBaseLength);

    // Destructor.
    virtual ~feet();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline feet::feet()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline feet::feet(const feet & origFeet) : length(origFeet)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline feet::feet(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base length constructor.

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline feet::feet(const length & origBaseLength) : length(origBaseLength)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline feet::~feet()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 10/25/2006 Created.

*******************************************************************************/
inline double feet::GetCoreUnitConversion() const
{
    // Conversion for number of core units to a foot.
    const unsigned int inchesInAFoot = 12;

    // Return our conversion.
    return (inchesInAFoot * CORE_UNITS_TO_ONE_INCH);
}
}

#endif
