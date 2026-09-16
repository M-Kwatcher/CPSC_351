#include "processes.h"



void parent(){
	pid_t pid;
	pid = fork();

	if (pid < 0){
		std::cout << "Error occurred during fork() call\n";
		exit(-1);
	}
	else if (pid == 0){
		// call child1()
		std::cout << "Calling child1()\n";
		child1();
	}
	else{
		std::cout << "I am the original parent; my process id is pid=" << getpid() << "\n";
		
		// now need to wait for child1 to complete its lifecycle
		wait(NULL);
		exit(0);
	}

}

void child1(){
	pid_t my_pid = getpid();
	pid_t parent_pid = getppid();

	std::cout << "I am child pid=" << my_pid << "; my parent is pid=" << parent_pid << "\n";

	// Fork Child 2
	pid_t pid1 = fork();
	if (pid1 < 0) {
		std::cout << "Error occurred during fork() call\n";
		exit(-1);
	}	
	if (pid1 == 0) {
		std::cout << "Calling child2\n";
		child2();
		exit(0); // Ensure child process exits after finishing
	}

	// Fork Child 3 (executed by child1)
	pid_t pid2 = fork();
	if (pid2 < 0) {
		std::cout << "Error occurred during fork() call\n";
		exit(-1);
	}
	if (pid2 == 0) {
		std::cout << "Calling child3\n";
		child3();
		exit(0); // Ensure child process exits after finishing
	}

	// child1 waits for both child processes to complete
	wait(NULL);
	wait(NULL);
	exit(0);
}

void child2(){
	std::cout << "I am child2 pid=" << getpid() << "; my parent is pid=" << getppid() << "\n";
}

void child3(){
	std::cout << "I am child3 pid=" << getpid() << "; my parent is pid=" << getppid() << "\n";
}
