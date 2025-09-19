#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;
using ULL = unsigned long long;

ULL factorial(const int num) {
	if(num==0) return 1;

	return num*factorial(num-1);
}



int main() {
	atomic<ULL> numeratorResult(0);
	atomic<ULL> denumeratorResult(0);
	atomic<ULL> divisonResult(0);
    atomic<bool> readyN(false);
    atomic<bool> readyD(false);


	int n, r;
	cout << "Enter P(n, r)\n";
    cout << "n="; cin  >> n; 
	cout << "r="; cin  >> r;
    int subNR = n-r;

	thread numerator([&]{
			numeratorResult = factorial(n);
			readyN = true;
			});
	
	thread denumerator([&]{
			denumeratorResult = factorial(subNR);
			readyD = true;
			});
   	
	thread divison([&] {
			while(!readyN || !readyD) this_thread::sleep_for(chrono::seconds(1));
			divisonResult = static_cast<double>(numeratorResult / denumeratorResult);
			});

	numerator.join();
	denumerator.join();
    divison.join();

	cout << "result is: " << divisonResult << endl;  
	
	return 0;
}
