#include "VendorClass.h"

class MockVendorClass: public VendorClass
{
    public:
        MockVendorClass() = default; // Constructor that transfers all the bus details from the txt file into the bus_map
        ~MockVendorClass() = default; // Destructor that writes all the bus details from the bus_map into the txt file

        virtual bool AddBus(BusDetails obj) override; // Function for adding buses by the vendor

        virtual bool OccupySeat(int, int) override; // Occupying seat in the bus
        virtual bool FreeSeat(int, int) override; // Freeing up a seat in the bus
        virtual bool CheckSeat(int, int) override; // Checking whether the seat is booked or not

        virtual int BusList() override; // Virtual function that will be defined in the inherited reservation class
};


bool MockVendorClass::AddBus(BusDetails obj)
{
    if (obj.no == "1")
    {
        return true;
    }
    return false;
}

bool MockVendorClass::OccupySeat(int bus_no, int seat_no)
{
    if (bus_no == 1)
    {
        if (seat_no > 0 && seat_no < 33)
        {
            return true;
        }
    }
    return false;
}

bool MockVendorClass::FreeSeat(int bus_no, int seat_no)
{
    if (bus_no == 1)
    {
        if (seat_no == 21)
        {
            return true;
        }
    }
    return false;
}

bool MockVendorClass::CheckSeat(int bus_no, int seat_no)
{
    if (bus_no == 1)
    {
        if (seat_no == 21)
        {
            return true;
        }
    }
    return false;
}

int MockVendorClass::BusList()
{
    return 10;
}

