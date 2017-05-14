#define NOT_CLOSED HIGH
#define HAVE_INPUT HIGH




int winter_prog_mode_1()
{
    if ( digitalRead(PIN_02) ==  NOT_CLOSED) // 检测0.2消防控制是否闭合
    {
      save_alert_msg("0.2消防控制没闭合");  // 存储报警信息
      Serial485.printf("0.2消防控制没闭合"); // 485输出
      shut_down_all(); // 输出全部停机
      return 1;
    }

    int val_PIN_11 = digitalRead(PIN_11);
    int val_PIN_14 = digitalRead(PIN_14);
    int val_PIN_21 = digitalRead(PIN_21);
    int val_PIN_22 = digitalRead(PIN_22);
    int val_PIN_23 = digitalRead(PIN_23);
    int val_PIN_24 = digitalRead(PIN_24);
    int val_PIN_25 = digitalRead(PIN_25);
    int val_PIN_26 = digitalRead(PIN_26);
    int val_PIN_27 = digitalRead(PIN_27);
    int val_PIN_30 = digitalRead(PIN_30);
    int val_PIN_31 = digitalRead(PIN_31);
    int val_PIN_32 = digitalRead(PIN_32);
    int val_PIN_33 = digitalRead(PIN_33);

    if (val_PIN_11==HAVE_INPUT || val_PIN_14==HAVE_INPUT || val_PIN_21==HAVE_INPUT || val_PIN_22==HAVE_INPUT || val_PIN_23==HAVE_INPUT || val_PIN_24==HAVE_INPUT || val_PIN_25==HAVE_INPUT || val_PIN_26==HAVE_INPUT || val_PIN_27==HAVE_INPUT || val_PIN_30==HAVE_INPUT || || val_PIN_31==HAVE_INPUT || || val_PIN_32==HAVE_INPUT || || val_PIN_33==HAVE_INPUT )
    {
      save_alert_msg("有报警信号输入");  // 存储报警信息
      Serial485.printf("有报警信号输入"); // 485输出
      return 0;
    }

    if ( digitalRead(PIN_34) == CLOSED ) // 检测3.4是否闭合
    {
        // 是
        if ( digitalRead(PIN_06) == CLOSED )
        {

        }
        else
        {

        }
    }
    else
    {
        // 否
    }



}
