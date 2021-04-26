#include <iostream>
#include <limits>
#include "board.hpp"
#include "rl.hpp"

void play(rl&);

int main() {
	rl_ann r;
	while(1) {
		play(r);
	}
	return 0;
}

void play(rl &r) {
	board b;
	int pos_x = 0, pos_o = 0, who_won = 0, n_state[3][3], o_state[3][3];
	bool p = true;
	float reward = 0.0;
	
	b.get_state(o_state);
	b.get_state(n_state);
	
	while(1) {
		if(p == true) {
			b.print_board();
			std::cout<<"Enter Move For X: ";
			std::cin >> pos_x;
			b.set_pos(pos_x, p);
			b.get_state(n_state);
		} else {
			b.get_state(o_state);
			pos_o = r.policy(o_state);
			b.set_pos(pos_o, p);
			b.get_state(n_state);
		}
		
		who_won = b.who_won();
		if(who_won == -1) {
			reward = 1;
			r.update_Q(o_state, pos_o, n_state, reward);
			break;
		} else if(who_won == 1) {
			reward = -1;
			r.update_Q(o_state, pos_o, n_state, reward);
			break;
		} else if(who_won == 0) {
			reward = -0.1;
			r.update_Q(o_state, pos_o, n_state, reward);
			break;
		} else {
			reward = 0;
			if(p == true) {
				r.update_Q(o_state, pos_o, n_state, reward);
			}
			p = !p;
		}
	}
	
	b.print_board();
	if(who_won == 0) {
		std::cout<<"IT'S A DRAW!"<<std::endl;
	}
	if(who_won == 1) {
		std::cout<<"X WON!"<<std::endl;
	}
	if(who_won == -1) {
		std::cout<<"O WON!"<<std::endl;
	}
}