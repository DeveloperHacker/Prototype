#include "Core/maze.h"

void Maze::read_maze(const std::string& file_name)
{
    std::ifstream input(file_name);
    std::string null_string;

    if (!input.is_open()) throw Exception("reading", "File not found.");

    while (!input.eof())
    {
        maze.push_back(null_string);
        std::getline(input, maze[maze.size() - 1]);
    }

    if (maze[maze.size() - 1] == null_string) maze.pop_back();

    input.close();
}


void Maze::write_maze()
{
    for (auto it = begin(maze); it != end(maze); ++it)
    {
        std::cout << *it;
        std::cout << std::endl;
    }
}

bool Maze::isExistance(int i, int j) const
{
    if (i < 0) return false;
    if (j < 0) return false;
    if ((size_t)i >= maze.size()) return false;
    if ((size_t)j >= maze[i].size()) return false;
    return true;
}

char Maze::getCell(int i, int j) const
{
    return maze[i][j];
}

std::size_t Maze::getSize() const
{
    return maze.size();
}

std::size_t Maze::getStringSize(std::size_t num) const
{
    return maze[num].size();
}
