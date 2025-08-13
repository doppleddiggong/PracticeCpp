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

namespace P_131128
{
    string solution(string X, string Y) {

        std::unordered_map<int, int> x_map;
        std::unordered_map<int, int> y_map;

        for (auto& c : X)
        {
            int num = c - '0';
            if (x_map.find(num) == x_map.end())
                x_map[num] = 1;
            else
                x_map[num]++;
        }

        for (auto& c : Y)
        {
            int num = c - '0';
            if (y_map.find(num) == y_map.end())
                y_map[num] = 1;
            else
                y_map[num]++;
        }

        std::multiset<int, std::greater<int>> descSet;

        for (auto& x : x_map)
        {
            if (y_map.find(x.first) != y_map.end())
            {
                int minCount = std::min(x.second, y_map[x.first]);
                for (int i = 0; i < minCount; i++)
                {
                    descSet.insert(x.first);
                }
            }
        }

        if (descSet.size() == 0)
        {
            return "-1";
        }
        else if (*descSet.begin() == 0)
        {
            return "0";
        }
        else
        {
            string ret;
            for (auto& c : descSet)
                ret += std::to_string(c);

            return ret;
        }
    }
}

namespace P_67256
{
    string solution(vector<int> numbers, string hand) {
        std::unordered_map<int, std::pair<int, int>> map{
            { 1, {0, 0} }, { 2, {0, 1} }, { 3, {0, 2} },
            { 4, {1, 0} }, { 5, {1, 1} }, { 6, {1, 2} },
            { 7, {2, 0} }, { 8, {2, 1} }, { 9, {2, 2} },
            { -100, {3, 0} }, { 0, {3, 1} }, { 100, {3, 2} }
        };

        auto calc = [&map](const int& start, const int& target) {
            auto s = map[start]; auto e = map[target];
            return abs(s.first - e.first) + abs(s.second - e.second);
            };

        int l_pos = -100, r_pos = 100;

        string answer = "";

        for (const auto& num : numbers)
        {
            if (num == 1 || num == 4 || num == 7)
            {
                answer.append("L");
                l_pos = num;
            }
            else if (num == 3 || num == 6 || num == 9)
            {
                answer.append("R");
                r_pos = num;
            }
            else
            {
                int l_dist = calc(l_pos, num);
                int r_dist = calc(r_pos, num);

                if (l_dist == r_dist)
                {
                    if (hand == "left")
                    {
                        answer.append("L");
                        l_pos = num;
                    }
                    else
                    {
                        answer.append("R");
                        r_pos = num;
                    }
                }
                else if (l_dist < r_dist)
                {
                    answer.append("L");
                    l_pos = num;
                }
                else
                {
                    answer.append("R");
                    r_pos = num;
                }
            }
        }

        return answer;
    }
}

namespace P_42889
{
    vector<int> solution(int N, vector<int> stages) {

        // 스테이지, 스테이지 체류자
        std::map<int, int> on_stage;
        // 스테이지, 스테이지 통과자
        std::unordered_map<int, int> pass_stage;
        // 스테이지, 실패율
        std::unordered_map<int, float> rate;

        for (const auto& stage : stages)
            on_stage[stage]++;

        int user_count = (int)stages.size();
        for (const auto& stage : on_stage)
        {
            pass_stage[stage.first] = user_count;
            user_count -= stage.second;
        }

        for (int i = 1; i <= N; i++)
        {
            auto _on_stage = on_stage[i];
            auto _pass_stage = pass_stage[i];

            if (_on_stage == 0 || _pass_stage == 0)
            {
                rate.insert(std::pair<int, float>(i, 0.0f));
                continue;
            }
            else
            {
                float r = (float)_on_stage / _pass_stage;
                rate.insert(std::pair<int, float>(i, r));
            }
        }

        vector<std::pair<int, float>> map_sort(rate.begin(), rate.end());
        std::sort(map_sort.begin(), map_sort.end(), [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
            });

        vector<int> answer;
        for (const auto& pair : map_sort)
            answer.push_back(pair.first);

        return answer;
    }
}

namespace P_12950
{
    vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
        vector<vector<int>> answer;

        for (int i = 0; i < arr1.size(); i++)
        {
            vector<int> i_vector;
            for (int j = 0; j < arr1[i].size(); j++)
                i_vector.push_back(arr1[i][j] + arr2[i][j]);
            answer.push_back(i_vector);
        }

        return answer;
    }
}

namespace P_12915
{
    vector<string> solution(vector<string> strings, int n) {
        std::sort(strings.begin(), strings.end(),
            [&](const auto& first, const auto& second)
            {
                if (first[n] != second[n])
                    return first[n] < second[n];
                else
                    return first < second;
            });

        return strings;
    }
}

namespace P_138477
{
    vector<int> solution(int k, vector<int> score) {
        vector<int> answer;
        vector<int> record;

        for (const auto& day_s : score)
        {
            if (record.size() < k)
                record.push_back(day_s);
            else
            {
                if (day_s > record[k - 1])
                    record[k - 1] = day_s;
            }

            std::sort(record.begin(), record.end(), std::greater<int>());
            answer.push_back(record.back());
        }

        return answer;
    }
}

namespace P_49994
{
    int solution(string dirs)
    {
        std::unordered_map<char, std::pair<int, int>> DIRECTION
        {
            { 'L', std::make_pair(-1, 0)},
            { 'R', std::make_pair(1, 0)},
            { 'U', std::make_pair(0, 1)},
            { 'D', std::make_pair(0, -1)},
        };

        std::set<std::tuple<int, int, int, int>> record;
        std::pair<int, int> cur(0, 0);

        auto get_next_pos = [&](const char& dir) {
            return std::make_pair(
                cur.first + DIRECTION[dir].first,
                cur.second + DIRECTION[dir].second);
            };

        auto dist = [&](const int& x, const int& y) {
            return x - 5 + y - 5;
            };

        for (const auto& dir : dirs)
        {
            auto next = get_next_pos(dir);

            if (-5 <= next.first && next.first <= 5 &&
                -5 <= next.second && next.second <= 5)
            {
                int cur_dist = dist(cur.first, cur.second);
                int next_dist = dist(next.first, next.second);

                if (cur_dist < next_dist)
                {
                    record.insert(std::make_tuple(
                        cur.first, cur.second,
                        next.first, next.second));
                }
                else
                {
                    record.insert(std::make_tuple(
                        next.first, next.second,
                        cur.first, cur.second));
                }

                cur = next;
            }
        }

        return record.size();
    }
}

namespace P_76502
{
    bool checkClose(string s)
    {
        std::stack<char> stack;

        for (auto c : s)
        {
            if (c == '(' || c == '[' || c == '{')
                stack.push(c);
            else if (c == ')')
            {
                if (stack.size() > 0 && stack.top() == '(')
                    stack.pop();
                else
                    stack.push(c);
            }
            else if (c == ']')
            {
                if (stack.size() > 0 && stack.top() == '[')
                    stack.pop();
                else
                    stack.push(c);
            }
            else if (c == '}')
            {
                if (stack.size() > 0 && stack.top() == '{')
                    stack.pop();
                else
                    stack.push(c);
            }
        }

        return stack.size() == 0;
    }


