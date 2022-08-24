#include <fstream>
#include <exception>
#include <algorithm>
#include "ReservationClass.h"
using namespace std;

// Constructor that loads all the Current Reservations from the txt file into the Reserve Map
ReservationClass::ReservationClass()
{
    ifstream file_read;
    string res_count, temp;
    try
    {
        file_read.open("Reservations.txt", ios::in);
        if (!file_read)
        {
            ofstream file_write;
            file_write.open("Reservations.txt", ios::out);
            file_write << 0;
            file_write.close();
        }
        else
        {
            getline(file_read, res_count, '\t');
            int count = stoi(res_count);
            if (count != 0)
            {
                // For no. of reservations run the loop and get individual reservation details
                for (int i = 0; i < count; i++)
                {
                    ReservationDetails obj;
                    getline(file_read, temp, '\t');
                    obj.busno = stoi(temp);
                    getline(file_read, obj.vendor, '\t');
                    getline(file_read, obj.ticket_id, '\t');
                    getline(file_read, obj.User_info.idtype, '\t');
                    getline(file_read, obj.User_info.name, '\t');
                    getline(file_read, temp, '\t');
                    obj.User_info.age = stoi(temp);
                    getline(file_read, obj.User_info.gender, '\t');
                    getline(file_read, obj.User_info.mobileno, '\t');
                    getline(file_read, obj.boarding_point, '\t');
                    getline(file_read, obj.dropoff_point, '\t');
                    getline(file_read, obj.booking_date, '\t');
                    getline(file_read, obj.booking_time, '\t');
                    getline(file_read, temp, '\t');
                    obj.seatcount = stoi(temp);
                    for (int i = 0; i < obj.seatcount; i++)
                    {
                        getline(file_read, temp, '\t');
                        obj.seats_booked.push_back(temp);
                    }
                    getline(file_read, temp, '\t');
                    obj.ticket_cost = stoi(temp);
                    // Insert the reservation detail mapped with the ticket_id of reservation into Reserve map
                    Reserve.insert(pair<string, ReservationDetails>(obj.ticket_id, obj));
                }
            }
        }

    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file";
    }
    file_read.close();

}

// Destructor that Saves the reservatiosn from the Reserve map into the txt file
ReservationClass::~ReservationClass()
{
    SaveReservationToFile();
}

// Takes input from the user and calls the addbus() of the parent class
bool ReservationClass::initBuses()
{
    // Get details for new bus that we need to add
    cout << "Adding Bus Details" << endl;
    BusDetails bus_obj;
    cout << "Enter Vendor Name: ";
    cin >> bus_obj.vendor_name;
    cout << "Enter Bus No: ";
    cin >> bus_obj.no;

    auto bus_map_iterator = bus_map.find(stoi(bus_obj.no));
    if (bus_map_iterator != bus_map.end())
    {
        cout << "Bus with provided No already present\n";
        return false;
    }
    cout << "Enter Starting Point: ";
    cin >> bus_obj.from;
    cout << "Enter End Point: ";
    cin >> bus_obj.to;
    cout << "Enter Departure Time(ex. 10:00AM): ";
    cin >> bus_obj.departure;
    cout << "Enter Arrival time(at end point): ";
    cin >> bus_obj.arrival;
    cout << "Enter No. of Bus Points(count in int): ";
    cin >> bus_obj.buspoints_count;
    cout << "For Bus No: " << bus_obj.no << ", Enter Buspoints locations(" << bus_obj.buspoints_count << " only ): ";
    string buspoint_name;
    for (int i = 0; i < bus_obj.buspoints_count; i++)
    {
        cin >> buspoint_name;
        bus_obj.buspoint[i + 1] = buspoint_name;
    }
    // Calling the Addbus from the VendorClass that inserts the busdetails into the bus_map
    AddBus(bus_obj);
    return true;
}

