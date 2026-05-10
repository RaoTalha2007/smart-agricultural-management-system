#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <windows.h>
#include <sstream>
using namespace std;

// ============================================
//                DATA STRUCTURE
// ============================================
struct Crop {
    int id;
    string name;
    string soilType;
    string waterNeed;
    string season;
};

// ============================================
//                UTILITY FUNCTIONS
// ============================================

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void clearScreen() {
    system("cls");
}
void pauseScreen() {
    /*cout << "\nPress Enter to Countinue...";
    cin.get();*/
    system("pause");
}
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
bool partialMatch(string text, string query) {
    return toLower(text).find(toLower(query)) != string::npos;
}

// ============================================
//                HEADER & MENUS
// ============================================

void header() {
    color(11);
    cout << "===============================================\n";
    cout << "   SMART AGRICULTURE CROP SUGGESTION SYSTEM   \n";
    cout << "===============================================\n\n";
    color(15);
}

void mainMenu() {
    header();
    cout << "1. Add Crop\n";
    cout << "2. Search Crops\n";
    cout << "3. Smart Suggestion\n";
    cout << "4. View All Crops\n";
    cout << "5. Update Crop\n";
    cout << "6. Delete Crop\n";
    cout << "7. Sort Crops\n";
    cout << "8. Statistics\n";
    cout << "9. Save & Exit\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter choice: ";
}

void searchMenu() {
    clearScreen();
    header();
    cout << "Search By:\n";
    cout << "1. Season\n";
    cout << "2. Soil Type\n";
    cout << "3. Return\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter choice: ";
}

void sortMenu() {
    clearScreen();
    header();
    cout << "Sort Crops By:\n";
    cout << "1. Id\n";
    cout << "2. Name\n";
    cout << "3. Season\n";
    cout << "4. Water Need\n";
    cout << "5. Return\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter choice: ";
}

// ============================================
//          Saving and Loading File
// ============================================

void saveToFile(vector<Crop>& crops) {
    ofstream file("crops.txt");
    for (auto& c : crops) {
        file << c.id << "," << c.name << "," << c.soilType << "," << c.waterNeed << "," << c.season << "\n";
    }
}

void loadFromFile(vector<Crop>& crops) {
    ifstream file("crops.txt");
    string line;

    while (getline(file, line)) {
        Crop c;
        string temp;
        stringstream ss(line);    //use to turn the whole line into a stream
        getline(ss, temp, ',');   //read until comma
        c.id = stoi(temp);        //convert string to integar
        getline(ss, c.name, ',');
        getline(ss, c.soilType, ',');
        getline(ss, c.waterNeed, ',');
        getline(ss, c.season, ',');
        crops.push_back(c);
    }
}

// ============================================
//                 Functions
// ============================================

void addCrop(vector<Crop>& crops) {
    clearScreen(); header();
    Crop c;
    cin.ignore();

    c.id = crops.empty() ? 1 : crops.back().id + 1;
    cout << "Enter Crop Name: ";
    getline(cin, c.name);
    cout << "Enter Soil Type: ";
    getline(cin, c.soilType);
    cout << "Enter Water Need (Low/Medium/High): ";
    getline(cin, c.waterNeed);
    cout << "Enter Season: ";
    getline(cin, c.season);

    crops.push_back(c);
    color(10);
    cout << "Crops added successfully!\n";
    color(15);
    pauseScreen();
}

// --------------- Search Options ---------------

void searchBySeason(vector<Crop>& crops) {
    clearScreen(); header();
    string season; cin.ignore();    //Used to ignore the characters when a line is inserted by the cin function so the getline funcation can read the line

    cout << "Enter Season: ";
    getline(cin, season);
    bool found = false;
    for (auto& c : crops) {
        if (partialMatch(c.season, season)) {
            cout << c.id << ". " << c.name << " | Soil: " << c.soilType << " | Water: " << c.waterNeed << "\n";
            found = true;
        }
    }
    if (!found) {
        color(12);
        cout << "No crops found.\n";
        color(15);
    }
    pauseScreen();
}
void searchBySoil(vector<Crop>& crops) {
    clearScreen(); header();
    string soil; cin.ignore();

    cout << "Enter Soil type: ";
    getline(cin, soil);
    bool found = false;
    for (auto& c : crops) {
        if (partialMatch(c.soilType, soil)) {
            cout << c.id << ". " << c.name << " | Season: " << c.season << " | Water: " << c.waterNeed << "\n";
            found = true;
        }
    }
    if (!found) {
        color(12);
        cout << "No crops found.\n";
        color(15);
    }
    pauseScreen();
}

// -------------- SMART SUGGESTION -----------

void smartSuggestion(vector<Crop>& crops) {
    clearScreen(); header();
    string soil, water, season;
    cin.ignore();

    cout << "Enter Soil Type: ";
    getline(cin, soil);
    cout << "Enter Water Need: ";
    getline(cin, water);
    cout << "Enter Season: ";
    getline(cin, season);

    bool found = false;
    for (int i = 0; i < crops.size(); i++) {
        Crop* ptr = &crops[i];   // 🔹 POINTER
        if (toLower(ptr->soilType) == toLower(soil) &&
            toLower(ptr->waterNeed) == toLower(water) &&
            toLower(ptr->season) == toLower(season)) {
            cout << ptr->id << ". " << ptr->name << "\n";
            found = true;
        }
    }
    if (!found) {
        color(12);
        cout << "No exact match found.\n";
        color(15);
    }
    pauseScreen();
}

