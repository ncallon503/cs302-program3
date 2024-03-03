#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <limits>
#include <exception>
#include <string>
#include <algorithm>

using namespace std;

// Exception for range of input
class IntException : public exception
{
public:
  const string errMsg() const;
};

class RangeException : public exception
{
public:
  const string errMsg() const;
};

class Review // The review class is used to store reviews in a vector in the Game class
{
public:
  Review();
  Review(const Review &src);
  Review &operator=(const Review &src);
  ~Review();

  friend istream &operator>>(istream &is, Review &src);
  friend ostream &operator<<(ostream &os, const Review &src);

  const double getDifficulty() const; // Limiting use of getters, but we need these 2 for the sum functions
  const double getScore() const;

private:
  string description; // User description of the game
  double difficulty;  // User difficulty score of the game
  double score;       // User score of the game (enjoyment)
};
class Game // The abstract base class Game is used for the derived classes Board, Video, and Sport
{
public:
  Game();
  Game(const string name, const string genre, const int accessibility, const double score, const double difficulty, vector<Review> someReviews); // Constructor with manual arguments
  Game(const Game &aGame);
  Game &operator=(const Game &aGame);
  virtual ~Game() = default; // Virtual destructor for derived classes to call their own destructors

  virtual bool displayQuick() const = 0;  // Simply displays the name of the game (const qualified for ostream)
  virtual bool displayDetail() const = 0; // Displays the game in detail like stats and overview, etc
  bool writeReview();                     // Writes a review prompting for user input which includes score and difficulty, this is the same for all derived classes so it does not use virtual or dynamic binding

  friend ostream &operator<<(ostream &os, const Game &src); // The overloaded ostream operator displays the game simply and not in detail, so just its name and type of game
  friend istream &operator>>(istream &is, Game &src);       // The overloaded istream operator prompts the user to enter details for the game and leave a review

  // For this assignment we will use two search keys, they will be the name of the game and the average score of the game (accumulated from all the reviews).
  bool operator==(const string name); // Compares the game's name to a string that is passed in
  bool operator==(const Game &op2);   // Compares two games and returns true if same name
  bool operator!=(const string name); // Same but inverse as above
  bool operator!=(const Game &op2);   // ^^^
  bool operator>(const string name);  // Compares name alphabetically and returns true if greater
  bool operator>(const Game &op2);    // Game object version ^
  bool operator>=(const string name); // Compares name alphabetically and returns true if greater or equal
  bool operator>=(const Game &op2);   // Game object version ^
  bool operator<(const string name);  // Compares name alphabetically and returns true if less
  bool operator<(const Game &op2);    // Game object version ^
  bool operator<=(const string name); // Compares name alphabetically and returns true if less or equal
  bool operator<=(const Game &op2);   // Game object version ^

  const string getName() const;       // Getter for name, this is needed for recursion in the removeHelper Tree function
  const int getAccessibility() const; // Getter for score, we use this for the insert to find a game with similar rating (if exists), and if exists, then we insert alphabetically by name and same rating

  virtual Game *clone() const = 0; // I made a clone method for the node constructors to use their own memory

protected:
  double sumDifficulty(unsigned int index); // Helper function that sums difficulty of all reviews
  double sumScore(unsigned int index);      // Helper function that sums score of all reviews

  bool update(); // Updates average difficulty and score after a review is added

  bool displayReviews(const int index) const; // Displays all reviews for a game recursively

  string name;            // Name of the game
  string genre;           // Genre of the game
  int accessibilityLevel; // Accessibility level of the game (1-10)
  double score;           // Score of 1-10 how good the game is based on reviews
  double difficulty;      // Score of 1-10 on how difficult the game is
  vector<Review> reviews; // Vector of reviews containing description, difficulty, and score

private:
};

class Board : public Game // Child of Game Class
{
public:
  Board();
  Board(const string name, const string genre, const int accessibility, const double score, const double difficulty, vector<Review> someReviews, const int numPlayers, const int averageTime); // Constructor with manual arguments
  Board(const Board &src);
  Board &operator=(const Board &src);
  ~Board();

  bool displayQuick() const;
  bool displayDetail() const;

  friend ostream &operator<<(ostream &os, const Board &src);
  friend istream &operator>>(istream &is, Board &src);

  Game *clone() const; // Clone used for separating memory management
private:
  int numPlayers;  // Recommended number of players for board game
  int averageTime; // Average duration of how long the games last
};

// class Video : public Game // Child of Game Class
// {
// public:
//   Video();
//   Video(const Video &src);
//   Video &operator=(const Video &src);
//   ~Video();

//   bool displayQuick() const;
//   bool displayDetail() const;

// private:
// };

// class Sport : public Game // Child of Game Class
// {
// public:
//   Sport();
//   Sport(const Sport &src);
//   Sport &operator=(const Sport &src);
//   ~Sport();

//   bool displayQuick() const;
//   bool displayDetail() const;

// private:
// };

#endif