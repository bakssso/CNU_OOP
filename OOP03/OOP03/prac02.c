#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

int main() {
	char s[100];

	printf("���ڸ� �Է��ϼ���(100�� �̳�). : ");
	scanf_s("%s", s, sizeof(s));

	printf("�Էµ� ���ڴ� %s �Դϴ�.\n", s);

	return 0;
}
