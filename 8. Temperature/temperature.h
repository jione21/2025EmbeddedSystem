#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

int temperatureInit(const char *devicePath);
int readTemperature(int fd);
void temperatureClose(int fd);

#endif
