#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node
{
public:
    int value;
    Node *left;
    Node *right;
};

// Yeni bir düğüm oluşturmak için yardımcı fonksiyon
Node *newNode(int item)
{
    Node *temp = new Node();
    temp->value = item;
    temp->left = temp->right = nullptr;
    return temp;
}

// İkili arama ağacı sınıfı
class BinarySearchTree
{
private:
    Node *root; // Ağacın kök düğümü
    int space;
    // Düğüm ekleme işlemi için yardımcı fonksiyon
    Node *insertHelper(Node *node, int value)
    {
        if (node == nullptr)
            return newNode(value);

        if (value < node->value)
            node->left = insertHelper(node->left, value);
        else if (value > node->value)
            node->right = insertHelper(node->right, value);

        return node;
    }

    // Düğüm silme işlemi için yardımcı fonksiyon
    Node *removeHelper(Node *node, int value)
    {
        // Ağacın boş olması durumunda geri dön
        if (node == nullptr)
            return nullptr;

        // Silinecek düğümü buluncaya kadar ağacı dolaşmaya devam et
        if (value < node->value)
            node->left = removeHelper(node->left, value);
        else if (value > node->value)
            node->right = removeHelper(node->right, value);

        // Eğer silinecek düğüme ulaşıldıysa, o düğümü sil
        else
        {
            // Tek çocuk ya da hiç çocuk yoksa, direk sil
            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            // İki çocuk varsa, sağ alt ağacın minimumunu al ve bu düğümü mevcut düğüme koy
            Node *temp = node->right;
            while (temp && temp->left != nullptr)
                temp = temp->left;

            node->value = temp->value;
            node->right = removeHelper(node->right, temp->value);
        }

        return node;
    }

    // Ağacın derinliğini hesaplamak için yardımcı fonksiyon
    int depthHelper(Node *node)
    {
        if (node == nullptr)
            return 0;
        else
        {
            int leftDepth = depthHelper(node->left);
            int rightDepth = depthHelper(node->right);
            if (leftDepth > rightDepth)
                return (leftDepth + 1);
            else
                return (rightDepth + 1);
        }
    }

    // Inorder tarayarak ağacın düğümlerine erişmek için yardımcı fonksiyon
    void inorderTraversalHelper(Node *node)
    {
        if (node != nullptr)
        {
            inorderTraversalHelper(node->left);
            cout << node->value << " ";
            inorderTraversalHelper(node->right);
        }
    }

    // Preorder tarayarak ağacın düğümlerine erişmek için yardımcı fonksiyon
    void preorderTraversalHelper(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->value << " ";
            preorderTraversalHelper(node->left);
            preorderTraversalHelper(node->right);
        }
    }

    // Postorder tarayarak ağacın düğümlerine erişmek için yardımcı fonksiyon
    void postorderTraversalHelper(Node *node)
    {
        if (node != nullptr)
        {
            postorderTraversalHelper(node->left);
            postorderTraversalHelper(node->right);
            cout << node->value << " ";
        }
    }
    void printBinaryTree(Node *root, int space = 0, int gap = 5)
    {
        if (root == NULL)
            return;

        // increase distance between levels
        space += gap;

        // print right child first
        printBinaryTree(root->right, space);

        // print node itself
        cout << endl;
        for (int i = gap; i < space; i++)
            cout << " ";
        cout << root->value << "\n";

        // print left child
        printBinaryTree(root->left, space);
    }
    bool isBalanced(Node *node)
    {
        if (!node)
            return true;

        int leftHeight = depthHelper(node->left);
        int rightHeight = depthHelper(node->right);

        if (abs(leftHeight - rightHeight) > 1)
            return false;

        return isBalanced(node->left) && isBalanced(node->right);
    }

