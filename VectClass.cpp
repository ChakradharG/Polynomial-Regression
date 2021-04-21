#include <iostream>
#include <array>
#include <cmath>
#include <chrono>


void checkLength(const int& l1, const int& l2){
	if (l1 != l2){
		std::cout << "Vectors are not equal in length";
		exit(1);
	}
}

class Vect{
	double* v;
	double temp;

public:
	int length;
	static std::chrono::duration <float> dur;
	static int cnt;

	~Vect(){
		cnt--;
		auto t0 = std::chrono::high_resolution_clock::now();
		delete[] v;
		auto t1 = std::chrono::high_resolution_clock::now();
		dur += (t1 - t0);
	}

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
			stream >> v[i];
		}
	}

	double& operator[](const int& index) const{
		return v[index];
	}

	void operator=(const Vect& v1){
		checkLength(length, v1.length);

		for (int i = 0; i < length; i++){
			v[i] = v1[i];
		}
	}

	void operator=(const double& x){
		for (int i = 0; i < length; i++){
			v[i] = x;
		}
	}

	void operator+=(const Vect& v1){
		checkLength(length, v1.length);

		for (int i = 0; i < length; i++){
			v[i] += v1[i];
		}
	}

	void operator-=(const Vect& v1){
		checkLength(length, v1.length);

		for (int i = 0; i < length; i++){
			v[i] -= v1[i];
		}
	}

	Vect& operator*(const Vect& v1){
		checkLength(length, v1.length);

		for(int i = 0; i < length; i++){
			v[i] *= v1[i];
		}
		return *this;
	}

	Vect& operator*(const double& x){
		for (int i = 0; i < length; i++){
			v[i] *= x;
		}
		return *this;
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
	
	void d(){
		std::cout << "\n\nDestructor Time: " << dur.count() * 1000 << " ms";
		std::cout << "\nObject Count: " << cnt;
	}
};
auto t = std::chrono::high_resolution_clock::now();
std::chrono::duration <float> Vect::dur = t-t;
int Vect::cnt = 0;
