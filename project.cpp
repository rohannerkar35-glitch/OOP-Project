#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Reservation
{
    int ticketNo;
    int age;
    float price;
    string name;
    string gender;
    string source;
    string destination;

public:

    // Book Ticket
    void bookTicket()
    {
        try
        {
            ofstream file("tickets.txt", ios::app);

            cout << "\nEnter Ticket Number: ";
            cin >> ticketNo;

            if(cin.fail())
                throw "Ticket Number must be numeric!";

            if(ticketNo <= 0)
                throw "Ticket Number must be positive!";

            cin.ignore();

            cout << "Enter Passenger Name: ";
            getline(cin, name);

            cout << "Enter Age: ";
            cin >> age;

            if(cin.fail())
                throw "Age must be numeric!";

            if(age < 0 || age > 120)
                throw "Invalid Age!";

            cin.ignore();

            cout << "Enter Gender (Male/Female): ";
            getline(cin, gender);

            if(gender != "Male" && gender != "male" &&
               gender != "Female" && gender != "female")
            {
                throw "Invalid Gender! Enter Male or Female.";
            }

            cout << "Enter Source: ";
            getline(cin, source);

            cout << "Enter Destination: ";
            getline(cin, destination);

            if(source == destination)
                throw "Source and Destination cannot be same!";

            // Base Fare
            price = 250;

            // Female Discount
            if(gender == "Female" || gender == "female")
            {
                price = price - (price * 0.50);
                cout << "\n50% Female Discount Applied!";
            }

            // Senior Citizen Discount
            if(age >= 60)
            {
                price = price - (price * 0.75);
                cout << "\n75% Senior Citizen Discount Applied!";
            }

            file << ticketNo << endl;
            file << name << endl;
            file << age << endl;
            file << gender << endl;
            file << source << endl;
            file << destination << endl;
            file << price << endl;

            file.close();

            cout << "\n\nTicket Booked Successfully!";
            cout << "\nFinal Ticket Price: Rs. " << price << endl;
        }
        catch(const char *msg)
        {
            cout << "\nError: " << msg << endl;

            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // View Tickets
    void viewTickets()
    {
        ifstream file("tickets.txt");

        if(!file)
        {
            cout << "\nNo Records Found!\n";
            return;
        }

        cout << "\n========== ALL RESERVATIONS ==========\n";

        while(file >> ticketNo)
        {
            file.ignore();

            getline(file, name);

            file >> age;
            file.ignore();

            getline(file, gender);
            getline(file, source);
            getline(file, destination);

            file >> price;
            file.ignore();

            cout << "\nTicket Number : " << ticketNo;
            cout << "\nPassenger Name: " << name;
            cout << "\nAge           : " << age;
            cout << "\nGender        : " << gender;
            cout << "\nSource        : " << source;
            cout << "\nDestination   : " << destination;
            cout << "\nTicket Price  : Rs. " << price;
            cout << "\n--------------------------------------\n";
        }

        file.close();
    }

    // Search Ticket
    void searchTicket()
    {
        int searchNo;
        bool found = false;

        try
        {
            cout << "\nEnter Ticket Number to Search: ";
            cin >> searchNo;

            if(cin.fail())
                throw "Ticket Number must be numeric!";

            ifstream file("tickets.txt");

            while(file >> ticketNo)
            {
                file.ignore();

                getline(file, name);

                file >> age;
                file.ignore();

                getline(file, gender);
                getline(file, source);
                getline(file, destination);

                file >> price;
                file.ignore();

                if(ticketNo == searchNo)
                {
                    cout << "\nTicket Found!\n";

                    cout << "Ticket Number : " << ticketNo << endl;
                    cout << "Passenger Name: " << name << endl;
                    cout << "Age           : " << age << endl;
                    cout << "Gender        : " << gender << endl;
                    cout << "Source        : " << source << endl;
                    cout << "Destination   : " << destination << endl;
                    cout << "Ticket Price  : Rs. " << price << endl;

                    found = true;
                    break;
                }
            }

            if(!found)
            {
                cout << "\nTicket Not Found!\n";
            }

            file.close();
        }
        catch(const char *msg)
        {
            cout << "\nError: " << msg << endl;

            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // Cancel Ticket
    void cancelTicket()
    {
        int cancelNo;
        bool found = false;

        try
        {
            cout << "\nEnter Ticket Number to Cancel: ";
            cin >> cancelNo;

            if(cin.fail())
                throw "Ticket Number must be numeric!";

            ifstream file("tickets.txt");
            ofstream temp("temp.txt");

            while(file >> ticketNo)
            {
                file.ignore();

                getline(file, name);

                file >> age;
                file.ignore();

                getline(file, gender);
                getline(file, source);
                getline(file, destination);

                file >> price;
                file.ignore();

                if(ticketNo == cancelNo)
                {
                    found = true;
                }
                else
                {
                    temp << ticketNo << endl;
                    temp << name << endl;
                    temp << age << endl;
                    temp << gender << endl;
                    temp << source << endl;
                    temp << destination << endl;
                    temp << price << endl;
                }
            }

            file.close();
            temp.close();

            remove("tickets.txt");
            rename("temp.txt", "tickets.txt");

            if(found)
            {
                cout << "\nTicket Cancelled Successfully!\n";
            }
            else
            {
                cout << "\nTicket Not Found!\n";
            }
        }
        catch(const char *msg)
        {
            cout << "\nError: " << msg << endl;

            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
};

int main()
{
    Reservation r;
    int choice;

    do
    {
        try
        {
            cout << "\n\n========== ONLINE TICKET RESERVATION SYSTEM ==========\n";
            cout << "1. Book Ticket\n";
            cout << "2. View All Tickets\n";
            cout << "3. Search Ticket\n";
            cout << "4. Cancel Ticket\n";
            cout << "5. Exit\n";

            cout << "\nEnter Your Choice: ";
            cin >> choice;

            if(cin.fail())
                throw "Choice must be numeric!";

            if(choice < 1 || choice > 5)
                throw "Please enter a valid choice (1-5)!";

            switch(choice)
            {
                case 1:
                    r.bookTicket();
                    break;

                case 2:
                    r.viewTickets();
                    break;

                case 3:
                    r.searchTicket();
                    break;

                case 4:
                    r.cancelTicket();
                    break;

                case 5:
                    cout << "\nThank You for Using the Reservation System!\n";
                    break;
            }
        }
        catch(const char *msg)
        {
            cout << "\nError: " << msg << endl;

            cin.clear();
            cin.ignore(1000, '\n');
        }

    } while(choice != 5);

    return 0;
}
