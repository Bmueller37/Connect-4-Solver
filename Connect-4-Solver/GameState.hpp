#pragma once
#ifndef HEADER_INCLUDED_
#define HEADER_INCLUDED_
#include <cstdint>
#include <string>
/*
This GameState class uses modified version of Pascal Pon's version of bitmask encoding to effeciently represent a Connect 4 Board
*/


class GameState {
public:
	GameState() : board{ 0 }, mask{ 0 }, moves{ 0 } {};
	GameState(const GameState& g1);

	void move(int col);
	bool isWinningMove(int col) const;
	bool isWin();
	bool isPlayable(int col);
	int numMoves();
	void generate(std::string moves);
	uint64_t key() const;
	
	private:
	//current player will always be whoever has next move
	uint64_t board;
	uint64_t mask;
	int moves;

	static bool alignment(uint64_t pos) {
		
		uint64_t m = pos & (pos >> (6 + 1));
		if (m & (m >> (2 * (6 + 1)))) return true;

		
		m = pos & (pos >> 6);
		if (m & (m >> (2 * 6))) return true;

		
		m = pos & (pos >> (6 + 2));
		if (m & (m >> (2 * (6 + 2)))) return true;

		
		m = pos & (pos >> 1);
		if (m & (m >> 2)) return true;

		return false;
	}


	static uint64_t top_mask(int col) {
		return (UINT64_C(1) << (6 - 1)) << col * (6 + 1);
	}

	
	static uint64_t bottom_mask(int col) {
		return UINT64_C(1) << col * (6 + 1);
	}

	
	static uint64_t column_mask(int col) {
		return ((UINT64_C(1) << 6) - 1) << col * (6 + 1);
	}



};

#endif