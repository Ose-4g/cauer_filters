#include <iostream>
#include <cmath>
#include "CauerFilter.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void printDetails(ofstream* file, CauerFilter a)
{
	//wirte details of the elliptic filter to a file.
	a.calculate_coefficients();
	*file<<a.n<<","
		<<a.getHo()<<",";
	a.printNumerator(file);
	*file<<",";
	a.printDenominator(file);
	*file<<","<<a.As<<endl;
}

int main()
{
	ofstream file;
	file.open("file.csv");
    
	file<<"ELLIPTIC FILTER TABLE FOR k = wp/ws = 0.5 Ap = Apmax = 0.25dB "<<endl<<endl;

	file<<"n"<<","
		<<"Constant"<<","
		<<"Numerator"<<","
		<<"Denominator"<<","
		<<"Asmin"<<endl<<endl;

	for(int n=1;n<11;n++)
		printDetails(&file, CauerFilter(0.25,n,200,400,0));


	file<<"\n\nELLIPTIC FILTER TABLE FOR k = wp/ws = 0.5 Ap = Apmax = 0.5dB "<<endl<<endl;
	
	file<<"n"<<","
		<<"Constant"<<","
		<<"Numerator"<<","
		<<"Denominator"<<","
		<<"Asmin"<<endl<<endl;

	for(int n=1;n<11;n++)
		printDetails(&file, CauerFilter(0.5,n,200,400,0));


	file.close();

	system("pause");
    return 0;
}