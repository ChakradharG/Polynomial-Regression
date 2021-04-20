#include <iostream>
#include <array>
#include <cmath>


class Vect{
	double* v;
	double temp;

public:
	int length;

	// ~Vect(){
	// 	auto t0 = std::chrono::high_resolution_clock::now();
	// 	delete[] v;
	// 	auto t1 = std::chrono::high_resolution_clock::now();
	// 	dur += (t1 - t0);
	// }

	void initialize(const int& length){
		v = new double[length];
		this->length = length;
	}

	double sum(){
		temp = 0;
		for (int i = 0; i < length; i++){
			temp += v[i];
		}
		return temp;
	}

	void getValues(std::istream& stream, const int& n){
		for (int i = 0; i < n; i++){
			stream >> temp;
			v[i] = temp;
		}
	}

	double& operator[](const int& index){
		return v[index];
	}

	Vect operator+(Vect v1){
		if (length != v1.length){
			std::cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			v2.initialize(length);
			for (int i = 0; i < length; i++){
				v2[i] = v[i] + v1[i];
			}
			return v2;
		}
	}

	Vect operator+(const double& x){
		Vect v2;
		v2.initialize(length);
		for (int i = 0; i < length; i++){
			v2[i] = v[i] + x;
		}
		return v2;
	}

	Vect operator-(Vect v1){
		if (length != v1.length){
			std::cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			v2.initialize(length);
			for (int i = 0; i < length; i++){
				v2[i] = v[i] - v1[i];
			}
			return v2;
		}
	}

	Vect operator-(const double& x){
		Vect v2;
		v2.initialize(length);
		for (int i = 0; i < length; i++){
			v2[i] = v[i] - x;
		}
		return v2;
	}

	Vect operator*(Vect v1){
		if (length != v1.length){
			std::cout << "Vectors are not equal in length";
			exit(1);
		}
		else{
			Vect v2;
			v2.initialize(length);
			for(int i = 0; i < length; i++){
				v2[i] = v[i] * v1[i];
			}
			return v2;
		}
	}

	Vect operator*(const double& x){
		Vect v2;
		v2.initialize(length);
		for (int i = 0; i < length; i++){
			v2[i] = v[i] * x;
		}
		return v2;
	}

	Vect operator^(const int& x){
		Vect v2;
		v2.initialize(length);
		for (int i = 0; i < length; i++){
			v2[i] = pow(v[i], x);
		}
		return v2;
	}

	void disp(){
		for (int i = 0; i < length; i++){
			std::cout << v[i] << " ";
		}
		std::cout << "\n";
	}
};
