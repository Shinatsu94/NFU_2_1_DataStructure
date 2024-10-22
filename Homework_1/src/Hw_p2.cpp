#include <iostream>
#include <cstring>
using namespace std;

int powerest(int *num, int n){
	cout<<"powerset(S) = {()";
	for(int i=0;i<=n;i++){
		cout<<", (";
		cout<<num[i];
		cout<<")";
	}
	cout<<"}"<<endl;
}

int main(){
	char *in = new char;
	cout<<"input S = (a b c ...):";
	cin.getline(in,256);
	//cout<<"your input:"<<in<<endl;
	int len = strlen(in);
	int n = 0;
	int *num = new int;
	num[0] = 0;
	for(int i=0;i<len;i++){
		int a = in[i]-48;
		if(a>=0 && a<=9){
			num[n] *= 10;
			num[n] += a; 
			//cout<<"["<<n<<"]:"<<num[n]<<endl;
		}else{
			n++;
			num[n] = 0;
		}
	}
	
	cout<<endl;
	powerest(num,n);
	
	return 0;
}
