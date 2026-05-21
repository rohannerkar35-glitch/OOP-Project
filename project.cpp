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
        ofstream file("tickets.txt", ios::app);

        cout << "\nEnter Ticket Number: ";
        cin >> ticketNo;

        cin.ignore();

        cout << "Enter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Gender (Male/Female): ";
        getline(cin, gender);

        cout << "Enter Source: ";
        getline(cin, source);

        cout << "Enter Destination: ";
        getline(cin, destination);

        // Original Ticket Price
        if(age < 12)
        {
            price = 100;
        }
        else if(age >= 60)
        {
            price = 150;
        }
        else
        {
            price = 250;
        }

        // 50% Discount for Female
        if(gender == "Female" || gender == "female")
        {
            price = price - (price * 0.50);
            cout << "\n50% Discount Applied for Female Passenger!\n";
        }

        file << ticketNo << endl;
        file << name << endl;
        file << age << endl;
        file << gender << endl;
        file << source << endl;
        file << destination << endl;
        file << price << endl;

        file.close();

        cout << "\nTicket Booked Successfully!\n";
        cout << "Final Ticket Price: " << price << endl;
    }

    // View All Tickets
    void viewTickets()
    {
        ifstream file("tickets.txt");

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
            cout << "\nTicket Price  : " << price;
            cout << "\n--------------------------------------\n";
        }

        file.close();
    }

    // Search Ticket
    void searchTicket()
    {
        int searchNo;
        bool found = false;

        ifstream file("tickets.txt");

        cout << "\nEnter Ticket Number to Search: ";
        cin >> searchNo;

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

                cout << "Passenger Name: " << name << endl;
                cout << "Age           : " << age << endl;
                cout << "Gender        : " << gender << endl;
                cout << "Source        : " << source << endl;
                cout << "Destination   : " << destination << endl;
                cout << "Ticket Price  : " << price << endl;

                found = true;
            }
        }

        if(found == false)
        {
            cout << "\nTicket Not Found!\n";
        }

        file.close();
    }

    // Cancel Ticket
    void cancelTicket()
    {
        int cancelNo;
        bool found = false;

        ifstream file("tickets.txt");
        ofstream temp("temp.txt");

        cout << "\nEnter Ticket Number to Cancel: ";
        cin >> cancelNo;

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
};

int main()
{
    Reservation r;
    int choice;

    do
    {
        cout << "\n========== ONLINE TICKET RESERVATION SYSTEM ==========\n";

        cout << "1. Book Ticket\n";
        cout << "2. View All Tickets\n";
        cout << "3. Search Ticket\n";
        cout << "4. Cancel Ticket\n";
        cout << "5. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

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
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}