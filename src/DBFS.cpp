#include "DBFS.h"
DBFS::DBFS(QObject* parent)
    : QObject(parent)
    , QRunnable()
    , cond(new QWaitCondition)
    , mutex(new QMutex)
{

    flag = false;
}
void DBFS::init(Map* map, int sx, int sy, int ex, int ey)
{
    this->mp = map;
    this->sx = sx;
    this->sy = sy;
    this->ex = ex;
    this->ey = ey;
}
void DBFS::resume()
{
    cond->wakeAll();
}
void DBFS::run()
{
    mutex->lock();
    Point pStart(sx, sy, QColor(255, 255, 0)), pEnd(ex, ey, QColor(255, 255, 0)), tempStart, tempEnd;
    std::queue<Point> Start, End;
    Start.push(pStart);
    End.push(pEnd);
    mp->map[sx][sy] = 4;
    mp->map[ex][ey] = 4;
    bool flags = false;
    int x = 0, y = 0, tx = 0, ty = 0, Astep = 0, Bstep = 0;
    QColor Color;
    emit SendDra(pStart.x, pStart.y, pStart.Step, pStart.Dir, pStart.Color);
    cond->wait(mutex);
    while (!Start.empty() && !End.empty()) {

        // 尽可能扩展队列小的
        if (Start.size() <= End.size()) {
            x = Start.front().x, y = Start.front().y, Astep = Start.front().Step, Color = Start.front().Color;
            Start.pop();
            flags = true;
        } else {
            x = End.front().x, y = End.front().y, Bstep = End.front().Step, Color = End.front().Color;
            End.pop();
            flags = false;
        }
        emit SendDra(x, y, Astep + Bstep + 1, "", Color);
        cond->wait(mutex);
        for (int k = 0; k < 4; k++) {
            tx = x + dir[k][0];
            ty = y + dir[k][1];
            if (tx >= 1 && tx <= mp->N && ty >= 1 && ty <= mp->M && mp->map[tx][ty] != 1) {
                if (!mp->map[tx][ty]) {
                    if (flags) {
                        mp->map[tx][ty] = 2;
                        Start.push(Point(tx, ty, Astep + 1, Dir[k], QColor(135, 206, 235)));
                        apre[{ tx, ty }] = Point(x, y, Dir[k]);

                    } else {
                        mp->map[tx][ty] = 3;
                        End.push(Point(tx, ty, Bstep + 1, Dir[k], QColor(255, 106, 106)));
                        bpre[{ tx, ty }] = Point(x, y, Dir[k]);
                    }
                } else if (mp->map[tx][ty] + mp->map[x][y] == 5) {
                    if (mp->map[tx][ty] == 2) {
                        tempStart = Point(tx, ty, Dir[k]);
                        tempEnd = Point(x, y, Dir[k]);
                        if (tempStart.Dir == "↑") {
                            tempStart.Dir = "↓";
                        } else if (tempStart.Dir == "↓") {
                            tempStart.Dir = "↑";
                        } else if (tempStart.Dir == "←") {
                            tempStart.Dir = "→";
                        } else if (tempStart.Dir == "→") {
                            tempStart.Dir = "←";
                        }

                    } else if (mp->map[tx][ty] == 3) {
                        tempStart = Point(x, y, Dir[k]);
                        tempEnd = Point(tx, ty, Dir[k]);
                        if (tempEnd.Dir == "↑") {
                            tempEnd.Dir = "↓";
                        } else if (tempEnd.Dir == "↓") {
                            tempEnd.Dir = "↑";
                        } else if (tempEnd.Dir == "←") {
                            tempEnd.Dir = "→";
                        } else if (tempEnd.Dir == "→") {
                            tempEnd.Dir = "←";
                        }
                    }
                    QVector<Point> vis;
                    while (tempStart != pStart) {
                        vis.push_back(tempStart);
                        tempStart = apre[{ tempStart.x, tempStart.y }];
                    }
                    std::reverse(vis.begin(), vis.end());
                    while (tempEnd != pEnd) {
                        if (tempEnd.Dir == "↑") {
                            tempEnd.Dir = "↓";
                        } else if (tempEnd.Dir == "↓") {
                            tempEnd.Dir = "↑";
                        } else if (tempEnd.Dir == "←") {
                            tempEnd.Dir = "→";
                        } else if (tempEnd.Dir == "→") {
                            tempEnd.Dir = "←";
                        }
                        vis.push_back(tempEnd);
                        tempEnd = bpre[{ tempEnd.x, tempEnd.y }];
                    }
                    int tmpStep = 0;
                    for (auto& v : vis) {
                        mp->map[v.x][v.y] = 5;
                        tmpStep++;
                        emit SendDra(v.x, v.y, tmpStep + 1, v.Dir, QColor(127, 255, 212));
                        cond->wait(mutex);
                    }
                    emit SendDra(pEnd.x, pEnd.y, tmpStep + 1, pEnd.Dir = "", QColor(255, 255, 0));
                    cond->wait(mutex);
                    flag = true;
                    break;
                }
            }
        }
        if (flag) {
            break;
        }
    }
    emit SendFlags();
    mutex->unlock();
}
