# CynOS（轻量可裁剪伪操作系统）

___



## 特性
1. 占用少量资源，组件耦合低，可裁剪性强

2. 方便裸机模块化编程

3. 移植简单

## 系统裁剪

1. 配置cynos_cfg.h文件即可
## 移植方法
1. 包含cynos.h文件
2. 在定时器中断内调用void cynos_time_run(CynOS_U32 timebase)函数
3. 调用系统初始化函数CynOS_Init()
4. 在Cynos_UserTask_Init()函数内建立用户任务
5. 启动轮询调度
> sys_bsp_init(); //系统底层初始化函数等
> CynOS_Init();
> Cynos_UserTask_Init();
> CynOsStart();

___
