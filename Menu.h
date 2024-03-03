/* Similar to program #2, I use a user menu to replace main for the user interface
and inside of it I have a private userTree which the menu accesses and manages
through public functions to edit and view the tree. */

#ifndef _MENU_H_
#define _MENU_H_

#include "Tree.h"

class UserMenu
{
public:
    UserMenu();
    ~UserMenu();
    const bool greeting() const; // Greets the user and describes what the menu does
    const int displayMenu();     // Displays the menu and handles user input (non-const because it modifies data throughout the entire program)

private:
    const int getInputChoice(const int minInt, const int maxInt) const; // Gets user input as an integer between a max and minimum value, recursively calls until valid input entered
    const bool initializeTree();                                        // This initializes the tree with different types of games pre-defined
    Tree userTree;                                                      // Tree that the menu manages with user input
};

#endif // _MENU_H_
