#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QPainter>

class Button : public QPushButton
{
private:
    bool mouseOver;
    QPixmap relax;
    QPixmap push;
    bool defaultTextures;

public:
    explicit Button(QWidget */*parent*/ = nullptr) : mouseOver(false), defaultTextures(true) {}
    ~Button() = default;

public:
    void setTexture(const QPixmap &relax, const QPixmap &push);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

};

#endif // BUTTON_H
