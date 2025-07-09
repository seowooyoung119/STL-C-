#include <unordered_map>


// ========================================
// 2. unordered_map 관련 함수들
// ========================================

unordered_map<char, int> lastIndex;
lastIndex['a'] = 1;
lastIndex['b'] = 5;
lastIndex['c'] = 10;

// ----------------------------------------
// 2-1. .find() 함수
// ----------------------------------------

auto it = lastIndex.find('a');  // iterator 반환
if (it != lastIndex.end()) 
{
    cout << "키 'a' 찾음: " << it->second << endl;
}

auto it2 = lastIndex.find('z');  // 없는 키
if (it2 == lastIndex.end()) 
{
    cout << "키 'z' 없음" << endl;
}

// ----------------------------------------
// 2-2. .end() 함수
// ----------------------------------------

.end()는 맵의 끝을 나타내는 특별한 iterator
"찾을 수 없음"을 나타내는 값
 
// ----------------------------------------
// 2-3. .count() 함수
// ----------------------------------------

// unordered_map에서는 키가 있으면 1, 없으면 0 반환
cout << "키 'a' 개수: " << lastIndex.count('a') << endl;  // 1
cout << "키 'z' 개수: " << lastIndex.count('z') << endl;  // 0

// 존재 확인용으로 자주 사용
if (lastIndex.count('a') > 0) 
{
    cout << "키 'a' 존재함" << endl;
}

// ----------------------------------------
// 2-4. .contains() 함수 (C++20 이상)
// ----------------------------------------

// 가장 직관적인 방법 (C++20 이상에서만 사용 가능)
if (lastIndex.contains('a')) 
{
    cout << "키 'a' 존재함 (contains 사용)" << endl;
}

if (!lastIndex.contains('z')) 
{
    cout << "키 'z' 없음 (contains 사용)" << endl;
}


// ========================================
// 3. 실제 사용 예시 비교
// ========================================

cout << "=== 키 존재 확인 방법 비교 ===" << endl;

char searchKey = 'a';

// 방법 1: find() 사용
if (lastIndex.find(searchKey) != lastIndex.end()) {
    cout << "방법 1 (find): 키 존재" << endl;
}

// 방법 2: count() 사용
if (lastIndex.count(searchKey) > 0) 
{
    cout << "방법 2 (count): 키 존재" << endl;
}

// 방법 3: contains() 사용 (C++20+)
if (lastIndex.contains(searchKey)) 
{
    cout << "방법 3 (contains): 키 존재" << endl;
}


// ========================================
// 4. 주의사항
// ========================================


// 잘못된 방법: 키가 없어도 자동 생성됨
cout << "map 크기 (before): " << lastIndex.size() << endl;
int value = lastIndex['z'];  // 'z' 키가 자동 생성됨 (기본값 0)
cout << "map 크기 (after): " << lastIndex.size() << endl;
cout << "자동 생성된 값: " << value << endl;
