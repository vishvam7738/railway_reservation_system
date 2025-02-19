#include "Cancel.h"

void Cancel::cancelTicket(Train &train, unordered_map<string, int> &bookingRecords, unordered_map<string, string> &userBookings, string userID)
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
    train.seats[seatNumber] = false;
    bookingRecords.erase(enteredBookingID);
    userBookings.erase(userID);

    cout << "Booking ID " << enteredBookingID << " canceled successfully!\n";
    train.displaySeats();
}
