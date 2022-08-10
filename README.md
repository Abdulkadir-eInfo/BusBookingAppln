# Bus Booking Application

### Bus Booking Application that deploys various concepts of C++.
###### Tried to enhance and add many features to it.

### * Various Features are:
#### -> For Vendor
#####     - Add Buses
#####       - View Bus List
#####       - View current Bookings
####  -> For Users
#####      - Register as User (Only registered Users are able to see main menu for Users)
#####      - Book Ticket by entering From and To location
#####      - Few Seats are allocated that can be booked by Females only; these seats gets open to book for all before specified time e.x. 2 hours before departure of b
#####      - View Current Bookings made by a User
#####      - View all Bookings made by the User(a record of all the bookings made by the User is maintained)
#####      - Cancel Ticket
#####      - Modify Ticket/ Cancel Partial Ticket
#####      - Cancel Ticket and Cancel Partial Ticket are allowed only on Tickets made by the User; User cannot access all the Current Bookings
#####      - View Bus List(Seats are occupied/ freed as per the booking and cancellation made by the User)
    
###  -> We are Using files that keeps record of Buses, Reservations, Users, Users_Reservations that allows us to make an application that is datawise consistent i.e. at the program end/ termination all data gets copied into the files and at the starting of application all the data is loaded from these files into various Templates libraries and Structures.

###  -> Concepts that were used in the development:
#####    - STL(maps); File Operations; Structures; enum Class; Virtual functions; CMake implmentations
#####    - Inheritance; CMake; Signal handling; Unittest++; Mock Classes; Astyle formatting and many more
