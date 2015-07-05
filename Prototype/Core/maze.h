#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Core/exception.h"

class Maze
{
private:
    std::vector<std::string> maze;
    friend class World;
public:
    Maze() = default;
    ~Maze() = default;

    char getCell(int i, int j) const;
    std::size_t getSize() const;
    std::size_t getStringSize(std::size_t) const;
    bool isExistance(int i, int j) const;

    void read_maze(const std::string& file_name);
    void write_maze();
};

#endif
