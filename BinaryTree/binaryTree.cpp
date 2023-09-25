#include <iostream>

using namespace std;

// İkili ağaç düğüm yapısı
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    // Yapıcı fonksiyon
    TreeNode(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

// İkili ağaç sınıfı
class BinaryTree {
private:
    TreeNode* root;

public:
    // Yapıcı fonksiyon
    BinaryTree() {
        root = NULL;
    }

    // Düğüm ekleme fonksiyonu
    void insert(int value) {
        TreeNode* newNode = new TreeNode(value);

        if (root == NULL) {
            root = newNode;
        } else {
            TreeNode* currentNode = root;
            while (true) {
                if (value < currentNode->data) {
                    if (currentNode->left == NULL) {
                        currentNode->left = newNode;
                        break;
                    } else {
                        currentNode = currentNode->left;
                    }
                } else {
                    if (currentNode->right == NULL) {
                        currentNode->right = newNode;
                        break;
                    } else {
                        currentNode = currentNode->right;
                    }
                }
            }
        }
    }

    // Düğümleri ziyaret etme fonksiyonları
    void inorderTraversal(TreeNode* node) {
        if (node != NULL) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    void preorderTraversal(TreeNode* node) {
        if (node != NULL) {
            cout << node->data << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void postorderTraversal(TreeNode* node) {
        if (node != NULL) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->data << " ";
        }
    }

    // Düğüm silme fonksiyonu
    TreeNode* deleteNode(TreeNode* node, int value) {
        if (node == NULL) {
            return node;
        } else if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            if (node->left == NULL && node->right == NULL) {
                delete node;
                node = NULL;
            } else if (node->left == NULL) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == NULL) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
            } else {
                TreeNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        return node;
    }

    // En küçük düğümü bulma fonksiyonu
    TreeNode* findMin(TreeNode* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    // İkili ağacın kök düğümünü döndürme fonksiyonu
    TreeNode* getRoot() {
        return root;
    }
};

int main() {
    // İkili ağaç oluşturma
    BinaryTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Düğümleri ziyaret etme
    cout << "Inorder traversal: ";
    tree.inorderTraversal(tree.getRoot());
    cout << endl;

    cout << "Preorder traversal: ";
    tree.preorderTraversal(tree.getRoot());
    cout << endl;

    cout << "Postorder traversal: ";
    tree.postorderTraversal(tree.getRoot());
    cout << endl;

    // Düğüm silme
    tree.deleteNode(tree.getRoot(), 20);
    cout << "Inorder traversal after deleting a node: ";
    tree.inorderTraversal(tree.getRoot());
    cout << endl;

    return 0;
}