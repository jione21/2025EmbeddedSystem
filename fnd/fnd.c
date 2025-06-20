#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "fnd.h"

#define FND_DRIVER_NAME "/dev/perifnd"

// 정수 숫자 출력 (ex. 123456)
int fndDisp(int num, int dotflag)
{
    int fd;
    stFndWriteForm stWriteData;

    // dotflag 및 유효 데이터 설정
    for (int i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = (dotflag >> i) & 0x01;
        stWriteData.DataValid[i] = 1;
    }

    // 각 자리 숫자 분리
    int value = num % 1000000;
    stWriteData.DataNumeric[0] = value / 100000;
    stWriteData.DataNumeric[1] = (value / 10000) % 10;
    stWriteData.DataNumeric[2] = (value / 1000) % 10;
    stWriteData.DataNumeric[3] = (value / 100) % 10;
    stWriteData.DataNumeric[4] = (value / 10) % 10;
    stWriteData.DataNumeric[5] = value % 10;

    // FND 디바이스 열기 및 출력
    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0) {
        perror("fndDisp: FND driver open failed");
        return 0;
    }

    write(fd, &stWriteData, sizeof(stFndWriteForm));
    close(fd);
    return 1;
}

// 현재 시간 표시 (예: 15:34:12 → 153412)
int fndDispTime(void)
{
    time_t tTime;
    if (time(&tTime) == -1) {
        perror("fndDispTime: time get failed");
        return 0;
    }

    struct tm *ptmcur = localtime(&tTime);
    int number = ptmcur->tm_hour * 10000 +
                 ptmcur->tm_min * 100 +
                 ptmcur->tm_sec;

    // 점 표시 위치: 시:분:초
    return fndDisp(number, 0x0A);  // 0b1010
}

