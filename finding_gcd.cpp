#include <iostream>

using namespace std;
int finding_gcd(int a, int b){
	int c;
	while(b != 0){
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int main(){

	int a, b;
	cin >> a >> b;
	cout << "GCD : " << finding_gcd(a,b) << endl;
}
