#include "tree.h"
#include "BST.h"
#include "AVL.h"
#include "RBT.h"

int main()
{
    RBT<int> rbt;
    int arr[] = { 10, 20, 30, 15, 25, 5, 1, 100, 50, 40 };
    for (int i : arr) {
        rbt.Insert(i);
    }

    std::cout << "InOrder: ";
    rbt.InOrder();
    
    std::cout << "PreOrder: ";
    rbt.PreOrder();

    std::cout << "PostOrder: ";
    rbt.PostOrder();

    std::cout << "Search 15: ";
    rbt.Search(15);
    
    std::cout << "Removing 30..." << std::endl;
    rbt.Remove(30);

    std::cout << "InOrder after removal: ";
    rbt.InOrder();

    return 0;
}