#include <stdio.h>
#include <unistd.h>
#include "temperature.h"

#define TEMP_DEVICE_PATH "/dev/spidev1.0"  // 디바이스 경로는 환경에 맞게 수정

int main(void)
{
    int fd = temperatureInit(TEMP_DEVICE_PATH);
    if (fd < 0) {
        fprintf(stderr, "Failed to initialize temperature sensor.\n");
        return 1;
    }

    while (1)
    {
        int temp = readTemperature(fd);
        if (temp == -999) {
            fprintf(stderr, "Failed to read temperature.\n");
        } else {
            printf("Current Temperature: %d°C\n", temp);
        }

        sleep(1);  // 1초마다 측정
    }

    temperatureClose(fd);
    return 0;
}
