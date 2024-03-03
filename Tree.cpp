/* My initial approach to the organization was using the names as the main categorizer for sorting
my binary search tree, but I think the better approach would be to use a constant integer
that is unchanging rather than duplicate names. What I mean by constant, is I have values
that actually change every single time a review is written by someone, being the score and difficulty
doubles, which are averages of all the reviews written on a Game, and change every time a
review is written by using the update() function at the end of these reviews. These would definitely mess
up the tree if I am sorting by them as they would change every time a review is written but not
move on the tree. So I chose accessibility level for my integer, and what this will do,
is due to having 2 key values to sort by and not one, accessibility will make its own smaller
subtrees (roots being integers from the range in RangeException) and for the names they will
be inserted in these smaller subtrees alphabetically. */

#ifndef _TREE_CPP_
#define _TREE_CPP_
#include "Tree.h"

Node::Node() : game(nullptr), left(nullptr), right(nullptr){};

Node::Node(const Node &src)
{
    game.reset(src.game.get()->clone());
    left = nullptr;
    right = nullptr;
}

Node::Node(Game *aGame)
{
    if (aGame != nullptr)
    {
        game.reset(aGame->clone());
    }
    else
    {
        game.reset();
    }
    left = nullptr;
    right = nullptr;
}

Node &Node::operator=(const Node &src)
{
    if (this != &src)
    {
        game.reset(src.game.get());
        left = nullptr;
        right = nullptr;
    }
    return *this;
}

Node::~Node() {} // Smart_ptr so we need not deallocate anything

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

bool Node::setGame(Game *aGame)
{
    game.reset(aGame->clone());
    return true;
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
    Node *toInsertAt = findAccessRootInsert(root, nullptr, aGame); // We use the score to find the correct place to insert (if a node is not found, we use the most recent before null found)
    if (toInsertAt == nullptr)                                     // If this was null, we don't need to traverse anymore and operation is done
        return true;
    return insertHelper(toInsertAt, nullptr, aGame);
}

Node *Tree::findAccessRootInsert(Node *src, Node *parent, Game *aGame)
{
    if (aGame->getAccessibility() < src->getGame()->getAccessibility()) // We use this to find the subtree that has the correct score to insert it there
    {
        if (src->getLeft() == nullptr) // Easy case, sets it, done
        {
            src->setLeft(new Node(aGame));
            return nullptr;
        }
        else // Left child not nullptr
        {
            if (src->getLeft()->getGame()->getAccessibility() == aGame->getAccessibility()) // If it is equal, we return src->getLeft() as the sub-root
            {
                return src->getLeft(); // We found the root! Now we use the insertHelper on this
            }
            else // If it is not equal, we need to keep traversing recursively
            {
                return findAccessRootInsert(src->getLeft(), src, aGame);
            }
        }
    }
    else if (aGame->getAccessibility() >= src->getGame()->getAccessibility())
    {
        if (src->getRight() == nullptr) // Easy case, sets it, done
        {
            src->setRight(new Node(aGame));
            return nullptr;
        }
        else // Right child not nullptr
        {
            if (src->getRight()->getGame()->getAccessibility() == aGame->getAccessibility()) // If it is equal, we return src->getRight() as the sub-root
            {
                return src->getRight(); // We found the root! Now we use the insertHelper on this
            }
            else // If it is not equal, we need to keep traversing recursively
            {
                return findAccessRootInsert(src->getRight(), src, aGame);
            }
        }
    }
    return nullptr;
}

bool Tree::insertHelper(Node *src, Node *parent, Game *aGame)
{
    if (src == nullptr) // Base case
    {
        src = new Node(aGame);
        return true;
    }
    else if (*aGame < *src->getGame()) // Dereference both to use operator overloading to compare the names alphabetically
    {
        if (src->getLeft() == nullptr)
        {
            src->setLeft(new Node(aGame));
            return true;
        }
        else
        {
            return insertHelper(src->getLeft(), src, aGame);
        }
    }
    else if (*aGame > *src->getGame())
    {
        if (src->getRight() == nullptr)
        {
            src->setRight(new Node(aGame));
            return true;
        }
        else
        {
            return insertHelper(src->getRight(), src, aGame);
        }
    }
    else if (*aGame == *src->getGame()) // If the names are the same, we cannot insert
    {
        cout << "Cannot insert a game of a duplicate name of a pre-existing game.\n";
        return false;
    }
    return false;
}

bool Tree::remove(const string name, const int accessibility)
{
    if (!root) // Empty tree
    {
        cout << "Cannot remove from empty tree.\n";
        return false;
    }
    Node *nodeToRemove = findAccessRootRemove(root, nullptr, name, accessibility);
    if (nodeToRemove == nullptr) // Node was not found, so we return false.
    {
        cout << "Node was not found. Returning false.\n";
        return false;
    }
    return removeHelper(nodeToRemove, name, accessibility);
}

