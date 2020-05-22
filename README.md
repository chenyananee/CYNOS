# CYNOS
裸机前后台伪操作系统，占用少量资源，组件耦合低，可裁剪性强
#系统裁剪由cynos_cfg.h内完成
使用说明：
  #1.包含一个cynos.h文件，将函数void cynos_time_run(CynOS_U32 timebase)添加到定时器中断内（提供系统时基）
  #2.在Cynos_UserTask_Init()函数内建立用户任务
  #3.调用一次 
      CynOS_Init();
      Cynos_UserTask_Init();
      CynOsStart();
  #4.整个内核已正常运行     
   

  
  
  
   






