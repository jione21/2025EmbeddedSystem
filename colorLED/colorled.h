#ifndef __COLORLED_H__
#define __COLORLED_H__

#define MAX_INPUT_VALUE 100
#define PWM_FREQUENCY 100000

// 색상 인덱스
#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2

// 초기화 및 설정 함수
void ColorLEDInit(void);
void ColorLEDSetColor(int red, int green, int blue);
void ColorLEDClose(void);

#endif // __COLORLED_H__
