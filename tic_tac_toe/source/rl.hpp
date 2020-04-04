#ifndef RL_HPP
#define RL_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include "ann.hpp"

// Abstract Class
class rl {
	public:
		virtual unsigned int policy(int state[3][3]) = 0;														// get optimum action for the state "state[3][3]" based on a policy
		virtual void update_Q(int c_state[3][3], unsigned int action, int n_state[3][3], float reward) = 0;		// update Q value for state action pair resulting in new state "n_state[3][3]", and reciving a reward of "reward". The action is found from the policy function.
};

// Class to perform reinforcement learning using hash tables
class rl_hash: public rl {
	private:
		std::unordered_map<std::string, float> Q;
		
		float get_Q(std::string key);																// get Q value for state action pair key "key"
		std::string get_key(int state[3][3], unsigned int action);									// get key for state action pair "state[3][3]" and "action"
	public:
		unsigned int policy(int state[3][3]);														// get optimum action for the state "state[3][3]" based on a policy
		void update_Q(int c_state[3][3], unsigned int action, int n_state[3][3], float reward);		// update Q value for state action pair resulting in new state "n_state[3][3]", and reciving a reward of "reward". The action is found from the policy function.
};

// Class to perform reinforcement learning using Artificial Neural Networks
class rl_ann: public rl{
	private:
		ann_network net;																			// ANN
		
		float get_Q(int state[3][3],  unsigned int action);											// get Q value for state action pair
	public:
		rl_ann();																					// Constructor for setting up the neural network
		unsigned int policy(int state[3][3]);														// get optimum action for the state "state[3][3]" based on a policy
		void update_Q(int c_state[3][3], unsigned int action, int n_state[3][3], float reward);		// update Q value for state action pair resulting in new state "n_state[3][3]", and reciving a reward of "reward". The action is found from the policy function.
};

#endif