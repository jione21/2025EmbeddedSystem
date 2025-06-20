#ifndef __ACCELMAGGYRO_H__
#define __ACCELMAGGYRO_H__

#define SENSOR_AXIS 3

// 각 센서의 데이터 저장용 구조체
typedef struct {
    int x;
    int y;
    int z;
} SensorData;

// 센서별 경로 상수
#define ACCEL_PATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNE_PATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYRO_PATH  "/sys/class/misc/FreescaleGyroscope/"

// 센서 초기화 및 데이터 읽기 함수
int readAccelerometer(SensorData *data);
int readMagnetometer(SensorData *data);
int readGyroscope(SensorData *data);

#endif
