#include  "pure_class.h"

using grammer::pure_class::Circle;
using grammer::pure_class::Rectangle;
using grammer::pure_class::IShape;

int main() {

    std::unique_ptr<IShape> c = std::make_unique<Circle>(3);
    std::unique_ptr<IShape> r = std::make_unique<Rectangle>(2, 3);
    c->ZhouChang();
    std::cout << c->GetArea() << std::endl;;
    r->ZhouChang();
    std::cout << r->GetArea() << std::endl;;
    return 0;
}
