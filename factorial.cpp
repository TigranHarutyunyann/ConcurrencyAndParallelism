#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
using ULL = unsigned long long;
           
ULL factorial(const int& num){
	if(num == 0) return 1;

	return num * factorial(num-1);

}


int main() {

	int pipe1[2];
	if(pipe(pipe1)==-1) {
		cerr << "Pipe failed. error\n";
		return 1;
	}

	pid_t pid = fork();
	if(pid < 0) {
		cerr << "Fork failed. error." << endl;
		return 2;
	}

	if(pid == 0){
		close(pipe1[0]);

		cout << "Current process ID = " << getpid();
		cout << "\nIn Child process. Enter a number \n> ";
		int num;
		cin >> num;
		ULL result = factorial(num);

		write(pipe1[1], &result, sizeof(result));

		close(pipe1[1]);
		exit(0);
	
	}else{
		cout << "Current process ID = " << getpid();
		close(pipe1[1]);

		ULL res;
		read(pipe1[0], &res, sizeof(res));

        close(pipe1[0]);
		wait(nullptr);
	    cout << "\nFactorial is: " << res << endl;
	}

	return 0;
}
