/*******************************************************************************

    \file  unit_math.h

    \brief

    \note  C Anilao 01/26/2006 Created.

*******************************************************************************/

#ifndef UNIT_MATH_H
#define UNIT_MATH_H

// General Depedencies.
#include "time.h"
#include "speed.h"
#include "inches.h"
#include "length.h"

namespace numeric
{
/*******************************************************************************

    \brief  Muliplies a speed object with a time object, resulting in a
            length object.

            Kilometers
            ---------- * time = kilometers.
            time

    \return const time & - time object to operate with.

    \note   C Anilao 11/06/2006 Created.

*******************************************************************************/
inline length operator*(const speed & lhs, const time & rhs)
{
    length retObj;
    const double milliSecInASec = 1000.0;

    //  inch         1 second
    // ------- *  ----------------- * elapsed milliseconds = inches traveled.
    // seconds    1000 milliseconds

    // Elapsed milliseconds is from rhs.  GetData() is already in inches
    // per seconds.  time.GetData() is already in milliseconds.
    return inches((double) lhs.GetData() *
                  (1.0 / milliSecInASec) * (double) rhs.GetData());
}

/*******************************************************************************

    \brief  operator overload.

               length
               ------ = speed
                time

    \param  time & - Time object to divide by.

    \return speed - The resulting speed object from the operation.

    \note   C Anilao 11/09/2006 Created.
    \note   C Anilao 11/27/2006 Rewrote calulation so that the number of
                                floating point operations would be reduced.

*******************************************************************************/
inline speed operator/(const length & lhs, const time & rhs)
{
    const double msInOneSec = 1000.0;
    const double coreToInches = CORE_UNITS_TO_ONE_INCH;
    const double coreToOneMS = CORE_UNITS_TO_ONE_MILLISECOND;

    // Execute the conversion and return.  CANNOT use units objects because we
    // are a parent class!  Must be done MANUALLY at this level.  If you do
    // rounding issues will occur!

    // Conversion to a speed object:
    //
    // "this->GetData()" in core_units_length
    // -------------------------------------- = x inches
    //   (254 core_units_length) / (1 inch)
    //
    // "rhs.GetData()" in core_units_time
    // ---------------------------------- = y millisec
    // (1 core_units_time) / (1 millisec)
    //
    //                1 second
    // y millisec * ------------- = z seconds
    //              1000 millisec
    //
    // x inches
    // --------- = x_1 speed
    // z seconds

    double x_inches = (double) lhs.GetData() / coreToInches;
    double y_millisec = (double) rhs.GetData() / coreToOneMS;
    double z_seconds = y_millisec / msInOneSec;
    double x1_inchPerSec = x_inches / z_seconds;

    // x_1 speed is in the core units of speed, so just set it.
    speed retSpeed;
    retSpeed.SetData(x1_inchPerSec);

    // Return a speed object.
    return retSpeed;
}

/*******************************************************************************

    \brief  operator overload.

               length
               ------ = time
                speed

    \param  speed & - Speed object to divide by.

    \return time - The resulting time object from the operation.

    \note   C Anilao 11/09/2006 Created.
    \note   C Anilao 11/27/2006 Rewrote calulation so that the number of
                                floating point operations would be reduced.

*******************************************************************************/
inline time operator/(const length & lhs, const speed & rhs)
{
    const double msInOneSec = 1000.0;
    const double coreToInches = CORE_UNITS_TO_ONE_INCH;
    const double coreToInchPerSec = CORE_UNITS_TO_INCH_PER_SECOND;

    // Execute the conversion and return.  CANNOT use units objects because we
    // are a parent class!  Must be done MANUALLY at this level.  If you do
    // rounding issues will occur!

    // Conversion to a speed object:
    //
    //  "this->GetData()"          1 inch
    //        in          * --------------------- = x inches
    //  core_units_length   254 core_units_length
    //
    //
    // "rhs.GetData()" in core_units_speed      inches
    // -----------------------------------  = y ------
    // core_units_speed / (inch / second)       second
    //
    //   inches       1 second           1               1
    // y ------ * ----------------- * -------- = -----------------
    //   second   1000 milliseconds   x inches    z milliseconds
    //

    double x_inches = (double) lhs.GetData() / coreToInches;
    double y_InchesPerSec = (double) rhs.GetData() / coreToInchPerSec;
    double z_ms = (x_inches * msInOneSec) / y_InchesPerSec;

    // x_1 milliseconds is in the core units of time, so just set it.
    time retTime;
    retTime.SetData(z_ms);

    // Return a speed object.
    return retTime;
}
}

#endif
