#ifndef _MENU_CPP_
#define _MENU_CPP_

#include "Menu.h"

const string IntException::errMsg() const
{
    return "Please enter a valid integer.\n";
}

const string RangeException::errMsg() const
{
    return "Please enter numbers in the valid range.\n";
}

UserMenu::UserMenu()
{
    initializeTree();
}

UserMenu::~UserMenu()
{
}

const bool UserMenu::initializeTree()
{
    Board aBoard("Chess", "Board", 7, 8.5, 5.0, {Review("Great game", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, 2, 70);
    userTree.insert(&aBoard);

    userTree.insert(new Board("Checkers", "Board", 2, 7.5, 4.0, {Review("Good game", 4.0, 4.0), Review("I like it", 4.0, 4.0)}, 2, 70));
    userTree.insert(new Board("Monopoly", "Board", 2, 6.5, 3.0, {Review("Okay game", 3.0, 3.0), Review("I don't mind it", 3.0, 3.0)}, 2, 70));
    userTree.insert(new Board("Risk", "Board", 2, 8.0, 4.5, {Review("Great game", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, 2, 70));

    userTree.insert(new Video("Call of Duty", "Video", 10, 9.0, 7.0, {Review("Great game", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, "Xbox", true));

    userTree.displayDetail();
    return true;
}

const int UserMenu::displayMenu()
{
    Review tempReview; // Review to insert
    string nameToFind = "";
    int accessibilityToFind = -1;
    int input = -1;
    while (input != 0)
    {
        cout << "\n1. View all games (simplified)\n2. View all games (detailed)\n3. Write a review for a game\n4. Insert a game\n5. Remove a game\n6. Remove all games\n0. Exit\n\n";
        input = getInputChoice(0, 6);

        switch (input)
        {
        case 1:
            cout << "Displaying game names, types, and accessibility levels.\n";
            userTree.displayQuick();
            break;
        case 2:
            cout << "Displaying games in detail including reviews from users.\n";
            userTree.displayDetail();
            break;
        case 3:
            cout << "Which game would you like to write a review for? Please enter the name and accessibility level:\n";
            cout << "Please enter the name: \n";
            cin >> nameToFind;
            cout << "You have entered " << nameToFind << ", now please enter the accessibility level: \n";
            accessibilityToFind = getInputChoice(0, 10);
            cout << "You have entered " << accessibilityToFind << ", let's see if this exists first:\n";
            if (userTree.findGame(nameToFind, accessibilityToFind) != nullptr)
            {
                cout << "This game exists, please enter your review for it:\n";
                userTree.findGame(nameToFind, accessibilityToFind)->getGame()->writeReview();
                cout << "Review added.\n";
            }
            else
            {
                cout << "This game does not exist.\n";
            }
            break;
        case 0:
            cout << "Exiting, thanks for your co-operation.\n";
            return 1;
            break;
        default:
            return 1;
            break;
        }
    }

    return 1;
}

const int UserMenu::getInputChoice(const int minInt, const int maxInt) const
{

    try
    {

        if (minInt > maxInt)
            throw RangeException();

        cout << "Please enter an integer between " << minInt << " and " << maxInt << ":\n\n";

        string input = "";
        cin >> input;

        int integer = stoi(input);
        if (integer < minInt || integer > maxInt)
            throw IntException();

        return integer;
    }
    catch (const IntException &e)
    {
        cerr << e.what();
        cin.clear();
        return getInputChoice(minInt, maxInt); // Recursively return until the user enters correct input in the range
    }
    catch (const RangeException &e)
    {
        cerr << e.what();
        cin.clear();
        return 0; // This function cannot work with ranges that have minimums above their maximums etc., so it will return instead of going infinitely
    }
}

#endif // _MENU_CPP_
