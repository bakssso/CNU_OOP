#include <iostream>
#include <string.h>
#pragma warning(disable:4996)

class Animal {
public:
	char* name;
	int age;

	Animal(int age_, const char* name_) {
		age = age_;
		name = new char[strlen(name_) + 1];
		strcpy(name, name_);
	}

	Animal(Animal& a) { //복사 생성자
		age = a.age;
		name = name;
	}

	void changeName(const char* newName) {
		strcpy(name, newName);
	}
	void printAnimal() {
		std::cout << "Name: " << name << " Age: "
			<< age << std::endl;
	}
};

int main() {
	Animal A(10, "Jenny"); //10살 Jenny 생성
	Animal B = A; // 10살 Jenny인 A를 B에게 복사
	A.age = 22;		//A의 나이를 22살로 바꿈
	//char* brown = "Brown";
	A.changeName("Brown"); //A의 이름을 Brown으로 바꿈

	A.printAnimal();
	B.printAnimal();
	return 0;
}
