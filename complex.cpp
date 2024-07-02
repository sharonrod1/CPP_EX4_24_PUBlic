#include "complex.hpp"

// Constructor
Complex::Complex(double r, double i) : real(r), imag(i) {}

// Getter for real part
double Complex::getReal() const {
    return real;
}

// Getter for imaginary part
double Complex::getImag() const {
    return imag;
}

// Magnitude of the complex number
double Complex::magnitude() const {
    return std::sqrt(real * real + imag * imag);
}

// Overload the > operator
bool Complex::operator>(const Complex& other) const {
    return this->magnitude() > other.magnitude();
}

// Method to get QString representation
QString Complex::toQString() const {
    return QString::number(real) + " + " + QString::number(imag) + "i";
}

// Overload << operator for output
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}
