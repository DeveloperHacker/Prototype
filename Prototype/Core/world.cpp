#include "Core/world.h"


World::World(const std::string& file_name, Character player) : chooser(hero.begin())
{
    auto search_gg = false;

    new_world(file_name);
//    new_world("ResourceFiles/Maps/level.map");

    for (auto& hero : this->hero)
    {
        if (hero->get_character() == player && !search_gg)
            hero = new Player(*hero);
        else
            hero = new Computer(*hero);
    }
}

World::~World()
{
    for (auto& hero : this->hero)
        delete hero;
}

Player *World::get_main_hero() const
{
    Player *player;
    for(auto hero : this->hero)
    {
        player = dynamic_cast<Player*>(hero);
        if (player != nullptr)
            return player;
    }
    return nullptr;
}

void World::new_world(const std::string& file_name)
{
    Point position;
    bool exit_existance = false;

    level.maze.clear();
    level.read_maze(file_name);

    for (auto i = 0U; i < level.maze.size(); ++i)
        for (auto j = 0U; j < (level.maze[i]).size(); ++j)
        {
            if(level.maze[i][j] == 'H')
            {
                position.x = j;
                position.y = i;
                Hero* temp = new Hero(position, Character::Human, STEP_HUMAN, REVIEW_HUMAN);
                hero.push_back(temp);
            }
            if(level.maze[i][j] == 'M')
            {
                position.x = j;
                position.y = i;
                Hero* temp = new Hero(position, Character::Minotavr, STEP_MINOTAVR, REVIEW_MINOTAVR);
                hero.push_back(temp);
            }
            if(level.maze[i][j] == 'E')
            {
                exit_existance = true;
            }
        }
    if (!exit_existance) throw Exception("new_world", "Invalid generated levels.");

    chooser = hero.begin();
}

bool World::player_move(Direction direction)
{
    Point position;

    if (direction == Direction::North)
        (*chooser)->step_to_north();
    else if (direction == Direction::East)
        (*chooser)->step_to_east();
    else if (direction == Direction::South)
        (*chooser)->step_to_south();
    else if (direction == Direction::West)
        (*chooser)->step_to_west();
    position = (*chooser)->get_position();

    if (!level.isExistance(position.y, position.x))
    {
        (*chooser)->step_back();
        return false;
    }
    if (level.maze[position.y][position.x] == '#')
    {
        (*chooser)->step_back();
        return false;
    }
    if (level.maze[position.y][position.x] == 'M')
    {
        emit Win(Character::Minotavr);
        return true;
    }

    return true;
}

void World::movement(Direction direction)
{
    Computer * comp;
    Point position;
    bool isMove = false;

    do
    {
        comp = dynamic_cast<Computer*>(*chooser);

        if (comp != nullptr)
        {
            comp->movement(get_level_map());
            isMove = true;
        }
        else
        {
            if (player_move(direction)) isMove = true;
        }

        position = (*chooser)->get_position();
        if ((*chooser)->get_character() == Character::Human)
        {
            if (level.maze[position.y][position.x] == 'E') emit Win(Character::Human);
        }
        else
        {
            if (level.maze[position.y][position.x] == 'H') emit Win(Character::Minotavr);
        }

        position = (*chooser)->get_prev_position();
        level.maze[position.y][position.x] = ' ';
        position = (*chooser)->get_position();
        level.maze[position.y][position.x] = (*chooser)->get_sign();

        if (isMove == true) { ++chooser; isMove = false; }
        if (chooser == hero.end()) chooser = hero.begin();
    } while (comp != nullptr);
}

Maze World::get_level_map() const
{
    return level;
}
