#ifndef ELLIPTIC_CURVE_HPP
#define ELLIPTIC_CURVE_HPP

#include "FiniteField.hpp"
#include <iostream>
#include <string>

class EllipticCurve {
public:
    using FieldElement = FiniteField::FieldElement;

    class Point {
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

    };

EllipticCurve(const FieldElement& a,const FieldElement& b);


    Point createPoint(const FieldElement& x, const FieldElement& y) const;
    bool is_on_curve(const Point& P) const;
    std::string toString() const;

    // Getters
    const FieldElement& a() const;
    const FieldElement& b() const;
    const Integer& p() const;

private:
    const FiniteField* field_;
    FieldElement a_, b_;
};

#endif // ELLIPTIC_CURVE_HPP
