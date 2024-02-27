/* In this program I decided to use a standard binary search tree as
I think I will feel more comfortable implementing a red-black tree in
python than in C++, most likely due to the difference in getters, setters,
and the sheer amount of complexity using dynamic memory that C++ incorporates.
I have a B*/
#ifndef _TREE_H_
#define _TREE_H_
#include "Game.h"

using namespace std;

class Node
{
public:
  Node();
  Node(const Node &src);
  Node(Game *aGame);
  Node &operator=(const Node &src);
  ~Node();

  Game *getGame() const; // We set the getters to const for the copy constructor and assignment operator
  Node *getLeft();
  Node *getRight();
  bool setLeft(Node *src);
  bool setRight(Node *src);

  friend ostream &operator<<(ostream &os, const Node &src); // Overloaded ostream operator will cout the game it is pointing to, nothing if Game is empty
  bool display();

private:
  unique_ptr<Game> game;
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

  bool insert(Game *aGame);       // Inserts a new game by passing a pointer of a Game
  bool remove(const string name); // Removes a game by passing in the name of the game to remove
  bool removeAll();               // Recursively removes all nodes in a tree
  bool displayQuick();            // Displays all games in the tree simply by name and type
  bool displayDetail();           // Displays all games in the tree and their details including reviews

private:
  Node *root;

  bool insertHelper(Node *src, Node *parent, Game *aGame); // Helper function for insert
  bool removeHelper(Node *&src, const string name);        // Helper function for remove
  Node *&goLeftMost(Node *&src);                           // Because iteration is not allowed, this is needed to traverse left for the inorder successor for the removeHelper

  bool displayQuick(Node *src);  // Helper for displayQuick
  bool displayDetail(Node *src); // Helper for displayDetail

  bool removeAllHelper(Node *src); // Helper for removeAll

  Node *copyTree(Node *src); // Helper for copy constructor and assignment operator
};

#endif