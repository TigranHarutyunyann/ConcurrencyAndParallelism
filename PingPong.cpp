#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <unistd.h>
using namespace std;

#define N 10

mutex mtx;
condition_variable cv;
bool pTurn = true;

void pingFunction(){
	
	for(int i = 0; i<N; i++){
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [] {return pTurn; });

		usleep(500000);
        cout << "Ping" << endl;

		pTurn = false;
		cv.notify_one();
	}
}

void pongFunction(){
	

	for(int i = 0; i<N; i++){
		std::unique_lock<std::mutex> lock(mtx);

		cv.wait(lock, [] {return !pTurn; });

		usleep(550000);
        cout << "Pong" << endl;

		pTurn = true;
		cv.notify_one();
	}

}


int main(){
    thread ping(pingFunction);
	thread pong(pongFunction);

	ping.join();
	pong.join();
	
	return 0;
}
