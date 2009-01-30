/*******************************************************************************
 
    \file   unitlibrary.h
 
    \brief  Executes a test on the library.
 
    \note   C Anilao 10/23/2006 Created.
 
    \note   C Anilao 11/27/2006 Added test for floors and fps.  Added repetitive 
                                division and multiplication operations to test 
                                that numbers are not degrading over time.  
                                Added test for fpm (floors per minute).  
    
    \note   C Anilao 11/28/2006 Added test for addition and subtraction 
                                operators.  '-=' '+=' and '-' Added assert for 
                                boolean operator for repeatative math test 
                                loops.
 
    \note   N Alcantara 12/05/2006 Added additional tests:  Logic and its 
                                   complement, decimal precision, proximity 
                                   to zero.
 
    \note   C Anilao 12/06/2006 Removed 'int i' declarations in several for 
                                loops.  Microsoft will not compile with this.
 
*******************************************************************************/

#ifndef UNITLIBTEST_H
#define UNITLIBTEST_H

// Standard Library Dependancies.
#include <cmath>
#include <limits>
#include <string>
#include <cassert>

// General Dependancies.
#include "../../numeric.h"

using namespace std;

const double ALMOST_ZERO = 1e-10;

namespace numeric
{
/*******************************************************************************
 
    \class  CUnitLibTest
 
    \brief  Test the library.
 
*******************************************************************************/
template<class unitType, class unitParent>
class CUnitLibTest
{
public:

    // Constructor.
    CUnitLibTest(){};

    // Destructor.
    virtual ~CUnitLibTest(){};

