#include <iostream>
#include <utility>
#include <list>
#include <windows.h>


//1_____Blue                                       10______Light Green
//2_____Green                                    11______Light Aqua
//3_____Aqua                                      12______Light Red
//4_____Red                                        13______Light Purple
//5_____Purple                                   14______Light Yellow
//6_____Yellow                                   15______Bright White
//7_____White
//8_____Gray
//9_____Light Blue
//0_____Black


HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //just once init to control console

class Component {
public:
  virtual void showPrice() {
    std::cout << "Base implementation showPrice!";
  }

  virtual double showTotalCost() {
    std::cout << "Base Implementation showTotalCost!";
    return 0.0;
  }
};

class Leaf : public Component {
private:
  std::string name;
  double price;
public:
  Leaf(std::string name, double price) : name(std::move(name)), price(price) {}

  void showPrice() override {
    SetConsoleTextAttribute(color, 12);
    std::cout << name << ", price=" << price << " eur" << std::endl;
  }

  double showTotalCost() override {
    return price;
  }

};

class Composite : public Component {
private:
  std::string name;
  std::list<Component *> listOfComponents;
public:
  explicit Composite(std::string name) : name(std::move(name)) {}

  void addComponent(Component *component) {
    listOfComponents.push_back(component);
  }

  void showPrice() override {

    SetConsoleTextAttribute(color, 2);
    std::cout << name << std::endl;
    for (Component *c: listOfComponents) {
      c->showPrice();
    }
  }

  // The function is an accessor that does not change any value of class members.
  double showTotalCost() override {
    double total = 0;
    for (Component *c: listOfComponents) {
      total += c->showTotalCost();
    }
    return total;
  }

};


int main() {


  auto *cpu = new Leaf("Intel i9 9540K", 700);
  auto *ram = new Leaf("Corsair X200 8GB", 300);
  auto *computer = new Composite("Computer");
  auto *motherboard = new Composite("Motherboard");

  computer->addComponent(motherboard);
  motherboard->addComponent(cpu);
  motherboard->addComponent(ram);
  motherboard->showPrice();
  SetConsoleTextAttribute(color, 1);
  std::cout << "Total cost: " << cpu->showTotalCost() << " eur" << std::endl;

  std::list<Component *> basket;
  basket.push_back(cpu);
  basket.push_back(cpu);
  basket.push_back(motherboard);

  double price = 0;
  for (Component *c: basket) {
    price += c->showTotalCost();
  }
  SetConsoleTextAttribute(color, 1);

  std::cout << "Price for Basket: " << price <<" eur" <<std::endl;

  return 0;
}
