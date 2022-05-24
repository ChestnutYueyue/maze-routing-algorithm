#ifndef POINT_H
#define POINT_H
#include <QPainter>
#include <QString>
class Point {
public:
    // x坐标
    int x = 0;
    // y坐标
    int y = 0;
    // 步数
    int Step = 0;
    // 方向
    QString Dir;
    // 颜色
    QColor Color;

public:
    Point();
    Point(int x, int y);
    Point(int x, int y, int step);
    Point(int x, int y, QString dir);
    Point(int x, int y, QColor Color);
    Point(int x, int y, int step, QString dir);
    Point(int x, int y, int step, QString dir, QColor Color);
    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    bool operator<(const Point& p) const;
};
#endif
