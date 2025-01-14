#include "Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->Step = 0;
    this->hCost = 0; // 默认初始化 hCost
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
    this->Step = 0;
    this->hCost = 0; // 默认初始化 hCost
}

Point::Point(int x, int y, int step)
{
    this->x = x;
    this->y = y;
    this->Step = step;
    this->hCost = 0; // 默认初始化 hCost
}

Point::Point(int x, int y, QString dir)
{
    this->x = x;
    this->y = y;
    this->Dir = dir;
    this->Step = 0;
    this->hCost = 0; // 默认初始化 hCost
}

Point::Point(int x, int y, QColor Color)
{
    this->x = x;
    this->y = y;
    this->Color = Color;
    this->Step = 0;
    this->hCost = 0; // 默认初始化 hCost
}

Point::Point(int x, int y, int step, QString dir)
{
    this->x = x;
    this->y = y;
    this->Step = step;
    this->Dir = dir;
    this->hCost = 0; // 默认初始化 hCost
}

Point::Point(int x, int y, int step, QString dir, QColor Color)
{
    this->x = x;
    this->y = y;
    this->Step = step;
    this->Dir = dir;
    this->Color = Color;
    this->hCost = 0; // 默认初始化 hCost
}

// 新增构造函数
Point::Point(int x, int y, int step, int hCost, QString dir, QColor Color)
{
    this->x = x;
    this->y = y;
    this->Step = step;
    this->hCost = hCost;
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
    return std::tie(x, y) < std::tie(p.x, p.y);
}
