#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>
#include <QString>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0);

    // Getter for real part
    double getReal() const;

    // Getter for imaginary part
    double getImag() const;

    // Magnitude of the complex number
    double magnitude() const;

    // Overload the > operator
    bool operator>(const Complex& other) const;

    // Method to get QString representation
    QString toQString() const;

    // Friend function to overload << for easy output
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif // COMPLEX_HPP
