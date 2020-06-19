#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


class Vect{
	vector<double> v;

public:
	int length(){
		return v.size();
	}

	void append(double x){
		v.push_back(x);
	}

	double sum(){
		double s = 0;
		for (vector<double>::iterator i = v.begin(); i != v.end(); i++){
			s += *i;
		}
		return s;
	}

	double operator[](int x){
		return v[x];
	}

	Vect operator+(Vect& v1){
		if (this->length() != v1.length()){
			cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			for(int i = 0; i < this->length(); i++){
				v2.append(v[i] + v1[i]);
			}
			return v2;
		}
	}

	Vect operator+(double x){
		Vect v2;
		for(int i = 0; i < this->length(); i++){
			v2.append(v[i] + x);
		}
		return v2;
	}

	Vect operator-(Vect& v1){
		if (this->length() != v1.length()){
			cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			for(int i = 0; i < this->length(); i++){
				v2.append(v[i] - v1[i]);
			}
			return v2;
		}
	}

	Vect operator-(double x){
		Vect v2;
		for(int i = 0; i < this->length(); i++){
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

	Vect operator*(double x){
		Vect v2;
		for (vector<double>::iterator i = v.begin(); i != v.end(); i++){
			v2.append((*i)*x);
		}
		return v2;
	}

	/**/Vect square(){
		Vect v2;
		for (vector<double>::iterator i = v.begin(); i != v.end(); i++){
			v2.append((*i)*(*i));
		}
		return v2;
	}

	/**/void disp(){
		for (vector<double>::iterator i = v.begin(); i != v.end(); i++){
			cout << *i << " ";
		}
		cout << "\n";
	}

};



int main(){
	const double eps = 1e-6, alp = 0.01;	//Error, Epsilon and Alpha
	double err = 1, temp;
	int iter = 0, epochs = 5000;
	
	double w1 = 0, w0 = 0;
	Vect x, y;
	for (int i = 0; i < 10; ++i){
		x.append(i);
	}
	y = x*5 + 3;	//Ground truth

	Vect J, yh;	//Loss funcion and the hypothesis function
	yh = ((x*w1) + w0);
	J.append((((y - yh).square()).sum())/20);

	while (err > eps && iter < epochs){
		double delJ0 = -((y - yh).sum())/10;
		double delJ1 = -(((x*(y - yh)).sum()))/10;

		w0 -= alp*delJ0;
		w1 -= alp*delJ1;

		iter++;
		yh = ((x*w1) + w0);
		J.append((((y - yh).square()).sum())/20);
		temp = J[iter] - J[iter-1];
		err = (temp > 0) ? temp : -temp;

	}

	cout << J[iter] << " " << w1 << " " << w0 << " " << iter << " " << err;

}
