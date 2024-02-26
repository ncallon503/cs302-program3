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

  Game *getGame();
  bool setLeft(Node *src);
  bool setRight(Node *src);
  Node *getLeft();
  Node *getRight();

  friend ostream &operator<<(ostream &os, const Node &src);
  bool display();

private:
  unique_ptr<Game> game;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

class Tree
{
public:
  Tree();
  Tree(const Tree &src);
  Tree &operator=(const Tree &src);
  ~Tree();

  bool insert(Game *aGame);
  bool remove(string name);
  bool display();
  bool displayDetail(string name);
  bool displayQuick(string name);
};

#endif