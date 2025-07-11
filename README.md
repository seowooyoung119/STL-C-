# STL-C++

## string
- .compare(인자)
- .length()

## vector
- vector<데이터 타입> 배열명
- push_back(인자)
- vector<int> 벡터명 (시작 위치, 끝위치) - 벡터배열의 일부를 잘아오고 싶을 때 새로 생성해서 가져오는 방법

  <br>

## utility
- pair<인자, 인자>
- make_pair(인자, 인자)

  <br>
## queue
최대 힙 : priority_queue<저장할_데이터_타입> 큐변수명; <br>
최소 힙 priority_queue<저장할_데이터_타입, 실제로_저장할_컨테이너, 비교함수> 큐변수명; <br>
| 메서드     | 기본형             | 설명                       | 시간 복잡도   |
| ------- | --------------- | ------------------------ | -------- |
| `push`  | `큐변수명.push(값);` | 큐에 새로운 값을 넣는다            | O(log N) |
| `pop`   | `큐변수명.pop();`   | top에 있는 가장 우선순위 높은 값을 제거 | O(log N) |
| `top`   | `큐변수명.top();`   | 가장 우선순위 높은 값을 반환 (삭제 X)  | O(1)     |
| `size`  | `큐변수명.size();`  | 현재 큐 안에 있는 요소 수 반환       | O(1)     |
| `empty` | `큐변수명.empty();` | 큐가 비어있는지 확인 (비었으면 true)  | O(1)     |



  <br>

## unordered_map
- unordered_map<키, 값> 배열명
- .find(인자)
- .end()
- .count(인자)
- .contains(인자)

## algorithm

- reserve(뒤집을 범위의 시작,뒤집을 범위의 끝); - 시간 복잡도 O(n / 2) 또는 O(n)
- sort(시작 위치, 끝 위치)
- max(비교a, 비교b) - 둘 중 큰 값을 반환
- min(비교a, 비교b) - 둘 중 작은 값을 반환

## typeinfo
- typeid()

## cmath
- round(인자) - 반올림 (주의 : 딱 0.5면? 0에서 먼쪽으로 숫자를 늘린다.)
- ceil(인자) - 반올림
- floor(인자) - 반올림


## sstream

- stringstream stream(s) 이후 stream >> a >> b >> c;  : 기존의 문자열을 공백으로 분리해서 데이터 타입에 맞게 캐스팅해줌
- stringstream ss; 이후 ss << hex << 10; : 10진수 -> 16진수 (hex 라는 조작자를 쓰면 된다.)
- stringstream ss(hexstr); 이후 ss >> hex >> a; : 10진수 <- 16진수 (hex 라는 조작자를 쓰면 된다.)



