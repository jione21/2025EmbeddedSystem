#include <stdio.h>
#include <unistd.h>  // for sleep()
#include "led.h"     // 우리가 만든 헤더

int main()
{
    if (ledLibInit() < 0)
    {
        printf("LED Driver Open Failed!\n");
        return -1;
    }

    // LED 0 ~ 4 순차적으로 ON
    for (int i = 0; i <= 4; i++)
    {
        printf("Turn on LED %d\n", i);
        ledOnOff(i, 1);
        sleep(1);  // 1초 대기
    }

    // LED 4 ~ 0 역순으로 OFF
    for (int i = 4; i >= 0; i--)
    {
        printf("Turn off LED %d\n", i);
        ledOnOff(i, 0);
        sleep(1);  // 1초 대기
    }

    ledLibExit();
    return 0;
}
