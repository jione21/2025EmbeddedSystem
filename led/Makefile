# 최종 실행파일명
TARGET = ledtest

# 크로스 컴파일러 설정
CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

# 라이브러리 및 오브젝트
LIB = libMyPeri.a
OBJ = led.o
SRC = led.c led.h ledtest.c

all: $(TARGET)

# 라이브러리 생성
$(LIB): $(OBJ)
	$(AR) rc $(LIB) $(OBJ)

# 오브젝트 파일 만들기
led.o: led.c led.h
	$(CC) -c led.c -o led.o

# 실행파일 만들기 (라이브러리 링크)
$(TARGET): ledtest.c $(LIB)
	$(CC) ledtest.c -L. -lMyPeri -o $(TARGET)

clean:
	rm -f *.o *.a $(TARGET)
