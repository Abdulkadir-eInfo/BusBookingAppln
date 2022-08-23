#ifndef USERCLASS_H
#define USERCLASS_H

#include <iostream>
#include <map>
#include <vector>

#pragma pack(push, 1)
struct UserDetails
{
    std::string name;
    std::string idtype;
    int age;
    std::string gender;
    std::string mobileno;
    int tickets_booked = 0;
};
#pragma pack(pop) //back to whatever the previous packing mode was

enum class Userchoice
{
    BOOKTICKET = 1,
    VIEWBOOKINGS,
    VIEWUSERBOOKINGS,
    CANCELTICKET,
    CANCELTICKET2,
    VIEWBUSLIST,
    SWITCHTOMAIN

};

class UserClass
{
    private:
        void initUsers(); // Init Users map from Users.txt
        void SaveToUsersFile(); // Save from Users map to Users.txt

    public:
        UserClass(); // Constructor that transfers all the Users details from the txt file into the Users_map
        ~UserClass(); // Destructor that Users data from Users_map to the txt files

        virtual UserDetails getUserDetails(std::string);

        virtual UserDetails RegisterUser(std::string) = 0; // Pure Virtual function that will be defined in the inherited reservation class
        virtual UserDetails LoadUserDetails(std::string) = 0; // Pure Virtual function that will be defined in the inherited reservation class
        virtual bool isUserPresent(std::string) = 0; // Pure Checks whether User Data is present in map or not

        std::map<std::string, UserDetails > Users_map; // Map of User Mobile No.to struct UserDetails

        virtual int ReservationList() = 0; // Pure Virtual function that will be defined in the inherited reservation class

};

#endif