#include <stdio.h>
#include <unistd.h>  // for sleep()
#include "colorled.h"

int main(void)
{
    // 컬러 LED 초기화
    ColorLEDInit();

    // 빨간색 ON
    ColorLEDSetColor(100, 0, 0);
    printf("Red LED ON\n");
    sleep(1);

    // 초록색 ON
    ColorLEDSetColor(0, 100, 0);
    printf("Green LED ON\n");
    sleep(1);

    // 파란색 ON
    ColorLEDSetColor(0, 0, 100);
    printf("Blue LED ON\n");
    sleep(1);

    // 종료 시 LED OFF
    ColorLEDSetColor(0, 0, 0);
    ColorLEDClose();
    printf("LED OFF and ColorLED closed.\n");

    return 0;
}
