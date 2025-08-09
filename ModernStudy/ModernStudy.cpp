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

namespace CONST_INT_CONST
{
    class Practice
    {
    public:
        static int instance_count;
        static int create_count;

        Practice() {
            instance_count++;
            create_count++;
        }

        ~Practice() {
            instance_count--;
        }
    };

    int Practice::instance_count = 0;
    int Practice::create_count = 0;


    // 매개 변수가 int
    class ConstPractice1 : Practice
    {
    private:
        int m_nValue;

    public:
        ConstPractice1() : m_nValue(0) {
        };

        void Practice(int practice)
        {
            m_nValue += practice;
            practice = m_nValue;
        }
    };

    // 매개 변수가 int&
    class ConstPractice2
    {
    private:
        int m_nValue;

    public:
        ConstPractice2() : m_nValue(0) {}

        void Practice(int& practice)
        {
            m_nValue += practice;
            practice = m_nValue;
        }
    };

    // 매개 변수가 const int x
    class ConstPractice3
    {
    private:
        int m_nValue;

    public:
        ConstPractice3() : m_nValue(0) {}

        void Practice(const int practice)
        {
            m_nValue += practice;
            // practice = m_nValue; // ❌ 컴파일 에러: const 값에 할당 불가
        }
    };

    // 매개 변수가 const int& x
    class ConstPractice4
    {
    private:
        int m_nValue;

    public:
        ConstPractice4() : m_nValue(0) {}

        void Practice(const int& practice)
        {
            m_nValue += practice;
            // practice = m_nValue; // ❌ 컴파일 에러: const 참조에 할당 불가
        }
    };

    // 리턴이 const int 
    class ConstPractice5
    {
    private:
        int m_nValue;

    public:
        ConstPractice5() : m_nValue(0) {}

        const int Practice(const int& practice)
        {
            m_nValue += practice;
            // practice = m_nValue; // ❌ 컴파일 에러
            return m_nValue;
        }
    };

    // 리턴이 const int&
    class ConstPractice6
    {
    private:
        int m_nValue;

    public:
        ConstPractice6() : m_nValue(0) {}

        const int& Practice(const int& practice)
        {
            m_nValue += practice;
            // x = m_nValue; // ❌ 컴파일 에러
            return m_nValue;
        }
    };


    // const 함수
    class ConstPractice7
    {
    private:
        int m_nValue;

    public:
        ConstPractice7() : m_nValue(0) {}

        void Practice(const int& practice) const
        {
            //m_nValue += practice;
            // x = m_nValue; // ❌ 컴파일 에러
            //return m_nValue;
        }
    };

    // mutable 키워드
    class ConstPractice8
    {
    private:
        mutable int m_nValue;

    public:
        ConstPractice8() : m_nValue(0) {}

        void Practice(const int& practice) const
        {
            m_nValue += practice;
            //x = m_nValue; // ❌ 컴파일 에러
            //return m_nValue;
        }
    };


    // int* const 
    class ConstPractice9
    {
    private:
        int m_nValue;

    public:
        ConstPractice9() : m_nValue(0) {}

        int Practice(int* const practice)
        {
            // 상수 포인터 to int
            m_nValue += *practice;
            *practice = m_nValue;
            //			practice = &m_nValue; // ❌ 컴파일 에러: const 포인터는 재할당 불가
            return m_nValue;
        }
    };

    // const int*
    class ConstPractice10
    {
    private:
        int m_nValue;

    public:
        ConstPractice10() : m_nValue(0) {}

        // int const* practice
        int Practice(const int* practice)
        {
            // 포인터 to 상수 int
            //m_nValue += practice;
            //x = m_nValue; // ❌ 컴파일 에러
            return m_nValue;
        }
    };

    // const int* const
    class ConstPractice11
    {
    private:
        int m_nValue;

    public:
        ConstPractice11() : m_nValue(0) {}

        // int const* practice
        int Practice(const int* const practice)
        {
            // 포인터 to 상수 int
            //m_nValue += practice;
            //x = m_nValue; // ❌ 컴파일 에러
            return m_nValue;
        }
    };

    // int& const
    class ConstPractice12
    {
    private:
        int m_nValue;

    public:
        ConstPractice12() : m_nValue(0) {}

