/*******************************************************************************

    \file   decimal.h

    \brief  Implementation of fixed point type.

    \note   C Anilao 01/22/2009 Created.

*******************************************************************************/

#ifndef DECIMAL_H
#define DECIMAL_H

// Standard library dependencies.
#include <cmath>
#include <limits>
#include <sstream>
#include <iomanip>
#include <exception>

// Maximum precision a long long can hold.
#define MAX_PRECISION 17

namespace numeric
{
/*******************************************************************************

    \class  Fixed point data type class.

    \brief  This is a fixed point alternative to using floating point.  This
            class has the advantage of having a controlled error when
            arithmetic operation are done on fractional numbers.

*******************************************************************************/
template<unsigned int PRECISION>
class decimal
{
private:

    // Core data type.
    typedef long long TData;

    // The core data member.
    TData data;

private:

    // IEEE states for a float f, f != f will be true only if f is NaN.
    bool IsNaN(long double number) const
    {
        volatile double testNumber = number;
        return testNumber != testNumber;
    }

    // Set the data variable using the minimum and maximum bounds.
    void SetData(TData newData)
    {
        if(newData > this->GetMaxValue() ||
           newData < this->GetMinValue() )
        {
            // If we throw an exception here, we over/underflowed.
            throw std::exception();
        }

        // It's safe to set the data if the value was in range.
        data = newData;
    }

public:

    // Default constructor.
    decimal() : data(0)
    {
        if(PRECISION > MAX_PRECISION) throw std::exception();
    }

    // Copy constructor.
    decimal(const decimal<PRECISION> & orig) : data(orig.data)
    {
        if(PRECISION > MAX_PRECISION) throw std::exception();
    }

    // Constructor with a long double.
    decimal(const long double & number)
    {
        if(PRECISION > MAX_PRECISION) throw std::exception();

        // Move the decimal point so that the desired number becomes a integer.
        // The decimal point is moved over on more point for rounding purposes.
        SetData((TData) (number * pow(10.0, (double) (PRECISION + 1))));

        // Calculate the sign.  Do not divide by zero.
        TData sign = 0;
        if(data != 0)
        {
            sign = (TData) (fabs((double) data) / data);
        }

        // Currently data's decimal point is moved over one extra point
        // so that we can round here.
        // e.g.
        // If number was passed in as 10.6 we move the decimal point to the
        // right.  So 10.6 becomes 106.0.  Then we add 5, then move the decimal
        // point back to normal.  111.0 (add 5) ... 11.1 (move decimal point
        // back).  Then we put that number in a integer and this will
        // effectively removed the decimal point at we will end up with an 11.
        // Note that 11 is the rounded value for 10.6.
        SetData(sign * (((TData) fabs((double) data) + 5) / 10));
    }

    // Destructor.
    ~decimal() {}

    // Calculates the maximum inclusive whole number that this class can hold.
    static TData GetMaxValue()
    {
        // Slides the value of LLONG_MAX to the right so that the decimal
        // values are truncated.
        // e.g.
        // If our data type was a char, the maximum value for char is 255.
        // If we set our PRECISION to 1, our maximum value is
        // 255 / 10^(PRECISION + 1).  This makes our maximum number 2.
        // This is 2 instead of 25 because we need the left most digit
        // for rounding.  If we wanted to represent 1.66, we would need to
        // set data to 166, multiply by 10, yielding 166.  Add 5, yielding
        // 171.  Then we would need to truncate the right most digit by
        // dividing by 10, yielding 17.  data = 17 represents 1.7 in this
        // example.  Since we have tried to place a number that has
        // a precision of 2 we needed to round this number.  Rounding
        // requires an extra left most digit.  This is reflected by the
        // PRECISION + 1 below.
        return LLONG_MAX / (long long) pow(10.0, (double) (PRECISION + 1));
    }

