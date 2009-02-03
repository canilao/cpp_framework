/*******************************************************************************

    \file   milepace.h

    \brief  Class declaration for a unit of time.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef MILEPACE_H
#define MILEPACE_H

// Standard Library Dependancies.
#include <string>
#include <sstream>

// General Dependancies.
#include "time.h"
#include "minutes.h"
#include "seconds.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for mile pace time.

    \brief  Concrete class for a measurable time unit.

*******************************************************************************/
class milepace : public time
{
public:

    // Constructor.
    milepace();

    // Copy Constructor.
    milepace(const milepace & origMilePace);

    // Base length number constructor.
    milepace(const time & origBaseTime);

    // Destructor.
    virtual ~milepace();

    // Override for string conversion.
    virtual std::string ToString();
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milepace::milepace()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milepace::milepace(const milepace & origSeconds) : time(origSeconds)
{}

/*******************************************************************************

    \brief  Base time constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milepace::milepace(const time & origBaseSeconds) : time(origBaseSeconds)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline milepace::~milepace()
{}

/*******************************************************************************

    \brief  String representation of the data.

    \return string - String representation of this object.

    \note   C Anilao 11/10/2006 Created.

*******************************************************************************/
inline std::string milepace::ToString()
{
    static char charBuff[100];

    // Break down the time into minutes and seconds.
    minutes totalMinutes = (*this);
    seconds totalSeconds = (*this) - minutes(static_cast<int>(totalMinutes));

    // Calculate our string.
    std::ostringstream localstream;

    localstream << std::setw(2) << std::setfill('0');
    localstream << (int) totalMinutes << ':';
    localstream << std::setw(2) << std::setfill('0');
    localstream << (int) totalSeconds; 

    return localstream.str();
}
}

#endif

