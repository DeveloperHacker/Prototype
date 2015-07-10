#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include <QDebug>
#include <iostream>
#include <functional>

#include "Core/maze.h"
#include "Core/computer.h"
#include "Core/player.h"
#include "Core/exception.h"
#include "Core/direction.h"

class World : public QObject
{
    Q_OBJECT
public:
    std::vector<Hero*> hero;

private:
    Maze level;
    std::vector<Hero*>::iterator chooser;
    static const int STEP_HUMAN = 1;
    static const int STEP_MINOTAVR = 1;
    static const int REVIEW_HUMAN = 6;
    static const int REVIEW_MINOTAVR = 7;

public:
    World(const std::string& file_name, Character);
    ~World();

public:
    Player *get_main_hero() const;
    Maze get_level_map() const;
    void movement(Direction direction);
    bool player_move(Direction);

public slots:
    void new_world(const std::string& file_name);

signals:
    void Win(Character);
};

#endif // WORLD_H
