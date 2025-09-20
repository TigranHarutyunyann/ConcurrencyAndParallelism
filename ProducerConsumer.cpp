#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

#define N 1
using namespace std;

int shared_buffer = 0;
counting_semaphore<N> empty_slots(N);
counting_semaphore<N> full_slots(0);


void produce() {
	for(int i=1; i<=5; i++){
		empty_slots.acquire(); 

		shared_buffer=i;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "Produced: " << shared_buffer << endl;

		full_slots.release(); 
	}
}

void consum(){
	for(int i=1; i<=5 ; i++){
		full_slots.acquire(); 
		

		this_thread::sleep_for(chrono::seconds(1));
		cout << "Consumed: " << shared_buffer << endl;
		shared_buffer = 0;

		empty_slots.release();
	}   
}


int main() {
    thread producer(produce);
	thread consumer(consum);

	producer.join();
	consumer.join();

	return 0;
}

