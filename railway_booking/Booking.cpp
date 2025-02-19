#include "Booking.h"

Booking::Booking() : bookingCounter(1) {}

string Booking::generateBookingID(int trainID)
{
    return "T" + to_string(trainID) + "-B" + to_string(bookingCounter++);
}

string Booking::bookTicket(Train &train, string userID)
{
    if (userBookings.find(userID) != userBookings.end())
    {
        cout << "User " << userID << " already has a booking on this train!\n";
        return "";
    }

    int seatNumber = -1;
    for (int i = 0; i < train.totalSeats; i++)
    {
        if (!train.seats[i])
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

    train.seats[seatNumber] = true;
    string bookingID = generateBookingID(train.trainID);
    bookingRecords[bookingID] = seatNumber;
    userBookings[userID] = bookingID;

    cout << "Ticket booked successfully!\nBooking ID: " << bookingID << "\nSeat No.: " << seatNumber + 1 << "\n";
    train.displaySeats();

    return bookingID;
}

void Booking::checkTicketStatus(string userID)
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
