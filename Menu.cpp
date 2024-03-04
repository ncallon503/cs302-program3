/* I made specific exceptions being IntException and RangeException telling
the user what input the program is desiring and what to input, which then recursively
calls the menu or the option again so the user can enter correct input. I put try
and catch blocks so the program would never explode or terminate instantly, the
menu would handle these cases and tell the user what to do to continue the program.
The user technically has 7 menu options, being viewing all games in a simplified way,
viewing them detailed which includes reviews and specifics of the child classes,
writing a review for a game by finding it from name and accessibility level, inserting
one of the 3 types of child Games (Board, Video or Sport), removing a specific game
by name and accessibility level, removing all the games in the tree, or exiting. */

#ifndef _MENU_CPP_
#define _MENU_CPP_

#include "Menu.h"

const string IntException::errMsg() const
{
    return "Please enter a positive integer data type.\n";
}

const string RangeException::errMsg() const
{
    return "Please enter numbers in the valid range.\n";
}

const string MinMaxException::errMsg() const
{
    return "The minimum value cannot be greater than the maximum value.\n";
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
    Board board1("Chess", "Board", 7, 8.5, 5.0, {Review("It is much more difficult than checkers.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, 2, 70);
    userTree.insert(&board1); // Repetitive, but I chose to insert by reference to avoid memory leaks

    Board board2("Checkers", "Board", 2, 7.5, 4.0, {Review("It's fun! Unlike Chess :) ", 4.0, 4.0), Review("I like it", 4.0, 4.0)}, 2, 70);
    userTree.insert(&board2);

    Board board3("Monopoly", "Board", 2, 6.5, 3.0, {Review("Very fun but I lost some friendships.", 3.0, 3.0), Review("I don't mind it", 3.0, 3.0)}, 2, 70);
    userTree.insert(&board3);

    Board board4("Risk", "Board", 2, 8.0, 4.5, {Review("Fun board game :)", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, 2, 70);
    userTree.insert(&board4);

    Video video1("Halo", "Video", 10, 9.0, 7.0, {Review("Aliens died. Much fun.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, "Xbox", true);
    userTree.insert(&video1);

    Video video2("Call of Duty", "Video", 10, 9.0, 7.0, {Review("My friends are mad but not my problem.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, "Xbox", true);
    userTree.insert(&video2);

    Video video3("League", "Video", 10, 9.0, 7.0, {Review("Queued with my friends and was a good time.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, "PC", false);
    userTree.insert(&video3);

    Video video4("Minecraft", "Video", 10, 9.0, 7.0, {Review("We made a castle :)", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, "Universal", false);
    userTree.insert(&video4);

    Sport sport1("Football", "Sport", 10, 9.0, 7.0, {Review("Best high school experience of my life.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, {"Cleats", "Shoulderpads", "Helmet"}, {"Quarterback", "Runningback", "Wide Receiver"});
    userTree.insert(&sport1);

    Sport sport2("Soccer", "Sport", 10, 9.0, 7.0, {Review("It's really fun playing with my friends.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, {"Cleats", "Shin Guards", "Jersey"}, {"Striker", "Midfielder", "Defender"});
    userTree.insert(&sport2);

    Sport sport3("Basketball", "Sport", 10, 9.0, 7.0, {Review("Fun playing out front of my parent's house :) ", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, {"Sneakers", "Jersey", "Shorts"}, {"Point Guard", "Shooting Guard", "Small Forward"});
    userTree.insert(&sport3);

    Sport sport4("Baseball", "Sport", 10, 9.0, 7.0, {Review("Baseball is fun if you are playing with your friends.", 5.0, 5.0), Review("I love it", 5.0, 5.0)}, {"Cleats", "Jersey", "Bat"}, {"Pitcher", "Catcher", "First Baseman"});
    userTree.insert(&sport4);

    return true;
}

const bool UserMenu::greeting() const
{
    cout << "Welcome to the game menu. This is where you can find games to suit your needs and also add games that you like,\n"
         << "write reviews for games and remove games that you dislike.\n"
         << "You can also view all games from a first glance or view the intricacies of them.\n"
         << "Please enter a number from 0 to 6 to choose an option.\n";
    return true;
}

const int UserMenu::displayMenu()
{
    try
    {
        Review tempReview; // Review to insert
        string nameToFind = "";
        Game *gameToAdd = nullptr;
        int accessibilityToFind = -1;
        int input = -1;
        int gameType = -1;
        while (input != 0)
        {
            cout << "\n1. View all games (simplified)\n2. View all games (detailed)\n3. Write a review for a game\n4. Insert a game\n5. Remove a game\n6. Remove all games\n0. Exit\n\n";
            input = getInputChoice(0, 6);

            switch (input)
            {
            case 1:
                cout << "Displaying game names, types, and accessibility levels.\n\n";
                userTree.displayQuick();
                break;
            case 2:
                cout << "Displaying games in detail including reviews from users.\n\n";
                userTree.displayDetail();
                break;
            case 3:
                cout << "Which game would you like to write a review for? Please enter the name and accessibility level:\n";
                cout << "Please enter the name: \n";
                cin >> nameToFind;
                cout << "You have entered " << nameToFind << " for the name, now please enter the accessibility level: \n";
                accessibilityToFind = getInputChoice(0, 10);
                cout << "You have entered accessibility level of " << accessibilityToFind << ", let's see if this exists first:\n";
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
            case 4:
                cout << "Please enter the type of game you would like to insert:\n 1 for Board, 2 for Video, 3 for Sport:\n";
                gameType = getInputChoice(1, 3);
                switch (gameType)
                {
                case 1:
                    cout << "You've chose to insert a Board game.\n";
                    gameToAdd = new Board();
                    break;
                case 2:
                    cout << "You've chose to insert a Video game.\n";
                    gameToAdd = new Video();
                    break;
                case 3:
                    cout << "You've chose to insert a Sport game.\n";
                    gameToAdd = new Sport();
                    break;
                default:
                    cout << "Invalid input.\n";
                    break;
                }
                cin >> *gameToAdd; // This uses dynamic binding to call the correct read function for the derived class and save lots of time and repetition
                userTree.insert(gameToAdd);
                delete gameToAdd; // The insert creates a copy managing separate memory so we do still need to deallocate this after the insert function
                gameToAdd = nullptr;
                break;
            case 5:
                cout << "Which game would you like to remove? Please enter the name and accessibility level:\n";
                cout << "Please enter the name: \n";
                cin >> nameToFind;
                cout << "You have entered " << nameToFind << "for the name, now please enter the accessibility level: \n";
                accessibilityToFind = getInputChoice(0, 10);
                cout << "You have entered accessibility level of " << accessibilityToFind << ", attempting to remove the game:\n";
                if (userTree.remove(nameToFind, accessibilityToFind))
                {
                    cout << "Game removed.\n";
                }
                else
                {
                    cout << "Game not found.\n";
                }
                break;
            case 6:
                cout << "Removing all games.\n";
                userTree.removeAll();
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
    }
    catch (const IntException &e)
    {
        cerr << e.errMsg();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return displayMenu(); // Tries to display the menu again after catching this exception and clearing the input stream
    }
    catch (const RangeException &e)
    {
        cerr << e.errMsg();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return displayMenu(); // Same as above but for range error
    }
    catch (...) // Catch other exceptions such as stoi failure, etc
    {
        cerr << "An unknown error occurred, please try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return displayMenu();
    }
    return 1;
}

const int UserMenu::getInputChoice(const int minInt, const int maxInt) const
{
    try
    {
        if (minInt > maxInt)
            throw RangeException();

        cout << "Please enter an integer between " << minInt << " and " << maxInt << ":\n";

        string input = "";
        cin >> input;

        if (!all_of(input.begin(), input.end(), ::isdigit)) // Check if input is all digits
            throw IntException();

        int integer = stoi(input);
        if (integer < minInt || integer > maxInt)
            throw RangeException();

        return integer;
    }
    catch (const IntException &e)
    {
        cerr << e.errMsg();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return getInputChoice(minInt, maxInt); // Recursively return until the user enters correct input in the range
    }
    catch (const RangeException &e)
    {
        cerr << e.errMsg();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return getInputChoice(minInt, maxInt);
    }
    catch (const MinMaxException &e)
    {
        cerr << e.errMsg();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; // This function cannot work with ranges that have minimums above their maximums etc., so it will return instead of going infinitely
    }
    catch (...) // Catch other exceptions such as stoi failure, etc
    {
        cerr << "An unknown error occurred, please try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
}

#endif // _MENU_CPP_
