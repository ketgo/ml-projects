#include "rl.hpp"
#include "board.hpp"
#include <cmath>

#ifdef RL_DEBUG
#include <iostream>
#endif

//################## Implimentation for reinforcement learving using Q values stored in hash table ####################
std::string rl_hash::get_key(int state[3][3], unsigned int action) {
	std::string key = "";
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			key += std::to_string(state[i][j]);
		}
	}
	key += std::to_string(action);
	
	return key;
}

float rl_hash::get_Q(std::string key) {
	float q = 0.0;
	std::unordered_map<std::string, float>::const_iterator itr = Q.find(key);
	
	if(itr == Q.end()) {
		Q.insert({key, q});
	} else {
		q = itr->second;
	}
	
	return q;
}

unsigned int rl_hash::policy(int state[3][3]) {
	float max = -100.0, q;
	unsigned int action = 0;
	board b;
	std::string key;
	
	// set state
	b.set_state(state);
	
	// Greedy policy
	for(unsigned int i=0; i<9; i++) {
		if(!b.is_set(i)) {
			key = get_key(state, i);
			q = get_Q(key);
			
#ifdef RL_DEBUG
			std::cout<<"[policy] "<<key<<"->"<<q<<std::endl;
#endif

			if(max < q) {
				max = q;
				action = i;
			}
		}
	}
	
	return action;
}

void rl_hash::update_Q(int c_state[3][3], unsigned int action, int n_state[3][3], float reward) {
	const float alpha = 0.7; // Update rate of Q values

	float max = -2.0, q;
	std::string key, new_key;
	board b;
	
	// Setting new state
	b.set_state(n_state);
	
	// Finding maximum Q values
	for(unsigned int i = 0; i<9; i++) {
		if(!b.is_set(i)) {
			new_key = get_key(n_state, i);
			q = get_Q(new_key);

#ifdef RL_DEBUG
			std::cout<<"[update] "<<new_key<<"->"<<q<<std::endl;
#endif

			if(max < q) {
				max = q;
			}
		}
	}
	// If no next maximum Q value found 
	if(max == -2.0) {
		max = 0.0;
	}
	
	// Geting state sction pair key for the current state
	key = get_key(c_state, action);
	
	// Updating the Q value for the current state
#ifdef RL_DEBUG
	std::cout<<"[update] Old: "<<Q[key];
#endif

	Q[key] = reward + alpha * max;
	
#ifdef RL_DEBUG
	std::cout<<", New: "<<Q[key]<<std::endl;
	for(int i=0; i<30; i++) {
		std::cout<<"#";
	}
	std::cout<<std::endl<<std::endl;
#endif	
	
}
//#################################################################################################################


//################# Implimentation for reinforcement learning using Q values obtained from ANN ####################
float act_fn(float z) {
	return std::tanh(z);
}

float diff_act_fn(float z) {
	return 1 - act_fn(z) * act_fn(z);
}

float rl_ann::get_Q(int state[3][3],  unsigned int action) {
	std::vector<float> in(10), out(1);
	
	// Set input
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			in[3*i + j] = state[i][j];
		}
	}
	in[9] = action;
	
	// get Q value
	net.predict(out, in);
	
	return out[0];
}

rl_ann::rl_ann() {
	std::vector<int> n(4);
	n[0] = 10;	// Number of Inputs
	n[1] = 10;
	n[2] = 10;
	n[3] = 1;
	
	net.initialize(n, 1, 50000, act_fn, diff_act_fn);
}

unsigned int rl_ann::policy(int state[3][3]) {
	float max = -100.0, q;
	unsigned int action = 10;	// Setting action to an invalid action.
	board b;
	
	// set state
	b.set_state(state);
	
	// Greedy policy
	for(unsigned int i=0; i<9; i++) {
		if(!b.is_set(i)) {
			q = get_Q(state, i);
			
#ifdef RL_DEBUG
			std::cout<<"[policy] ";
			for(int j=0; j<3; j++) {
				for(int k=0; k<3; k++) {
					std::cout<<state[j][k];
				}
			}
			std::cout<<i<<"->"<<q<<std::endl;
#endif

			if(max < q) {
				max = q;
				action = i;		// Get action with max Q value
			}
		}
	}
	
	return action;
}

void rl_ann::update_Q(int c_state[3][3], unsigned int action, int n_state[3][3], float reward) {
	const float alpha = 0.7;	// Update rate of Q values
	float max = -2.0, q;
	std::vector<float> n_Q(1), in(10);
	board b;
	
	// Setting new state
	b.set_state(n_state);
	
	// Finding maximum Q values
	for(unsigned int i = 0; i<9; i++) {
		if(!b.is_set(i)) {
			q = get_Q(n_state, i);

#ifdef RL_DEBUG
			std::cout<<"[update] ";
			for(int j=0; j<3; j++) {
				for(int k=0; k<3; k++) {
					std::cout<<n_state[j][k];
				}
			}
			std::cout<<i<<"->"<<q<<std::endl;
#endif

			if(max < q) {
				max = q;
			}
		}
	}
	// If no next maximum Q value found 
	if(max == -2.0) {
		max = 0.0;
	}
	
#ifdef RL_DEBUG
	std::cout<<"[update] Old: "<<get_Q(c_state, action);
#endif
	
	// Getting the new Q value for the current state acttion pairs
	n_Q[0] = reward + alpha * max;
	
#ifdef RL_DEBUG
	std::cout<<", New: "<<n_Q[0];
#endif	
	
	// training the neural network
	// Set input
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			in[3*i + j] = c_state[i][j];
		}
	}
	in[9] = action;
	
	net.fit(n_Q, in);

#ifdef RL_DEBUG
	std::cout<<", Updated: "<<get_Q(c_state, action)<<std::endl;
	for(int i=0; i<30; i++) {
		std::cout<<"#";
	}
	std::cout<<std::endl<<std::endl;
#endif	
}
//#################################################################################################################