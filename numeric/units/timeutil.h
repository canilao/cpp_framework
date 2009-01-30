/****************************************************************************************
 *
 *   \file      timeutil.h
 *
 *   \brief     Header that contains time related utilities.
 *
 *   \history
 *      - C Anilao      10/22/2006
 *        Created.
 *
 ***************************************************************************************/

#ifndef TIMEUTIL_H
#define TIMEUTIL_H

// General Dependancies.
#include "days.h"
#include "time.h"
#include "hours.h"
#include "minutes.h"
#include "seconds.h"
#include "milliseconds.h"

namespace numeric
{

/******************************************************************************
 *
 *   \brief  Stucture that is used to hold time in a way that is readable.
 *
 *****************************************************************************/
struct timestruct
{
    // Constructor.
    timestruct()
    {
        days_data = 0;
        hours_data = 0;
        minutes_data = 0;
        seconds_data = 0;
        milliseconds_data = 0;
    }

    // Constructor.
    timestruct(const time & origTime)
    {
        // Convert to a time structure.
        ConvertToTimeStruct(origTime);
    }

    // Copy constructor.
    timestruct(const timestruct & origStruct)
    {
        // Just memcpy our data over.
        memcpy((void *) this, (void *) &origStruct, sizeof(timestruct));
    }

    /*****************************************************************************************
     *
     *   \brief     Converts a time object and turns breaks it down into this structure.
     *
     ***************************************************************************************/
    void ConvertToTimeStruct(const time & origTime)
    {
        // Sequentially add data to the structure.
        days_data = days(origTime);
        hours_data = hours(origTime - days(days_data));
        minutes_data = minutes(origTime - days(days_data) - hours(hours_data));
        seconds_data = seconds(origTime -
                               days(days_data) -
                               hours(hours_data) -
                               minutes(minutes_data));
        milliseconds_data = milliseconds(origTime -
                                         days(days_data) -
                                         hours(hours_data) -
                                         minutes(minutes_data) -
                                         seconds(seconds_data));
    }

    /*****************************************************************************************
     *
     *   \brief     This structure to a time object.
     *
     ***************************************************************************************/
    time GetTimeObject()
    {
        // Add up our data.
        return (days(days_data) +
                hours(hours_data) +
                minutes(minutes_data) +
                seconds(seconds_data) +
                milliseconds(milliseconds_data));
    }

    /*****************************************************************************************
     *
     *   \brief     Assignment operator.
     *
     ***************************************************************************************/
    timestruct operator=(const timestruct & rhs)
    {
        // Just memcpy our data over.
        memcpy((void *) this, (void *) &rhs, sizeof(timestruct));

        return (*this);
    }

    // Number of whole number days.
    unsigned long days_data;

    // Number of whole number hours.
    unsigned long hours_data;

    // Number of whole number minutes.
    unsigned long minutes_data;

    // Number of whole number seconds.
    unsigned long seconds_data;

    // Number of whole number milliseconds.
    unsigned long milliseconds_data;
};

}

#endif
