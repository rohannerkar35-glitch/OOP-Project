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
    void bookTicket()#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Reservation
{
private:
    int ticketNo, age;
    float price;
    string name, gender;
    string source, destination;
    string journeyDate;

public:

    // ================= BOOK TICKET =================
    void bookTicket()
    {
        try
        {
            cout << "\nEnter Ticket Number: ";
            cin >> ticketNo;

            if(cin.fail() || ticketNo <= 0)
                throw "Invalid Ticket Number!";

            // ---------- Duplicate Ticket Check ----------
            ifstream checkFile("tickets.txt");

            int tNo, tAge;
            float tPrice;
            string tName, tGender, tSource, tDestination, tDate;

            while(checkFile >> tNo)
            {
                checkFile.ignore();

                getline(checkFile, tName);

                checkFile >> tAge;
                checkFile.ignore();

                getline(checkFile, tGender);
                getline(checkFile, tSource);
                getline(checkFile, tDestination);
                getline(checkFile, tDate);

                checkFile >> tPrice;
                checkFile.ignore();

                if(tNo == ticketNo)
                {
                    throw "Ticket Number Already Exists!";
                }
            }

            checkFile.close();

            cin.ignore();

            cout << "Enter Passenger Name: ";
            getline(cin, name);

            cout << "Enter Age: ";
            cin >> age;

            if(cin.fail() || age < 0 || age > 120)
                throw "Invalid Age!";

            cin.ignore();

            cout << "Enter Gender (Male/Female): ";
            getline(cin, gender);

            cout << "Enter Source: ";
            getline(cin, source);

            cout << "Enter Destination: ";
            getline(cin, destination);

            if(source == destination)
                throw "Source and Destination cannot be same!";

            cout << "Enter Journey Date (DD/MM/YYYY): ";
            getline(cin, journeyDate);

            // ---------- Ticket Fare ----------
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

            ofstream file("tickets.txt", ios::app);

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
            cout << "\nFinal Fare: Rs. " << price << endl;
        }
        catch(const char *msg)
        {
            cout << "\nError: " << msg << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // ================= VIEW ALL TICKETS =================
    void viewTickets()
    {
        ifstream file("tickets.txt");

        if(!file)
        {
            cout << "\nNo Reservation Records Found!\n";
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

            cout << "\nTicket No     : " << ticketNo;
            cout << "\nPassenger     : " << name;
            cout << "\nAge           : " << age;
            cout << "\nGender        : " << gender;
            cout << "\nSource        : " << source;
            cout << "\nDestination   : " << destination;
            cout << "\nJourney Date  : " << journeyDate;
            cout << "\nFare          : Rs. " << price;
            cout << "\n----------------------------------\n";
        }

        file.close();
    }

    // ================= SEARCH TICKET =================
    void searchTicket()
    {
        int searchNo;
        bool found = false;

        cout << "\nEnter Ticket Number to Search: ";
        cin >> searchNo;

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
            getline(file, journeyDate);

            file >> price;
            file.ignore();

            if(ticketNo == searchNo)
            {
                found = true;

                cout << "\nTicket Found!\n";
                cout << "Passenger    : " << name << endl;
                cout << "Age          : " << age << endl;
                cout << "Gender       : " << gender << endl;
                cout << "Source       : " << source << endl;
                cout << "Destination  : " << destination << endl;
                cout << "Journey Date : " << journeyDate << endl;
                cout << "Fare         : Rs. " << price << endl;

                break;
            }
        }

        if(!found)
            cout << "\nTicket Not Found!\n";

        file.close();
    }

    // ================= UPDATE TICKET =================
    void updateTicket()
    {
        int updateNo;
        bool found = false;

        cout << "\nEnter Ticket Number to Update: ";
        cin >> updateNo;
        cin.ignore();

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
            getline(file, journeyDate);

            file >> price;
            file.ignore();

            if(ticketNo == updateNo)
            {
                found = true;

                cout << "\nEnter New Passenger Name: ";
                getline(cin, name);

                cout << "Enter New Age: ";
                cin >> age;
                cin.ignore();

                cout << "Enter New Journey Date: ";
                getline(cin, journeyDate);

                // Recalculate fare
                price = 250;

                if(gender == "Female" || gender == "female")
                    price = price - (price * 0.50);

                if(age >= 60)
                    price = price - (price * 0.75);
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
            cout << "\nTicket Updated Successfully!\n";
        else
            cout << "\nTicket Not Found!\n";
    }

    // ================= CANCEL TICKET =================
    void cancelTicket()
    {
        int cancelNo;
        bool found = false;

        cout << "\nEnter Ticket Number to Cancel: ";
        cin >> cancelNo;

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
            cout << "\nTicket Cancelled Successfully!\n";
        else
            cout << "\nTicket Not Found!\n";
    }

    // ================= PRINT RECEIPT =================
    void printReceipt()
    {
        int receiptNo;
        bool found = false;

        cout << "\nEnter Ticket Number: ";
        cin >> receiptNo;

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
            getline(file, journeyDate);

            file >> price;
            file.ignore();

            if(ticketNo == receiptNo)
            {
                found = true;

                cout << "\n====================================";
                cout << "\n         TICKET RECEIPT";
                cout << "\n====================================";
                cout << "\nTicket No     : " << ticketNo;
                cout << "\nPassenger     : " << name;
                cout << "\nAge           : " << age;
                cout << "\nGender        : " << gender;
                cout << "\nSource        : " << source;
                cout << "\nDestination   : " << destination;
                cout << "\nJourney Date  : " << journeyDate;
                cout << "\nFare          : Rs. " << price;
                cout << "\n====================================\n";

                break;
            }
        }

        if(!found)
            cout << "\nTicket Not Found!\n";

        file.close();
    }
};

// ================= MAIN FUNCTION =================
int main()
{
    Reservation r;
    int choice;

    do
    {
        cout << "\n\n========== ONLINE TICKET RESERVATION SYSTEM ==========\n";
        cout << "1. Book Ticket\n";
        cout << "2. View All Tickets\n";
        cout << "3. Search Ticket\n";
        cout << "4. Update Ticket\n";
        cout << "5. Cancel Ticket\n";
        cout << "6. Print Ticket Receipt\n";
        cout << "7. Exit\n";

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
                r.updateTicket();
                break;

            case 5:
                r.cancelTicket();
                break;

            case 6:
                r.printReceipt();
                break;

            case 7:
                cout << "\nThank You for Using the System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 7);

    return 0;
}
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
