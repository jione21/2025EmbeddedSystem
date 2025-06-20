#include "textlcd.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <line1> [line2]\n", argv[0]);
        return 1;
    }

    if (!textLcdInit()) {
        fprintf(stderr, "LCD Init failed\n");
        return 1;
    }

    textLcdClear();

    // 첫 번째 줄 출력 및 알림
    textLcdWriteLine(1, argv[1]);
    printf("LCD Line 1: \"%s\"\n", argv[1]);

    // 두 번째 줄이 있으면 출력 및 알림
    if (argc >= 3) {
        textLcdWriteLine(2, argv[2]);
        printf("LCD Line 2: \"%s\"\n", argv[2]);
    }

    return 0;
}
