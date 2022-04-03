#include "GameState.hpp"
#include <iostream>
#include <bitset>
/*
This GameState class uses Pascal Pon's version of bitmask encoding to effeciently represent a connect 4 mask
*/


/*
GameState::GameState(std::string moveSet);
GameState::GameState(const GameState&);
*/

GameState::GameState(const GameState& g1)
{
	board = g1.board;
	mask = g1.mask;
	moves = g1.moves;
}

void GameState::move(int col)
{
	board ^= mask; //XOR 
	mask |= mask + (UINT64_C(1) << col * 7);
	moves++;
}

bool GameState::isWinningMove(int col) const
{
	uint64_t pos = board;
	pos |= (mask + bottom_mask(col)) & column_mask(col);
	return alignment(pos);
}

//Function is relative to player who just moved
bool GameState::isWin()
{
	uint64_t position = board ^ mask;

	uint64_t align = position & (position >> 7);
	if (align & (align >> 14)) return true; //horizontal

	align = position & (position >> 6);
	if (align & (align >> 12)) return true; //diag left

	align = position & (position >> 8);
	if (align & (align >> 16)) return true; //diag right

	align = position & (position >> 1);
	if (align & (align >> 2)) return true; //vertical

	return false;


}

bool GameState::isPlayable(int col)
{
	return (mask & (UINT64_C(1) << 5 << col * 7)) == 0;
}

int GameState::numMoves()
{
	return moves;
}

void GameState::generate(std::string moves)
{
	for (int i = 0; i < moves.length(); i++) {
		move(((int)moves[i]) - 49);
	}
	this->moves = moves.length();
}

uint64_t GameState::key() const
{
	return board + mask;
}
