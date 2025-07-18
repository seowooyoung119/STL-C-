# C++ std::map 동작 원리 상세 가이드

## 개요

`std::map`은 키-값 쌍을 저장하는 연관 컨테이너로, 내부적으로 **Red-Black Tree**라는 자가 균형 이진 검색 트리를 사용하여 구현됩니다.

## 내부 구조

### Red-Black Tree 특성

`std::map`의 핵심 동작 원리는 Red-Black Tree의 특성에 기반합니다:

1. **모든 노드는 빨간색 또는 검은색**
2. **루트 노드는 항상 검은색**
3. **빨간색 노드의 자식은 반드시 검은색**
4. **모든 리프 노드(NIL)는 검은색**
5. **루트에서 임의의 리프까지의 경로에 있는 검은색 노드의 개수는 동일**

이러한 특성으로 인해 트리의 높이가 항상 O(log n)으로 유지됩니다.

### 노드 구조

```cpp
template<typename Key, typename Value>
struct MapNode {
    std::pair<const Key, Value> data;  // 키-값 쌍
    MapNode* parent;                   // 부모 노드
    MapNode* left;                     // 왼쪽 자식
    MapNode* right;                    // 오른쪽 자식
    Color color;                       // RED 또는 BLACK
};
```

## 주요 연산의 동작 원리

### 검색 (Find)

1. **루트부터 시작하여 이진 검색 수행**
2. **비교 연산자를 통해 키 비교**
3. **찾는 키가 현재 노드보다 작으면 왼쪽 서브트리로**
4. **찾는 키가 현재 노드보다 크면 오른쪽 서브트리로**
5. **키를 찾거나 NIL 노드에 도달할 때까지 반복**

**시간 복잡도**: O(log n)

### 삽입 (Insert)

#### 1단계: 기본 BST 삽입
1. **루트부터 시작하여 삽입 위치 탐색**
2. **비교 연산을 통해 적절한 위치 찾기**
3. **새 노드를 빨간색으로 삽입**

#### 2단계: Red-Black Tree 특성 복원
삽입 후 Red-Black Tree의 특성이 위반될 수 있으므로 **재균형화(Rebalancing)** 수행:

**Case 1: 삽입된 노드가 루트**
- 노드를 검은색으로 변경

**Case 2: 부모가 검은색**
- 아무 작업 불필요

**Case 3: 부모와 삼촌이 모두 빨간색**
- 부모와 삼촌을 검은색으로 변경
- 할아버지를 빨간색으로 변경
- 할아버지에서 다시 검사

**Case 4: 부모는 빨간색, 삼촌은 검은색**
- 회전(Rotation) 수행하여 균형 복원

### 삭제 (Erase)

#### 1단계: 노드 찾기 및 삭제 준비
1. **삭제할 노드 탐색**
2. **자식 노드 개수에 따른 처리**:
   - **리프 노드**: 직접 삭제
   - **자식 1개**: 자식으로 대체
   - **자식 2개**: 중위 후속자(inorder successor)로 대체

#### 2단계: Red-Black Tree 특성 복원
삭제된 노드가 검은색이었다면 Black Height 위반 가능성:

**삭제 후 재균형화 과정**:
1. **형제 노드의 색상 확인**
2. **형제의 자식들의 색상 확인**
3. **적절한 회전 및 색상 변경 수행**

### 회전 (Rotation)

Red-Black Tree의 균형을 유지하기 위한 핵심 연산:

#### 좌회전 (Left Rotation)
```
    x               y
   / \             / \
  α   y    →      x   γ
     / \         / \
    β   γ       α   β
```

#### 우회전 (Right Rotation)
```
      y           x
     / \         / \
    x   γ  →    α   y
   / \             / \
  α   β           β   γ
```

## 메모리 관리

### 노드 할당
- **기본적으로 std::allocator 사용**
- **사용자 정의 할당자 지원**
- **노드별 동적 할당**

### 메모리 레이아웃
```cpp
// 실제 메모리 구조 (단순화)
[Header Node] → [Root Node] → [Internal Nodes] → [Leaf Nodes]
     ↓              ↓              ↓                ↓
   size, etc    Key-Value     Key-Value        Key-Value
```

## 반복자 동작 원리

### 구조
```cpp
template<typename T>
class map_iterator {
    Node* current;
    
public:
    // 중위 순회(inorder traversal)를 통한 순차 접근
    iterator& operator++();  // 다음 노드로 이동
    iterator& operator--();  // 이전 노드로 이동
};
```

### 순회 방식
1. **중위 순회(Inorder Traversal) 사용**
2. **왼쪽 서브트리 → 현재 노드 → 오른쪽 서브트리**
3. **정렬된 순서로 요소 접근 보장**

#### 다음 노드 찾기 (operator++)
1. **오른쪽 자식이 있으면**: 오른쪽 서브트리의 최소값
2. **오른쪽 자식이 없으면**: 현재 노드가 왼쪽 자식인 첫 번째 조상

#### 이전 노드 찾기 (operator--)
1. **왼쪽 자식이 있으면**: 왼쪽 서브트리의 최대값
2. **왼쪽 자식이 없으면**: 현재 노드가 오른쪽 자식인 첫 번째 조상

## 정렬 유지 메커니즘

### 비교 함수 (Compare)
```cpp
template<typename Key, typename Value, typename Compare = std::less<Key>>
class map {
    Compare comp;  // 비교 함수 객체
    
    // 모든 삽입/검색 시 comp 사용
    bool isLess(const Key& a, const Key& b) const {
        return comp(a, b);
    }
};
```

### 정렬 보장
1. **삽입 시 비교 함수를 통해 적절한 위치 결정**
2. **중위 순회를 통해 정렬된 순서 유지**
3. **키의 불변성 보장 (const Key)**

## 성능 특성

### 시간 복잡도
- **검색, 삽입, 삭제**: O(log n)
- **순회**: O(n)

### 공간 복잡도
- **저장 공간**: O(n)
- **추가 오버헤드**: 포인터 3개 + 색상 정보 (노드당)

### 캐시 지역성
- **연속된 메모리 배치 아님**
- **포인터를 통한 접근으로 캐시 미스 가능성**
- **깊이가 log n으로 제한되어 접근 횟수는 적음**

## 특수 케이스

### 빈 맵 처리
- **더미 헤더 노드 사용**
- **begin()과 end()가 동일한 위치**

### 중복 키 처리
- **삽입 시 기존 키 발견하면 삽입 실패**
- **operator[]는 기존 값 수정**

### 예외 안전성
- **Strong Exception Safety 보장**
- **삽입/삭제 실패 시 원본 상태 유지**