    // Execute Test.
    void Test();
};

/*******************************************************************************
 
    \brief  Test

*******************************************************************************/
template<class unitType, class unitParent>
inline void CUnitLibTest<unitType, unitParent>::Test()
{
    /*** Constructor Tests ***/
    unitType unitWholeNumber = 10;
    assert(static_cast<int>(unitWholeNumber) == 10);
    unitType unitDouble = 10.5;
    assert(fabs(static_cast<double>(unitDouble) - 10.5) < ALMOST_ZERO);
    unitType unitInitOnConstructWhole(25);
    assert(static_cast<int>(unitInitOnConstructWhole) == 25);
    unitType unitConstructDouble(25.5);
    assert(unitConstructDouble == unitType(25.5));

    /*** Assignment Tests ***/
    unitWholeNumber = 1;
    assert(static_cast<int>(unitWholeNumber) == 1);
    unitDouble = 20.1;
    assert(fabs(
               static_cast<double>(unitDouble) -
               static_cast<double>(20.1)) <
           ALMOST_ZERO);
    unitDouble = 20.11;
    assert(fabs(
               static_cast<double>(unitDouble) -
               static_cast<double>(20.11)) <
           ALMOST_ZERO);
    unitDouble = 20.101;
    assert(fabs(static_cast<double>(unitDouble) -
                static_cast<double>(20.101)) < ALMOST_ZERO);
    unitDouble = 20.1009;
    assert(fabs(static_cast<double>(unitDouble) -
                static_cast<double>(20.1009)) < ALMOST_ZERO);

    /*** Comparison Tests ***/
    unitType greater = 10.1009, lesser = 10.1008, equal = 10.1009;

    assert(greater > lesser);
    assert(lesser < greater);
    assert(lesser <= greater);
    assert(greater >= lesser);
    assert(lesser <= lesser);
    assert(greater >= greater);
    assert(lesser != greater);
    assert(equal == greater);

    // Complement
    assert(!(lesser > greater));
    assert(!(greater < lesser));
    assert(!(greater <= lesser));
    assert(!(lesser >= greater));
    assert(!(lesser == greater));
    assert(!(equal != greater));

    /*** String Tests ***/
    unitType unitString1 = 1;
    unitType unitString2 = 20;
    unitType unitString3 = 2.7;
    unitType unitString4 = 30.1;
    unitType unitString5 = 30.11;
    unitType unitString6 = 30.111;
    unitType unitString7 = 30.1111;

    std::string testString1 = unitString1.ToString();
    assert(testString1 == "1");
    std::string testString2 = unitString2.ToString();
    assert(testString2 == "20");
    std::string testString3 = unitString3.ToString();
    assert(testString3 == "2.7");
    std::string testString4 = unitString4.ToString();
    assert(testString4 == "30.1");
    std::string testString5 = unitString5.ToString();
    assert(testString5 == "30.11");
    std::string testString6 = unitString6.ToString();
    assert(testString6 == "30.111");
    std::string testString7 = unitString7.ToString();
    assert(testString7 == "30.1111");

    /*** Zero Tests ***/
    double zero = 0.0;

    // One decimal place
    unitDouble = 17.1;
    zero = (static_cast<double>(unitDouble) - 17.1);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to zero - One decimal places
    int i;
    for (i = 0; i < 171; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.1;
    }
    assert(unitDouble == unitType(0.0));

    // Two decimal places
    unitDouble = 17.11;
    zero = (static_cast<double>(unitDouble) - 17.11);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to zero - Two decimal places
    for (i = 0; i < 1711; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.01;
    }
    assert(unitDouble == unitType(0.0));

    // Three decimal places
    unitDouble = 17.101;
    zero = (static_cast<double>(unitDouble) - 17.101);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to zero - Three decimal places
    for (i = 0; i < 17101; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.001;
    }
    assert(unitDouble == unitType(0.0));

    // Four decimal places
    unitDouble = 1.1009;
    zero = (static_cast<double>(unitDouble) - 1.1009);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to zero - Four decimal places
    for (i = 0; i < 11009; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.0001;
    }
    assert(unitDouble == unitType(0.0));

    /*** Near-Zero Tests ***/
    // One decimal place
    unitDouble = 17.1;
    zero = (static_cast<double>(unitDouble) - 17.1);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to nearly zero - One decimal place
    for (i = 0; i < 170; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.1;
    }
    assert(unitDouble != unitType(0.0));

    // Two decimal places
    unitDouble = 17.11;
    zero = (static_cast<double>(unitDouble) - 17.11);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to nearly zero - Two decimal places
    for (i = 0; i < 1710; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.01;
    }
    assert(unitDouble != unitType(0.0));

    // Three decimal places
    unitDouble = 17.101;
    zero = (static_cast<double>(unitDouble) - 17.101);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to nearly zero - Three decimal places
    for (i = 0; i < 17100; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.001;
    }
    assert(unitDouble != unitType(0.0));

    // Four decimal places
    unitDouble = 17.1009;
    zero = (static_cast<double>(unitDouble) - 17.1009);
    assert(fabs(zero - 0.0) < ALMOST_ZERO);

    // Repetitive subtractions to nearly zero - Four decimal places
    for (i = 0; i < 171008; ++i)
    {
        unitDouble = static_cast<double>(unitDouble) - 0.0001;
    }
    assert(unitDouble != unitType(0.0));

    /*** "To One" Tests ***/
    unitType toOne(0.0), _toOne(0.0);
    for (i = 0; i < 10000; ++i)
    {
        toOne = toOne + unitType(0.0001);
        _toOne += unitType(0.0001);
    }
    assert(toOne == unitType(1.0));
    assert(_toOne == unitType(1.0));

    /*** Addition Tests ***/
    // Whole numbers
    unitType unitAdd1 = 10;
    unitType unitAdd2 = 20;
    unitType unitAddTotal = unitAdd1 + unitAdd2;
    assert(unitAddTotal == unitType(30));

    // One decimal place
    unitAdd1 = 0.1;
    unitAdd2 = 0.1;
    unitAddTotal = unitAdd1 + unitAdd2;
    assert(unitAddTotal == unitType(0.2));

    // Two decimal place
    unitAdd1 = 0.11;
    unitAdd2 = 0.11;
    unitAddTotal = unitAdd1 + unitAdd2;
    assert(unitAddTotal == unitType(0.22));

    // One decimal place
    unitAdd1 = 0.101;
    unitAdd2 = 0.101;
    unitAddTotal = unitAdd1 + unitAdd2;
    assert(unitAddTotal == unitType(0.202));

    // One decimal place
    unitAdd1 = 0.1009;
    unitAdd2 = 0.1009;
    unitAddTotal = unitAdd1 + unitAdd2;
    assert(unitAddTotal == unitType(0.2018));

    /*** Convertion Operator Tests ***/
    unitType conversionOperatorTesting = 100.1009;
    double DoubleConv = conversionOperatorTesting;
    assert(unitType(DoubleConv) == unitType(100.1009));
    unsigned long LongConv = conversionOperatorTesting;
    assert(LongConv == 100);

    // Test for conversion to base class, then back again.
    unitType unitBaseLengthTest = 100.123956789;
    unitParent baseClassConvTest = unitBaseLengthTest;
    std::string baseStringTest1 = baseClassConvTest.ToString();
    unitBaseLengthTest = baseClassConvTest;
    assert(unitBaseLengthTest == baseClassConvTest);
}

/*******************************************************************************
 
    \brief  ExecuteUnitLibraryTest
 
*******************************************************************************/
void ExecuteUnitLibraryTest()
{
    /*** Length Test Suite ***/
    CUnitLibTest<inches, length> inchesTestObj;
    inchesTestObj.Test();
    assert(miles(1) == inches(63360));

    CUnitLibTest<feet, length> feetTestObj;
    feetTestObj.Test();
    assert(feet(1) == inches(12));

    CUnitLibTest<millimeters, length> mmTestObj;
    mmTestObj.Test();
    assert(miles(1) == millimeters(1609344));

    CUnitLibTest<centimeters, length> cmTestObj;
    cmTestObj.Test();
    assert(inches(1) == centimeters(2.54));

    CUnitLibTest<kilometers, length> kmTestObj;
    kmTestObj.Test();
    assert(inches(39370.07874015748) == kilometers(1));

    CUnitLibTest<miles, length> milesTestObj;
    milesTestObj.Test();
    assert(miles(1) == millimeters(1609344));

    /*** Mass Test Suite ***/
    // Test out the mass units.
    CUnitLibTest<pounds, mass> lbsTestObj;
    lbsTestObj.Test();
    assert(pounds(1) == kilograms(0.45359237000));

    CUnitLibTest<kilograms, mass> kgTestObj;
    kgTestObj.Test();
    assert(kilograms(1) == pounds(2.204622622));

    /*** Time Test Suite ***/
    CUnitLibTest<hours, time> hoursTestObj;
    hoursTestObj.Test();
    assert(seconds(1) == hours(2.7777777777777777777777777777778e-4));

    CUnitLibTest<milliseconds, time> msTestObj;
    msTestObj.Test();
    assert(milliseconds(1) == seconds(0.001));

    CUnitLibTest<seconds, time> secTestObj;
    secTestObj.Test();
    assert(seconds(1) == milliseconds(1000));

    CUnitLibTest<minutes, time> minTestObj;
    minTestObj.Test();
    assert(minutes(1) == milliseconds(60000));

    /*** Speed Test Suite ***/
    CUnitLibTest<mph, speed> mphTestObj;
    mphTestObj.Test();
    assert(kph(1.609344) == mph(1));

    length oneMile = mph(1) * minutes(60);
    assert(oneMile == miles(1));

    CUnitLibTest<kph, speed> kphTestObj;
    kphTestObj.Test();
    assert(mph(0.62137119223733) == kph(1));

    /*** Pace Test Suite ***/
    kmpace tenMinKm1 = minutes(10);
    kph sixKmPerHour = tenMinKm1;
    double sixKmPerHourScalar = sixKmPerHour;
    assert(sixKmPerHourScalar == 6.0);
    kmpace tenMinKm2 = sixKmPerHour;
    assert(minutes(10) == tenMinKm2);
    assert(std::string("10:00") == tenMinKm2.ToString());

    milepace tenMinMile1 = minutes(10);
    mph sixMilePerHour = tenMinMile1;
    double sixMilePerHourScalar = sixMilePerHour;
    assert(mph(sixMilePerHourScalar) == mph(6.0));
    milepace tenMinMile2 = sixMilePerHour;
    assert(minutes(10) == tenMinMile2);
    assert(std::string("10:00") == tenMinMile2.ToString());

    // Repetitively execute the division and multiplication operator.
    speed speedDivTest1;
    length lenDivTest1 = miles(1);
    for(int i=0 ; i<1000 ; ++i)
    {
        speedDivTest1 = lenDivTest1 / minutes(60);
        lenDivTest1 = speedDivTest1 * minutes(60);
        assert(lenDivTest1 == miles(1));
        assert(speedDivTest1 == mph(1));
    }

    // Test out the division operator for length, will return a speed object.
    miles divMiles = 1;
    hours divHours = 2;
    speed divSpeed = divMiles / divHours;
    assert(mph(0.5) == mph(divSpeed));

    mph oneMPH = 1;
    time divTime = divMiles / oneMPH;
    assert(hours(1) == hours(divTime));

    /*** Time Struct Test Suite ***/
    time oneOfAllTest = days(1) +
                        hours(1) +
                        minutes(1) +
                        seconds(1) +
                        milliseconds(1);

    timestruct timeStructTest(oneOfAllTest);
    assert(timeStructTest.days_data == 1);
    assert(timeStructTest.hours_data == 1);
    assert(timeStructTest.minutes_data == 1);
    assert(timeStructTest.seconds_data == 1);
    assert(timeStructTest.milliseconds_data == 1);
    assert(timeStructTest.GetTimeObject() == oneOfAllTest);
}
}

#endif
