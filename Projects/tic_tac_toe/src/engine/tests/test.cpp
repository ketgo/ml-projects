#include <iostream>
#include <cmath>
#include "ann.hpp"

using namespace std;

// Logistic activation function
float logistic(float z) {
	return 1/(1 + exp(-z));
}

float diff_logistic(float z) {
	return logistic(z) * (1 - logistic(z));
}

// Hyperbolic tangent activation function
float hyperbolic(float z) {
	return tanh(z);
}

float diff_hyperbolic(float z) {
	return 1 - hyperbolic(z) * hyperbolic(z);
}

int main() {
	vector<int> n(5);
	n[0] = 2;	// Number of Inputs
	n[1] = 2;
	n[2] = 2;
	n[3] = 2;
	n[4] = 1;
	
	
	ann_network net(n, 1, 1000, hyperbolic, diff_hyperbolic);
	//Sample Points
	vector<float> in[4];
	vector<float> out[4], out_t;
	
	out_t.resize(1);
	for(int i=0; i<4; i++) {
		in[i].resize(2);
		out[i].resize(1);
	}
	
	in[0][0] = 1;
	in[0][1] = 1;
	out[0][0] = 0;
	in[1][0] = 1;
	in[1][1] = 0;
	out[1][0] = 1;
	in[2][0] = 0;
	in[2][1] = 1;
	out[2][0] = 1;
	in[3][0] = 0;
	in[3][1] = 0;
	out[3][0] = 0;
	
	cout<<"BEFORE:"<<endl;
	for(int i=0; i<4; i++) {
		net.predict(out_t, in[i]);
		for(int j=0; j<in[i].size(); j++) {
			cout<<in[i][j]<<" ";
		}
		cout<<out_t[0]<<" "<<out[i][0]<<endl;
	}
	
	// Traing
	int count=0;
	while(count<1000) {
		for(int i=0; i<4; i++) {
			net.fit(out[i], in[i]);
		}
		count++;
	}
	
	// NOTE: The implimentation does not perform batch learning! The neural network will fit to the last inputs provided.
	cout<<"AFTER:"<<endl;
	for(int i=0; i<4; i++) {
		net.predict(out_t, in[i]);
		for(int j=0; j<in[i].size(); j++) {
			cout<<in[i][j]<<" ";
		}
		cout<<out_t[0]<<" "<<out[i][0]<<endl;
	}
	
	return 0;
}
