/*******************************************************************************

    \file   unit.h

    \brief  Class declaration for base unit of measure.

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/

#ifndef UNIT_H
#define UNIT_H

// Standard Library Dependancies.
#include <cstdio>
#include <string>
#include <sstream>
#include "../decimal/decimal.h"

namespace numeric
{
/*******************************************************************************

    \class  unit

    \brief  Abstract base class for all measurable units.

*******************************************************************************/
template<unsigned int UNIT_PRECISION>
class unit
{
public:

    // Constructor.
    unit() {}

    // Destructor.
    virtual ~unit() {}

    // Gets the decimal precision of the core data type.
    unsigned int GetCorePrecision() const
    {
        return UNIT_PRECISION;
    }

    // Gets the data element.
    const decimal<UNIT_PRECISION> & GetData() const
    {
        return unitData;
    }

    // Sets the data element.
    void SetData(const decimal<UNIT_PRECISION> & newData)
    {
        unitData = newData;
    }

    // Sets the data element.
    void SetData(const long double & number)
    {
        unitData = number;
    }

    // Gets the maximum value representable by the data.
    long long GetMaxDataValue() const
    {
        return unitData.GetMaxValue();
    }

    // Gets the minimum value representable by the data.
    long long GetMinDataValue() const
    {
        return unitData.GetMinValue();
    }

    // Gets the data element.
    virtual std::string ToString()
    {
        std::ostringstream localstream;
        localstream << (double) unitData;
        return localstream.str();
    }

private:

    // Storage for our data.
    decimal<UNIT_PRECISION> unitData;
};
}

#endif
