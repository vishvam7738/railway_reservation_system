#include "Train.h"
#include<sstream>
#include<iomanip>
#include<iostream>
Train::Train(int id, string trainName, int seatsCount)
    : trainID(id), name(trainName), totalSeats(seatsCount), seats(seatsCount, false) {}

void Train::displaySeats()
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
        cout << " || ";
        for (int j = 2; j < 4; j++)
        {
            int seatIndex = i * 4 + j;
            cout << (seats[seatIndex] ? "X " : "O ") << setw(2) << seatIndex + 1 << " | ";
        }
        cout << "\n";
        if ((i + 1) % 5 == 0)
        {
            cout << "+----+----+    +----+----+\n";
        }
    }
}

void Train::checkAvailability()
{
    int availableSeats = 0;
    for (bool seat : seats)
        if (!seat)
            availableSeats++;
    cout << "Available seats in " << name << " (Train " << trainID << "): " << availableSeats << "\n";
    displaySeats();
}
