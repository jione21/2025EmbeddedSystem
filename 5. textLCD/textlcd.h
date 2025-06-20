#ifndef _TEXTLCD_H_
#define _TEXTLCD_H_

#define TEXTLCD_DEVICE_NAME "/dev/peritextlcd"

// 기본 설정
#define LINE_NUM        2
#define COLUMN_NUM      16
#define LINE_BUFF_NUM   (COLUMN_NUM + 4)  // 드라이버는 20바이트 기대 (dummy 포함)

// 명령/데이터 모드 구분
#define MODE_CMD        0
#define MODE_DATA       1

// 디스플레이 모드 명령어
#define CMD_DISPLAY_MODE                0x10
#define BIT_DISPLAY_MODE_CURSOR_DISP   0x01
#define BIT_DISPLAY_MODE_CURSOR_BLINK  0x02
#define BIT_DISPLAY_MODE_DISP_ENABLE   0x04

// 커서 이동 모드
#define CMD_CURSOR_MOVE_MODE           0x11
#define CURSOR_MOVE_MODE_ENABLE        0x01
#define CURSOR_MOVE_MODE_RIGHT_DIR     0x02

// 커서 위치 이동
#define CMD_CURSOR_MOVE_POSITION       0x12
#define CURSOR_MOVE_X_MASK             0x3F
#define CURSOR_MOVE_Y_MASK             0xC0

// 문자열 출력 명령
#define CMD_WRITE_STRING               0x20
#define CMD_DATA_WRITE_BOTH_LINE       0
#define CMD_DATA_WRITE_LINE_1          1
#define CMD_DATA_WRITE_LINE_2          2

// GPIO 테스트 (디버깅용)
#define CMD_TEST_GPIO_HIGH             0x30
#define CMD_TEST_GPIO_LOW              0x31

// 드라이버에 전달할 데이터 구조체
typedef struct {
    unsigned char cmd;
    unsigned char cmdData;
    unsigned char reserved[2];
    char TextData[LINE_NUM][LINE_BUFF_NUM];  // 각 라인당 20바이트 필요
} stTextLCD;

// 함수 프로토타입
int textLcdInit(void);
int textLcdWriteLine(int line, const char* str);
int textLcdClear(void);

#endif  // _TEXTLCD_H_
