#ifndef _TREE_CPP_
#define _TREE_CPP_
#include "Tree.h"

Node::Node() : game(nullptr), left(nullptr), right(nullptr){};

Node::Node(const Node &src)
{
    game.reset(src.game.get());
}

Node::Node(Game *aGame)
{
    game.reset(aGame); // We only set the game pointer because we are creating a new node and don't want the memory to point to other places
}

Node &Node::operator=(const Node &src)
{
    if (this != &src)
    {
        game.reset(src.game.get());
    }
    return *this;
}

Node::~Node()
{
    game.reset();
    left.reset(); // Not entirely necessary but just good practice to reset nodes for deallocation
    right.reset();
}

ostream &operator<<(ostream &os, const Node &src)
{
    os << *src.game.get() << endl;
    return os;
}

Game *Node::getGame()
{
    return game.get();
}

bool Node::setLeft(Node *src)
{
    left.reset(src);
    return true;
}

bool Node::setRight(Node *src)
{
    right.reset(src);
    return true;
}

Node *Node::getLeft()
{
    return left.get();
}

Node *Node::getRight()
{
    return right.get();
}

#endif