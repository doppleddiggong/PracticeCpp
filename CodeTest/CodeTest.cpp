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

void main(void)
{
    auto c1 = P_43163::solution("hit", "cog", { "hot", "dot", "dog", "lot", "log", "cog" });
}