    int solution(string s) {
        int answer = 0;

        for (int i = 0; i < s.length(); i++)
        {
            // 문자열을 회전시킨다
            string tmp(s);
            std::rotate(tmp.begin(), tmp.begin() + i, tmp.end());

            // 문자열이 모두 닫히는지 체크한다
            if (checkClose(tmp))
                answer += 1;
        }

        return answer;
    }
}

namespace P_12973
{
    int solution(string s)
    {
        std::stack<char> stack;
        for (auto c : s)
        {
            if (stack.empty())
                stack.push(c);
            else
            {
                if (c == stack.top())
                    stack.pop();
                else
                    stack.push(c);
            }
        }

        if (stack.empty())
            return 1;
        else
            return 0;
    }
}

namespace P_42584
{
    vector<int> solution(vector<int> p) {
        vector<int> answer;

        for (int i = 0; i < p.size(); i++)
        {
            int time = 0;
            for (int j = i + 1; j < p.size(); j++)
            {
                time++;
                if (p[i] > p[j])
                    break;
            }

            answer.push_back(time);
        }

        return answer;
    }
}

namespace P_64061
{
    int solution(vector<vector<int>> board, vector<int> moves) {

        std::unordered_map<int, std::stack<int>> map;
        std::stack<int> reward;

        for (int x = board.size() - 1; x >= 0; x--)
        {
            for (int y = 0; y < board[x].size(); y++)
            {
                if (board[x][y] != 0)
                    map[y].push(board[x][y]);
            }
        }

        int answer = 0;

        for (auto p : moves)
        {
            if (!map[p - 1].empty())
            {
                auto cur_pick = map[p - 1].top();
                map[p - 1].pop();

                if (reward.empty())
                    reward.push(cur_pick);
                else
                {
                    if (reward.top() == cur_pick)
                    {
                        answer += 2;
                        reward.pop();
                    }
                    else
                        reward.push(cur_pick);
                }
            }
        }
        return answer;
    }
}


namespace P_81303
{
    string solution(int size, int cur_pos, vector<string> cmd)
    {
        list<int> table;
        for (int i = 0; i < size; i++)
            table.push_back(i);

        auto cursor = table.begin();
        std::advance(cursor, cur_pos);

        stack<pair<list<int>::iterator, int>> deleted;

        for (auto c : cmd)
        {
            auto split_pos = c.find(' ');

            string order;
            int move;

            if (split_pos != std::string::npos)
            {
                order = c.substr(0, split_pos);
                move = stoi(c.substr(split_pos + 1));
            }
            else
            {
                order = c;
            }

            if (order == "U")
            {
                for (int i = 0; i < move; i++)
                {
                    if (cursor != table.begin())
                    {
                        cursor--;
                    }
                }
            }
            else if (order == "D")
            {
                for (int i = 0; i < move; i++)
                {
                    if (cursor != table.end())
                    {
                        cursor++;
                    }
                }
            }

            else if (order == "C")
            {
                deleted.push({ cursor, *cursor });
                cursor = table.erase(cursor);
                if (cursor == table.end())
                    cursor = std::prev(table.end());
            }
            else if (order == "Z")
            {
                auto pair = deleted.top(); // 값을 복사
                auto pos = pair.first;
                auto val = pair.second;
                deleted.pop();

                // pos는 무효화되었을 수 있으므로 다시 위치를 찾아야 함
                // 여기서는 val을 이용해서 정렬 순서대로 다시 삽입
                auto it = table.begin();
                while (it != table.end() && *it < val)
                    ++it;

                table.insert(it, val);
            }
        }

        string result(size, 'X');
        for (int idx : table)
            result[idx] = 'O';

        return result;
    }
}

namespace P_12906
{
    vector<int> solution(vector<int> arr)
    {
        std::vector<int> answer;
        for (auto v : arr)
        {
            if (answer.size() == 0)
            {
                answer.push_back(v);
            }
            else
            {
                if (v != answer[answer.size() - 1])
                    answer.push_back(v);
            }
        }

        return answer;
    }
}

namespace P_12940
{
    vector<int> gcd(int v)
    {
        vector<int> answer;

        for (int i = 1; i <= v; i++)
        {
            if (v % i == 0)
            {
                answer.push_back(i);
            }
        }

        return answer;
    }

    vector<int> solution(int n, int m) {

        int before = 1;

        std::unordered_map<int, int> map;
        for (auto v : gcd(n))
            map[v]++;

        auto m_gcd = gcd(m);
        std::reverse(m_gcd.begin(), m_gcd.end());

        for (auto v : m_gcd)
        {
            if (map[v] > 0 && v > before)
            {
                before = v;
            }
        }

        int after;

        int min = std::min(n, m);
        int max = std::max(n, m);
        int lcm = max;

        while (true)
        {
            if (lcm % min == 0)
            {
                after = lcm;
                break;
            }
            else
            {
                lcm += max;
            }
        }

        return { before, after };
    }
}

namespace P_147355
{
    int solution(string t, string p) {

        int answer = 0;
        auto p_num = std::stoll(p);

        int length = t.size() - p.size();
        for (int i = 0; i <= length; i++)
        {
            string s = t.substr(i, p.size());
            auto s_num = std::stoll(s.c_str());

            if (s_num <= p_num)
                answer++;
        }

        return answer;
    }
}

namespace P_131705
{
    int solution(vector<int> number) {
        int answer = 0;
        for (int x = 0; x < number.size(); x++)
        {
            for (int y = x + 1; y < number.size(); y++)
            {
                for (int z = y + 1; z < number.size(); z++)
                {
                    if ((number[x] + number[y] + number[z]) == 0)
                    {
                        answer++;
                    }
                }
            }
        }


        return answer;
    }
}

namespace P_132267
{
    // a : 콜라를 받기위해 마트에 주어야 하는 병수
    // b : 빈병 a개를 가져다 주면 마트가 주는 콜라병수
    // n : 상빈이가 가지고 있는 빈 병수
    int solution(int a, int b, int n) {

        int empty = n;
        int answer = 0;

        while (empty >= a)
        {
            int coke = (empty / a);
            empty -= (coke * a);

            answer += (coke * b);
            empty += (coke * b);
        }

        return answer;
    }
}

namespace P_181927
{
    vector<int> solution(vector<int> num_list) {

        vector<int> answer(num_list.begin(), num_list.end());

        auto it = num_list.end();

        --it;
        auto last = *it;

        --it;
        auto last_prev = *it;

        if (last > last_prev)
            answer.push_back(last - last_prev);
        else
            answer.push_back(last * 2);

        return answer;
    }
}

namespace P_181930
{
    int solution(int a, int b, int c) {

        if (a != b && b != c && a != c)
        {
            return a + b + c;
        }
        else if (a == b && b == c)
        {
            auto first = a + b + c;
            auto second = pow(a, 2) + pow(b, 2) + pow(c, 2);
            auto third = pow(a, 3) + pow(b, 3) + pow(c, 3);

            return first * second * third;
        }
        else
        {
            auto first = a + b + c;
            auto second = pow(a, 2) + pow(b, 2) + pow(c, 2);
            return first * second;
        }

        return 0;
    }
}

