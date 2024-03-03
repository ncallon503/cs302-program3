#ifndef _GAME_CPP_
#define _GAME_CPP_
#include "Game.h"

// Parent Game Abstract Base Class

Game::Game() : name(""), genre(""), score(0), difficulty(0) {}

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
    string accessLevel = "";
    cout << "Enter a name: ";
    is >> src.name;
    cout << "Enter a genre: ";
    is >> src.genre;
    cout << "Enter an accessibility level: ";
    {
        if (!(cin >> accessLevel)) // The input stream does not throw an exception when the user enters a string instead of an integer so we need this as well
            throw RangeException();
    }
    src.accessibilityLevel = stoi(accessLevel);
    cout << "Accessibility entered is " << src.accessibilityLevel << "\n";
    cout << "Enter the first review: ";
    src.writeReview();
    src.update(); // Updates average ratings (right now this will only go off of one review)
    return is;
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

Board::Board() : Game() {}

Board::Board(const Board &src) : Game(src) {}

Board &Board::operator=(const Board &src)
{
    if (this != &src)
    {
        Game::operator=(src); // Calls Game operator = to save repetition then copies the unique data
    }
    return *this;
}

Board::~Board() {} // Same as parent, no dynamic memory so no need

ostream &operator<<(ostream &os, const Board &src)
{
    src.displayQuick();
    return os;
}

bool Board::displayQuick() const
{
    cout << "Type: Board Game, Name: " << name << ", Accessibility level: " << accessibilityLevel << "\n";
    return true;
}

bool Board::displayDetail() const
{
    cout << "Type: Board Game, Name: " << name << ", Genre: " << genre << ", accessibility: " << accessibilityLevel << ", Score: " << score << ", Difficulty: " << difficulty << "\n";
    cout << "Reviews: \n";
    for (unsigned int i = 0; i < reviews.size(); i++) // unsigned for vector
    {
        cout << reviews[i];
    }
    return true;
}

Game *Board::clone() const
{
    return new Board(*this); // I implemented this to be safe and never have two pointers pointing at the same memory with copy constructors and assignment operators
}

// End Board Class

// -----------------

// Derived Video Class

// End Video Class

// -----------------

// Derived Card Class

// End Card Class

// Review class for vectors

Review::Review() : description(""), difficulty(0), score(0) {}

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