// Show all the buses from the bus_map and returns the size of the bus_map
int ReservationClass::BusList()
{
    // For all pairs in the bus_map, print the details of the buses
    for (auto bus_info : bus_map)
    {
        cout << "\nBus No: " << bus_info.second.no << "\t\tVendor: " << bus_info.second.vendor_name << "\nFrom: " << bus_info.second.from << "\t\tTo:" << bus_info.second.to << "\nDeparture: " << bus_info.second.departure << "\tArrival: " << bus_info.second.arrival << "\nBusPoints: " << bus_info.second.buspoints_count << "\n";
        for (int i = 0; i < bus_info.second.buspoints_count; i++)
        {
            cout <<  i + 1 << " : " << bus_info.second.buspoint[i + 1] << "\n";
        }
        cout << "Seats Booked(" << bus_info.second.count << "): \n";
        for (int i = 1; i <= BUSSEATSIZE; i++)
        {
            if (bus_info.second.seats[i])
            {
                cout << i << " , ";
            }
        }
        cout << "\n";
    }
    return bus_map.size();
}

// Displays all the reservation in the system
int ReservationClass::ReservationList()
{
    if (Reserve.size() == 0)
    {
        cout << "No Bookings present" << endl;
        return 0;
    }
    for (auto Reserve_info : Reserve)
    {
        cout << "\nBus No: " << Reserve_info.second.busno <<  "\tVendor: " << Reserve_info.second.vendor << "\nTicket Id: " << Reserve_info.second.ticket_id << "\nName: " << Reserve_info.second.User_info.name << "\tMobile No: " << Reserve_info.second.User_info.mobileno << "\nIDType: " << Reserve_info.second.User_info.idtype << "\tGender: " << Reserve_info.second.User_info.gender << "\tAge: " << Reserve_info.second.User_info.age << endl;
        cout << "Boarding: " << Reserve_info.second.boarding_point << "\t\tDropoff: " << Reserve_info.second.dropoff_point << "\nBooking Date: " << Reserve_info.second.booking_date << "\t\tBooking Time: " << Reserve_info.second.booking_time ;
        cout << "\nNo. of Seats Booked: " << Reserve_info.second.seatcount << " (";
        for (auto Reserve_iterator : Reserve_info.second.seats_booked)
        {
            cout << Reserve_iterator << " ";
        }
        cout << ")\nTicket Fare: " << Reserve_info.second.ticket_cost << endl;
    }
    return Reserve.size();
}


// Returns count of the Reserved tickets
int ReservationClass::ReservationCount()
{
    return Reserve.size();
}

// Function that saves reservation data to the txt file
void ReservationClass::SaveReservationToFile()
{
    if (Reserve.empty() == false)
    {
        ofstream file_write;
        try
        {
            // Open Reservations.txt to overwrite it updated data from the Reserve map
            file_write.open("Reservations.txt", ios::out);
            file_write << ReservationCount() << "\t";
            // Write each reservation details in the file
            for (auto Reserve_info : Reserve)
            {
                file_write << Reserve_info.second.busno << "\t" << Reserve_info.second.vendor << "\t" << Reserve_info.second.ticket_id << "\t" << Reserve_info.second.User_info.idtype << "\t"  << Reserve_info.second.User_info.name << "\t" << Reserve_info.second.User_info.age << "\t" << Reserve_info.second.User_info.gender << "\t" << Reserve_info.second.User_info.mobileno;
                file_write << "\t" << Reserve_info.second.boarding_point << "\t" << Reserve_info.second.dropoff_point << "\t" << Reserve_info.second.booking_date << "\t" << Reserve_info.second.booking_time << "\t" << Reserve_info.second.seatcount << "\t";
                for (auto Reserve_iterator : Reserve_info.second.seats_booked)
                {
                    file_write << Reserve_iterator << "\t";
                }
                file_write << Reserve_info.second.ticket_cost << "\t";
            }

        }
        catch (const ofstream::failure &e)
        {
            cout << "Exception opening/reading file";
        }
        file_write.close();
    }
    else
    {
        ofstream file_write;
        file_write.open("Reservations.txt", ios::out);
        file_write << ReservationCount() << "\t";
        file_write.close();
    }
}

