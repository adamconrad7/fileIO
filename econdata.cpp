#include "econdata.hpp"
#include <iostream>
#include <fstream>
#inlude <algorithm>

/*
 * This function displays a series of prompts to users and records their responses in order to display sata based on certain criteria.
 */
void menu(char char1, int n_states, struct states* stateptr){
  bool income = true;
  //Counties:
  if(char1=='c'){
    for(int i=0; i<n_states; i++){
      cout<<i+1<<") "<<stateptr[i].name<<endl;
    }
    int n = get_input(prompt0, 1,2,3);
    char datapick = get_input(prompt2, 'u', 'i');
    char sort_type;
    if(datapick != 'i'){
      income = false;
      sort_type = get_input(prompt3u, 'h','l','s');
    }else{
      sort_type = get_input(prompt3i, 'h','l','s');
    }
    display_countydata(sort_type, income, stateptr, n-1);
  //States
  }else{
    char datapick = get_input(prompt2, 'u', 'i');
    char sort_type;
    if(datapick != 'i'){
      income = false;
      sort_type = get_input(prompt3u, 'h','l','s');
    }else{
      sort_type = get_input(prompt3i, 'h','l','s');
    }
    display_statedata(sort_type, income, stateptr, n_states);
  }
}

/*
 * These functions takes in a series of parameters and sorts data acoordingly before outputting it to users.
 */
void display_statedata(char method, bool income, struct states* stateptr, int n ){
  switch (method) {
    //High
    case 'h':
      if(income){
        sort(stateptr, stateptr+ n , cmp_states_income);
        cout<<stateptr[0].name<<"  $"<<stateptr[0].med_income<<endl;
      }else{
        sort(stateptr, stateptr+ n , cmp_states_unemployment);
        cout<<stateptr[0].name<<" "<<stateptr[0].unemployed_2015<<"%"<<endl;
      }
    break;
    //Low
    case 'l':
        if(income){
            sort(stateptr, stateptr+ n , cmp_states_income);
            cout<<stateptr[n-1].name<<"  $"<<stateptr[n-1].med_income<<endl;
        }else{
          sort(stateptr, stateptr+ n , cmp_states_unemployment);
          cout<<stateptr[n-1].name<<" "<<stateptr[n-1].unemployed_2015<<"%"<<endl;
        }
    break;
    //sorted
    case 's':
    if(income){
        sort(stateptr, stateptr+ n , cmp_states_income);
        for (int i = 0; i < n; i++) {
          cout<<stateptr[i].name<<"  $"<<stateptr[i].med_income<<endl;
        }
    }else{
      //Need to use a different function to sort states based on change in unemployemet
      sort(stateptr, stateptr+ n , cmp_state_change_unemployment);
      for (int i = 0; i < n; i++) {
        cout<<stateptr[i].name<<" "<<stateptr[i].unemployed_2015-stateptr[i].unemployed_2007<<"%"<<endl;
      }
    }
  }
}

void display_countydata(char method, bool income, struct states* stateptr, int n ){
  switch (method) {
    //High
    case 'h':
      if(income){
        sort(stateptr[n].county_array, stateptr[n].county_array + stateptr[n].n_countys, cmp_counties_income);
        cout<<stateptr[n].county_array[0].name<<"  $"<<stateptr[n].county_array[0].med_income<<endl;
      }else{
        sort(stateptr[n].county_array, stateptr[n].county_array + stateptr[n].n_countys, cmp_counties_unemployment);
        cout<<stateptr[n].county_array[0].name<<" "<<stateptr[n].county_array[0].unemployed_2015<<"%"<<endl;
      }
    break;
    //Low
    case 'l':
        if(income){
            sort(stateptr[n].county_array, stateptr[n].county_array + stateptr[n].n_countys, cmp_counties_income);
            cout<<stateptr[n].county_array[stateptr[n].n_countys-1].name<<"  $"<<stateptr[n].county_array[stateptr[n].n_countys-1].med_income<<endl;
        }else{
          sort(stateptr[n].county_array, stateptr[n].county_array + stateptr[n].n_countys, cmp_counties_unemployment);
          cout<<stateptr[n].county_array[stateptr[n].n_countys-1].name<<" "<<stateptr[n].county_array[stateptr[n].n_countys-1].unemployed_2015<<"%"<<endl;
        }
    break;
    //sorted
    case 's':
    if(income){
        sort(stateptr[n].county_array, stateptr[n].county_array + stateptr[n].n_countys, cmp_counties_income);
        for (int i = 0; i < stateptr[n].n_countys; i++) {
          cout<<stateptr[n].county_array[i].name<<"  $"<<stateptr[n].county_array[i].med_income<<endl;
        }
    }else{
      //Need to use a different function to sort states based on change in unemployemet
      sort(stateptr[n].county_array, stateptr[n].county_array + stateptr[n].n_countys, cmp_county_change_unemployment);
      for (int i = 0; i < stateptr[n].n_countys; i++) {
        cout<<stateptr[n].county_array[i].name<<" "<<stateptr[n].county_array[i].unemployed_2015 - stateptr[n].county_array[i].unemployed_2007<<"%"<<endl;
      }
    }
  }
}

