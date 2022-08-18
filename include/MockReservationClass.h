#include "ReservationClass.h"

class MockReservationClass: public ReservationClass
{
    public:
        MockReservationClass() = default;
        ~MockReservationClass() = default;
        virtual bool IsFemaleReservation(std::string, std::string) override; // Checks whether the current time is 2 hours before the departure time; if satisfies Female_Reservation is On and returns true
        virtual std::string BookTicket(UserDetails) override; // Book a ticket for User
        virtual bool CancelTicket(std::string) override; // Cancel the whole ticket
        virtual bool CancelPartialTicket(std::string); // Cancel only few seats from the reservation

        virtual bool initBuses() override; // Takes input from the user and calls the addbus() of the parent class
        virtual int BusList() override;  // Show all the buses from the bus_map
        virtual int ReservationList() override; // Displays all the reservation in the system
        virtual bool ShowCurrentUserBookings(std::string) override; // Show current bookings made by the User
        virtual bool ShowUserBookings(std::string) override; // Shows all bookings made by a User

        virtual UserDetails RegisterUser(std::string) override; // Member function that registers a new user, creates a file for storing bookings for that User
        virtual UserDetails LoadUserDetails(std::string) override; // Member function that loads the user info from txt file and returns the structure
        virtual bool isUserPresent(std::string) override; // Checks whether User Data is present in map or not

        virtual bool SaveUserBookingstoUserFile(std::string, ReservationDetails) override; // Save Bookings details of users into seperate txt file and return status of saving

};

bool MockReservationClass::IsFemaleReservation(std::string current_time, std::string departure_time)
{
    int dTime = std::stoi(departure_time.c_str());
    int cTime = std::stoi(current_time.c_str());
    if (cTime + 2 < dTime)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string MockReservationClass::BookTicket(UserDetails user_info)
{
    return "202284/010" + user_info.name + "1";
}

bool MockReservationClass::CancelTicket(std::string name)
{
    if (name == "User1")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MockReservationClass::CancelPartialTicket(std::string name)
{
    if (name == "User1")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MockReservationClass::initBuses()
{
    return true;
}

int MockReservationClass::BusList()
{
    return 10;
}

int MockReservationClass::ReservationList()
{
    return 0;
}

bool MockReservationClass::ShowCurrentUserBookings(std::string name)
{
    if (name == "User1")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MockReservationClass::ShowUserBookings(std::string name)
{
    if (name == "User1")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MockReservationClass::isUserPresent(std::string name)
{
    if (name == "User1")
    {
        return true;
    }
    return false;
}

UserDetails MockReservationClass::RegisterUser(std::string mobile_no)
{
    UserDetails obj;
    obj.mobileno = mobile_no;
    return obj;
}

UserDetails MockReservationClass::LoadUserDetails(std::string mobile_no)
{
    UserDetails obj;
    obj.mobileno = mobile_no;
    return obj;
}

bool MockReservationClass::SaveUserBookingstoUserFile(std::string mobile_no, ReservationDetails Reservation_info)
{
    if (mobile_no == Reservation_info.User_info.mobileno)
    {
        return true;
    }
    return false;
}