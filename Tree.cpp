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
    game.reset(); // Not entirely necessary but just good practice to reset nodes for deallocation
}

ostream &operator<<(ostream &os, const Node &src)
{
    if (src.game.get() != nullptr) // Only couts if the game pointer is pointing to something
        os << *src.game.get() << endl;
    return os;
}

Game *Node::getGame() const
{
    return game.get();
}

bool Node::setLeft(Node *src)
{
    left = src;
    return true; // Returns true no matter what due to nullptr also being acceptable
}

bool Node::setRight(Node *src)
{
    right = src;
    return true;
}

Node *&Node::getLeft()
{
    return left;
}

Node *&Node::getRight()
{
    return right;
}

Tree::Tree() : root(nullptr)
{
}

Tree::Tree(const Tree &src)
{
    root = copyTree(src.root);
}

Tree &Tree::operator=(const Tree &src)
{
    if (this != &src) // Check for self assignment
    {
        root = copyTree(src.root);
    }
    return *this;
}

Tree::~Tree()
{
    removeAll();
}

bool Tree::insert(Game *aGame)
{
    if (root == nullptr) // If the tree is empty, we need to create a new node and set it as the root
    {
        root = new Node(aGame);
        return true;
    }
    return insertHelper(root, nullptr, aGame);
}

bool Tree::remove(const string name)
{
    if (!root) // Empty tree
    {
        cout << "Cannot remove from empty tree.\n";
        return false;
    }
    return removeHelper(root, name);
}

bool Tree::insertHelper(Node *&src, Node *parent, Game *aGame)
{
    if (src == nullptr)
    {
        src = new Node(aGame);
    }
    if (*aGame >= *src->getGame()) // We dereference to use the overloaded operators to compare alphabetically
    {
        if (src->getRight() == nullptr) // Insertion case
        {
            src->setRight(new Node(aGame));
            return true;
        }
        return insertHelper(src->getRight(), src, aGame);
    }
    else
    {
        if (src->getLeft() == nullptr) // Insertion case
        {
            src->setLeft(new Node(aGame));
            return true;
        }
        return insertHelper(src->getLeft(), src, aGame);
    }
}

bool Tree::removeHelper(Node *&src, const string name)
{
    return true;
}

bool Tree::displayQuick()
{
    return displayQuick(root);
}

bool Tree::displayDetail()
{
    return displayDetail(root);
}

bool Tree::displayQuick(Node *src)
{
    if (src == nullptr)
    {
        return false;
    }
    displayQuick(src->getLeft());
    src->getGame()->displayQuick();
    displayQuick(src->getRight());
    return true;
}

bool Tree::displayDetail(Node *src)
{
    if (src == nullptr)
    {
        return false;
    }
    displayDetail(src->getLeft());
    src->getGame()->displayDetail();
    displayDetail(src->getRight());
    return true;
}

bool Tree::removeAll()
{
    return removeAllHelper(root);
}

bool Tree::removeAllHelper(Node *&src)
{
    if (src == nullptr)
    {
        return false;
    }
    removeAllHelper(src->getLeft());
    removeAllHelper(src->getRight());
    delete src;
    src = nullptr;
    return true;
}

Node *Tree::copyTree(Node *src)
{
    if (src == nullptr)
    {
        return nullptr;
    }
    Node *temp = new Node(src->getGame());
    temp->setLeft(copyTree(src->getLeft())); // We use the setters and the Node * return type to recursively set left and right until the final case of nullptr, and because we are not using return in front of these, the final line will still execute and return the node to be set
    temp->setRight(copyTree(src->getRight()));
    return temp;
}

#endif