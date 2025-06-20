#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>     // for open/close
#include <fcntl.h>      // for O_RDWR
#include <sys/ioctl.h>  // for ioctl
#include <sys/ipc.h>    // for msgget(), msgrcv(), msgsnd()
#include <sys/msg.h>    // for IPC_CREAT, IPC_RMID, IPC_NOWAIT

#include "button.h"
#include "led.h"

int main(void)
{
    BUTTON_MSG_T msg;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

    // 초기화
    ledLibInit();
    buttonInit();

    while (1)
    {
        // 메시지 수신 (버튼 이벤트)
        msgrcv(msgID, &msg, sizeof(BUTTON_MSG_T) - sizeof(long int), 0, 0);

        int ledNum = -1;

        // 키 코드에 따라 LED 번호 매핑
        switch (msg.keyInput)
        {
            case KEY_HOME:        ledNum = 0; break;
            case KEY_BACK:        ledNum = 1; break;
            case KEY_SEARCH:      ledNum = 2; break;
            case KEY_MENU:        ledNum = 3; break;
            case KEY_VOLUMEUP:    ledNum = 4; break;
            case KEY_VOLUMEDOWN:  ledNum = 5; break;
            default:
                printf("Unknown key code: %d\n", msg.keyInput);
                continue;
        }

        // 눌림 상태에 따라 LED ON/OFF
        if (msg.pressed)
        {
            printf("LED %d ON (Key code: %d)\n", ledNum + 1, msg.keyInput);
            ledOnOff(ledNum, 1);
        }
        else
        {
            printf("LED %d OFF (Key code: %d)\n", ledNum + 1, msg.keyInput);
            ledOnOff(ledNum, 0);
        }
    }

    // 자원 해제
    ledLibExit();
    buttonExit();

    return 0;
}
