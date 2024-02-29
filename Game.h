#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <limits>
#include <exception>
#include <string>

using namespace std;

class RangeException : public exception
{
  virtual const char *what() const throw()
  {
    return "Invalid input. For the rating and difficulty please remember to enter an integer from 1 to 10.";
  }
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
  bool operator>(const string name);  // Compares name alphabetically and rating numerically and returns true if greater
  bool operator>(const Game &op2);    // Game object version ^
  bool operator>=(const string name); // Compares name alphabetically and rating numerically and returns true if greater or equal
  bool operator>=(const Game &op2);   // Game object version ^
  bool operator<(const string name);  // Compares name alphabetically and rating numerically and returns true if less
  bool operator<(const Game &op2);    // Game object version ^
  bool operator<=(const string name); // Compares name alphabetically and rating numerically and returns true if less or equal
  bool operator<=(const Game &op2);   // Game object version ^

  const string getName() const; // Getter for name, only one that is needed, for recursion in the removeHelper Tree function

  virtual Game *clone() const = 0; // I made a clone method for the node constructors to use their own memory

protected:
  double sumDifficulty(int index); // Helper function that sums difficulty of all reviews
  double sumScore(int index);      // Helper function that sums score of all reviews

  bool update(); // Updates average difficulty and score after a review is added

  string name;            // Name of the game
  string genre;           // Genre of the game
  double score;           // Score of 1-10 how good the game is based on reviews
  double difficulty;      // Score of 1-10 on how difficult the game is
  vector<Review> reviews; // Vector of reviews containing description, difficulty, and score

private:
};

class Board : public Game // Child of Game Class
{
public:
  Board();
  Board(const Board &src);
  Board &operator=(const Board &src);
  ~Board();

  bool displayQuick() const;
  bool displayDetail() const;

  friend ostream &operator<<(ostream &os, const Board &src);

  Game *clone() const; // Clone used for separating memory management
private:
};

// class Video : public Game // Child of Game Class
// {
// public:
//   Video();
//   Video(const Video &src);
//   Video &operator=(const Video &src);
//   ~Video();

//   bool displayDetail();
//   bool writeReview();

// private:
// };

// class Sport : public Game // Child of Game Class
// {
// public:
//   Sport();
//   Sport(const Sport &src);
//   Sport &operator=(const Sport &src);
//   ~Sport();

//   bool displayDetail();
//   bool writeReview();

// private:
// };

#endif