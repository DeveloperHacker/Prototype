#include "generator.h"

Generator::Generator(const std::string &path)
{
    seed = time(0);
    srand(seed);
    fileName = path + "Level" + IntegerToString(seed) + ".map";
    size.setWidth(rand() % (UpperMazeSize - LowerMazeSize) + LowerMazeSize);
    size.setHeight(rand() % (UpperMazeSize - LowerMazeSize) + LowerMazeSize);
}

void Generator::GenMaze()
{
    GenSceleton();

    GenWalls(Point(1, 1), Point(size.width() - 2, size.height() - 2), DepthGenLoops);
    level[0][0] = '#';

    PutObjects();
}

void Generator::PutObjects()
{
    Point pos;

    level[1][1] = 'H';
    level[size.height() - 2][size.width() - 2] = 'E';

    qDebug() << size;
    qDebug() << "QMinotaurs: " << (size.height() < size.width() ? size.height() : size.width()) * ConcentrationMinutaur / Coef;
    for (auto i = 0U; i < (size.height() < size.width() ? size.height() : size.width()) * ConcentrationMinutaur / Coef; ++i)
    {
        do {
            pos.x = rand() % size.width();
            pos.y = rand() % size.height();
        } while (level[pos.y][pos.x] != ' ');
        level[pos.y][pos.x] = 'M';
    }
}

Point Generator::RandomIntersectionPoint(Point lu, Point rd) const
{
    Point intersectionPoint;

    lu.x += LowerMazeSizeRoom - 1;
    lu.y += LowerMazeSizeRoom - 1;
    rd.x -= LowerMazeSizeRoom - 1;
    rd.y -= LowerMazeSizeRoom - 1;

    do
    {
        intersectionPoint.x = rand() % (rd.x - lu.x - 1) + 1 + lu.x;
        intersectionPoint.y = rand() % (rd.y - lu.y - 1) + 1 + lu.y;
    } while (intersectionPoint.x % 2 != 0 || intersectionPoint.y % 2 != 0);

    return intersectionPoint;
}

std::vector<Point> Generator::RandomPassPoints(Point lu, Point rd, Point c, unsigned qPass) const
{
    std::vector<Point> points;

    while (true) {
        points.push_back(Point(c.x, rand() % (c.y - lu.y) + lu.y));
        if (points.back().y % 2 == 1) break;
        else points.pop_back();
    }
    while (true) {
        points.push_back(Point(c.x, rand() % (rd.y - c.y) + c.y + 1));
        if (points.back().y % 2 == 1) break;
        else points.pop_back();
    }
    while (true) {
        points.push_back(Point(rand() % (c.x - lu.x) + lu.x, c.y));
        if (points.back().x % 2 == 1) break;
        else points.pop_back();
    }
    while (true) {
        points.push_back(Point(rand() % (rd.x - c.x) + c.x + 1, c.y));
        if (points.back().x % 2 == 1) break;
        else points.pop_back();
    }

    unsigned k;
    unsigned size = points.size();

    while (qPass < size)
    {
        k = rand() % points.size();
        if (points[k] != Point(0, 0))
        {
            points[k] = Point(0, 0);
            --size;
        }
    }

    return points;
}

std::string Generator::GetFileName() const
{
    return fileName;
}

maze_t Generator::GetLevel() const
{
    return level;
}

QSize Generator::GetSize() const
{
    return size;
}

void Generator::Print(std::string *file) const
{
    std::ofstream out;

    if (file == nullptr) out.open(fileName);
    else out.open(*file);

    for (const auto& string : level)
    {
        for (const auto& value : string) out << value;
        out << std::endl;
    }
}

void Generator::GenSceleton()
{
    std::string wall;
    std::string floor;

    for (auto i = 0; i < size.width(); ++i)
    {
        wall.push_back('#');
        floor.push_back(' ');
    }
    floor[0] = '#';
    floor[size.width() - 1] = '#';

    for (auto i = 0; i < size.height(); ++i)
        level.push_back(floor);
    level[0] = wall;
    level[size.height() - 1] = wall;
}

void Generator::GenWalls(Point lu, Point rd, unsigned depth)
{
//    qDebug() << "(" << lu.x << ";" << lu.y << ")";
//    qDebug() << "(" << rd.x << ";" << rd.y << ")";
//    qDebug() << "(" << ban.x << ";" << ban.y << ")" << '\n';

    if (rd.x - lu.x < (long int)UpperMazeSizeRoom) return;
    if (rd.y - lu.y < (long int)UpperMazeSizeRoom) return;
    auto qPass = depth > 0 ? 4 : 3;
    depth > 0 ? --depth : 0;
    auto c = RandomIntersectionPoint(lu, rd);
    auto p = RandomPassPoints(lu, rd, c, qPass);


    for (auto i = lu.y; i <= rd.y; ++i) level[i][c.x] = '#';
    for (auto j = lu.x; j <= rd.x; ++j) level[c.y][j] = '#';

    for (auto point : p) level[point.y][point.x] = ' ';

    GenWalls(Point(lu.x, lu.y), Point(c.x - 1, c.y - 1), depth);
    GenWalls(Point(c.x + 1, lu.y), Point(rd.x, c.y - 1), depth);
    GenWalls(Point(lu.x, c.y + 1), Point(c.x - 1, rd.y), depth);
    GenWalls(Point(c.x + 1, c.y + 1), Point(rd.x, rd.y), depth);
}

std::string Generator::IntegerToString(int64_t value)
{
    std::string string;
    std::string::reverse_iterator iter;
    std::string::reverse_iterator rend;
    auto temp = value;

    if (value < 0) string.push_back('-');
    while (temp != 0)
    {
        string.push_back(' ');
        temp /= 10;
    }

    rend = string.rend();
    if (value < 0) --rend;
    iter = string.rbegin();

    while (iter != rend)
    {
        *iter = (char)(value % 10 + '0');
        value /= 10;
        ++iter;
    }
    return string;
}
