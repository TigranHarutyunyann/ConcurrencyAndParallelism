#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <unistd.h>

#define N 5
using namespace std;

condition_variable cv;
mutex mtx;
thread friends[N];
bool booking = false;

void getReadyForVacation(const int number){
	sleep(1);
	cout << "I'am friend: " << number << endl;

	std::unique_lock<std::mutex> lock(mtx);
    while(!booking){
//		cv.wait(lock);
	}

	cout << "frined number>" << number << " say thank you\n";
}

void bookTickets(){
    sleep(2);
	mtx.lock();

	booking = true;
	cout << "Frineds: tickets are booked!\n";

	cv.notify_all();
	mtx.unlock();
	
}

int main(){

	//threads init's
	for(int i=0; i<N; i++){
		friends[i] = thread(getReadyForVacation, i);
	}
	thread Rich(bookTickets);

	//thread join's
	for(int i=0; i<N; i++){
    	friends[i].join();
	}
	Rich.join();

	
	
	return 0;
}
