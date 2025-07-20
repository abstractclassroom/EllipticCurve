#include "ECurvePoint.hpp"


// Private constructor for infinity point
EllipticCurve::Point::Point(bool inf, const EllipticCurve* c)
    : x(FieldElement(0, c->field_)), y(FieldElement(0, c->field_)), isInfinity(inf), curve(c) {}



// Point operations
EllipticCurve::Point::Point(const FieldElement& x_, const FieldElement& y_, const EllipticCurve* c)
    : x(x_), y(y_), curve(c), isInfinity(false) {}

EllipticCurve::Point EllipticCurve::Point::operator+(const Point& other) const {
    if (isInfinity) return other;
    if (other.isInfinity) return *this;

    const auto& p = *curve;

    if (x == other.x && y != other.y) return Point(true, curve);

    FieldElement s = (x == other.x && y == other.y)
        ? (FieldElement(3, curve->field_) * x * x + curve->a_) / (FieldElement(2, curve->field_) * y)
        : (other.y - y) / (other.x - x);

    FieldElement x3 = s * s - x - other.x;
    FieldElement y3 = s * (x - x3) - y;
    return Point(x3, y3, curve);
}

EllipticCurve::Point& EllipticCurve::Point::operator+=(const Point& other) {
    *this = *this + other;
    return *this;
}

bool EllipticCurve::Point::operator==(const Point& other) const {
    if (isInfinity && other.isInfinity) return true;
    if (isInfinity != other.isInfinity) return false;

    return x == other.x &&
           y == other.y &&
           curve->getAParameter() == other.curve->getAParameter() &&
           curve->getBParameter() == other.curve->getBParameter() &&
           curve->getPrime() == other.curve->getPrime();
}

bool EllipticCurve::Point::operator!=(const Point& other) const {
    return !(*this == other);
}

EllipticCurve::Point EllipticCurve::Point::scalarMultiply(const Integer& k) const {
    Point result(true, curve);   //infinity point
    Point addend = *this;
    Integer n = k;

    while (n != Integer(0)) {
        if ((n & Integer(1)) != Integer(0)) {
            result += addend;
        }
        addend += addend;  // Double the point
        n >>= 1;           // Move to next bit
    }

    return result;
}

EllipticCurve::Point EllipticCurve::Point::scalarMultiply(const FieldElement& k) const {
    return scalarMultiply(k.value);
}



