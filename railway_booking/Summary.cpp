#include "Summary.h"

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
