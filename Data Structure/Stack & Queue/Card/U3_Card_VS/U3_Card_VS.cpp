#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// Card structure
struct Card {
    string name;
    double probability;
    Card* next;
    string cla; // Card category
};

// Pack structure
struct Pack {
    string type;
    Card* head;
    double criticalProbability; // Critical hit probability
    Pack* criticalPack;         // Pack to draw from on critical hit
    int num_card;               // Number of cards in the pack
};

// Function declarations
void addCardToPack(Pack* pack, const string& name, double probability, string cla);
Pack* createPack(const string& type, const string& filename);
void drawCard(Pack* pack);
void drawPack(Pack* pack, int times);
void printMenu();
void freePack(Pack* pack);
string UTF8ToGB(const char* str);

// Main function
int main() {
    srand(time(nullptr)); // Set random seed
    string choice;
    int drawType, drawTimes;

    string filename = "card.txt";
    Pack* ssrPack = createPack("SSR", filename);
    Pack* srPack = createPack("SR", filename);
    Pack* sPack = createPack("S", filename);
    Pack* aPack = createPack("A", filename);

    // Set critical hit logic
    srPack->criticalProbability = 10;
    srPack->criticalPack = ssrPack;
    sPack->criticalProbability = 10;
    sPack->criticalPack = srPack;
    aPack->criticalProbability = 10;
    aPack->criticalPack = sPack;

    printMenu();

    while (true) {
        cout << "Choose a pack to draw from (1-SSR, 2-SR, 3-S, 4-A): ";
        cin >> drawType;
        cout << "Choose number of draws (1-single, 5-multi): ";
        cin >> drawTimes;

        switch (drawType) {
        case 1:
            drawPack(ssrPack, drawTimes);
            break;
        case 2:
            drawPack(srPack, drawTimes);
            break;
        case 3:
            drawPack(sPack, drawTimes);
            break;
        case 4:
            drawPack(aPack, drawTimes);
            break;
        default:
            cout << "Invalid choice.\n";
            continue;
        }

        cout << "Continue drawing (1), or exit (0): ";
        cin >> choice;
        if (choice == "0") {
            break;
        }
    }

    freePack(ssrPack);
    freePack(srPack);
    freePack(sPack);
    freePack(aPack);

    return 0;
}

// Read pack information from file
Pack* createPack(const string& type, const string& filename) {
    ifstream file(filename);
    string line;
    Pack* pack = new Pack{ type, nullptr, 0.0, nullptr, 0 };

    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return nullptr;
    }

    while (getline(file, line)) {
        string str = UTF8ToGB(line.c_str()).c_str();
        if (str == type + "包") {
            double currentProbability = 0;
            while (getline(file, line)) {
                string str = UTF8ToGB(line.c_str()).c_str();
                if (str.find("包") != std::string::npos) {
                    break;
                }
                size_t posClassEnd = str.find("：");
                string classLabel = str.substr(0, posClassEnd);

                // Extract initial probability and card count
                size_t posSpace = str.find(" ", posClassEnd + 3);
                double probability = stod(str.substr(posClassEnd + 3, posSpace - posClassEnd - 3)) * 100;
                int numCards = stoi(str.substr(posSpace + 1, str.find("个", posSpace) - posSpace - 1));

                // Extract name list
                size_t posNames = str.find(" ", posSpace) + 3;
                string namesList = str.substr(posNames);
                istringstream namesStream(namesList);

                string name;
                while (namesStream >> name) {
                    currentProbability += probability;
                    addCardToPack(pack, name, currentProbability, classLabel);
                }
            }
        }
    }

    file.close();
    return pack;
}

// Add card to pack
void addCardToPack(Pack* pack, const string& name, double probability, string cla) {
    Card* newCard = new Card{ name, probability, nullptr, cla };
    if (pack->head == nullptr) {
        pack->head = newCard;
    }
    else {
        Card* temp = pack->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newCard;
    }
    pack->num_card++;
}

// Free pack memory
void freePack(Pack* pack) {
    Card* current = pack->head;
    while (current != nullptr) {
        Card* next = current->next;
        delete current;
        current = next;
    }
    delete pack;
}

// Draw a card
void drawCard(Pack* pack) {
    if (rand() % 100 < pack->criticalProbability) {
        drawCard(pack->criticalPack); // Critical hit, draw from higher-level pack
    }
    else {
        Card* current = pack->head;
        double randNum = rand() % 100;

        while (current != nullptr && current->next != nullptr) {
            if (current->probability <= randNum && current->next->probability > randNum) {
                cout << "Drawn " << current->cla << " card: " << current->name << endl;
                return;
            }
            current = current->next;
        }

        // Handle the last card in the list
        if (current != nullptr) {
            cout << "Drawn " << current->cla << " card: " << current->name << endl;
        }
    }
}

// Draw a pack of cards
void drawPack(Pack* pack, int times) {
    for (int i = 0; i < times; ++i) {
        drawCard(pack);
    }
}

// Print menu
void printMenu() {
    cout << "===== Card Drawing Simulation =====\n";
    cout << "1. SSR Pack\n";
    cout << "2. SR Pack\n";
    cout << "3. S Pack\n";
    cout << "4. A Pack\n";
    cout << "===================================\n";
}

// Convert UTF-8 to GB2312
string UTF8ToGB(const char* str) {
    string result;
    WCHAR* strSrc;
    LPSTR szRes;

    // Get the size of temporary variables
    int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    strSrc = new WCHAR[i + 1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

    // Get the size of temporary variables
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
    szRes = new CHAR[i + 1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

    result = szRes;
    delete[] strSrc;
    delete[] szRes;

    return result;
}
