// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <cstring>
#include <string.h> 
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#define PORT 23

using namespace std;

//Gloabal variables 
bool notDone = true;
bool localecho = true;
bool serverOn = true;
string name;
string number;
string* searchString = new string[0];
int sizeOfSearchString = 0;
int resultCount = 0;

bool insert(string name, string number){
	//variables 
	string dataRow;
	string insert;

	//Pull the text file for editing
	ifstream databaseIn("database.txt");

	//test to see if file opens 
	if(databaseIn.is_open()){
		//loop through the file until you get an empty line
		while(getline(databaseIn,dataRow)){
			//add the dataRow to insert for later
			insert += dataRow + "\n";
		}

		//add the new values to the insert values 
		insert += name + "," + number + "\n";
		
		//create another file and insert
		ofstream databaseOut("database.txt");
		databaseOut << insert;

	}
	else{
		return false;
	}

	databaseIn.close();
	return true;

}

void addToString(string toAdd){
	string* temp = searchString;
	sizeOfSearchString += 1;
	searchString = new string[sizeOfSearchString];
	for(int i = 0; i < sizeOfSearchString-1; i++){
		searchString[i] = temp[i];
	}
	searchString[sizeOfSearchString-1] = toAdd;
}

string* search(string typeToSearch, string* searchArray){
	//variables 
	string search;
	string nHolder;
	string numHolder;
	string* sun = new string[2];

	//open the file for reading 
	ifstream databaseIn("database.txt");

	//check if file can open
	if(databaseIn.is_open()){
		//check which type is being search
		if((typeToSearch.compare("name") == 0) || (typeToSearch.compare("number") == 0)){
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(nHolder.compare(searchArray[0]) == 0 || numHolder.compare(searchArray[0]) == 0){
					//create the string array 
					addToString(nHolder);
					addToString(numHolder);
					resultCount++;
					
				}

			}

		}
		else{
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(nHolder.compare(searchArray[0]) == 0 && numHolder.compare(searchArray[1]) == 0){
					//create the string array 
					addToString(nHolder);
					addToString(numHolder);
					resultCount++;
				}

			}

		}

		databaseIn.close();
		string* s = searchString;
		sizeOfSearchString = 0;
		searchString = new string[sizeOfSearchString];
		return s;

	}

	databaseIn.close();
	return NULL;
} 

bool update(string typeToUpdate, string* thingToUpdate, string* searchArray){
	//variables 
	string search;
	string nHolder;
	string numHolder;
	string lineHolder;
	string newTextFile;
	bool success = false;

	//open the file for reading 
	ifstream databaseIn("database.txt");

	//check if file can open
	if(databaseIn.is_open()){
		//check which type is being search
		if(typeToUpdate.compare("name") == 0){
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//hold the string for later
				lineHolder = search;

				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(nHolder.compare(searchArray[0]) == 0){
					//add the line to the new text file
					newTextFile += thingToUpdate[0] + "," + numHolder + "\n";
					success = true;
				}else{
					newTextFile += lineHolder + "\n";
				}

			}

		}else if(typeToUpdate.compare("number") == 0){
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//hold the string for later
				lineHolder = search;

				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(numHolder.compare(searchArray[0]) == 0){
					//add the line to the new text file
					newTextFile += nHolder + "," + thingToUpdate[0] + "\n";
					success = true;
				}else{
					newTextFile += lineHolder + "\n";
				}

			}

		}else{
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//hold the string for later
				lineHolder = search;

				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(nHolder.compare(searchArray[0]) == 0 && numHolder.compare(searchArray[1]) == 0){
					//create the string array 
					newTextFile += thingToUpdate[0] + "," + thingToUpdate[1] + "\n";
					success = true;
				}else{
					newTextFile += lineHolder + "\n";
				}

			}

		}

	}

	//cout << newTextFile << endl;

	//add back to the database 
	ofstream databaseOut("database.txt");
	if(databaseOut.is_open()){
		databaseOut << newTextFile;
	}

	//close the database
	databaseOut.close();
	databaseIn.close();
	return success;
}

