#ifndef LIGHT
#define LIGHT

#include "Core/maze.h"
#include "Core/point.h"

namespace Light
{
std::vector<std::vector<bool>> getLight(Point pos, unsigned rev, Maze map)
{
    std::vector<std::vector<bool>> light(rev*2 + 1, std::vector<bool>(rev*2 + 1, false));
    Point A(rev, rev);
    static const auto MaxDistance = 0.4;
    std::vector<Point> containedPoint;
    containedPoint.reserve(pow(rev*2 + 1, 2) / 4);

    light[rev][rev] = true;
    for (auto I = 0U; I < rev*2 + 1; ++I)
        for (auto J = 0U; J < rev*2 + 1; ++J)
            if (map.isExistance(I - rev + pos.y, J - rev + pos.x) && light[I][J] == false
                    && (rev*rev >= (A.x - J)*(A.x - J) + (A.y - I)*(A.y - I)))
            {
                Point B(J, I);
                bool logikInterm = true;
                containedPoint.clear();
                for (auto i = 0U; i < rev*2 + 1; ++i)
                    for (auto j = 0U; j < rev*2 + 1; ++j)
                    {
                        Point C(j, i);
                        if (C != A && C != B)
                        if (MaxDistance * (pow((B.x - A.x), 2) + pow((B.y - A.y), 2))
                                >= pow(((C.x - A.x)*(B.y - A.y) - (C.y - A.y)*(B.x - A.x)) , 2)
                                && ((B.x - A.x)*(C.x - A.x) + (B.y - A.y)*(C.y - A.y)) >= 0
                                && ((B.x - A.x)*(B.x - C.x) + (B.y - A.y)*(B.y - C.y)) >= 0)
                        {
                            if  (map.isExistance(i - rev + pos.y, j - rev + pos.x)
                                 && map.getCell(pos.y - rev + i, pos.x - rev + j) == ' ')
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

    std::ofstream out("Light.log");
    for (auto str : light)
    {
        for (auto val : str)
            out << ((val == true) ? 'T' : 'f');
        out << std::endl;
    }
    out.close();

    return light;
}
}

#endif // LIGHT

