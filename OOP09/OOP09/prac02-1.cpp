#include <vector>
#include <string>
#include <iostream>

class Base1 {
public:
	Base1(int n) : vector_(n, 3) {
	}
	//.....
private:
	std::vector<char> vector_;
};

class Base2 {
public:
	Base2(int n) : vector_(n, 3) {
	}
	//.....
private:
	std::vector<char> vector_;
};

class Derived : public  Base2, Base1 {
public:
	Derived(const std::string& str) : Base1(512), Base2(1024)
	{
		i = 0;
	}
	// ...
private:
	std::string str_;
	int i = 0;
};
int main() {
	Derived drv("1");
	return 0;
}
