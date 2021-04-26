#include <iostream>
#include "board.hpp"

board::board() {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			state[i][j] = 0;			// set positions to empty
		}
	}
}

int board::set_pos(const unsigned int pos, const bool p) {
	if(pos >= 9) {
		return -1;
	}
	
	int pos_x = pos / 3;
	int pos_y = pos % 3;
	
	if(state[pos_x][pos_y] != 0) {
		return -2;
	}
	
	if(p == true) {
		state[pos_x][pos_y] = 1;
	} else {
		state[pos_x][pos_y] = -1;
	}
	
	return 0;
}

bool board::is_set(const unsigned int pos) {
	if(state[pos/3][pos%3] == 0) {
		return false;
	}
	return true;
}

int board::who_won() {
	// Note: The following code checks who wins by computing sums of individual rows, columns and the two diagonals. 
	//		 If the sum = 3 then X wins, if sum = -3 then O wins, else it is a draw if all positions have been played.
	
	int sum_r[3] = {0, 0, 0};	// sum for individual rows
	int sum_c[3] = {0, 0, 0};	// sum for individual columns
	int sum_d[2] = {0, 0};	// sum for the two diagonals
	
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			sum_r[i] += state[i][j];
			sum_c[i] += state[j][i];
		}
		sum_d[0] += state[i][i];
		sum_d[1] += state[i][2-i];	// Note: it's 2-i and NOT 3-i since i = 0,1,2
	}
	
	// Check rows and columns
	for(int i=0; i<3; i++) {
		if((sum_r[i] == 3) || (sum_c[i] == 3)) {
			return 1;
		}
		if((sum_r[i] == -3) || (sum_c[i] == -3)) {
			return -1;
		}
	}
	
	// Check diagonals
	if((sum_d[0] == 3) || (sum_d[1] == 3)) {
		return 1;
	}
	if((sum_d[0] == -3) || (sum_d[1] == -3)) {
		return -1;
	}
	
	// check if all position played. If not, then the game is still not finished since non of the above conditions are ture.
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(state[i][j] == 0) {
				return -2;
			}
		}
	}
	
	// Since non of the above conditions are true, then the game is a draw.
	return 0;
}

void board::print_board() {
	std::cout<<std::endl;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(state[i][j] == 0) {
				std::cout<<3*i+j<<" ";
			} else if(state[i][j] == 1) {
				std::cout<<"X ";
			} else {
				std::cout<<"O ";
			}
		}
		std::cout<<std::endl;
	}
}

void board::get_state(int s[3][3]) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			s[i][j] = state[i][j];
		}
	}
}

void board::set_state(int s[3][3]) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			state[i][j] = s[i][j];
		}
	}
}