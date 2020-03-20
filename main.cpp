#include <iostream>
#include <utility>
#include <list>

class Component {
public:
  virtual void showPrice() {
    std::cout << "Base implementation!";
  }
};

class Leaf : public Component {
private:
  std::string name;
  double price;
public:
  Leaf(std::string name, double price) : name(std::move(name)), price(price) {}

  void showPrice() override {
    std::cout << name << ", price=" << price;
  }
};

class Composite : public Component {
private:
  std::string name;
  std::list<Component*> listOfComponents;
public:
  explicit Composite(std::string name) : name(std::move(name)) {}
  void addComponent(Component *component){
    listOfComponents.push_back(component);
  }
  void showPrice() override {
    std::cout << name << std::endl;
    for(Component *c: listOfComponents){
      c->showPrice();
    }
  }
};


int main() {
  Component *cpu = new Leaf("Intel i9 9540K", 700);
  Component *ram = new Leaf("Corsair X200 8GB", 300);

  Composite motherboard("ASUS X75E TITAN");

  motherboard.addComponent(cpu);
  motherboard.addComponent(ram);


  motherboard.showPrice();


  return 0;
}
