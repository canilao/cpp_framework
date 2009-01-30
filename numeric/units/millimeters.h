/*******************************************************************************

    \file   millimeters.h

    \brief  Class declaration for a millimeter of length.

    \note   C Anilao 10/26/2006 Created.

*******************************************************************************/

#ifndef MILLIMETERS_H
#define MILLIMETERS_H

// Standard Library Dependancies.

// General Dependancies.
#include "length.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for a millimeter.

    \brief  Concrete class for measurable length units.

*******************************************************************************/
class millimeters : public length
{
public:

    // Constructor.
    millimeters();

    // Copy Constructor.
    millimeters(const millimeters & origMillimeters);

    // Decimal number constructor.
    millimeters(const double & decimalNumber);

    // Base length number constructor.
    millimeters(const length & origBaseLength);

    // Destructor.
    virtual ~millimeters();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

     \brief Constructor

     \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline millimeters::millimeters()
{}

/*******************************************************************************

     \brief Copy constructor

     \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline millimeters::millimeters(const millimeters & origMillimeters)
    :
    length(origMillimeters)
{}

/*******************************************************************************

     \brief Decimal constructor.

     \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline millimeters::millimeters(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

     \brief Base length constructor.

     \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline millimeters::millimeters(const length & origBaseLength)
    :
    length(origBaseLength)
{}

/*******************************************************************************

     \brief Destructor

     \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline millimeters::~millimeters()
{}

/*******************************************************************************

     \brief The child class must define this for conversions.

     \note  C Anilao 10/26/2006 Created.

*******************************************************************************/
inline double millimeters::GetCoreUnitConversion() const
{
    // Return our conversion.
    return CORE_UNITS_TO_ONE_MM;
}
}

#endif