bool remove(string typeToSearch, string* searchArray){
	//variables 
	string search;
	string nHolder;
	string numHolder;
	string lineHolder;
	string newTextFile;
	bool success = false;

	//open the file for reading 
	ifstream databaseIn("database.txt");

	//check if file can open
	if(databaseIn.is_open()){
		//check which type is being search
		if(typeToSearch.compare("name") == 0){
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//hold the string for later
				lineHolder = search;

				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(nHolder.compare(searchArray[0]) != 0){
					//add the line to the new text file
					newTextFile += lineHolder + "\n";

				}else{
					success = true;
				}

			}

		}else if(typeToSearch.compare("number") == 0){
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//hold the string for later
				lineHolder = search;

				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(numHolder.compare(searchArray[0]) != 0){
					//add the line to the new text file
					newTextFile += lineHolder + "\n";

				}else{
					success = true;
				}

			}

		}else{
			//get each line of the file for testing 
			while(getline(databaseIn, search)){
				//hold the string for later
				lineHolder = search;

				//create the string to search
				int pos = search.find(",");
				nHolder = search.substr(0, pos);
				numHolder = search.erase(0, pos + 1);

				//check if holder is equal to the required string 
				if(nHolder.compare(searchArray[0]) == 0 && numHolder.compare(searchArray[1]) == 0){
					//do nothing
					success = true;
				}else{
					//create the string array 
					newTextFile += lineHolder + "\n";
				}

			}

		}

	}
	//add back to the database 
	ofstream databaseOut("database.txt");
	if(databaseOut.is_open()){
		databaseOut << newTextFile;
	}

	//close the database
	databaseOut.close();
	databaseIn.close();
	return success;
}


