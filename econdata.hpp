#ifndef econdata_hpp
#define econdata_hpp
#include <string>
using namespace std;
const string prompt5 ="Press any key to continue, or (0) to quit.";
const string prompt1 = "Would you like to explore the data on a (c)ounty or (s)tate level?";
const string prompt2 = "Would you like to see (u)nemployment or (i)ncome data?";
const string prompt3i = "Would you like to see the (h)ighest income, (l)owest income, or in (s)orted order?";
const string prompt3u = "Would you like to the (h)ighest unemployemet, (l)owest unemployemet, or (s)orted in order of change?";
const string prompt0 ="Please select a state who's counties you would like to explore.";


struct states* allocate_states(int n);
struct countys* allocate_countys(int n);
void read_state_data(struct states* stateptr, int c, std::ifstream& infile);
void read_county_data(struct countys* countyptr, int n_countys, std::ifstream& infile);
char get_input(string prompt, char c1, char c2);
char get_input(string prompt, char c1, char c2, char c3);
char get_input(string prompt, int i1, int i2, int i3);
void printstates(int n, struct states* stateptr);
void printcountys(int n, struct countys* countyptr);
void display_data(int method, bool high, struct states* stateptr, int n);
bool cmp_counties_unemployment( const struct countys& c1, const struct countys& c2);
bool get_input(string prompt, char i1);
void display_statedata(char method, bool income, struct states* stateptr, int n);
void display_countydata(char method, bool income, struct states* stateptr, int n);
bool cmp_states_unemployment(const struct states& c1, const struct states& c2);
bool cmp_states_income(const struct states& c1, const struct states& c2);
bool cmp_state_change_unemployment(const struct states& c1, const struct states& c2);
bool cmp_counties_income(const struct countys& c1, const struct countys& c2);
void menu(char char1, int n_states,  struct states* stateptr);
bool cmp_county_change_unemployment(const struct countys& c1, const struct countys& c2);
void free_state_data(struct states* stateptr, int n);

struct countys{
  std::string name;
  float unemployed_2007;
  float unemployed_2015;
  int med_income;
};

struct states{
  std::string name;
  float unemployed_2007;
  float unemployed_2015;
  int med_income;
  int n_countys;
  countys* county_array;
};
#endif
