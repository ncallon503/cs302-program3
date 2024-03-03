#include "Game.h"
#include "Tree.h"

int main()
{
    Tree aTree;

    Board aBoard;
    cin >> aBoard;

    Board aBoard2;
    cin >> aBoard2;

    Board aBoard3;
    cin >> aBoard3;

    Board aBoard4;
    cin >> aBoard4;

    Board aBoard5;
    cin >> aBoard5;

    Board aBoard6;
    cin >> aBoard6;

    Board aBoard7;
    cin >> aBoard7;

    Board aBoard8;
    cin >> aBoard8;

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
    aTree.insert(&aBoard3);
    aTree.insert(&aBoard4);
    aTree.insert(&aBoard5);
    aTree.insert(&aBoard6);
    aTree.insert(&aBoard7);
    aTree.insert(&aBoard8);

    aTree.displayQuick();

    cout << "Removing removeMe:\n";
    aTree.remove("removeMe", 5);

    cout << "Displaying after removeMe:\n";
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