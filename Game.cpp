/* All the classes use dynamic binding to simplify the amount of code and
avoid repetition, and I overloaded the operators to compare alphabetically
in addition to having the Tree compare their accessibility level to sort them
into their own "subtrees". The istream operator could not be made virtual so
I made a virtual read function that is called so dynamic binding can actually take
place and the correct child virtual class functions are called so things can be
entered like equipment for a sport game, number of players for a board game, 18+
for a video game and more. I also made a clone() method which returns a pointer
new memory of the child class so the smart pointers could not point to a same
object and cause weird interactions for Node copy constructors and assignment
operators. */

#ifndef _GAME_CPP_
#define _GAME_CPP_
#include "Game.h"

// Parent Game Abstract Base Class

Game::Game() : name(""), genre(""), score(0), difficulty(0) {}

Game::Game(const string name, const string genre, const int accessibility, const double score, const double difficulty, const vector<Review> someReviews) : name(name), genre(genre), accessibilityLevel(accessibility), score(score), difficulty(difficulty), reviews(someReviews) {}

Game::Game(const Game &aGame) : name(aGame.name), genre(aGame.genre), accessibilityLevel(aGame.accessibilityLevel), score(aGame.score), difficulty(aGame.difficulty), reviews(aGame.reviews) {}

Game &Game::operator=(const Game &aGame)
{
    if (this != &aGame)
    {
        name = aGame.name;
        genre = aGame.genre;
        score = aGame.score;
        difficulty = aGame.difficulty;
        reviews = aGame.reviews;
        accessibilityLevel = aGame.accessibilityLevel;
    }
    return *this;
}

ostream &operator<<(ostream &os, const Game &src)
{
    src.displayQuick();
    return os;
}
istream &operator>>(istream &is, Game &src)
{
    src.read(is);
    return is;
}

