#include "UserClass.h"

class MockUserClass: public UserClass
{

    public:
        MockUserClass() = default; // Constructor that transfers all the Users details from the txt file into the Users_map
        ~MockUserClass() = default; // Destructor that Users data from Users_map to the txt files

        virtual UserDetails RegisterUser(std::string) override; // Member function that registers a new user, creates a file for storing bookings for that User
        virtual UserDetails LoadUserDetails(std::string) override; // Member function that loads the user info from txt file and returns the structure

        virtual bool isUserPresent(std::string) override; // Checks whether User Data is present in map or not

        virtual int ReservationList() override; // Virtual function that will be defined in the inherited reservation class
};

bool MockUserClass::isUserPresent(std::string name)
{
    if (name == "User1")
    {
        return true;
    }
    return false;
}

int MockUserClass::ReservationList()
{
    return 0;
}

UserDetails MockUserClass::RegisterUser(std::string mobile_no)
{
    UserDetails obj;
    obj.mobileno = mobile_no;
    return obj;
}

UserDetails MockUserClass::LoadUserDetails(std::string mobile_no)
{
    UserDetails obj;
    obj.mobileno = mobile_no;
    return obj;
}