namespace P_181943
{
    string solution(string my_string, string overwrite_string, int s) {
        auto before = my_string.substr(0, s);
        auto after = my_string.substr(s + overwrite_string.length());
        return before + overwrite_string + after;
    }
}

namespace P_43105
{
    int solution(vector<vector<int>> triangle) {
        for (int cur_floor = 1; cur_floor < triangle.size(); cur_floor++)
        {
            for (int room = 0; room < triangle[cur_floor].size(); room++)
            {
                int from_left = 0;
                if (room > 0)
                    from_left = triangle[cur_floor - 1][room - 1];

                int from_right = 0;
                if (room < triangle[cur_floor - 1].size())
                    from_right = triangle[cur_floor - 1][room];

                triangle[cur_floor][room] += std::max(from_left, from_right);
            }
        }

        auto max = std::max_element(triangle.back().begin(), triangle.back().end());
        return *max;
    }
}

namespace P_12924
{
    int solution(int n) {

        int answer = 1;

        for (int i = n - 1; i >= 1; i--)
        {
            int target = i;
            for (int j = i - 1; j >= 1; j--)
            {
                target += j;

                if (target == n)
                {
                    answer++;
                    break;
                }
                else if (target > n)
                {
                    break;
                }
            }
        }

        return answer;
    }
}

namespace P_134240
{
    string solution(vector<int> food) {

        vector<int> calc;

        for (int i = 1; i < food.size(); i++)
        {
            for (int v = 0; v < food[i] / 2; v++)
            {
                calc.push_back(i);
            }
        }

        string answer;
        for (auto it = calc.begin(); it != calc.end(); ++it)
            answer += std::to_string((*it));

        answer += "0";

        for (auto it = calc.rbegin(); it != calc.rend(); ++it)
            answer += std::to_string((*it));

        return answer;
    }
}

namespace P_12977
{
    std::vector<bool> map;

    void GenerateMap()
    {
        int num = 2997;
        map.resize(num + 1);

        std::fill(map.begin(), map.end(), true);

        for (int i = 2; i <= num; i++)
        {
            if (!map[i])
                continue;

            for (int j = i * i; j <= num; j += i)
                map[j] = false;
        }
    }


    int solution(vector<int> nums) {
        GenerateMap();

        int answer = 0;

        for (int x = 0; x < nums.size(); x++)
        {
            for (int y = x + 1; y < nums.size(); y++)
            {
                for (int z = y + 1; z < nums.size(); z++)
                {
                    int target = nums[x] + nums[y] + nums[z];

                    if (map[target])
                        answer++;
                }
            }
        }

        return answer;
    }
}

namespace P_42576
{
    string solution(vector<string> participant, vector<string> completion)
    {
        std::unordered_map<std::string, int> map;
        for (const auto& name : participant)
            map[name]++;

        for (const auto& name : completion)
        {
            if (map.find(name) != map.end() &&
                map[name] > 0)
            {
                map[name]--;

                if (map[name] == 0)
                    map.erase(name);
            }
        }

        return map.begin()->first;
    }
}

namespace P_42577
{
    bool solution(vector<string> phone_book) {

        std::sort(phone_book.begin(), phone_book.end());

        for (auto it = phone_book.begin(); it != phone_book.end(); )
        {
            auto prev_it = it++;
            if (it == phone_book.end())
                return true;

            string first = (*prev_it);
            string second = (*it);
            string third = second.substr(0, first.length());
            if (first == third)
            {
                return false;
            }
        }

        return true;
    }
}

namespace P_92334
{
    vector<int> solution(vector<string> id_list, vector<string> report, int k) {

        std::unordered_map<string, std::unordered_set<string>> map;

        for (const auto& report_msg : report)
        {
            auto space_pos = report_msg.find(' ');

            auto reporter = report_msg.substr(0, space_pos);
            auto ban = report_msg.substr(space_pos + 1);

            map[ban].insert(reporter);
        }

        std::unordered_map<string, int> mail;

        for (const auto& id : id_list)
        {
            if (map[id].size() >= k)
            {
                for (auto c : map[id])
                {
                    mail[c]++;
                }
            }
        }

        vector<int> answer;
        for (const auto& id : id_list)
        {
            answer.push_back(mail[id]);
        }

        return answer;
    }
}

namespace P_72411
{
    std::unordered_set<string> combinations(const std::string& input, int r)
    {
        std::unordered_set<string> map;
        if (input.length() < r)
            return map;

        std::vector<bool> select(input.size(), false);
        std::fill(select.end() - r, select.end(), true);

        {
            std::string result;
            for (int i = 0; i < input.size(); i++)
            {
                if (select[i])
                {
                    result += input[i];
                }
            }

            map.insert(result);
        }

        while (std::next_permutation(select.begin(), select.end()))
        {
            std::string result;

            for (int i = 0; i < input.size(); i++)
            {
                if (select[i])
                {
                    result += input[i];
                }
            }

            map.insert(result);
        }

        return map;
    }

    vector<string> solution(vector<string> orders, vector<int> course) {
        std::sort(orders.begin(), orders.end());

        std::vector<std::string> answer;

        for (auto value : course)
        {
            std::unordered_map<string, int> map;

            int max_call = 2;
            for (auto combo : orders)
            {
                std::sort(combo.begin(), combo.end());

                auto combination = combinations(combo, value);
                for (auto c : combination)
                {
                    map[c]++;
                    max_call = std::max(max_call, map[c]);
                }
            }

            for (auto kv : map)
            {
                if (kv.second >= max_call)
                {
                    answer.push_back(kv.first);
                }
            }
        }

        std::sort(answer.begin(), answer.end());
        return answer;
    }
}

namespace P_72411
{
    vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {

        int row = arr1.size();
        int col = arr2[0].size();

        int col2 = arr1[0].size();

        vector<vector<int>> result(row, vector<int>(col, 0));

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                for (int k = 0; k < col2; k++)
                    result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }

        return result;
    }
}

namespace P_120817
{
    double solution(vector<int> numbers) {
        double sum = 0;
        for (auto c : numbers)
            sum += c;
        return sum / numbers.size();
    }
}