void evalCommand(string cmd, int sock){
	char* msg = "";
	if(cmd.substr(0,5).compare("hello") == 0){
    	msg = "\u001b[34mHello, I am a Linux Server talking to you over Telnet!\n\u001b[33m";
    	send(sock , msg , strlen(msg) , 0 );
    }else if(cmd.substr(0,4).compare("help") == 0){
    	msg = " \u001b[36mManual:\n\thello - Say Hi :)\n\tclear - Clear the terminal\n\texit - Exit the program\n\tshutdown - Shutdown the server and exit the program\n\thelp - Display this message\n\tsearch - Search for a record in the database(e.g. search [fields] [values])\n\tinsert - Insert a new record into the database(e.g. insert [name] [number])\n\tupdate - Update a record into the database(e.g. update [fields] [values] [new_values])\n\tdelete - Delete a record from the database(e.g. delete [fields] [values])\n\t[fields] = name,number,both (Choose one option)\n\t[values] = Comma separated list of values, spaces should be represented as an underscore _ (e.g. Tom_Doe,0839413943)\n\u001b[33m";
    	send(sock , msg , strlen(msg) , 0 );
    }else if(cmd.substr(0,5).compare("clear") == 0){
    	msg = "\033[2J\033[H";
    	send(sock , msg , strlen(msg) , 0 );
    }else if(cmd.substr(0,8).compare("shutdown") == 0){
    	msg = "\u001b[34mServer closing, good bye!\n\u001b[33m";
    	send(sock , msg , strlen(msg) , 0 );
    	notDone = false;
    	serverOn = false;
    }else if(cmd.substr(0,4).compare("exit") == 0){
    	msg = "\u001b[34mGood Bye!\n\u001b[33m";
    	send(sock , msg , strlen(msg) , 0 );
    	notDone = false;
    }else if(cmd.substr(0,6).compare("search") == 0){
    	//GET INPUT FORMATTED
    	resultCount = 0;
    	string field = "";
    	string valueStr = "";
    	string values[2] = {"",""};
    	int words = 0;
    	string word = "";
	    for (auto x : cmd){
	        if (x == ' '){
	        	words++;
	            if(words == 2){
	            	field = word;
	            }
	            word = "";
	        }else{
	            word = word + x;
	        }
	    }
	    valueStr = word;
	    word = "";
	    words = 0;
	    for (auto x : valueStr){
	        if (x == ','){
	            values[words] = word;
	            word = "";
	            words++;
	        }else{
	            word = word + x;
	        }
	    }
	    values[words] = word;

	    //SEARCH
	    string* res = search(field, values);

		//Display Results
    	msg = "\u001b[35mResults:\n";
    	send(sock , msg , strlen(msg) , 0 );
    	string results = "";
    	if(res != NULL){
    		for(int x=0;x<resultCount*2;x++){
				if(!res[x].empty() && res[x] != "" && res[x] != "\r" && res[x] != "\n"){
					string tmp = "    ";
					for(int y=0;y<2;y++){
						if(y == 1){
							tmp = tmp+", "+res[x];
						}else{
							tmp = tmp+res[x];
							x++;
						}
					}
					results = results+tmp+"\n";
				}else{
					break;
				}
    		}
    	}
		results = results+"\u001b[33m";
		msg = const_cast<char*>(results.c_str());
		send(sock , msg , strlen(msg) , 0 );

		searchString = new string[0];
		sizeOfSearchString = 0;

    }else if(cmd.substr(0,6).compare("insert") == 0){
    	//GET INPUT FORMATTED
    	resultCount = 0;
    	string valueStr = "";
    	string values[2] = {"",""};
    	int words = 0;
    	string word = "";
	    for (auto x : cmd){
	        if (x == ' '){
	            word = "";
	        }else{
	            word = word + x;
	        }
	    }
	    valueStr = word;
	    word = "";
	    words = 0;
	    for (auto x : valueStr){
	        if (x == ','){
	            values[words] = word;
	            word = "";
	            words++;
	        }else{
	            word = word + x;
	        }
	    }
	    values[words] = word;

	    //INSERT
	    bool res = insert(values[0], values[1]);

		//Display Results
    	if(res){
			msg = "\u001b[35mNew Record Added!\n\u001b[33m";
	    	send(sock , msg , strlen(msg) , 0 );
    	}else{
    		msg = "\u001b[35mERROR: Failed to Add Record.\n\u001b[33m";
	    	send(sock , msg , strlen(msg) , 0 );
    	}
    }else if(cmd.substr(0,6).compare("delete") == 0){
    	//GET INPUT FORMATTED
    	resultCount = 0;
    	string field = "";
    	string valueStr = "";
    	string values[2] = {"",""};
    	int words = 0;
    	string word = "";
	    for (auto x : cmd){
	        if (x == ' '){
	        	words++;
	            if(words == 2){
	            	field = word;
	            }
	            word = "";
	        }else{
	            word = word + x;
	        }
	    }
	    valueStr = word;
	    word = "";
	    words = 0;
	    for (auto x : valueStr){
	        if (x == ','){
	            values[words] = word;
	            word = "";
	            words++;
	        }else{
	            word = word + x;
	        }
	    }
	    values[words] = word;

	    //INSERT
	    bool res = remove(field, values);

		//Display Results
    	if(res){
			msg = "\u001b[35mRecord Deleted!\n\u001b[33m";
    		send(sock , msg , strlen(msg) , 0 );
    	}else{
    		msg = "\u001b[35mERROR: Failed to Delete Record.\n\u001b[33m";
	    	send(sock , msg , strlen(msg) , 0 );
    	}
    	
    }else if(cmd.substr(0,6).compare("update") == 0){

    	//GET INPUT FORMATTED
    	resultCount = 0;
    	string field = "";
    	string newValStr = "";
    	string valueStr = "";
    	string values[2] = {"",""};
    	string newVals[2] = {"",""};
    	int words = 0;
    	string word = "";
	    for (auto x : cmd){
	        if (x == ' '){
	        	words++;
	            if(words == 2){
	            	field = word;
	            }else if(words == 3){
	            	valueStr = word; 
	            }
	            word = "";
	        }else{
	            word = word + x;
	        }
	    }
	    newValStr = word;

	    word = "";
	    words = 0;
	    for (auto x : valueStr){
	        if (x == ','){
	            values[words] = word;
	            word = "";
	            words++;
	        }else{
	            word = word + x;
	        }
	    }
	    values[words] = word;

	    word = "";
	    words = 0;
	    for (auto x : newValStr){
	        if (x == ','){
	            newVals[words] = word;
	            word = "";
	            words++;
	        }else{
	            word = word + x;
	        }
	    }
	    newVals[words] = word;

	    //SEARCH
	    bool res = update(field, newVals, values);

		//Display Results
    	if(res){
			msg = "\u001b[35mRecord Updated!\n\u001b[33m";
    		send(sock , msg , strlen(msg) , 0 );
    	}else{
    		msg = "\u001b[35mERROR: Failed to Update Record.\n\u001b[33m";
	    	send(sock , msg , strlen(msg) , 0 );
    	}

    }else{
    	msg = "\u001b[31mInvalid command!\n\u001b[33m";
    	send(sock , msg , strlen(msg) , 0 );
    }
}

