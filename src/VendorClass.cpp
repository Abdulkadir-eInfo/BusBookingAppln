#include <fstream>
#include <exception>
#include "VendorClass.h"
using namespace std;

// Constructor that transfers all the bus details from the txt file into the bus_map
VendorClass::VendorClass()
{
    // Initializing the bus_map that we will be using for all the operations
    string bus_no, points_count, buspoint_name, reservation_count, reserved_seat;
    ifstream file_read;

    try
    {
        file_read.open("busdetails.txt", ios::in);
        if (!file_read)
        {
            ofstream file_write;
            file_write.open("busdetails.txt", ios::out);
            file_write.close();
        }
        // loop will run until we get line copied into the string i.e. until we reach last line
        while ( getline(file_read, bus_no, '\t') )
        {
            // Getting details of each bus from the file into the structure
            struct BusDetails bus;
            bus.no = bus_no;
            getline(file_read, bus.vendor_name, '\t');
            getline(file_read, bus.from, '\t');
            getline(file_read, bus.to, '\t');
            getline(file_read, bus.departure, '\t');
            getline(file_read, bus.arrival, '\t');
            getline(file_read, points_count, '\t');
            bus.buspoints_count = stoi(points_count); // Error is here
            for (int i = 0; i < bus.buspoints_count; i++)
            {
                getline(file_read, buspoint_name, '\t');
                bus.buspoint[i + 1] = buspoint_name;
            }
            getline(file_read, reservation_count, '\t');
            bus.count = stoi(reservation_count);
            for (int i = 0; i < bus.count; i++)
            {
                getline(file_read, reserved_seat, '\t');
                bus.seats[stoi(reserved_seat)] = true;
            }
            int bno = stoi(bus.no);
            // Inserting the individual busdetails structure mapped to the bus_no into bus_map
            bus_map.insert(pair<int, struct BusDetails>(bno, bus));
        }
    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file";
    }
    file_read.close();
}

// Destructor that writes all the bus details from the bus_map into the txt file
VendorClass::~VendorClass()
{
    SaveBusDataToFile();
}

// Function for adding buses by the vendor
bool VendorClass::AddBus(BusDetails obj)
{
    int bno = stoi(obj.no);
    bus_map.insert(pair<int, struct BusDetails>(bno, obj));
    return true;
}

// Occupying seat in the bus
bool VendorClass::OccupySeat(int busno, int seatno)
{
    for (auto &bus_info_ptr : bus_map)
    {
        if (bus_info_ptr.first == busno)
        {
            bus_info_ptr.second.count++;
            bus_info_ptr.second.seats[seatno] = true;
            return true;
        }
    }
    return false;
}

// Freeing up a seat in the bus
bool VendorClass::FreeSeat(int busno, int seatno)
{
    for (auto &bus_info_ptr : bus_map)
    {
        if (bus_info_ptr.first == busno)
        {
            // If bus_no matches, reduce the count of reserved seats by 1 and free up the provided seatno by marking it as not booked
            bus_info_ptr.second.count--;
            bus_info_ptr.second.seats[seatno] = false;
            return true;
        }
    }
    return false;
}

// Checking whether the seat is booked or not
bool VendorClass::CheckSeat(int busno, int seatno)
{
    for (auto bus_info_ptr : bus_map)
    {
        if (bus_info_ptr.first == busno)
        {
            // If provided seatno is true(means the seat is already reserved); return false that is we can't book it now; or else return true
            if (bus_info_ptr.second.seats[seatno])
                return false;
            else
                break;
        }
    }
    return true;

}

// Function that saves bus data to the txt file
void VendorClass::SaveBusDataToFile()
{
    if (!bus_map.empty())
    {
        ofstream file_write;
        try
        {
            // Open file and overwrite it
            file_write.open("busdetails.txt", ios::out);
            BusDetails bus;
            // Write individual busdetails from the bus_map into the txt file.
            for (auto bus_info_ptr : bus_map)
            {
                file_write << bus_info_ptr.second.no << "\t" << bus_info_ptr.second.vendor_name << "\t" << bus_info_ptr.second.from << "\t" << bus_info_ptr.second.to << "\t" << bus_info_ptr.second.departure << "\t" << bus_info_ptr.second.arrival << "\t" << bus_info_ptr.second.buspoints_count << "\t";
                for (int i = 0; i < bus_info_ptr.second.buspoints_count; i++)
                {
                    file_write << bus_info_ptr.second.buspoint[i + 1] << "\t";
                }
                file_write << bus_info_ptr.second.count << "\t";
                for (int i = 1; i <= BUSSEATSIZE; i++)
                {
                    if (bus_info_ptr.second.seats[i])
                        file_write << i << "\t";
                }
            }

        }
        catch (const ofstream::failure &e)
        {
            cout << "Exception opening/reading file";
        }
        file_write.close();
    }
}