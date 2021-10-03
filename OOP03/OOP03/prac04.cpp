#include <iostream>

void increment(int* ptr) {
	*ptr += 1;
}
int main() {

	int x = 55;
	int* ptr = &x;
	
	std::cout << "Before increment: " << x << std::endl;
	increment(ptr);
	std::cout << "After increment: " << *ptr << std::endl;

	system("pause");
	return 0;
}