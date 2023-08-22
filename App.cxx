/* Project: To-Do List.
 * 
 * Author: Howard Anderson.
 * 
 * Date: 11/2/2022.
 * 
 * File: App.cxx ( Implementation File for App.hpp).
 */

#include "App.hpp"

// Static Callback Functions.
static int callback(void* data,int argc,char** argv,char** colname) {
	//std::cerr<<"\n\n"<<(const char*)data;
	//std::cout<<"\n\nArgc = "<<argc<<"\n\n";
	for(int i=0;i<argc;i++) { std::cout<<argv[i]<<"\t"; }
	std::cout<<"\n";
	return 0;
}

static int count(void* rows,int agrc,char** argv,char** colname) {
	int* c = (int*)rows; 
	*c = atoi(argv[0]); 
	return 0;
}

// Class: App - Function Definitions:

// Constructors.
App::App() { 
	_db = NULL; sqlite3_open("Listtodo.db",&_db); 
	try {
		_nrows = count_records();
		if(_nrows == 0 ) { throw(_nrows); }
		std::cout<<"\n\n[ $ ] Tasks Found: "<<_nrows<<"\n\n"; // *Tasks*
		
		}
	catch(int rows) { std::cout<<"\n\n[ ! ] Exception: No records Found.\n\n"; }
	//createtable(); 
}

// Destructor.
App::~App() { sqlite3_close(_db); _db = NULL; std::cout<<"\n\n[ $ ] Exiting\n\n"; }


// Functions for Transations on the Database:

// Inserts Items once.
bool App::insert(const std::string date) {
	std::string data[3], sql;
	char* ermesg = NULL;
	int uid = _nrows + 1;
	data[0] = date;
	std::cin.clear(); std::cin.ignore();
	while(!isformatted(data[0])) {
		try {
			if(!isformatted(data[0])) { throw(data[0]); }
		}
		catch(std::string date) {
			std::cerr<<"\n\n[ ! ] Exception: Date isn't formatted as required !!";
			std::cout<<"\n\nDate [DD-MM-YYY]: "; std::cin>>data[0];
		}
	}
	std::cout<<"\n\nParticulars: "; std::getline(std::cin,data[1]); //getline(std::cin,);
	std::cout<<"\n\nDuration: "; getline(std::cin,data[2]);
	sql = "INSERT INTO LIST(UID,DATE,PARTICULARS,DURATION) VALUES( "+ std::to_string(uid) + ",' "+data[0]+" ', ' "+data[1]+" ' , ' "+data[2]+" ' );";
	try {
		int status = sqlite3_exec(_db,sql.c_str(),NULL,0,&ermesg);
		if(status != SQLITE_OK) { throw (ermesg); } 
		else { std::cout<<"\n\n[ $ ] Record Successfully Inserted !!\n\n"; }
	}
	catch(char* ermesg) { std::cerr<<"\n\n[ ! ] Error on Insertion: "<<ermesg<<"\n\n"; return false; }
	sqlite3_free(ermesg); ermesg = NULL; 
	return true;
}

// Prints all the Items.
void App::printall() {
	const std::string sql = "SELECT * FROM LIST; ";
	std::cout<<"\n\nUID  \t DATE  \t\t TASKS\t\t  DURATION \n\n";
	sqlite3_exec(_db,sql.c_str(),callback,NULL,NULL);
}

// Check for correct Date Formatting.
bool App::isformatted(const std::string& date) {
	if(date.size() == 10) { 
		if(date[2] == '-' && date[5] == '-') { return true; }
	}
	return false;
}

// Creates a new Table in Sqlite3.
void App::createtable() {
	char* error;
	std::string sql = "CREATE TABLE LIST(UID INT,DATE TEXT,PARTICULARS TEXT,DURATION TEXT);";
	try {
		if(SQLITE_OK == sqlite3_exec(_db,sql.c_str(),NULL,0,&error)) { std::cout<<"\n\n[ $ ] Table Created Successfully !!\n\n"; }
		else { throw("Error"); }
	}
	catch(...) { std::cerr<<"\n\n[ ! ] Error on Table Creation: "<<error<<"n\n"; }
	sqlite3_free(error); error = NULL;
}

// Counts the Number of Records.
int App::count_records() {
	std::string sql = "SELECT COUNT(*) FROM LIST;";
	int records_count;
	char* error;
	try {
		if(SQLITE_OK == sqlite3_exec(_db,sql.c_str(),count,&records_count,&error)) { return records_count; }
		else { throw(error); }
	}
	catch(char* err) { std::cerr<<"\n\n[ ! ] Error: "<<err<<"\n\n"; }
	sqlite3_free(error); error = NULL;
	return 0;
}

// Delete a particular Item.
void App::drop(const std::string& uid) {
	std::string sql = "DELETE FROM LIST WHERE UID = " + uid + ";";
	char* error;
	try { 
		if(SQLITE_OK == sqlite3_exec(_db,sql.c_str(),NULL,0,&error)) { std::cout<<"\n\n[ $ ] Record Deleted Successfully !!\n\n"; }
		else { throw(error); }
	}
	catch(char* e) { std::cerr<<"\n\n[ ! ] Error on Deletion: "<<e<<"\n\n"; }
	sqlite3_free(error); error = NULL;
}

// Print Items on particular date.
void App::print(const std::string& date) { 
	std::cin.clear(); std::cin.ignore();
	while(!isformatted(date)) {
		try {
			if(!isformatted(date)) { throw(date); }
		}
		catch(std::string date) {
			std::cerr<<"\n\n[ ! ] Exception: Date isn't formatted as required !!";
			std::cout<<"\n\nEnter the Date [DD-MM-YYYY]: "; getline(std::cin,date);
		}
	}
	std::string sql = "SELECT * FROM LIST WHERE DATE = ' " + date + " ';";
	std::cout<<"\n\nUID  \t DATE  \t\t TASKS\t\t  DURATION \n\n";
	sqlite3_exec(_db,sql.c_str(),callback,NULL,NULL);
}
