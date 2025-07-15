# STL Vector 정리

## 📌 push_back vs emplace_back

### push_back
- 이미 생성된 객체를 복사/이동해서 vector에 넣음
- 과정: 객체 생성 → 복사/이동 생성자 → vector 삽입

```cpp
vector<string> vec;
string str = "Hello";
vec.push_back(str);        // 복사 생성자
vec.push_back("World");    // 임시 객체 생성 후 이동
```

### emplace_back
- vector 내부에서 직접 객체 생성 (in-place construction)
- 생성자 인자만 넘겨주면 됨

```cpp
vector<string> vec;
vec.emplace_back("Hello");     // vector 내부에서 string 생성자 호출
vec.emplace_back(5, 'A');      // string(5, 'A') 직접 호출
```

> **💡 성능**: emplace_back이 보통 더 빠름. 불필요한 복사/이동 없애기 때문.

## 📊 Vector 시간 복잡도

### 접근 (Access)
- `vec[i]`, `at(i)`: **O(1)**
- `front()`, `back()`: **O(1)**

### 삽입 (Insertion)
- `push_back()`: 평균 **O(1)**, 최악 **O(n)**
- 중간 삽입: **O(n)**
- 맨 앞 삽입: **O(n)**

### 삭제 (Deletion)
- `pop_back()`: **O(1)**
- 중간 삭제: **O(n)**
- 맨 앞 삭제: **O(n)**

### 검색 (Search)
- 일반 검색: **O(n)**
- 정렬된 vector에서 binary search: **O(log n)**

## 🔄 정렬 시간 복잡도

### std::sort (보통 Introsort 사용)
| 경우 | 시간 복잡도 | 설명 |
|------|------------|------|
| **Best** | O(n log n) | 이미 정렬된 상태 |
| **Average** | O(n log n) | 일반적인 경우 |
| **Worst** | O(n log n) | Introsort라서 최악도 보장 |

### 다른 정렬 알고리즘들
| 알고리즘 | Best | Average | Worst |
|---------|------|---------|-------|
| **Quicksort** | O(n log n) | O(n log n) | O(n²) |
| **Mergesort** | O(n log n) | O(n log n) | O(n log n) |
| **Heapsort** | O(n log n) | O(n log n) | O(n log n) |

## 🔧 Vector 내부 동작

### 기본 구조
```cpp
template<typename T>
class vector {
private:
    T* data;           // 실제 데이터
    size_t size_;      // 현재 원소 개수
    size_t capacity_;  // 할당된 메모리 크기
};
```

### 메모리 확장 과정
1. 처음엔 capacity = 0
2. 첫 삽입때 메모리 할당 (보통 1개)
3. capacity 부족하면:
   - 새 메모리 할당 (보통 2배)
   - 기존 원소들 새 메모리로 복사/이동
   - 기존 메모리 해제
   - 새 원소 삽입

### 확장 예시
```
원소: [1] [2] [3] [4] [5]
cap:   1   2   4   4   8
size:  1   2   3   4   5
```

### push_back 내부 동작
```cpp
void push_back(const T& value) {
    if (size_ == capacity_) {
        // 메모리 재할당
        size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = allocate(new_cap);
        
        // 기존 원소들 이동
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);
        }
        
        deallocate(data);
        data = new_data;
        capacity_ = new_cap;
    }
    
    data[size_++] = value;
}
```

## ⚡ 특징 및 최적화

### 주요 특징
- **연속 메모리**: 모든 원소가 연속된 메모리에 저장
- **캐시 효율**: CPU 캐시 히트율 높음
- **반복자 무효화**: 재할당시 모든 포인터/반복자 무효화

### 최적화 팁
- `reserve()`로 미리 메모리 확보
- `shrink_to_fit()`로 불필요한 메모리 해제
- 가능하면 emplace_back 사용

---

## 📝 요약

- **push_back vs emplace_back**: emplace_back이 성능상 유리
- **시간 복잡도**: 끝 삽입/삭제 O(1), 중간 삽입/삭제 O(n)
- **정렬**: std::sort는 O(n log n) 보장
- **메모리**: 2배씩 확장, 연속 메모리 사용