int main(int argc, char const *argv[])
{ 
	while(serverOn){
	    //Variable Declarations
	    int server_fd, new_socket, valread; 
	    struct sockaddr_in address; 
	    int opt = 1; 
	    int addrlen = sizeof(address); 
	    char buffer[1024] = {0};
	    char* msg = "\033[2J\033[H\u001b[32m\u001b[1m-------------------\n| Friendly Phones |\n-------------------\nType help for more information!\u001b[0m\n\u001b[33m";
		
		//Server Setup
		server_fd = socket(AF_INET, SOCK_STREAM, 0);
	    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	    address.sin_family = AF_INET; 
	    address.sin_addr.s_addr = INADDR_ANY; 
	    address.sin_port = htons( PORT ); 
	    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
	    	cerr << "Binding on port " << PORT << " failed!" << endl;
	    	exit(EXIT_FAILURE); 
	    }
		listen(server_fd, 3);
		new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

	    //Initial Comms
	    valread = read( new_socket , buffer, 1024);
	    send(new_socket , msg , strlen(msg) , 0 );

	    //Main Loop
	    string inputString = "";
	    string word = "";

	    while(notDone){

		    if(localecho){
		    	string output(1024, 0);
			    if (read(new_socket, &output[0], 1023)<0) {
			        cerr << "Failed to read data from socket.\n";
			    }
			    
			    const regex accepted("[^\(\)a-zA-Z0-9,_ -]");

			    stringstream res;
			    regex_replace(std::ostream_iterator<char>(res), output.begin(), output.end(), accepted, ""); 
			    output = res.str();

			    if(output.length() == 1){
			    	msg = "\u001b[31m\nLocal Echo Off!\n\u001b[33m";
			    	send(new_socket , msg , strlen(msg) , 0 );
			    	localecho = false;
			    	continue;
			    }
			    evalCommand(output, new_socket);
			}else{

				string output(1024, 0);
			    if (read(new_socket, &output[0], 1023)<0) {
			        cerr << "Failed to read data from socket.\n";
			    }
			    
			    const regex accepted("[^\(\)a-zA-Z0-9,_ -]");

			    stringstream res;
			    regex_replace(std::ostream_iterator<char>(res), output.begin(), output.end(), accepted, ""); 
			    output = res.str();
			    msg = &output[0];
			    if(output.compare("") != 0 && output.compare(" ") != 0){
			    	word = word + output;
				}else if(output.compare("") == 0){
					if(inputString.compare("") != 0){
						inputString = inputString+" "+word;
					}else{
						inputString = word;
					}
					word = "";

					char* inputStrArr = &inputString[0];

					msg = "\n";
					send(new_socket , msg , strlen(msg) , 0 );
					//cout << "IN: " << inputString << endl;
					evalCommand(inputString, new_socket);					
			    	inputString = "";
				}else{
					if(inputString.compare("") != 0){
						inputString = inputString+" "+word;
					}else{
						inputString = word;
					}
					word = "";
				}


			    if(output.length() > 1){
			    	msg = "\u001b[31m\nLocal Echo On!\n\u001b[33m";
			    	send(new_socket , msg , strlen(msg) , 0 );
			    	localecho = true;
			    	continue;
			    }

			}
	    }
	    shutdown(server_fd, SO_REUSEADDR);
	    close(server_fd);
	}
    
    return 0; 
}