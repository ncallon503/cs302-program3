#include<iostream>
#include<cstring>

using namespace std;

class Game {
  public:
    Game();
    Game(const Game &src);
    Game & operator=(const Game &src);
    virtual ~Game() = default;

    virtual bool display() = 0;

  protected:
    string name; // Name of the game
    string genre; // Genre of the game
    int score; // Score of 1-10 how good the game is based on reviews
    int difficulty; // Score of 1-10 on how difficult the game is
    vector<int> reviews; // The reviews that determine how high/low the score is
    vector<Player> players; // Vector of players that the game class uses

    unique_ptr<Game> left; // Unique pointer to left leaf
    unique_ptr<Game> right; // Unique pointer to right leaf

  private:

};

class Board: public Game {
  public:
    Board();
    Board(const Board &src);
    Board & operator=(const Board &src);
    ~Board();

    bool display();

  private:

};

class Video: public Game {
  public:
    Video();
    Video(const Video &src);
    Video & operator=(const Video &src);
    ~Video();

    bool display();

  private:

};

class Sport: public Game {
  public:
    Sport();
    Sport(const Sport &src);
    Sport & operator=(const Sport &src);
    ~Sport();

    bool display();

  private:

};

class Player {
  public:
    Player();
    Player(const Player &src);
    Player & operator=(const Player &src);
    ~Player();

  private:
    int score;
    int roundsPlayed;

}

