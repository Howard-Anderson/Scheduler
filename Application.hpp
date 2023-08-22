/* Project: To-Do Application.
 * 
 * Author: Howard Anderson.
 * 
 * Date: 10/2/2022.
 * 
 * File: Application.hpp (Header File).
 */ 

#ifndef APP_HPP__
#define APP_HPP__

#include <iostream>
#include <list>
#include <iterator>

/* Notes:
 * Date: Format (DD-MM-YYYY);
 * Duration - minutes;
 */
  
struct Data {
	std::string date;
	std::string particulars;
	std::string duration;
};

class Application {
	// Class Attributes.
	Data* _data;
	std::list<Data> _list;
	
	public:
		Application() { _data = NULL; }
		
		void insert_item(const std::string, const std::string, const int);
		
		void printall();
		
		// Prints items for a specific date.
		void print(const std::string);
		
		~Application() { if(_data ! = NULL) { delete _data; } std::cout<<"\n\n\t\t~~ [ $ ] Exiting.... ~~\n\n"; }

};

void Application::insert_item(const std::string date, const std::string particulars, const int mins) {
	_data = new Data;
	_data->date = date; _data->particulars = particulars; 
	_data->duration = std::to_string(mins) + " mins ";
	_list.push_back(*_data);
	delete _data;
}

void Application::printall() {
	std::cout<<"\n\nDate\t\tParticulars\t\tDuration\n\n";
	if(_list.empty()) { std::cout<<"\n\n[ $ ] List is Empty !!\n\n"; return; }
	for(std::list<Data>::iterator it = _list.begin(); it != _list.end(); ++it) {
		std::cout<<"\n"<<it->date<<"\t\t"<<it->particulars<<"\t\t"<<it->duration;
	}
}

void Application::print(const std::string date) {
	std::cout<<"\n\nDate\t\tParticulars\t\tDuration\n\n";
	if(_list.empty()) { std::cout<<"\n\n[ $ ] List is Empty !!\n\n"; return; }
	for(std::list<Data>::iterator it = _list.begin(); it != _list.end(); ++it) {
		if(it->date == date) { std::cout<<"\n"<<it->date<<"\t\t"<<it->particulars<<"\t\t"<<it->duration; }
	}
}

#endif
