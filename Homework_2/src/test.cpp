#include <iostream>
#include <cmath> // For pow function
using namespace std;

class Term {
    friend class Polynomial; // Allow Polynomial to access private members
private:
    float coef; // Coefficient
    int exp;    // Exponent
};

class Polynomial {
public:
    Polynomial();
    Polynomial Add(const Polynomial& poly) const;  // Add two polynomials
    Polynomial Mult(const Polynomial& poly) const; // Multiply two polynomials
    float Eval(float x) const; // Evaluate the polynomial at a given value
    friend istream& operator>>(istream& in, Polynomial& poly); // Overload >> for input
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // Overload << for output

private:
    Term* termArray; // Array of nonzero terms
    int capacity;    // Size of termArray
    int terms;       // Number of nonzero terms

    void AddTerm(float coef, int exp); // Add a single term to the polynomial
};

Polynomial::Polynomial() : termArray(nullptr), capacity(0), terms(0) {}

void Polynomial::AddTerm(float coef, int exp) {
    if (coef == 0) return; // Skip zero coefficients

    // Resize termArray if necessary
    if (terms == capacity) {
        capacity = (capacity == 0) ? 1 : 2 * capacity;
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            newArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newArray;
    }

    // Add the new term
    termArray[terms].coef = coef;
    termArray[terms].exp = exp;
    terms++;
}

Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    int i = 0, j = 0;

    while (i < this->terms && j < poly.terms) {
        if (this->termArray[i].exp == poly.termArray[j].exp) {
            float newCoef = this->termArray[i].coef + poly.termArray[j].coef;
            if (newCoef != 0) result.AddTerm(newCoef, this->termArray[i].exp);
            i++;
            j++;
        } else if (this->termArray[i].exp > poly.termArray[j].exp) {
            result.AddTerm(this->termArray[i].coef, this->termArray[i].exp);
            i++;
        } else {
            result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
    }

    while (i < this->terms) {
        result.AddTerm(this->termArray[i].coef, this->termArray[i].exp);
        i++;
    }

    while (j < poly.terms) {
        result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
        j++;
    }

    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;

    for (int i = 0; i < this->terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float newCoef = this->termArray[i].coef * poly.termArray[j].coef;
            int newExp = this->termArray[i].exp + poly.termArray[j].exp;
            result.AddTerm(newCoef, newExp);
        }
    }

    return result;
}

float Polynomial::Eval(float x) const {
    float result = 0;

    for (int i = 0; i < this->terms; i++) {
        result += termArray[i].coef * pow(x, termArray[i].exp);
    }

    return result;
}

istream& operator>>(istream& in, Polynomial& poly) {
    cout << "Enter the number of terms: ";
    int numTerms;
    in >> numTerms;

    for (int i = 0; i < numTerms; i++) {
        float coef;
        int exp;
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        in >> coef >> exp;
        poly.AddTerm(coef, exp);
    }

    return in;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    if (poly.terms == 0) {
        out << "0";
        return out;
    }

    for (int i = 0; i < poly.terms; i++) {
        if (i > 0 && poly.termArray[i].coef > 0) out << " + ";
        out << poly.termArray[i].coef;
        if (poly.termArray[i].exp != 0) out << "x^" << poly.termArray[i].exp;
    }

    return out;
}

int main() {
    Polynomial p1, p2;

    cout << "Enter the first polynomial: " << endl;
    cin >> p1;

    cout << "Enter the second polynomial: " << endl;
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    float x;
    cout << "Enter a value to evaluate the first polynomial: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}
