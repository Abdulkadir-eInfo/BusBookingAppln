#include <memory>
#include <UnitTest++/UnitTest++.h>
#include "MockReservationClass.h"
using namespace std;

struct TestClass
{
    shared_ptr<MockReservationClass> ptr = make_shared<MockReservationClass>();
    TestClass() { }
    ~TestClass() { }
};

TEST_FIXTURE(TestClass, initBusesTest)
{
    cout << "\nTesting initBuses()" << endl;
    CHECK_EQUAL(ptr->initBuses(), true);
}

TEST_FIXTURE(TestClass, BusListTest)
{
    cout << "\nTesting BusList()" << endl;
    CHECK_EQUAL(ptr->BusList(), 10);
}

TEST_FIXTURE(TestClass, IsUSERPresentTest)
{
    cout << "\nTesting isUserPresent()" << endl;
    CHECK_EQUAL(ptr->isUserPresent("User1"), true);
}

TEST_FIXTURE(TestClass, RegisterUserTest)
{
    cout << "\nTesting RegisterUser()" << endl;
    CHECK_EQUAL(ptr->RegisterUser("1111111111").mobileno, "1111111111");
}

TEST_FIXTURE(TestClass, LoadUserTest)
{
    cout << "\nTesting LoadUser()" << endl;
    CHECK_EQUAL(ptr->RegisterUser("1111111111").mobileno, "1111111111");
}

TEST_FIXTURE(TestClass, IsFemaleReservationTest)
{
    cout << "\nTesting IsFemaleReservation()" << endl;
    CHECK_EQUAL(ptr->IsFemaleReservation("12", "18"), true);
}

TEST_FIXTURE(TestClass, BookTicketTest)
{
    UserDetails user_info;
    user_info.name = "User1";
    cout << "\nTesting BookTicket()" << endl;
    CHECK_EQUAL(ptr->BookTicket(user_info), "202284/010User11");
}

TEST_FIXTURE(TestClass, CancelTicketTest)
{
    cout << "\nTesting CancelTicket()" << endl;
    CHECK_EQUAL(ptr->CancelTicket("User1"), true);
}

TEST_FIXTURE(TestClass, CancelPartialTicketTest)
{
    cout << "\nTesting CancelPartialTicket()" << endl;
    CHECK_EQUAL(ptr->CancelPartialTicket("User1"), true);
}

TEST_FIXTURE(TestClass, ReservationListTest)
{
    cout << "\nTesting ReservationList()" << endl;
    CHECK_EQUAL(ptr->ReservationList(), 0);
}

TEST_FIXTURE(TestClass, ShowCurrentUserBookingsTest)
{
    cout << "\nTesting ShowCurrentUserBookings()" << endl;
    CHECK_EQUAL(ptr->ShowCurrentUserBookings("User1"), true);
}

TEST_FIXTURE(TestClass, ShowUserBookingsTest)
{
    cout << "\nTesting ShowUserBookings()" << endl;
    CHECK_EQUAL(ptr->ShowUserBookings("User1"), true);
}

TEST_FIXTURE(TestClass, SaveUserBookingsToUserFileTest)
{
    ReservationDetails Reserve_info;
    Reserve_info.User_info.mobileno = "1231231234";
    cout << "\nTesting SaveUserBookingstoUserFile()" << endl;
    CHECK_EQUAL(ptr->SaveUserBookingstoUserFile("1231231234", Reserve_info), true);
}

int main(int, char const *[])
{
    return UnitTest::RunAllTests();
}
