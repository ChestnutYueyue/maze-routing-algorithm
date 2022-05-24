#include "DFS.h"
DFS::DFS(QObject* parent)
    : QObject(parent)
    , QRunnable()
    , cond(new QWaitCondition)
    , mutex(new QMutex)
{
    flag = false;
}
void DFS::init(Map* map, int sx, int sy, int ex, int ey)
{
    this->mp = map;
    this->sx = sx;
    this->sy = sy;
    this->ex = ex;
    this->ey = ey;
}
void DFS::resume()
{
    cond->wakeAll();
}
void DFS::run()
{
    mutex->lock();
    Point pStart(sx, sy, QColor(255, 255, 0)), pEnd(ex, ey, QColor(255, 255, 0)), temp;
    s.push(pStart);
    mp->map[sx][sy] = 4;
    int tx, ty, k;
    emit SendDra(pStart.x, pStart.y, pStart.Step, pStart.Dir, pStart.Color);
    cond->wait(mutex);
    while (!s.empty()) {
        temp = s.top();
        emit SendDra(temp.x, temp.y, temp.Step, temp.Dir, temp.Color);
        cond->wait(mutex);
        if (temp == pEnd) {
            emit SendDra(temp.x, temp.y, temp.Step, temp.Dir = "", temp.Color = QColor(255, 255, 0));
            flag = true;
            emit SendFlags(flag);
            break;
        }
        for (k = 0; k < 4; k++) {
            tx = temp.x + dir[k][0];
            ty = temp.y + dir[k][1];
            if (tx < 1 || tx > mp->N || ty < 1 || ty > mp->M || mp->map[tx][ty]) {
                continue;
            }
            break;
        }
        if (k < 4) {
            temp.x = tx;
            temp.y = ty;
            temp.Step += 1;
            temp.Dir = Dir[k];
            temp.Color = QColor(135, 206, 235);
            s.push(temp);
            mp->map[tx][ty] = 2;
        } else {
            temp.Step -= 1;
            temp.Dir = "";
            temp.Color = QColor(255, 106, 106);
            s.pop();
            mp->map[temp.x][temp.y] = 3;
            emit SendDra(temp.x, temp.y, temp.Step, temp.Dir, temp.Color);
            cond->wait(mutex);
        }
    }
    emit SendFlags(flag);
    mutex->unlock();
}