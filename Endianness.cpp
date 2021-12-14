#include <stdio.h>

// 测试本机的字节序
int main(int argc, char* argv[]) {
	unsigned int x = 0x11223344; // 4字节无符号整型变量
	char* c = (char*)&x; // 取该整型变量存放内存的首地址（低地址）

	if (*c == 0x44)
		printf("Little Endian\n"); // 低地址   →   高地址
	else                           // 0x44 0x33 0x22 0x11
		printf("Big Endian\n"); // 低地址   →   高地址
								// 0x11 0x22 0x33 0x44
	return 0;
}
