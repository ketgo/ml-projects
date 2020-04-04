#ifndef BOARD_HPP
#define BOARD_HPP

class board {
	private:
		// Stores state of the board.
		// Each position takes values: 1-X, -1-O, 0-empty.
		int state[3][3];
	public:
		// Constructor
		board();
		
		// Set X or O at postion index idx.
		// p = True -> X
		// p = False -> O
		int set_pos(const unsigned int pos, const bool p);
		
		// check if pos is set
		bool is_set(const unsigned int pos);
		
		// Check who won: -1 - still playing, 0 - draw, 1 - X win, 2 - O win.
		int who_won();
		
		// Print board
		void print_board();
		
		// get state
		void get_state(int s[3][3]);
		
		// set state
		void set_state(int s[3][3]);
};

#endif