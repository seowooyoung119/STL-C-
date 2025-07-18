#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::max
#include <functional>

// ���� Ž�� Ʈ���� ��� ����ü
struct Node 
{
    int key;
    Node* left;
    Node* right;

    // ������
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// BST�� ��带 �����ϴ� �Լ�
Node* insert(Node* root, int key) 
{
    if (root == nullptr)
    {
        return new Node(key);
    }

    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) 
    {
        root->right = insert(root->right, key);
    }
    // Ű�� �̹� �����ϸ� �ƹ��͵� ���� ���� (�ߺ� ��� �� ��)
    return root;
}

// BST���� Ư�� Ű�� Ž���ϴ� �Լ�
// Ž�� ��θ� ����Ͽ� �ð������� �����ݴϴ�.
Node* search(Node* root, int target_key) 
{
    Node* current = root;
    std::cout << "\n[Ž�� ����: " << target_key << "]" << std::endl;

    while (current != nullptr)
    {
        std::cout << "���� ���: " << current->key;

        if (target_key == current->key) 
        {
            std::cout << " -> ��ǥ Ű(" << target_key << ")�� ã�ҽ��ϴ�!" << std::endl;
            return current;
        }
        else if (target_key < current->key) 
        {
            std::cout << " -> " << target_key << "��(��) " << current->key << "���� �����Ƿ� �������� �̵�" << std::endl;
            current = current->left;
        }
        else 
        { // target_key > current->key
            std::cout << " -> " << target_key << "��(��) " << current->key << "���� ũ�Ƿ� ���������� �̵�" << std::endl;
            current = current->right;
        }
    }
    std::cout << "��ǥ Ű(" << target_key << ")�� ã�� ���߽��ϴ�." << std::endl;
    return nullptr;
}

// Ʈ���� ���� ��ȸ�ϸ� ��� (���ĵ� ������ Ű�� �� �� ����)
void inorderTraversal(Node* root)
{
    if (root == nullptr) 
    {
        return;
    }
    inorderTraversal(root->left);
    std::cout << root->key << " ";
    inorderTraversal(root->right);
}

// Ʈ���� �ð������� ����ϱ� ���� ��ƿ��Ƽ �Լ� (���⵵�� ����)
struct Trunk 
{
    Trunk* prev;
    std::string str;

    Trunk(Trunk* p, std::string s) : prev(p), str(s) {}
};

// Trunk�� ����ϴ� ���� �Լ�
void showTrunks(Trunk* p) 
{
    if (p == nullptr) 
    {
        return;
    }
    showTrunks(p->prev);
    std::cout << p->str;
}

// Ʈ���� ����ϴ� �ٽ� ��� �Լ�
void printTree(Node* root, Trunk* prev, bool isLeft) 
{
    if (root == nullptr) 
    {
        return;
    }

    std::string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (prev == nullptr) 
    {
        std::cout << root->key << std::endl;
    }
    else 
    {
        std::cout << (isLeft ? "��������" : "��������") << root->key << std::endl;
    }

    printTree(root->left, trunk, false);

    delete trunk; // �޸� ����
}


int main() 
{
    Node* root = nullptr;

    // ������ ���� (����: 50, 17, 76, 9, 23, 54, 72)
    std::cout << "===== ��� ���� =====" << std::endl;
    root = insert(root, 50);
    insert(root, 17);
    insert(root, 76);
    insert(root, 9);
    insert(root, 23);
    insert(root, 54);
    insert(root, 72);
    insert(root, 60); // 54�� 72 ���� (72�� ���� �ڽ�)
    insert(root, 80); // 76�� ������ �ڽ�

    std::cout << "\n===== ���� Ʈ�� ���� =====" << std::endl;
    printTree(root, nullptr, false);

    std::cout << "\n===== ���� ��ȸ (���ĵ� ���� Ȯ��) =====" << std::endl;
    inorderTraversal(root);
    std::cout << std::endl;

    // 76 Ž�� ����
    search(root, 76);

    // 23 Ž�� ����
    search(root, 23);

    // 80 Ž�� ����
    search(root, 80);

    // ���� �� Ž�� ����
    search(root, 100);

    // Ʈ���� ��� ��� �޸� ���� (���� map������ �ڵ����� ����)
    // ������ ���ø� ���� �������� �����մϴ�.
    std::vector<Node*> nodes_to_delete;
    std::function<void(Node*)> collect_nodes =
        [&](Node* node) 
        {
        if (node == nullptr) return;
        nodes_to_delete.push_back(node);
        collect_nodes(node->left);
        collect_nodes(node->right);
        };
    collect_nodes(root);
    for (Node* node : nodes_to_delete) 
    {
        delete node;
    }

    return 0;
}