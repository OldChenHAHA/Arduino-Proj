
#include "config.h"
#include "myfunctions.h"
/*
   逻辑动作测试函数

   @var const char* stat 根据此参数来执行动作，这里测试PIN13的LED
*/
//void ledtest(const char *stat)
//{
//    //根据参数决定LED开关
//#ifdef DEBUG
//    Serial.println(stat);
//#endif
//    digitalWrite(LED_PIN, strcmp(stat, "ON") ? LOW : HIGH);
//}

/*
   关闭LCD背光
   此函数符合菜单动作定义规则，即无返回值、一个字符串参数

   @var const char* stat 值为“ON"打开背光，为“OFF”关闭背光
*/
void Backlight(const char *stat)
{
    //这里定义了一个逻辑动作
    //根据参数决定LCD背光的开关
    digitalWrite(backlightPin, strcmp(stat, "ON") ? LOW : HIGH);
}

KEY::KEY(void) {};
KEY::~KEY(void) {};

void KEY::Initialise() {
    //设置按键为上拉电阻输入（低电平有效）
    pinMode(KEY_UP_PIN, INPUT_PULLUP);
    pinMode(KEY_DOWN_PIN, INPUT_PULLUP);
    pinMode(KEY_ENTER_PIN, INPUT_PULLUP);
    pinMode(KEY_EXIT_PIN, INPUT_PULLUP);

    // 初始化按键值为高电平
    k_down = HIGH;
    k_up = HIGH;
    k_enter = HIGH;
    k_exit = HIGH;
    old_k_up = HIGH;
    old_k_down = HIGH;
    old_k_enter = HIGH;
    old_k_exit = HIGH;
    // 按键开始计时
    starttime = millis();

}

int KEY::getKeyAction() {

    endtime = millis();
    //计算无按键时间，决定是否关闭LCD背光
    if (endtime - starttime > 5000) {
        Backlight("OFF");
    }

    old_k_up = digitalRead(KEY_UP_PIN);
    old_k_down = digitalRead(KEY_DOWN_PIN);
    old_k_enter = digitalRead(KEY_ENTER_PIN);
    old_k_exit = digitalRead(KEY_EXIT_PIN);

    delay(KEY_TREMBLE_TIME);

    k_up = digitalRead(KEY_UP_PIN);
    k_down = digitalRead(KEY_DOWN_PIN);
    k_enter = digitalRead(KEY_ENTER_PIN);
    k_exit = digitalRead(KEY_EXIT_PIN);

    //有键按下，打开LCD背光，计时清零
    if (k_up == LOW || k_down == LOW || k_enter == LOW || k_exit == LOW) {
        //myGLCD.disableSleep();
        Backlight("ON");
        starttime = endtime;
    }

    int key_action = KEY_NONE_ACTION;
    // 检测按键
    if (k_up == LOW && old_k_up == LOW) {
        key_action = KEY_UP_ACTION;
    }
    else if (k_down == LOW && old_k_down == LOW) {
        key_action = KEY_DOWN_ACTION;
    }
    else if (k_enter == LOW && old_k_enter == LOW) {
        key_action = KEY_ENTER_ACTION;
    }
    else if (k_exit == LOW && old_k_exit == LOW) {
        key_action = KEY_EXIT_ACTION;
    }
    else {
        key_action = KEY_NONE_ACTION;
    }

    return key_action;

}


void updateMenu(void)
{
    int cur_menu_num = cur_item[0].num;
    int idx = disp_start_index + cur_item_index;

    switch (keyObj.getKeyAction())
    {
    case KEY_UP_ACTION:
        if(flag_changing_param_val)
        {
            cur_item[idx].param_val += 0.1;
            break;
        }   
    
        cur_item_index--;
        /* 菜单项上选择是否越界 */
        if (cur_item_index < 0)
        {
            cur_item_index = 0;
            disp_start_index--;
            if (disp_start_index < 0)   disp_start_index = 0;
        }

        break;
    case KEY_DOWN_ACTION:
        if(flag_changing_param_val)
        {
            cur_item[idx].param_val -= 0.1;
            break;
        }
            
        cur_item_index++;
        /* 菜单项下选择是否越界 */
        if (cur_item_index >= MENU_MAX_ROW || cur_item_index >= cur_menu_num)
        {
            if (cur_item_index >= cur_menu_num)	    cur_item_index = cur_menu_num - 1;
            if (cur_item_index >= MENU_MAX_ROW)	  cur_item_index = MENU_MAX_ROW - 1;
            if (disp_start_index + MENU_MAX_ROW < cur_menu_num)	disp_start_index ++;
        }
        break;
    case KEY_ENTER_ACTION:
        // 计算此时菜单项索引值
        if (cur_item[idx].next != NULL && cur_item[idx].type == MENU_SUBMENU)
        {
            // 条件成立说明此菜单项指向了下一级菜单
            prev_item = cur_item;
            cur_item = cur_item[idx].next;
            // 重置菜单项索引和绘图索引
            cur_item_index = 0;
            disp_start_index = 0;
        }
        else if ( cur_item[idx].type == MENU_ACTION_NUMBER )
        {
            flag_changing_param_val = true;
        }
        else if (cur_item[idx].type == MENU_ACTION_LOGIC)
        {
            //cur_item[idx].action();
        }
        break;
    case KEY_EXIT_ACTION:
        if(flag_changing_param_val)
        {
            flag_changing_param_val = false;
            break;
        }
        if (prev_item != NULL)
        {
            cur_item = prev_item;
            prev_item = cur_item[0].prev;
            // 重置菜单项索引和绘图索引
            cur_item_index = 0;
            disp_start_index = 0;
            
        }
        break;
    default:
        return;
        break;
    }
    menu_draw_required = true;

}


