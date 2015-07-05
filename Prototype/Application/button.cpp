#include "Application/button.h"

void Button::paintEvent(QPaintEvent *)
{
    const auto w = width();
    const auto h = height();
    QPainter painter(this);

    if (defaultTextures)
    {
        if (mouseOver)
        {
            painter.fillRect(0, 0, w, h, Qt::GlobalColor::black);
            painter.fillRect( w / 3, h / 3, w / 3, h / 3, Qt::GlobalColor::gray);
        }
        else
        {
            painter.fillRect(0, 0, w, h, Qt::GlobalColor::gray);
            painter.fillRect( w / 3, h / 3, w / 3, h / 3, Qt::GlobalColor::white);
        }
    }
    else
    {
        if (mouseOver)
        {
            painter.drawPixmap(0, 0, width(), height(), push);
        }
        else
        {
            painter.drawPixmap(0, 3, width(), height(), relax);
        }
    }
}

void Button::enterEvent(QEvent *)
{
    mouseOver = true;
}

void Button::leaveEvent(QEvent *)
{
    mouseOver = false;
}

void Button::setTexture(const QPixmap &relax, const QPixmap &push)
{
    defaultTextures = false;
    this->relax = relax;
    this->push = push;
}

