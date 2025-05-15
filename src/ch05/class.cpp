// C++20 Classes Demonstration
// This file demonstrates key concepts from the material on C++ classes

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <stdexcept>
#include <initializer_list>

// ==========================================
// PART 1: CONCRETE TYPES
// ==========================================

// 1.1 An Arithmetic Type Example - Complex Number Class
class Complex {
private:
    double re, im;  // representation: two doubles

public:
    // Constructors
    Complex(double r, double i) : re{r}, im{i} {}           // construct from two scalars
    Complex(double r) : re{r}, im{0} {}                     // construct from one scalar
    Complex() : re{0}, im{0} {}                             // default complex: {0,0}
    Complex(const Complex& z) : re{z.re}, im{z.im} {}       // copy constructor

    // Accessors
    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }

    // Operators
    Complex& operator+=(const Complex& z) {
        re += z.re;
        im += z.im;
        return *this;
    }

    Complex& operator-=(const Complex& z) {
        re -= z.re;
        im -= z.im;
        return *this;
    }

    // Multiplication and division would be defined here
};

// Non-member operators for Complex
Complex operator+(Complex a, const Complex& b) {
    return a += b;  // Use already defined += and return the result
}

Complex operator-(Complex a, const Complex& b) {
    return a -= b;  // Use already defined -= and return the result
}

Complex operator-(Complex a) {
    return {-a.real(), -a.imag()};  // Unary minus
}

bool operator==(const Complex& a, const Complex& b) {
    return a.real() == b.real() && a.imag() == b.imag();
}

bool operator!=(const Complex& a, const Complex& b) {
    return !(a == b);
}

// 1.2 A Container Example - Vector class with RAII
class Vector {
private:
    double* elem;  // pointer to elements
    int sz;        // size

public:
    // Default constructor
    Vector() : elem{nullptr}, sz{0} {}
    
    // Constructor (acquires resources)
    Vector(int s) : elem{new double[s]}, sz{s} {
        for (int i = 0; i != s; ++i)
            elem[i] = 0;  // Initialize elements
    }

    // Destructor (releases resources)
    ~Vector() {
        delete[] elem;  // Free memory
    }

    // Copy constructor
    Vector(const Vector& other) : elem{new double[other.sz]}, sz{other.sz} {
        for (int i = 0; i != sz; ++i)
            elem[i] = other.elem[i];
    }

    // Copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            double* p = new double[other.sz];
            for (int i = 0; i != other.sz; ++i)
                p[i] = other.elem[i];
            delete[] elem;
            elem = p;
            sz = other.sz;
        }
        return *this;
    }

    // Move constructor (C++11 and later)
    Vector(Vector&& other) noexcept : elem{other.elem}, sz{other.sz} {
        other.elem = nullptr;
        other.sz = 0;
    }

    // Move assignment (C++11 and later)
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] elem;
            elem = other.elem;
            sz = other.sz;
            other.elem = nullptr;
            other.sz = 0;
        }
        return *this;
    }

    // Initializer list constructor
    Vector(std::initializer_list<double> lst)
        : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
        std::copy(lst.begin(), lst.end(), elem);  // Copy from lst into elem
    }

    // Add element at the end
    void push_back(double d) {
        double* p = new double[sz + 1];
        for (int i = 0; i != sz; ++i)
            p[i] = elem[i];
        p[sz] = d;
        delete[] elem;
        elem = p;
        ++sz;
    }

    // Access functions
    double& operator[](int i) {
        if (i < 0 || i >= sz) throw std::out_of_range("Vector::operator[]");
        return elem[i];
    }

    const double& operator[](int i) const {
        if (i < 0 || i >= sz) throw std::out_of_range("Vector::operator[]");
        return elem[i];
    }

    int size() const { return sz; }
};

// Function to read values into a Vector
Vector read(std::istream& is) {
    Vector v;
    for (double d; is >> d;)
        v.push_back(d);
    return v;  // Return by value (move semantics make this efficient)
}

// ==========================================
// PART 2: ABSTRACT TYPES
// ==========================================

// 2.1 Abstract Container Interface
class Container {
public:
    virtual double& operator[](int) = 0;           // Pure virtual function
    virtual int size() const = 0;                  // Pure virtual function
    virtual ~Container() {}                        // Virtual destructor
};