namespace P_120821
{
    vector<int> solution(vector<int> numbers) {

        vector<int> ret(numbers);
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
}

namespace P_87390
{
    vector<int> solution(int n, long long left, long long right) {

        //std::vector<std::vector<int>> data(n, std::vector<int>(n, 0));

        //for (int x = 0; x < n; x++)
        //{
        //    for (int y = 0; y < n; y++)
        //    {
        //        data[x][y] = std::max(x, y) + 1;
        //    }
        //}
        vector<int> answer;
        for (long long pos = left; pos <= right; pos++)
        {
            int x = pos % n;
            int y = pos / n;

            int value = std::max(x, y) + 1;

            answer.push_back(value);
        }

        return answer;
    }
}

namespace P_12910
{
    vector<int> solution(vector<int> arr, int divisor) {
        vector<int> answer;

        for (auto v : arr)
        {
            if (v % divisor == 0)
            {
                answer.push_back(v);
            }
        }

        if (answer.size() > 0)
        {
            std::sort(answer.begin(), answer.end());
            return answer;
        }
        else
        {
            return { -1 };
        }
    }
}

namespace P_131127
{
    int solution(vector<string> want, vector<int> number, vector<string> discount) {
        int answer = 0;

        std::unordered_map<string, int> origin_map;

        for (int i = 0; i < want.size(); i++)
            origin_map[want[i]] = number[i];

        for (int start = 0; start <= discount.size() - 10; start++)
        {
            std::unordered_map<string, int> copy_map(origin_map);

            for (int i = start; i < start + 10; i++)
            {
                if (copy_map.find(discount[i]) != copy_map.end())
                {
                    copy_map[discount[i]]--;
                }
            }

            int sum = std::count_if(copy_map.begin(), copy_map.end(),
                [](auto kv) { return kv.second; });

            if (sum == 0)
                answer++;
        }

        return answer;
    }
}

namespace P_42888
{
    struct EventRecord
    {
        string uid;
        string event;

        EventRecord(string _uid, string _event)
        {
            uid = _uid;;
            event = _event;
        }


        string GetMessage(string name)
        {
            if (event == "Enter")
                return name + "님이 들어왔습니다.";
            else if (event == "Leave")
                return name + "님이 나갔습니다.";
        }
    };

    std::unordered_map<string, string> map;

    vector<string> solution(vector<string> record) {

        std::vector<EventRecord> list;

        for (auto c : record)
        {
            auto split_pos = c.find(' ');
            auto split_pos2 = c.find(' ', split_pos + 1);

            string event = c.substr(0, split_pos);
            string uid = c.substr(split_pos + 1, split_pos2 - split_pos - 1);
            string name = c.substr(split_pos2 + 1);

            list.push_back(EventRecord(uid, event));

            if (event != "Leave")
                map[uid] = name;
        }

        vector<string> answer;

        for (auto data : list)
        {
            if (data.event == "Change")
                continue;

            answer.push_back(data.GetMessage(map[data.uid]));
        }

        return answer;
    }
}

namespace P_42578
{
    int solution(vector<vector<string>> clothes) {

        // type, has
        std::unordered_map< string, int> map;

        for (auto c : clothes)
        {
            auto type = c[1];
            map[type] += 1;
        }

        int answer = 1;
        for (auto kv : map)
            answer *= (kv.second + 1);
        return answer - 1;
    }
}

namespace P_17684
{
    std::unordered_map<string, int> map
    {
        {"A", 1 },
        {"B", 2 },
        {"C", 3 },
        {"D", 4 },
        {"E", 5 },
        {"F", 6 },
        {"G", 7 },
        {"H", 8 },
        {"I", 9 },
        {"J", 10 },
        {"K", 11 },
        {"L", 12 },
        {"M", 13 },
        {"N", 14 },
        {"O", 15 },
        {"P", 16 },
        {"Q", 17 },
        {"R", 18 },
        {"S", 19 },
        {"T", 20 },
        {"U", 21 },
        {"V", 22 },
        {"W", 23 },
        {"X", 24 },
        {"Y", 25 },
        {"Z", 26 },
    };

    vector<int> solution(string msg) {


        int nextIndex = 27;
        int pos = 0;
        vector<int> answer;

        while (pos < msg.size()) {
            int len = 1;

            // 가능한 가장 긴 문자열을 찾음
            while (pos + len <= msg.size() &&
                map.find(msg.substr(pos, len)) != map.end())
            {
                len++;
            }

            string found = msg.substr(pos, len - 1);
            answer.push_back(map[found]);

            // 사전에 새 항목 추가
            if (pos + len - 1 < msg.size())
            {
                string next = msg.substr(pos, len);
                map[next] = nextIndex++;
            }

            pos += found.size();
        }

        return answer;
    }
}

namespace P_42626
{
    // 섞은 음식의 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두 번째로 맵지 않은 음식의 스코빌 지수 * 2)
    int solution(vector<int> scoville, int K) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> map(scoville.begin(), scoville.end());

        int answer = 0;

        while (map.size() >= 2 && map.top() < K)
        {
            int first = map.top();
            map.pop();

            int sec = map.top();
            map.pop();

            map.push(first + sec * 2);
            answer++;
        }

        return (map.top() >= K) ? answer : -1;
    }
}

namespace P_42748
{
    vector<int> solution(vector<int> array, vector<vector<int>> commands) {
        vector<int> answer;

        for (auto cmd : commands)
        {
            auto array_begin = array.begin();
            array_begin += (cmd[0] - 1);

            auto array_end = array.begin();
            array_end += cmd[1];

            std::vector<int> queue(array_begin, array_end);
            std::sort(queue.begin(), queue.end());

            answer.push_back(queue[(cmd[2] - 1)]);
        }

        return answer;
    }
}

namespace P_120833
{
    vector<int> solution(vector<int> numbers, int num1, int num2) {
        vector<int> answer;

        for (int i = num1; i <= num2; i++)
            answer.push_back(numbers[i]);

        return answer;
    }
}

namespace P_120816
{
    int solution(int slice, int n) {
        return ceil(n / (float)slice);
    }
}

namespace P_43238
{
    long long solution(int n, vector<int> times) {
        long long left = 1;
        long long right = (long long)*max_element(times.begin(), times.end()) * n;
        long long answer = right;

        while (left <= right) {
            long long mid = (left + right) / 2;
            long long total = 0;

            for (int t : times) {
                total += mid / t;
                if (total >= n) // 오버플로우 방지 및 불필요한 계산 방지
                    break;
            }

            if (total >= n) {
                answer = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        return answer;
    }
}

namespace P_120841
{
    int solution(vector<int> dot) {
        int x = dot[0];
        int y = dot[1];

        if (x > 0 && y > 0)
            return 1;
        else if (x < 0 && y > 0)
            return 2;
        else if (x < 0 && y < 0)
            return 3;
        else if (x > 0 && y < 0)
            return 4;

        return 1;
    }
}

namespace P_120903
{
    int solution(vector<string> s1, vector<string> s2) {
        int answer = 0;

        for (auto s : s1)
        {
            if (std::find(s2.begin(), s2.end(), s) != s2.end())
            {
                answer++;
            }
        }

        return answer;
    }
}


namespace P_68937
{
    int getDistance(int start, int end, const vector<vector<int>>& adjacency)
    {
        if (start == end)
            return 0;

        vector<bool> visited(adjacency.size(), false);
        queue<pair<int, int>> q; // pair<node, distance>

        q.push({ start, 0 });
        visited[start] = true;

        while (!q.empty())
        {
            auto [cur, dist] = q.front();
            q.pop();

            for (int next : adjacency[cur])
            {
                if (!visited[next])
                {
                    if (next == end)
                        return dist + 1;

                    visited[next] = true;
                    q.push({ next, dist + 1 });
                }
            }
        }

        return -1; // 연결 안 됨
    }

    int solution(int n, vector<vector<int>> edges) {
        vector<vector<int>> adjacency(n + 1);

        for (const auto& e : edges)
        {
            adjacency[e[0]].push_back(e[1]);
            adjacency[e[1]].push_back(e[0]);
        }

        for (int i = 1; i <= n; ++i)
        {
            sort(adjacency[i].begin(), adjacency[i].end());
        }

        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);

        vector<bool> mask(n, false);
        fill(mask.begin(), mask.begin() + 3, true); // 3개 선택

        int answer = 0;

        do
        {
            vector<int> node;
            for (int i = 0; i < n; i++)
            {
                if (mask[i])
                    node.push_back(nums[i]);
            }

            for (int i = 0; i < (int)node.size() - 1; i++)
            {
                int dist = getDistance(node[i], node[i + 1], adjacency);

                if (dist == 2)
                    return 2;

                answer = max(answer, dist);
            }

        } while (prev_permutation(mask.begin(), mask.end()));

        return answer;
    }
}

namespace P_43163
{
    int similar(string begin, string target)
    {
        int ret = 0;
        for (int i = 0; i < begin.size(); i++)
        {
            if (begin[i] == target[i])
                ret++;
        }

        return ret;
    }

