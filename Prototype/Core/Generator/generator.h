#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include <stack>
#include <QtCore>
#include <ctime>

#include "Core/point.h"

typedef std::vector<std::string> maze_t;
class Generator
{
private:
    static const auto UpperMazeSize = 100U;
    static const auto LowerMazeSize = 50U;
    static const auto UpperMazeSizeRoom = 3U;
    static const auto LowerMazeSizeRoom = 1U;
    static const auto Coef = 100;
    static const auto ConcentrationMinutaur = 10U; // = [Muinotaurs / Coef Cells]
    static const auto DepthGenLoops = 0U;

private:
    maze_t level;
    QSize size;
    std::string fileName;
    unsigned seed;

public:
    Generator(const std::string &);
    ~Generator() = default;

public:
    void GenMaze();
    std::string GetFileName() const;
    QSize GetSize() const;
    maze_t GetLevel() const;
    void Print(std::string *file = nullptr) const;

private:
    void GenSceleton();
    void GenWalls(Point, Point, unsigned);
    Point RandomIntersectionPoint(Point, Point) const;
    std::vector<Point> RandomPassPoints(Point, Point, Point, unsigned) const;
    void PutObjects();

public:
    static std::string IntegerToString(int64_t);
};

#endif // GENERATOR_H