        int Practice(const int& const practice)
        {
            m_nValue += practice;
            //x = m_nValue; // ❌ 컴파일 에러
            return m_nValue;
        }
    };

    // const int const
    class ConstPractice13
    {
    private:
        int m_nValue;

    public:
        ConstPractice13() : m_nValue(0) {}

        int Practice(const int const practice)
        {
            m_nValue += practice;
            //x = m_nValue; // ❌ 컴파일 에러
            return m_nValue;
        }
    };

    class People
    {
    private:
        int m_nAge;

    public:
        People() : m_nAge(100) {}
        People(int age) : m_nAge(age) {}

        void SetAge(int age)
        {
            m_nAge = age;
        }

        void SetAge(char* age)
        {
            m_nAge = atoi(age);
        }
    };


    void solution()
    {
        {
            ConstPractice1* p1 = nullptr;

            ConstPractice1 value = ConstPractice1();
            ConstPractice1& p2 = value;

            // err, 비 const 참조에 대한 초기값은 lvalue여야 합니다
            // ConstPractice1& p3 = ConstPractice1();
        }

        {
            // 스택에 생성
            ConstPractice1 p_stack = ConstPractice1();
            p_stack.Practice(10);

            // 힙에 생성
            ConstPractice1* p_heap = new ConstPractice1();
            p_heap->Practice(10);

            int x = 10;
            int* px = &x;
            int px2 = *px;
            int& rx = x;

            int* p_int = new int(100);
            int& r1 = *p_int;
            int& r2 = r1;

            ConstPractice1 practice_stack = ConstPractice1();
            ConstPractice1* p_practice_heap = new ConstPractice1();
            ConstPractice1* p_nullptr = nullptr;
        }


        {
            // nullptr이란 무엇인가?
            std::nullptr_t np = nullptr;
            std::cout << static_cast<void*>(np) << std::endl;
            std::cout << NULL << std::endl;
            std::cout << 0 << std::endl;

            std::cout << std::is_same<decltype(nullptr), std::nullptr_t>::value << std::endl;
        }

        {
            // 함수 오버로딩
            People people;
            people.SetAge(NULL);
            people.SetAge(nullptr);
        }

        {
            // const int const

            int tmp = 5;
            auto tmp2 = new int(5);
            auto tmp3 = new int(5);

            const int        practice1 = tmp;
            int const        practice2 = tmp;
            const int const  practice3 = tmp;

            const int& practice4 = tmp;
            int& const       practice5 = tmp;
            const int& const practice6 = tmp;

            int* const       practice7 = tmp2;
            const int* const practice8 = tmp2;
            const int* practice9 = tmp2;
        }
    }
}

namespace LAMBDA
{
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
    }

    int main(void) {

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

namespace VECTOR_UNORDEREDSET
{
    void solution()
    {
        // 백만
        constexpr int N = 1'000'000;
        // 99만9999를 찾는다, 강제로 탐색 시간 늘리기, 최악의 경우
        int target = N - 1;

        // 데이터 준비
        std::vector<int> vec;
        std::unordered_set<int> uset;
        std::set<int> oset;

        for (int i = 0; i < N; ++i) {
            vec.push_back(i);
            uset.insert(i);
            oset.insert(i);
        }

        // vector 탐색 시간 측정
        auto start = chrono::high_resolution_clock::now();
        auto it_vec = std::find(vec.begin(), vec.end(), target);
        auto end = chrono::high_resolution_clock::now();
        std::cout << "vector find: "
            << chrono::duration_cast<chrono::microseconds>(end - start).count()
            << " us\n";

        // unordered_set 탐색 시간 측정
        start = chrono::high_resolution_clock::now();
        auto it_uset = uset.find(target);
        end = chrono::high_resolution_clock::now();
        std::cout << "unordered_set find: "
            << chrono::duration_cast<chrono::microseconds>(end - start).count()
            << " us\n";

        // set 탐색 시간 측정
        start = chrono::high_resolution_clock::now();
        auto it_oset = oset.find(target);
        end = chrono::high_resolution_clock::now();
        std::cout << "set find: "
            << chrono::duration_cast<chrono::microseconds>(end - start).count()
            << " us\n";
    }
}


int main()
{
    std::cout << "Hello World!\n";
}