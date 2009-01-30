/*******************************************************************************

    \file   kmpace.h

    \brief  Class declaration for a unit of time.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/

#ifndef KMPACE_H
#define KMPACE_H

// Standard Library Dependancies.
#include <string>

// General Dependancies.
#include "time.h"
#include "minutes.h"
#include "seconds.h"

namespace numeric
{
/*******************************************************************************

    \class  Class for a declaration for kilometer pace time.

    \brief  Concrete class for a measurable time unit.

*******************************************************************************/
class kmpace : public time
{
public:

    // Constructor.
    kmpace();

    // Copy Constructor.
    kmpace(const kmpace & origKmPace);

    // Base length number constructor.
    kmpace(const time & origBaseTime);

    // Destructor.
    virtual ~kmpace();

    // Override for string conversion.
    virtual std::string ToString();
};

/*******************************************************************************

    \brief  Constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kmpace::kmpace()
{}

/*******************************************************************************

    \brief  Copy constructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kmpace::kmpace(const kmpace & origSeconds) : time(origSeconds)
{}

/*******************************************************************************

    \brief  Base time constructor.

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kmpace::kmpace(const time & origBaseSeconds) : time(origBaseSeconds)
{}

/*******************************************************************************

    \brief  Destructor

    \note   C Anilao 11/01/2006 Created.

*******************************************************************************/
inline kmpace::~kmpace()
{}

/*******************************************************************************

    \brief  String representation of the data.

    \return string - String representation of this object.

    \note   C Anilao 11/10/2006 Created.

*******************************************************************************/
inline std::string kmpace::ToString()
{
    static char charBuff[100];

    // Break down the time into minutes and seconds.
    minutes totalMinutes = (*this);
    seconds totalSeconds = (*this) - minutes(static_cast<int>(totalMinutes));

    // Calculate our string.
    sprintf(charBuff, "%02d:%02d", (int) totalMinutes, (int) totalSeconds);
    std::string retStr(charBuff);

    return retStr;
}
}

#endif

