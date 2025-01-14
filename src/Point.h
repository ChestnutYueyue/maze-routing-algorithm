#ifndef POINT_H
#define POINT_H
#include <QPainter>
#include <QString>

class Point {
public:
    int x = 0;         // x坐标
    int y = 0;         // y坐标
    int Step = 0;      // g值：实际路径代价
    int hCost = 0;     // h值：启发式代价（新增）
    QString Dir;       // 方向
    QColor Color;      // 颜色

public:
    Point();
    Point(int x, int y);
    Point(int x, int y, int step);
    Point(int x, int y, QString dir);
    Point(int x, int y, QColor Color);
    Point(int x, int y, int step, QString dir);
    Point(int x, int y, int step, QString dir, QColor Color);
    Point(int x, int y, int step, int hCost, QString dir, QColor Color); // 新增

    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    bool operator<(const Point& p) const;
};

#endif // POINT_H
