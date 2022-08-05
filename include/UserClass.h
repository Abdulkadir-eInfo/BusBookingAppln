#include <iostream>
#include <map>
#include <vector>

#ifndef USERCLASS_H
#define USERCLASS_H


#pragma pack(push, 1)
struct UserDetails
{
    std::string name;
    std::string idtype;
    int age;
    std::string gender;
    std::string mobileno;
    int tickets_booked=0;
};
#pragma pack(pop) //back to whatever the previous packing mode was


enum class Userchoice
{
    BOOKTICKET=1,
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
    UserDetails getUserDetails(std::string);
    void initUsers(); // Init Users map from Users.txt
    void SaveToUsersFile(); // Save from Users map to Users.txt

    public:
    UserClass(); // Constructor that transfers all the Users details from the txt file into the Users_map
    ~UserClass(); // Destructor that Users data from Users_map to the txt files

    virtual UserDetails RegisterUser(std::string)=0; // Member function that registers a new user, creates a file for storing bookings for that User
    virtual UserDetails LoadUserDetails(std::string)=0; // Member function that loads the user info from txt file and returns the structure

    virtual bool isUserPresent(std::string)=0; // Checks whether User Data is present in map or not
    
    std::map<std::string,struct UserDetails > Users_map; // Map of User Mobile No.to struct UserDetails
    
    virtual int ReservationList()=0; // Virtual function that will be defined in the inherited reservation class
    
};

#endif