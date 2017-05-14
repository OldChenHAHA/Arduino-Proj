#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "config.h"


/*
   菜单结构
   一个数组既代表一级菜单，数组中的一个元素就是一个菜单项，就是一个单独的结构体，
   数组中的第一个元素中的num值很重要，表示本级菜单具有多少个菜单项。

   @var int num 本级菜单数量，必须在第一项中设置正确的菜单项数量
   @var char* label 菜单文本
   @var int type 此项类型，参考宏定义
   @var void (*action)(const char *) 指向动作的函数指针，此项要执行的具体动作函数
   @var mymenu* next 下一级菜单，只需在菜单的第一项设置，其他项置空（NULL）即可
   @var mymenu* prev 上一级菜单，同上
*/
typedef struct menu {
    int num;
    char label[20]; //display label
    float param_val;  
    int type; //0:item, 1:submenu, 2:param  
    void (*action)(const char *);
    struct menu * next;
    struct menu * prev;
} mymenu;



class KEY {
public:

    KEY();

    void Initialise();
    int getKeyAction();

   ~KEY();

private:

    // 定义按键消抖延时时间
    const int KEY_TREMBLE_TIME = 20;

    // 定义LCD背光显示计时变量，无按键操作超时就关闭背光
    unsigned long starttime;
    unsigned long endtime;

    int k_up,k_down,k_enter,k_exit;
    int old_k_up,old_k_down,old_k_enter,old_k_exit;

};



extern void ledtest(const char *stat);
extern void Backlight(const char *stat);
extern void updateMenu(void);
extern void drawMenu(void);

extern mymenu main_menu[7];
extern mymenu set_winter_delay[13];
extern mymenu set_summer_delay[13];
extern mymenu set_param_values[8];
extern mymenu set_work_mode[6];
extern mymenu set_PID_values[6];

extern mymenu *cur_item, *prev_item;
extern int cur_item_index, disp_start_index;

extern bool menu_draw_required;
extern bool flag_changing_param_val;

extern U8GLIB_ST7920_128X64_1X u8g;
extern KEY keyObj;


#endif
