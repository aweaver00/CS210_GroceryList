#include "GroceryItem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

map<string, GroceryItem> calcFrequency(ifstream &inFS)
{
    map<string, GroceryItem> groceryMap;
    string itemName;

    // read through file of grocery items and calculate _Query_perf_frequency
    while (inFS >> itemName)
    {
        auto p_item = groceryMap.find(itemName);

        if (p_item == groceryMap.end())
        {
            GroceryItem newItem(itemName);
            groceryMap.emplace(itemName, newItem);
        }
        else
        {
            p_item->second.addItem();
        }
    }

    return groceryMap;
}

// function to print visual
void printVisual(map<string, GroceryItem> &groceryMap)
{
    for (auto item : groceryMap)
    {
        cout << setw(15) << right << item.second.getName() << " ";
        for (int i = 0; i < item.second.getQuantity(); ++i)
        {
            cout << "*";
        }
        cout << endl;
    }
}

// function to look for user specified item and print the total qty
void printSpecifiedItem(map<string, GroceryItem> &groceryMap)
{
    string userItem;

    cout << "Please enter the item you want to search: ";
    cin >> userItem;

    // ensure user input is in correct case format
    if (!userItem.empty())
    {
        for (char &c : userItem)
        {
            // Convert the character to lowercase if it's an uppercase letter
            c = std::tolower(c);
        }

        userItem[0] = std::toupper(userItem[0]);
    }

    auto p_item = groceryMap.find(userItem);

    // if users item exists then print the frequency else print " has 0 entries"
    if (p_item == groceryMap.end())
    {
        cout << userItem << " has 0 entries." << endl;
    }
    else
    {
        cout << userItem << " has " << p_item->second.getQuantity() << " entries." << endl;
    }
}

// function to print list of  aggregated items and  qty
void printAllItems(map<string, GroceryItem> &groceryMap)
{
    for (auto item : groceryMap)
    {
        cout << item.second.getName() << " " << item.second.getQuantity() << endl;
    }
}

bool menu(map<string, GroceryItem> &groceryMap)
{
    int userOption;

    cout << "\n**** WELCOME TO CORNER GROCER! ****" << endl;
    cout << "1: Get item frequency" << endl;
    cout << "2: Print all items" << endl;
    cout << "3: Print visual of item frequency" << endl;
    cout << "4: Exit" << endl;
    cout << "Please Enter an option (1-4): ";
    // cin >> userOption;

    try
    {
        // check that userOption is an int
        if (!(cin >> userOption))
        {
            throw runtime_error("Invalid input. Please enter an integer (1-4).");
        }
        // if it is int, continue
        switch (userOption)
        {
        case 1:
            printSpecifiedItem(groceryMap);
            break;
        case 2:
            printAllItems(groceryMap);
            break;
        case 3:
            printVisual(groceryMap);
            break;
        case 4:
            return true;
        default:
            cerr << "Invalid option. Please enter a valid option (1-4)." << endl;
            break;
        }
    }
    catch (const std::exception &e)
    {
        // handle exception and display error message
        cerr << "Error: " << e.what() << endl;
        cin.clear();             // Clear the error state
        cin.ignore(10000, '\n'); // Ignore invalid input up to a newline character
    }

    return false;
}

int main()
{
    ifstream inFS;  // input file stream
    ofstream outFS; // output file stream
    string inFile = "groceries.txt";
    string outFile = "frequency.dat";

    cout << "Opening " << inFile << " file..." << endl;

    // open source file with grocery items
    inFS.open(inFile);
    if (!inFS.is_open())
    {
        cout << "**ERROR** trying to open " << inFile << endl;
        return 1; // stops and notifies user of error
    }

    map<string, GroceryItem> groceryMap = calcFrequency(inFS);

    // create output file
    cout << "Creating " << outFile << " file..." << endl;

    // udpate frequency.dat
    outFS.open(outFile);
    if (!outFS.is_open())
    {
        cout << "**ERROR** trying to open " << outFile << endl;
        return 1; // stops and notifies user of error
    }

    // create ouput file for all items and
    for (auto item : groceryMap)
    {
        outFS << item.second.getName() << " " << item.second.getQuantity() << endl;
    }

    inFS.close();
    outFS.close();

    bool shouldQuit = false;

    while (!shouldQuit)
    {
        shouldQuit = menu(groceryMap);
    }

    cout << "Goodbye!" << endl;
}
