#include <iostream>

class MockReservationClass
{
    public:
        MockReservationClass() = default;
        ~MockReservationClass() = default;
        virtual std::string BookTicket(std::string); // Book a ticket for User
        virtual bool CancelTicket(std::string); // Cancel the whole ticket

        virtual int BusList();  // Show all the buses from the bus_map
        virtual int ReservationList(); // Displays all the reservation in the system
        virtual bool ShowCurrentUserBookings(std::string); // Show current bookings made by the User

};

std::string MockReservationClass::BookTicket(std::string name)
{
    return "202284/010" + name + "1";
}

bool MockReservationClass::CancelTicket(std::string name)
{
    if (name == "User1")
        return true;
    else
        return false;
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
        return true;
    else
        return false;
}