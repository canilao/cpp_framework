/*******************************************************************************
 
    \file  inches.h
 
    \brief Class declaration for a inch of length.
 
    \note  C Anilao 10/26/2006 Created.
 
*******************************************************************************/

#ifndef INCHES_H
#define INCHES_H

// General Dependancies.
#include "length.h"

namespace numeric
{
/*******************************************************************************
 
    \class  Class for a declaration for an inch.
 
    \brief  Concrete class for measurable length units.
 
*******************************************************************************/
class inches : public length
{
public:

    // Constructor.
    inches();

    // Copy Constructor.
    inches(const inches & origInches);

    // Decimal number constructor.
    inches(const double & decimalNumber);

    // Base length number constructor.
    inches(const length & origBaseLength);

    // Destructor.
    virtual ~inches();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;
};

/*******************************************************************************
 
    \brief  Constructor
 
    \note   C Anilao 10/26/2006 Created.
 
*******************************************************************************/
inline inches::inches()
{}

/*******************************************************************************
 
    \brief  Copy constructor
 
    \note   C Anilao 10/26/2006 Created.
 
*******************************************************************************/
inline inches::inches(const inches & origInches) : length(origInches)
{}

/*******************************************************************************
 
    \brief  Decimal constructor.
 
    \note   C Anilao 10/26/2006 Created.
 
*******************************************************************************/
inline inches::inches(const double & decimalNumber)
{
    // Use our assignment operator to assign ourself.
    SetData(decimalNumber * GetCoreUnitConversion());
}

/*******************************************************************************
 
    \brief  Base length constructor.
 
    \note   C Anilao 10/26/2006 Created.
 
*******************************************************************************/
inline inches::inches(const length & origBaseLength) : length(origBaseLength)
{}

/*******************************************************************************
 
    \brief  Destructor
 
    \note   C Anilao 10/26/2006 Created.
 
*******************************************************************************/
inline inches::~inches()
{}

/*******************************************************************************
 
    \brief  The child class must define this for conversions.
 
    \note   C Anilao 10/26/2006 Created.
 
*******************************************************************************/
inline double inches::GetCoreUnitConversion() const
{
    // Return our conversion.
    return CORE_UNITS_TO_ONE_INCH;
}
}

#endif
