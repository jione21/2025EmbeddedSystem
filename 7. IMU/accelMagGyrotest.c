#include <stdio.h>
#include <unistd.h>  // for sleep()
#include "accelMagGyro.h"

int main(void)
{
    SensorData accel, magne, gyro;

    while (1)
    {
        // 가속도계 값 읽기
        if (readAccelerometer(&accel) == 0) {
            printf("[Accelerometer] X: %d, Y: %d, Z: %d\n", accel.x, accel.y, accel.z);
        } else {
            fprintf(stderr, "Failed to read accelerometer data\n");
        }

        // 자기장 센서 값 읽기
        if (readMagnetometer(&magne) == 0) {
            printf("[Magnetometer]  X: %d, Y: %d, Z: %d\n", magne.x, magne.y, magne.z);
        } else {
            fprintf(stderr, "Failed to read magnetometer data\n");
        }

        // 자이로 센서 값 읽기
        if (readGyroscope(&gyro) == 0) {
            printf("[Gyroscope]     X: %d, Y: %d, Z: %d\n", gyro.x, gyro.y, gyro.z);
        } else {
            fprintf(stderr, "Failed to read gyroscope data\n");
        }

        printf("--------------------------------------------------\n");

        sleep(1);  // 1초마다 갱신
    }

    return 0;
}
