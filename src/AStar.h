#ifndef ASTAR_H
#define ASTAR_H

#include "Map.h"
#include "Point.h"
#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QStringList>
#include <QThread>
#include <QWaitCondition>
#include <queue>
#include <unordered_map>

class AStar : public QObject, public QRunnable {
    Q_OBJECT

private:
    // 嵌套比较器类
    class Compare {
    public:
        bool operator()(const Point& a, const Point& b) const {
            return a.Step + a.hCost > b.Step + b.hCost; // 优先队列按 f = g + h 排序
        }
    };

    class HashFunc {
    public:
        template <typename T, typename U>
        size_t operator()(const std::pair<T, U>& p) const {
            return std::hash<T>()(p.first) ^ std::hash<U>()(p.second);
        }
    };

    class EqualKey {
    public:
        template <typename T, typename U>
        bool operator()(const std::pair<T, U>& p1, const std::pair<T, U>& p2) const {
            return p1.first == p1.first && p1.second == p2.second;
        }
    };

public:
    int x, y, sx, sy, ex, ey;
    Map* mp;

private:
    QStringList Dir = { "↓", "→", "↑", "←" };
    QWaitCondition* cond;
    QMutex* mutex;
    std::unordered_map<std::pair<int, int>, Point, HashFunc, EqualKey> pre;
    int dir[4][2] = {
        { 0, 1 },
        { 1, 0 },
        { 0, -1 },
        { -1, 0 }
    };

public:
    explicit AStar(QObject* parent = nullptr);
    void init(Map* map, int sx, int sy, int ex, int ey);
    void resume();

protected:
    void run();

signals:
    void SendDra(int x, int y, int step, QString Dir, QColor Color);
    void SendFlags();
};

#endif // ASTAR_H