// 2.2 Vector_container implementation using Vector
class Vector_container : public Container {
private:
    Vector v;

public:
    Vector_container(int s) : v(s) {}
    Vector_container(std::initializer_list<double> il) : v(il) {}
    ~Vector_container() override {}

    double& operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }
};

// 2.3 List_container implementation using std::list
class List_container : public Container {
private:
    std::list<double> ld;  // Standard library list of doubles

public:
    List_container() = default;
    List_container(std::initializer_list<double> il) : ld{il} {}
    ~List_container() override {}

    double& operator[](int i) override {
        for (auto& x : ld) {
            if (i == 0) return x;
            --i;
        }
        throw std::out_of_range("List_container::operator[]");
    }

    int size() const override { return static_cast<int>(ld.size()); }
};

// Function that uses Container interface without knowing implementation
void use(Container& c) {
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        std::cout << c[i] << '\n';
}

// ==========================================
// PART 3: CLASS HIERARCHIES
// ==========================================

// 3.1 Shape class hierarchy
class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x{x}, y{y} {}
};

class Shape {
public:
    virtual Point center() const = 0;      // Pure virtual
    virtual void move(Point to) = 0;       // Pure virtual
    virtual void draw() const = 0;         // Pure virtual
    virtual void rotate(int angle) = 0;    // Pure virtual
    virtual ~Shape() {}                   // Virtual destructor
};

class Circle : public Shape {
private:
    Point p;   // Center
    int r;     // Radius

public:
    Circle(Point p, int r) : p{p}, r{r} {}

    Point center() const override { return p; }
    void move(Point to) override { p = to; }
    
    void draw() const override {
        std::cout << "Drawing Circle at (" << p.x << "," << p.y 
                  << ") with radius " << r << std::endl;
    }
    
    void rotate(int) override {
        // Circles remain the same when rotated
        std::cout << "Rotating a circle is a no-op" << std::endl;
    }
};

class Triangle : public Shape {
private:
    Point p1, p2, p3;  // Three vertices

public:
    Triangle(Point a, Point b, Point c) : p1{a}, p2{b}, p3{c} {}

    Point center() const override {
        return Point{(p1.x + p2.x + p3.x) / 3, (p1.y + p2.y + p3.y) / 3};
    }

    void move(Point to) override {
        Point c = center();
        int dx = to.x - c.x;
        int dy = to.y - c.y;
        
        p1.x += dx; p1.y += dy;
        p2.x += dx; p2.y += dy;
        p3.x += dx; p3.y += dy;
    }

    void draw() const override {
        std::cout << "Drawing Triangle with vertices at "
                  << "(" << p1.x << "," << p1.y << "), "
                  << "(" << p2.x << "," << p2.y << "), "
                  << "(" << p3.x << "," << p3.y << ")"
                  << std::endl;
    }

    void rotate(int angle) override {
        // Would implement actual rotation around the center
        std::cout << "Rotating Triangle by " << angle << " degrees" << std::endl;
    }
};

// 3.2 Extended hierarchy with Smiley
class Smiley : public Circle {
private:
    std::vector<std::unique_ptr<Shape>> eyes;  // Usually two eyes
    std::unique_ptr<Shape> mouth;              // A single mouth

public:
    Smiley(Point p, int r) : Circle{p, r} {}
    
    void add_eye(std::unique_ptr<Shape> s) {
        eyes.push_back(std::move(s));
    }
    
    void set_mouth(std::unique_ptr<Shape> s) {
        mouth = std::move(s);
    }
    
    void draw() const override {
        Circle::draw();  // Draw the face outline
        for (const auto& e : eyes) 
            e->draw();   // Draw the eyes
        if (mouth) 
            mouth->draw(); // Draw the mouth
    }
    
    void move(Point to) override {
        Point old_center = center();
        Circle::move(to);
        Point new_center = center();
        
        // Move all parts
        int dx = new_center.x - old_center.x;
        int dy = new_center.y - old_center.y;
        
        for (auto& e : eyes) {
            Point p = e->center();
            e->move(Point{p.x + dx, p.y + dy});
        }
        
        if (mouth) {
            Point p = mouth->center();
            mouth->move(Point{p.x + dx, p.y + dy});
        }
    }
    
