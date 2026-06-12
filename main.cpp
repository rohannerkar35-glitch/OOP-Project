#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
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
    string journeyDate;

public:

    bool isDuplicateTicket(int tNo)
    {
        ifstream file("tickets.txt");

        int tempTicket, tempAge;
        float tempPrice;
        string tempName, tempGender, tempSource, tempDestination, tempDate;

        while(file >> tempTicket)
        {
            file.ignore();

            getline(file, tempName);

            file >> tempAge;
            file.ignore();

            getline(file, tempGender);
            getline(file, tempSource);
            getline(file, tempDestination);
            getline(file, tempDate);

            file >> tempPrice;
            file.ignore();

            if(tempTicket == tNo)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void calculatePrice()
    {
        price = 250;

        if(gender == "Female" || gender == "female")
        {
            price = price - (price * 0.50);
        }

        if(age >= 60)
        {
            price = price - (price * 0.75);
        }
    }

    void printReceipt()
    {
        cout << "\n\n========== TICKET RECEIPT ==========";
        cout << "\nTicket Number : " << ticketNo;
        cout << "\nPassenger Name: " << name;
        cout << "\nAge           : " << age;
        cout << "\nGender        : " << gender;
        cout << "\nSource        : " << source;
        cout << "\nDestination   : " << destination;
        cout << "\nJourney Date  : " << journeyDate;
        cout << "\nTicket Price  : Rs. " << price;
        cout << "\n====================================\n";
    }

    void bookTicket()
    {
        try
        {
            ofstream file("tickets.txt", ios::app);

            if(!file)
                throw "Unable to open file!";

            cout << "\nEnter Ticket Number: ";
            cin >> ticketNo;

            if(cin.fail())
                throw "Ticket Number must be numeric!";

            if(ticketNo <= 0)
                throw "Ticket Number must be positive!";

            if(isDuplicateTicket(ticketNo))
                throw "Ticket Number already exists! Please enter a unique ticket number.";

            cin.ignore();

            cout << "Enter Passenger Name: ";
            getline(cin, name);

            if(name == "")
                throw "Passenger name cannot be empty!";

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

            if(source == "")
                throw "Source cannot be empty!";

            cout << "Enter Destination: ";
            getline(cin, destination);

            if(destination == "")
                throw "Destination cannot be empty!";

            if(source == destination)
                throw "Source and Destination cannot be same!";

            cout << "Enter Journey Date (DD/MM/YYYY): ";
            getline(cin, journeyDate);

            if(journeyDate == "")
                throw "Journey date cannot be empty!";

            calculatePrice();

            if(gender == "Female" || gender == "female")
                cout << "\n50% Female Discount Applied!";

            if(age >= 60)
                cout << "\n75% Senior Citizen Discount Applied!";

            file << ticketNo << endl;
            file << name << endl;
            file << age << endl;
            file << gender << endl;
            file << source << endl;
            file << destination << endl;
            file << journeyDate << endl;
            file << price << endl;

            file.close();

            cout << "\n\nTicket Booked Successfully!";
            printReceipt();
        }
        catch(const char *msg)
        {
            cout << "\nError: " << msg << endl;

            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

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
            getline(file, journeyDate);

            file >> price;
            file.ignore();

            cout << "\nTicket Number : " << ticketNo;
            cout << "\nPassenger Name: " << name;
            cout << "\nAge           : " << age;
            cout << "\nGender        : " << gender;
            cout << "\nSource        : " << source;
            cout << "\nDestination   : " << destination;
            cout << "\nJourney Date  : " << journeyDate;
            cout << "\nTicket Price  : Rs. " << price;
            cout << "\n--------------------------------------\n";
        }

        file.close();
    }

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

            if(!file)
                throw "No records found!";

            while(file >> ticketNo)
            {
                file.ignore();

                getline(file, name);

                file >> age;
                file.ignore();

                getline(file, gender);
                getline(file, source);
                getline(file, destination);
                getline(file, journeyDate);

                file >> price;
                file.ignore();

                if(ticketNo == searchNo)
                {
                    cout << "\nTicket Found!";
                    printReceipt();

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

            if(!file)
                throw "No records found!";

            if(!temp)
                throw "Unable to create temporary file!";

            while(file >> ticketNo)
            {
                file.ignore();

                getline(file, name);

                file >> age;
                file.ignore();

                getline(file, gender);
                getline(file, source);
                getline(file, destination);
                getline(file, journeyDate);

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
                    temp << journeyDate << endl;
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

    void updateTicket()
    {
        int updateNo;
        bool found = false;

        try
        {
            cout << "\nEnter Ticket Number to Update: ";
            cin >> updateNo;

            if(cin.fail())
                throw "Ticket Number must be numeric!";

            ifstream file("tickets.txt");
            ofstream temp("temp.txt");

            if(!file)
                throw "No records found!";

            if(!temp)
                throw "Unable to create temporary file!";

            while(file >> ticketNo)
            {
                file.ignore();

                getline(file, name);

                file >> age;
                file.ignore();

                getline(file, gender);
                getline(file, source);
                getline(file, destination);
                getline(file, journeyDate);

                file >> price;
                file.ignore();

                if(ticketNo == updateNo)
                {
                    found = true;

                    cout << "\nEnter New Passenger Name: ";
                    getline(cin, name);

                    if(name == "")
                        throw "Passenger name cannot be empty!";

                    cout << "Enter New Age: ";
                    cin >> age;

                    if(cin.fail())
                        throw "Age must be numeric!";

                    if(age < 0 || age > 120)
                        throw "Invalid Age!";

                    cin.ignore();

                    cout << "Enter New Gender (Male/Female): ";
                    getline(cin, gender);

                    if(gender != "Male" && gender != "male" &&
                       gender != "Female" && gender != "female")
                    {
                        throw "Invalid Gender! Enter Male or Female.";
                    }

                    cout << "Enter New Source: ";
                    getline(cin, source);

                    if(source == "")
                        throw "Source cannot be empty!";

                    cout << "Enter New Destination: ";
                    getline(cin, destination);

                    if(destination == "")
                        throw "Destination cannot be empty!";

                    if(source == destination)
                        throw "Source and Destination cannot be same!";

                    cout << "Enter New Journey Date (DD/MM/YYYY): ";
                    getline(cin, journeyDate);

                    if(journeyDate == "")
                        throw "Journey date cannot be empty!";

                    calculatePrice();
                }

                temp << ticketNo << endl;
                temp << name << endl;
                temp << age << endl;
                temp << gender << endl;
                temp << source << endl;
                temp << destination << endl;
                temp << journeyDate << endl;
                temp << price << endl;
            }

            file.close();
            temp.close();

            remove("tickets.txt");
            rename("temp.txt", "tickets.txt");

            if(found)
            {
                cout << "\nTicket Updated Successfully!";
                printReceipt();
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
    int choice = 0;

    do
    {
        try
        {
            cout << "\n\n========== ONLINE TICKET RESERVATION SYSTEM ==========\n";
            cout << "1. Book Ticket\n";
            cout << "2. View All Tickets\n";
            cout << "3. Search Ticket\n";
            cout << "4. Cancel Ticket\n";
            cout << "5. Update Ticket\n";
            cout << "6. Exit\n";

            cout << "\nEnter Your Choice: ";
            cin >> choice;

            if(cin.fail())
                throw "Choice must be numeric!";

            if(choice < 1 || choice > 6)
                throw "Please enter a valid choice (1-6)!";

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
                    r.updateTicket();
                    break;

                case 6:
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

    } while(choice != 6);

    return 0;
}