/* For the tree strucutre I made the decision of using a binary search tree so I could focus more on
the dynamic binding and overloading in this assignment so I wanted to dedicate all my time
into that. With having 2 search keys, I have subtrees decided by accessibility level (which
can be thought of as "easy of entry") and after that they are categorized alphabetically. Games
are allocated in nodes by shared_ptr's and left and right node pointers use normal pointers. */

#ifndef _TREE_H_
#define _TREE_H_
#include "Game.h"

class Node
{
public:
  Node();
  Node(const Node &src);
  Node(Game *aGame);
  Node &operator=(const Node &src);
  ~Node();

  Game *getGame() const; // We set the getter to const for the copy constructor and assignment operator
  Node *&getLeft();
  Node *&getRight();
  bool setGame(Game *aGame); // We don't use this really, except for with the inorder successor in the removeHelper function
  bool setLeft(Node *src);
  bool setRight(Node *src);

  friend ostream &operator<<(ostream &os, const Node &src); // Overloaded ostream operator will cout the game it is pointing to, nothing if Game is empty
  bool display();

private:
  shared_ptr<Game> game;
  Node *left;
  Node *right;
};

class Tree
{
public:
  Tree();
  Tree(const Tree &src);
  Tree &operator=(const Tree &src);
  ~Tree();

  bool insert(Game *aGame);                                   // Inserts a new game by passing a pointer of a Game
  bool remove(const string name, const int accessibility);    // Removes a game by passing in the name of the game to remove and the score of it (needs both name and score due to 2 keys)
  bool removeAll();                                           // Recursively removes all nodes in a tree
  bool displayQuick();                                        // Displays all games in the tree simply by name and type
  bool displayDetail();                                       // Displays all games in the tree and their details including reviews
  Node *findGame(const string name, const int accessibility); // Finds a game by passing in the name and accessibiilty level

private:
  Node *root;

  bool insertHelper(Node *src, Node *parent, Game *aGame);                                         // Helper function for insert
  Node *findAccessRootInsert(Node *src, Node *parent, Game *aGame);                                // This helps find the place to treat as root to insert for the score
  bool removeHelper(Node *&src, const string name, const int accessibility);                       // Helper function for remove
  Node *findAccessRootRemove(Node *src, Node *parent, const string name, const int accessibility); // This is the remove version of finding root of accessibility
  Node *goLeftMost(Node *src);                                                                     // Because iteration is not allowed, this is needed to traverse left for the inorder successor for the removeHelper

  bool displayQuick(Node *src);  // Helper for displayQuick
  bool displayDetail(Node *src); // Helper for displayDetail

  bool removeAllHelper(Node *src); // Helper for removeAll

  Node *findGameHelper(Node *src, const string name, const int accessibility); // Helper for findGame

  Node *copyTree(Node *src); // Helper for copy constructor and assignment operator
};

#endif