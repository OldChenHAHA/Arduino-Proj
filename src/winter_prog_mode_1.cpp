#define NOT_CLOSED HIGH //没闭合
#define HAVE_INPUT HIGH  // 有输入
#define START_UP HIGH // 启动
#define SHUT_DOWN LOW // 停止
#define CUT_OFF LOW // 断开



int winter_prog_mode_1()
{
    if ( digitalRead(PIN_02) ==  NOT_CLOSED) // 检测0.2消防控制是否闭合
    {
      save_alert_msg("0.2消防控制没闭合");  // 存储报警信息
      Serial485.printf("0.2消防控制没闭合"); // 485输出
      shut_down_all(); // 输出全部停机
      return 1;
    }

    int val_PIN_i11 = digitalRead(PIN_i11);
    int val_PIN_i14 = digitalRead(PIN_i14);
    int val_PIN_i21 = digitalRead(PIN_i21);
    int val_PIN_i22 = digitalRead(PIN_i22);
    int val_PIN_i23 = digitalRead(PIN_i23);
    int val_PIN_i24 = digitalRead(PIN_i24);
    int val_PIN_i25 = digitalRead(PIN_i25);
    int val_PIN_i26 = digitalRead(PIN_i26);
    int val_PIN_i27 = digitalRead(PIN_i27);
    int val_PIN_i30 = digitalRead(PIN_i30);
    int val_PIN_i31 = digitalRead(PIN_i31);
    int val_PIN_i32 = digitalRead(PIN_i32);
    int val_PIN_i33 = digitalRead(PIN_i33);

    if (val_PIN_11==HAVE_INPUT || val_PIN_14==HAVE_INPUT || val_PIN_21==HAVE_INPUT || val_PIN_22==HAVE_INPUT || val_PIN_23==HAVE_INPUT || val_PIN_24==HAVE_INPUT || val_PIN_25==HAVE_INPUT || val_PIN_26==HAVE_INPUT || val_PIN_27==HAVE_INPUT || val_PIN_30==HAVE_INPUT || || val_PIN_31==HAVE_INPUT || || val_PIN_32==HAVE_INPUT || || val_PIN_33==HAVE_INPUT )
    {
      save_alert_msg("有报警信号输入");  // 存储报警信息
      Serial485.printf("有报警信号输入"); // 485输出
      return 0;
    }

    if ( digitalRead(PIN_i34) == CLOSED ) // 检测i3.4是否闭合
    {
        // i3.4闭合
        if ( digitalRead(PIN_06) == CLOSED )
        {
            delay(3000); // T06延时3秒，启动Q1.7
            digitalWrite(PIN_Q17, START_UP);
            if ( digitalRead(PIN_22) == CLOSED )
            {   //是
                digitalWrite(PIN_Q17, SHUT_DOWN); // 停Q1.7
                save_alert_msg("2.2闭合");  // 存储报警信息
                Serial485.printf("2.2闭合"); // 485输出
                return 0;
            }
            else 
            {
                goto tag1;
            }

        }
        else // 0.6没闭合
        {
            delay(3000); // T06延时3s，启动Q2.0
            digitalWrite(PIN_Q20, START_UP);
            if (digitalRead(PIN_26) == CLOSED) // 检测2.6是否闭合
            { //2.6闭合
                /* code */
            }
            else //2.6没闭合
            {
                tag1:if( digitalRead(PIN_i10) ) // i1.0是否闭合
                { // i1.0 闭合
                    delay(3000); //T08延时3s，启动Q2.3
                    digitalWrite(PIN_Q23, START_UP);
                    if (digitalRead(PIN_i24) == CLOSED)//检测i2.4是否闭合
                    {//i2.4闭合
                        //停Q2.3，报警
                        digitalWrite(PIN_Q23, SHUT_DOWN);
                        save_alert_msg("i2.4闭合");  // 存储报警信息
                        Serial485.printf("i2.4闭合"); // 485输出
                        return 0;
                    }
                    else
                    {//i2.4没闭合
                        goto tag2;
                    }
                }
                else
                {// i1.0 没闭合
                    //T08延时3s，启动Q2.4
                    delay(3000);
                    digitalWrite(PIN_Q24, START_UP);
                    if ( digitalRead(PIN_i30)==CLOSED )//检测i3.0是否闭合
                    {//i3.0 闭合
                        // 停Q2.4 报警
                        digitalWrite(PIN_Q24, SHUT_DOWN);
                        save_alert_msg("i3.0闭合");  // 存储报警信息
                        Serial485.printf("i3.0闭合"); // 485输出
                        return 0;
                    }
                    else
                    {// i3.0没闭合
                        tag2: if (digital(PIN_34) == CUT_OFF) // 检测3.4是否断开
                        {// 3.4断开
                            if( digitalRead(PIN_i20) == CUT_OFF )//i2.0是否断开
                            {// i2.0断开
                                // 停Q1.7或者Q2.0 存信息
                                digitalWrite(PIN_Q17, SHUT_DOWN);
                                save_alert_msg("i2.0断开");  // 存储报警信息
                                Serial485.printf("i2.0断开"); // 485输出
                                return 0;
                            }
                            else
                            {// i2.0 没断开
                                goto tag3;
                            }
                        }
                        else
                        {//3.4没断开
                            goto tag3;
                        }
                    }

                }

            }


        }
    }
    else
    {// i3.4没闭合
        tag3:if( digitalRead(PIN_i01)==CLOSED )//i0.1是否闭合
        {// i0.1闭合


        }
        else
        {// i0.1没闭合
            if()//i1.7是否闭合
            {// i1.7闭合



            }
            else
            {// i1.7没闭合
                return 0;
            }

        }







        
    }



}
