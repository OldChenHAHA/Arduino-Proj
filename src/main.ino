/*

    created by Mr.Chen

*/

#include "config.h"
#include "myfunctions.h"




void setup()
{
  pinMode(backlightPin, OUTPUT);
  Backlight("ON");
  /* 控制按键初始化 */
  keyObj.Initialise();

  /* 菜单之间的关联性设置 */
  main_menu[2].next = set_winter_delay;
  set_winter_delay[0].prev = main_menu;
  main_menu[3].next = set_summer_delay;
  set_summer_delay[0].prev = main_menu;
  main_menu[4].next = set_param_values;
  set_param_values[0].prev = main_menu;
  main_menu[5].next = set_work_mode;
  set_work_mode[0].prev = main_menu;
  main_menu[6].next = set_PID_values;
  set_PID_values[0].prev = main_menu;

  // 初始化当前菜单为第一集
  cur_item = main_menu;
  prev_item = NULL;
  // 当前选择菜单内第一项
  cur_item_index = 0;
  // 从第一项开始显示菜单
  disp_start_index = 0;
  // 为了初始化过程看清楚，按时3秒
  delay(1000);
  // 初始化完成，清屏并关闭LCD背光
  Backlight("OFF");

  menu_draw_required = 1;

#ifdef DEBUG
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("menu start");
#endif

}

void loop()
{
  // picture loop
  if (  menu_draw_required != 0 ) {
    u8g.firstPage();
    do  {
      drawMenu();
    } while ( u8g.nextPage() );
    menu_draw_required = 0;
  }

  updateMenu();

}

