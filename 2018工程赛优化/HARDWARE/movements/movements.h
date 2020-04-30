#include "xunji.h"
#include "timer.h"

void led(int a);
	
void yunsu(long a,long b);//速度 时间（循迹）
void ting(void);//立刻停止

void jiansu3(long a);//减速3—>a
void jiansu4(long a);//减速4—>a
void jiansu5(long a);//减速5—>a

void jiasu2(long a);//加速2—>a
void jiasu3(long a);//加速3—>a
void jiasu4(long a);//加速4—>a
void jiansusmall(long a);//微减速—>a
void jiasudao(u16 speed);//加速到speed
void jiansudao(u16 speed);//加速到speed
void zhijiaoyou(u16 zuo,u16 you,u16 time);//延时直角右转
void zhijiaozuo(u16 zuo,u16 you,u16 time);//延时直角右转
void duanting(u16 time);//短停
void zhuanxiang(u16 zuo,u16 you,u16 time);//转向
void daochexunxian(void);//倒车巡线
void cgzhijiaozuo(u16 zuo,u16 you);//传感器直角左转
void cgzhijiaoyou(u16 zuo, u16 you);//传感器直角右转
void cgchasu(u16 zuo,u16 you);//传感器差速
void zhangai0time(u16 time_set);//过时间扫地毯
void zhangai1time(u16 time_set);//过时间扫地毯
void zhongjianzuo0time(u16 time_set);//过时间扫中间左
void zhongjianyou0time(u16 time_set);//过时间扫中间右
void zhongjianzuo1time(u16 time_set);//过时间扫中间左灭
void rukou0time(u16 time_set);//过时间扫迷宫入口
void rukou1time(u16 time_set);//过非巡线区入口
void sebiaozuo0time(u16 time_set);//过时间扫色标左
void sebiaoyou0time(u16 time_set);//过时间扫色标右
void sebiaozuoyou0time(u16 time_set);//过时间扫色标左右
void chasusebiaoyou0(u16 zuo,u16 you);//直线直到色标右扫到正墙
void yuandiyouzhuanbizhangzuo1(u16 zuo,u16 you);//原地右转直到避障左灭
void yuandiyouzhuanbizhangyou0(u16 zuo,u16 you);//原地左转直到避障右亮
void chasubizhangyou0(u16 zuo,u16 you);//转弯直到避障右扫到侧墙
void chasubizhangyou1(u16 zuo,u16 you);//转弯直到避障右灭
void yuandizuozhuansebiaoyou1(u16 zuo,u16 you);//原地左转直到色标右灭
void yuandizuozhuanbizhangyou1(u16 zuo,u16 you);//原地左转直到避障右灭
void chasubizhangzuo0(u16 zuo,u16 you);//差速直到避障左扫到正墙
void chasurukou1(u16 zuo,u16 you);//差速直到入口灭
void chasusebiaozuo0(u16 zuo,u16 you);//差速直到色标左扫到正墙
void daochesebiaohou0(void);//巡线倒车过时间扫色标后
void daochesebiaohou1(void);//巡线倒车色标灭
void rukouzhixian(void);//用入口传感器走直线
void yuandiyouzhuanrukou0(u16 zuo,u16 you);//原地右转直到入口亮
void yuandizuozhuanrukou1(u16 zuo,u16 you);//原地左转直到入口亮
void chasurukou0(u16 zuo,u16 you);//差速直到入口扫到侧墙
void bizhangyouzhixian(void);//用避障右走直线
void bzylinesebiaoyou0(void);//避障右直线知道色标右0

