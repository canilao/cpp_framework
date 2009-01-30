/*******************************************************************************

    \file   pounds.h

    \brief  Class declaration for a unit of mass.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef POUNDS_H
#define POUNDS_H

// General Dependancies.
#include "mass.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for pounds.

    \brief  Concrete class for a measurable mass unit.

*******************************************************************************/
class pounds : public mass
{
public:

    // Constructor.
    pounds();

    // Copy Constructor.
    pounds(const pounds & origPounds);

    // Decimal number constructor.
    pounds(const double & decimalNumber);

    // Base length number constructor.
    pounds(const mass & origBaseMass);

    // Destructor.
    virtual ~pounds();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
pounds::pounds()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
pounds::pounds(const pounds & origPounds) : mass(origPounds)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
pounds::pounds(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base length constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
pounds::pounds(const mass & origBasePounds) : mass(origBasePounds)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
pounds::~pounds()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
double pounds::GetCoreUnitConversion() const
{
    // Return our conversion.
    return (CORE_UNITS_TO_ONE_POUND);
}
}

#endif

