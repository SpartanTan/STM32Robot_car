#include "xunji.h"
#include "timer.h"

void led(int a);
	
void yunsu(long a,long b);//�ٶ� ʱ�䣨ѭ����
void ting(void);//����ֹͣ

void jiansu3(long a);//����3��>a
void jiansu4(long a);//����4��>a
void jiansu5(long a);//����5��>a

void jiasu2(long a);//����2��>a
void jiasu3(long a);//����3��>a
void jiasu4(long a);//����4��>a
void jiansusmall(long a);//΢���١�>a
void jiasudao(u16 speed);//���ٵ�speed
void jiansudao(u16 speed);//���ٵ�speed
void zhijiaoyou(u16 zuo,u16 you,u16 time);//��ʱֱ����ת
void zhijiaozuo(u16 zuo,u16 you,u16 time);//��ʱֱ����ת
void duanting(u16 time);//��ͣ
void zhuanxiang(u16 zuo,u16 you,u16 time);//ת��
void daochexunxian(void);//����Ѳ��
void cgzhijiaozuo(u16 zuo,u16 you);//������ֱ����ת
void cgzhijiaoyou(u16 zuo, u16 you);//������ֱ����ת
void cgchasu(u16 zuo,u16 you);//����������
void zhangai0time(u16 time_set);//��ʱ��ɨ��̺
void zhangai1time(u16 time_set);//��ʱ��ɨ��̺
void zhongjianzuo0time(u16 time_set);//��ʱ��ɨ�м���
void zhongjianyou0time(u16 time_set);//��ʱ��ɨ�м���
void zhongjianzuo1time(u16 time_set);//��ʱ��ɨ�м�����
void rukou0time(u16 time_set);//��ʱ��ɨ�Թ����
void rukou1time(u16 time_set);//����Ѳ�������
void sebiaozuo0time(u16 time_set);//��ʱ��ɨɫ����
void sebiaoyou0time(u16 time_set);//��ʱ��ɨɫ����
void sebiaozuoyou0time(u16 time_set);//��ʱ��ɨɫ������
void chasusebiaoyou0(u16 zuo,u16 you);//ֱ��ֱ��ɫ����ɨ����ǽ
void yuandiyouzhuanbizhangzuo1(u16 zuo,u16 you);//ԭ����תֱ����������
void yuandiyouzhuanbizhangyou0(u16 zuo,u16 you);//ԭ����תֱ����������
void chasubizhangyou0(u16 zuo,u16 you);//ת��ֱ��������ɨ����ǽ
void chasubizhangyou1(u16 zuo,u16 you);//ת��ֱ����������
void yuandizuozhuansebiaoyou1(u16 zuo,u16 you);//ԭ����תֱ��ɫ������
void yuandizuozhuanbizhangyou1(u16 zuo,u16 you);//ԭ����תֱ����������
void chasubizhangzuo0(u16 zuo,u16 you);//����ֱ��������ɨ����ǽ
void chasurukou1(u16 zuo,u16 you);//����ֱ�������
void chasusebiaozuo0(u16 zuo,u16 you);//����ֱ��ɫ����ɨ����ǽ
void daochesebiaohou0(void);//Ѳ�ߵ�����ʱ��ɨɫ���
void daochesebiaohou1(void);//Ѳ�ߵ���ɫ����
void rukouzhixian(void);//����ڴ�������ֱ��
void yuandiyouzhuanrukou0(u16 zuo,u16 you);//ԭ����תֱ�������
void yuandizuozhuanrukou1(u16 zuo,u16 you);//ԭ����תֱ�������
void chasurukou0(u16 zuo,u16 you);//����ֱ�����ɨ����ǽ
void bizhangyouzhixian(void);//�ñ�������ֱ��
void bzylinesebiaoyou0(void);//������ֱ��֪��ɫ����0

