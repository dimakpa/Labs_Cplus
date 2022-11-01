#include <iostream>
#include "Maap.h"
int main(void)
{
    Pair<int, string> pair2(1, "aaa");
    Pair<int, string> pair1(1, "aaa");
    Map<int, string> tree(pair2);

    tree.AddNode(3, "bbb");

    tree.PrintTree();
    tree.DelNode(3);
    tree.PrintTree();
    return 0;
}