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

namespace P_131128
{
    string solution(string X, string Y) {

        std::unordered_map<int, int> x_map;
        std::unordered_map<int, int> y_map;

        for(auto& c : X)
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

        for( auto& x : x_map)
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
            for( auto& c : descSet)
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
                else if(l_dist < r_dist)
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

            if( _on_stage == 0 || _pass_stage == 0)
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
        for( const auto& pair : map_sort)
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
                i_vector.push_back( arr1[i][j] + arr2[i][j] );
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
                if (day_s > record[k-1])
                    record[k-1] = day_s;
            }

            std::sort(record.begin(), record.end(), std::greater<int>());
            answer.push_back( record.back() );
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
                cur.second + DIRECTION[dir].second );
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

        for (int x = board.size()-1; x >= 0; x--)
        {
            for (int y = 0; y < board[x].size(); y++)
            {
                if(board[x][y] != 0 )
                    map[y].push(board[x][y]);
            }
        }

        int answer = 0;

        for (auto p : moves)
        {
            if (!map[p-1].empty())
            {
                auto cur_pick = map[p-1].top();
                map[p-1].pop();

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
        for(auto v : arr)
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
            if (v % i == 0 )
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
            if (map[v] > 0 && v > before )
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
            if (lcm % min == 0 )
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
            for (int y = x+1; y < number.size(); y++)
            {
                for (int z = y+1; z < number.size(); z++)
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
            answer.push_back(last*2);

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
        else if( a == b && b == c )
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
        auto after = my_string.substr(s+ overwrite_string.length());
        return before+ overwrite_string+ after;
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

        for (int i = n-1; i >= 1; i--)
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
        map.resize(num+1);

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
            auto ban = report_msg.substr(space_pos+1);

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
        
        for(int i = 0; i < row; i++ )
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
            if ( v % divisor == 0 )
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

            for (int i = start; i < start+10; i++)
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

        EventRecord( string _uid, string _event )
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
            auto split_pos2 = c.find(' ', split_pos+1);

            string event = c.substr(0, split_pos);
            string uid = c.substr(split_pos+1, split_pos2 - split_pos-1);
            string name = c.substr(split_pos2+1);

            list.push_back(EventRecord(uid, event));

            if (event != "Leave")
                map[uid] = name;
        }

        vector<string> answer;

        for (auto data : list)
        {
            if (data.event == "Change")
                continue;

            answer.push_back( data.GetMessage(map[data.uid]) );
        }

        return answer;
    }
}

namespace P_42579
{
    vector<int> solution(vector<string> genres, vector<int> plays)
    {
        // 장르, 토탈 재생횟수
        std::unordered_map<string, int> genres_play_count;
        // 장르, 플레이수, 인덱스
        std::unordered_map<string, std::multimap<int, int, std::greater<int>>> genres_play;

        for (int i = 0; i < genres.size(); i++)
        {
            genres_play[ genres[i] ].emplace( plays[i], i);
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
            for(auto song : genres_play[gen.first])
            {
                if(song_count > 0)
                {
                    answer.push_back(song.second);
                    song_count--;
                }
            }
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
        for (auto kv : map )
            answer *= (kv.second+1);
        return answer-1;
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
            while ( pos + len <= msg.size() && 
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

        while(map.size() >= 2 && map.top() < K)
        {
            int first = map.top();
            map.pop();

            int sec= map.top();
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
        return answer;
    }
}

void main(void)
{
    return;
}