void drawMenu()
{

    int i, h;
    u8g_uint_t w, d;

    u8g.setFont(u8g_font_6x13);
    u8g.setFontRefHeightText();
    u8g.setFontPosTop();

    h = u8g.getFontAscent() - u8g.getFontDescent();
    w = u8g.getWidth();

    for ( i = 0; i < min(MENU_MAX_ROW,cur_item[0].num); i++ )
    {
        int idx_temp = i+disp_start_index;
        char *label = cur_item[idx_temp].label;
        if (cur_item[idx_temp].type == MENU_ACTION_NUMBER)
        {   
            char char_temp[8];
            if (flag_changing_param_val)
                sprintf(char_temp,"U/D %10.0f",cur_item[idx_temp].param_val);
            else 
                sprintf(char_temp,"    %10.0f",cur_item[idx_temp].param_val);
            
            for (int i_temp=0; i_temp < strlen(char_temp); i_temp++)
            {
                label[6 + i_temp] = char_temp[i_temp];
            }
        }
        
        d = (w - u8g.getStrWidth(label)) / 2;
        u8g.setDefaultForegroundColor();
        if ( i == cur_item_index )
        {
            u8g.drawBox(0, i * h + 1, w, h);
            u8g.setDefaultBackgroundColor();
        }
        //u8g.drawStr(d, i * h, label);
        u8g.drawStr(0, i * h, label);

    }

}




// 第一级菜单
mymenu main_menu[7] = {
    {7, "alert msg show", 0, MENU_SUBMENU, NULL, NULL, NULL},
    {7, "alert msg find", 0, MENU_SUBMENU, NULL, NULL, NULL},
    {7, "winter delay set", 0, MENU_SUBMENU, NULL, NULL, NULL},
    {7, "summer delay set", 0, MENU_SUBMENU, NULL, NULL, NULL},
    {7, "param set", 0, MENU_SUBMENU, NULL, NULL, NULL},
    {7, "woke mode choose", 0, MENU_SUBMENU, NULL, NULL, NULL},
    {7, "PID param set", 0, MENU_SUBMENU, NULL, NULL, NULL}
};

// 第二级菜单

mymenu cur_alert_message = {1, "cur_alert_message: ",0, MENU_ACTION_NONE, NULL, NULL, NULL};
mymenu record_alert_message[30];

mymenu set_winter_delay[13] = {
    {13, "01setupdey:    s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "02M2done:      s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "03M1done:      s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "04delayJ1:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "05delayB1:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "06delayB2:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "07delayB3:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "08delayB4:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "09shutdel:     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "10wetdel :     s",1200, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "11delthr :     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "12M2close:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "13M1close:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL}
};

mymenu set_summer_delay[13] = {
    {13, "14setupdey:    s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "15M2done:      s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "16M1done:      s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "17delayJ1:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "18delayB1:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "19delayB2:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "20delayB3:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "21delayB4:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "22shutdel:     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "23wetdel :     s",0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "24delthr :     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "25M2close:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {13, "26M1close:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL}
};

mymenu set_param_values[8] = {
    {8, "T01 =     'C",  10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "F01 =      %",  11, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "T02 =     'C",  12, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "F02 =      %",  13, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "T03 =     'C",  13, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "F03 =      %",  14, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "T05 =     'C",  54, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {8, "F05 =      %",  16, MENU_ACTION_NUMBER, NULL, NULL, NULL}
};

mymenu set_work_mode[6] = {
    {6, "mode 1", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
    {6, "mode 2", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
    {6, "mode 3", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
    {6, "mode 4", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
    {6, "mdoe 5", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
    {6, "mode 6", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL}
};

mymenu set_PID_values[6] = {
    {6, "PID1 param", 0, MENU_ACTION_NONE, NULL, NULL, NULL},
    {6, "P1 = ", 12, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {6, "I1 = ", 12, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {6, "PID2 param", 0, MENU_ACTION_NONE, NULL, NULL, NULL},
    {6, "P2 = ", 13, MENU_ACTION_NUMBER, NULL, NULL, NULL},
    {6, "I2 = ", 13, MENU_ACTION_NUMBER, NULL, NULL, NULL}
};



// 定义菜单操作需要的全局变量
// 分别为当前菜单、上一级菜单、当前菜单项索引和开始显示的菜单项索引
mymenu *cur_item, *prev_item;
int cur_item_index, disp_start_index;

bool menu_draw_required = false;
bool flag_changing_param_val = false;

U8GLIB_ST7920_128X64_1X u8g(LCD_EN_PIN, LCD_RW_PIN, LCD_RS_PIN);
KEY keyObj;


