#include <iostream>
using namespace std;

//Ackermann's function
int F1(int m, int n){
	if(m == 0){
		return n+1;
	}else if(n == 0){
		return F1(m-1,1);
	}else{
		return F1(m-1,F1(m,n-1));
	}
	return -1; //error value.
}

int main(){
	int m,n;
	cout<<"input (m n):";
	cin>>m>>n;
	
	printf("Ackermann(%d,%d) = %d\n",m,n,F1(m,n));
	return 0;
}