// Save Bookings details of 5 users into seperate txt file and return status of saving
bool ReservationClass::SaveUserBookingstoUserFile(string mobile_no, ReservationDetails User_info)
{
    string filename;
    auto User_iterator = Users_map.find(mobile_no);
    filename = "User_" + mobile_no + ".txt";
    ofstream file_write;
    try
    {
        // Open file for appending to it
        file_write.open(filename, ios::app);
        if (!file_write)
        {
            cout << "Could not open/access the User File" << endl;
            return false;
        }
        // Write the details of the Reservation into the Userfile
        file_write << User_info.busno << "\t" << User_info.vendor << "\t" << User_info.ticket_id;
        file_write << "\t" << User_info.boarding_point << "\t" << User_info.dropoff_point << "\t" << User_info.booking_date << "\t" << User_info.booking_time;
        file_write << "\t" << User_info.seatcount << "\t";
        for (auto Reserve_iterator : User_info.seats_booked)
        {
            file_write << Reserve_iterator << "\t";
        }
        file_write << User_info.ticket_cost << "\t";
        User_iterator->second.tickets_booked++;

    }
    catch (const ofstream::failure &e)
    {
        cout << "Exception opening/reading file" << endl;
    }
    file_write.close();
    return true;
}

// Member function that registers a new user, creates a file for storing bookings for that User
UserDetails ReservationClass::RegisterUser(string mobile_no)
{
    // Get details of User for registration
    UserDetails User_info;
    char gender;
    User_info.mobileno = mobile_no;
    cout << "Enter Your Name(must comply with your IDtype): ";
    getline(cin >> ws, User_info.name);
    cout << "Enter ID proof(Aadhar/Voter/Driving): ";
    getline(cin >> ws, User_info.idtype);
    cout << "Enter Age: ";
    cin >> User_info.age;
    cout << "Enter Gender(M or F): ";
    while (true)
    {
        cin >> User_info.gender;
        gender = toupper(User_info.gender[0]);
        if (User_info.gender.length() > 1)
        {
            cout << "Enter only 1 character(M or F): " << endl;
            continue;
        }
        if (gender != 'F' && gender != 'M')
        {
            cout << "Enter Appropirate gender(M or F): " << endl;
            continue;
        }
        else
        {
            break;
        }
    }
    User_info.gender = gender;
    User_info.tickets_booked = 0;
    string filename = "User_" + User_info.mobileno + ".txt";
    // Create a file with User_mobileno.txt format and write the User details into it
    ofstream user_file_write;
    try
    {
        user_file_write.open(filename, ios::out);
        user_file_write << User_info.mobileno << "\t" << User_info.name << "\t" << User_info.idtype << "\t" << User_info.age << "\t" << User_info.gender << "\t";
    }
    catch (const ofstream::failure &e)
    {
        cout << "Exception opening/reading file" << endl;
    }
    user_file_write.close();

    Users_map[mobile_no] = User_info;
    return User_info;
}

// Member function that loads the user info from txt file and returns the structure
UserDetails ReservationClass::LoadUserDetails(string mobile_no)
{
    UserDetails user_info = getUserDetails(mobile_no);
    auto User_iterator = Users_map.find(mobile_no);
    user_info.tickets_booked = User_iterator->second.tickets_booked;

    return user_info;
}

// Checks whether User Data is present in map or not
bool ReservationClass::isUserPresent(string mobile_no)
{
    // Find User with provided mobile_no is present or not
    auto User_iterator = Users_map.find(mobile_no);
    if (User_iterator == Users_map.end())
    {
        return false;
    }
    return true;

}

// Converts time from 10:00AM format to 24-hour format 10:00
string ReservationClass::timeConversion(string s)
{
    string hour = s.substr(0, 2);
    string id = s.substr(5, 2);
    int iHour = stoi(hour.c_str());

    if ( id == "PM" )
    {
        if ( iHour != 12 )
        {
            iHour += 12;
        }
        hour = to_string(iHour);
    }

    if ( id == "AM" )
    {
        if ( iHour == 12 )
        {
            hour = "24";
        }
        else if ( iHour < 10 )
        {
            hour = "0" + to_string(iHour);
        }
        else
        {
            hour = to_string(iHour);
        }
    }

    return hour + s.substr(2, 3);
}

