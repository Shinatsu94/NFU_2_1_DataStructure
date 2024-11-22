#include <iostream>
#include <cmath>
using namespace std;

class Term{
	friend class Polynomial;
	private:
		float coef;
		int exp;
};
class Polynomial{
	public:
		Polynomial();
		Polynomial Add(Polynomial poly);
		Polynomial Mult(Polynomial poly);
		float Eval(float f);
		void AddTerm(float coef, int exp);
		friend istream& operator>>(istream& in, Polynomial poly);
		friend ostream& operator<<(ostream& out, Polynomial poly);
		
	private:
		Term *termArray;
		int capacity;
		int terms;
};
Polynomial::Polynomial(): termArray(NULL), capacity(0), terms(0){}
Polynomial Polynomial::Add(Polynomial poly){
	Polynomial result;
	
	int i=0,j=0;
	while(i < this->terms && j < poly.terms){
		if(this->termArray[i].exp == poly.termArray[j].exp){
			float newCoef = this->termArray[i].coef + poly.termArray[j].coef;
			if(newCoef != 0) result.AddTerm(newCoef, this->termArray[j].exp);
		}else if(this->termArray[i].exp > poly.termArray[j].exp){
			result.AddTerm(this->termArray[i].coef, this->termArray[i].exp);
			i++;
		}else{
			result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
			j++;
		}
	}
	while(i < this->terms){
		result.AddTerm(this->termArray[i].coef, this->termArray[i].exp);
		i++;
	}
	while(j < poly.terms) {
		result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
		j++;
	}
	
	return result;
}
Polynomial Polynomial::Mult(Polynomial poly){
	Polynomial result;
	
	for(int i=0;i<this->terms;i++){
		for(int j=0;j<poly.terms;j++){
			float newCoef = termArray[i].coef * poly.termArray[j].coef;
			int newExp = termArray[i].exp + poly.termArray[j].exp;
			result.AddTerm(newCoef, newExp);
		}
	}
	
	return result;
}
float Polynomial::Eval(float f){
	float result = 0;
	for(int i=0;i<this->terms;i++){
		result += termArray[i].coef * pow(f, this->termArray[i].exp);
	}
	
	return result;
}

void Polynomial::AddTerm(float coef, int exp){
	if(coef == 0) return;
	if(this->terms == this->capacity){
		this->capacity = (this->capacity == 0)?1:2 * this->capacity;
		Term *newArray = new Term[this->capacity];
		for(int i=0;i<this->terms;i++){
			newArray[i] = this->termArray[i];
		}
		delete[] this->termArray;
		this->termArray = newArray;
	}
	this->termArray[this->terms].coef = coef;
	this->termArray[this->terms].exp = exp;
	this->terms++;
}

istream& operator>>(istream& in, Polynomial poly){
	int numTerms;
	cout<<"Enter the number of terms: ";
	in >> numTerms;
	
	for(int i=0;i<numTerms;i++){
		float coef;
		int exp;
		cout<<"Enter coefficient and exponent for term "<< i+1 <<": ";
		in >> coef >> exp;
		poly.AddTerm(coef,exp);
	}
	
	return in;
}/*
ostream& operator<<(ostream& out, Polynomial poly){
	if(poly.terms == 0){
		out<<"0";
		return out;
	}
	
	for(int i=0;i<poly.terms;i++){
		out<<poly.termArray[i].coef;
		if(poly.termArray[i].exp != 0) out<<"x^"<<poly.termArray[i].exp;
	}
	
	return out;
}*/


int main(){
	Polynomial p1,p2;
	cout<<"Enter the first polynomial: "<<endl;
	cin >> p1;
	cout<<"Enter the second polynomial: "<<endl;
	cin >> p2;
	
	//cout<<"Sum: "<<p1.Add(p2)<<endl;
	//cout<<"Product: "<<p1.Mult(p2)<<endl;
	/*
	float x;
	cout<<"Enter the vlaue to evaluate the first polynomial: ";
	cin >> x;
	cout<<"P1("<<x<<") = "<<p1.Eval(x)<<endl;
	*/
	return 0;
}