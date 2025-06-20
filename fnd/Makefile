# 최종 실행파일명
TARGET = fndtest

# 크로스 컴파일러 설정
CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

# 라이브러리 및 오브젝트
LIB = libMyPeri.a
OBJ = led.o button.o buzzer.o fnd.o

# 기본 타겟
all: $(TARGET)

# 라이브러리 생성
$(LIB): $(OBJ)
	$(AR) rc $(LIB) $(OBJ)

# 오브젝트 파일 만들기
led.o: led.c led.h
	$(CC) -c led.c -o led.o

button.o: button.c button.h
	$(CC) -c button.c -o button.o

buzzer.o: buzzer.c buzzer.h
	$(CC) -c buzzer.c -o buzzer.o

fnd.o: fnd.c fnd.h
	$(CC) -c fnd.c -o fnd.o

$(TARGET): fndtest.c $(LIB)
	$(CC) fndtest.c -L. -lMyPeri -o $(TARGET)

# 정리
clean:
	rm -f *.o *.a $(TARGET)
