#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <limits>
#include <exception>

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

  const bool getDifficulty() const; // Limiting use of getters, but we need these 2 for the sum functions
  const bool getScore() const;

private:
  string description; // User description of the game
  bool difficulty;    // User difficulty score of the game
  bool score;         // User score of the game (enjoyment)
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

  friend ostream &operator<<(ostream &os, const Game &src);
  friend istream &operator>>(istream &is, Game &src);

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
