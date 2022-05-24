#ifndef DFS_H
#define DFS_H
#include "Map.h"
#include "Point.h"
#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QWaitCondition>
#include <stack>

class DFS : public QObject, public QRunnable {
    Q_OBJECT
public:
    int x, y, sx, sy, ex, ey;
    Map* mp;

private:
    // 走向
    QStringList Dir = { "↓", "→", "↑", "←" };
    bool flag;
    QWaitCondition* cond;
    std::stack<Point> s;
    QMutex* mutex;
    int dir[4][2] = {
        { 0, 1 },
        { 1, 0 },
        { 0, -1 },
        { -1, 0 }
    };

public:
    explicit DFS(QObject* parent = nullptr);
    void init(Map* map, int sx, int sy, int ex, int ey);
    void resume();

protected:
    void run();

signals:
    void SendDra(int x, int y, int step, QString Dir, QColor Color);
    void SendFlags(bool flag);
};
#endif
