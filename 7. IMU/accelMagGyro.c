#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "accelMagGyro.h"

// 센서 데이터 읽기 (공통 내부 함수)
static int readSensor(const char *basePath, SensorData *data)
{
    char path[100];
    int fd;
    FILE *fp;

    // 센서 활성화 (enable)
    snprintf(path, sizeof(path), "%senable", basePath);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open enable file");
        return -1;
    }
    dprintf(fd, "1");
    close(fd);

    // 센서 데이터 읽기
    snprintf(path, sizeof(path), "%sdata", basePath);
    fp = fopen(path, "rt");
    if (fp == NULL) {
        perror("Failed to open data file");
        return -1;
    }

    if (fscanf(fp, "%d, %d, %d", &data->x, &data->y, &data->z) != 3) {
        fprintf(stderr, "Failed to parse sensor data\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

// 가속도계 데이터 읽기
int readAccelerometer(SensorData *data)
{
    return readSensor(ACCEL_PATH, data);
}

// 자기장 센서 데이터 읽기
int readMagnetometer(SensorData *data)
{
    return readSensor(MAGNE_PATH, data);
}

// 자이로 센서 데이터 읽기
int readGyroscope(SensorData *data)
{
    return readSensor(GYRO_PATH, data);
}
