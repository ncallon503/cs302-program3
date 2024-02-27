#include "Game.h"
#include "Tree.h"

int main()
{
    Tree aTree;

    Board aBoard;
    cin >> aBoard;

    Board aBoard2;
    cin >> aBoard2;

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

    aTree.insert(&aBoard);
    aTree.insert(&aBoard2);

    aTree.displayDetail();
    aTree.displayQuick();

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