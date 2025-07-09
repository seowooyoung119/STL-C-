#include <vector>
#include <utility>

    // ========================================
    // 1. vector<pair<typename1, typename2>>
    // ========================================

    // pair: 두 개의 값을 하나로 묶는 구조체
    // pair<첫번째타입, 두번째타입>
    vector<pair<char, int>> compares;

    // pair 생성 방법들
    pair<char, int> p1 = { 'a', 5 };           // 방법 1
    pair<char, int> p2 = make_pair('b', 10); // 방법 2
    compares.push_back({ 'c', 15 });           // 방법 3 (직접 삽입)

    // pair 접근
    cout << "첫번째 값: " << p1.first << endl;   // 'a'
    cout << "두번째 값: " << p1.second << endl;  // 5

    // vector<pair> 순회
    for (const auto& p : compares) 
    {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