Node *Tree::findGame(const string name, const int accessibility)
{
    if (!root) // Empty tree
    {
        cout << "Cannot find in empty tree.\n";
        return nullptr;
    }
    Node *nodeToFind = findAccessRootRemove(root, nullptr, name, accessibility); // We reuse this function instead of the insert version to get access to subtree
    if (nodeToFind == nullptr)
    {
        cout << "Could not find subtree for node to find.\n";
        return nullptr;
    }
    Node *theGame = findGameHelper(nodeToFind, name, accessibility);
    if (theGame == nullptr)
    {
        cout << "Could not find node in said accessibility subtree.\n";
        return nullptr;
    }
    return theGame;
}

Node *Tree::findGameHelper(Node *src, const string name, const int accessibility)
{
    if (!src)
    {
        cout << "Could not find game of name " << name << " and accessibility " << accessibility << "\n";
        return nullptr; // Base case, could not find node
    }
    if (*src->getGame() > name) // If the name is later in the alphabet, go left
    {
        return findGameHelper(src->getLeft(), name, accessibility);
    }
    else if (*src->getGame() < name) // If the name is earlier in the alphabet, go right
    {
        return findGameHelper(src->getRight(), name, accessibility);
    }
    else if (*src->getGame() == name) // If the name is the same, we have found the node to remove
    {
        return src;
    }
    return nullptr;
}

Node *Tree::findAccessRootRemove(Node *src, Node *parent, const string name, const int accessibility)
{
    if (accessibility < src->getGame()->getAccessibility()) // We use this to find the subtree that has the correct score to insert it there
    {
        if (src->getLeft() == nullptr) // Nothing to remove, the accessibility tree doesnt exist
        {
            return nullptr;
        }
        else // Left child not nullptr
        {
            if (src->getLeft()->getGame()->getAccessibility() == accessibility) // If it is equal, we return src->getLeft() as the sub-root
            {
                return src->getLeft();
            }
            else // If it is not equal, we need to keep traversing recursively
            {
                return findAccessRootRemove(src->getLeft(), src, name, accessibility);
            }
        }
    }
    else if (accessibility >= src->getGame()->getAccessibility())
    {
        if (src->getRight() == nullptr) // Nothing to remove, the accessibility tree doesnt exist
        {
            return nullptr;
        }
        else // Right child not nullptr
        {
            if (src->getRight()->getGame()->getAccessibility() == accessibility) // If it is equal, we return src->getRight() as the sub-root
            {
                return src->getRight();
            }
            else // If it is not equal, we need to keep traversing recursively
            {
                return findAccessRootRemove(src->getRight(), src, name, accessibility);
            }
        }
    }
    return nullptr;
}

bool Tree::removeHelper(Node *&src, const string name, const int accessibility)
{
    if (!src)
    {
        cout << "Could not find node to remove.\n";
        return false; // Base case, could not find node with name to remove
    }
    if (*src->getGame() > name) // If the name is later in the alphabet, go left (These look weird but have to be reversed because the way the operator I overloaded works)
    {
        return removeHelper(src->getLeft(), name, accessibility);
    }
    else if (*src->getGame() < name) // If the name is earlier in the alphabet, go right
    {
        return removeHelper(src->getRight(), name, accessibility);
    }
    else if (*src->getGame() == name) // If the name is the same, we have found the node to remove
    {

        if (!src->getLeft() || !src->getRight()) // Covers two cases, one leaf or no leaves
        {
            Node *temp = src->getLeft() ? src->getLeft() : src->getRight(); // If left exists set temp to left, otherwise set temp to right
            if (temp)
            { // One leaf case, this essentially scoops it up and replaces src with the child
                Node *toDelete = src;
                src = temp;
                delete toDelete;
            }
            else // If temp is nullptr, then no leaves, we can simply delete it
            {
                delete src;
                src = nullptr;
            }
        }
        else // Covers case of two children
        {
            // Find inorder successor (smallest in the right subtree)
            Node *leftMost = goLeftMost(src->getRight());                                                           // This recursively traverses left to get the leftmost node of the right subtree
            src->setGame(leftMost->getGame());                                                                      // Replace this nodes content with inorder successor
            removeHelper(src->getRight(), leftMost->getGame()->getName(), leftMost->getGame()->getAccessibility()); // This removes the inorder successor (leftMost) from the right subtree
        }
        return true; // Node removed successfully
    }
    return false;
}

bool Tree::displayQuick()
{
    if (!root)
        cout << "The tree is empty, cannot display from an empty tree.\n";
    return displayQuick(root);
}

bool Tree::displayDetail()
{
    if (!root)
        cout << "The tree is empty, cannot display from an empty tree.\n";
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
    cout << "\n ------------------- \n\n";
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
    cout << "\n ------------------- \n\n";
    displayDetail(src->getRight());
    return true;
}

bool Tree::removeAll()
{
    if (!root)
        return false; // Return false if empty tree
    bool retValue = removeAllHelper(root);
    root = nullptr;
    return retValue; // Takes 3 steps because we are returning by boolean and want to keep the return value
}

bool Tree::removeAllHelper(Node *src)
{
    if (src == nullptr)
    {
        return true;
    }
    removeAllHelper(src->getLeft());
    removeAllHelper(src->getRight());
    delete src;
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

Node *Tree::goLeftMost(Node *src)
{
    if (src->getLeft() == nullptr)
    {
        return src;
    }
    return goLeftMost(src->getLeft());
}

#endif