    int GetWords(string start, string target, vector<string> list, int count)
    {
        vector<string> ret;

        for (auto c : list)
        {
            int similar_count = similar(start, c);

            // 한글자 차이난것만 찾는다
            if (similar_count == start.length() - 1)
                ret.push_back(c);
        }

        vector<string> ret2(list);
        for (auto f : ret)
        {
            auto it = std::find(ret2.begin(), ret2.end(), f);
            ret2.erase(it);
        }

        for (auto n_start : ret)
        {
            if (n_start == target)
                return count + 1;
            else
            {
                int res = GetWords(n_start, target, ret2, count + 1);
                if (res != 0)
                    return res;
            }
        }

        return 0;
    }

    int solution(string begin, string target, vector<string> words) {

        if (std::find(words.begin(), words.end(), target) == words.end())
            return 0;

        int count = GetWords(begin, target, words, 0);
        return count;
    }
}

namespace P_12903
{
    // 단어 s의 가운데 글자를 반환하는 함수, 
    // solution을 만들어 보세요.
    // 단어의 길이가 짝수라면 가운데 두글자를 반환하면 됩니다.

    //cout << P_12903::solution("abcde") << endl;
    //cout << P_12903::solution("qwer") << endl;
    string solution(string s) {
        string answer(s);

        while (answer.length() > 2)
        {
            answer.erase(0, 1);
            answer.erase(answer.length() - 1, 1);
        }

        return answer;
    }
}

namespace P_12935
{
    // 정수를 저장한 배열, arr 에서 가장 작은 수를 제거한 배열을 리턴하는 함수, 
    // solution을 완성해주세요.
    // 단, 리턴하려는 배열이 빈 배열인 경우엔 배열에 - 1을 채워 리턴하세요.
    // 예를들어 arr이[4, 3, 2, 1]인 경우는[4, 3, 2]를 리턴 하고, 
    // [10]면[-1]을 리턴 합니다.
    vector<int> solution(vector<int> arr) {
        vector<int> answer;

        auto min = *min_element(arr.begin(), arr.end());

        arr.erase(std::remove_if(arr.begin(), arr.end(),
            [&](int num) { return num == min; })
        );

        if (arr.size() == 1)
            return vector<int> { -1 };
        else
            return arr;
    }
}

namespace P_70128
{
    int solution(vector<int> a, vector<int> b) {
        int ret = 0;

        for (int i = 0; i < a.size(); i++)
            ret += a[i] * b[i];

        return ret;
    }
}

namespace P_12922
{
    //길이가 n이고, "수박수박수박수...."와 같은 패턴을 유지하는 문자열을 리턴하는 함수, 
    // solution을 완성하세요. 
    // 예를들어 n이 4이면 "수박수박"을 리턴하고 
    // 3이라면 "수박수"를 리턴하면 됩니다.
    string solution(int n) {
        string answer = "";

        for (int i = 0; i < n; i++)
        {
            i & 1 ? answer += "박" : answer += "수";
        }

        return answer;
    }
}

namespace P_77884
{
    int solution(int left, int right) {

        auto GetDivisorCount = [](int value) {
            int count = 0;
            for (int i = 1; i <= value; ++i)
                if (value % i == 0)
                    ++count;
            return count;
            };

        int answer = 0;

        for (int i = left; i <= right; ++i)
        {
            int divisorCount = GetDivisorCount(i);
            if (divisorCount % 2 == 0)
                answer += i;
            else
                answer -= i;
        }

        return answer;
    }
}

namespace P_12917
{
    string solution(string s) {
        std::sort(s.rbegin(), s.rend());
        //        std::sort(s.begin(), s.end(), std::greater<char>());
        return s;
    }
}

namespace P_68935
{
    // https://school.programmers.co.kr/learn/courses/30/lessons/68935
    std::vector<int> ConvertToBase(int num)
    {
        std::vector<int> result;

        int target = num;
        while (target >= 3)
        {
            int quotient = target / 3;
            int remainder = target % 3;
            result.push_back(remainder);

            target = quotient;
        }

        result.push_back(target);
        return result;
    }

    int solution(int n) {

        int ret = 0;
        auto q = ConvertToBase(n);

        int index = 0;
        for (auto it = q.rbegin(); it != q.rend(); ++it)
            ret += ((*it) * std::pow(3, index++));

        return ret;
    }
}

namespace P_82612
{
    long long solution(int price, int money, int count)
    {
        long long answer = money;

        for (int i = 1; i <= count; i++)
            answer -= (price * i);
        return answer < 0 ? std::abs(answer) : 0;
    }
}

namespace P_176963
{
    vector<int> solution(vector<string> name,
        vector<int> yearning,
        vector<vector<string>> photo)
    {
        vector<int> answer;

        unordered_map<string, int> map;
        for (int i = 0; i < name.size(); i++)
            map[name[i]] = yearning[i];

        for (auto& p : photo)
        {
            int sum = 0;
            for (auto& name : p)
            {
                if (map.find(name) != map.end())
                    sum += map[name];
            }
            answer.insert(answer.end(), sum);
        }

        return answer;
    }
}

namespace P_136798
{
    //   int GetDivisorCount(int value)
    //   {
    //       int count = 0;
    //       for (int i = 1; i <= value; i++)
    //           if (value % i == 0)
    //               count++;

    //       return count;
       //}

