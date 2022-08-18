#include <csignal>
#include <memory>
#include "ReservationClass.h"
using namespace std;

// Shared_ptr for ReservationClass that will be automatically destroyed on program termination or end
shared_ptr<ReservationClass> Res_ptr = make_shared<ReservationClass>();

// Signal Handler function that copies all the txt files to database
void signalHandler(int signum)
{
    Res_ptr.reset();
    if (system(NULL)) puts ("Copying files back into database....");
    else exit (EXIT_FAILURE);

    if (system("cp -u ../build/User*.txt ../database/ ") < 0)
    {
        cout << "File Copy Operation for User files  failed" << endl;
    }
    if (system("cp -u ../build/bus*.txt ../database/ ") < 0)
    {
        cout << "File Copy Operation for bus file  failed" << endl;
    }
    if (system("cp -u ../build/Reser*.txt ../database/ ") < 0)
    {
        cout << "File Copy Operation for Reservation file failed" << endl;
    }
    if (signum != SIGUSR1)
        exit(0);
}


// MAIN Driver
int main()
{
    int vendor_user_choice = 1; // run astyle
    cout << "WELCOME";

    // Linking all terminating signals with signal handler that will copy all txt files from the directory to database
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGKILL, signalHandler);
    signal(SIGSTOP, signalHandler);
    signal(SIGTSTP, signalHandler);

    while (vendor_user_choice == 1 || vendor_user_choice == 2)
    {
        cout << "\nContinue as Vendor or User(Press 1 for Vendor, 2 for User, 3 to Quit): ";
        cin >> vendor_user_choice;
        if (vendor_user_choice == 1)
        {

            int vendor_choice = 1, flag = 1, x;
            while (vendor_choice == 1 || vendor_choice == 2 || vendor_choice == 3)
            {
                cout << "\nMENU\n" << "1.Add Bus\n2.View Bus List\n3.View Bookings\n4.Switch TO Main Menu\nEnter your Choice:";
                cin >> vendor_choice;
                Vendorchoice ch = (Vendorchoice)vendor_choice;
                cout << "\n";
                switch (ch)
                {
                    case Vendorchoice::ADDBUS:
                        if (Res_ptr->initBuses())
                        {
                            cout << "Bus Added Successfully" << endl;
                        }
                        break;
                    case Vendorchoice::VIEWBUSLIST:
                        Res_ptr->BusList();
                        break;
                    case Vendorchoice::VIEWBOOKINGS:
                        cout << "Viewing Bookings" << endl;
                        Res_ptr->ReservationList();
                        break;
                    case Vendorchoice::SWITCHTOMAIN:
                        cout << "Switching to Main Menu" << endl;
                        break;
                    default:
                        cout << "Invalid Input" << endl;
                        break;
                }
            }

        }
        if (vendor_user_choice == 2)
        {
            int choice = 1;
            int returnvar = 0;
            char user_choice = 'N';
            string mobile_no;
            UserDetails user_info;
            int user_info_loaded = 0;
            cout << "Are you Already Registered?(Y/N)\nEnter Your Input: ";
            cin >> user_choice;
            user_choice = toupper(user_choice);
            if (user_choice == 'N')
            {
                int register_choice = 2;
                cout << "\n1.Register as User\n2.Switch to Main Menu\nEnter Your Choice: ";
                cin >> register_choice;
                if (register_choice == 1)
                {
                    // Take input from user for user info and store it into a struct : Name, Age, Gender, Mobile No.
                    cout << "Enter your Mobile No.: ";
                    while (true)
                    {
                        cin >> mobile_no;
                        if (mobile_no.length() == 10)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Enter 10 digits valid mobile no: ";
                        }
                    }
                    user_info = Res_ptr->RegisterUser(mobile_no);
                    user_info_loaded = 1;

                }
                else if (register_choice == 2)
                {
                    cout << "Switching to Main Menu" << endl << endl;
                    choice = 7;
                }
                else
                {
                    cout << "Invalid Input" << endl << endl;
                    choice = 7;
                }
            }
            else if (user_choice == 'Y')
            {
                cout << "Enter your Registered Mobile No: " << endl;
                cin >> mobile_no;
                if (!Res_ptr->isUserPresent(mobile_no))
                {
                    cout << "User with given Mobile No. Not Registered" << endl;
                    choice = 7;
                }
                else
                {
                    user_info = Res_ptr->LoadUserDetails(mobile_no);
                    user_info_loaded = 1;
                }
            }
            else
            {
                cout << "Invalid Input" << endl;
                break;
            }
            if (user_info_loaded == 1)
            {
                string id;
                while (choice != 7)
                {
                    cout << "\nMENU\n" << "1.Book Ticket\n2.View Current Bookings for the User\n3.View User Booking History\n4.Cancel Ticket\n5.Cancel Partial Ticket\n6.View Bus List\n7.Switch TO Main Menu\nEnter your Choice:";
                    cin >> choice;
                    Userchoice ch = (Userchoice)choice;
                    cout << "\n";
                    switch (ch)
                    {
                        case Userchoice::BOOKTICKET:
                            id = Res_ptr->BookTicket(user_info);
                            if (id != "0" && id != "SORRY")
                            {
                                cout << "\nBooking succesfull with Ticket ID: " << id << endl;
                            }
                            break;
                        case Userchoice::VIEWBOOKINGS:
                            cout << "Viewing Current Bookings" << endl;
                            Res_ptr->ShowCurrentUserBookings(user_info.mobileno);
                            break;
                        case Userchoice::VIEWUSERBOOKINGS:
                            Res_ptr->ShowUserBookings(user_info.mobileno);
                            break;
                        case Userchoice::CANCELTICKET:
                            if (Res_ptr->CancelTicket(user_info.name))
                            {
                                cout << "Reservation Cancelled Successfully" << endl;
                            }
                            break;
                        case Userchoice::CANCELTICKET2:
                            if (Res_ptr->CancelPartialTicket(user_info.name))
                            {
                                cout << "Reservation Modified Successfully" << endl;
                            }
                            break;
                        case Userchoice::VIEWBUSLIST:
                            Res_ptr->BusList();
                            break;
                        case Userchoice::SWITCHTOMAIN:
                            cout << "Switching to Main Menu" << endl;
                            break;
                        default:
                            break;
                    }
                }

            }

        }
    }
    if (vendor_user_choice == 3)
    {
        cout << "Quitting you out" << endl;
        signalHandler(SIGUSR1);
    }
    if (vendor_user_choice != 1 && vendor_user_choice != 2 && vendor_user_choice != 3)
    {
        cout << "Invalid Choice" << endl;
        signalHandler(SIGUSR1);
    }

    return 0;
}
