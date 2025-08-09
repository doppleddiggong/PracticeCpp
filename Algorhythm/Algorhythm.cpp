#include <iostream>
#include <iterator>
#include <chrono>
#include <functional>

#include <algorithm>
#include <numeric>

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

namespace LAMBDA
{
    // [캡처리스트](파라미터 리스트)->반환타입 {함수 본문};
    // 람다는 클래스다.
    // 람다는 익명 클래스다.
    // c++에서는 로컬 클래스 선언을 허용한다

    void test() {
        struct inner_class
        {
            int add(int a, int b)
            {
                return a + b;
            }
        };

        inner_class obj;
        auto c3 = obj.add(2, 3);
    }

    int lambdaPractice(void) {

        // 람다는 익명클래스 이다.
        auto add = [](int a, int b) {return a + b; };
        auto c1 = add(1, 2);
        auto c2 = add(2, 3);


        // [] 는 람다표현식이 자신을 둘러싸는 코드의 범위에서 변수를 캡처할 수 있게 해주는 도구이다.
        // -> 을 이용해서 반환 타입을 지정할 수 있다
        // 지정을 안하면 자동적으로 추론해줌
        auto add2 = [](int a, int b) -> float {return a + b; };
        auto add3 = [](float a, double b) { return a + b; };
        auto add4 = [](int a, double b) { return a + b; };

        // 에러남, string에는 int와 + 가가능한 오퍼레이터가 없으니깐.
        // auto add10 = [](string a, double b) { return a + b; };


        auto add5 = [c1, c2]() { return c1 + c2; };

        // 이건 안됌.
        // auto add6 = [c1, c2]() { c1 = 10; c2 = 20; };

        auto add7 = [&c1, &c2]() { c1 = 10; c2 = 20; };
        add7();

        // 이건 안됌.
        // = c1을 const로 가져온다는 얘기라서,
        //auto add8 = [=, &c2]() { c1 = 10; c2 = 20; };


        // &로 하겠다는 얘기는, 나는 여기에 선언된, 변수를 참조로 가져가서, 
        // 수정할거이라는 내용임
        auto add9 = [&]() {
            c1 = 100;
            c2 = 200;
            return c1 + c2; };

        auto add9value = add9();


        // 이건 안됌
        // =로 하겠다는 얘기는, 외부 변수를 값 복사하는 것이고,
        // 복사된 변수는 const 취급을 당함
        //auto add10 = [=]() {
        //    c1 = 100;
        //    c2 = 200;
        //    return c1 + c2; };

        // 이거는 됌
        // =로 가져간거니깐, 이집에 있는 변수를 이쁘게 읽을게요. 같은 얘기
        auto add11 = [=]() { return c1 + c2; };
        auto add11value = add11();


        // 혼합도 됌
        // 기본적으로 = 로 처리하는데,
        // add11value는 값을 수정좀 하겠수다.
        auto add12 = [=, &add11value]() {
            add11value = 300;
            return c1 + add11value; };
        auto add12value = add12();


        // 이건 안됌
        // 캡처리스트가 비어있음
        // 람다 내부에서 외부 변수를 안 보겠다고 했음
        // 그래서 컴파일러가 c1도, add11value 도 모름
        //auto add13 = []() {
        //    add11value = 300;
        //    return c1 + add11value; };



        // 람다를 파라미터로 받아 실행하고, 
        // 그 결과를 조합하는 함수형 스타일의 코드
        auto add_combine = [](auto someFunc) {
            int sum = someFunc(1, 2) + someFunc(4, 5);
            return sum;
            };

        // 이런식으로 람다함수를 매개변수로 전달해서 사용도 가능함
        auto combineValue = add_combine(add);

        // 좀더 복잡하게 짜면 이런것도 가능함
        // '동적 함수' 조합 구현
        auto mul = [](int a, int b) {
            return a * b; };
        auto combineValue2 = add_combine(mul);

        // 원래는 안되는데...
        // c1을 const로 쓰기로 했으니깐
        /*auto add14 = [c1, add11value]()
        {
                c1 = 10;
                return c1 + add11value;
        };*/

        // mutable 먹이면 또 가능함.
        // 그렇다고 c1 값이 또 10으로 된건 아님.
        auto add15 = [c1, add11value]()
            mutable
            {
                c1 = 10;
                return c1 + add11value;
            };

        auto add15value = add15();


        // 팩토리얼
        // #include <functional>
        std::function<int(int)> factorial = [&factorial](int i)
            {
                return i > 1 ? i * factorial(i - 1) : 1;
            };

        // 이것이 궁극의 람다인듯
        auto factorialValue = factorial(5);

        return 0;
    }
}

namespace TREE_NODE
{
    // 전위 순회
    string preorder(vector<int> nodes, int idx)
    {
        if (idx < nodes.size())
        {
            int value = nodes[idx];
            string ret = std::to_string(value) + " ";
            ret += preorder(nodes, idx * 2 + 1);
            ret += preorder(nodes, idx * 2 + 2);
            return ret;
        }

        return "";
    }


    // 중위 순회
    string inorder(vector<int> nodes, int idx)
    {
        if (idx < nodes.size())
        {
            string ret = inorder(nodes, idx * 2 + 1);
            ret += to_string(nodes[idx]) + " ";
            ret += inorder(nodes, idx * 2 + 2);
            return ret;
        }

        return "";
    }

    // 후위 순회
    string postorder(vector<int> nodes, int idx)
    {
        if (idx < nodes.size())
        {
            string ret = postorder(nodes, idx * 2 + 1);
            ret += postorder(nodes, idx * 2 + 2);
            ret += to_string(nodes[idx]) + " ";
            return ret;
        }

        return "";
    }
}

int main()
{
    std::cout << "Hello World!\n";
}