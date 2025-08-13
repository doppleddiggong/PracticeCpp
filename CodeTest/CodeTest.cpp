#include <iostream>
#include <iterator>
#include <chrono>
#include <functional>

#include <algorithm>
#include <numeric>
#include <optional>

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

namespace P_43163 {
    int solution(std::string begin, std::string target, std::vector<std::string> words);
}

namespace P_120836
{
    int solution(int n) {
        
        std::set < std::pair<int, int> > set;

        for (int i = 1; i <= n; i++)
        {
            if ( n % i == 0 )
            {
                set.insert(std::make_pair(i, n / i));
            }
        }

        return set.size();
    }
}

namespace P_120905
{
    vector<int> solution(int n, vector<int> numlist) {
        vector<int> answer;

        for (auto num : numlist)
        {
            if (num % n == 0)
            {
                answer.push_back(num);
            }
        }
 

        return answer;
    }
}

void main(void)
{
    auto c1 = P_120905::solution(3, { 4, 5, 6, 7, 8, 9, 10, 11, 12 });
    auto c2 = P_120905::solution(5, { 1, 9, 3, 10, 13, 5 });
    auto c3 = P_120905::solution(12, { 2, 100, 120, 600, 12, 12 } );
}
