// header guard to protect against multiple include
#ifndef PROJECT_3_GROCERY_ITEM 
#define PROJECT_3_GROCERY_ITEM
#include <string>
using namespace std;

class GroceryItem //define class GroceryItem
{
private:
    // Private member variables
    string m_name; // description/name of grocery item
    int m_quantity;     // qty of grocery item
    

public:
    // constructors
    GroceryItem(string& name);

    // getter and setter functions for grocery items
    string getName() const;
    int getQuantity() const;

    void addItem();    // adds item to list, increment by one?
    
    //may not be needed?
    void removeItem(); // removes item from list, decrement by one? 
    
};

#endif
