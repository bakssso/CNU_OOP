#include <iostream>

template<typename T>

typename void ssswap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

/* ... (추가) template swap의 string type specialization ... */
template <>
typename void ssswap<std::string>
(std::string& a, std::string& b) {
	std ::string temp = a;
	a = b;
	b = temp;
}

int main() {
	int a = 1;
	int b = 2;
	float c = 3.3;
	float d = 4.4;
	std::string e = "World";
	std::string f = "Hello";

	ssswap<int>(a, b); //swap(a,b)도 가능
	ssswap<float>(c, d); //swap(c,d)도 가능

   //(추가) e, f의 swap이 가능하도록 swap template 호출
	ssswap<std::string>(e, f);


	std::cout << "a: " << a << ", b: " << b << std::endl;
	std::cout << "c: " << c << ", d: " << d << std::endl;
	std::cout << "e: " << e << ", f: " << f << std::endl;

	return 0;
}
