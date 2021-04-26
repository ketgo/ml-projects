#include "ann.hpp"
#include <iostream>

#ifdef ANN_DEBUG
#include <cstdlib>
#endif

// TODO Exception Handling
ann_network::ann_network() {
}

ann_network::ann_network(std::vector<int>& net, float r, int e, activation fn, activation diff_fn) {
	initialize(net, r, e, fn, diff_fn);
}

void ann_network::initialize(std::vector<int>& net, float r, int e, activation fn, activation diff_fn) {
	rate = r;
	epoch = e;
	act_fn = fn;
	diff_act_fn = diff_fn;
	layers.resize(net.size()-1);	// not including ibput layer
	
	for(int i=0; i<layers.size(); i++) {
		layers[i].input.resize(net[i]+1);
		
		layers[i].z.resize(net[i+1]);
		
		layers[i].output.resize(net[i+1]);
		
		layers[i].weights.resize(net[i+1]);
		for(int j=0; j<layers[i].weights.size(); j++) {
			layers[i].weights[j].resize(net[i]+1);
			for(int k=0; k<layers[i].weights[j].size(); k++) {
				layers[i].weights[j][k] = float(rand())/float(RAND_MAX);
			}
		}
		
		layers[i].gradient.resize(net[i+1]);
		for(int j=0; j<layers[i].gradient.size(); j++) {
			layers[i].gradient[j].resize(net[i]+1);
		}
		
		layers[i].delta.resize(net[i+1]);
	}
}

void ann_network::_predict(std::vector<float>& in, int l) {
// The function predicts the output for input "in" using recursion.

	if(l<layers.size()) {
#ifdef ANN_DEBUG		
		std::cout<<"[predict] LAYER: "<<l<<std::endl;
#endif

		for(int i=0; i<in.size(); i++) {
			layers[l].input[i] = in[i];
		}
		layers[l].input.back() = 1.0;

#ifdef ANN_DEBUG		
		std::cout<<"[predict] Input: ";
		for(int i=0; i<layers[l].input.size(); i++) {
			std::cout<<layers[l].input[i]<<", ";
		}
		std::cout<<std::endl;
#endif
	
		for(int i=0; i<layers[l].weights.size(); i++) {
			layers[l].z[i] = 0.0;
			for(int j=0; j<layers[l].weights[i].size(); j++) {
				layers[l].z[i] += layers[l].weights[i][j]*layers[l].input[j];
			}
			layers[l].output[i] = act_fn(layers[l].z[i]);
		}

#ifdef ANN_DEBUG		
		std::cout<<"[predict] Output: ";
		for(int i=0; i<layers[l].output.size(); i++) {
			std::cout<<layers[l].output[i]<<", ";
		}
		std::cout<<std::endl;
#endif
		
		_predict(layers[l].output, l+1);
	}
}

void ann_network::predict(std::vector<float>& out, std::vector<float>& in) {
	_predict(in, 0);
	for(int i=0; i<out.size(); i++) {
		out[i] = layers.back().output[i];
	}
}

void ann_network::_fit(int l) {
// The function calculates the gradidient of the loss function with respect to the weights.

	float sum;
	if(l>=0) {
#ifdef ANN_DEBUG		
		std::cout<<"[fit] LAYER: "<<l<<std::endl;
#endif
		// Calculating the delta for the layer
		for(int i=0; i<layers[l].delta.size(); i++) {
			sum = 0.0;
			for(int j=0; j<layers[l+1].delta.size(); j++) {
				sum += layers[l+1].delta[j] * layers[l+1].weights[j][i];
			}
			layers[l].delta[i] = sum * diff_act_fn(layers[l].z[i]);
		}
		
#ifdef ANN_DEBUG		
		std::cout<<"[fit] Delta: ";
		for(int i=0; i<layers[l].delta.size(); i++) {
			std::cout<<layers[l].delta[i]<<", ";
		}
		std::cout<<std::endl;
#endif

		// Calculating the gradient for the layer
		for(int i=0; i<layers[l].gradient.size(); i++) {
			for(int j=0; j<layers[l].gradient[i].size(); j++) {
				layers[l].gradient[i][j] = layers[l].input[j] * layers[l].delta[i];
			}
		}
		
#ifdef ANN_DEBUG		
		std::cout<<"[fit] Gradient:"<<std::endl;
		for(int i=0; i<layers[l].gradient.size(); i++) {
			for(int j=0; j<layers[l].gradient[i].size(); j++) {
				std::cout<<layers[l].gradient[i][j]<<", ";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
#endif
		
		_fit(l-1);
	}
}

void ann_network::fit(std::vector<float>& target, std::vector<float>& in) {
	int l, count = 0;
	
	while(count<epoch) {
		_predict(in, 0);	// Set outputs of each layers for every itterations
		
		l = layers.size() -1;	// index for output layer

#ifdef ANN_DEBUG		
		std::cout<<"[fit] LAYER: "<<l<<std::endl;
#endif

		// Calculating the delta for output neuron
		for(int i=0; i<layers[l].delta.size(); i++) {
			layers[l].delta[i] = (layers[l].output[i] - target[i]) * diff_act_fn(layers[l].z[i]);

#ifdef ANN_DEBUG
			std::cout<<"[fit] ERROR: "<<(layers[l].output[i] - target[i])<<std::endl;
#endif

		}
		
#ifdef ANN_DEBUG		
		std::cout<<"[fit] Delta: ";
		for(int i=0; i<layers[l].delta.size(); i++) {
			std::cout<<layers[l].delta[i]<<", ";
		}
		std::cout<<std::endl;
#endif

		// Calculating the gradient for output neuron
		for(int i=0; i<layers[l].gradient.size(); i++) {
			for(int j=0; j<layers[l].gradient[i].size(); j++) {
				layers[l].gradient[i][j] = layers[l].input[j] * layers[l].delta[i];
			}
		}
		
#ifdef ANN_DEBUG		
		std::cout<<"[fit] Gradient:"<<std::endl;
		for(int i=0; i<layers[l].gradient.size(); i++) {
			for(int j=0; j<layers[l].gradient[i].size(); j++) {
				std::cout<<layers[l].gradient[i][j]<<", ";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
#endif
	
		_fit(l-1);
	
		// Updating the weights
		for(int i=0; i<layers.size(); i++) {
			for(int j=0; j<layers[i].weights.size(); j++) {
				for(int k=0; k<layers[i].weights[j].size(); k++) {
					layers[i].weights[j][k] -= rate * layers[i].gradient[j][k];
				}
			}
		}
		
		count++;
	}
}