// Checks whether the current time is 2 hours before the departure time; if satisfies Female_Reservation is On and returns true
bool ReservationClass::IsFemaleReservation(string current_time, string departure_time)
{
    string dep_time = timeConversion(departure_time);
    string cur_time = current_time.substr(0, 5);

    string dep_h = dep_time.substr(0, 2);
    string cur_h = cur_time.substr(0, 2);
    int dHour = stoi(dep_h.c_str());
    int cHour = stoi(cur_h.c_str());

    string dep_m = dep_time.substr(3, 2);
    string cur_m = cur_time.substr(3, 2);
    int dMin = stoi(dep_m.c_str());
    int cMin = stoi(cur_m.c_str());

    if (dHour > cHour + 2)
    {
        return true;
    }
    else if (dHour = cHour + 2)
    {
        if (dMin > cMin)
        {
            return true;
        }
    }
    return false;
}

// Book a ticket for User, returns ticket id of the booked ticket
string ReservationClass::BookTicket(UserDetails User_info)
{
    bool is_Female = false;
    // Set is_Female flag appropriately from the User's gender detail
    if (User_info.gender == "F")
    {
        is_Female = true;
    }
    time_t t = time(0);
    tm *now = localtime(&t);

    ReservationDetails passenger_obj;
    passenger_obj.User_info = User_info;
    string seatno;
    int matched_buses = 0, boarding_point_found_flag;
    cout << "Booking Tickets for Passenger" << endl;
    cout << "From location: ";
    getline(cin >> ws, passenger_obj.boarding_point);
    cout << "To location: ";
    getline(cin >> ws, passenger_obj.dropoff_point);

    for (auto bus_info : bus_map)
    {
        boarding_point_found_flag = 0;
        for (int x = 1; x <= bus_info.second.buspoints_count; x++)
        {
            if (bus_info.second.buspoint[x] == passenger_obj.boarding_point)
            {
                boarding_point_found_flag = 1;
                continue;
            }
            // Print out the bus details where the from and to location entered by User matches the buspoints
            if (bus_info.second.buspoint[x] == passenger_obj.dropoff_point && boarding_point_found_flag)
            {
                matched_buses++;
                if(matched_buses==1)
                {
                    cout << "Following buses routes matches your boarding/dropoff point:" << endl;
                }
                cout << "\nBus No: " << bus_info.second.no << "\t\tVendor: " << bus_info.second.vendor_name << "\nFrom: " << bus_info.second.from << "\t\tTo:" << bus_info.second.to << "\nDeparture: " << bus_info.second.departure << "\tArrival: " << bus_info.second.arrival << "\nBusPoints: " << bus_info.second.buspoints_count << "\n";
                for (int i = 0; i < bus_info.second.buspoints_count; i++)
                {
                    cout <<  i + 1 << " : " << bus_info.second.buspoint[i + 1] << "\n";
                }
                cout << "Seats Booked(" << bus_info.second.count << "): \n";
                for (int i = 1; i <= BUSSEATSIZE; i++)
                {
                    if (bus_info.second.seats[i])
                    {
                        cout << i << " , ";
                    }
                }
                cout << "\n";
                break;
            }

        }
    }

    if (matched_buses != 0)
    {
        cout << "\nEnter Bus No (from above shown buses): ";
        cin >> passenger_obj.busno;
        auto bus_map_iterator = bus_map.find(passenger_obj.busno);
        if (bus_map_iterator == bus_map.end())
        {
            cout << "Bus with provided No. not available\n";
            return "SORRY";
        }

        // Get the boarding point and dropoff point no from the available list of buspoints for the selected bus
        int boa_no = 1, dro_no = 2;
        auto bus_info2 = bus_map.begin();
        for (bus_info2; bus_info2 != bus_map.end(); bus_info2++)
        {
            if (bus_info2->first == passenger_obj.busno)
            {
                for (int i = 0; i < bus_info2->second.buspoints_count; i++)
                {
                    if (bus_info2->second.buspoint[i + 1] == passenger_obj.boarding_point)
                    {
                        boa_no = i + 1;
                    }
                    if (bus_info2->second.buspoint[i + 1] == passenger_obj.dropoff_point)
                    {
                        dro_no = i + 1;
                    }
                }
                break;
            }
        }

        // Display fare for one ticket based on points chosen by User for the journey in the selected bus
        cout << "\nFare for one ticket in Bus No." << bus_info2->first << " for selected journey will be " << (dro_no - boa_no) * 100 << endl;

        passenger_obj.vendor = bus_info2->second.vendor_name;
        passenger_obj.booking_time = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
        // Get the status whether Female Reservation is applicable or not
        bool is_Female_Reservation = IsFemaleReservation(passenger_obj.booking_time, bus_info2->second.departure);

        if (is_Female_Reservation)
        {
            cout << "\nSeat No. 1 to 8 is allocated for Females" << endl;
            if (!is_Female)
            {
                cout << "These seats if not reserved by Females until 2 hours before start of the bus, gets open to reserve for all" << endl;
            }
        }

        cout << "Seats already Reserved in Bus No. " << bus_info2->first << " (" << bus_info2->second.count << "): \n";
        for (int i = 1; i <= BUSSEATSIZE; i++)
        {
            if (bus_info2->second.seats[i])
            {
                cout << i << " , ";
            }
        }

        cout << "\nHow many seats you want to book: ";
        cin >> passenger_obj.seatcount;

        // Abort booking if User tries to book 0 number of seats
        if ((int)passenger_obj.seatcount <= 0)
        {
            cout << "You choose to reserve 0 seats, aborting the current booking" << endl;
            return "0";
        }
        cout << "Enter seatnos you want to book(1 to 32):";
        int count = passenger_obj.seatcount;
        for (int i = 0; i < count; i++)
        {
            cin >> seatno;
            if (stoi(seatno) > 0 && stoi(seatno) <= BUSSEATSIZE)
            {
                // Check whether the passenger is male and while female reservation is applicable; is he trying to book seats between 1 to 8
                if (is_Female_Reservation && !is_Female && stoi(seatno) > 0 && stoi(seatno) <= 8)
                {
                    cout << "Seat No 1 to 8 are allocated to Females, Choose from Remaining Seats" << endl;
                    count++;
                }
                // Check whether the input seatno is available or not
                else if (CheckSeat(passenger_obj.busno, stoi(seatno)))
                {
                    // If seatno is available push into the seats_booked vector and Occupy that seat in the bus
                    passenger_obj.seats_booked.push_back(seatno);
                    OccupySeat(passenger_obj.busno, stoi(seatno));
                }
                else
                {
                    cout << "Seat " << seatno << " Already Booked" << endl;
                    count++;
                }
            }
            else
            {
                cout << "Enter Valid Seat No(1 to 32): ";
                count++;
            }
        }
        // Determine the cost of ticket using from and to location and number of seats
        passenger_obj.ticket_cost = (passenger_obj.seatcount) * ((dro_no - boa_no) * 100);

        // Generate Ticket_id using today's date appended with bus_no, User_name, and a seat_no
        passenger_obj.ticket_id = tid + "0" + to_string(passenger_obj.busno) + passenger_obj.User_info.name + seatno;
        passenger_obj.booking_date = to_string(now->tm_year + 1900) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_mday);
        passenger_obj.booking_time = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
        // Insert the Ticket_id, Reservationdetails pair into the Reserve map
        Reserve.insert(pair<string, ReservationDetails>(passenger_obj.ticket_id, passenger_obj));
        cout << "Your ticket is booked, your fare is: " << passenger_obj.ticket_cost << ", Plz pay the fare via UPI or Cash" << endl;
        // Update the Userfile that maintains the User Bookings history
        SaveUserBookingstoUserFile(User_info.mobileno, passenger_obj);
        return passenger_obj.ticket_id;
    }
    else
    {
        cout << "\nNo matching buses found" << endl;
        return "SORRY";
    }
    return "0";
}

