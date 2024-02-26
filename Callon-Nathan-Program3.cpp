#include "Game.h"
#include "Tree.h"

int main()
{
    Board aBoardGame;
    aBoardGame.writeReview();
    aBoardGame.writeReview();
    aBoardGame.displayDetail();

    Node *aNode = new Node(new Board());
    aNode->getGame()->writeReview();
    cout << "aNode:" << *aNode << "\n";

    aNode->setLeft(new Node(new Board()));
    aNode->setRight(new Node(new Board()));

    aNode->getLeft()->getGame()->writeReview();
    aNode->getRight()->getGame()->writeReview();

    cout << "aNode->getLeft(): \n";
    aNode->getLeft()->getGame()->displayDetail();
    cout << "aNode->getRight(): \n";
    aNode->getRight()->getGame()->displayDetail();

    // Review temp;
    // cin >> temp;
}