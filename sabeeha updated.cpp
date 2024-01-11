#include <iostream>

using namespace std;

const int NUM_BOATS = 10;
const int OPENING_HOUR = 10;
const int CLOSING_HOUR = 17;
const double HOURLY_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;

struct Boat {
    int boatNumber;
    double moneyTaken;
    double totalHoursHired;
    int returnHour;
    bool isAvailable;
};

// Function prototypes
void hireBoat(Boat boats[]);
void bubbleSort(Boat boats[]);
int findNextAvailableBoat(const Boat boats[]);
int findNextAvailableTime(const Boat boats[], int currentHour);
void displayAvailableBoats(const Boat boats[]);
double calculateCost(double hireDuration);
void generateDailyReport(const Boat boats[]);

int main() {
    Boat boats[NUM_BOATS];

    // Initialize boats
    for (int i = 0; i < NUM_BOATS; ++i) {
        boats[i].boatNumber = i + 1;
        boats[i].moneyTaken = 0.0;
        boats[i].totalHoursHired = 0.0;
        boats[i].returnHour = OPENING_HOUR;
        boats[i].isAvailable = true;
    }

    int choice;
    do {
        cout << "\nMenu:\n1. Hire a boat\n2. Display available boats\n0. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hireBoat(boats);
                break;
            case 2:
                displayAvailableBoats(boats);
                break;
            case 0:
                generateDailyReport(boats);
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}

void hireBoat(Boat boats[]) {
    int availableBoatIndex = findNextAvailableBoat(boats);

    if (availableBoatIndex == -1) {
        cerr << "Error: No available boats. The next available time is unknown.\n";
        return;
    }

    int boatIndex;
    cout << "Enter boat number (1 to " << NUM_BOATS << "): ";
    cin >> boatIndex;

    if (boatIndex < 1 || boatIndex > NUM_BOATS || !boats[boatIndex - 1].isAvailable) {
        cerr << "Error: Invalid boat number or the boat is not available at this time.\n";
        return;
    }

    int startTime;
    double hireDuration;

    cout << "Enter start time (between 10 and 17): ";
    cin >> startTime;

    if (startTime < OPENING_HOUR || startTime >= CLOSING_HOUR) {
        cerr << "Error: Invalid start time. Must be between 10 and 17.\n";
        return;
    }

    cout << "Enter hire duration (in hours, e.g., 1 or 0.5 for half-hour): ";
    cin >> hireDuration;

    if (hireDuration <= 0 || startTime + hireDuration > CLOSING_HOUR) {
        cerr << "Error: Invalid hire duration or return time exceeds 17:00.\n";
        return;
    }

    double payment = calculateCost(hireDuration);
    boats[boatIndex - 1].moneyTaken += payment;
    boats[boatIndex - 1].totalHoursHired += hireDuration;
    boats[boatIndex - 1].returnHour = static_cast<int>(startTime + hireDuration);
    boats[boatIndex - 1].isAvailable = false;

    cout << "Boat " << boats[boatIndex - 1].boatNumber << " hired successfully. Payment: $" << payment << "\n";
}

int findNextAvailableBoat(const Boat boats[]) {
    for (int i = 0; i < NUM_BOATS; ++i) {
        if (boats[i].isAvailable) {
            return i;
        }
    }
    return -1;  // No available boats
}

int findNextAvailableTime(const Boat boats[], int currentHour) {
    for (int hour = currentHour; hour < CLOSING_HOUR; ++hour) {
        bool isHourAvailable = true;

        for (int i = 0; i < NUM_BOATS; ++i) {
            if (!boats[i].isAvailable && hour >= boats[i].returnHour) {
                isHourAvailable = false;
                break;
            }
        }

        if (isHourAvailable) {
            return hour;
        }
    }

    return -1;  // No available time
}

double calculateCost(double hireDuration) {
    return (hireDuration >= 1) ? (hireDuration * HOURLY_RATE) : ((hireDuration + 0.5) * HALF_HOUR_RATE);
}

void bubbleSort(Boat boats[]) {
    // Implementation of the bubbleSort function goes here
}

void generateDailyReport(const Boat boats[]) {
    // Implementation of the generateDailyReport function goes here
}

void displayAvailableBoats(const Boat boats[]) {
    cout << "\nAvailable Boats:\n";
    for (int i = 0; i < NUM_BOATS; ++i) {
        cout << "Boat " << boats[i].boatNumber << ": ";
        if (boats[i].isAvailable) {
            cout << "Available\n";
        } else {
            cout << "Not Available (Return time: " << boats[i].returnHour << ":";
            // Adjust the display for half-hour hires
            if (boats[i].totalHoursHired - static_cast<int>(boats[i].totalHoursHired) == 0.5) {
                cout << "30";
            } else {
                cout << "00";
            }
            cout << ")\n";
        }
    }
}