/*
 * These functions allocate arrays of structs that will hold data from the file in memory.
 */
struct states* allocate_states(int n){
  states* stateptr = new states[n];
  return stateptr;
}

struct countys* allocate_countys(int n){
  countys* countyptr = new countys[n];
  return countyptr;
}

/*
 * These functions fill structs with data from file.
 */
void read_state_data(struct states* stateptr, int c, std::ifstream& infile){
  for(int j =0; j<((int)c-48); j++){
    infile >> stateptr[j].name >> stateptr[j].unemployed_2007 >> stateptr[j].unemployed_2015 >> stateptr[j].med_income>> stateptr[j].n_countys;
    countys* countyptr = allocate_countys(stateptr[j].n_countys);
    read_county_data(countyptr, stateptr[j].n_countys, infile);
    stateptr[j].county_array = countyptr;
  }

}

void read_county_data(struct countys* countyptr, int n_countys, std::ifstream& infile){
  for(int i=0; i<n_countys; i++){
	  infile >> countyptr[i].name >>countyptr[i].unemployed_2007 >> countyptr[i].unemployed_2015 >> countyptr[i].med_income;
	}
}

/*
 * This function de-allocates data dynamically allocated by allocate_states()
 */
void free_state_data(struct states* stateptr, int n){
  for(int j=0; j<n; j++){
    delete [] stateptr[j].county_array;
  }
delete [] stateptr;
}

/*
 * These functions are used with sort() and return a bool based on which of two parameters is greater.
 */
bool cmp_counties_unemployment(const struct countys& c1, const struct countys& c2){
  return(c1.unemployed_2015 > c2.unemployed_2015);
}

bool cmp_counties_income(const struct countys& c1, const struct countys& c2){
  return(c1.med_income > c2.med_income);
}

bool cmp_states_unemployment(const struct states& c1, const struct states& c2){
  return(c1.unemployed_2015 > c2.unemployed_2015);
}

bool cmp_states_income(const struct states& c1, const struct states& c2){
  return(c1.med_income > c2.med_income);
}

bool cmp_state_change_unemployment(const struct states& c1, const struct states& c2){
  float d1 = c1.unemployed_2015 - c1.unemployed_2007;
  float d2 = c2.unemployed_2015 - c2.unemployed_2007;
  return(d1<d2);
}

bool cmp_county_change_unemployment(const struct countys& c1, const struct countys& c2){
  float d1 = c1.unemployed_2015 - c1.unemployed_2007;
  float d2 = c2.unemployed_2015 - c2.unemployed_2007;
  return(d1<d2);
}

/*
 * These functions simply take in a promt and acceptable responses and check if they match in ored to validate input.
 */
char get_input(string prompt, char c1, char c2){
  bool flag = false;
  char in;
  do{
    cout<<prompt<<endl;
    cin>>in;
    if(in != c1 && in != c2){
      cout<<"Please enter a valid choice."<<endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}

char get_input(string prompt, char c1, char c2, char c3){
  bool flag = false;
  char in;
  do{
    cout<<prompt<<endl;
    cin>> in;
    if(in != c1 && in != c2 && in != c3){
      cout<<"Please enter a valid choice."<<endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}

char get_input(string prompt, int i1, int i2, int i3){
  bool flag = false;
  int in;
  do{
    cout<<prompt<<endl;
    cin>> in;
    if(in != i1 && in != i2 && in != i3){
      cout<<"Please enter a valid choice."<<endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}

bool get_input(string prompt, char i1){
  char in;
  cout<<prompt<<endl;
  cin>> in;
  if(in != i1){
    return true;
  }else{
    return false;
  }
}