public:
    // Kurucu fonksiyon
    BinarySearchTree()
    {
        root = nullptr;
    }

    // Yeni bir düğüm eklemek için fonksiyon
    void insert(int value)
    {
        root = insertHelper(root, value);
    }

    // Belirtilen düğümü silmek için fonksiyon
    void remove(int value)
    {
        root = removeHelper(root, value);
    }

    // Ağacın derinliğini hesaplamak için fonksiyon
    int depth()
    {
        return depthHelper(root);
    }

    // Inorder tarayarak ağacın düğümlerine erişmek için fonksiyon
    void inorderTraversal()
    {
        inorderTraversalHelper(root);
    }

    // Preorder tarayarak ağacın düğümlerine erişmek için fonksiyon
    void preorderTraversal()
    {
        preorderTraversalHelper(root);
    }
    // Postorder tarayarak ağacın düğümlerine erişmek için fonksiyon
    void postorderTraversal()
    {
        postorderTraversalHelper(root);
    }
    // ağacın çizimini yapmak için fonksiyon

    // Ağacın bütün düğümlerini silmek için fonksiyon
    void destroyTree()
    {
        while (root != nullptr)
            remove(root->value);
    }
    //txt Dosyasındaki veriyi iki boyutlu bir diziye çekmek için kullanılan fonksiyon
    void dataFromFile(string **&data, int &row_count)
    {
        ifstream file;
        file.open("sehir_plaka_kodlari.txt");

        if (!file.is_open())
        {
            cout << "Dosya Bulunamadi!";
        }

        // satir sayisini bul
        row_count = 0;
        string line;
        while (getline(file, line))
        {
            row_count++;
        }

        // İkili verileri 2 boyutlu diziye aktar
        data = new string *[row_count];
        file.clear();  // Dosyayı tekrar başa sar.
        file.seekg(0); // Okuma konumunu sıfırla.
        for (int i = 0; i < row_count; ++i)
        {
            data[i] = new string[2];
            getline(file, data[i][0], ',');
            getline(file, data[i][1]);
        }
    }
    void build()
    {
        printBinaryTree(root, 0, 5);
    }
    // İkili Ağac Dengeli mi?
    bool isBalanced()
    {
        return isBalanced(root);
    }
};
int main()
{
    BinarySearchTree tree;
    int row_count;
    int p1, p2;
    int p1Depth, p2Depth;
    string **data;
    tree.dataFromFile(data, row_count);
    int depths[row_count];
    // Düğümler ekleme ve derinliklerini diziye atmak
    for (int i = 0; i < row_count; i++)
    {
        tree.insert(stoi(data[i][0]));
        depths[i] = tree.depth();
    }
    // ekrana girilecek 2 plaka kodunun ekrana yazdırılması
    cout << "iki plaka kodunu giriniz: ";
    cin >> p1 >> p2;
    for (int j = 0; j < row_count; j++)
    {
        if (p1 == stoi(data[j][0]))
        {
            p1Depth = depths[j];
        }
        if (p2 == stoi(data[j][0]))
        {
            p2Depth = depths[j];
        }
        if (p1 == stoi(data[j][0]) || p2 == stoi(data[j][0]))
        {
            cout << data[j][0] << " : " << data[j][1] << endl;
        }
    }
    cout << "iki plakanin agactaki duzey farki: " << abs(p1Depth - p2Depth) << endl;
    // Ağacın derinliğini hesaplama ve ekrana yazdırma
    cout << "Agacin derinligi: " << tree.depth() << endl;
    if (tree.isBalanced())
    {
        cout << "Agac dengelidir." << endl;
    }
    else
    {
        cout << "Agac dengesizdir." << endl;
    }

    // Inorder, preorder ve postorder tarayarak ağacın düğümlerine erişme
    cout << "Inorder traversal: ";
    tree.inorderTraversal();
    cout << endl;

    cout << "Preorder traversal: ";
    tree.preorderTraversal();
    cout << endl;

    cout << "Postorder traversal: ";
    tree.postorderTraversal();
    cout << endl;
    // Ağacı temizleme
    tree.build();
    tree.destroyTree();
    system("pause");
    return 0;
}
