#include <iostream>
#include <vector>

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
		return accumulate(v.begin(), v.end(), 0);
	}

	double operator[](int& x){
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

	Vect operator*(double x){
		Vect v2;
		for (std::vector<double>::iterator i = v.begin(); i != v.end(); i++){
			v2.append((*i)*x);
		}
		return v2;
	}

	/**/void disp(){
		for (std::vector<double>::iterator i = v.begin(); i != v.end(); i++){
			cout << *i << " ";
		}
		cout << "\n";
	}

};



int main(){
	

}
