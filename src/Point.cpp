#include "Point.h"
Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->Step = 0;
}
Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
    this->Step = 0;
}
Point::Point(int x, int y, int step)
{
    this->x = x;
    this->y = y;
    this->Step = step;
}
Point::Point(int x, int y, QString dir)
{
    this->x = x;
    this->y = y;
    this->Dir = dir;
}
Point::Point(int x, int y, int step, QString dir)
{
    this->x = x;
    this->y = y;
    this->Step = step;
    this->Dir = dir;
}
Point::Point(int x, int y, QColor Color)
{
    this->x = x;
    this->y = y;
    this->Color = Color;
}
Point::Point(int x, int y, int step, QString dir, QColor Color)
{
    this->x = x;
    this->y = y;
    this->Step = step;
    this->Dir = dir;
    this->Color = Color;
}
bool Point::operator==(const Point& p) const
{
    return (x == p.x) && (y == p.y);
}
bool Point::operator!=(const Point& p) const
{
    return (x != p.x) || (y != p.y);
}
bool Point::operator<(const Point& p) const
{

    if (this->x < p.x)
        return true;
    if (this->x > p.x)
        return false;
    if (this->y < p.y)
        return true;
    return false;
}