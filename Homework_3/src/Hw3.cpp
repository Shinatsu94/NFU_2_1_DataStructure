#include <iostream>
#include <cmath>
using namespace std;

struct Node{
	int coef;   //integer coefficients
	int exp;    //exponent
	Node* link; //point to next node
};

class Polynomial{
public:
	Polynomial();                    //constructor
	Polynomial(const Polynomial& a); //copy constructor
	~Polynomial();                   //destructor
	const Polynomial& operator=(const Polynomial& a); //assignment operator
	Polynomial operator+(const Polynomial& b) const; //addition operator
	Polynomial operator-(const Polynomial& b) const; //subtraction operator
	Polynomial operator*(const Polynomial& b) const; //multiplication operator
	float Evaluate(float x) const;
	
	friend istream& operator>>(istream& is, Polynomial& x);
	friend ostream& operator<<(ostream& os, Polynomial& x);
	
private:
	Node* header;                    //header node
	void AddTerm(int coef, int exp); //insert new term
	void Clear();                    //clear polynomial
};
Polynomial::Polynomial(){
	header = new Node{0, 0, NULL};
	header->link = header;
}
Polynomial::Polynomial(const Polynomial& a){
	header = new Node{0, 0, NULL};
	header->link = header;
	Node* check = a.header->link;
	while(check != a.header){
		AddTerm(check->coef, check->exp);
		check = check->link;
	}
}
Polynomial::~Polynomial(){
	Clear();
	delete header;
}
const Polynomial& Polynomial::operator=(const Polynomial& a){
	if(this == &a)return *this;
	Clear();
	Node* check = a.header->link;
	while(check != a.header){
		AddTerm(check->coef, check->exp);
		check = check->link;
	}
	return *this;
}
Polynomial Polynomial::operator+(const Polynomial& b) const{
	Polynomial result;
	Node* p1 = this->header->link;
	Node* p2 = b.header->link;
	
	while(p1 != this->header || p2 != b.header){
		if(p1 == this->header || (p2 != b.header && p2->exp > p1->exp)){
			result.AddTerm(p2->coef, p2->exp);
			p2 = p2->link;
		}else if((p1 != this->header && p1->exp > p2->exp) || p2 == b.header){
			result.AddTerm(p1->coef, p1->exp);
			p1 = p1->link;
		}else{
			int newCoef = p1->coef + p2->coef;
			if(newCoef != 0)result.AddTerm(newCoef, p1->exp);
			p1 = p1->link;
			p2 = p2->link;
		}
	}
	return result;
}
Polynomial Polynomial::operator-(const Polynomial& b) const{
	Polynomial result;
	Node* p1 = this->header->link;
	Node* p2 = b.header->link;
	
	while(p1 != this->header || p2 != b.header){
		if(p1 == this->header || (p2 != b.header && p2->exp > p1->exp)){
			result.AddTerm(p2->coef, p2->exp);
			p2 = p2->link;
		}else if((p1 != this->header && p1->exp > p2->exp) || p2 == b.header){
			result.AddTerm(p1->coef, p1->exp);
			p1 = p1->link;
		}else{
			int newCoef = p1->coef - p2->coef;
			if(newCoef != 0)result.AddTerm(newCoef, p1->exp);
			p1 = p1->link;
			p2 = p2->link;
		}
	}
	return result;
}
Polynomial Polynomial::operator*(const Polynomial& b) const{
	Polynomial result;
	Node* p1 = this->header->link;
	
	while(p1 != this->header){
		Node* p2 = b.header->link;
		while(p2 != b.header){
			int newCoef = p1->coef * p2->coef;
			int newExp = p1->exp + p2->exp;
			result.AddTerm(newCoef, newExp);
			p2 = p2->link;
		}
		p1 = p1->link;
	}
	return result;
}
float Polynomial::Evaluate(float x) const{
	float result = 0;
	Node* check = header->link;
	while(check != header){
		result += check->coef * pow(x, check->exp);
		check = check->link;
	}
	return result;
}
void Polynomial::AddTerm(int coef, int exp){
	if(coef == 0)return;
	
	Node* check = header;
	while(check->link != header && check->link->exp > exp){
		check = check->link;
	}
	if(check->link != header && check->link->exp == exp){
		check->link->coef += coef;
		if(check->link->coef == 0){
			Node* temp = check->link;
			check->link = temp->link;
			delete temp;
		}
	}else{
		Node* newNode = new Node{coef, exp, check->link};
		check->link = newNode;
	}
}
void Polynomial::Clear(){
	Node* check = header->link;
	while(check != header){
		Node* temp = check; //save current node.
		check = check->link;//move to next node.
		delete temp; //delete current node.
	}
	header->link = header;
}

istream& operator>>(istream& is, Polynomial& x){
	x.Clear();
	int n;
	cout<<" Enter number of terms: ";
	is >> n;
	for(int i=0;i<n;i++){
		int coef,exp;
		cout<<"  Enter coefficient and exponent: "<<i+1<<": ";
		is >> coef >> exp;
		x.AddTerm(coef,exp);
	}
	return is;
}
ostream& operator<<(ostream& os, Polynomial& x){
	Node* check = x.header->link;
	if(check == x.header){
		os<<"0";
		return os;
	}
	bool first = true;
	while(check != x.header){
		if(!first && check->coef > 0)os<<" + ";
		if(!first && check->coef < 0)os<<" - ";
		if(check->coef != 1 || check->exp == 0)os<<abs(check->coef);
		if(check->exp != 0){
			os<<"x";
			if(check->exp != 1)os<<"^"<<check->exp;
		}
		check = check->link;
		first = false;
	}
	return os;
}

int main(){
	Polynomial p1, p2;
    cout << "Enter the first polynomial:" << endl;
    cin >> p1;
    cout << "Enter the second polynomial:" << endl;
    cin >> p2;
	
    cout << "First polynomial: " << p1 << endl;
    cout << "Second polynomial: " << p2 << endl;
	
    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;
	
	cout<<endl;
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
	
    float x;
	cout<<endl;
    cout << "Enter a value to evaluate the first polynomial: ";
    cin >> x;
    cout << "Value of the first polynomial at " << x << ": " << p1.Evaluate(x) << endl;
	
    return 0;
}