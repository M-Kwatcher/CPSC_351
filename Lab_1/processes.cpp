#include "processes.h"


void end_of_life_cleanup(){
	wait(NULL);
	wait(NULL);
	exit(0);
}

void error_logic(){
	std::cout << "Error occurred during fork() call\n";
	exit(-1);
}

void print_pid_info(){
	std::cout << "I am child pid=" << getpid() << "; my parent is pid=" << getppid() << "\n";
}

void parent(){
	pid_t pid;
	pid = fork();

	if (pid < 0){
		error_logic();
	}
	else if (pid == 0){
		// call child1()
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
/******************************************************************************************
 * this function uses logic from gemini's pro model. Instead of using if, else if, else,  *
 * gemini recommended a flat approach(using a singular if statement to check pid against  *
 * fork() return values). This allows us to more easily trace the execution of parent vs  *
 * child logic. In the child branch, we reach an exit(0) call that terminates the child's *
 * flow. The parent is the only one capable of reaching lines beyond each exit() call.    *
 ******************************************************************************************/	

	print_pid_info();

	// Fork Child 2
	pid_t pid1 = fork();
	if (pid1 < 0) {
		error_logic();
	}	
	if (pid1 == 0) {
		child2();
		exit(0); // Ensure child process exits after finishing
	}

	// Fork Child 3 (executed by child1)
	pid_t pid2 = fork();
	if (pid2 < 0) {
		error_logic();
	}
	if (pid2 == 0) {
		child3();
		exit(0); // Ensure child process exits after finishing
	}

	// child1 waits for both child processes to complete
	end_of_life_cleanup();
}

void child2(){
	print_pid_info();
	// need to call fork() twice 
	// call exit(0) on child logic after invoking appropriate child() function
	// call wait(NULL) twice before final exit(0) call below if logic

	pid_t pid1 = fork();

	if(pid1 < 0){
		error_logic();
	}

	if(pid1 == 0){
		// in child logic
		child4();
		exit(0);
	}

	pid_t pid2 = fork();

	if(pid2 < 0){
		error_logic();
	}

	if(pid2 == 0){
		child5();
		exit(0);
	}
	
	end_of_life_cleanup();
}

void child3(){
	print_pid_info();

	pid_t pid1 = fork();

	if(pid1 < 0){
		error_logic();
	}

	if(pid1 == 0){
		child6();
		exit(0);
	}

	pid_t pid2 = fork();

	if(pid2 < 0){
		error_logic();
	}

	if(pid2 == 0){
		child7();
		exit(0);
	}
	
	end_of_life_cleanup();
}

void child4(){
	print_pid_info();
}

void child5(){
	print_pid_info();
}

void child6(){
	print_pid_info();
}

void child7(){
	print_pid_info();
}