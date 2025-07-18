#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::max
#include <functional>

// 이진 탐색 트리의 노드 구조체
struct Node 
{
    int key;
    Node* left;
    Node* right;

    // 생성자
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// BST에 노드를 삽입하는 함수
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
    // 키가 이미 존재하면 아무것도 하지 않음 (중복 허용 안 함)
    return root;
}

// BST에서 특정 키를 탐색하는 함수
// 탐색 경로를 출력하여 시각적으로 보여줍니다.
Node* search(Node* root, int target_key) 
{
    Node* current = root;
    std::cout << "\n[탐색 시작: " << target_key << "]" << std::endl;

    while (current != nullptr)
    {
        std::cout << "현재 노드: " << current->key;

        if (target_key == current->key) 
        {
            std::cout << " -> 목표 키(" << target_key << ")를 찾았습니다!" << std::endl;
            return current;
        }
        else if (target_key < current->key) 
        {
            std::cout << " -> " << target_key << "은(는) " << current->key << "보다 작으므로 왼쪽으로 이동" << std::endl;
            current = current->left;
        }
        else 
        { // target_key > current->key
            std::cout << " -> " << target_key << "은(는) " << current->key << "보다 크므로 오른쪽으로 이동" << std::endl;
            current = current->right;
        }
    }
    std::cout << "목표 키(" << target_key << ")를 찾지 못했습니다." << std::endl;
    return nullptr;
}

// 트리를 중위 순회하며 출력 (정렬된 순서로 키를 볼 수 있음)
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

// 트리를 시각적으로 출력하기 위한 유틸리티 함수 (복잡도가 높음)
struct Trunk 
{
    Trunk* prev;
    std::string str;

    Trunk(Trunk* p, std::string s) : prev(p), str(s) {}
};

// Trunk를 출력하는 헬퍼 함수
void showTrunks(Trunk* p) 
{
    if (p == nullptr) 
    {
        return;
    }
    showTrunks(p->prev);
    std::cout << p->str;
}

// 트리를 출력하는 핵심 재귀 함수
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
        std::cout << (isLeft ? "┌───" : "└───") << root->key << std::endl;
    }

    printTree(root->left, trunk, false);

    delete trunk; // 메모리 해제
}


int main() 
{
    Node* root = nullptr;

    // 데이터 삽입 (예시: 50, 17, 76, 9, 23, 54, 72)
    std::cout << "===== 노드 삽입 =====" << std::endl;
    root = insert(root, 50);
    insert(root, 17);
    insert(root, 76);
    insert(root, 9);
    insert(root, 23);
    insert(root, 54);
    insert(root, 72);
    insert(root, 60); // 54와 72 사이 (72의 왼쪽 자식)
    insert(root, 80); // 76의 오른쪽 자식

    std::cout << "\n===== 현재 트리 구조 =====" << std::endl;
    printTree(root, nullptr, false);

    std::cout << "\n===== 중위 순회 (정렬된 순서 확인) =====" << std::endl;
    inorderTraversal(root);
    std::cout << std::endl;

    // 76 탐색 예시
    search(root, 76);

    // 23 탐색 예시
    search(root, 23);

    // 80 탐색 예시
    search(root, 80);

    // 없는 값 탐색 예시
    search(root, 100);

    // 트리의 모든 노드 메모리 해제 (실제 map에서는 자동으로 관리)
    // 간단한 예시를 위해 수동으로 해제합니다.
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