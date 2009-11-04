/*******************************************************************************

    \file   length.h

    \brief  Contains class implementation for base length.

            Core data is in 1/10TH MILLIMETERS.  This is because, you can
            calculate all other lengths in whole numbers from this size.

            For example: 1 inch, the smallest English Unit (without fractions)
                         is exactly 254 1/10th Millimeters.

    \note   C Anilao 10/05/2006 Created.
    \note   C Anilao 11/27/2006 Rewrote calulation so that the number of
                                floating point operations would be reduced.

*******************************************************************************/

#ifndef LENGTH_H
#define LENGTH_H

// Standard Library Depedencies.
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>

// General Depedencies.
#include "unit.h"

// This defines how many coredata units makes one millimeter.
#define CORE_UNITS_TO_ONE_MM 10000ULL

// This defines how many coredata units makes one inch.
#define CORE_UNITS_TO_ONE_INCH 254000ULL

// The number of decimal points needed to represent the core unit accurately.
#define LENGTH_PRECISION 2u

namespace numeric
{
/*******************************************************************************

    \class  length

    \brief  Abstract base class for all measurable length units.

*******************************************************************************/
class length : public unit<LENGTH_PRECISION>
{
public:

    // Constructor.
    length();

    // Copy Constructor.
    length(const length & origBaseLength);

    // Destructor.
    virtual ~length();

    // The child class must define this for conversions.
    virtual double GetCoreUnitConversion() const;

    // length assignment operator overload.
    virtual length operator=(const length & rhs);

    // Decimal number assignment operator overload.
    virtual length operator=(const double & rhs);

    // Addition operator overload.
    virtual length operator+(const length & rhs) const;

    // Subtraction operator overload.
    virtual length operator-(const length & rhs) const;

    // Addition operator overload.
    virtual length operator+=(const length & rhs);

    // Subtraction operator overload.
    virtual length operator-=(const length & rhs);

    // Equality operator overload.
    virtual bool operator==(const length & rhs) const;

    // Inequality operator overload.
    virtual bool operator!=(const length & rhs) const;

    // Greater-or-equal-than operator overload.
    virtual bool operator>=(const length & rhs) const;

    // Less-or-equal-than operator overload.
    virtual bool operator<=(const length & rhs) const;

    // Greater operator overload.
    virtual bool operator>(const length & rhs) const;

    // Less-or-equal-than operator overload.
    virtual bool operator<(const length & rhs) const;

    // Conversion operator overload.
    virtual operator double() const;

    // Conversion operator overload.
    virtual operator int() const;

    // Conversion operator overload.
    virtual operator unsigned long() const;

    // Override for string conversion.
    virtual std::string ToString() const;

    // Conversion operator overload.
    virtual operator std::string() const;

    // Calculates the highest decimal point precision this object can represent.
    unsigned int GetHighestDecimalPrecision();

    // Calculates the highest whole number precision this object can represent.
    unsigned int GetHighestWholePrecision();

    // Gets the maximum value for this object.
    long long GetMaximumValue();

    // Gets the minimum value for this object.
    long long GetMinimumValue();

    // Gets the smallest value representable by this object.
    long double GetSmallestValue();

