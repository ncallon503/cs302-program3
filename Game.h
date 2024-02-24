/* In this program I decided to use a standard binary search tree as
I think I will feel more comfortable implementing a red-black tree in
python than in C++, most likely due to the difference in getters, setters,
and the sheer amount of complexity using dynamic memory that C++ incorporates.
I have a B*/
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>

using namespace std;

class Game
{
public:
  Game();
  Game(const Game &src);
  Game &operator=(const Game &src);
  virtual ~Game() = default;

  bool displayName();               // Simply displays the name of the game
  virtual bool displayDetail() = 0; // Displays the game in detail like stats and overview, etc
  virtual bool writeReview() = 0;   // Writes a review prompting for user input which includes score and difficulty

protected:
  string name;               // Name of the game
  string genre;              // Genre of the game
  int score;                 // Score of 1-10 how good the game is based on reviews
  int difficulty;            // Score of 1-10 on how difficult the game is
  vector<string> reviews;    // Vector of user reviews (Description)
  vector<int> revDifficulty; // Vector if ratings of the difficulty of the game
  vector<int> revScore;      // Vector of ratings of how good the game is

  unique_ptr<Game> left;  // Unique pointer to left leaf
  unique_ptr<Game> right; // Unique pointer to right leaf

private:
};

class Board : public Game
{
public:
  Board();
  Board(const Board &src);
  Board &operator=(const Board &src);
  ~Board();

  bool displayDetail();
  bool writeReview();

private:
};

class Video : public Game
{
public:
  Video();
  Video(const Video &src);
  Video &operator=(const Video &src);
  ~Video();

  bool displayDetail();
  bool writeReview();

private:
};

class Sport : public Game
{
public:
  Sport();
  Sport(const Sport &src);
  Sport &operator=(const Sport &src);
  ~Sport();

  bool displayDetail();
  bool writeReview();

private:
};

class Player
{
public:
  Player();
  Player(const Player &src);
  Player &operator=(const Player &src);
  ~Player();

private:
  int score;
  int roundsPlayed;
};