    void rotate(int angle) override {
        // Rotate the eyes and mouth around the center
        std::cout << "Rotating Smiley by " << angle << " degrees" << std::endl;
        for (auto& e : eyes)
            e->rotate(angle);
        if (mouth)
            mouth->rotate(angle);
    }

    void wink(int i) {
        if (i >= 0 && i < static_cast<int>(eyes.size())) {
            std::cout << "Winking eye #" << i << std::endl;
            // Implementation would temporarily change the eye
        }
    }
};

// Function to safely work with Shapes using unique_ptr
void draw_all(const std::vector<std::unique_ptr<Shape>>& v) {
    for (const auto& p : v)
        p->draw();
}

void rotate_all(std::vector<std::unique_ptr<Shape>>& v, int angle) {
    for (auto& p : v)
        p->rotate(angle);
}

// Factory function that creates shapes based on input
enum class ShapeType { circle, triangle, smiley };

std::unique_ptr<Shape> create_shape(ShapeType type) {
    switch (type) {
        case ShapeType::circle:
            return std::make_unique<Circle>(Point{10, 10}, 20);
        
        case ShapeType::triangle:
            return std::make_unique<Triangle>(
                Point{0, 0}, Point{20, 0}, Point{10, 20});
        
        case ShapeType::smiley: {
            auto face = std::make_unique<Smiley>(Point{15, 15}, 30);
            
            // Add left eye
            face->add_eye(std::make_unique<Circle>(Point{8, 8}, 5));
            
            // Add right eye
            face->add_eye(std::make_unique<Circle>(Point{22, 8}, 5));
            
            // Add mouth
            face->set_mouth(std::make_unique<Triangle>(
                Point{10, 20}, Point{20, 20}, Point{15, 25}));
            
            return face;
        }
    }
    
    return nullptr;
}

// Main function to demonstrate concepts
int main() {
    std::cout << "==== CONCRETE TYPES DEMONSTRATION ====\n";
    
    // Complex numbers
    Complex a{1, 2};
    Complex b{3};
    Complex c = a + b;
    std::cout << "Complex number: " << c.real() << " + " << c.imag() << "i\n\n";
    
    // Vector
    Vector v1 = {1, 2, 3, 4, 5};
    for (int i = 0; i < v1.size(); ++i)
        std::cout << "v1[" << i << "] = " << v1[i] << '\n';
    std::cout << "\n";
    
    std::cout << "==== ABSTRACT TYPES DEMONSTRATION ====\n";
    
    // Container
    Vector_container vc = {10, 20, 30, 40, 50};
    List_container lc = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    std::cout << "Using Vector_container:\n";
    use(vc);
    
    std::cout << "\nUsing List_container:\n";
    use(lc);
    std::cout << "\n";
    
    std::cout << "==== CLASS HIERARCHIES DEMONSTRATION ====\n";
    
    // Create a collection of shapes
    std::vector<std::unique_ptr<Shape>> shapes;
    
    // Add different shapes
    shapes.push_back(create_shape(ShapeType::circle));
    shapes.push_back(create_shape(ShapeType::triangle));
    shapes.push_back(create_shape(ShapeType::smiley));
    
    // Draw all shapes
    std::cout << "Drawing all shapes:\n";
    draw_all(shapes);
    
    // Rotate all shapes
    std::cout << "\nRotating all shapes by 45 degrees:\n";
    rotate_all(shapes, 45);
    
    // Demonstrate dynamic_cast
    std::cout << "\nTesting shape types with dynamic_cast:\n";
    for (auto& shape : shapes) {
        if (auto* s = dynamic_cast<Smiley*>(shape.get())) {
            std::cout << "Found a Smiley. Making it wink...\n";
            s->wink(0);
        }
        else if (dynamic_cast<Circle*>(shape.get())) {
            std::cout << "Found a Circle.\n";
        }
        else if (dynamic_cast<Triangle*>(shape.get())) {
            std::cout << "Found a Triangle.\n";
        }
    }
    
    return 0;
}