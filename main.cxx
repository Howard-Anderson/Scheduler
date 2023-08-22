/* Project: To-Do List CLI.
 * 
 * Author: Howard Anderson.
 * 
 * Date: 10/2/2022.
 * 
 * A Simple To-Do List Application.
 */
  
#include <iostream>
#include <sqlite3.h>

//#include "Application.hpp"

#include "App.hpp"

// CMD Argument Count.
#define NO_ARGS 1
#define ONE_ARGS 2
#define TWO_ARGS 3

// CMD - Argument Values.
#define HELP "-h"
#define INSERT "-a"
#define DELETE "-d"


// Prints the available options.
void print_options() {
	std::cout<<"\n\n\t\tAVAILABLE OPTIONS:\n\n";
	std::cout<<"\n\n -h\t\t\tDisplays this help.";
	std::cout<<"\n -a\t\t\tInsert an item.";
	std::cout<<"\n -p <date>\t\tPrint an item.";
	std::cout<<"\n --print-all\t\tPrint all the items.";
	std::cout<<"\n -d <uid>\t\tDelete an item.";
}

// Prints the Title.
void print_title() {
	const std::string title = "\n\t\t+**************************************+" \
							  "\n\t\t+              Scheduler               +" \
							  "\n\t\t+**************************************+\n";
	std::cout<<"\n\n"<<title<<"\n\n";
}

void print_menu() {
	std::cout<<"\n\n Available Options:\n\n" \
			 <<"\n [A] Add Items" \
			 <<"\n [P] Print Items" \
			 <<"\n [D] Delete Item";
}

void execute(App &application) {
	print_menu();
	char option;
	char loop = ' '; // Determine whether to continue to add another item or not.
	std::cout<<"\n\n[#]: Option: "; std::cin>>option;
	switch(option) {
		case 'A':
			do {
				std::string date;
				std::cout<<"[#]: Enter Date [DD-MM-YYYY]: "; std::cin>>date;
				application.insert(date);
				std::cout<<"\n\n[$]: Continue ? [y/N]: "; std::cin>>loop;
			} while(loop == 'y' || loop == 'Y');
			break;
		case 'D':
			do {
				std::string uid;
				std::cout<<"[#]: Enter UID: "; std::cin>>uid;
				application.drop(uid);
				std::cout<<"\n\n[$]: Continue ? [y/N]: "; std::cin>>loop;
			} while(loop == 'y' || loop == 'Y');
			break;
		case 'P':
			std::string date;
			std::cout<<"[#]: Enter Date [DD-MM-YYYY]: "; std::cin>>date;
			application.print(date);
			break;
	}
}

//int main(int argc, char **argv) {
	//Application app;
	//std::string str[3];

	//switch(argc) {
		//case 1: 
			//std::cerr<<"\n\nThere is nothing to perform...\n\n"; break;
		//case 2: 
			////std::string arg = argv[1];
			//if(std::string(argv[1]) == "-h") { print_options(); }
			//if(std::string(argv[1]) == "-i") { 
				//for(auto i=0;i<3;i++) { std::cin>>str[i]; }
				//app.insert_item(str[0],str[1],std::stoi(str[2]));
			//}
			//if(std::string(argv[1]) == "--print-all") { app.printall(); }
			//break;
		//default: print_options();
	//}

	//return 0;
//}

//int main(int argc,char** argv) {
	//App app;
	
	//switch(argc) {
		//case 1: 
			//std::cerr<<"\n\nThere is nothing to perform...\n\n"; print_options(); break;
		//case 2: 
			//if(std::string(argv[1]) == "-h") { print_options(); }
			//if(std::string(argv[1]) == "-i") { app.insert(); }
			//if(std::string(argv[1]) == "--print-all") { app.printall(); }
			//break;
		//case 3:
			//if(std::string(argv[1]) == "-d") { app.drop(argv[2]); } 
			//if(std::string(argv[1]) == "-p") { app.print(argv[2]); }
			//break;
		//default: print_options();
	//}
	
	//std::cout<<"\n\n";
	//return 0;
//}

int main(int argc, char** argv) {
	print_title();
	App application;
	
	switch(argc) {
		case 1:
			execute(application); break;
		case 2: 
			if(std::string(argv[1]) == "-h") { print_options(); }
			if(std::string(argv[1]) == "--print-all") { application.printall(); }
			break;
		case 3:
			if(std::string(argv[1]) == "-a") { application.insert(argv[2]); }
			if(std::string(argv[1]) == "-d") { application.drop(argv[2]); } 
			if(std::string(argv[1]) == "-p") { application.print(argv[2]); }
			break;
		default: print_options();
	}
	
	std::cout<<"\n\n";
	
	return 0;
}

