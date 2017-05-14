#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG

#include "Arduino.h"
#include "U8glib.h"

/* 定义arduino 引脚*/
// CONTROL KEY PIN
#define KEY_UP_PIN 4
#define KEY_DOWN_PIN 5
#define KEY_ENTER_PIN 6
#define KEY_EXIT_PIN 7
//LCD SPI Com: SCK = en = 13, MOSI = rw = 12, CS = di = 11
#define LCD_EN_PIN 13
#define LCD_RW_PIN 12
#define LCD_RS_PIN 11
#define backlightPin 10

// LCD屏幕上菜单的最大显示行数
#define MENU_MAX_ROW 4

/* 以下定义菜单项类型*/
#define MENU_SUBMENU 0 // 具有子菜单的菜单项
#define MENU_PARAM 1   // 参数项（用于执行参数设置）
#define MENU_ACTION_NONE 101  // 无动作的菜单项
#define MENU_ACTION_LOGIC 102  // 执行逻辑参数设置的菜单项（开/关、真/假等设置）
#define MENU_ACTION_NUMBER 103  // 执行数值调整设置的菜单项（时间、音量等设置）
#define MENU_ACTION_STRING 104  // 执行字符串设置的菜单项（欢迎语、LED显示文字等设置）

// KEY ACTION DEFINE
#define KEY_NONE_ACTION 0
#define KEY_UP_ACTION 1
#define KEY_DOWN_ACTION 2
#define KEY_ENTER_ACTION 3
#define KEY_EXIT_ACTION 4








#endif
