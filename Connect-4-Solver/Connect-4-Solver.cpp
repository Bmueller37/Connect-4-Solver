// Connect-4-Solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameState.hpp"
#include <bitset>
#include <string>


int minimax(GameState& g, int& best) {
	
	if (g.numMoves() == 42) {
		return 0;
	}

	for (int x = 0; x < 7; x++) 
		if (g.isPlayable(x) && g.isWinningMove(x))
			return (7 * 6 + 1 - g.numMoves()) / 2;

	
	int max = -42; //worse possible score
	int b = -5000;
	for (int i = 0; i < 7; i++) {
		if (g.isPlayable(i)) {
			GameState g2(g);
			g2.move(i);

			int score = -minimax(g2, best);
			
			if (score > max)
			{
				b = i;
				max = score;
			}

		}
	}
	best = b;
	return max;
}

int main()
{
    GameState t;
	t.generate("17516442226766");
	int best = 0;
	std::cout << minimax(t, best) << std::endl;
	std::cout << best << std::endl;
    return 0;
}
