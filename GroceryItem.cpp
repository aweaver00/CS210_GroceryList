#include "GroceryItem.h"
#include <string>
using namespace std;

// constructors
GroceryItem::GroceryItem(string &name) : m_name(name), m_quantity(1)
{
}

// getter and setter functions for grocery items
string GroceryItem::getName() const {
    return m_name;
}

int GroceryItem::getQuantity() const {
    return m_quantity;
}

void GroceryItem::addItem() {
    // adds item to list, increment by one
    m_quantity += 1;
} 

// may not be needed?
void GroceryItem::removeItem() {
    // removes item from list, decrement by one
    m_quantity -= 1;
} 

