#ifndef ECurvePoint_HPP
#define ECurvePoint_HPP

#include "FiniteField.hpp"
#include "ECurve.hpp"
#include <iostream>

class EllipticCurve::Point {
public:
    FieldElement x, y;
    const EllipticCurve* curve;
    bool isInfinity;

    Point(const FieldElement& x_, const FieldElement& y_, const EllipticCurve* c);
    Point(bool inf, const EllipticCurve* c); // Constructor for point at infinity
    Point(const EllipticCurve* c);           // Default infinity point constructor

    Point operator+(const Point& other) const;
    Point& operator+=(const Point& other);
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    Point scalarMultiply(const Integer& k) const;
    Point scalarMultiply(const FieldElement& k) const;

};

#endif // ECurvePoint_HPP
