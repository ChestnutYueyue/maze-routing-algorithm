#include "AStar.h"
#include <cmath>
#include <queue>

AStar::AStar(QObject* parent)
    : QObject(parent)
    , QRunnable()
    , cond(new QWaitCondition)
    , mutex(new QMutex)
{
}

void AStar::init(Map* map, int sx, int sy, int ex, int ey) {
    this->mp = map;
    this->sx = sx;
    this->sy = sy;
    this->ex = ex;
    this->ey = ey;
}

void AStar::resume() {
    cond->wakeAll();
}

void AStar::run() {
    mutex->lock();

    Point pStart(sx, sy, QColor(255, 255, 0)), pEnd(ex, ey, QColor(255, 255, 0));
    pStart.Step = 0;
    pStart.hCost = std::abs(ex - sx) + std::abs(ey - sy); // 曼哈顿距离

    // 使用嵌套的 Compare 类
    std::priority_queue<Point, std::vector<Point>, Compare> pq;
    pq.push(pStart);
    mp->map[sx][sy] = 4;

    emit SendDra(pStart.x, pStart.y, pStart.Step, pStart.Dir, QColor(255, 255, 0));
    cond->wait(mutex);

    while (!pq.empty()) {
        Point current = pq.top();
        pq.pop();

        emit SendDra(current.x, current.y, current.Step, "", current.Color);
        cond->wait(mutex);

        if (current == pEnd) {
            emit SendDra(pEnd.x, pEnd.y, current.Step, pEnd.Dir, QColor(255, 255, 0));
            cond->wait(mutex);

            while (pEnd != pStart) {
                mp->map[pEnd.x][pEnd.y] = 3;
                pEnd = pre[{pEnd.x, pEnd.y}];
                pEnd.Color = QColor(255, 106, 106);
                emit SendDra(pEnd.x, pEnd.y, pEnd.Step, pEnd.Dir, pEnd.Color);
                cond->wait(mutex);
            }

            emit SendDra(pStart.x, pStart.y, current.Step, "", QColor(255, 255, 0));
            cond->wait(mutex);
            break;
        }

        for (int k = 0; k < 4; k++) {
            int nx = current.x + dir[k][0];
            int ny = current.y + dir[k][1];

            if (nx < 1 || nx > mp->N || ny < 1 || ny > mp->M || mp->map[nx][ny]) {
                continue;
            }

            Point neighbor(nx, ny);
            neighbor.Step = current.Step + 1;
            neighbor.hCost = std::abs(ex - nx) + std::abs(ey - ny);
            neighbor.Dir = Dir[k];
            neighbor.Color = QColor(135, 206, 235);

            pq.push(neighbor);
            pre[{nx, ny}] = current;
            mp->map[nx][ny] = 2;
        }
    }

    emit SendFlags();
    mutex->unlock();
}
