#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Train
{
public:
    int trainID;
    string name;
    int totalSeats;
    vector<bool> seats;
    unordered_map<string, int> bookingRecords;
    unordered_map<string, string> userBookings;
    int bookingCounter;

    Train(int id, string trainName, int seatsCount);

    void displaySeats();
    void checkAvailability();
    string generateBookingID();
    string bookTicket(string userID);
    void cancelTicket(string userID);
    void checkTicketStatus(string userID);
};

#endif // TRAIN_H
