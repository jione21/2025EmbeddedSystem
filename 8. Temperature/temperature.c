#include "temperature.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define SPI_SPEED 20000

static char gbuf[10];

// SPI 디바이스 초기화
int temperatureInit(const char *devicePath)
{
    int fd;
    __u8 mode = 0, lsb, bits;
    __u32 speed = SPI_SPEED;

    fd = open(devicePath, O_RDWR);
    if (fd < 0) {
        perror("temperatureInit: Failed to open SPI device");
        return -1;
    }

    mode |= SPI_3WIRE;

    if (ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
        perror("temperatureInit: SPI_IOC_RD_MODE failed");
        close(fd);
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
        perror("temperatureInit: SPI_IOC_RD_LSB_FIRST failed");
        close(fd);
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("temperatureInit: SPI_IOC_RD_BITS_PER_WORD failed");
        close(fd);
        return -1;
    }

    return fd;
}

// 온도값 읽기 (섭씨 °C)
int readTemperature(int fd)
{
    memset(gbuf, 0, sizeof(gbuf));

    int len = read(fd, gbuf, 2);
    if (len != 2) {
        perror("readTemperature: SPI read failed");
        return -999;  // 에러 코드
    }

    int value = (gbuf[0] << 8) | gbuf[1];

    // 음수 보정 (2의 보수)
    if (value & 0x8000) {
        value = ~value + 1;
    }

    value >>= 7;  // 9비트 온도 데이터 (LSB 7비트는 무시)
    return value;
}

// SPI 디바이스 종료
void temperatureClose(int fd)
{
    close(fd);
}
