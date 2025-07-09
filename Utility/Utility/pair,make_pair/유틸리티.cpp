#include <vector>
#include <utility>

    // ========================================
    // 1. vector<pair<typename1, typename2>>
    // ========================================

    // pair: �� ���� ���� �ϳ��� ���� ����ü
    // pair<ù��°Ÿ��, �ι�°Ÿ��>
    vector<pair<char, int>> compares;

    // pair ���� �����
    pair<char, int> p1 = { 'a', 5 };           // ��� 1
    pair<char, int> p2 = make_pair('b', 10); // ��� 2
    compares.push_back({ 'c', 15 });           // ��� 3 (���� ����)

    // pair ����
    cout << "ù��° ��: " << p1.first << endl;   // 'a'
    cout << "�ι�° ��: " << p1.second << endl;  // 5

    // vector<pair> ��ȸ
    for (const auto& p : compares) 
    {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
