#include "Train.h"
#include "Booking.h"
#include "Cancel.h"
#include "Summary.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    // List of available trains with train ID, name, and total seats
    vector<Train> trains = {
        {101, "Bangalore - Kanyakumari Express", 40},
        {102, "Delhi - Jaisalmer Express", 40},
        {103, "Mumbai - Chennai Express", 40},
        {104, "Kolkata - Hyderabad Express", 40},
        {105, "Pune - Jaipur Express", 40},
        {106, "Lucknow - Patna Express", 40},
        {107, "Chandigarh - Bhopal Express", 40},
        {108, "Ahmedabad - Varanasi Express", 40}};

    Booking bookingSystem;
    Cancel cancelSystem;
    unordered_map<string, vector<string>> userBookingHistory;

    while (true)
    {
        string userID;
        while (true)
        {
            // Prompt user for ID or exit option
            cout << "Enter your User ID (1-100) or 0 to exit: ";
            cin >> userID;

            if (userID == "0")
            {
                printSummary(userBookingHistory);
                return 0;
            }

            try
            {
                int id = stoi(userID);
                if (id >= 1 && id <= 100)
                    break;
            }
            catch (...)
            {
                cout << "Invalid input! Please enter a number between 1 and 100.\n";
            }
        }

    trainSelection:
        while (true)
        {
            // Display available trains
            cout << "\nAvailable Trains:\n";
            for (size_t i = 0; i < trains.size(); i++)
            {
                cout << i + 1 << ". " << trains[i].name << " (Train " << trains[i].trainID << ")\n";
            }

            int trainChoice;
            cout << "\nSelect a train (1-8) or 0 to exit: ";
            cin >> trainChoice;

            if (trainChoice == 0)
            {
                printSummary(userBookingHistory);
                return 0;
            }

            if (trainChoice < 1 || trainChoice > 8)
            {
                cout << "Invalid train selection! Please try again.\n";
                continue;
            }

            Train &selectedTrain = trains[trainChoice - 1];

            while (true)
            {
                // Display menu options
                cout << "\n1. Check Seat Availability\n";
                cout << "2. Book Ticket\n";
                cout << "3. Cancel Ticket\n";
                cout << "4. Check Ticket Status\n";
                cout << "5. Select Another Train\n";
                cout << "6. Exit the System\n";
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;

                switch (choice)
                {
                case 1:
                    selectedTrain.displaySeats();
                    break;
                case 2:
                {
                    // Book ticket and update history
                    string bookingID = bookingSystem.bookTicket(selectedTrain, userID);
                    if (!bookingID.empty())
                    {
                        userBookingHistory[userID].push_back(selectedTrain.name);
                    }
                    goto askUserID;
                }
                case 3:
                    // Cancel ticket
                    cancelSystem.cancelTicket(selectedTrain, bookingSystem.bookingRecords, bookingSystem.userBookings, userID);
                    break;
                case 4:
                    // Check ticket status
                    bookingSystem.checkTicketStatus(userID);
                    break;
                case 5:
                    // Go back to train selection
                    goto trainSelection;
                case 6:
                    // Exit system and show summary
                    printSummary(userBookingHistory);
                    return 0;
                default:
                    cout << "Invalid choice! Please enter a number between 1 and 6.\n";
                }
            }
        }
    askUserID:;
    }
}