    int solution(int number, int limit, int power) {
        int answer = 0;

        std::vector<int> divisorCount(number + 1, 0);

        for (int i = 1; i <= number; i++)
            for (int j = i; j <= number; j += i)
                divisorCount[j]++;

        for (int i = 1; i <= number; i++)
        {
            auto gdc = divisorCount[i];

            if (gdc > limit)
                gdc = power;

            answer += gdc;
        }

        return answer;
    }
}

namespace P_1845
{
    int solution(vector<int> nums)
    {
        std::set<int> temp(nums.begin(), nums.end());

        int findCount = nums.size() * 0.5f;
        if (temp.size() < nums.size() * 0.5f)
        {
            return temp.size();
        }
        else
        {
            return findCount;
        }
    }
}

namespace P_12918
{
    bool solution(string s) {

        vector<char> v(s.begin(), s.end());

        if (v.size() == 4 || v.size() == 6)
        {
            for (const auto& c : v)
            {
                if (c >= '0' && c <= '9')
                    continue;
                else
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}

namespace P_142086
{
    vector<int> solution(string s) {
        auto func = [&](int start_index, char find) -> int {
            int count = 0;
            for (int i = start_index - 1; i >= 0; i--)
            {
                if (s[i] == find)
                    return count + 1;
                else
                    count++;
            }
            return -1;
            };

        vector<int> answer;
        for (int i = 0; i < s.length(); i++)
        {
            answer.push_back(func(i, s[i]));
        }

        return answer;
    }
}

namespace P_42889
{
    std::vector<std::pair<string, int>> GetValue(const std::unordered_map<string, int>& data)
    {
        std::vector<std::pair<string, int>> ret(data.begin(), data.end());
        return ret;
    }
}

namespace P_159994
{
    string solution(
        vector<string> cards1,
        vector<string> cards2,
        vector<string> goal)
    {
        std::queue<string> q1;
        for (const auto& s : cards1)
            q1.push(s);

        std::queue<string> q2;
        for (const auto& s : cards2)
            q2.push(s);

        for (const auto& find : goal)
        {
            string q1_f = q1.size() > 0 ? q1.front() : "";
            string q2_f = q2.size() > 0 ? q2.front() : "";

            if (q1_f == find)
                q1.pop();
            else if (q2_f == find)
                q2.pop();
            else
                return "No";
        }

        return "Yes";
    }
}

namespace P_68644
{
    vector<int> solution(vector<int> numbers) {
        std::set<int> sum;

        for (int first = 0; first < numbers.size() - 1; first++)
        {
            for (int second = first + 1; second < numbers.size(); second++)
            {
                sum.insert(numbers[first] + numbers[second]);
            }
        }

        vector<int> answer(sum.begin(), sum.end());
        std::sort(answer.begin(), answer.end());
        return answer;
    }
}

namespace P_42586
{
    vector<int> solution(vector<int> progresses, vector<int> speeds)
    {
        std::map<int, int> work_map;
        for (int i = 0; i < progresses.size(); i++)
            work_map[i] = ceil((100 - progresses[i]) / speeds[i]);

        std::vector<int> answer;
        while (work_map.size() > 0)
        {
            auto kv_first = work_map.begin();

            int work_day = kv_first->first;
            int complete_day = kv_first->second;
            work_map.erase(kv_first);

            vector<int> remove_work;

            for (auto kv : work_map)
            {
                //?? >= ,  > 
                if (complete_day > kv.second)
                    remove_work.push_back(kv.first);
                else
                    break;
            }

            for (auto v : remove_work)
                work_map.erase(v);

            answer.push_back(1 + remove_work.size());
        }

        return answer;
    }
}

namespace P_12982
{
    int solution(vector<int> d, int budget) {

        std::sort(d.begin(), d.end());

        for (int i = 0; i < d.size(); i++)
        {
            auto it_end = std::prev(d.end(), i);
            auto sum = std::accumulate(d.begin(), it_end, 0);

            if (budget >= sum)
                return d.size() - i;
        }
    }
}

namespace P_12930_2
{
    string solution(string s) {
        // 1. 빈 문자열의 위치를 찾아낸다
        vector<int> space_pos;
        for (int i = 0; i < s.length();)
        {
            auto space = s.find(' ', i);
            if (space == std::string::npos)
                break;

            i += (space + 1);
            space_pos.push_back(space);
        }

        // 2. 빈 문자열을 기준으로 문자열을 잘라낸다
        vector<string> split_string;
        for (int i = 0; i < space_pos.size(); i++)
        {
            int start = 0;
            if (i > 0)
                start = space_pos[i - 1] + 1;

            int end = space_pos[i] - start;
            auto s_2 = s.substr(start, end);

            split_string.push_back(s_2);
        }

        // 3. 마지막 문자열까지 붙여준다
        auto s_3 = s.substr(space_pos[space_pos.size() - 1] + 1);
        split_string.push_back(s_3);

        // 4. 문자열을 변환한다
        for (int i = 0; i < split_string.size(); i++)
        {
            auto& target = split_string[i];
            for (int i = 0; i < target.length(); i++)
            {
                if (i == 0 || i % 2 == 0)
                    target[i] = std::toupper(target[i]);
                else
                    target[i] = std::tolower(target[i]);
            }

            if (i != split_string.size() - 1)
                target += " ";
        }

        // 5. 문자열을 합치고 리턴한다
        std::string answer;
        for (auto str : split_string)
            answer += str;
        return answer;
    }
}

namespace P_12930
{
    string solution(string s)
    {
        int count = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
            {
                count = 0;
            }
            else
            {
                if (count % 2 == 0)
                {
                    s[i] = std::toupper(s[i]);
                    count++;
                }
                else
                {
                    s[i] = std::tolower(s[i]);
                    count++;
                }
            }
        }

        return s;
    }
}

namespace P_12926
{
    string solution(string s, int n) {

        for (auto& c : s)
        {
            if (c == ' ')
                continue;

            int num = c;


            if ('A' <= num && num <= 'Z')
            {
                num += n;

                if (num > 'Z')
                    num -= ('z' - 'a' + 1);
                c = num;
            }
            else if ('a' <= num && num <= 'z')
            {
                num += n;

                if (num > 'z')
                    num -= ('z' - 'a' + 1);
                c = num;
            }
        }

        return s;
    }
}

namespace P_12901
{
    // 2016. 01. 01은 금요일입니다.

    vector<int> month_days = {
        0,
        31, 29, 31,
        30, 31, 30,
        31, 31, 30,
        31, 30, 31 };

    vector<string> week_days = {
        "FRI", "SAT", "SUN", "MON", "TUE", "WED", "THU" };

    string solution(int a, int b) {
        int after_day = 0;
        if (a != 1)
        {
            for (int i = 1; i < a; i++)
                after_day += month_days[i];
        }
        after_day += (b - 1);
        string answer = week_days[after_day % 7];
        return answer;
    }
}

namespace P_135808
{
    int solution(int k, int m, vector<int> score) {

        std::sort(score.begin(), score.end(), std::greater<int>());

        std::vector<int> box;
        int answer = 0;

        for (int i = 0; i < score.size(); i++)
        {
            box.push_back(score[i]);

            if (box.size() == m)
            {
                auto min = *min_element(box.begin(), box.end());
                answer += (min * box.size());

                // 다음 상자
                box.clear();
            }
        }

        return answer;
    }
}

namespace P_12921
{
    std::vector<bool> prime_map;

    void GenerateMap(int n)
    {
        prime_map.assign(n + 1, true); // ← 이게 핵심

        for (int i = 2; i <= n; i++)
            prime_map[i] = true;

        for (int i = 2; i * i <= n; i++)
        {
            if (!prime_map[i])
                continue;

            for (int j = i * i; j <= n; j += i)
            {
                // 소수가 아님
                prime_map[j] = false;
            }
        }
    }


    int solution(int n) {

        if (n == 2)
            return 1;
        // 소수 구분용 맵을 만듬
        GenerateMap(n);

        int answer = 0;
        for (int i = 1; i < n; i++)
        {
            if (prime_map[i])
                answer++;
        }

        return answer;
    }
}

namespace P_42840
{
    std::vector<int> student1 = { 1, 2, 3, 4, 5 };
    std::vector<int> student2 = { 2, 1, 2, 3, 2, 4, 2, 5 };
    std::vector<int> student3 = { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 };

    vector<int> solution(vector<int> answers) {

        std::vector<int> result(3, 0);

        int t1_idx = 0;
        int t2_idx = 0;
        int t3_idx = 0;

        for (int i = 0; i < answers.size(); i++)
        {
            int v1 = student1[i % student1.size()];
            int v2 = student2[i % student2.size()];
            int v3 = student3[i % student3.size()];

            if (answers[i] == v1)
                result[0]++;
            if (answers[i] == v2)
                result[1]++;
            if (answers[i] == v3)
                result[2]++;
        }

        std::vector<int> answer;

        int max = *std::max_element(result.begin(), result.end());
        for (int i = 0; i < result.size(); i++)
        {
            if (result[i] == max)
                answer.push_back(i + 1);
        }

        return answer;
    }
}

namespace P_12949
{
    vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
        vector<vector<int>> answer;
        return answer;
    }
}

namespace P_42583
{
    int solution(int bridge_length, int weight, vector<int> truck_weights) {
        int turn = 0;

        queue<int> truck_queue;
        for (auto v : truck_weights)
            truck_queue.push(v);

        // index, truck_state
        // 0 : 다리에 오른다
        // 1 : 다리를 지나간다
        // 2 : 다리를 지나갔다
        std::unordered_map<int, int> bride_truck;

        while (truck_queue.size() > 0 ||
            bride_truck.size() > 0)
        {
            // 다리위의 차량 무게
            int bridge_weight = 0;

            vector<int> remove_truck;

            // 다리위에 있는 트럭의 상태값을 증가시킨다
            for (auto& kv : bride_truck)
            {
                kv.second += 1;

                if (kv.second == bridge_length)
                    remove_truck.push_back(kv.first);
                else
                    bridge_weight += truck_weights[kv.first];
            }

            for (auto v : remove_truck)
                bride_truck.erase(v);

            if (bridge_weight <= weight &&
                truck_queue.size() > 0)
            {
                auto truck_queue_weight = truck_queue.front();

                // 다리위에 있는 트럭과 대기열의 트럭의 무게를 비교한다.
                if (bridge_weight + truck_queue_weight <= weight)
                {
                    bridge_weight += truck_queue_weight;
                    truck_queue.pop();

                    bride_truck.insert(std::make_pair(truck_weights.size() - (truck_queue.size() + 1), 0));
                }
            }

            turn++;
        }

        return turn;
    }
}

namespace P_12981
{
    vector<int> solution(int n, vector<string> words) {

        std::unordered_map<string, int> map;

        char last_char;

        for (int i = 0; i < words.size(); i++)
        {
            auto verse = words[i];

            if (i != 0)
            {
                // 끝말 잇기 실패
                if (last_char != verse[0])
                    return { (i % n) + 1, (i / n) + 1 };
            }

            // 중복 단어 처리
            map[verse]++;
            if (map[verse] > 1)
                return { (i % n) + 1, (i / n) + 1 };

            last_char = verse[verse.size() - 1];
        }

        return { 0,0 };
    }
}

namespace P_81301
{
    int solution(string s) {
        int answer = 0;

        string findNumber;

        for (int pos = 0; pos < s.size(); pos++)
        {
            char c = s[pos];

            if (isdigit(c))
                findNumber += c;
            else
            {
                string find = s.substr(pos, 3);
                if (find == "zer")
                {
                    findNumber += '0';
                    pos += 3;
                }
                else if (find == "one")
                {
                    findNumber += '1';
                    pos += 2;
                }
                else if (find == "two")
                {
                    findNumber += '2';
                    pos += 2;
                }
                else if (find == "thr")
                {
                    findNumber += '3';
                    pos += 4;
                }
                else if (find == "fou")
                {
                    findNumber += '4';
                    pos += 3;
                }
                else if (find == "fiv")
                {
                    findNumber += '5';
                    pos += 3;
                }
                else if (find == "six")
                {
                    findNumber += '6';
                    pos += 2;
                }
                else if (find == "sev")
                {
                    findNumber += '7';
                    pos += 4;
                }
                else if (find == "eig")
                {
                    findNumber += '8';
                    pos += 4;
                }
                else if (find == "nin")
                {
                    findNumber += '9';
                    pos += 3;
                }
            }
        }

        return std::stoi(findNumber);
    }
}

namespace P_42579
{
    vector<int> solution_2(vector<string> genres, vector<int> plays)
    {
        // 장르, 토탈 재생횟수
        std::unordered_map<string, int> genres_play_count;
        // 장르, 플레이수, 인덱스
        std::unordered_map<string, std::multimap<int, int, std::greater<int>>> genres_play;

        for (int i = 0; i < genres.size(); i++)
        {
            genres_play[genres[i]].emplace(plays[i], i);
            genres_play_count[genres[i]] += plays[i];
        }

        // 장르, 토탈 재생횟수 정렬
        std::vector< std::pair<string, int>> genres_sort(genres_play_count.begin(), genres_play_count.end());
        std::sort(genres_sort.begin(), genres_sort.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second; // 재생 수 기준 내림차순 정렬
            });

