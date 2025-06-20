#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "button.h"
#include "led.h"
#include "buzzer.h"

int main(void)
{
    BUTTON_MSG_T msg;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

    // 초기화
    ledLibInit();
    buttonInit();
    buzzerInit();

    while (1)
    {
        msgrcv(msgID, &msg, sizeof(BUTTON_MSG_T) - sizeof(long int), 0, 0);

        int ledNum = -1;
        int scale = -1;
        const char* noteName = NULL;

        if (msg.pressed)
        {
            // BTN 키 코드 기반 매핑
            switch (msg.keyInput)
            {
                case 102:  // KEY_HOME
                    ledNum = 0; scale = 1; noteName = "DO"; break;
                case 158:  // KEY_BACK
                    ledNum = 1; scale = 2; noteName = "RE"; break;
                case 217:  // KEY_SEARCH
                    ledNum = 2; scale = 3; noteName = "MI"; break;
                case 139:  // KEY_MENU
                    ledNum = 3; scale = 4; noteName = "FA"; break;
                case 115:  // KEY_VOLUMEUP
                    ledNum = 4; scale = 5; noteName = "SOL"; break;
                case 114:  // KEY_VOLUMEDOWN
                    ledNum = 5; scale = 6; noteName = "LA"; break;
                default:
                    printf("Unknown button (key code = %d)\n", msg.keyInput);
                    continue;
            }

            // 동작 수행
            ledOnOff(ledNum, 1);
            buzzerSTART(scale);
            printf("LED %d ON /  BTN %d PUSHED / BUZZER play %s\n", ledNum + 1, ledNum + 1, noteName);

            sleep(1);

            ledOnOff(ledNum, 0);
            buzzerEND();
            printf("LED %d OFF\n", ledNum + 1);
        }
    }

    // 자원 해제
    ledLibExit();
    buttonExit();
    buzzerExit();

    return 0;
}
