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
	Polynomial(): termArray(NULL), capacity(0), terms(0){} //constructor
	Polynomial(const Polynomial& other); //copy constructor
	~Polynomial(){delete[] termArray;} //destructor
	Polynomial Simplify();
	Polynomial Add(Polynomial poly);
	Polynomial Mult(Polynomial poly);
	float Eval(float f);
	
	float GetCoef(int index)const{return termArray[index].coef;}
	int GetExp(int index)const{return termArray[index].exp;}
	
	friend istream& operator>>(istream& in, Polynomial& poly);
	friend ostream& operator<<(ostream& out, Polynomial poly);
	
private:
	Term *termArray;
	int capacity;
	int terms;
	void AddTerm(float coef, int exp);
};
Polynomial::Polynomial(const Polynomial& other){
	terms = other.terms;
	capacity = other.capacity;
	termArray = new Term[capacity];
	for(int i=0;i<terms;i++){
		termArray[i] = other.termArray[i];
	}
}
Polynomial Polynomial::Simplify(){
	Polynomial result;
	
	for(int i=0;i<terms;i++){
		for(int j=i+1;j<terms;j++){
			if(termArray[i].exp < termArray[j].exp){
				Term temp = termArray[i];
				termArray[i] = termArray[j];
				termArray[j] = temp;
			}
		}
	}
	for(int i=0;i<terms;i++){
		float newCoef = termArray[i].coef;
		int newExp = termArray[i].exp;
		while(i+1 < terms && termArray[i+1].exp == newExp){
			newCoef += termArray[i+1].coef;
			i++;
		}
		if(newCoef != 0){result.AddTerm(newCoef, newExp);}
	}
	
	return result;
}
Polynomial Polynomial::Add(Polynomial poly){
	Polynomial p1 = Simplify();
	Polynomial p2 = poly.Simplify();
	Polynomial result;
	int i = 0, j = 0;
	
	while(i < p1.terms || j < p2.terms){
		if(i < p1.terms && (j >= p2.terms || p1.termArray[i].exp > p2.termArray[j].exp)){
			result.AddTerm(p1.termArray[i].coef, p1.termArray[i].exp);
			i++;
		}else if(j < p2.terms && (i >= p1.terms || p2.termArray[j].exp > p1.termArray[i].exp)){
			result.AddTerm(p2.termArray[j].coef, p2.termArray[j].exp);
			j++;
		}else{
			float newCoef = p1.termArray[i].coef + p2.termArray[j].coef;
			if(newCoef != 0){result.AddTerm(newCoef, p1.termArray[i].exp);}
			i++; j++;
		}
	}
	
	return result;
}
Polynomial Polynomial::Mult(Polynomial poly){
	Polynomial result;
	
	for(int i=0;i<terms;i++){
		for(int j=0;j<poly.terms;j++){
			float newCoef = termArray[i].coef * poly.termArray[j].coef;
			int newExp = termArray[i].exp + poly.termArray[j].exp;
			result.AddTerm(newCoef, newExp);
		}
	}
	
	return result.Simplify();
}
float Polynomial::Eval(float f){
	float result = 0;
	for(int i=0;i<terms;i++){
		result += GetCoef(i) * pow(f, GetExp(i));
	}
	
	return result;
}
void Polynomial::AddTerm(float coef, int exp){
	if(coef == 0)return;
	if(terms == capacity){
		capacity = (capacity == 0)?1 :capacity*2;
		Term *newArray = new Term[capacity];
		for(int i=0;i<terms;i++){
			newArray[i] = termArray[i];
		}
		delete[] termArray;
		termArray = newArray;
	}
	termArray[terms].coef = coef;
	termArray[terms].exp = exp;
	terms++;
}

istream& operator>>(istream& in, Polynomial& poly){
	int numTerms;
	cout<<" Enter the number of terms: ";
	in>>numTerms;
	
	for(int i=0;i<numTerms;i++){
		float coef;
		int exp;
		cout<<"  Enter coefficient and exponent for term: "<< i+1 <<": ";
		in>>coef>>exp;
		poly.AddTerm(coef,exp);
	}
	
	return in;
}
ostream& operator<<(ostream& out, Polynomial poly){
	if(poly.terms == 0){
		out<<"0";
		return out;
	}
	
	for(int i=0;i<poly.terms;i++){
		if(i > 0 && poly.GetCoef(i) > 0){out<<" + ";}
		if(i > 0 && poly.GetCoef(i) < 0){out<<" - ";}
		if(poly.GetCoef(i) != 1 || (i+1 == poly.terms)){out<<abs(poly.GetCoef(i));}
		if(poly.GetExp(i) != 0){
			out<<"x";
			if(poly.GetExp(i) != 1)out<<"^"<<poly.GetExp(i);
		}
	}
	
	return out;
}

int main(){
	Polynomial p1,p2;
	cout<<"Enter the first polynomial: "<<endl;
	cin>>p1;
	cout<<"Enter the second polynomial: "<<endl;
	cin>>p2;
	
	cout<<"Sum: "<<p1.Add(p2)<<endl;
	cout<<"Product: "<<p1.Mult(p2)<<endl;
	
	float x;
	cout<<"Enter the value to evaluate the first polynomial: ";
	cin>>x;
	cout<<"P1("<<x<<") = "<<p1.Eval(x)<<endl;
	
	return 0;
}