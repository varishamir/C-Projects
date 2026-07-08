#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct TimeStruct {
    int hour;
    int minutes;
};

int main() {
    string path = "file_path.txt";
    ifstream inFile(path);

    if (!inFile.is_open() || inFile.peek() == ifstream::traits_type::eof()) {
        if (inFile.is_open()) inFile.close();

        ofstream outFile(path);
        int number;
        cout << "How many medicines do you take daily? ";
        cin >> number;

        outFile << number << endl;

        for (int i = 0; i < number; ++i) {
            string medname;
            int intakes;
            cout << "\n--- Medicine " << (i + 1) << " ---\n";
            cout << "Enter medicine name: ";
            cin >> medname;

            cout << "Enter number of intakes: ";
            cin >> intakes;

            outFile << medname << " " << intakes << endl;

            for (int j = 0; j < intakes; ++j) {
                int h, m;
                string period;

                cout << "Enter time for intake " << (j + 1) << " (HH MM AM/PM): ";
                cin >> h >> m >> period;

                if ((period == "PM" || period == "pm") && h != 12) {
                    h += 12;
                } else if ((period == "AM" || period == "am") && h == 12) {
                    h = 0;
                }
                outFile << h << " " << m << endl;
            }
        }
        outFile.close();
        cout << "\nFile created and data saved successfully!\n";
    }
	inFile.close();

    time_t now = time(nullptr);
    struct tm *localTime = localtime(&now);
    int hr = localTime->tm_hour;
    int mins = localTime->tm_min;
    
    cout << "...........MEDICATION TRACKER.................." << endl << endl;

    cout << "___________What are you looking for____________" << endl;
    cout << "|                                              |" << endl;
    cout << "|    1. Medicines names                        |" << endl;
    cout << "|    2. Number of Medicines                    |" << endl;
    cout << "|    3. Medicines timings                      |" << endl;
    cout << "|    4. Upcoming reminder                      |" << endl;
    cout << "|______________________________________________|" << endl;

    inFile.open(path);
	int options;
    cout << "Enter number of option: ";
    cin >> options;

    int medicineNumber = 0;
    if (!(inFile >> medicineNumber)) return 0;

    if (options == 2) {
        cout << "Number of medicines you take: " << medicineNumber << endl;
    }

    for (int j = 0; j < medicineNumber; j++) {
        string currentMedName;
        int intakes;
        
        inFile >> currentMedName >> intakes;

        if (options == 1) {
            cout << "Medicine " << (j + 1) << ": " << currentMedName << endl;
        }

        for (int k = 0; k < intakes; ++k) {
            int h, m;
            inFile >> h >> m;

            if (options == 3) {
                cout << currentMedName << " intake " << (k + 1) << ": " << h << ":" << m << endl;
            }

            if (options == 4) {
                if (h == hr && (mins >= m && mins <= m + 30)) {
                    cout << "It's time to take " << currentMedName << endl;
                    #ifdef _WIN32
                    Beep(3000, 900);
                    #endif
                } else {
                	cout << "Upcoming Reminder for " << currentMedName << " at " << h << ":" << m << endl;
                }
            }
        }
    }

    inFile.close();
    return 0;
}