    // Calculate the inclusive minimum value this class can hold.
    static TData GetMinValue()
    {
        // Slides the value of LLONG_MAX to the right so that the decimal
        // values are truncated.
        // e.g.
        // If our data type was a char, the maximum value for char is 255.
        // If we set our PRECISION to 1, our maximum value is
        // 255 / 10^(PRECISION + 1).  This makes our maximum number 2.
        // This is 2 instead of 25 because we need the left most digit
        // for rounding.  If we wanted to represent 1.66, we would need to
        // set data to 166, multiply by 10, yielding 166.  Add 5, yielding
        // 171.  Then we would need to truncate the right most digit by
        // dividing by 10, yielding 17.  data = 17 represents 1.7 in this
        // example.  Since we have tried to place a number that has
        // a precision of 2 we needed to round this number.  Rounding
        // requires an extra left most digit.  This is reflected by the
        // PRECISION + 1 below.
        return LLONG_MIN / (long long) pow(10.0, (double) (PRECISION + 1));
    }

    // Multiplication between this object and a object of the same type.
    decimal<PRECISION> operator*(const decimal<PRECISION> & rhs) const
    {
        // Operate using floating point.  This is valid since the operation
        // is relatively short and the error is removed when the value
        // saved back into a decimal object.  The action of saving to
        // a decimal object will remove error and represent an exact number.
        long double result = (long double)(*this) * (long double) rhs;

        // Calculate the +/- sign.
        long double sign = fabs(result) / result;
        if(IsNaN(sign))
        {
            sign = 0.0L;
        }

        // Result value slided to the left for rounding.
        result *= (long double) pow(10.0, (double) (PRECISION + 1));
        result += 5.0L * sign;

        // Slide back to the right to truncate unneeded information.
        result /= 10.0L;

        // Construct a new object with our result and return it.
        return decimal<PRECISION>(result);
    }

    // Division between this object and a object of the same type.
    decimal<PRECISION> operator/(const decimal<PRECISION> & rhs) const
    {
        // Operate using floating point.  This is valid since the operation
        // is relatively short and the error is removed when the value
        // saved back into a decimal object.  The action of saving to
        // a decimal object will remove error and represent an exact number.
        long double result = (long double) data / (long double) rhs.data;

        // Calculate the +/- sign.
        long double sign = fabs(result) / result;
        if(IsNaN(sign))
        {
            sign = 0.0L;
        }

        // Result value slided to the left for rounding.
        result *= (long double) pow(10.0, (double) (PRECISION + 1));
        result += 5.0L * sign;

        // Slide back to the right to truncate unneeded information.
        result /= 10.0L;

        // Construct a new object with our result and return it.
        return decimal<PRECISION>(result);
    }

    // Addition between this object and another like object.
    decimal<PRECISION> operator+(const decimal<PRECISION> & rhs) const
    {
        // Create a return object and set the data.
        decimal<PRECISION> retObj;
        retObj.SetData(data + rhs.data);
        return retObj;
    }

    // Subtraction between this object and another like object.
    decimal<PRECISION> operator-(const decimal<PRECISION> & rhs) const
    {
        // Create a return object and set the data.
        decimal<PRECISION> retObj;
        retObj.SetData(data - rhs.data);
        return retObj;
    }

    // Equality operator.
    bool operator==(const decimal<PRECISION> & rhs) const
    {
        // Comparing the data member is all that's needed.
        return (rhs.data == data);
    }

    // Inequality operator.
    bool operator!=(const decimal<PRECISION> & rhs) const
    {
        // Comparing the data member is all that's needed.
        return (rhs.data != data);
    }

    // Assignment operator.
    decimal<PRECISION> & operator=(const decimal<PRECISION> & rhs)
    {
        // Set the data and return a reference to ourself.
        SetData(rhs.data);
        return *this;
    }

    // Assignment operator.
    decimal<PRECISION> & operator=(const long double & rhs)
    {
        // Set the data and return a reference to ourself.
        *this = decimal<PRECISION>(rhs);
        return *this;
    }

    // Greater than operator.
    bool operator>(const decimal<PRECISION> & rhs) const
    {
        return data > rhs.data;
    }

    // Less than operator.
    bool operator<(const decimal<PRECISION> & rhs) const
    {
        return data<rhs.data;
    }

    // Conversion operator overload.
    operator long double() const
    {
        return (long double) data / (long double) pow(10.0, (double) PRECISION);
    }

    // Conversion operator overload.
    operator std::string() const
    {
        return this->ToString();
    }

    // String conversion method.
    std::string ToString() const
    {
        // Use a string stream to format the data.
        std::ostringstream localstream;
        localstream << std::setprecision(15) << (long double)(*this);

        return localstream.str();
    }
};
}

#endif
