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
	pid_t my_pid, parent_pid, first_fork_pid, second_fork_pid;
	my_pid = getpid();
	parent_pid = getppid();

	std::cout << "I am child pid=" << my_pid << "; my parent is pid=" << parent_pid << "\n";
	
	// now needs to call fork() to make child2 and child3
	first_fork_pid = fork();

	if (first_fork_pid < 0){
		// in error logic
		std::cout << "Error occurred during fork() call\n";
		exit(-1);
	}
	else if(first_fork_pid == 0){
		// in child logic; call child2
		// I think I need to call fork() again here
		child2();
	}
	else{
		// in parent logic
		//std::cout << "I am child pid=" << my_pid << "; my parent is pid=" << parent_pid << "\n";
		wait(NULL);
		exit(0);
	}

	second_fork_pid = fork();
	if (second_fork_pid < 0){
		// in error logic
		std::cout << "Error occurred during fork() call\n";
		exit(-1);		
	}
	else if(second_fork_pid == 0){
		// in child logic
		child3();
	}
	else{
		// in parent logic
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