bool Game::read(istream &is)
{
    string accessLevel = "";
    cout << "Enter a name: ";
    is >> name;
    cout << "Enter a genre: ";
    is >> genre;
    cout << "Enter an accessibility level between 1 and 10: ";
    {
        if (!(cin >> accessLevel)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
            throw RangeException();
    }
    if (!isdigit(accessLevel[0])) // Check for valid input
    {
        cout << "Accessibility must be a number. ";
        throw RangeException();
    }
    if (stoi(accessLevel) < 0 || stoi(accessLevel) > 10) // Check range as well
    {
        cout << "Accessibility must be between 0 and 10.";
        throw RangeException();
    }
    accessibilityLevel = stoi(accessLevel);
    cout << "Entering first review ---v:\n";
    writeReview();
    update(); // Updates average ratings (right now this will only go off of one review)
    return true;
}

bool Game::operator==(const string name) // This one will only compare the name.
{
    return this->name == name; // Returns true if matching, false if not
}

bool Game::operator==(const Game &src)
{
    return name == src.name; // Returns true if matches other game's name, false if not
}

bool Game::operator!=(const string name)
{
    return this->name != name; // Returns true if not matching, false if matching
}

bool Game::operator!=(const Game &src)
{
    return name != src.name; // Returns true if does not match other game's name, false if it does
}

bool Game::operator>(const Game &src)
{
    return name[0] > src.name[0]; // Only returns true if both are greater, false if not
}

bool Game::operator>(const string name)
{
    return this->name[0] > name[0]; // Only checks for a string
}

bool Game::operator>=(const Game &src)
{
    return name[0] >= src.name[0]; // Returns true if both are greater or equal, false if not
}

bool Game::operator>=(const string name)
{
    return this->name[0] >= name[0]; // Same as above but for a string passed in
}

bool Game::operator<(const Game &src)
{
    return name[0] < src.name[0]; // Returns true if both are less, false if not
}

bool Game::operator<(const string name)
{
    return this->name[0] < name[0]; // Same as above but for a string passed in
}

bool Game::operator<=(const Game &src)
{
    return name[0] <= src.name[0]; // Returns true if both are less or equal, false if not
}

bool Game::operator<=(const string name)
{
    return this->name[0] <= name[0]; // Same as above but for a string passed in
}

bool Game::writeReview()
{
    Review temp;
    try
    {
        if (!(cin >> temp)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
            throw RangeException();
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of bad input
        return writeReview();                                // Recursively return until valid input is entered
    }
    reviews.push_back(temp); // If passed through all of that, successfully adds review
    update();                // Updates the difficulty and score
    return true;
}

bool Game::displayReviews(const int index) const
{
    if (index == reviews.size()) // Base case for end of vector
    {
        return true;
    }
    cout << reviews[index];           // Display the review
    return displayReviews(index + 1); // Recursively display the next review
}

double Game::sumDifficulty(unsigned int index)
{
    if (index == reviews.size()) // Base case for end of vector
    {
        return 0;
    }
    return reviews[index].getDifficulty() + sumDifficulty(index + 1); // Recursively return difficulty + next difficulty
}

double Game::sumScore(unsigned int index)
{
    if (index == reviews.size()) // Base case for end of vector
    {
        return 0;
    }
    return reviews[index].getScore() + sumScore(index + 1); // Recursively return difficulty + next difficulty
}

bool Game::update()
{
    if (reviews.size() == 0) // If there are no reviews, set difficulty and score to 0 and return false (also avoids 0 division)
    {
        difficulty = 0;
        score = 0;
        return false;
    }
    difficulty = sumDifficulty(0) / reviews.size(); // Sum of all difficulties divided by number of reviews
    score = sumScore(0) / reviews.size();           // Sum of all scores divided by number of reviews
    return true;
}

const string Game::getName() const
{
    return name; // A necessary getter for the removeHelper function, we use the operators otherwise
}

const int Game::getAccessibility() const
{
    return accessibilityLevel; // We use this to find where to insert due to having 2 keys
}

// End Parent Class

// -----------------

// Derived Board Class

Board::Board() : Game(), numPlayers(0), averageTime(0) {}

Board::Board(const string name, const string genre, const int accessibility, const double score, const double difficulty, const vector<Review> someReviews, const int numPlayers, const int averageTime) : Game(name, genre, accessibility, score, difficulty, someReviews), numPlayers(numPlayers), averageTime(averageTime) {}

Board::Board(const Board &src) : Game(src), numPlayers(src.numPlayers), averageTime(src.averageTime) {}

Board &Board::operator=(const Board &src)
{
    if (this != &src)
    {
        Game::operator=(src); // Calls Game operator = to save repetition then copies the unique data
        numPlayers = src.numPlayers;
        averageTime = src.averageTime;
    }
    return *this;
}

Board::~Board() {} // Same as parent, no dynamic memory so no need

ostream &operator<<(ostream &os, const Board &src)
{
    src.displayQuick();
    return os;
}

// istream &operator>>(istream &is, Board &src)
// {
//     string numPlayers = "", averageTime = "";
//     cout << "Board version called";
//     Game *temp = &src;
//     is >> *temp;

//     cout << "Enter a number of players recommended above 0: ";
//     if (!(cin >> numPlayers)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
//         throw RangeException();
//     if (stoi(numPlayers) <= 0) // Check range as well
//     {
//         cout << "Number of players must be above 0.";
//         throw RangeException();
//     }
//     src.numPlayers = stoi(numPlayers);

//     cout << "Enter the average duration this board game takes (in minutes): ";
//     {
//         if (!(cin >> averageTime)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
//             throw RangeException();
//     }
//     if (stoi(averageTime) <= 0) // Check range as well
//     {
//         cout << "Board game must take above 0 minutes.";
//         throw RangeException();
//     }
//     src.averageTime = stoi(averageTime);
//     return is;
// }

bool Board::read(istream &is)
{
    string numPlayersString = "", averageTimeString = "";
    Game::read(is);
    cout << "Enter a number of players recommended above 0: ";
    if (!(cin >> numPlayersString)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
        throw RangeException();
    if (stoi(numPlayersString) <= 0) // Check range as well
    {
        cout << "Number of players must be above 0.";
        throw RangeException();
    }
    numPlayers = stoi(numPlayersString);

    cout << "Enter the average duration this board game takes (in minutes): ";
    {
        if (!(cin >> averageTimeString)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
            throw RangeException();
    }
    if (stoi(averageTimeString) <= 0) // Check range as well
    {
        cout << "Board game must take above 0 minutes.";
        throw RangeException();
    }
    averageTime = stoi(averageTimeString);
    return true;
}

bool Board::displayQuick() const
{
    cout << "Name: " << name << ", Type: Board Game, Accessibility level: " << accessibilityLevel << "\n";
    return true;
}

bool Board::displayDetail() const
{
    cout << "Name: " << name << ", Type: Board Game, Genre: " << genre << ", accessibility: " << accessibilityLevel << ", Average Score: " << score << ", Average Difficulty: " << difficulty << "\n";
    cout << "Number of players: " << numPlayers << ", Average game time: " << averageTime << " minutes\n";
    cout << "Reviews: \n";
    displayReviews(0); // Recursively displays the reviews
    return true;
}

Game *Board::clone() const
{
    return new Board(*this); // I implemented this to be safe and never have two pointers pointing at the same memory with copy constructors and assignment operators
}

// End Board Class

// -----------------

// Derived Video Class

Video::Video() : Game(), console(""), eighteenPlus(false) {}

Video::Video(const string name, const string genre, const int accessibility, const double score, const double difficulty, const vector<Review> someReviews, const string console, const bool eighteenPlus) : Game(name, genre, accessibility, score, difficulty, someReviews), console(console), eighteenPlus(eighteenPlus) {}

Video::Video(const Video &src) : Game(src), console(src.console), eighteenPlus(src.eighteenPlus) {}

Video &Video::operator=(const Video &src)
{
    if (this != &src)
    {
        Game::operator=(src); // Calls Game operator = to save repetition then copies the unique data
        console = src.console;
        eighteenPlus = src.eighteenPlus;
    }
    return *this;
}

Video::~Video() {} // Same as parent, no dynamic memory so no need

ostream &operator<<(ostream &os, const Video &src)
{
    src.displayQuick();
    return os;
}

// istream &operator>>(istream &is, Video &src)
// {
//     cout << "Video version called\n";
//     string eighteenPlus = "";
//     Game *temp = &src;
//     is >> *temp;

//     cout << "Enter a console: ";
//     is >> src.console;
//     cout << "Is this game rated 18+? (1 for yes, 0 for no): ";
//     {
//         if (!(cin >> eighteenPlus)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
//             throw RangeException();
//     }
//     if (stoi(eighteenPlus) != 0 && stoi(eighteenPlus) != 1) // Check for valid input as well
//     {
//         cout << "Must be 0 or 1.";
//         throw RangeException();
//     }
//     src.eighteenPlus = stoi(eighteenPlus);
//     cout << "Reached this\n";
//     return is;
// }

bool Video::read(istream &is)
{
    string eighteenPlus = "";
    Game::read(is);
    cout << "Enter a console: ";
    is >> console;
    cout << "Is this game rated 18+? (1 for yes, 0 for no): ";
    {
        if (!(cin >> eighteenPlus)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
            throw RangeException();
    }
    if (stoi(eighteenPlus) != 0 && stoi(eighteenPlus) != 1) // Check for valid input as well
    {
        cout << "Must be 0 or 1.";
        throw RangeException();
    }
    eighteenPlus = stoi(eighteenPlus);
    return true;
}

bool Video::displayQuick() const
{
    cout << "Name: " << name << ", Type: Video Game, Accessibility level: " << accessibilityLevel << "\n";
    return true;
}

bool Video::displayDetail() const
{
    string yesOrNo = this->eighteenPlus ? "Yes" : "No"; // Displays yes or no instead of 0 or 1
    cout << "Name: " << name << ", Type: Video Game, Genre: " << genre << ", Accessibility: " << accessibilityLevel << ", Average Score: " << score << ", Average Difficulty: " << difficulty << "\n";
    cout << "Console: " << console << ", 18+: " << yesOrNo << "\n";
    cout << "Reviews: \n";
    displayReviews(0); // Recursively displays the reviews
    return true;
}

Game *Video::clone() const
{
    return new Video(*this); // Implemented to be safe and not share memory
}

// End Video Class

// -----------------

// Derived Sport Class

Sport::Sport() : Game(), equipment{}, positions{} {}

Sport::Sport(const string name, const string genre, const int accessibility, const double score, const double difficulty, const vector<Review> someReviews, const vector<string> equipment, const vector<string> positions) : Game(name, genre, accessibility, score, difficulty, someReviews), equipment(equipment), positions(positions) {}

Sport::Sport(const Sport &src) : Game(src), equipment(src.equipment), positions(src.positions) {}

Sport &Sport::operator=(const Sport &src)
{
    if (this != &src)
    {
        Game::operator=(src); // Calls Game operator = to save repetition then copies the unique data
        equipment = src.equipment;
        positions = src.positions;
    }
    return *this;
}

Sport::~Sport() {} // Same as parent, no dynamic memory so no need

ostream &operator<<(ostream &os, const Sport &src)
{
    src.displayQuick();
    return os;
}

// istream &operator>>(istream &is, Sport &src)
// {
//     string equipPiece = "", aPosition = "";
//     Game *temp = &src;
//     is >> *temp;

//     src.addEquipment(); // Adds equipment recursively from user input
//     src.addPositions(); // Adds positions recursively from user input

//     return is;
// }

bool Sport::read(istream &is)
{
    Game::read(is);
    addEquipment(); // Adds equipment recursively from user input
    addPositions(); // Adds positions recursively from user input
    return true;
}

const int Sport::addEquipment()
{
    string equipPiece = "";
    cout << "Enter a piece of equipment for the sport, or \"stop\" to stop.\n";
    cin >> equipPiece;
    if (equipPiece == "stop") // If the user enters -1, we return 0
    {
        return 0;
    }
    equipment.push_back(equipPiece); // Otherwise we add the equipment to the vector

    return 1 + addEquipment(); // Returns 1 + the next piece of equipment
}

const int Sport::addPositions()
{
    string aPosition = "";
    cout << "Enter a position for the sport, or \"stop\" to stop.\n";
    cin >> aPosition;
    if (aPosition == "stop") // If the user enters -1, we return 0
    {
        return 0;
    }
    positions.push_back(aPosition); // Otherwise we add the position to the vector

    return 1 + addPositions(); // Returns 1 + the next position
}

bool Sport::displayQuick() const
{
    cout << "Name: " << name << ", Type: Sport, Accessibility level: " << accessibilityLevel << "\n";
    return true;
}

bool Sport::displayDetail() const
{
    cout << "Name: " << name << ", Type: Sport, Genre: " << genre << ", Accessibility: " << accessibilityLevel << ", Average Score: " << score << ", Average Difficulty: " << difficulty << "\n";
    cout << "Equipment: \n";
    displayEquipment(0); // Recursively displays the equipment
    cout << "\nPositions: \n";
    displayPositions(0); // Recursively displays the positions
    cout << "\nReviews: \n";
    displayReviews(0); // Recursively displays the reviews
    return true;
}

bool Sport::displayEquipment(const int index) const
{
    if (index == equipment.size()) // Base case for end of vector
    {
        return true;
    }
    cout << equipment[index] << "\t";   // Display the equipment
    return displayEquipment(index + 1); // Recursively display the next piece of equipment
}

bool Sport::displayPositions(const int index) const
{
    if (index == positions.size()) // Base case for end of vector
    {
        return true;
    }
    cout << positions[index] << "\t";   // Display the position
    return displayPositions(index + 1); // Recursively display the next position
}

Game *Sport::clone() const
{
    return new Sport(*this); // Implemented to be safe and not share memory
}

// End Sport Class

// Review class for vectors

Review::Review() : description(""), difficulty(0), score(0) {}

Review::Review(const string description, const double difficulty, const double score) : description(description), difficulty(difficulty), score(score) {}

Review::Review(const Review &src) : description(src.description), difficulty(src.difficulty), score(src.score) {}

Review &Review::operator=(const Review &src) // We still implement copy constructor and assignment operator for vector assignment operator
{
    if (this != &src)
    {
        description = src.description;
        difficulty = src.difficulty;
        score = src.score;
    }
    return *this;
}

Review::~Review() {} // As always no dynamic memory

ostream &operator<<(ostream &os, const Review &src)
{
    os << "Description: " << src.description << ", Difficulty: " << src.difficulty << ", Score: " << src.score << "\n";
    return os;
}

istream &operator>>(istream &is, Review &src)
{
    string difficulty = "", score = "";
    cout << "Enter a description: ";
    is >> src.description;
    cout << "Enter a difficulty: ";
    is >> difficulty;
    if (stoi(difficulty) < 0 || stoi(difficulty) > 10) // Use this for safe conversions
    {
        throw RangeException();
    }
    src.difficulty = stoi(difficulty);
    cout << "Enter a score: ";
    is >> score;
    if (stoi(score) < 0 || stoi(score) > 10)
    {
        throw RangeException();
    }
    src.score = stoi(score);
    return is;
}

const double Review::getDifficulty() const
{
    return difficulty;
}

const double Review::getScore() const
{
    return score;
}

// End Review Class

#endif
