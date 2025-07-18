#include "EllipticCurve.hpp"

// EllipticCurve constructor
EllipticCurve::EllipticCurve(const FieldElement& a, const FieldElement& b, const Point& generator)
    : a_(a), b_(b), generator_(generator) {
    generator_.curve = this;
}

// Check if a point lies on the curve
bool EllipticCurve::is_on_curve(const Point& P) const {
    if (P.isInfinity) return true;
    return (P.y * P.y) == (P.x * P.x * P.x + a_ * P.x + b_);
}

// Point addition
EllipticCurve::Point EllipticCurve::Point::operator+(const Point& other) const {
    if (isInfinity) return other;
    if (other.isInfinity) return *this;
    if (x == other.x && y != other.y) return Point();

    FieldElement m;
    if (*this == other) {
        if (y == FieldElement(0)) return Point();
        m = (FieldElement(3) * x * x + curve->a()) / (FieldElement(2) * y);
    } else {
        m = (other.y - y) / (other.x - x);
    }

    FieldElement x3 = m * m - x - other.x;
    FieldElement y3 = m * (x - x3) - y;
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

std::ostream& operator<<(std::ostream& os, const EllipticCurve::Point& p) {
    if (p.isInfinity) {
        os << "Point(infinity)";
    } else {
        os << "Point(" << p.x << ", " << p.y << ")";
    }
    return os;
}
