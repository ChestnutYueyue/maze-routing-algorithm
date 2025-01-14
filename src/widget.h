#ifndef WIDGET_H
#define WIDGET_H
#include "BFS.h"
#include "DBFS.h"
#include "DFS.h"
#include "AStar.h"
#include "Map.h"
#include "Point.h"
#include <QList>
#include <QPainter>
#include <QThreadPool>
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    // 界面初始化
    void InterfaceInitialization();
    // 对象初始化
    void ObjectInitialization();
    // 线程任务链接
    void ThreadedTasks();
    // 初始化地图
    void MapInitialize();
    // 地图复位
    void MapReset();
    // 游戏信息显示
    void GameInfo();
    // 地图显示
    void mapDraw(int x, int y, int step, QString dir, QColor Color);
    // 游戏信息更新
    void GameInfoUpdate(int x, int y, int step);
    // 线程信号连接
    void ThreadSignalConnections();
    // 时间信号连接
    void TimeSignalConnections();
    // 按钮连接设置
    void buttonSettings();
    // 进度条开始状态
    void progressBarStart();
    // 进度条结束状态
    void progressBarEnd();
    ~Widget();

protected:
    // 事件过滤
    bool eventFilter(QObject* watcher, QEvent* event) override;

private:
    Ui::Widget* ui;

public:
    // 算法对象
    BFS* bfs;
    DFS* dfs;
    DBFS* dbfs;
    AStar* astar;
    // 计时器
    QTimer* tim;
    // 线程池
    QThreadPool* pool;
    // 地图
    QList<Map*> drawMapList;
    // 辅助地图
    Map temp;
    // 时间
    clock_t start = 0;
    // 创建一个画布
    QPixmap* pix;
};
#endif // WIDGET_H
