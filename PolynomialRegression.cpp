/*
Values in lines containing '//^' can be tweaked
in order to get a more accurate output.
*/
#include <fstream>
#include <vector>
#include <time.h>
#include <chrono>
#include "VectClass.cpp"

using namespace std;


void readData(int&, Vect&, Vect&, int&, double&);
void writeData(Vect&, Vect&, Vect&, int&);


void elapsedTime(chrono::_V2::system_clock::time_point st, chrono::_V2::system_clock::time_point en, string s){
	chrono::duration <float> dur = en - st;
	cout << "\n" << s << dur.count() * 1000 << " ms";
}

int main(){
	auto t0 = chrono::high_resolution_clock::now();
	double err = 1, eps = 1e-6, alp;	//^eps = stopping criterion epsilon, alp = learning rate alpha
	int iter = 0, order, len, denom, epochs = 10000;	//^
	Vect x, y, yh;
	vector<double> J;	//x,y = data points, yh = hypothesis function, J = loss function
	auto t1 = chrono::high_resolution_clock::now();

	readData(len, x, y, order, alp);
	yh.initialize(len);
	auto t2 = chrono::high_resolution_clock::now();

	/*This block is to get the inputs from the terminal (user)*/
	// cout << "Length of the vector? ";
	// cin >> len;

	// cout << "x: ";
	// x.getValues(cin, len);
	// cout << "y: ";
	// y.getValues(cin, len);

	// cout << "Order of the output polynomial? ";
	// cin >> order;

	// cout << "Learning rate? ";	//Uncomment to give custom learning rate at runtime
	// cin >> alp;

	denom = 10 * len;	//^
	alp = 5 * pow(10, -order);	//Comment to give custom learning rate at runtime
	order++;
	auto t3 = chrono::high_resolution_clock::now();

	double* W = new double[order];	//Weight matrix
	double* delJ = new double[order];	//Partial derivatives of J
	srand(time(0));
	for (int i = 0; i < order; i++){	//Initializing weights randomly
		W[i] = ((double) rand()/(RAND_MAX));
	}
	auto t4 = chrono::high_resolution_clock::now();

	// yh = (x^0) * W[0];
	for (int i = 0; i < 10; i++){
		yh[i] = W[0];
	}
	for (int i = 1; i < order; i++){
		yh += (x^i) * W[i];
	}

	Vect yDiff;
	yDiff.initialize(len);
	yDiff = y;
	yDiff -= yh;

	J.push_back((yDiff^2).sum()/(2*len));

	auto t5 = chrono::high_resolution_clock::now();
	while (err > eps && iter < epochs){
		for (int i = 0; i < order; i++){
			delJ[i] = -(((x^i)*yDiff).sum())/denom;
			W[i] -= alp * delJ[i];
		}

		iter++;
		yDiff += yh;
		// yh = (x^0) * W[0];
		for (int i = 0; i < 10; i++){
			yh[i] = W[0];
		}
		for (int i = 1; i < order; i++){
			yh += (x^i) * W[i];
		}
		yDiff -= yh;

		J.push_back((yDiff^2).sum()/(2*denom));
		err = J[iter] - J[iter-1];
		if (err > 0){
			alp /= 2;	//^
		}
		err = (err < 0) ? -err : err;

	}
	auto t6 = chrono::high_resolution_clock::now();

	elapsedTime(t0, t1, "Initialization: ");
	elapsedTime(t1, t2, "Read Data: ");
	elapsedTime(t2, t3, "2nd Initialization: ");
	elapsedTime(t3, t4, "Weights: ");
	elapsedTime(t4, t5, "1st Iteration: ");
	elapsedTime(t5, t6, "Bulk: ");
	elapsedTime(t0, t6, "\nTotal: ");

	// writeData(x, y, yh, len);

	/*This block is to print the output to the terminal*/
	// cout << "\n" << err << " " << iter << "\n";

	// x.disp();
	// y.disp();
	// yh.disp();

	// cout << "\nCoefficients: ";
	// for (int i = order-1; i >= 0; i--){
	// 	cout << W[i] << " ";
	// }

	delete[] W;
	delete[] delJ;
}


void readData(int& len, Vect& x, Vect& y, int& order, double& alp){
	ifstream input;
	input.open("Input.txt");

	input >> len;
	x.initialize(len);
	x.getValues(input, len);
	y.initialize(len);
	y.getValues(input, len);
	input >> order;
	// input >> alp;	//Uncomment to give custom learning rate at runtime

	input.close();
}


void writeData(Vect& x, Vect& y, Vect& yh, int& len){
	ofstream output;
	output.open("Output.csv");

	output << "X, Y, Yh\n";
	for (int i = 0; i < len; i++){
		output << x[i] << ", " << y[i] << ", " << yh[i] << "\n";
	}


	output.close();
}
