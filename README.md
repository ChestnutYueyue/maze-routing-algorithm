<div align="center">
<h1 align="center">迷宫寻路算法</h1>
</div>

 ## 开发环境
 - 编程语言：C++11
 - 图像界面：Qt6.2.3
 - 测试运行IDE：vscode + GCC11.2 + CMake \
![演示](https://github.com/ChestnutYueyue/maze-routing-algorithm/blob/master/img/主界面.png?raw=true) \
 ![演示](https://github.com/ChestnutYueyue/maze-routing-algorithm/blob/master/img/DFS.png?raw=true) \
 ![演示](https://github.com/ChestnutYueyue/maze-routing-algorithm/blob/master/img/BFS.png?raw=true) \
 ![演示](https://github.com/ChestnutYueyue/maze-routing-algorithm/blob/master/img/DBFS.png?raw=true) 

 ## v1.4.0更新（优化）
 - [x] 优化了基础框架提高了适用性和简易性
 - [x] 再次优化了绘图方式解决了延迟导致运行效率低问题，进一步提升了绘图运行效率
 - [x] 更改了重置地图的方式，采用了拷贝对象抛弃了原有的循环重置地图数据，进一步提高了运行速度
 - [x] 更改了原先的进度显示方式，采用了进度条显示。更加直观

 ## v1.3.0更新(修复)
 - [x] 修复了双向BFS搜索导向错误的问题！
 
 ## v1.2.0更新(重要)
 - [x] 更改了绘图方法，效率得到极大的提升，采用了双缓冲绘图每次只绘制一个坐标点位
 - [x] 增加了路径路线的回溯导向。

 ## v1.1.0更新
 - [x] 更新BFS和DBFS路径记录方式采用了unordered_map

## v1.0.0更新
- [x] 双向BFS算法
- [x] 时间控制

## 实现功能
- [x] DFS算法
- [x] BFS算法
- [x] 地图生成
- [x] 重置地图

 ## 感谢
 双向BFS算法的关键中间状态确认由我的好友 *cribug_one* 指导完成\
 非常感谢各位帮助！！