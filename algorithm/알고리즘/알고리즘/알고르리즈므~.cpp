#include <algorithm>


reverse(str.begin(), str.end()

//==================================//
// string 예시 //

#include <algorithm>
#include <string>

	std::reverse(first, last);

매개변수

first : 뒤집을 범위의 시작 반복자
last : 뒤집을 범위의 끝 반복자(포함되지 않음)

동작 방식
함수는 지정된 범위의 요소들을 제자리에서(in - place) 뒤집습니다.
즉, 새로운 메모리를 할당하지 않고 기존 컨테이너의 요소들의 순서만 바꿉니다.

//==================================//
// vector 예시 //

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::reverse(vec.begin(), vec.end());

    for (int n : vec) {
        std::cout << n << " ";  // 5 4 3 2 1
    }
    return 0;
}


//==================================//
시간 복잡도

O(n / 2) 또는 O(n) : n은 뒤집을 요소의 개수
양 끝에서 중앙으로 이동하면서 요소를 교환하므로 실제로는 n / 2번의 교환이 발생


//==================================//
주의사항

반복자가 양방향 반복자(bidirectional iterator) 이상이어야 함
범위가 유효해야 함(first <= last)
원본 컨테이너가 수정되므로 const 컨테이너에는 사용 불가

이 함수는 문자열 뒤집기, 배열 순서 변경 등 다양한 상황에서 유용하게 사용됩니다.