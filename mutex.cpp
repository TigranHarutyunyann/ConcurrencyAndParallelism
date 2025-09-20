#include <iostream>
#include <mutex>
#include <thread>

#define SIZE 4
using namespace std;

int global_i = 0;
mutex mut;

void inrement(int n) {
	mut.lock();
	int i=global_i;
	while((i+100) != global_i) {
		++global_i;
	} 

	cout << "Working with thread " << n << ": TID=" << this_thread::get_id() <<  ": Result="<< global_i << endl;
	mut.unlock();
}

void decrement(int n) {
	mut.lock();
	int i=global_i;
	while((i-100) != global_i) {
		--global_i;
	} 
	cout << "Working with thread index=" << n << ": TID=" << this_thread::get_id() <<  ": Result=" << global_i << endl;
	mut.unlock();
}


int main() {
	thread threads[SIZE];

	for(int j = 0; j<SIZE; j++){
		if(j >= 2){
			threads[j] = thread(decrement, j);
		}else {
			threads[j] = thread(inrement, j);
		}
	}

	for(auto &t : threads){
		t.join();
	}
    cout << "So result is " << global_i << endl;

	return 0;
}
