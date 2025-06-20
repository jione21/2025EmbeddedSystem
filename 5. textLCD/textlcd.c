#include "textlcd.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// LCD 초기화: 디스플레이 ON, 커서/블링크 OFF
int textLcdInit(void)
{
    int fd = open(TEXTLCD_DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("textLcdInit: open failed");
        return 0;
    }

    stTextLCD lcd;
    memset(&lcd, 0, sizeof(stTextLCD));
    lcd.cmd = CMD_DISPLAY_MODE;
    lcd.cmdData = BIT_DISPLAY_MODE_DISP_ENABLE;

    write(fd, &lcd, sizeof(stTextLCD));
    close(fd);
    return 1;
}

// 지정된 라인에 문자열 출력 (1 or 2 line, 최대 16자)
int textLcdWriteLine(int line, const char* str)
{
    if (line < 1 || line > 2 || str == NULL) {
        fprintf(stderr, "textLcdWriteLine: invalid line or null string\n");
        return 0;
    }

    int fd = open(TEXTLCD_DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("textLcdWriteLine: open failed");
        return 0;
    }

    stTextLCD lcd;
    memset(&lcd, 0, sizeof(stTextLCD));
    lcd.cmd = CMD_WRITE_STRING;
    lcd.cmdData = (line == 1) ? CMD_DATA_WRITE_LINE_1 : CMD_DATA_WRITE_LINE_2;

    int len = strlen(str);
    if (len > COLUMN_NUM)
        len = COLUMN_NUM;

    memcpy(lcd.TextData[line - 1], str, len);

    write(fd, &lcd, sizeof(stTextLCD));
    close(fd);
    return 1;
}

// LCD 전체 클리어
int textLcdClear(void)
{
    return textLcdWriteLine(1, "                ") &&
           textLcdWriteLine(2, "                ");
}
