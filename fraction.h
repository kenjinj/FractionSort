#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

using namespace std;

class fraction {
public:
    fraction();
    fraction(int n, unsigned d);
    fraction(int w, unsigned n, unsigned d);
    fraction(float n);
    bool Valid() const;
    int Whole() const;
    int Numerator() const;
    unsigned Denominator() const;
    bool operator==(const fraction& rhs) const;
    bool operator!=(const fraction& rhs) const;
    bool operator<(const fraction& rhs) const;
    bool operator<=(const fraction& rhs) const;
    bool operator>(const fraction& rhs) const;
    bool operator>=(const fraction& rhs) const;
    fraction operator+(const fraction& rhs) const;
    fraction operator-(const fraction& rhs) const;
    fraction operator*(const fraction& rhs) const;
    fraction operator/(const fraction& rhs) const;
    fraction operator+=(const fraction& rhs);
    fraction operator-=(const fraction& rhs);
    fraction operator*=(const fraction& rhs);
    fraction operator/=(const fraction& rhs);
    friend istream& operator>>(istream& is, fraction& obj);
    friend ostream& operator<<(ostream& os, const fraction& obj);
private:
    static int gcd(int a, int b);
    bool checkValid();
    int num;
    unsigned denom;
    bool valid;
};

#endif
