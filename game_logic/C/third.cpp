#include <iostream>
#include <set>
#include <vector>

// функция сортровки на основе красно-черного дерева
void treeSort(std::vector<int>& values) {

    // по умолчанию создается отсортированным по возрастанию
    std::multiset<int> rbTree(values.begin(), values.end());
    values.assign(rbTree.begin(), rbTree.end());
}

int main() {
    std::vector<int> values = {5, 3, 8, 1, 4, 7, 9};
    treeSort(values);

    std::cout << "Sorted values: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}