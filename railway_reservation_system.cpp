#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Train class to manage train details and bookings
class Train
{
public:
    int trainID;                                // Unique ID for the train
    string name;                                // Train name
    int totalSeats;                             // Total number of seats in the train
    vector<bool> seats;                         // Seat availability (true = booked, false = available)
    unordered_map<string, int> bookingRecords;  // Maps booking ID to seat number
    unordered_map<string, string> userBookings; // Maps user ID to booking ID
    int bookingCounter;                         // Counter for generating booking IDs

    // Constructor to initialize train details
    Train(int id, string trainName, int seatsCount)
        : trainID(id), name(trainName), totalSeats(seatsCount), seats(seatsCount, false), bookingCounter(1) {}

    // Display the seating arrangement of the train
    void displaySeats()
    {
        cout << "\nSeat Map for " << name << " (Train " << trainID << "):\n";
        cout << "O = Available, X = Booked\n";
        cout << "+----+----+    +----+----+\n";

        for (int i = 0; i < totalSeats / 4; i++)
        {
            cout << "| ";
            for (int j = 0; j < 2; j++)
            {
                int seatIndex = i * 4 + j;
                cout << (seats[seatIndex] ? "X " : "O ") << setw(2) << seatIndex + 1 << " | ";
            }
            cout << " || "; // Aisle separator
            for (int j = 2; j < 4; j++)
            {
                int seatIndex = i * 4 + j;
                cout << (seats[seatIndex] ? "X " : "O ") << setw(2) << seatIndex + 1 << " | ";
            }
            cout << "\n";
            if ((i + 1) % 5 == 0)
            { // Separate blocks for better readability
                cout << "+----+----+    +----+----+\n";
            }
        }
    }

    // Check and display the number of available seats
    void checkAvailability()
    {
        int availableSeats = 0;
        for (bool seat : seats)
            if (!seat)
                availableSeats++;
        cout << "Available seats in " << name << " (Train " << trainID << "): " << availableSeats << "\n";
        displaySeats();
    }

    // Generate a unique booking ID
    string generateBookingID()
    {
        stringstream ss;
        ss << "T" << trainID << "-B" << bookingCounter;
        return ss.str();
    }

    // Book a ticket for a user
    string bookTicket(string userID)
    {
        if (userBookings.find(userID) != userBookings.end())
        {
            cout << "User " << userID << " already has a booking on this train!\n";
            return "";
        }

        // Find the first available seat
        int seatNumber = -1;
        for (int i = 0; i < totalSeats; i++)
        {
            if (!seats[i])
            {
                seatNumber = i;
                break;
            }
        }

        if (seatNumber == -1)
        {
            cout << "Sorry, no seats available on this train.\n";
            return "";
        }

        // Book the seat
        seats[seatNumber] = true;
        string bookingID = generateBookingID();
        bookingRecords[bookingID] = seatNumber;
        userBookings[userID] = bookingID;

        cout << "Ticket booked successfully!\nBooking ID: " << bookingID << "\nSeat No.: " << seatNumber + 1 << "\n";
        displaySeats();
        bookingCounter++;

        return bookingID;
    }

    // Cancel a ticket based on user ID
    void cancelTicket(string userID)
    {
        if (userBookings.find(userID) == userBookings.end())
        {
            cout << "No booking found for user " << userID << "!\n";
            return;
        }

        string userBookingID = userBookings[userID];

        // Ask the user to enter their Booking ID for confirmation
        string enteredBookingID;
        cout << "Enter your Booking ID to cancel: ";
        cin >> enteredBookingID;

        if (enteredBookingID != userBookingID)
        {
            cout << "Invalid Booking ID! Cancellation failed.\n";
            return;
        }

        int seatNumber = bookingRecords[enteredBookingID];
        seats[seatNumber] = false;
        bookingRecords.erase(enteredBookingID);
        userBookings.erase(userID);

        cout << "Booking ID " << enteredBookingID << " canceled successfully!\n";
        displaySeats();
    }

    // Check the booking status of a user
    void checkTicketStatus(string userID)
    {
        if (userBookings.find(userID) != userBookings.end())
        {
            string bookingID = userBookings[userID];
            cout << "Booking ID " << bookingID << " is confirmed for seat " << bookingRecords[bookingID] + 1 << "\n";
        }
        else
        {
            cout << "No booking found for user " << userID << "\n";
        }
    }
};

// Print a summary of all bookings before exiting
void printSummary(const unordered_map<string, vector<string>> &userBookingHistory)
{
    cout << "\nSummary of bookings before exiting:\n";
    if (userBookingHistory.empty())
    {
        cout << "No bookings were made.\n";
    }
    else
    {
        cout << "+------------+----------------------------------+\n";
        cout << "|  User ID   |    Seat Booked in:               |\n";
        cout << "+------------+----------------------------------+\n";
        for (const auto &entry : userBookingHistory)
        {
            cout << "| " << setw(10) << left << entry.first << " | " << setw(32) << left << entry.second[0] << " |\n";
            for (size_t i = 1; i < entry.second.size(); i++)
            {
                cout << "|            | " << setw(32) << left << entry.second[i] << " |\n";
            }
            cout << "+------------+----------------------------------+\n";
        }
    }
    cout << "Exiting the system...\n";
}

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

    // Stores user booking history
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

        while (true)
        {
            // Display available trains
            cout << "\nAvailable Trains:\n";
            for (size_t i = 0; i < trains.size(); i++)
            {
                cout << i + 1 << ". " << trains[i].name << " (Train " << trains[i].trainID << ")\n";
            }

            int trainChoice;
            // Prompt user to select a train or exit
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

            // Reference the selected train
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
                    // Check seat availability
                    selectedTrain.checkAvailability();
                    break;
                case 2:
                {
                    // Book a ticket and update user booking history
                    string bookingID = selectedTrain.bookTicket(userID);
                    if (!bookingID.empty())
                    {
                        userBookingHistory[userID].push_back(selectedTrain.name);
                    }
                    goto askUserID;
                }
                case 3:
                    // Cancel ticket
                    selectedTrain.cancelTicket(userID);
                    break;
                case 4:
                    // Check ticket status
                    selectedTrain.checkTicketStatus(userID);
                    break;
                case 5:
                    // Go back to train selection
                    goto trainSelection;
                case 6:
                    // Exit the system and print summary
                    printSummary(userBookingHistory);
                    return 0;
                default:
                    cout << "Invalid choice! Please enter a number between 1 and 6.\n";
                }
            }
        trainSelection:;
        }
    askUserID:;
    }
}