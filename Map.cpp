#include "Map.h"
#include <QDebug>
Map::Map(QObject* parent)
    : QObject(parent)
{
    this->sx = 1;
    this->sy = 1;
    this->M = 56;
    this->N = 56;
    this->width = 560;
    this->height = 560;
    this->x_num = 1;
    this->y_num = 1;
    for (int i = 0; i < N + 1; i++) {
        map.push_back(QVector<int>(M + 1, 1));
    }
    create();
}
Map::Map(const Map& m)
{
    this->map = m.map;
    this->sx = m.sx;
    this->sy = m.sy;
    this->M = m.M;
    this->N = m.N;
    this->width = m.width;
    this->height = m.height;
}
Map& Map::operator=(const Map& m)
{
    this->map = m.map;
    this->sx = m.sx;
    this->sy = m.sy;
    this->M = m.M;
    this->N = m.N;
    this->width = m.width;
    this->height = m.height;
    return *this;
}
void Map::push(int x, int y, int direct)
{
    block_row.push_back(x);
    block_column.push_back(y);
    block_direct.push_back(direct);
}
int Map::count()
{
    int cnt = 0;
    if (x_num + 1 < M) {
        push(x_num + 1, y_num, Dir_down);
        cnt++;
    } // down
    if (y_num + 1 < N) {
        push(x_num, y_num + 1, Dir_right);
        cnt++;
    } // right
    if (x_num - 1 >= 1) {
        push(x_num - 1, y_num, Dir_up);
        cnt++;
    } // up
    if (y_num - 1 >= 1) {
        push(x_num, y_num - 1, Dir_left);
        cnt++;
    } // left
    return cnt;
}

void Map::create()
{
    count();
    map[sx][sy] = 0;
    while (block_row.size()) {
        int num = block_row.size();
        int randnum = rand() % num;
        x_num = block_row[randnum];
        y_num = block_column[randnum];
        switch (block_direct[randnum]) {
        case Dir_down: {
            x_num = block_row[randnum] + 1;
            y_num = block_column[randnum];
            break;
        }
        case Dir_right: {
            x_num = block_row[randnum];
            y_num = block_column[randnum] + 1;
            break;
        }
        case Dir_left: {
            x_num = block_row[randnum];
            y_num = block_column[randnum] - 1;
            break;
        }
        case Dir_up: {
            x_num = block_row[randnum] - 1;
            y_num = block_column[randnum];
            break;
        }
        }
        if (map[x_num][y_num] == 1) {
            map[block_row[randnum]][block_column[randnum]] = 0;
            map[x_num][y_num] = 0;
            count();
        }
        block_row.erase(block_row.begin() + randnum);
        block_column.erase(block_column.begin() + randnum);
        block_direct.erase(block_direct.begin() + randnum);
    }
}
void Map::drawMap(QPainter* painter)
{
    QBrush temp;
    for (int n = 0; n <= N; n++) {
        for (int m = 0; m <= M; m++) {
            if (map[m][n] == 1) {
                temp = QBrush(QColor(0, 10, 0));
            } else if (map[m][n] == 0) {
                temp = QBrush(QColor(255, 255, 255));
            } else if (map[m][n] == 2) {
                temp = QBrush(QColor(135, 206, 235));
            } else if (map[m][n] == 3) {
                temp = QBrush(QColor(255, 106, 106));
            } else if (map[m][n] == 4) {
                temp = QBrush(QColor(255, 255, 0));
            } else if (map[m][n] == 5) {
                temp = QBrush(QColor(127, 255, 212));
            }
            painter->fillRect(m * (width / M), n * (height / N), width / M, height / N, temp);
        }
    }
}
