#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>
#include "complex.hpp"

// General template function
template <typename T>
QString toQString(const T& value) {
    return QString::number(value);
}

// Template specialization for Complex type
template <>
QString toQString<Complex>(const Complex& value) {
    return value.toQString();
}
template <>
QString toQString<std::string>(const std::string& value) {
    return QString::fromStdString(value);
}

// Template specialization for const char* type
template <>
QString toQString<const char*>(const char* const& value) {
    return QString(value);
}

#endif // UTILS_HPP
