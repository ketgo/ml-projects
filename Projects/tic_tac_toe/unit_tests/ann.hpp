#ifndef ANN_HPP
#define ANN_HPP

#include <vector>

typedef float (*activation)(float);

struct ann_layer{
	std::vector<float> output;
	std::vector<float> z;
	std::vector<float> input;
	std::vector<std::vector<float>> weights;
	
	// training variables
	std::vector<std::vector<float>> gradient;
	std::vector<float> delta;
};

// Constructs a fully connected network
class ann_network{
	private:
		std::vector<ann_layer> layers;
		float rate;
		int epoch;
		activation act_fn;					// activation function of the neurons
		activation diff_act_fn;				// differentiation of the activation function. Note: The current implimentation takes that as input for the class. Feature version should complute this internally.
		
		void _predict(std::vector<float>& in, int l);
		void _fit(int l);
	public:
		ann_network(std::vector<int>& net, float r, int e, activation fn, activation diff_fn);
		void predict(std::vector<float>& out, std::vector<float>& in);
		void fit(std::vector<float>& target, std::vector<float>& in);
};

#endif