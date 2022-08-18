#include <memory>
#include <UnitTest++/UnitTest++.h>
#include "MockUserClass.h"
using namespace std;

struct TestClass
{
    shared_ptr<MockUserClass> ptr = make_shared<MockUserClass>();
    TestClass() { }
    ~TestClass() { }
};

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

TEST_FIXTURE(TestClass, ReservationListTest)
{
    cout << "\nTesting ReservationList()" << endl;
    CHECK_EQUAL(ptr->ReservationList(), 0);
}

int main(int, char const *[])
{
    return UnitTest::RunAllTests();
}
