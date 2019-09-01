#include <iostream>

#include <ql/quantlib.hpp>

using namespace QuantLib;


Real myReciproke(Real x)
{
    QL_REQUIRE(x != 0, "Divided by Zero");
    return 1 / x;
}


void DateTesting1()
{
    Date myDate(12, Aug, 2009);
    std::cout << myDate << std::endl;
    myDate++;
    std::cout << myDate << std::endl;
    myDate += 12 * Days;
    std::cout << myDate << std::endl;
    myDate -= 2 * Months;
    std::cout << myDate << std::endl;
    myDate--;
    std::cout << myDate << std::endl;
    Period myP(10, Weeks);
    myDate += myP;
    std::cout << myDate << std::endl;
}


void DateTesting2()
{
    Date myDate(12, Aug, 2009);
    std::cout << "Original Date:" << myDate << std::endl;
    std::cout << "Weekday:" << myDate.weekday() << std::endl;
    std::cout << "Day of Month:" << myDate.dayOfMonth() << std::endl;
    std::cout << "Day of Year:" << myDate.dayOfYear() << std::endl;
    std::cout << "Month:" << myDate.month() << std::endl;
    int month = myDate.month();
    std::cout << "Month via Integer:" << month << std::endl;
    std::cout << "Year:" << myDate.year() << std::endl;
    int serialNum = myDate.serialNumber();
    std::cout << "Serial Number:" << serialNum << std::endl;
}


void DateTesting3()
{
    std::cout << "Today:" << Date::todaysDate() << std::endl;
    std::cout << "Min Date:" << Date::minDate() << std::endl;
    std::cout << "Max Date:" << Date::maxDate() << std::endl;
    std::cout << "Is Leap:" << Date::isLeap(2011) << std::endl;
    std::cout << "End of Month:" << Date::endOfMonth(Date(4, Aug, 2009)) << std::endl;
    std::cout << "Is Month End:" << Date::isEndOfMonth(Date(29, Sep, 2009)) << std::endl;
    std::cout << "Is Month End:" << Date::isEndOfMonth(Date(30, Sep, 2009)) << std::endl;
    std::cout << "Next WD:" << Date::nextWeekday(Date(1, Sep, 2009), Friday) << std::endl;
    std::cout << "n-th WD:" << Date::nthWeekday(3, Wed, Sep, 2009) << std::endl;
}


void DateTesting4()
{
    Date d = Settings::instance().evaluationDate();
    std::cout << "Eval Date:" << d << std::endl;
    Settings::instance().evaluationDate() = Date(5, Jan, 1995);
    d = Settings::instance().evaluationDate();
    std::cout << "New Eval Date:" << d << std::endl;
}


void CalendarTesting1()
{
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
    Calendar saudiArabCal = SaudiArabia();
    Date nyEve(31, Dec, 2009);
    std::cout << "Is BD:" << frankfCal.isBusinessDay(nyEve) << std::endl;
    std::cout << "Is Holiday:" << frankfCal.isHoliday(nyEve) << std::endl;
    std::cout << "Is Weekend:" << saudiArabCal.isWeekend(Saturday) << std::endl;
    std::cout << "Is Last BD:" << frankfCal.isEndOfMonth(Date(30, Dec, 2009)) << std::endl;
    std::cout << "Last BD:" << frankfCal.endOfMonth(nyEve) << std::endl;
}


int main()
{
    int x = 1;
    int y = 2;

    QL_REQUIRE(x != 0, "Divided by Zero");
    std::cout << y / x << std::endl;

    std::cout << "Current QL Version: " << QL_LIB_VERSION << std::endl;

    std::cout << myReciproke(2.0) << std::endl;

    DateTesting1();
    DateTesting2();
    DateTesting3();
    DateTesting4();

    CalendarTesting1();

    return 0;
}
