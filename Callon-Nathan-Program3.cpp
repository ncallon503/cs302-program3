/* Nathan Callon, CS302, 3/2/2024, Karla Fant
For this program I heavily focused on dynamic binding and making the best use of it, and using it
to make my program not just more flexible and avoiding repetition but making the menu able to do
things it wasn't before such as using upcasting with base class pointers to child objects to
perform tree operations and have the overloaded operators and virtual overriden functions perform
a bulk of the work while also making the code look simpler and more understandable (for the client
at least). I chose to have a Parent Abstract Base Class named Game, and the children are the Board class,
Video class, and Sport class which all have their own unique properties, all of which are managed by
a Node class, that is managed by a Tree class, that is managed by a UserMenu class. */

#include "Game.h"
#include "Tree.h"
#include "Menu.h"

int main()
{
    UserMenu aMenu;
    aMenu.greeting();
    aMenu.displayMenu();

    return 0;
}