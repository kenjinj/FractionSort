/*
* File:   fraction.cpp
* Author: Kenji
*
* Created on September 6, 2014, 10:07 PM
*/

#include <cstdlib>
#include <cstdio>
#include <limits>
#include "fraction.h"

using namespace std;

fraction::fraction(){
    num = 0;
    denom = 0;
    valid = false;
}

fraction::fraction(int n, unsigned d)
{
    num = n;
    denom = d;
    // reduce
    int x = fraction::gcd(abs(n), d);
    num = n/x;
    denom = d/x;
    valid = checkValid();
}

fraction::fraction(int w, unsigned n, unsigned d) {
    int numSigned = (int)n;
    if (w > 0) numSigned += (w * d);
    else if (w < 0) numSigned = (w * d) - numSigned;
    // reduce
    int x = fraction::gcd(abs(numSigned), d);
    num = numSigned/x;
    denom = d/x;
    valid = checkValid();
}

fraction::fraction(float n) {
    unsigned precision = 10000;
    // get whole number
    int whole = (int)n;
    // get numerator
    float real;
    (whole < 0) ? (real = -1*n + whole) : (real = n - whole);
    unsigned uNum = (unsigned)(real * precision);
    fraction f = fraction(whole, uNum, precision);
    num = f.num;
    denom = f.denom;
    valid = checkValid();
}

bool fraction::Valid() const{
    return valid;
}

int fraction::Whole() const{
    return (num/(int)denom);
}

int fraction::Numerator() const{
    return (num%(int)denom);
}

unsigned fraction::Denominator() const{
    return denom;
}

bool fraction::operator==(const fraction& rhs) const{
    if ((num * (int)rhs.denom) == ((int)denom * rhs.num)) return true;
    return false;
}

bool fraction::operator!=(const fraction& rhs) const{
    if ((num * (int)rhs.denom) != ((int)denom * rhs.num)) return true;
    return false;
}

bool fraction::operator< (const fraction& rhs) const{
    if ((num * (int)rhs.denom) < ((int)denom * rhs.num)) return true;
    return false;
}

bool fraction::operator<=(const fraction& rhs) const{
    if ((num * (int)rhs.denom) <= ((int)denom * rhs.num)) return true;
    return false;
}

bool fraction::operator>(const fraction& rhs) const{
    if ((num * (int)rhs.denom) > ((int)denom * rhs.num)) return true;
    return false;
}

bool fraction::operator>=(const fraction& rhs) const{
    if ((num * (int)rhs.denom) >= ((int)denom * rhs.num)) return true;
    return false;
}

fraction fraction::operator+(const fraction& rhs) const{
    int numT = num * rhs.denom;
    numT += rhs.num * denom;
    unsigned denomT = denom * rhs.denom;

    int x = fraction::gcd(abs(numT), denomT);
    numT = numT / x;
    denomT = denomT / x;
    fraction sum = fraction(numT, denomT);
    return sum;
}

fraction fraction::operator-(const fraction& rhs) const{
    int numT = num * rhs.denom;
    numT -= rhs.num * denom;
    unsigned denomT = denom * rhs.denom;

    int x = fraction::gcd(abs(numT), denomT);
    numT = numT / x;
    denomT = denomT / x;
    fraction diff = fraction(numT, denomT);
    return diff;
}

fraction fraction::operator*(const fraction& rhs) const{
    fraction prod;
    if (rhs.num != 0){
        int numT = num * rhs.num;
        unsigned denomT = denom * rhs.denom;

        int x = fraction::gcd(abs(numT), denomT);
        numT = numT / x;
        denomT = denomT / x;
        prod = fraction(numT, denomT);
    }
    else{
        prod = fraction(0,1);
    }
    return prod;
}

fraction fraction::operator/(const fraction& rhs) const{
    if (rhs.num != 0)
    {
        int numT = num * rhs.denom;
        int denomT = (int)denom * rhs.num;
        if(numT < 0 ^ denomT < 0){
            if(numT > 0)
            {
                numT *= -1;
                denomT *= -1;
            }
        }
        else if(numT < 0 && denomT < 0){
            numT *= -1;
            denomT *= -1;
        }
        int x = fraction::gcd(abs(numT), denomT);
        numT = numT / x;
        denomT = denomT / x;
        fraction quot = fraction(numT, (unsigned)denomT);
        return quot;
    }
    return *this;
}

fraction fraction::operator+=(const fraction& rhs) {
    num = num * rhs.denom;
    num += rhs.num * denom;
    denom = denom * rhs.denom;

    int x = fraction::gcd(abs(num), denom);
    num = num / x;
    denom = denom / x;
    
    valid = checkValid();
    return *this;
}

fraction fraction::operator-=(const fraction& rhs) {
    num = num * rhs.denom;
    num -= rhs.num * denom;
    denom = denom * rhs.denom;

    int x = fraction::gcd(abs(num), denom);
    num = num / x;
    denom = denom / x;
    
    valid = checkValid();
    return *this;
}

fraction fraction::operator*=(const fraction& rhs) {
    if (valid){
        num *= rhs.num;
        denom *= rhs.denom;

        int x = fraction::gcd(abs(num), denom);
        num = num / x;
        denom = denom / x;
        valid = checkValid();
    }
    else if (rhs.num == 0){
        num = 0;
        denom = 1;
        valid = true;
    }
    return *this;
}

fraction fraction::operator/=(const fraction& rhs){
    if (rhs.num != 0)
    {
        num *= rhs.denom;
        int denomT = (int)denom * rhs.num;

        if(num < 0 ^ denomT < 0){
            if(num > 0)
            {
                num *= -1;
                denomT *= -1;
            }
        }
        else if(num < 0 && denomT < 0){
            num *= -1;
            denomT *= -1;
        }
        denom = (unsigned)denomT;
        valid =  checkValid();
        if (valid){
            int x = fraction::gcd(abs(num), denomT);
            num = num / x;
            denomT = denomT / x;

            denom = (unsigned)denomT;
        }
        else
            denom = (unsigned)denomT;
    }
    return *this;
}

istream& operator>>(istream &is, fraction &obj) {
    int wholeTemp = 0;
    int numTemp = 0;
    int denomTemp = 0;

    char line[20];
    is >> line;

    scanf(line, "%d %d/%d", &wholeTemp, &numTemp, &denomTemp);
    fraction* temp = new fraction(wholeTemp, numTemp, denomTemp);
    obj.num = temp->num;
    obj.denom = temp->denom;
    obj.valid = temp->valid;
    delete temp;
    return is;
}

ostream& operator<<(ostream& os, const fraction& obj) {
    if (obj.valid)
    {
        int w, n, d;
        d = obj.denom;
        w = obj.num / d;
        n = obj.num % d;
        if (w < 0) n *= -1;
        if (n == 0) d = 1;
        os << w << " " << n << "/" << d;
    }
    else
        os << "[Cannot print invalid fraction (" << obj.num << "/" << obj.denom << ")]";
    return os;
}

/*                      *
 *                      *
 *  PRIVATE FUNCTIONS   *
 *                      *
 *                      */

// Euclid's algorithm
int fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool fraction::checkValid(){
    if((int)denom <= 0){
        denom = 1;
        return false;
    }
    if(num >= numeric_limits<int>::max()-1 || num <= numeric_limits<int>::min()+1)
        return false;
    if(denom >= numeric_limits<unsigned int>::max()-1)
        return false;
    return true;
}
