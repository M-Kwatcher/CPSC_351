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
	pid_t my_pid, parent_pid, f_pid;
	my_pid = getpid();
	parent_pid = getppid();

	std::cout << "I am child pid=" << my_pid << "; my parent is pid=" << parent_pid << "\n";
	
	// now needs to call fork() to make child2 and child3
	f_pid = fork();

	if (f_pid < 0){
		// in error logic
		std::cout << "Error occurred during fork() call\n";
		exit(-1);
	}
	else if(f_pid == 0){
		// in child logic; call child2 and child3
		// I think I need to call fork() again here
		f_pid = fork();
		if (f_pid < 0){
			std::cout << "Error occurred during fork() call\n";
			exit(-1);
		}
		else if (f_pid == 0){
			// in child logic; call child3
			std::cout << "Calling child3\n";
			child3();
		}
		else{
			// in parent logic; call child2
			std::cout << "Calling child2\n";
			child2();
			wait(NULL);
			exit(0);
		}
		
	}
	else{
		// in parent logic
		//std::cout << "I am child pid=" << my_pid << "; my parent is pid=" << parent_pid << "\n";
		wait(NULL);
		exit(0);
	}
}

void child2(){
	std::cout << "I am child2 pid=" << getpid() << "; my parent is pid=" << getppid() << "\n";
}

void child3(){
	std::cout << "I am child3 pid=" << getpid() << "; my parent is pid=" << getppid() << "\n";
}
