#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPainter>
#include <QGridLayout>

#include "Core/world.h"
#include "Core/Generator/generator.h"

namespace Light
{
std::vector<std::vector<bool>> getLight(char gg, unsigned rev, std::vector<std::string>& map);
std::vector<std::string> BreakingMap(std::vector<std::string> map);
}

class Screen : public QWidget
{
    Q_OBJECT
private:
    static const auto coef_x = 128;
    static const auto coef_y = 72;

private:
    World *world;
    std::vector<std::vector<bool>> memory;

public:
    Screen(const QSize &, Character, QWidget *parent = nullptr);
    ~Screen();

    void paintEvent(QPaintEvent *);
    static unsigned I(unsigned r, unsigned Rmax, unsigned Imax);

public slots:
    void move_to_north();
    void move_to_south();
    void move_to_west();
    void move_to_east();

    void repeaterWin(Character);
    void repeaterError(Exception);

signals:
    void Error(Exception);
    void End(Character);
};

#endif // SCREEN_H
