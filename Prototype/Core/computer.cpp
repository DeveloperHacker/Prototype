#include "Core/computer.h"

Computer::Computer(Hero& temp)
{
    position = temp.get_position();
    prev_position = position;
    character = temp.get_character();
    step = temp.get_step();
    review = temp.get_review();
    sign = temp.get_sign();
}

bool Computer::movement(Maze level_map)
{
    const auto Q_POSSIBILITIES = 4U;
    SegmentDistribution distributed_move[Q_POSSIBILITIES];
    Point shift;
    Point temp;
    bool result, approval1 = false, approval2 = false, approval3 = false;
    unsigned left_boundary = 0;
    unsigned root_decision, decision;


    if(move_to_hero(level_map) == true) return true;

    //относительно героя компьютера
    if (prev_position == position)
    {
        shift.x = 0;
        shift.y = -1;
    }
    else
    {
    shift.x = position.x - prev_position.x;
    shift.y = position.y - prev_position.y;
    }

    distributed_move[0].probability = 70; // Смещение вперёд
    distributed_move[0].shift = shift;

    distributed_move[1].probability = 2; // Смещение назад
    distributed_move[1].shift.x = -shift.x;
    distributed_move[1].shift.y = -shift.y;

    distributed_move[2].probability = 14; // Смещение влево
    distributed_move[2].shift.x = shift.y;
    distributed_move[2].shift.y = -shift.x;

    distributed_move[3].probability = 14; // Смещение вправо
    distributed_move[3].shift.x = -shift.y;
    distributed_move[3].shift.y = shift.x;

    for (auto i = 0U; i < Q_POSSIBILITIES; ++i)
    {
        temp.x = position.x + distributed_move[i].shift.x;
        temp.y = position.y + distributed_move[i].shift.y;
        if (level_map.isExistance(temp.y, temp.x))
        {
            approval1 = level_map.getCell(temp.y, temp.x) != '#';
            approval2 = level_map.getCell(temp.y, temp.x) != 'E';
            approval3 = level_map.getCell(temp.y, temp.x) != 'M';
        }
        result = approval1 && approval2 && approval3;
        distributed_move[i].use = result;
        if (result == true) left_boundary += distributed_move[i].probability;
    }

    if (left_boundary == 0) return true;
    root_decision = rand() % left_boundary;

    for (auto i = 0U; i < Q_POSSIBILITIES; ++i)
    {
        if (!distributed_move[i].use) continue;
        if (root_decision < distributed_move[i].probability)
        {
            decision = i;
            break;
        }
        else
            root_decision -= distributed_move[i].probability;
    }

    prev_position = position;
    position.x += distributed_move[decision].shift.x;
    position.y += distributed_move[decision].shift.y;

    return true;
}

bool Computer::move_to_hero(Maze& level_map)
{
    Point lu_cornor;
    Point rd_cornor;
    Point point;
    unsigned step = 1;
    Point hero_position = position;
    unsigned hero_review = review;
    bool end = false;

    unsigned ** screen;
    unsigned size_screen = (review * 2 + 1);
    screen = new unsigned*[size_screen];
    for (auto i = 0U; i < size_screen; ++i)
        screen[i] = new unsigned[size_screen];
    for (auto i = 0U; i < size_screen; ++i)
        for (auto j = 0U; j < size_screen; ++j)
            screen[i][j] = 0;


    screen[hero_review][hero_review] = 1;
    while (step <= hero_review)
    {
        lu_cornor.x = hero_position.x - (step-1);
        lu_cornor.y = hero_position.y - (step-1);
        rd_cornor.x = hero_position.x + (step-1);
        rd_cornor.y = hero_position.y + (step-1);

        for (int i = lu_cornor.y; i <= rd_cornor.y; i++)
            for (int j = lu_cornor.x; j <= rd_cornor.x; j++)
            {
                if (!level_map.isExistance(i, j)) continue;
                point.y = i - hero_position.y + hero_review;
                point.x = j - hero_position.x + hero_review;
                if (screen[point.y][point.x] == step && level_map.getCell(i, j) != '#')
                {
                    if (level_map.isExistance(i - 1, j) && (point.y - 1 >= 0))
                        if (screen[point.y - 1][point.x] == 0)
                            screen[point.y - 1][point.x] = step + 1;

                    if (level_map.isExistance(i + 1, j) && ((unsigned)point.y + 1 < size_screen))
                        if (screen[point.y + 1][point.x] == 0)
                            screen[point.y + 1][point.x] = step + 1;

                    if (level_map.isExistance(i, j - 1) && (point.x - 1 >= 0))
                        if (screen[point.y][point.x  - 1] == 0)
                            screen[point.y][point.x - 1] = step + 1;

                    if (level_map.isExistance(i, j + 1) && ((unsigned)point.x + 1 < size_screen))
                        if (screen[point.y][point.x + 1] == 0)
                            screen[point.y][point.x + 1] = step + 1;
                }
            }

        step++;
    }

    for (auto i = 0U; i < size_screen; ++i)
    {
        for (auto j = 0U; j < size_screen; ++j)
        {
            if (screen[i][j] != 0 && level_map.getCell(i + position.y - review, j + position.x - review) == 'H')
            {
                point.y = i;
                point.x = j;

                for (auto it = screen[i][j] - 1; it > 1; --it)
                {
                    if ((unsigned)point.x + 1 < size_screen)
                    if (screen[point.y][point.x + 1] == it
                            && level_map.getCell(point.y + position.y - review, point.x + 1 + position.x - review) != '#')
                    {
                        point.x = point.x + 1;
                        point.y = point.y;
                        continue;
                    }

                    if (point.x - 1 >= 0)
                    if (screen[point.y][point.x - 1] == it
                            && level_map.getCell(point.y + position.y - review, point.x - 1 + position.x - review) != '#')
                    {
                        point.x = point.x - 1;
                        point.y = point.y;
                        continue;
                    }

                    if ((unsigned)point.y + 1 < size_screen)
                    if (screen[point.y + 1][point.x] == it
                            && level_map.getCell(point.y + 1 + position.y - review, point.x + position.x - review) != '#')
                    {
                        point.x = point.x;
                        point.y = point.y + 1;
                        continue;
                    }

                    if (point.y - 1 >= 0)
                    if (screen[point.y - 1][point.x] == it
                            && level_map.getCell(point.y - 1 + position.y - review, point.x + position.x - review) != '#')
                    {
                        point.x = point.x;
                        point.y = point.y - 1;
                        continue;
                    }
                }

                end = true;
                break;
            }
        }
        if (end) break;
    }

    if (end)
    {
        prev_position = position;
        position.x = position.x + point.x - review;
        position.y = position.y + point.y - review;
    }

    delete [] screen;

    if (end) return true;
    else return false;
}
