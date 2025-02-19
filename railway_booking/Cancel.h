#ifndef CANCEL_H
#define CANCEL_H

#include "Train.h"
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Cancel
{
public:
    void cancelTicket(Train &train, unordered_map<string, int> &bookingRecords, unordered_map<string, string> &userBookings, string userID);
};

#endif
