#include "./ui_widget.h"
#include "widget.h"

Widget::Widget(QWidget *parent)
{
    // 界面初始化
    this->InterfaceInitialization();
    // 对象初始化
    this->ObjectInitialization();
    // 线程任务链接
    this->ThreadedTasks();
    // 初始化地图
    this->MapInitialize();
    // 游戏信息显示
    this->GameInfo();
    // BFS线程信号连接
    this->ThreadSignalConnections();
    // 时间信号连接
    this->TimeSignalConnections();
    // 按钮连接设置
    this->buttonSettings();
}
void Widget::InterfaceInitialization()
{
    // 界面初始化
    ui = new Ui::Widget;
    ui->setupUi(this);
    // 事件过滤器安装
    this->installEventFilter(this);
    ui->GameWidget->installEventFilter(this);
    ui->GameInfo->installEventFilter(this);
    // 焦点设置
    ui->GameInfo->setFocus();
    ui->GameInfo->setFocusPolicy(Qt::NoFocus);
}
void Widget::ObjectInitialization()
{
    // 创建线程池
    pool = new QThreadPool;
    // 创建一个画布
    pix = new QPixmap(ui->GameWidget->size());
    // 时间控制
    tim = new QTimer(this);
}

void Widget::ThreadedTasks()
{
    // 初始化任务对象
    bfs = new BFS;
    dfs = new DFS;
    dbfs = new DBFS;
    astar = new AStar;
}
void Widget::MapInitialize()
{
    if (!drawMapList.isEmpty())
    {
        drawMapList.removeLast();
    }
    Map *mp = new Map;
    drawMapList.prepend(mp);
    QPainter p(pix);
    drawMapList[0]->drawMap(&p);
    temp = *mp;
}
void Widget::MapReset()
{
    Map *mp = new Map(temp);
    QPainter p(pix);
    drawMapList.prepend(mp);
    drawMapList.removeLast();
    drawMapList[0]->drawMap(&p);
}
void Widget::GameInfo()
{
    ui->x->setText("0");
    ui->y->setText("0");
    ui->gameTime->setText("0");
    ui->gameStep->setText("0");
    ui->gameStatus->reset();
}
// 地图显示
void Widget::mapDraw(int x, int y, int step, QString dir, QColor Color)
{
    QPainter p(pix);
    p.setFont(QFont("宋体", 9));
    p.fillRect(QRectF(x * 10, y * 10, 10, 10), QBrush(Color));
    p.drawText(QRectF(x * 10, y * 10, 10, 10), Qt::AlignHCenter | Qt::AlignVCenter, dir);
}
// 游戏信息更新
void Widget::GameInfoUpdate(int x, int y, int step)
{
    ui->gameTime->setText(QString::number((double)(clock() - start) / CLOCKS_PER_SEC));
    ui->gameStep->setText(QString::number(step));
    ui->x->setText(QString::number(x));
    ui->y->setText(QString::number(y));
}
// 线程信号连接
void Widget::ThreadSignalConnections()
{
    connect(dbfs, &DBFS::SendDra, this, [=](int x, int y, int step, QString Dir, QColor Color)
            {
        this->mapDraw(x, y, step, Dir, Color);
        this->GameInfoUpdate(x, y, step); });
    connect(dbfs, &DBFS::SendFlags, this, [=]()
            { this->progressBarEnd(); });
    connect(bfs, &BFS::SendDra, this, [=](int x, int y, int step, QString Dir, QColor Color)
            {
        this->mapDraw(x, y, step, Dir, Color);
        this->GameInfoUpdate(x, y, step); });
    connect(bfs, &BFS::SendFlags, this, [=]()
            { this->progressBarEnd(); });
    connect(dfs, &DFS::SendDra, this, [=](int x, int y, int step, QString Dir, QColor Color)
            {
        this->mapDraw(x, y, step, Dir, Color);
        this->GameInfoUpdate(x, y, step); });
    connect(dfs, &DFS::SendFlags, this, [=]()
            { this->progressBarEnd(); });
    connect(astar, &AStar::SendDra, this, [=](int x, int y, int step, QString Dir, QColor Color)
            {
        this->mapDraw(x, y, step, Dir, Color);
        this->GameInfoUpdate(x, y, step); });
    connect(astar, &AStar::SendFlags, this, [=]()
            { this->progressBarEnd(); });
}
// 时间信号连接
void Widget::TimeSignalConnections()
{
    connect(tim, &QTimer::timeout, this, [=]()
            {
        bfs->resume();
        dfs->resume();
        dbfs->resume();
        astar->resume();
        update(); });
}
// 按钮连接设置
void Widget::buttonSettings()
{
    connect(ui->GenerateMap, &QPushButton::clicked, this, [=]()
            {
        // 释放被保留的线程
        pool->releaseThread();
        // 清除所有当前排队但未开始运行的任务
        pool->clear();
        // 重新创建线程任务
        this->ThreadedTasks();
        // 重新连接线程信号
        this->ThreadSignalConnections();
        // 新建一个地图对象
        this->MapInitialize();
        // 复位信息显示
        this->GameInfo();
        // 更新
        update(); });
    // 信号连接
    connect(ui->rebuild, &QPushButton::clicked, this, [=]()
            {
        // 释放被保留的线程
        pool->releaseThread();
        // 清除所有当前排队但未开始运行的任务
        pool->clear();
        // 重新创建线程任务
        this->ThreadedTasks();
        // 重新连接线程信号
        this->ThreadSignalConnections();
        // 复位信息显示
        this->GameInfo();
        // 复位地图
        this->MapReset();
        // 更新
        update(); });
    connect(ui->Dbfs, &QPushButton::clicked, this, [=]()
            {
        dbfs->init(drawMapList[0], drawMapList[0]->sx, drawMapList[0]->sy, drawMapList[0]->M - 1, drawMapList[0]->N - 1);
        pool->start(dbfs);
        dbfs->setAutoDelete(false);
        tim->start();
        start = clock();
        this->progressBarStart(); });
    connect(ui->Bfs, &QPushButton::clicked, this, [=]()
            {
        bfs->init(drawMapList[0], drawMapList[0]->sx, drawMapList[0]->sy, drawMapList[0]->M - 1, drawMapList[0]->N - 1);
        pool->start(bfs);
        bfs->setAutoDelete(false);
        tim->start();
        start = clock();
        this->progressBarStart(); });
    connect(ui->Dfs, &QPushButton::clicked, this, [=]()
            {
        dfs->init(drawMapList[0], drawMapList[0]->sx, drawMapList[0]->sy, drawMapList[0]->M - 1, drawMapList[0]->N - 1);
        pool->start(dfs);
        dfs->setAutoDelete(false);
        tim->start();
        start = clock();
        this->progressBarStart(); });
    connect(ui->AStar, &QPushButton::clicked, this, [=]()
            {
        astar->init(drawMapList[0], drawMapList[0]->sx, drawMapList[0]->sy, drawMapList[0]->M - 1, drawMapList[0]->N - 1);
        pool->start(astar);
        astar->setAutoDelete(false);
        tim->start();
        start = clock();
        this->progressBarStart(); });
    // 输入框连接滑动条
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->horizontalSlider, &QSlider::setValue);
    // 控制时间设置
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int val)
            { tim->setInterval(val); });
    // 滑动条连接输入框
    connect(ui->horizontalSlider, QOverload<int>::of(&QSlider::valueChanged), ui->spinBox, &QSpinBox::setValue);
    // 控制时间设置
    connect(ui->horizontalSlider, QOverload<int>::of(&QSlider::valueChanged), this, [=](int val)
            { tim->setInterval(val); });
}
// 进度条开始状态
void Widget::progressBarStart()
{
    ui->gameStatus->setMinimum(0);
    ui->gameStatus->setMaximum(0);
    ui->gameStatus->setValue(0);
}
// 进度条结束状态
void Widget::progressBarEnd()
{

    ui->gameStatus->setMinimum(0);
    ui->gameStatus->setMaximum(100);
    ui->gameStatus->setValue(100);
}
// 事件过滤
bool Widget::eventFilter(QObject *watcher, QEvent *event)
{

    // 主窗口绘图事件处理
    if (watcher == this && event->type() == QEvent::Paint)
    {
        QPainter *Painter = new QPainter(this);
        Painter->fillRect(0, 0, this->width(), this->height(), QBrush(QColor(255, 255, 255)));
    }
    // 子窗口绘图事件处理
    if (watcher == ui->GameWidget && event->type() == QEvent::Paint)
    {
        // 双缓存绘制
        QPainter *Painter = new QPainter(ui->GameWidget);
        Painter->drawPixmap(0, 0, *pix);
    }
    return QWidget::eventFilter(watcher, event);
}

Widget::~Widget()
{
    delete ui;
}
