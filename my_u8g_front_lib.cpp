//
///*
//   逻辑参数设置菜单
//   逻辑菜单表示菜单项中的action函数要执行逻辑设置动作，即设置某个参数的逻辑值
//   逻辑菜单只需两个菜单项代表true和false
//   需要遵守的规则为：菜单中的文本需要设置为“ON”和“OFF”，
//   在执行动作函数的时候，可以将正确的参数传递过去，
//   动作函数的规则参照函数说明
//*/
//// mymenu logic_menu[2] = {
////     {2, "ON", MENU_PARAM, NULL, NULL, NULL},
////     {2, "OFF", MENU_PARAM, NULL, NULL, NULL}
//// };
//
//
//// uint8_t delay_param[2][13] = { // 0:winter, 1:summer
////     { 10,10 }, // 启动延时 10s
////     { 180,180 }, // M2开到位 180s
////     { 180,180 }, // M1开到位 180s
////     { 3,3 }, // 延时开J1 3s
////     { 3,3 }, // 延时开B1 3s
////     { 3,3 }, // 延时开B2 3s
////     { 3,3 }, // 延时开B3 3s
////     { 3,3 }, // 延时开B4 3s
////     { 10,10 }, // 停机延时 10s
////     { 1200,0 }, // 加湿延时 1200s 和 0s
////     { 10,10 }, // 延时停风阀 10s
////     { 180,180 } // M2关到位 180s
//// };
//
//// 第一级菜单
//mymenu main_menu[8] = {
//    {8, "参数显示", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "报警信息显示", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "报警信息查询", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "冬季延时设置", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "夏季延时设置", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "参数设置", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "工作模式选择", 0, MENU_SUBMENU, NULL, NULL, NULL},
//    {8, "PID参数设置", 0, MENU_SUBMENU, NULL, NULL, NULL}
//};
//
//// 第二级菜单
//
//mymenu cur_alert_message = {1, "cur_alert_message", MENU_ACTION_NONE, NULL, NULL, NULL};
//mymenu record_alert_message[30];
//
//mymenu set_winter_delay[13] = {
//    {13, "01 启动延时:     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "02 M2开到位:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "03 M1开到位:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "04 延时开J1:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "05 延时开B1:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "06 延时开B2:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "07 延时开B3:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "08 延时开B4:     s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "09 停机延时:     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "10 加湿延时:     s",1200, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "11 延时停阈:     s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "12 M2关延时:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "13 M1关延时:     s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL}
//};
//
//mymenu set_summer_delay[13] = {
//    {13, "14 启动延时:    s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "15 M2开到位:    s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "16 M1开到位:    s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "17 延时开J1:    s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "18 延时开B1:    s",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "19 延时开B2;    s",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "20 延时开B3;    s",  3, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "21 延时开B4:    s",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "22 停机延时:    s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "23 加湿延时:    s",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "24 延时停阈:    s", 10, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "25 M2关延时:    s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {13, "26 M1关延时:    s",180, MENU_ACTION_NUMBER, NULL, NULL, NULL}
//};
//
//mymenu set_param_values[8] = {
//    {8, "T01 =     'C",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "F01 =      %",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "T02 =     'C",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "F02 =      %",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "T03 =     'C",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "F03 =      %",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "T05 =     'C",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {8, "F05 =      %",  0, MENU_ACTION_NUMBER, NULL, NULL, NULL}
//};
//
//mymenu set_work_pattern[6] = {
//    {6, "模式1", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
//    {6, "模式2", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
//    {6, "模式3", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
//    {6, "模式4", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
//    {6, "模式5", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL},
//    {6, "模式6", 0, MENU_ACTION_LOGIC, NULL, NULL, NULL}
//};
//
//mymenu set_PID_values[6] = {
//    {6, "PID1参数", 0, MENU_ACTION_NONE, NULL, NULL, NULL},
//    {6, "P1 = ", 0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {6, "I1 = ", 0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {6, "PID2参数", 0, MENU_ACTION_NONE, NULL, NULL, NULL},
//    {6, "P2 = ", 0, MENU_ACTION_NUMBER, NULL, NULL, NULL},
//    {6, "I2 = ", 0, MENU_ACTION_NUMBER, NULL, NULL, NULL}
//};