        vector<int> answer;
        for (auto& gen : genres_sort)
        {
            int song_count = min(2, (int)genres_play[gen.first].size());
            for (auto song : genres_play[gen.first])
            {
                if (song_count > 0)
                {
                    answer.push_back(song.second);
                    song_count--;
                }
            }
        }

        return answer;
    }

    vector<int> solution(vector<string> genres, vector<int> plays) {

        std::unordered_map<string, int> genres_map;

        for (int i = 0; i < genres.size(); i++)
            genres_map[genres[i]] += plays[i];

        std::vector<std::pair<string, int>> genres_vec(genres_map.begin(), genres_map.end());

        std::sort(genres_vec.begin(), genres_vec.end(),
            [](const std::pair<string, int>& a, const std::pair<string, int>& b) {
                return a.second > b.second;
            });

        vector<int> answer;

        for (int i = 0; i < genres_vec.size(); i++)
        {
            // 장르명으로 된 데이터를 기반
            // 플레이수, 인덱스
            std::vector<std::pair<int, int>> plays_vec;

            int min_v = std::min(2, static_cast<int>(genres.size()));

            for (int j = 0; j < genres.size(); j++)
            {
                if (genres_vec[i].first == genres[j])
                    plays_vec.push_back(std::make_pair(plays[j], j));

                if (plays_vec.size() >= 2)
                    break;
            }

            std::sort(plays_vec.begin(), plays_vec.end(),
                [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                    return a.first > b.first;
                });

            for (auto c : plays_vec)
                answer.push_back(c.second);
        }

        return answer;
    }
}

namespace P_12985
{
    int solution(int n, int a, int b)
    {
        int answer = 0;

        while (a != b)
        {
            a = ceil((float)a / 2);
            b = ceil((float)b / 2);

            answer++;
        }

        return answer;
    }
}

namespace P_120824
{
    vector<int> solution(vector<int> num_list) {
        vector<int> answer{ 0, 0 };

        for (auto n : num_list)
        {
            if (n % 2 == 0)
                answer[0]++;
            else
                answer[1]++;
        }

        return answer;
    }
}

namespace P_120822
{
    string solution(string my_string) {
        std::reverse(my_string.begin(), my_string.end());
        return my_string;
    }
}

namespace P_120814
{
    int solution(int n) {

        return ceil(n / 7.0f);
    }
}

namespace P_42861
{
    vector<int> island(101);

