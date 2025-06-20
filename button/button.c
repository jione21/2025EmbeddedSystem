#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static char buttonPath[200];
static int fd;
static int msgID;
static pthread_t buttonTh_id;

int probeButtonPath(char* newPath) {
    int returnValue = 0;
    int number = 0;
    FILE *fp = fopen(PROBE_FILE, "rt");
    char tmpStr[200];

    while (!feof(fp)) {
        fgets(tmpStr, 200, fp);
        if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0) {
            returnValue = 1;
        }
        if ((returnValue == 1) &&
            (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)) {
            number = tmpStr[strlen(tmpStr) - 3] - '0'; // event 번호 추출
            break;
        }
    }
    fclose(fp);
    if (returnValue == 1)
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
    return returnValue;
}

void* buttonThFunc(void* arg) {
    struct input_event stEvent;
    BUTTON_MSG_T msg;

    while (1) {
        int readSize = read(fd, &stEvent, sizeof(stEvent));
        if (readSize != sizeof(stEvent))
            continue;

        if (stEvent.type == EV_KEY) {
            msg.messageNum = 1;
            msg.keyInput = stEvent.code;
            msg.pressed = stEvent.value;
            msgsnd(msgID, &msg, sizeof(BUTTON_MSG_T) - sizeof(long int), 0);
        }
    }
    return NULL;
}

int buttonInit(void) {
    if (probeButtonPath(buttonPath) == 0)
        return 0;
    fd = open(buttonPath, O_RDONLY);
    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}

int buttonExit(void) {
    pthread_cancel(buttonTh_id);
    pthread_join(buttonTh_id, NULL);
    close(fd);
    msgctl(msgID, IPC_RMID, 0);
    return 0;
}
