#include <iostream>
#include <vector>
#include <list>     // 연결 리스트 (체이닝 구현)
#include <string>
#include <utility>  // std::pair

// --------------------------------------------------------
// std::unordered_map의 동작 원리를 모방한 간단한 해시 테이블
// --------------------------------------------------------
template<typename Key, typename Value>
class MyUnorderedMap {
public:
    // 버킷의 기본 크기
    static const int DEFAULT_BUCKET_SIZE = 10;

    // 각 버킷은 (Key, Value) 쌍을 저장하는 연결 리스트
    // std::list<std::pair<Key, Value>> : 체이닝을 위한 연결 리스트
    std::vector<std::list<std::pair<Key, Value>>> buckets;

    MyUnorderedMap() : buckets(DEFAULT_BUCKET_SIZE) {
        std::cout << "MyUnorderedMap이 " << DEFAULT_BUCKET_SIZE << "개의 버킷으로 초기화되었습니다." << std::endl;
    }

    // 간단한 해시 함수 (정수 키에만 유효)
    // 실제 std::unordered_map은 std::hash를 사용합니다.
    size_t getHash(const Key& key) const {
        return std::hash<Key>{}(key); // std::hash 템플릿 사용 (더 일반적)
    }

    // 키를 버킷 인덱스로 변환
    size_t getBucketIndex(const Key& key) const {
        return getHash(key) % buckets.size();
    }

    // ------------------- 삽입 연산 -------------------
    void insert(const Key& key, const Value& value) {
        size_t hash_value = getHash(key);
        size_t bucket_idx = getBucketIndex(key);

        std::cout << "\n[삽입 시도: Key=" << key << ", Value=" << value << "]";
        std::cout << " -> 해시 값: " << hash_value << ", 버킷 인덱스: " << bucket_idx << std::endl;

        // 해당 버킷의 연결 리스트 탐색
        for (auto& pair : buckets[bucket_idx]) {
            if (pair.first == key) {
                std::cout << "  키 " << key << "가 이미 존재합니다. 값 업데이트." << std::endl;
                pair.second = value; // 값 업데이트
                return;
            }
        }

        // 키가 없으면 리스트에 추가
        buckets[bucket_idx].push_back({ key, value });
        std::cout << "  새로운 (Key, Value) 쌍 {" << key << ", " << value << "}를 버킷 " << bucket_idx << "에 삽입했습니다." << std::endl;
        printBucketContent(bucket_idx);
    }

    // ------------------- 탐색 연산 -------------------
    Value* find(const Key& key) {
        size_t hash_value = getHash(key);
        size_t bucket_idx = getBucketIndex(key);

        std::cout << "\n[탐색 시도: Key=" << key << "]";
        std::cout << " -> 해시 값: " << hash_value << ", 예상 버킷 인덱스: " << bucket_idx << std::endl;

        // 해당 버킷의 연결 리스트 탐색
        std::cout << "  버킷 " << bucket_idx << "의 내용을 순회하며 키 " << key << "를 찾습니다: ";
        bool first_item = true;
        for (auto& pair : buckets[bucket_idx]) {
            if (!first_item) std::cout << " -> ";
            std::cout << "{" << pair.first << ", " << pair.second << "}";
            first_item = false;

            if (pair.first == key) {
                std::cout << " -> 찾았습니다!" << std::endl;
                return &pair.second; // 값의 포인터 반환
            }
        }

        std::cout << " -> 찾지 못했습니다." << std::endl;
        return nullptr; // 찾지 못함
    }

    // ------------------- 디버깅/시각화 유틸리티 -------------------

    // 특정 버킷의 내용을 출력
    void printBucketContent(size_t bucket_idx) const {
        if (bucket_idx >= buckets.size()) {
            std::cout << "유효하지 않은 버킷 인덱스입니다." << std::endl;
            return;
        }
        std::cout << "  [버킷 " << bucket_idx << " 내용]: ";
        if (buckets[bucket_idx].empty()) {
            std::cout << "비어있음";
        }
        else {
            for (const auto& pair : buckets[bucket_idx]) {
                std::cout << "{" << pair.first << ", " << pair.second << "} ";
            }
        }
        std::cout << std::endl;
    }

    // 전체 해시 테이블의 상태 출력
    void printAllBuckets() const {
        std::cout << "\n===== 현재 MyUnorderedMap 상태 =====" << std::endl;
        for (size_t i = 0; i < buckets.size(); ++i) {
            std::cout << "버킷 " << i << ": ";
            if (buckets[i].empty()) {
                std::cout << "[비어있음]" << std::endl;
            }
            else {
                for (const auto& pair : buckets[i]) {
                    std::cout << "{" << pair.first << ", " << pair.second << "} -> ";
                }
                std::cout << "nullptr" << std::endl; // 연결 리스트의 끝을 시각적으로 표현
            }
        }
        std::cout << "=======================================" << std::endl;
    }
};

int main() {
    MyUnorderedMap<int, std::string> myMap;

    // 데이터 삽입 예시
    myMap.insert(10, "Apple");  // 해시: 10, 버킷: 0
    myMap.insert(20, "Banana"); // 해시: 20, 버킷: 0 (충돌!)
    myMap.insert(5, "Cherry");  // 해시: 5, 버킷: 5
    myMap.insert(15, "Date");   // 해시: 15, 버킷: 5 (충돌!)
    myMap.insert(3, "Elderberry"); // 해시: 3, 버킷: 3
    myMap.insert(13, "Fig");    // 해시: 13, 버킷: 3 (충돌!)
    myMap.insert(23, "Grape");  // 해시: 23, 버킷: 3 (충돌!)
    myMap.insert(33, "Honeydew"); // 해시: 33, 버킷: 3 (충돌!)
    myMap.insert(4, "Icecream"); // 해시: 4, 버킷: 4

    myMap.printAllBuckets();

    // 데이터 탐색 예시
    std::cout << "\n===== 데이터 탐색 =====" << std::endl;

    // 존재하는 키 탐색
    Value* val = myMap.find(20);
    if (val) {
        std::cout << "찾은 값: " << *val << std::endl;
    }
    else {
        std::cout << "20에 해당하는 값을 찾을 수 없습니다." << std::endl;
    }

    val = myMap.find(13);
    if (val) {
        std::cout << "찾은 값: " << *val << std::endl;
    }
    else {
        std::cout << "13에 해당하는 값을 찾을 수 없습니다." << std::endl;
    }

    // 존재하지 않는 키 탐색
    val = myMap.find(99);
    if (val) {
        std::cout << "찾은 값: " << *val << std::endl;
    }
    else {
        std::cout << "99에 해당하는 값을 찾을 수 없습니다." << std::endl;
    }

    // 값 업데이트 테스트
    myMap.insert(10, "New Apple"); // 기존 10의 값 업데이트
    myMap.printBucketContent(0); // 0번 버킷 내용 확인
    val = myMap.find(10);
    if (val) {
        std::cout << "업데이트 후 찾은 값: " << *val << std::endl;
    }

    myMap.printAllBuckets();

    return 0;
}