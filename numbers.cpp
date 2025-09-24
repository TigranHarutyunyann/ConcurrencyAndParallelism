#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unistd.h>

#define N 7
using namespace std;


mutex mtx;
condition_variable ev;
condition_variable od;
condition_variable ze;
int g_num = N; 			  //user input number
int g_count = 0; 		  //count to num
bool g_statusNum = false; //false-odd, true-even
bool finished = false;
bool zero_turn = true;


void zeroTurn(){
 	//usleep(200000); 
	while(true){
		std::unique_lock<std::mutex> lock(mtx);
		ze.wait(lock, [] {return zero_turn || finished; });
        if(finished) return;

	    if(g_count >= g_num){
			finished = true;
			ev.notify_one();
			od.notify_one();
			return;
		}

		cout << "0 ";

		if(g_statusNum){
			ev.notify_one(); //call even
							 
		}else{
			od.notify_one(); //call odd

		}

		zero_turn = false;
	}
}

void oddTurn(){
	usleep(100000);

	while(true){
		std::unique_lock<std::mutex> lock(mtx);
		od.wait(lock, [] { return (!g_statusNum && !zero_turn) || finished; });

		if(finished) return;

		++g_count;
		cout << "\033[91m" << g_count << "\033[0m ";
		g_statusNum = true;

		zero_turn = true;
		ze.notify_one();	
	}
}

void evenTurn(){
    usleep(100000);
	while(true){
		std::unique_lock<std::mutex> lock(mtx);
		ev.wait(lock, [] { return (g_statusNum && !zero_turn) || finished; });

		if(finished) return;

		++g_count;
		cout << "\033[92m" << g_count << "\033[0m ";
		g_statusNum = false; 

		zero_turn = true;
		ze.notify_one();
	}	
}


int main(){
    thread t_zero(zeroTurn);
	thread t_odd(oddTurn);
	thread t_even(evenTurn);

	t_zero.join();
	t_odd.join();
	t_even.join();
	return 0;
}
