# C++ unordered_map 동작 원리

## 1. 기본 구조 - 해시 테이블

`unordered_map`은 해시 테이블(Hash Table)을 기반으로 구현됩니다. 내부적으로 버킷(bucket) 배열을 사용하며, 각 버킷은 동일한 해시 값을 가진 요소들을 저장합니다.

```
버킷 배열 구조:
[0] -> (key1, value1) -> (key5, value5) -> NULL
[1] -> (key2, value2) -> NULL
[2] -> NULL
[3] -> (key3, value3) -> (key7, value7) -> NULL
[4] -> (key4, value4) -> NULL
```

## 2. 해시 함수의 역할

### 2.1 해시 값 계산
- 키(key)를 입력받아 해시 값(hash value)을 생성
- 해시 값을 버킷 배열 크기로 나눈 나머지가 버킷 인덱스가 됨
- `bucket_index = hash(key) % bucket_count`

### 2.2 기본 해시 함수
- 정수형: 키 자체를 해시 값으로 사용
- 문자열: 각 문자의 ASCII 값을 조합하여 계산
- 사용자 정의 타입: 커스텀 해시 함수 필요

## 3. 충돌 처리 (Collision Resolution)

### 3.1 체이닝 (Chaining) 방식
- 대부분의 구현에서 사용하는 방식
- 동일한 버킷에 여러 요소가 매핑되면 연결 리스트로 연결
- 각 버킷은 같은 해시 값을 가진 요소들의 체인을 유지

### 3.2 충돌 발생 시 처리 과정
1. 해시 함수로 버킷 인덱스 계산
2. 해당 버킷에 이미 요소가 있는지 확인
3. 있다면 체인의 끝에 새 요소 추가
4. 키가 같은 요소가 있다면 값만 업데이트

## 4. 삽입 (Insert) 과정

### 4.1 요소 삽입 단계
1. **해시 계산**: `hash_value = hash_function(key)`
2. **버킷 결정**: `bucket_index = hash_value % bucket_count`
3. **키 검색**: 해당 버킷에서 동일한 키 존재 여부 확인
4. **삽입/업데이트**: 
   - 키가 없으면 새 요소 삽입
   - 키가 있으면 기존 값 업데이트

### 4.2 Load Factor 관리
- `Load Factor = 요소 개수 / 버킷 개수`
- 기본적으로 Load Factor가 1.0을 초과하면 rehashing 발생
- 버킷 개수를 대략 2배로 증가시킴

## 5. 검색 (Find) 과정

### 5.1 검색 단계
1. **해시 계산**: 찾고자 하는 키의 해시 값 계산
2. **버킷 접근**: 해당 버킷으로 이동
3. **선형 검색**: 버킷 내에서 키를 순차적으로 비교
4. **결과 반환**: 찾으면 iterator 반환, 못 찾으면 end() 반환

### 5.2 시간 복잡도
- **평균**: O(1) - 이상적인 해시 분포 시
- **최악**: O(n) - 모든 요소가 같은 버킷에 집중된 경우

## 6. 삭제 (Erase) 과정

### 6.1 삭제 단계
1. **요소 검색**: 삭제할 요소를 먼저 찾음
2. **연결 해제**: 체인에서 해당 노드를 제거
3. **메모리 해제**: 삭제된 요소의 메모리 반환
4. **크기 감소**: 전체 요소 개수 감소

## 7. 리해싱 (Rehashing)

### 7.1 리해싱 발생 조건
- Load Factor가 임계값(보통 1.0)을 초과할 때
- 수동으로 `rehash()` 함수 호출 시

### 7.2 리해싱 과정
1. **새 버킷 배열 생성**: 기존 크기의 약 2배
2. **모든 요소 재배치**: 기존 요소들을 새 해시 값으로 재계산하여 이동
3. **기존 배열 해제**: 이전 버킷 배열 메모리 해제
4. **포인터 업데이트**: 내부 포인터를 새 배열로 변경

## 8. 메모리 구조

### 8.1 내부 데이터 구조
```cpp
class unordered_map {
    bucket_type* buckets;        // 버킷 배열
    size_t bucket_count;         // 버킷 개수
    size_t size;                 // 현재 요소 개수
    hasher hash_function;        // 해시 함수 객체
    key_equal key_eq;            // 키 비교 함수
    float max_load_factor;       // 최대 Load Factor
};
```

### 8.2 각 버킷의 구조
```cpp
struct bucket_node {
    std::pair<Key, Value> data;  // 키-값 쌍
    bucket_node* next;           // 다음 노드 포인터
};
```

## 9. 성능 특성

### 9.1 시간 복잡도
- **삽입**: 평균 O(1), 최악 O(n)
- **검색**: 평균 O(1), 최악 O(n)
- **삭제**: 평균 O(1), 최악 O(n)
- **리해싱**: O(n)

### 9.2 공간 복잡도
- **메모리 사용량**: O(n + m) (n: 요소 개수, m: 버킷 개수)
- **Load Factor**: 메모리 효율성과 성능의 트레이드오프

## 10. 최적화 기법

### 10.1 Robin Hood Hashing
- 일부 구현에서 사용하는 고급 기법
- 충돌 발생 시 더 효율적인 재배치 수행

### 10.2 버킷 크기 최적화
- 소수(prime number)를 버킷 크기로 사용하여 해시 분포 개선
- 2의 거듭제곱 크기 사용 시 비트 연산으로 모듈로 연산 최적화

이러한 동작 원리를 통해 `unordered_map`은 평균적으로 O(1)의 빠른 접근 시간을 제공하면서도 동적인 크기 조절이 가능한 효율적인 연관 컨테이너로 동작합니다.
