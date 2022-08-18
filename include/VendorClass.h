#ifndef VENDORCLASS_H
#define BUSSEATSIZE 32
#define VENDORCLASS_H

#include <iostream>
#include <map>

#pragma pack(push, 1)
struct BusDetails
{
    std::string vendor_name;
    std::string no;
    std::string from;
    std::string to;
    std::string departure;
    std::string arrival;
    int buspoints_count;
    std::map<int, std::string> buspoint;
    int count = 0;
    bool seats[BUSSEATSIZE + 1] = {false};
};
#pragma pack(pop) //back to whatever the previous packing mode was

enum class Vendorchoice
{
    ADDBUS = 1,
    VIEWBUSLIST,
    VIEWBOOKINGS,
    SWITCHTOMAIN
};

class VendorClass
{
    private:
        void SaveBusDataToFile(); // Function that saves bus data to the txt file

    public:
        VendorClass(); // Constructor that transfers all the bus details from the txt file into the bus_map
        ~VendorClass(); // Destructor that writes all the bus details from the bus_map into the txt file

        std::map<int, BusDetails> bus_map; // Map that maps busno with the busdetails struct
        virtual bool AddBus(BusDetails obj); // Function for adding buses by the vendor

        virtual bool OccupySeat(int, int); // Occupying seat in the bus
        virtual bool FreeSeat(int, int); // Freeing up a seat in the bus
        virtual bool CheckSeat(int, int); // Checking whether the seat is booked or not

        virtual int BusList() = 0; // Pure Virtual function that will be defined in the inherited reservation class

};

#endif