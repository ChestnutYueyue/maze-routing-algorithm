#include "BFS.h"
BFS::BFS(QObject* parent)
    : QObject(parent)
    , QRunnable()
    , cond(new QWaitCondition)
    , mutex(new QMutex)
{
}
void BFS::init(Map* map, int sx, int sy, int ex, int ey)
{
    this->mp = map;
    this->sx = sx;
    this->sy = sy;
    this->ex = ex;
    this->ey = ey;
}
void BFS::resume()
{
    cond->wakeAll();
}
void BFS::run()
{
    mutex->lock();
    Point pStart(sx, sy, QColor(255, 255, 0)), pEnd(ex, ey, QColor(255, 255, 0));
    std::queue<Point> s;
    s.push(pStart);
    mp->map[sx][sy] = 4;
    emit SendDra(pStart.x, pStart.y, pStart.Step, pStart.Dir, QColor(255, 255, 0));
    cond->wait(mutex);
    while (!s.empty()) {
        Point temp = s.front();
        emit SendDra(s.front().x, s.front().y, s.front().Step, "", s.front().Color);
        cond->wait(mutex);
        if (temp == pEnd) {
            emit SendDra(pEnd.x, pEnd.y, temp.Step, pEnd.Dir, QColor(255, 255, 0));
            cond->wait(mutex);
            while (pEnd != pStart) {
                mp->map[pEnd.x][pEnd.y] = 3;
                pEnd = pre[{ pEnd.x, pEnd.y }];
                pEnd.Color = QColor(255, 106, 106);
                if (pEnd.Dir == "↑") {
                    pEnd.Dir = "↓";
                } else if (pEnd.Dir == "↓") {
                    pEnd.Dir = "↑";
                } else if (pEnd.Dir == "←") {
                    pEnd.Dir = "→";
                } else if (pEnd.Dir == "→") {
                    pEnd.Dir = "←";
                }
                emit SendDra(pEnd.x, pEnd.y, s.front().Step, pEnd.Dir, pEnd.Color);
                cond->wait(mutex);
            }
            emit SendDra(pStart.x, pStart.y, temp.Step, "", QColor(255, 255, 0));
            cond->wait(mutex);
            break;
        }
        for (int k = 0; k < 4; k++) {
            temp.x = s.front().x + dir[k][0];
            temp.y = s.front().y + dir[k][1];
            temp.Step = s.front().Step + 1;
            temp.Dir = Dir[k];
            temp.Color = QColor(135, 206, 235);
            if (temp.x < 1 || temp.x > mp->N || temp.y < 1 || temp.y > mp->M || mp->map[temp.x][temp.y]) {
                continue;
            }
            s.push(temp);
            pre[{ temp.x, temp.y }] = s.front();
            mp->map[temp.x][temp.y] = 2;
        }
        s.pop();
    }
    emit SendFlags();
    mutex->unlock();
}