    bool OrderBy(const std::vector<int>& a, const std::vector<int>& b)
    {
        return a[2] < b[2];
    }

    int findParent(int idx)
    {
        if (island[idx] == idx)
            return idx;
        return island[idx] == findParent(island[idx]);
    }

    int solution(int n, vector<vector<int>> costs)
    {
        int answer = 0;

        // 0. 섬 저장
        for (int i = 0; i < n; i++)
            island[i] = i;

        // 1. 비용을 오름차순으로 정렬
        std::sort(costs.begin(), costs.end(), OrderBy);

        for (int i = 0; i < costs.size(); i++)
        {
            int start = findParent(costs[i][0]);
            int end = findParent(costs[i][1]);
            int cost = costs[i][2];

            // 2. cycle이 만들어지지 않으면 다리 추가
            if (start != end)
            {
                answer += cost;
                island[end] = start;
            }
        }

        return answer;
    }
}

namespace P_120847
{
    int solution(vector<int> numbers) {
        std::sort(numbers.begin(), numbers.end(), std::greater<int>());
        return numbers[0] * numbers[1];
    }
}

namespace P_120906
{
    int solution(int n) {

        int answer = 0;
        string sum = std::to_string(n);
        for (auto c : sum)
        {
            if (c == '0')
                continue;
            answer += (c - '0');
        }

        return answer;
    }
}

namespace P_120889
{
    int solution(vector<int> sides) {
        std::sort(sides.begin(), sides.end(), std::greater<int>());
        return (sides[0] >= sides[1] + sides[2]) ? 2 : 1;
    }
}

namespace P_77486
{
    // <판매원 이름, 추천인 이름>
    std::unordered_map<string, string> map;

    // <판매원 이름, 수익>
    std::unordered_map<string, int> reward;

    void AddReward(string target, int price)
    {
        int my_reward = ceil(price * 0.9f);
        int up_reward = price - my_reward;

        if (up_reward > 0)
        {
            // 나한테 돈을 준다
            reward[target] += my_reward;

            // 추천인에게 상납한다
            AddReward(map[target], up_reward);
        }
        else
        {
            reward[target] += price;
        }
    }

    vector<int> solution(
        vector<string> enroll,
        vector<string> referral,
        vector<string> seller,
        vector<int> amount)
    {
        reward.clear();
        map.clear();

        for (int i = 0; i < enroll.size(); i++)
            map[enroll[i]] = referral[i];

        for (int i = 0; i < amount.size(); i++)
            AddReward(seller[i], amount[i] * 100);

        vector<int> answer;
        for (int i = 0; i < enroll.size(); i++)
        {
            if (reward.find(enroll[i]) != reward.end())
                answer.push_back(reward[enroll[i]]);
            else
                answer.push_back(0);
        }

        return answer;
    }
}

namespace P_161989
{
    int solution(int n, int m, vector<int> section) {

        vector<bool> wall;
        for (int i = 0; i < n; i++)
        {
            auto find = std::find(section.begin(), section.end(), i + 1);

            if (find != section.end())
            {
                wall.push_back(false);
            }
            else
            {
                wall.push_back(true);
            }
        }

        int answer = 0;

        for (int i = 0; i < wall.size(); i++)
        {
            if (wall[i] == false)
            {
                int draw = std::min(i + m, static_cast<int>(wall.size()));

                for (int j = i; j < draw; j++)
                {
                    wall[j] = true;
                }

                answer++;
            }
        }

        return answer;
    }
}

namespace P_133499
{
    std::vector<string> w{ "aya", "ye", "woo", "ma" };
    std::vector<string> ng{ "ayaaya", "yeye", "woowoo", "mama" };
    int solution(vector<string> babbling) {

        int answer = 0;
        for (auto& v : babbling)
        {
            bool blocked = false;

            for (auto& s : ng)
            {
                if (v.find(s) != std::string::npos)
                {
                    blocked = true;
                    break;
                }
            }

            if (blocked)
            {
                v = "ZZZ";
                continue;
            }

            for (auto& s : w)
            {
                size_t pos = 0;
                while ((pos = v.find(s)) != std::string::npos)
                    v.replace(pos, s.length(), "_");
            }
        }

        for (auto& v : babbling)
        {
            bool alpha = false;
            if (v == "ZZZ")
            {
                alpha = true;
            }
            else
            {
                for (auto c : v)
                {
                    if ('a' <= c && c < 'z')
                    {
                        alpha = true;
                        break;
                    }
                }
            }

            if (!alpha)
                answer++;
        }

        return answer;
    }
}

namespace P_340199
{
    bool CheckSize(vector<int> wallet, vector<int> bill)
    {
        int wallet_min = min(wallet[0], wallet[1]);
        int wallet_max = max(wallet[0], wallet[1]);

        int bill_min = min(bill[0], bill[1]);
        int bill_max = max(bill[0], bill[1]);

        return wallet_min < bill_min || wallet_max < bill_max;
    }

    int solution(vector<int> wallet, vector<int> bill) {

        int answer = 0;

        while (CheckSize(wallet, bill))
        {
            if (bill[0] > bill[1])
                bill[0] *= 0.5f;
            else
                bill[1] *= 0.5f;

            answer++;
        }

        return answer;
    }
}

namespace P_155652
{
    char move(char c, int index, string& skip)
    {
        for (int i = 0; i < index; i++)
        {
            c += 1;
            if (c > 'z')
                c += ('a' - 'z' - 1);

            if (skip.find(c) != std::string::npos)
                i--;
        }

        return c;
    }

    string solution(string s, string skip, int index) {
        for (auto& c : s)
        {
            if (skip.find(c) == std::string::npos)
                c = move(c, index, skip);
        }

        return s;
    }
}