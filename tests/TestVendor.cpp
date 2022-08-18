#include <memory>
#include <UnitTest++/UnitTest++.h>
#include "MockVendorClass.h"
using namespace std;

struct TestClass
{
    shared_ptr<MockVendorClass> ptr = make_shared<MockVendorClass>();
    TestClass() { }
    ~TestClass() { }
};

TEST_FIXTURE(TestClass, AddBusTest)
{
    cout << "\nTesting AddBus()" << endl;
    BusDetails obj;
    obj.no = "1";
    CHECK_EQUAL(ptr->AddBus(obj), true);
}

TEST_FIXTURE(TestClass, OccupySeatTest)
{
    cout << "\nTesting OccupySeat()" << endl;
    CHECK_EQUAL(ptr->OccupySeat(1, 33), false);
}

TEST_FIXTURE(TestClass, CheckSeatTest)
{
    cout << "\nTesting CheckSeat()" << endl;
    CHECK_EQUAL(ptr->CheckSeat(1, 21), true);
}

TEST_FIXTURE(TestClass, FreeSeatTest)
{
    cout << "\nTesting FreeSeat()" << endl;
    CHECK_EQUAL(ptr->FreeSeat(1, 21), true);
}

TEST_FIXTURE(TestClass, BusListTest)
{
    cout << "\nTesting BusList()" << endl;
    CHECK_EQUAL(ptr->BusList(), 10);
}

int main(int, char const *[])
{
    return UnitTest::RunAllTests();
}