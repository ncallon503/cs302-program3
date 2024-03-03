/* The UserMenu can essentially replace the main function because all the menu
functionality is definied within this class. There are also exceptions for types
of errors that will be thrown so the user can know what input is wrong and how
to react correctly. */

#ifndef _MENU_H_
#define _MENU_H_

#include "Tree.h"

class UserMenu
{
public:
    UserMenu();
    ~UserMenu();
    const int displayMenu(); // Displays initial menu

private:
    const int getInputChoice(const int minInt, const int maxInt) const; // Gets user input as an integer between a max and minimum value, recursively calls until valid input entered
    const bool initializeTree();                                        // This initializes the tree with different types of games pre-defined
    Tree userTree;                                                      // Tree that the menu manages with user input
};

#endif // _MENU_H_
