#include "EllipticCurve.hpp"
#include <sstream>

// Constructor
EllipticCurve::EllipticCurve(const FieldElement& a, const FieldElement& b)
    : field_(a.field), a_(a), b_(b) {}

// Create a point using the curve
EllipticCurve::Point EllipticCurve::createPoint(const FieldElement& x, const FieldElement& y) const {
    Point p1(x, y, this);
    if (!is_on_curve(p1)) {
        throw std::invalid_argument("Point is not on the curve");
    }
    return p1;
}

// Check if point lies on the curve
bool EllipticCurve::is_on_curve(const Point& P) const {
    if (P.isInfinity) return true;
    const auto& x = P.x;
    const auto& y = P.y;
    return y * y == x * x * x + a_ * x + b_;
}


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
    if (isInfinity || other.isInfinity) return false;
    return x == other.x && y == other.y && curve == other.curve;
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


std::ostream& operator<<(std::ostream& os, const EllipticCurve::Point& p) {
    if (p.isInfinity) return os << "Point(infinity)";
    return os << "Point(" << p.x << ", " << p.y << ")";
}

std::string EllipticCurve::toString() const {
    std::ostringstream oss;
    oss << "y^2 = x^3 + " << a_ << "x + " << b_ << " over GF(" << field_->getPrime() << ")";
    return oss.str();
}

// Private constructor for infinity point
EllipticCurve::Point::Point(bool inf, const EllipticCurve* c)
    : x(FieldElement(0, c->field_)), y(FieldElement(0, c->field_)), isInfinity(inf), curve(c) {}

// Getters
const EllipticCurve::FieldElement& EllipticCurve::a() const { return a_; }
const EllipticCurve::FieldElement& EllipticCurve::b() const { return b_; }
const Integer& EllipticCurve::p() const { return field_->getPrime(); }