// -------------- DISPLAY ALL ----------------

void displayAll(vector<Crop>& crops) {
    clearScreen(); header();

    cout << "+----+------------+----------+----------+----------+\n";
    cout << "| ID | Name       | Soil     | Water    | Season   |\n";
    cout << "+----+------------+----------+----------+----------+\n";

    for (auto& c : crops) {
        cout << "| " << left << setw(3) << c.id
            << "| " << setw(11) << c.name
            << "| " << setw(9) << c.soilType
            << "| " << setw(9) << c.waterNeed
            << "| " << setw(9) << c.season << "|\n";
    }
    cout << "+----+------------+----------+----------+----------+\n";

    pauseScreen();
}

// -------------- UPDATE ---------------------

void updateCrop(vector<Crop>& crops) {
    clearScreen(); header();
    int id;
    cout << "Enter Crop ID: ";
    cin >> id;
    cin.ignore();

    for (int i = 0; i < crops.size(); i++) {
        Crop* ptr = &crops[i];
        if (ptr->id == id) {
            cout << "New Soil Type: ";
            getline(cin, ptr->soilType);
            cout << "New Water Need: ";
            getline(cin, ptr->waterNeed);
            cout << "New Season: ";
            getline(cin, ptr->season);
            color(10);
            cout << "Updated Successfully!\n";
            color(15);
            pauseScreen();
            return;
        }
    }
    color(12);
    cout << "Crop not found.\n";
    color(15);
    pauseScreen();
}

// -------------- DELETE ---------------------
void deleteCrop(vector<Crop>& crops) {
    clearScreen(); header();
    int id;
    cout << "Enter Crop ID: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < crops.size(); i++) {
        if (crops[i].id == id) {
            crops.erase(crops.begin() + i);
            found = true;
            break;
        }
    }

    if (found) {
        color(10);
        cout << "\nCrop deleted successfully!\n";
        color(15);
    }
    else {
        color(12);
        cout << "\nCrop not found!\n";
        color(15);
    }
    pauseScreen();
}

// -------------- SORTING --------------------

bool compareByName(Crop a, Crop b) {
    return a.name < b.name;
}

bool compareBySeason(Crop a, Crop b) {
    return a.season < b.season;
}

bool compareByWater(Crop a, Crop b) {
    return a.waterNeed < b.waterNeed;
}

bool compareById(Crop a, Crop b) {
    return a.id < b.id;
}

void sortCrops(vector<Crop>& crops) {
    while (true) {
        sortMenu();
        int ch;
        cin >> ch;
        if (ch == 1) {
            sort(crops.begin(), crops.end(), compareById);
        }
        if (ch == 2) {
            sort(crops.begin(), crops.end(), compareByName);
        }
        else if (ch == 3) {
            sort(crops.begin(), crops.end(), compareBySeason);
        }
        else if (ch == 4) {
            sort(crops.begin(), crops.end(), compareByWater);
        }
        else if (ch == 5) {
            return;
        }
        else if (ch > 5 || ch < 1) {
            cout << "Invalid choice!\n";
            pauseScreen(); return;
        }
        cout << "Sorted successfully!\n";
        pauseScreen();
    }
}

// -------------- STATISTICS ------------------

void statistics(vector<Crop>& crops) {
    clearScreen(); header();

    cout << "Total Crops: " << crops.size() << "\n\n";
    map<string, int> seasonCount;
    map<string, int> soilCount;

    for (int i = 0; i < crops.size(); i++) {
        Crop* ptr = &crops[i];   // 🔹 POINTER
        seasonCount[ptr->season]++;
        soilCount[ptr->soilType]++;
    }
    cout << "Crops Per Season:\n";
    for (auto& p : seasonCount)
        cout << p.first << ": " << p.second << "\n";
    cout << "\nCrops Per Soil Type:\n";
    for (auto& p : soilCount)
        cout << p.first << ": " << p.second << "\n";
    pauseScreen();
}


// ============================================
//                MAIN
// ============================================

int main() {
    vector<Crop> crops;
    loadFromFile(crops);
    while (true) {
        clearScreen();
        mainMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:addCrop(crops); break;
        case 2: {
            searchMenu();
            int ch;
            cin >> ch;
            if (ch == 1)
                searchBySeason(crops);
            else if (ch == 2)
                searchBySoil(crops);
            break;
        }
        case 3: smartSuggestion(crops); break;
        case 4: displayAll(crops); break;
        case 5: updateCrop(crops); break;
        case 6: deleteCrop(crops); break;
        case 7: sortCrops(crops); break;
        case 8: statistics(crops); break;
        case 9: saveToFile(crops);
            cout << "Saved successfully.\nGoodbye!\n";
            return 0;
        default:
            cout << "Invalid option!\n";
            pauseScreen();
        }
    }
}