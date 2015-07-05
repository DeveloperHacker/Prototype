#ifndef REVIEW
#define REVIEW

#include <queue>
#include <QDebug>

#include "Core/maze.h"
#include "Core/point.h"
#include "Core/direction.h"

class WaveFront
{
public:
    unsigned energy;
    Direction direct;

    WaveFront()
    {
        energy = 0;
        direct = Direction::North;
    }
    WaveFront(const WaveFront& front)
    {
        if (this != &front)
        {
            energy = front.energy;
            direct = front.direct;
        }
    }
    WaveFront(unsigned energy, Direction direct = Direction::North)
    {
        this->energy = energy;
        this->direct = direct;
    }

    WaveFront& operator =(const WaveFront& front)
    {
        this->direct = front.direct;
        this->energy = front.energy;
        return *this;
    }
    bool operator ==(const WaveFront& front)
    {
        return front.energy == energy;
    }
    bool operator !=(const WaveFront& front)
    {
        return front.energy != energy;
    }
    WaveFront operator -(unsigned val)
    {
        return WaveFront(energy - val, this->direct);
    }
};

namespace Review
{
static Direction getDirect(int dx, int dy)
{
    if (dx > 0) return Direction::West;
    if (dx < 0) return Direction::East;
    if (dy > 0) return Direction::South;
    if (dy < 0) return Direction::North;
    throw Exception("Review", "Fatal error.");
}

static std::vector<std::vector<WaveFront>> getLight(Point pos, Maze& map, unsigned rev)
{
    std::queue<Point*> que;
    std::vector<std::vector<WaveFront>> light(rev*2 + 1, std::vector<WaveFront>(rev*2 + 1));

    light[rev][rev] = WaveFront(rev);
    for (auto i = -1; i <= 1; i++)
        for (auto j = -1; j <= 1; j++)
            if (i*i != j*j)
            {
                if (map.getCell(pos.y + i, pos.x + j) == ' ')
                {
                    light[rev + i][rev + j] = WaveFront(rev - 1, Review::getDirect(j, i));
                    que.push(new Point(rev + j, rev + i));
                }
                else light[rev + i][rev + j] = WaveFront(1, Review::getDirect(j, i));
            }

    while (!que.empty())
    {
        Point p = *que.front();

        if (light[p.y][p.x].energy > 0)
        {
            for (auto i = -1; i <= 1; i++)
                for (auto j = -1; j <= 1; j++)
                    if (i*i != j*j && light[p.y + i][p.x + j] == WaveFront(0))
                    {
                        if (map.getCell(pos.y - rev + p.y + i, pos.x - rev + p.x + j) == ' ')
                        {
                            light[p.y + i][p.x + j] = WaveFront(light[p.y][p.x] - 1);
                            que.push(new Point(p.x + j, p.y + i));
                        }
                        else light[p.y + i][p.x + j] = WaveFront(1, light[p.y][p.x].direct);
                    }
        }

        delete que.front();
        que.pop();
    }

    return light;
}
}

#endif // REVIEW

