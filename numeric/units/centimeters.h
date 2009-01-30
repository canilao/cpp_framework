/*******************************************************************************

    \file   centimeters.h

    \brief  Class declaration for a centimeter of length.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/

#ifndef CENTIMETERS_H
#define CENTIMETERS_H

// General Dependancies.
#include "length.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for a centimeter.

    \brief  Concrete class for measurable length units.

*******************************************************************************/
class centimeters : public length
{
public:

    // Constructor.
    centimeters();

    // Copy Constructor.
    centimeters(const centimeters & origCentimeters);

    // Decimal number constructor.
    centimeters(const double & decimalNumber);

    // Base length number constructor.
    centimeters(const length & origBaseLength);

    // Destructor.
    virtual ~centimeters();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline centimeters::centimeters()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline centimeters::centimeters(const centimeters & origCentimeters) 
: length(origCentimeters)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline centimeters::centimeters(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief Base length constructor.

    \note C Anilao 10/26/2006 Created.

*******************************************************************************/
inline centimeters::centimeters(const length & origBaseLength) 
: length(origBaseLength)
{}

/*******************************************************************************

    \brief Destructor

    \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline centimeters::~centimeters()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/
inline double centimeters::GetCoreUnitConversion() const
{
    // Number of millimeters in a centimeter.
    const unsigned int mmInACm = 10;

    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MM * mmInACm);
}
}

#endif
