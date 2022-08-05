#include <fstream>
#include <exception>
#include "VendorClass.h"
using namespace std;

// Constructor that transfers all the bus details from the txt file into the bus_map
VendorClass::VendorClass()
{
    string bus_no,points_count,buspoint_name,reservation_count,reserved_seat;
    struct BusDetails bus1;
    ifstream file_read;
    
    try
    {
        file_read.open("busdetails.txt",ios::in);
        if(!file_read)
        {
            ofstream file_write;
            file_write.open("busdetails.txt",ios::out);
            file_write.close();
        }
        /** loop will run until we get line copied into the string i.e. until we reach last line */
        while ( getline(file_read,bus1.no,'\t') )
        {
            struct BusDetails bus;
            bus.no=bus1.no;
            getline(file_read,bus.from,'\t');
            getline(file_read,bus.to,'\t');
            getline(file_read,bus.departure,'\t');
            getline(file_read,bus.arrival,'\t');
            getline(file_read,points_count,'\t');
            bus.buspoints_count=stoi(points_count);// Error is here
            for (int i=0;i<bus.buspoints_count;i++) 
            { 
                getline(file_read,buspoint_name,'\t');
                bus.buspoint[i+1]=buspoint_name;
            }
            getline(file_read,reservation_count,'\t');
            bus.count=stoi(reservation_count);
            for(int i=0;i<bus.count;i++)
            {
                getline(file_read,reserved_seat,'\t');
                bus.seats[stoi(reserved_seat)]=true;
            }
            int bno=stoi(bus.no);
            bus_map.insert(pair<int,struct BusDetails>(bno,bus));
        }
    }
    catch(const ifstream::failure& e)
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
void VendorClass::AddBus(BusDetails obj)
{
    int bno=stoi(obj.no);
    bus_map.insert(pair<int,struct BusDetails>(bno,obj));
}

// Occupying seat in the bus
void VendorClass::OccupySeat(int busno, int seatno)
{
    for (auto &bus_info_ptr:bus_map)
    {
        if(bus_info_ptr.first==busno)
        {
            bus_info_ptr.second.count++;
            bus_info_ptr.second.seats[seatno]=true;
        }
    }
}

// Freeing up a seat in the bus
void VendorClass::FreeSeat(int busno,int seatno)
{
    for (auto &bus_info_ptr:bus_map)
    {
        if(bus_info_ptr.first==busno)
        {
            bus_info_ptr.second.count--;
            bus_info_ptr.second.seats[seatno]=false;
        }
    }
}

// Checking whether the seat is booked or not
bool VendorClass::CheckSeat(int busno, int seatno)
{
    for (auto bus_info_ptr:bus_map)
    {
        if(bus_info_ptr.first==busno)
        {
            if(bus_info_ptr.second.seats[seatno])
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
    if(!bus_map.empty())
    {
        ofstream file_write;
        try
        {
            file_write.open("busdetails.txt",ios::out);
            BusDetails bus;
            for (auto bus_info_ptr:bus_map)
            {
                file_write << bus_info_ptr.second.no << "\t" << bus_info_ptr.second.from << "\t" << bus_info_ptr.second.to << "\t" << bus_info_ptr.second.departure << "\t" << bus_info_ptr.second.arrival << "\t" << bus_info_ptr.second.buspoints_count << "\t";
                for(int i=0;i<bus_info_ptr.second.buspoints_count;i++)
                {
                    file_write << bus_info_ptr.second.buspoint[i+1] << "\t";
                }
                file_write << bus_info_ptr.second.count << "\t";
                for(int i=1;i<=BUSSEATSIZE;i++)
                {
                    if(bus_info_ptr.second.seats[i])
                        file_write << i << "\t";
                }
            }
            
        }
        catch(const ofstream::failure& e)
        {
            cout << "Exception opening/reading file";
        }
        file_write.close();
    }
}