#ifndef MAP_H
#define MAP_H

#include <QBrush>
#include <QObject>
#include <QPainter>
#include <QVector>
#include <iostream>
#include <random>


enum Dir {
    Dir_down = 1,
    Dir_right = 2,
    Dir_left = 4,
    Dir_up = 8
};

class Map : public QObject {
    Q_OBJECT
public:
    int sx, sy, M, N, width, height;
    QVector<QVector<int>> map;

private:
    int x_num;
    int y_num;
    std::random_device rand;
    QVector<int> block_row;
    QVector<int> block_column;
    QVector<int> block_direct;

public:
    Map(QObject* parent = nullptr);
	Map(const Map& m);
    Map& operator=(const Map& m);
    void push(int x, int y, int direct);
    int count();
    void create();
    void drawMap(QPainter* painter);
};
#endif