// Cancel the whole ticket, returns status of cancellation
bool ReservationClass::CancelTicket(string name)
{
    cout << "Cancelling Ticket" << endl;
    int bus_no;
    int flag = 0, confirm = 0;
    string uname;
    cout << "Enter Bus No: ";
    cin >> bus_no;
    cout << "Enter Name(as on Reserved ticket): ";
    cin >> uname;
    // If User enter's name different than that in his profile, don't allow cancelling
    // Name in the Reservation is directly fetched from the profile, so it can't be different if user is trying to cancel own's ticket
    if (uname != name)
    {
        cout << "You are not allowed to Cancel another User's Ticket" << endl;
        return false;
    }

    for (auto Reserve_info = Reserve.begin(); Reserve_info != Reserve.end(); ++Reserve_info)
    {
        // Find the reservation with entered details in the reserve map
        if (Reserve_info->second.busno == bus_no && Reserve_info->second.User_info.name == uname)
        {
            cout << "\nFollowing Reservation will be cancelled:\n";
            cout << "Bus No: " << Reserve_info->second.busno << "\tVendor: " << Reserve_info->second.vendor << "\nTicket Id: " << Reserve_info->second.ticket_id << "\nName: " << Reserve_info->second.User_info.name << "\tMobile No: " << Reserve_info->second.User_info.mobileno << "\nIDType: " << Reserve_info->second.User_info.idtype << "\tAge: " << Reserve_info->second.User_info.age << "\tGender: " << Reserve_info->second.User_info.gender << endl;
            cout << "Boarding: " << Reserve_info->second.boarding_point << "\tDropoff: " << Reserve_info->second.dropoff_point << "\nBooking Date: " << Reserve_info->second.booking_date << "\t\tBooking Time: " << Reserve_info->second.booking_time ;
            cout << "\nNo. of Seats Booked: " << Reserve_info->second.seatcount << " (";
            for (auto Reserve_iterator : Reserve_info->second.seats_booked)
            {
                cout << Reserve_iterator << " ";
            }
            cout << ")\nTicket Fare: " << Reserve_info->second.ticket_cost << endl;

            cout << "DO you really want to Cancel(Press 1 to confirm or 0 to abort): ";
            cin >> confirm;
            if (confirm == 0)
            {
                cout << "Reservation Cancellation Aborted" << endl;
                return false;
            }

            // Freeing up the reserved seats from the bus
            for (auto Reserve_iterator : Reserve_info->second.seats_booked)
            {
                FreeSeat(Reserve_info->second.busno, stoi(Reserve_iterator));
            }

            Reserve.erase(Reserve_info->second.ticket_id);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "No Ticket with entered details present" << endl;
        return false;
    }
    return true;
}

// Cancel only few seats from the reservation
bool ReservationClass::CancelPartialTicket(string name)
{
    cout << "Cancelling Partial Ticket" << endl;
    int bus_no, cancel_seat_count, tickets_cancelled, one_ticket_fare;
    int flag = 0;
    string uname, cancel_seatno;
    cout << "Enter Bus No: ";
    cin >> bus_no;
    cout << "Enter Name(as on Reserved ticket): ";
    cin >> uname;
    // If User enter's name different than that in his profile, don't allow cancelling
    // Name in the Reservation is directly fetched from the profile, so it can't be different if user is trying to cancel own's ticket
    if (uname != name)
    {
        cout << "You are not allowed to Cancel another User's Ticket" << endl;
        return false;
    }

    for (auto Reserve_info = Reserve.begin(); Reserve_info != Reserve.end(); ++Reserve_info)
    {
        // Find the reservation with entered details in the reserve map
        if (Reserve_info->second.busno == bus_no && Reserve_info->second.User_info.name == uname)
        {
            flag = 1;
            cout << "\nFollowing Reservation will be cancelled:\n";
            cout << "Bus No: " << Reserve_info->second.busno << "\tVendor: " << Reserve_info->second.vendor << "\nTicket Id: " << Reserve_info->second.ticket_id << "\nName: " << Reserve_info->second.User_info.name << "\tMobile No: " << Reserve_info->second.User_info.mobileno << "\nIDType: " << Reserve_info->second.User_info.idtype << "\tAge: " << Reserve_info->second.User_info.age << "\tGender: " << Reserve_info->second.User_info.gender << endl;
            cout << "Boarding: " << Reserve_info->second.boarding_point << "\tDropoff: " << Reserve_info->second.dropoff_point << "\nBooking Date: " << Reserve_info->second.booking_date << "\t\tBooking Time: " << Reserve_info->second.booking_time ;
            cout << "\nNo. of Seats Booked: " << Reserve_info->second.seatcount << " (";
            for (auto Reserve_iterator : Reserve_info->second.seats_booked)
            {
                cout << Reserve_iterator << " ";
            }
            cout << ")\nTicket Fare: " << Reserve_info->second.ticket_cost << endl;

            // How many seats from the reserved seat count, user want to cancel
            cout << "Enter the no. of seats you want to cancel from the " << Reserve_info->second.seats_booked.size() << " reserved seats (50% of the fare will be deducted even if you cancel a ticket now): ";
            cin >> cancel_seat_count;
            one_ticket_fare = (Reserve_info->second.ticket_cost / Reserve_info->second.seatcount);
            tickets_cancelled = 0;
            if (cancel_seat_count < Reserve_info->second.seatcount)
            {
                for (int j = 0; j < cancel_seat_count; j++)
                {
                    cout << "Enter the seatno for cancellation: ";
                    cin >> cancel_seatno;
                    // Check whether entered seatno is present in seats_booked
                    auto Reserve_iterator = find(Reserve_info->second.seats_booked.begin(), Reserve_info->second.seats_booked.end(), cancel_seatno);
                    if (Reserve_iterator == Reserve_info->second.seats_booked.end())
                    {
                        cout << cancel_seatno << " is not reserved in this ticket" << endl;
                        cancel_seat_count++;
                    }
                    else
                    {
                        // If present, free up the seat and remove that seatno from the seats_booked vector
                        FreeSeat(Reserve_info->second.busno, stoi(cancel_seatno));
                        Reserve_info->second.seats_booked.erase(Reserve_iterator);
                        Reserve_info->second.seatcount--;
                        tickets_cancelled++;
                    }
                }
                if (Reserve_info->second.seatcount == 0)
                {
                    cout << "All reserved tickets have been cancelled, hence the whole reservation is cancelled" << endl;
                    Reserve.erase(Reserve_info->second.ticket_id);
                    return false;
                }
                flag = 1;
                Reserve_info->second.ticket_cost = ((one_ticket_fare * Reserve_info->second.seatcount) + (tickets_cancelled * (one_ticket_fare / 2)));
                cout << "Revised Ticket fare: " << Reserve_info->second.ticket_cost << endl;
                break;
            }
            else if (cancel_seat_count == Reserve_info->second.seatcount)
            {
                cout << "You entered cancel seat count equalling to reserved seat, Use Cancel whole ticket feature" << endl;
                return false;
            }
            else
            {
                cout << "Invalid input; Can't cancel seats greater than reserved seats" << endl;
                return false;
            }
        }
    }
    if (flag == 0)
    {
        cout << "No Ticket with entered details present" << endl;
        return false;
    }
    return true;
}

// Shows all booking history made by a User
bool ReservationClass::ShowUserBookings(string mobile_no)
{
    ifstream file_read;
    string temp, filename;
    // Check whether mobile_no is present in Registered User's data i.e. in Users_map
    auto User_iterator = Users_map.find(mobile_no);
    if (User_iterator == Users_map.end())
    {
        cout << "Booking Data for Given User not found" << endl;
        return false;
    }
    filename = "User_" + User_iterator->first + ".txt";
    try
    {
        file_read.open(filename, ios::in);
        if (!file_read)
        {
            cout << "Could not Open/Access the User File" << endl;
            return false;
        }
        // Read from the Userfile and display the UserDetails and Reservations made by the User
        cout << "Showing Booking History for " << endl;

        UserDetails user_info;
        getline(file_read, user_info.mobileno, '\t');
        getline(file_read, user_info.name, '\t');
        getline(file_read, user_info.idtype, '\t');
        getline(file_read, temp, '\t');
        user_info.age = stoi(temp);
        getline(file_read, user_info.gender, '\t');
        user_info.tickets_booked = User_iterator->second.tickets_booked;

        cout << "Name: " << user_info.name << "\t Mobile No: " << user_info.mobileno << endl;
        cout << "IDType: " << user_info.idtype << "\tAge: " << user_info.age << "\tGender: " << user_info.gender << endl;
        cout << "No. of Bookings present: " << user_info.tickets_booked << endl << endl;

        for (int i = 0; i < user_info.tickets_booked; i++)
        {
            ReservationDetails obj;
            obj.User_info = user_info;
            getline(file_read, temp, '\t');
            obj.busno = stoi(temp);
            getline(file_read, obj.vendor, '\t');
            getline(file_read, obj.ticket_id, '\t');
            getline(file_read, obj.boarding_point, '\t');
            getline(file_read, obj.dropoff_point, '\t');
            getline(file_read, obj.booking_date, '\t');
            getline(file_read, obj.booking_time, '\t');
            getline(file_read, temp, '\t');
            obj.seatcount = stoi(temp);
            for (int i = 0; i < obj.seatcount; i++)
            {
                getline(file_read, temp, '\t');
                obj.seats_booked.push_back(temp);
            }
            getline(file_read, temp, '\t');
            obj.ticket_cost = stoi(temp);

            cout  << "\nBus No: " << obj.busno << "\tVendor: " << obj.vendor << "\nTicket Id: " << obj.ticket_id  << endl;
            cout << "Boarding: " << obj.boarding_point << "\t\tDropoff: " << obj.dropoff_point << "\nBooking Date: " << obj.booking_date << "\t\tBooking Time: " << obj.booking_time;
            cout << "\nNo. of Seats Booked: " << obj.seatcount << " (";
            for (auto Reserve_iterator : obj.seats_booked)
            {
                cout << Reserve_iterator << " ";
            }
            cout << ")\nTicket Fare: " << obj.ticket_cost << endl;
        }
    }
    catch (const ofstream::failure &e)
    {
        cout << "Exception opening/reading file" << endl;
    }
    file_read.close();
    return true;
}

// Shows current bookings made by the User
bool ReservationClass::ShowCurrentUserBookings(string mobile_no)
{
    if (Reserve.size() == 0)
    {
        cout << "\nNo Bookings present" << endl;
        return 0;
    }
    // Iterate through the Reserve loop
    for (auto Reserve_info : Reserve)
    {
        // Print out the Reservation Details only if the mobile_no matches
        if (Reserve_info.second.User_info.mobileno == mobile_no)
        {
            cout << "\nBus No: " << Reserve_info.second.busno <<  "\tVendor: " << Reserve_info.second.vendor <<  "\nTicket Id: " << Reserve_info.second.ticket_id << "\nName: " << Reserve_info.second.User_info.name << "\tMobile No: " << Reserve_info.second.User_info.mobileno << "\nIDType: " << Reserve_info.second.User_info.idtype << "\tGender: " << Reserve_info.second.User_info.gender << "\tAge: " << Reserve_info.second.User_info.age << endl;
            cout << "Boarding: " << Reserve_info.second.boarding_point << "\t\tDropoff: " << Reserve_info.second.dropoff_point << "\nBooking Date: " << Reserve_info.second.booking_date << "\t\tBooking Time: " << Reserve_info.second.booking_time ;
            cout << "\nNo. of Seats Booked: " << Reserve_info.second.seatcount << " (";
            for (auto Reserve_iterator : Reserve_info.second.seats_booked)
            {
                cout << Reserve_iterator << " ";
            }
            cout << ")\nTicket Fare: " << Reserve_info.second.ticket_cost << endl << endl;
        }

    }
    return true;
}