#ifndef CAUERFILTER_H_INCLUDED
#define CAUERFILTER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct CauerFilter
{
	double Ap; //maximum pass band loss in dB,
	double As; //minium stop band loss in dB
	double wp; //pass band cutoff frequency
	double ws; //stop band cut off frequency


	double k, //selectivity factor
	u,
	q, //modular constant
	D, //Discrimination factor
	V,
	po,
	W,
	miu;

	int r;

	double n;//order of the normalized equation


	/**Constructor*/
	CauerFilter(double Ap, //maximum pass band loss in dB,
					double As,//minium stop band loss in dB
					double wp,//pass band cutoff frequency
					double ws //stop band cut off frequency
					)
	{
		this->Ap = Ap;
		this->As = As;
		this->ws = ws;
		this->wp = wp;

		calculate_constants_of_elliptic_filter();

	}



	CauerFilter(double Ap, //maximum pass band loss in dB,
					int n,//order
					double wp,//pass band cutoff frequency
					double ws, //stop band cut off frequency
					int justThere//just to differentiate the two constructors.
					)

	{
		this->n = n;
		this->Ap =Ap;
		this->ws = ws;
		this->wp = wp;

		k = wp/ws;

		double a = (1-(k*k));
		a = pow(a,0.25);

		u = 0.5*(1-a)/(1+a);

		q = u + 2*pow(u,5) + 15*pow(u,9) + 150*pow(u,13);

		int b= (int) n;
		r = (b%2==0?b/2:(b-1)/2);

		//calculate the value of As
		As = pow(10,Ap/10)-1;
		As/=(16*pow(q,n));
		As+=1;
		As = 10*log10(As);
	}


	/**Calculate for normalized transfer functions*/
	void calculate_coefficients();

	double CauerFilter:: getHo();

	void printNumerator(ofstream*);
	void printDenominator(ofstream*);
	






private:
	double sum_function_1(int m);
	double sum_function_2(int m);
	double sum_function_3(int m);
	double sum_function_4(int m);
	double sum_function(int type,int m);
	/**Calculated the order of the normalized equation*/
	void calculate_constants_of_elliptic_filter();
	double summation(int,int);

	vector <double> Ai;
	vector <double> Bi;
	vector <double> Ci;
	
};



#endif // CAUERFILTER_H_INCLUDED
