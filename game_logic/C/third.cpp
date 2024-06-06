#include <iostream>
#include <vector>

// узел
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// класс для вставки элементов в дерево и 
// обхода с лево на право для сортировки по возрастанию 
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else {
            insertRecursive(root, value);
        }
    }

    void inOrderTraversal(std::vector<int>& sortedValues) {
        inOrderRecursive(root, sortedValues);
    }

    void reverseInOrderTraversal(std::vector<int>& sortedValues) {
        reverseInOrderRecursive(root, sortedValues);
    }

private:
    TreeNode* root;

    void insertRecursive(TreeNode* node, int value) {
        if (value < node->value) {
            if (node->left == nullptr) {
                node->left = new TreeNode(value);
            } else {
                insertRecursive(node->left, value);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new TreeNode(value);
            } else {
                insertRecursive(node->right, value);
            }
        }
    }

    // по возрастанию
    void inOrderRecursive(TreeNode* node, std::vector<int>& sortedValues) {
        if (node != nullptr) {
            inOrderRecursive(node->left, sortedValues);
            sortedValues.push_back(node->value);
            inOrderRecursive(node->right, sortedValues);
        }
    }

    // по убыванию
    void reverseInOrderRecursive(TreeNode* node, std::vector<int>& sortedValues) {
        if (node != nullptr) {
            reverseInOrderRecursive(node->right, sortedValues);
            sortedValues.push_back(node->value);
            reverseInOrderRecursive(node->left, sortedValues);
        }
    }
};


// целевая функция сортировки, получает вектор целых чисел, 
// вставляет их в бинарное дерево 
// обходит дерево слева на право для сортировки по возрастанию (по умолчанию)
void treeSort(std::vector<int>& values, const bool mode = true) {
    BinarySearchTree bst;
    for (int value : values) {
        bst.insert(value);
    }
    values.clear();

    // ну в общем ясно
    if (mode){
        bst.inOrderTraversal(values);
    } else {
        bst.reverseInOrderTraversal(values);
    }
}

int main() {
    std::vector<int> values = {5, 3, 8, 1, 4, 7, 9, 5, 5, -3};
    treeSort(values);

    std::cout << "Sorted values: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}