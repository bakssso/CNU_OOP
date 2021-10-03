#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

int main() {
	char s[100];

	printf("문자를 입력하세요(100자 이내). : ");
	scanf_s("%s", s, sizeof(s));

	printf("입력된 문자는 %s 입니다.\n", s);

	return 0;
}
