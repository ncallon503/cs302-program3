/* Nathan Callon, CS302, 3/2/2024, Karla Fant
For this program I heavily focused on dynamic binding and making the best use of it, and using it
to make my program not just more flexible and avoiding repetition but making the menu able to do
things it wasn't before such as using upcasting with base class pointers to child objects to
perform tree operations and have the overloaded operators and virtual overriden functions perform
a bulk of the work while also making the code look simpler and more understandable (for the client
at least). I chose to have a Parent Abstract Base Class named Game, and the children are the Board class,
Video class, and Sport class which all have their own unique properties, all of which are managed by
a Node class, that is managed by a Tree class, that is managed by a UserMenu class. */

#include "Game.h"
#include "Tree.h"
#include "Menu.h"

int main()
{

    UserMenu aMenu;
    aMenu.displayMenu();

    // Board aBoard;
    // cin >> aBoard;

    // Game *aBoard = new Board();
    // cin >> *aBoard;

    // aBoard->displayDetail();

    // Board aBoard2;
    // cin >> aBoard2;

    // Board aBoard3;
    // cin >> aBoard3;

    // Board aBoard4;
    // cin >> aBoard4;

    // Board aBoard5;
    // cin >> aBoard5;

    // Board aBoard6;
    // cin >> aBoard6;

    // Board aBoard7;
    // cin >> aBoard7;

    // Board aBoard8;
    // cin >> aBoard8;

    // cout << "aBoard < aBoard2:" << (aBoard < aBoard2) << "\n";
    // cout << "aBoard <= aBoard2:" << (aBoard <= aBoard2) << "\n";
    // cout << "aBoard > aBoard2:" << (aBoard > aBoard2) << "\n";
    // cout << "aBoard >= aBoard2:" << (aBoard >= aBoard2) << "\n";
    // cout << "aBoard == aBoard2:" << (aBoard == aBoard2) << "\n";
    // cout << "aBoard != aBoard2:" << (aBoard != aBoard2) << "\n";

    // Node aNode(&aBoard);
    // Node aNode2(&aBoard2);

    // cout << "aNode->getGame() < aNode2->getGame():" << (*aNode.getGame() < *aNode2.getGame()) << "\n";
    // cout << "aNode->getGame() <= aNode2->getGame():" << (*aNode.getGame() <= *aNode2.getGame()) << "\n";
    // cout << "aNode->getGame() > aNode2->getGame():" << (*aNode.getGame() > *aNode2.getGame()) << "\n";
    // cout << "aNode->getGame() >= aNode2->getGame():" << (*aNode.getGame() >= *aNode2.getGame()) << "\n";
    // cout << "aNode->getGame() == aNode2->getGame():" << (*aNode.getGame() == *aNode2.getGame()) << "\n";
    // cout << "aNode->getGame() != aNode2->getGame():" << (*aNode.getGame() != *aNode2.getGame()) << "\n";

    // aTree.insert(&aBoard);
    // aTree.insert(&aBoard2);
    // aTree.insert(&aBoard3);
    // aTree.insert(&aBoard4);
    // aTree.insert(&aBoard5);
    // aTree.insert(&aBoard6);
    // aTree.insert(&aBoard7);
    // aTree.insert(&aBoard8);

    // aMenu.displayQuick();

    // cout << "Removing Chess:\n";
    // aTree.remove("Chess", 7);

    // cout << "Displaying after remove Chess:\n";
    // aTree.displayQuick();

    // Board aBoardGame;
    // aBoardGame.writeReview();
    // aBoardGame.writeReview();
    // aBoardGame.displayDetail();

    // Node *aNode = new Node(new Board());
    // aNode->getGame()->writeReview();
    // cout << "aNode:" << *aNode << "\n";

    // aNode->setLeft(new Node(new Board()));
    // aNode->setRight(new Node(new Board()));

    // aNode->getLeft()->getGame()->writeReview();
    // aNode->getRight()->getGame()->writeReview();

    // cout << "aNode->getLeft(): \n";
    // aNode->getLeft()->getGame()->displayDetail();
    // cout << "aNode->getRight(): \n";
    // aNode->getRight()->getGame()->displayDetail();

    // delete aNode;

    // Review temp;
    // cin >> temp;
}