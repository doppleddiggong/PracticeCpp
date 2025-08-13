#include <iostream>
#include <cstdint>
#include <iomanip>
#include <string>
#include <sstream>
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

namespace PERMUTATION
{
    void permutation()
    {
        std::vector<int> nums = { 1,2,3,4 };
        int r = 3;

        std::sort(nums.begin(), nums.end());

        std::vector<bool> mask(nums.size(), false);
        std::fill(mask.begin(), mask.begin() + r, true);

        do
        {
            for (int i = 0; i < nums.size(); ++i)
            {
                if (mask[i])
                    std::cout << nums[i] << " ";
            }
            std::cout << "\n";
        } while (std::prev_permutation(mask.begin(), mask.end()));
    }
}

namespace BIT
{
    string ConvertBit(int value)
    {
        string ret;
        int num_bits = sizeof(int) * 8;

        for (int i = num_bits - 1; i >= 0; --i)
        {
            int b = (value >> i) & 1;
            ret += (b ? '1' : '0');

            // 8비트마다 공백 추가 (맨 마지막 비트 제외)
            if (i % 8 == 0 && i != 0)
                ret += ' ';
        }

        return ret;
    }

    void TestBitOperator()
    {
        unsigned int a = 5;   // 0101
        unsigned int b = 3;   // 0011


        cout << "(  a  ) : " << ConvertBit(a) << endl;
        cout << "(  a  ) : " << a << endl;

        cout << "(  b  ) : " << ConvertBit(b) << endl;
        cout << "(  b  ) : " << b << endl;

        {
            int v = (a & b);

            cout << "(a & b) : " << ConvertBit(v) << endl;    // AND → 1
            cout << "(a & b) : " << v << endl;    // AND → 1
        }

        {
            int v = (a | b);

            cout << "(a | b) : " << ConvertBit(v) << endl;    // OR → 7
            cout << "(a | b) : " << v << endl;                // OR → 7
        }

        {
            int v = (a ^ b);

            cout << "(a ^ b) : " << ConvertBit(v) << endl;    // XOR → 6
            cout << "(a ^ b) : " << v << endl;                // XOR → 6
        }

        {
            int v = (~a);

            cout << "(~a) : " << ConvertBit(v) << endl;       // NOT → 4294967290 (unsigned int 보수)
            cout << "(~a) : " << v << endl;                   // NOT → 4294967290 (unsigned int 보수)
        }

        {
            int v = (a << 1);

            cout << "(a << 1) : " << ConvertBit(v) << endl;  // Left shift → 10
            cout << "(a << 1) : " << v << endl;              // Left shift → 10
        }

        {
            int v = (a >> 1);

            cout << "(a >> 1) : " << ConvertBit(v) << endl;  // Right shift → 2
            cout << "(a >> 1) : " << v << endl;  // Right shift → 2
        }
    }

    const int FLAG_IDLE = 1 << 0;    // 00001
    const int FLAG_MOVE = 1 << 1;    // 00010
    const int FLAG_ATK  = 1 << 2;    // 00100
    const int FLAG_STUN = 1 << 3;    // 01000
    const int FLAG_DIE  = 1 << 4;    // 10000

    struct BitState
    {
        int CurrentState = 0;

        void AddState(int state)
        {
            CurrentState |= state;
        }

        void RemoveState(int state)
        {
            CurrentState &= ~state;
        }

        bool HasState(int state)
        {
            return (CurrentState & state) != 0;
        }

        void PrintCurrentState()
        {
            cout << "CurrentState : "
                << ((CurrentState & FLAG_IDLE) ? "IDLE " : " ")
                << ((CurrentState & FLAG_MOVE) ? "MOVE" : " ")
                << ((CurrentState & FLAG_ATK) ? "ATK " : " ")
                << ((CurrentState & FLAG_STUN) ? "STUN " : " ")
                << ((CurrentState & FLAG_DIE) ? "DIE " : " ")
                << endl;
        }

        void Test()
        {
            // EMPTY
            PrintCurrentState();

            // MOVE
            AddState(FLAG_MOVE);
            PrintCurrentState();

            // MOVE STUN
            AddState(FLAG_STUN);
            PrintCurrentState();

            // MOVE
            RemoveState(FLAG_STUN);
            PrintCurrentState();
        }
    };
}

namespace CustomColor
{
    struct BitColor
    {
        unsigned int value; // 0xAARRGGBB

        BitColor() : value(0xFF000000) {} // 기본 불투명 검정

        // 채널 추출
        unsigned char GetA() const { return (value >> 24) & 0xFF; }
        unsigned char GetR() const { return (value >> 16) & 0xFF; }
        unsigned char GetG() const { return (value >> 8) & 0xFF; }
        unsigned char GetB() const { return (value >> 0) & 0xFF; }

        // 채널 설정
        void SetA(unsigned char a) { value = (value & 0x00FFFFFF) | (a << 24); }
        void SetR(unsigned char r) { value = (value & 0xFF00FFFF) | (r << 16); }
        void SetG(unsigned char g) { value = (value & 0xFFFF00FF) | (g << 8); }
        void SetB(unsigned char b) { value = (value & 0xFFFFFF00) | b; }

        void Print() const {
            cout << "ARGB: 0x" << hex << value << dec << "  ("
                << "A=" << (int)GetA() << ", "
                << "R=" << (int)GetR() << ", "
                << "G=" << (int)GetG() << ", "
                << "B=" << (int)GetB() << ")\n";
        }
    };

    struct FColor
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;

        FColor(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255)
            : R(r), G(g), B(b), A(a) {
        }

        // 16진수 문자열 (#RRGGBB 또는 #RRGGBBAA) 생성자
        static FColor FromHex(const std::string& hexCode)
        {
            std::string code = hexCode;
            if (!code.empty() && code[0] == '#')
                code.erase(0, 1);

            if (code.length() != 6 && code.length() != 8)
                throw std::invalid_argument("Hex code must be 6 or 8 characters");

            auto HexToByte = [](const std::string& str) { return static_cast<uint8_t>(std::stoi(str, nullptr, 16)); };

            FColor color;
            color.R = HexToByte(code.substr(0, 2));
            color.G = HexToByte(code.substr(2, 2));
            color.B = HexToByte(code.substr(4, 2));
            color.A = (code.length() == 8) ? HexToByte(code.substr(6, 2)) : 255;
            return color;
        }

        // ARGB 정수로 변환
        uint32_t ToARGB() const
        {
            return (static_cast<uint32_t>(A) << 24) |
                (static_cast<uint32_t>(R) << 16) |
                (static_cast<uint32_t>(G) << 8) |
                (static_cast<uint32_t>(B) << 0);
        }

        void Print() const
        {
            std::cout << "ARGB: 0x" << std::hex << std::setw(8) << std::setfill('0') << ToARGB()
                << std::dec << " (R=" << (int)R
                << ", G=" << (int)G
                << ", B=" << (int)B
                << ", A=" << (int)A << ")\n";
        }

        void Test()
        {
            FColor color1; // 기본 검정
            color1.Print();

            FColor color2 = FColor::FromHex("FFCA50");
            color2.Print();

            FColor color3 = FColor::FromHex("#3366CCFF");
            color3.Print();
        }
    };
}


int main()
{
    //BIT::BitState bitState;
    //bitState.Test();

    //CustomColor::BitColor bitColor;
    //bitColor.value = 0xff00ff;
    //bitColor.Print();

    //CustomColor::FColor fColor;
    //fColor.Test();

    return 0;
}