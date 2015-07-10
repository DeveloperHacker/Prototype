#include "Application/screen.h"

Screen::Screen(const QSize &size, Character player, QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, size.width(), size.height());

    Generator generator("ResourceFiles/Maps/");

    generator.GenMaze();
    generator.Print();

    world = new World(generator.GetFileName(), player);

    auto map = world->get_level_map();
    std::vector<std::vector<bool>> temp(map.getSize());
    for (std::size_t i = 0; i < map.getSize(); ++i)
    {
        for (std::size_t j = 0; j < map.getStringSize(i); ++j)
            temp[i].push_back(false);
    }
    memory = temp;

    connect(world, SIGNAL(Win(Character)), this, SLOT(repeaterWin(Character)));
}

Screen::~Screen()
{
    delete world;
}

void Screen::paintEvent(QPaintEvent *)
{
    auto map = world->get_level_map();
    auto hero = world->get_main_hero();
    auto review = hero->get_review();
    auto position = hero->get_position();
    auto q_h_cell = 2 * review + 3;
    auto q_w_cell = coef_x * q_h_cell / coef_y;
    auto size = height() / q_h_cell;
    auto w = width();
    auto h = height();
    auto x = q_w_cell / 2;
    auto y = q_h_cell / 2;

    QPainter painter(this);
    QPixmap wallPix("ResourceFiles/Textures/SceletonWall.png");
    QPixmap humanPix("ResourceFiles/Textures/SceletonHuman.png");
    QPixmap minotaurPix("ResourceFiles/Textures/SceletonMinotaur.png");
    QPixmap doorPix("ResourceFiles/Textures/SceletonDoor.png");

    painter.fillRect(0, 0, w, h, QColor(255, 255, 255, 255));

    std::vector<std::string> SegmentMap(q_h_cell);
    for (auto i = 0U; i < q_h_cell; ++i)
        for (auto j = 0U; j <= q_w_cell; ++j)
        {
            auto I = i + position.y - y;
            auto J = j + position.x - x;

            if (map.isExistance (I, J))
                SegmentMap[i].push_back(map.getCell(I, J));
            else SegmentMap[i].push_back('#');
        }
    std::vector<std::string> BreakMap = Light::BreakingMap(SegmentMap);
    auto light = Light::getLight('H', review, SegmentMap);

    for (auto i = 0U; i < q_h_cell; ++i)
        for (auto j = 0U; j <= q_w_cell; ++j)
        {
            auto I = i + position.y - y;
            auto J = j + position.x - x;
            auto distance = (j - x) * (j - x) + (i - y) * (i - y);
            if (map.isExistance(I, J))
            {
                if (SegmentMap[i][j] == '#')
                    painter.drawPixmap(j * size, i * size, size, size, wallPix);
                if (light[i][j] == true)
                {
                    memory[I][J] = true;
                    if (SegmentMap[i][j] == 'H')
                        painter.drawPixmap(j * size, i * size, size, size, humanPix);
                    if (SegmentMap[i][j] == 'E')
                        painter.drawPixmap(j * size, i * size, size, size, doorPix);
                    if (SegmentMap[i][j] == 'M')
                        painter.drawPixmap(j * size, i * size, size, size, minotaurPix);

                    painter.fillRect(j * size, i * size, size, size, QColor(10, 10, 10, Screen::I(distance, pow(review, 2), 190)));
                }
                else
                {
                    if (memory[I][J])
                        painter.fillRect(j * size, i * size, size, size, QColor(10, 10, 10, 200));
                    else
                        painter.fillRect(j * size, i * size, size, size, QColor(50, 50, 50, 255));
                }
            }
            else
            {
                  painter.fillRect(j * size, i * size, size, size, QColor(50, 50, 50, 255));
            }
        }
}

unsigned Screen::I(unsigned r, unsigned R, unsigned Imax)
{
    const auto a = 1 / 2;
    return sqrt(Imax*Imax * r / R * (r + 2*a) / (R + 2*a));
}

void Screen::move_to_north()
{
    world->movement(Direction::North);
    update();
}

void Screen::move_to_south()
{
    world->movement(Direction::South);
    update();
}

void Screen::move_to_west()
{
    world->movement(Direction::West);
    update();
}

void Screen::move_to_east()
{
    world->movement(Direction::East);
    update();
}

void Screen::repeaterWin(Character winner)
{
    emit End(winner);
}

void Screen::repeaterError(Exception exception)
{
    emit Error(exception);
}