    // This helps calculate the required precision the core data value needs.
    unsigned int CalculateRequiredDataPrecision();
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline length::length()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline length::length(const length & origBaseLength)
{
    // Save our data to this object.
    SetData(origBaseLength.GetData());
}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline length::~length()
{}

/*******************************************************************************

    \brief  Addition operator overload.

    \param  const length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 10/16/2006 Created.

*******************************************************************************/
inline length length::operator+(const length & rhs) const
{
    // Create an object to do our calculations.
    length retObj;

    // Do our addition and set our data.
    retObj.SetData(GetData() + rhs.GetData());

    // Return our result.
    return retObj;
}

/*******************************************************************************

    \brief  Subtraction operator overload.

    \param  const length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 10/16/2006 Created.

*******************************************************************************/
inline length length::operator-(const length & rhs) const
{
    // Create an object to do our calculations.
    length retObj;

    // Do our subtraction and set our data.
    retObj.SetData(GetData() - rhs.GetData());

    // Return our result.
    return retObj;
}

/*******************************************************************************

    \brief  Addition increment operator overload.

    \param  const length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 11/07/2006 Created.

*******************************************************************************/
inline length length::operator+=(const length & rhs)
{
    // Do our addition and set our data.
    SetData(GetData() + rhs.GetData());

    // Return our result.
    return (*this);
}

/*******************************************************************************

    \brief  Subtraction increment operator overload.

    \param  const length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 11/07/2006 Created.

*******************************************************************************/
inline length length::operator-=(const length & rhs)
{
    // Do our subtraction and set our data.
    SetData(GetData() - rhs.GetData());

    // Return our result.
    return (*this);
}

/*******************************************************************************

    \brief  Equality operator overload.

    \param  const length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 10/16/2006 Created.
    \note   N Alcantara 12/05/2006 Changed the equality operation to just
                                   operate on the max amount of precision
                                   digits.

*******************************************************************************/
inline bool length::operator==(const length & rhs) const
{
    return GetData() == rhs.GetData();
}

/*******************************************************************************

    \brief  Inequality operator overload.

    \param  const length & - length to be operated with.

    \return length - Copy of this object.

    \note   N Alcantara 12/01/2006 Created.
    \note   N Alcantara 12/05/2006 Forcing overloaded operator usage: == prior
                                   to negation

*******************************************************************************/
inline bool length::operator!=(const length & rhs) const
{
    return !(*this == rhs);
}

/*******************************************************************************

    \brief  Greater-or-equal-than operator overload.

    \param  const length & - length to be operated with.

    \return bool - True if comparison is correct, false if not.

    \note   C Anilao 10/16/2006 Created.
    \note   N Alcantara 12/05/2006 Forcing overloaded operator usage, > and ==

*******************************************************************************/
inline bool length::operator>=(const length & rhs) const
{
    return ((*this > rhs) || (*this == rhs));
}

/*******************************************************************************

    \brief  Less-or-equal-than operator overload.

    \param  const length & - length to be operated with.

    \return bool - True if comparison is correct, false if not.

    \note   C Anilao 10/16/2006 Created.
    \note   N Alcantara 12/05/2006 Forcing overloaded operator usage, < and ==

*******************************************************************************/
inline bool length::operator<=(const length & rhs) const
{
    return ((*this < rhs) || (*this == rhs));
}

/*******************************************************************************

    \brief  operator overload.

    \param  const length & - length to be operated with.

    \return bool - True if comparison is correct, false if not.

    \note   C Anilao 10/16/2006 Created.

*******************************************************************************/
inline bool length::operator>(const length & rhs) const
{
    return (GetData() > rhs.GetData());
}

/*******************************************************************************

    \brief  operator overload.

    \param  length & - length to be operated with.

    \return bool - True if comparison is correct, false if not.

    \note   C Anilao 10/16/2006 Created.

*******************************************************************************/
inline bool length::operator<(const length & rhs) const
{
    return (GetData() < rhs.GetData());
}

/*******************************************************************************

    \brief  Child class must define this for conversions.

    \return double - Returns the object conversion ratio.
                     i.e. 1 millimeter is equal to 10 coreunits.
                     So the millimeter object would return 10.

    \note   C Anilao 10/25/2006 Created.

*******************************************************************************/
inline double length::GetCoreUnitConversion() const
{
    // Return a default value.
    return 1.0;
}

/*******************************************************************************

    \brief  operator overload.

    \param  length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 10/16/2006 Created.

*******************************************************************************/
inline length length::operator=(const length & rhs)
{
    // Save our data to this object.
    SetData(rhs.GetData());

    // Return this a copy of this object back to the client.
    return (*this);
}

/*******************************************************************************

    \brief  operator overload.

    \param  length & - length to be operated with.

    \return length - Copy of this object.

    \note   C Anilao 10/16/2006 Created.

*******************************************************************************/
inline length length::operator=(const double & rhs)
{
    // Calculate our convertion to core units, and save to our object.
    SetData(rhs * GetCoreUnitConversion());

    // Return this a copy of this object back to the client.
    return (*this);
}

/*******************************************************************************

    \brief  String representation of the data.

    \return string - String representation of this object.

    \note   C Anilao 10/05/2006 Created.

*******************************************************************************/
inline std::string length::ToString() const
{
    long double out = (long double) GetData() /
                      (long double) GetCoreUnitConversion();

    // Use string stream to convert and format the double properly.
    std::ostringstream localstream;
    localstream << std::setprecision(10) << out;

    return localstream.str();
}

/*******************************************************************************

    \brief  operator overload.

    \param  length & - length to be operated with.

    \return string - String representation of this object.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline length::operator std::string() const
{
    return ToString();
}

/*******************************************************************************

    \brief  operator overload.

    \return double - double representation of this object.

    \note C Anilao 08/25/2006 Created.
    \note N Alcantara 12/01/2006 Removed Round.  Rounding the resulting
                                 conversion caused error when casting values
                                 to doubles.
    \note C Anilao 01/16/2007 Per design we are going to round any infomation
                              that is going out of the unit library.  Replaced
                              the round function.

*******************************************************************************/
inline length::operator double() const
{
    return (double) GetData() / (double) GetCoreUnitConversion();
}

/*******************************************************************************

    \brief  operator overload.

    \return int - integer representation of this object.

    \note   C Anilao 08/25/2006 Created.
    \note   C Anilao 12/06/2006 Have to round here because if the resulting
                                double conversion is slightly lower, the int
                                cast will act like a call to floor() call and
                                we could lose an entire number.  10.0 one was
                                case was slightly lower than 10.0 and the int
                                cast was resulting in a value of 9.

*******************************************************************************/
inline length::operator int() const
{
    // Make sure we are not losing any data when we cast to a smaller size.
    return static_cast<int>(static_cast<double>(*this));
}

/*******************************************************************************

    \brief  operator overload.

    \return unsigned long - integer representation of this object in long
                            datatype.

    \note   C Anilao 08/25/2006 Created.

*******************************************************************************/
inline length::operator unsigned long() const
{
    // Make sure we are not losing any data when we cast to a smaller size.
    return static_cast<unsigned long>(static_cast<double>(*this));
}

/*******************************************************************************

    \brief  Number of decimal significant digits this number can hold.

    \return unsigned int - Highest number of decimal significant digits.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline unsigned int length::GetHighestDecimalPrecision()
{
    // Calculate the smallest number representable by this object.
    long double smallest = GetSmallestValue();
    long double precision = 0.0L;

    // Increment precision until we get a whole number.
    while((int) (smallest * (long double) pow(10.0L, precision)) <= 0)
    {
        ++precision;
    }

    // The precision is one less then the number of decimal places.
    // e.g. if the smallest number is 0.003 then you can only accurately
    // represent two decimal places. Before this calculation, precision is
    // one decimal place higher then it should be.
    precision = precision > 0.0L ? precision - 1 : 0.0L;

    return (unsigned int) precision;
}

/*******************************************************************************

    \brief  Number of whole number significant digits this number can hold.

    \return unsigned int - Highest number of significant digits.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline unsigned int length::GetHighestWholePrecision()
{
    // Calculate the largest number representable by this object.
    long double largest = (long double) GetMaxDataValue() /
                          (long double) GetCoreUnitConversion();

    long double precision = 0.0L;

    // Increment precision until we get a whole number.
    while((long long)(largest / (long double) pow(10.0L, precision)) > 0)
    {
        ++precision;
    }

    return (unsigned int) precision;
}

/*******************************************************************************

    \brief  Gets the maximum representable value.

    \return long long - Highest representable value.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline long long length::GetMaximumValue()
{
    // Calculate the largest number representable by this object.
    long double largest = (long double) GetMaxDataValue() /
                          (long double) GetCoreUnitConversion();

    return (long long) largest;
}

/*******************************************************************************

    \brief  Gets the minimum representable value.

    \return long long - Lowest representable value.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline long long length::GetMinimumValue()
{
    // Calculate the largest number representable by this object.
    long double lowest = (long double) GetMinDataValue() /
                         (long double) GetCoreUnitConversion();

    return (long long) lowest;
}

/*******************************************************************************

    \brief  Gets the smallest representable value.

    \return long double - Smallest representable value.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline long double length::GetSmallestValue()
{
    // Calculate the smallest number representable by this object.
    long double smallest =  1.0L / (long double) GetCoreUnitConversion();

    return smallest;
}

/*******************************************************************************

    \brief  Calculates what the precision of the parent unit should be.  The
            smallest units should use this data to set the precision.
            e.g. The smallest standard unit is inches.  The smallest value
            is 0.0001 inches.  This converts to a core unit of 2.54.  This
            that the core unit needs 2 decimal places to represent this
            correctly:

            inches x;
            unsigned int y = x.CalculateRequiredDataPrecision();

            y will yield the number 2.  This should be the length family's
            precision for the core unit value.

    \return unsigned int - The value that the unit precision should be set to.

    \note   C Anilao 01/21/2009 Created.

*******************************************************************************/
inline unsigned int length::CalculateRequiredDataPrecision()
{
    // Get the smallest number at the highest precision representable.
    double smallest = pow(10.0, (double) GetHighestDecimalPrecision() * -1.0);

    // Multiplying the core conversion by the smallest number will generate a 
	// the core unit value needs to represented accuratly.  The number of decimal 
	// places this number is what the precision of the core data type should be 
	// set to.
    double smallest_core = smallest * GetCoreUnitConversion();

    std::ostringstream local_stream;

    local_stream << std::setprecision(20) << smallest_core;
    std::string smallest_core_str = local_stream.str();

    unsigned int unit_precision_counter = 0;

    // Use a flag to signal a decimal point has been located.
    bool decimal_found = false;

    // Run though the string and find any numbers after the decimal point.
    for(unsigned int i = 0 ; i < smallest_core_str.size() ; ++i)
    {
        // Increment the counter only if the decimal was located.
        if(decimal_found) ++unit_precision_counter;

        // Set the flag if we run into a decimal point.
        decimal_found |= (smallest_core_str.at(i) == '.');
    }

    return unit_precision_counter;
}
}

#endif
