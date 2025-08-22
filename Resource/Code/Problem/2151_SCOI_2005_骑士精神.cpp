#include <unordered_set>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <queue>

const std::string Standard("111110111100*110000100000");
constexpr int
    dx[]{-2, -2, -1, -1, 1, 1, 2, 2},
    dy[]{-1, 1, -2, 2, -2, 2, -1, 1};

inline std::pair<int, int> convert(const int &_N) { return std::make_pair(_N / 5, _N % 5); }
inline int convert(const std::pair<int, int> &_P) { return _P.first * 5 + _P.second; }

template <typename _Tp>
inline void clear(_Tp &_X) { _X = _Tp(); }

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        typedef std::tuple<int, int, int, std::string, int> Status;
        static std::priority_queue<Status, std::vector<Status>, std::greater<>> q;
        static std::unordered_set<std::string> vis;
        static std::string now;
        clear(q);
        vis.clear();
        now = std::string();
        static std::string temporaryString;
        for (int i = 0; i < 5; ++i)
            std::cin >> temporaryString, now += temporaryString;
        static int evaluation, spacePosition;
        evaluation = 0, spacePosition = -1;
        for (int i = 0; i < 25; evaluation += now[i] != Standard[i], ++i)
            if (now[i] == '*')
                spacePosition = i;
        q.emplace(evaluation, 0, evaluation, now, spacePosition);
        static int ans;
        ans = -1;
        vis.emplace(now);
        while (!q.empty())
        {
            auto [_ignored, step, nowEvaluation, present, nowSpacePosition] = q.top();
            q.pop();
            if (!nowEvaluation)
            {
                ans = step;
                break;
            }
            auto [nowX, nowY] = convert(nowSpacePosition);
            for (int i = 0; i < 8; ++i)
            {
                static int nextX, nextY;
                nextX = nowX + dx[i], nextY = nowY + dy[i];
                if (nextX < 0 || nextX > 4 || nextY < 0 || nextY > 4)
                    continue;
                static int nextIndex, nextEvaluation;
                static std::string nextStatus;
                nextIndex = convert({nextX, nextY});
                nextEvaluation = nowEvaluation;
                nextStatus = present;
                if (nextStatus[nowSpacePosition] == Standard[nowSpacePosition])
                    ++nextEvaluation;
                if (nextStatus[nextIndex] == Standard[nextIndex])
                    ++nextEvaluation;
                std::swap(nextStatus[nextIndex], nextStatus[nowSpacePosition]);
                if (nextStatus[nowSpacePosition] == Standard[nowSpacePosition])
                    --nextEvaluation;
                if (nextStatus[nextIndex] == Standard[nextIndex])
                    --nextEvaluation;
                if (vis.find(nextStatus) == vis.end() && nextEvaluation + step <= 15)
                    q.emplace(step + 1 + nextEvaluation, step + 1, nextEvaluation, nextStatus, nextIndex), vis.emplace(present);
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}