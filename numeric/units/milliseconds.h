/*******************************************************************************

    \file   milliseconds.h

    \brief  Class declaration for a unit of mass.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef MILLISECONDS_H
#define MILLISECONDS_H

// General Dependancies.
#include "time.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for milliseconds.

    \brief  Concrete class for a measurable mass unit.

*******************************************************************************/
class milliseconds : public time
{
public:

    // Constructor.
    milliseconds();

    // Copy Constructor.
    milliseconds(const milliseconds & origMilliseconds);

    // Decimal number constructor.
    milliseconds(const double & decimalNumber);

    // Base length number constructor.
    milliseconds(const time & origBaseTime);

    // Destructor.
    virtual ~milliseconds();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milliseconds::milliseconds()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milliseconds::milliseconds(const milliseconds & origMilliseconds)
    :
    time(origMilliseconds)
{}

/*******************************************************************************

    \brief  Decimal constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milliseconds::milliseconds(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************

    \brief  Base time constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milliseconds::milliseconds(const time & origBaseMilliseconds)
    :
    time(origBaseMilliseconds)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milliseconds::~milliseconds()
{}

/*******************************************************************************

    \brief  The child class must define this for conversions.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline double milliseconds::GetCoreUnitConversion() const
{
    // Return our conversion.
    return (CORE_UNITS_TO_ONE_MILLISECOND);
}
}

#endif

