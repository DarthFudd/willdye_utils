// Demonstrate that appending to a C++ string with 'str += x' is much faster than 'str = str + x'. An example of
// the output should be in a comment at the bottom of this file. --willdye, circa 2018. License: public domain.
#include <chrono> // Requires -std=c++11 or equivalent
#include <iomanip>
#include <iostream>
using namespace std;
using namespace std::chrono;
static system_clock::time_point
prefix(string *str, string comment){
	cout << " ; avg nsec for " << comment << ": ";
	cout << flush; // Flush now because the next cout might not be visible for several seconds.
	str->clear();
	return high_resolution_clock::now();} // This timestamp must remain on the last line of this proc.
static void
suffix(int cycles, system_clock::time_point before){
	system_clock::time_point after = high_resolution_clock::now(); // Timestamp must be on 1st proc line.
	// <nanoseconds> requires 64 bits, hence the "long long int".
	long long int elapsed_time = duration_cast<nanoseconds>(after - before).count();
	float average = elapsed_time / cycles;
	if( average > 10 )
		cout << setw(6); // Width 6 fits numbers such as "10,000" (comma included).
	cout << average;}
int
main(int argc, char* argv[]){
	cout << "Demonstrate the speed of 's += x' versus 's = s + x'\n";
	cout << "(spoiler: 's += x' is *much* faster than 's = s + x',\n";
	cout << "and the speed difference increases with string size).\n";
	cout.imbue(locale("")); // In my locale, 1000 prints as "1,000".
	for(int i = 10000; i <= 300000; i += 10000){
		cout << "Set size: " << setw(7) << i;
		string str;
		system_clock::time_point stamp;
		stamp = prefix(&str, "'s+=x'");  for(int j = 0; j < i; j++) str += '*';      suffix(i, stamp);
		stamp = prefix(&str, "'s=s+x'"); for(int k = 0; k < i; k++) str = str + '*'; suffix(i, stamp);
		cout << '\n';}
	return 0;}
/***************************************************************************************************************
Output example, by willdye on an Ubuntu workstation in early 2018:
	# g++ -Wall -std=c++17 append-performance.cpp && ./a.out
	Demonstrate the speed of 's += x' versus 's = s + x'
	(spoiler: 's += x' is *much* faster than 's = s + x',
	and the speed difference increases with string size).
	Set size:  10,000 ; avg nsec for 's+=x': 5 ; avg nsec for 's=s+x':    337
	Set size:  20,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':    602
	Set size:  30,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':    893
	Set size:  40,000 ; avg nsec for 's+=x': 2 ; avg nsec for 's=s+x':  1,076
	Set size:  50,000 ; avg nsec for 's+=x': 2 ; avg nsec for 's=s+x':  1,401
	Set size:  60,000 ; avg nsec for 's+=x': 2 ; avg nsec for 's=s+x':  1,877
	Set size:  70,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  2,348
	Set size:  80,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  2,654
	Set size:  90,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  2,990
	Set size: 100,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  3,532
	Set size: 110,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  4,000
	Set size: 120,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  4,083
	Set size: 130,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  4,697
	Set size: 140,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  4,573
	Set size: 150,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  5,250
	Set size: 160,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  5,375
	Set size: 170,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  5,635
	Set size: 180,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  6,324
	Set size: 190,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  7,005
	Set size: 200,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  7,036
	Set size: 210,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  7,017
	Set size: 220,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  7,776
	Set size: 230,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  7,708
	Set size: 240,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  8,478
	Set size: 250,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  8,468
	Set size: 260,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  8,897
	Set size: 270,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  9,708
	Set size: 280,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x':  9,681
	Set size: 290,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x': 10,207
	Set size: 300,000 ; avg nsec for 's+=x': 3 ; avg nsec for 's=s+x': 10,142
***************************************************************************************************************/
