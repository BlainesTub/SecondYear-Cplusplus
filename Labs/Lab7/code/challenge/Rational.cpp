//
// Created by khaled Kelany on 2020-11-01.
//

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <set>

class Rational {
public:
    /*
     * Construct a zero rational number.
     * This constructor is fully implemented.
     */
    Rational() {
        Rational(0, 1);
    }

    /*
     * Copy the initial value of the numerator and denominator
     * If the denominator value is zero, throw std::runtime_error exception
     */
    Rational(int n, int d) {
            numerator = n;
            denominator = d;

            if(denominator == 0) throw std::runtime_error("Denominator is 0");
        reduce();
    };

    /*
     * Reduce the fraction by diving by GCD. Make sure to call this function after each mathematical operation to make
     * the fraction stored in the reduced form.
     */
    void reduce() {
        int gcd = 1;
        std::set<int> numerGCDs;
        std::set<int> denomGCDs;

        //Find Divisors for nom and demon
        for(int i=1; i< numerator; ++i){
            if(numerator % i ==0) numerGCDs.insert(i);
        }
        for(int i=1; i< denominator; ++i){
            if(denominator % i ==0) denomGCDs.insert(i);
        }

        //Compare divisors. Grab biggest one
        for(auto n : numerGCDs){
            for(auto d : denomGCDs){
                if(n==d) gcd = n;
            }
        }

        //Reduce! Reuse, Recycle!
        numerator = numerator/gcd;
        denominator = denominator/gcd;

    }

    /*
     * Adding two rational numbers.
     */
    Rational operator+(const Rational &a) const {
        Rational sum;

        
        int aNumer = a.numerator;
        int aDenom = a.denominator;

        int newNumerator = numerator*a.denominator;
        int newDenominator = denominator*a.numerator;  

        aNumer = a.numerator*denominator;
        aDenom = a.denominator*numerator;

        sum.numerator = aNumer + newNumerator;
        sum.denominator = newDenominator;
        sum.reduce();
        return sum;
    }

    /*
     * Adding integer to rational number.
     */
    Rational operator+(const int i) const {
        Rational sum;
        int whole = i*denominator;
        int top = whole + numerator;

        sum.numerator = top;
        sum.denominator = denominator;

        sum.reduce();

        return sum;
        


    }

    /*
     * Subtracting two rational numbers.
     */
    Rational operator-(const Rational &a) const {
        Rational sum;
        int aNumer = a.numerator;
        int aDenom = a.denominator;

        int newNumerator = numerator*aDenom;
        int newDenominator = denominator*aNumer;  

        aNumer = aNumer*denominator;
        aDenom = aDenom*numerator;

        sum.numerator = aNumer - newNumerator;
        sum.denominator = aDenom;
        sum.reduce();
        return sum;


    }

    /*
     * Subtracting integer from rational number.
     */
    Rational operator-(const int i) const {

        Rational sum;
        int whole = i*denominator;
        int top = numerator - whole;

        sum.numerator = top;
        sum.denominator = denominator;

        sum.reduce();

        return sum;
        

    }

    /*
     * Multiplying two rational numbers.
     */
    Rational operator*(const Rational &a) const {
        Rational multiplied;
        multiplied.numerator = numerator*a.numerator;
        multiplied.denominator = denominator*a.denominator;
        
        multiplied.reduce();
        return multiplied;

    }

    /*
     * Multiplying integer by rational number.
     */
    Rational operator*(const int i) const {
        Rational multiplied;
        multiplied.numerator = numerator*i;
        multiplied.denominator = denominator;

        multiplied.reduce();
        return multiplied;

    }

    /*
     * Dividing two rational numbers.
     * If dividing by zero, throw a std::runtime_error exception.
     */
    Rational operator/(const Rational &a) const {
        if(a.numerator ==0) throw std::runtime_error("divide b 0");
        Rational divided;
        divided.numerator = numerator*a.denominator;
        divided.denominator = denominator*a.numerator;

        divided.reduce();
        return divided;
    }

    /*
     * Dividing rational numbers by integer.
     * If dividing by zero, throw a std::runtime_error exception.
     */
    Rational operator/(const int i) const {
        if(i==0) throw std::runtime_error("Cannot divide by 0");
        Rational divided;
        divided.numerator = numerator;
        divided.denominator = denominator*i;
        divided.reduce();

 

        return divided;
    }

    /*
     * Print the rational number in the form of a/b.
     */
    void printRational() {
        std::cout << numerator << "/" << denominator << std::endl;
    }

    /*
     * Numerator getter.
     */
    int getNumerator() const {
        return numerator;
    }

    /*
     * Denominator getter.
     */
    int getDenominator() const {
        return denominator;
    }

private:
    int numerator{};
    int denominator{};
};

void evaluate_exception(std::function<void()> test) {
    static std::string fail{"FAIL\n"};
    static std::string pass{"PASS\n"};

    try {
        test();
        std::cout << fail;
    } catch (std::runtime_error &e) {
        std::cout << pass;
    }
}

void evaluate_test(bool result) {
    static std::string fail{"FAIL\n"};
    static std::string pass{"PASS\n"};

    if (result) {
        std::cout << pass;
    } else {
        std::cout << fail;
    }
}

int main() {
    Rational default_rational{};
    Rational zero_rational{0, 1};
    Rational rational1{5, 7};
    Rational rational2{110, 30};

    std::cout << "Testing Exceptions\n";

    std::cout << "\tZero denominator: ";
    evaluate_exception([&]() { Rational{5, 0}; });

    std::cout << "\tDividing by zero fraction: ";
    evaluate_exception([&]() { rational1 / zero_rational; });

    std::cout << "\tDividing by zero integer: ";
    evaluate_exception([&]() { rational1 / 0; });

    std::cout << "\nTesting Functions\n";

    std::cout << "\tAdding 110/30 to 5/7: ";
    default_rational = rational1 + rational2;
    evaluate_test(default_rational.getNumerator() == 92 && default_rational.getDenominator() == 21);

    std::cout << "\tSubtracting 110/30 from 5/7: ";
    default_rational = rational1 - rational2;
    evaluate_test(default_rational.getNumerator() == -62 && default_rational.getDenominator() == 21);

    std::cout << "\tMultiplying 5/7 by 110/30: ";
    default_rational = rational1 * rational2;
    evaluate_test(default_rational.getNumerator() == 55 && default_rational.getDenominator() == 21);

    std::cout << "\tDividing 5/7 by 110/30: ";
    default_rational = rational1 / rational2;
    evaluate_test(default_rational.getNumerator() == 15 && default_rational.getDenominator() == 77);

    std::cout << "\tAdding 3 to 5/7: ";
    default_rational = rational1 + 3;
    evaluate_test(default_rational.getNumerator() == 26 && default_rational.getDenominator() == 7);

    std::cout << "\tSubtracting 3 from 5/7: ";
    default_rational = rational1 - 3;
    evaluate_test(default_rational.getNumerator() == -16 && default_rational.getDenominator() == 7);

    std::cout << "\tMultiplying 5/7 by 3: ";
    default_rational = rational1 * 3;
    evaluate_test(default_rational.getNumerator() == 15 && default_rational.getDenominator() == 7);

    std::cout << "\tDividing 5/7 by 3: ";
    default_rational = rational1 / 3;
    evaluate_test(default_rational.getNumerator() == 5 && default_rational.getDenominator() == 21);

    return 0;
}