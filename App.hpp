/* Project: To-Do List.
 * 
 * Author: Howard Anderson.
 * 
 * Date: 11/2/2022.
 * 
 * File: App.hpp (Defines App class with the sqlite3 implementation).
 */
 
#ifndef APP_HPP__
#define APP_HPP__

#include <iostream>
#include <sqlite3.h>

/* Notes:
 * 
 * Callback Functions: static int func(void* data_return,int argc,char** argv,char** colNames);
 * 
 * Table Name: List. 
 */
 
class App {

	private:
		sqlite3* _db;
		int _nrows; // To keep track of number of Rows in the Table.

		bool isformatted(const std::string&);

		void createtable();

		int count_records();

	public: 
		App();
 
		bool insert(const std::string);

		void print(const std::string&);

		void printall();
 
		void drop(const std::string&);

		~App();
};

// void* data, int argc, char** argv, char** colnames.
static int callback(void*, int, char**, char**);
// void* rows, int argc, char** argv, char** colnames.
static int count(void*, int, char**, char**);

#endif

