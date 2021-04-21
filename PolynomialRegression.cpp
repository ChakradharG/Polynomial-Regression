/*
Values in lines containing '//^' can be tweaked
in order to get a more accurate output.
*/
#include <fstream>
#include <vector>
#include <time.h>
#include "VectClass.cpp"

using namespace std;


void readData(int&, Vect&, Vect&, int&, double&);
void writeData(Vect&, Vect&, Vect&, int&);


int main(){
	double err = 1, eps = 1e-6, alp;	//^eps = stopping criterion epsilon, alp = learning rate alpha
	int iter = 0, order, len, denom, epochs = 10000;	//^
	Vect x, y, yh, yDiff;	//x,y = data points, yh = hypothesis function, yDiff = y - yh
	vector<double> J;	//J = loss function

	readData(len, x, y, order, alp);	//Read data from file, comment this line and uncomment the following block to give data through the terminal
	yh.initialize(len);
	yDiff.initialize(len);

	/*This block is to get the inputs from the terminal (user)*/
	// cout << "Length of the vector? ";
	// cin >> len;

	// x.initialize(len);
	// cout << "x: ";
	// x.getValues(cin, len);
	// y.initialize(len);
	// cout << "y: ";
	// y.getValues(cin, len);

	// cout << "Order of the output polynomial? ";
	// cin >> order;

	// cout << "Learning rate? ";	//Uncomment to give custom learning rate at runtime
	// cin >> alp;

	denom = 10 * len;	//^
	alp = 5 * pow(10, -order);	//Comment to give custom learning rate at runtime
	order++;

	double* W = new double[order];	//Weight matrix
	double* delJ = new double[order];	//Partial derivatives of J
	srand(time(0));
	for (int i = 0; i < order; i++){	//Initializing weights randomly
		W[i] = ((double) rand()/(RAND_MAX));
	}

	yh = W[0];	//Assigning bias to every element of yh
	for (int i = 1; i < order; i++){
		yh += (x^i) * W[i];
	}

	yDiff = y;
	yDiff -= yh;

	J.push_back((yDiff^2).sum()/(2*len));

	while (err > eps && iter < epochs){
		for (int i = 0; i < order; i++){
			delJ[i] = -(((x^i)*yDiff).sum())/denom;
			W[i] -= alp * delJ[i];
		}

		iter++;

		yDiff += yh;
		yh = W[0];	//Assigning bias to every element of yh
		for (int i = 1; i < order; i++){
			yh += (x^i) * W[i];
		}
		yDiff -= yh;

		J.push_back((yDiff^2).sum()/(2*denom));
		err = J[iter] - J[iter-1];
		alp = (err > 0) ? alp/2 : alp;	//^
		err = (err < 0) ? -err : err;

	}

	writeData(x, y, yh, len);

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
