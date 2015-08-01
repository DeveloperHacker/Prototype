#ifndef LIGHT
#define LIGHT

#include "Core/maze.h"
#include "Core/point.h"

namespace Light
{
std::vector<std::vector<bool>> getLight(char gg, unsigned rev, std::vector<std::string>& map)
{
    std::vector<std::vector<bool>> light(map.size(), std::vector<bool>(map[0].size(), false));
    Point A(map[0].size() / 2, map.size() / 2);
    static const auto MaxDistance = 0.3;
    std::vector<Point> containedPoint;
    std::vector<char*> memoryCell;
    containedPoint.reserve(map.size() * map[0].size() / 4);

    for (auto& str : map) for (auto& val : str)
            if (val == gg)
            {
                val = ' ';
                memoryCell.push_back (&val);
            }
    light[A.y][A.x] = true;

    for (auto I = 0U; I < map.size(); ++I)
        for (auto J = 0U; J < map[0].size(); ++J)
        {
            Point B(J, I);
            if (light[I][J] == false && (rev*rev >= pow((A.x - B.x), 2) + pow((A.y - B.y), 2)))
            {
                bool logikInterm = true;
                containedPoint.clear();
                for (auto i = 0U; i < map.size(); ++i)
                    for (auto j = 0U; j < map[0].size(); ++j)
                    {
                        Point C(j, i);
                        if (C != A && C != B)
                        if (MaxDistance * (pow((B.x - A.x), 2) + pow((B.y - A.y), 2))
                                >= pow(((C.x - A.x)*(B.y - A.y) - (C.y - A.y)*(B.x - A.x)) , 2)
                                && ((B.x - A.x)*(C.x - A.x) + (B.y - A.y)*(C.y - A.y)) >= 0
                                && ((B.x - A.x)*(B.x - C.x) + (B.y - A.y)*(B.y - C.y)) >= 0)
                        {
                            if  (map[i][j] == ' ')
                            {
                                logikInterm = logikInterm && true;
                                containedPoint.push_back(Point(j, i));
                            }
                            else
                                logikInterm = false;
                        }
                    }
                light[I][J] = logikInterm;
                for (const auto& val : containedPoint)
                    light[val.y][val.x] = light[val.y][val.x] || logikInterm;
            }
        }

    for (auto val : memoryCell) *val = gg;
    return light;
}

std::vector<std::string> BreakingMap(const unsigned BreakingCoef, std::vector<std::string> map)
{
    std::vector<std::string>  breakMap(map.size() * BreakingCoef);

    for (auto i = 0U; i < map.size (); ++i)
    {
        for (auto ch : map[i])
            for (auto j = 0U; j < BreakingCoef; ++j)  breakMap[i * BreakingCoef].push_back(ch);
        for (auto j = 1U; j < BreakingCoef; ++j) breakMap[i * BreakingCoef + j] = std::string(breakMap[i * BreakingCoef]);
    }

    return breakMap;
}
}

#endif // LIGHT

