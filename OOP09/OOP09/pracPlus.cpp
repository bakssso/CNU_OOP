#include <iostream>

class Shape {
public:
	virtual void draw() {};
};

class RoundedRectangle : public Shape {
public :
	void draw() override {
		std::cout << "Inside RoundedRectangle::draw() method." << std::endl;
	}
};

class RoundedSquare : public Shape {
public:
	void draw() override {
		std::cout << "Inside RoundedSquare::draw() method." << std::endl;
	}
};

class Rectangle : public Shape {
public:
	void draw() override {
		std::cout << "Inside Rectangle::draw() method." << std::endl;
	}
};

class Square : public Shape {
public:
	virtual void draw() {
		std::cout << "Inside Square::draw() method." << std::endl;
	}
};


class AbstractFactory {
public:
	virtual Shape* getShape(std::string shapeType) = 0;
};

class ShapeFactory : public AbstractFactory {
public:
	virtual Shape* getShape(std::string shapeType) override {
		if (shapeType == "RECTANGLE") {
			return new RoundedRectangle();
		}
		else if (shapeType == "SQUARE") {
			return new RoundedSquare();
		}
		return NULL;
	}
};

class RoundedShapeFactory : public AbstractFactory {
public:
	virtual Shape* getShape(std::string shapeType) override {
		if (shapeType == "RECTANGLE") {
			return new RoundedRectangle();
		}
		else if (shapeType == "SQUARE") {
			return new RoundedSquare();
		}
		return NULL;
	}
};

class FactoryProducer {
public:
	AbstractFactory* getFactory(bool rounded) {
		if (rounded) {
			return new RoundedShapeFactory();
		}
		else {
			return new ShapeFactory();
		}
	}
};

int main() {
	FactoryProducer* FP = new FactoryProducer();
	AbstractFactory* shapeFactory = FP->getFactory(false);
	Shape* shape1 = shapeFactory->getShape("RECTANGLE");
	shape1->draw();
	Shape* shape2 = shapeFactory->getShape("SQUARE");
	shape2->draw();

	FactoryProducer* FP2 = new FactoryProducer();
	AbstractFactory* shapeFactory2 = FP2->getFactory(true);
	Shape* shape3 = shapeFactory2->getShape("RECTANGLE");
	shape3->draw();
	Shape* shape4 = shapeFactory2->getShape("SQUARE");
	shape4->draw();
}