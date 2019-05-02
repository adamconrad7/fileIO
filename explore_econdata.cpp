/* Adam Conrad
 * 1/21/19
 * This program reads in a file specified on the command line and allows users to explore
 * it's contetnts based on certain criteria. This file contains the main() function.
 */
#include "econdata.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;
int main(int argc, char* argv[]){
ifstream infile(argv[1]);                //Takes in file name from command line and throws error if it can't be opened.
if (infile.fail()){
  cout<<"Failure to open file."<<endl;
  exit(EXIT_FAILURE);
}
char c;
infile.get(c);
states* stateptr = allocate_states(c);   //Dynamically allocates an array of pointers to structs that will contain the file's data.
read_state_data(stateptr, c, infile);    //Assigns stucts with data read in from file.
infile.close();
int n_states =(int)c-48;
bool again;
do{                                      //Allows the user to access and explore the data through a simple menu interface.
  char char1 = get_input(prompt1, 'c', 's');
  menu(char1, n_states, stateptr);
  again = get_input(prompt5, '0');
}while(again);
free_state_data(stateptr, n_states);    //De-allocates memory for structs.
return 0;
}
