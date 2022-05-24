#ifndef DBFS_H
#define DBFS_H
#include "Map.h"
#include "Point.h"
#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QWaitCondition>
#include <queue>
#include <unordered_map>
class DBFS : public QObject, public QRunnable {
    Q_OBJECT
private:
    // 一般直接采用移位加异或（XOR）得到哈希值
    class HashFunc {

    public:
        template <typename T, typename U>
        size_t operator()(const std::pair<T, U>& p) const
        {
            return std::hash<T>()(p.first) ^ std::hash<U>()(p.second);
        }
    };

    // 键值比较，哈希碰撞的比较定义，需要直到两个自定义对象是否相等
    class EqualKey {
    public:
        template <typename T, typename U>
        bool operator()(const std::pair<T, U>& p1, const std::pair<T, U>& p2) const
        {
            return p1.first == p2.first && p1.second == p2.second;
        }
    };

public:
    int x, y, sx, sy, ex, ey;
    Map* mp;

private:
    // 走向
    QStringList Dir = { "↓", "→", "↑", "←" };
    bool flag;
    QWaitCondition* cond;
    QMutex* mutex;
    // 记录路径
    std::unordered_map<std::pair<int, int>, Point, HashFunc, EqualKey> apre, bpre;
    int dir[4][2] = {
        { 0, 1 },
        { 1, 0 },
        { 0, -1 },
        { -1, 0 }
    };
    QVector<QString> dis;

public:
    explicit DBFS(QObject* parent = nullptr);
    void init(Map* map, int sx, int sy, int ex, int ey);
    void resume();

protected:
    void run();

signals:
    void SendDra(int x, int y, int step,QString Dir, QColor Color);
    void SendFlags();
};
#endif
