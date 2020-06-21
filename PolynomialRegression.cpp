/*
Values in lines containing '//^' can be tweaked
in order to get a more accurate output.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;


class Vect{
	vector<double> v;
	double temp;

public:
	inline int length(){
		return v.size();
	}

	void append(const double& x){
		v.push_back(x);
	}

	double sum(){
		temp = 0;
		for (int i = 0; i < this->length(); i++){
			temp += v[i];
		}
		return temp;
	}

	void getValues(istream& stream, const int& n){
		for (int i = 0; i < n; i++){
			stream >> temp;
			v.push_back(temp);
		}
	}

	double operator[](const int& x){
		return v[x];
	}

	Vect operator+(Vect v1){
		if (this->length() != v1.length()){
			cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			for (int i = 0; i < this->length(); i++){
				v2.append(v[i] + v1[i]);
			}
			return v2;
		}
	}

	Vect operator+(const double& x){
		Vect v2;
		for (int i = 0; i < this->length(); i++){
			v2.append(v[i] + x);
		}
		return v2;
	}

	Vect operator-(Vect v1){
		if (this->length() != v1.length()){
			cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			for (int i = 0; i < this->length(); i++){
				v2.append(v[i] - v1[i]);
			}
			return v2;
		}
	}

	Vect operator-(const double& x){
		Vect v2;
		for (int i = 0; i < this->length(); i++){
			v2.append(v[i] - x);
		}
		return v2;
	}

	Vect operator*(Vect v1){
		if (this->length() != v1.length()){
			cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			for(int i = 0; i < this->length(); i++){
				v2.append(v[i] * v1[i]);
			}
			return v2;
		}
	}

	Vect operator*(const double& x){
		Vect v2;
		for (int i = 0; i < this->length(); i++){
			v2.append(v[i] * x);
		}
		return v2;
	}

	Vect operator^(const int& x){
		Vect v2;
		for (int i = 0; i < this->length(); i++){
			v2.append(pow(v[i], x));
		}
		return v2;
	}

	void disp(){
		for (int i = 0; i < this->length(); i++){
			cout << v[i] << " ";
		}
		cout << "\n";
	}

};


void readData(int&, Vect&, Vect&, int&, double&);
void writeData(Vect&, Vect&, Vect&, int&);


int main(){
	double err = 1, eps = 1e-6, alp;	//^eps = stopping criterion epsilon, alp = learning rate alpha
	int iter = 0, order, len, denom, epochs = 10000;	//^
	Vect x, y, yh, J;	//x,y = data points, yh = hypothesis function, J = loss function

	readData(len, x, y, order);

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
	alp = 5 * pow(10, -order);
	order++;

	double* W = new double[order];	//Weight matrix
	double* delJ = new double[order];	//Partial derivatives of J
	srand(time(0));
	for (int i = 0; i < order; i++){	//Initializing weights randomly
		W[i] = ((double) rand()/(RAND_MAX));
	}

	yh = (x^0) * W[0];
	for (int i = 1; i < order; i++){
		yh = yh + (x^i) * W[i];
	}
	
	J.append(((y - yh)^2).sum()/(2*len));

	while (err > eps && iter < epochs){
		for (int i = 0; i < order; i++){
			delJ[i] = -(((x^i)*(y - yh)).sum())/denom;
			W[i] -= alp * delJ[i];
		}

		iter++;
		yh = (x^0) * W[0];
		for (int i = 1; i < order; i++){
			yh = yh +  (x^i) * W[i];
		}

		J.append(((y - yh)^2).sum()/(2*denom));
		err = J[iter] - J[iter-1];
		if (err > 0){
			alp /= 2;	//^
		}
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
	x.getValues(input, len);
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