#ifndef BOOKING_H
#define BOOKING_H

#include "Train.h"

class Booking
{
public:
    unordered_map<string, int> bookingRecords;
    unordered_map<string, string> userBookings;
    int bookingCounter;

public:
    Booking();

    string generateBookingID(int trainID);
    string bookTicket(Train &train, string userID);
    void checkTicketStatus(string userID);

    friend class Cancel; // Allow Cancel class to access booking records
};

#endif
