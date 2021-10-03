#include <iostream>

void increment(int &ref) {
	ref += 1;
}
int main() {

	int x = 55;
	int &ref = x;

	std::cout << "Before increment: " << x << std::endl;
	increment(ref);
	std::cout << "After increment: " << ref << std::endl;

	system("pause");
	return 0;
}