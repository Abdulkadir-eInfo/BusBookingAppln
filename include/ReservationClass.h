#ifndef RESERVATIONCLASS_H
#define RESERVATIONCLASS_H

#include <iostream>
#include "UserClass.h"
#include "VendorClass.h"

#pragma pack(push, 1)
struct ReservationDetails
{
    UserDetails User_info;
    int busno;
    std::string vendor;
    std::string boarding_point;
    std::string dropoff_point;
    std::string booking_date;
    std::string booking_time;
    int seatcount;
    std::vector<std::string> seats_booked;
    std::string ticket_id;
    int ticket_cost;
};
#pragma pack(pop) //back to whatever the previous packing mode was

class ReservationClass: private UserClass, private VendorClass
{
    private:
        time_t t = time(0);
        tm *now = localtime(&t);
        std::string tid = std::to_string(now->tm_year + 1900) + std::to_string(now->tm_mon + 1) + std::to_string(now->tm_mday) + "/";
        void SaveReservationToFile(); // Function that saves reservation data to the txt file
        int ReservationCount(); // Returns count of the Reserved tickets
        std::string timeConversion(std::string); // Converts time from 10:00AM format to 24-hour format 10:00

    public:
        ReservationClass(); // Constructor that loads all the Current Reservations from the txt file into the Reserve Map
        ~ReservationClass(); // Destructor that Saves the reservatiosn from the Reserve map into the txt file
        std::map<std::string, ReservationDetails> Reserve; // Map that maps ticketid with the ReservationDetails struct

        virtual bool initBuses(); // Takes input from the user and calls the addbus() of the parent class
        virtual int BusList() override;  // Show all the buses from the bus_map
        virtual int ReservationList() override; // Displays all the reservation in the system
        virtual bool ShowCurrentUserBookings(std::string); // Show current bookings made by the User

        virtual UserDetails RegisterUser(std::string) override; // Member function that registers a new user, creates a file for storing bookings for that User
        virtual UserDetails LoadUserDetails(std::string) override; // Member function that loads the user info from txt file and returns the structure
        virtual bool isUserPresent(std::string) override; // Checks whether User Data is present in map or not

        virtual bool SaveUserBookingstoUserFile(std::string, ReservationDetails); // Save Bookings details of users into seperate txt file and return status of saving

        virtual bool IsFemaleReservation(std::string, std::string); // Checks whether the current time is 2 hours before the departure time; if satisfies Female_Reservation is On and returns true

        virtual std::string BookTicket(UserDetails); // Book a ticket for User
        virtual bool CancelTicket(std::string); // Cancel the whole ticket
        virtual bool CancelPartialTicket(std::string); // Cancel only few seats from the reservation

        virtual bool ShowUserBookings(std::string); // Shows all bookings made by a User

};

#endif