#include <fstream>
#include <exception>
#include "UserClass.h"
using namespace std;

// Constructor that transfers all the Users details from the txt file into the Users_map
UserClass::UserClass()
{
    initUsers();
}

// Destructor that Users data from Users_map to the txt files
UserClass::~UserClass()
{
    SaveToUsersFile();
}


// Using mobile_no, reads from the corresponding User file and return the structure with all the User Details
UserDetails UserClass::getUserDetails(string mobile_no)
{
    UserDetails user_info;
    // Filename will be created of Format User_mobileno.txt
    string filename = "User_" + mobile_no + ".txt";
    ifstream file_read;
    string temp;

    // Reading details of User from respective Userfile
    try
    {
        file_read.open(filename, ios::in);
        getline(file_read, user_info.mobileno, '\t');
        getline(file_read, user_info.name, '\t');
        getline(file_read, user_info.idtype, '\t');
        getline(file_read, temp, '\t');
        user_info.age = stoi(temp);
        getline(file_read, user_info.gender, '\t');
    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file" << endl;
    }
    file_read.close();

    return user_info;

}

// Init Users map from Users.txt
void UserClass::initUsers()
{
    string Users_count, User_mobileno, User_booking_count;
    int User_count = 0;
    ifstream file_read;

    try
    {
        file_read.open("Users.txt", ios::in);
        if (!file_read)
        {
            ofstream file_write;
            file_write.open("Users.txt", ios::out);
            file_write << 0 << "\t";
            file_write.close();
        }
        else
        {
            getline(file_read, Users_count, '\t');
            User_count = stoi(Users_count);
            if (User_count > 0)
            {
                // For each User_count get mobile_no and booking count from the Users.txt file, open respective Userfile and get the User_info and insert into map
                for (int i = 0; i < User_count; i++)
                {
                    getline(file_read, User_mobileno, '\t');
                    getline(file_read, User_booking_count, '\t');

                    UserDetails user_info = getUserDetails(User_mobileno);
                    user_info.tickets_booked = stoi(User_booking_count);
                    // Inserting UserDetails into the map
                    Users_map[User_mobileno] = user_info;
                }
            }
        }
    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file" << endl;
    }
    file_read.close();

}

// Save from Users map to Users.txt
void UserClass::SaveToUsersFile()
{
    ofstream file_write;
    try
    {
        file_write.open("Users.txt", ios::out);
        file_write << Users_map.size() << "\t";
        // Write each User mobileno and bookings done by the User in the Users.txt file
        for (auto User_info : Users_map)
        {
            file_write << User_info.first << "\t" << User_info.second.tickets_booked << "\t";
        }
    }
    catch (const ofstream::failure &e)
    {
        cout << "Exception opening/reading file" << endl;
    }

    file_write.close();
}

