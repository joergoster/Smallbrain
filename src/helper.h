#pragma once

#include <algorithm>
#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>  // for is_same_v
#include <vector>

#include "types.h"

/// @brief Gets the file index of the square where 0 is the a-file
/// @param sq
/// @return the file of the square
inline constexpr File squareFile(Square sq) { return File(sq & 7); }

/// @brief  distance between two squares
/// @param a
/// @param b
/// @return
uint8_t squareDistance(Square a, Square b);

namespace builtin {
/// @brief least significant bit instruction
/// @param mask
/// @return the least significant bit as the Square
Square lsb(U64 mask);

/// @brief most significant bit instruction
/// @param mask
/// @return the most significant bit as the Square
Square msb(U64 mask);

/// @brief Counts the set bits
/// @param mask
/// @return the count
int popcount(U64 mask);

/// @brief remove the lsb and return it
/// @param mask
/// @return the lsb
Square poplsb(U64 &mask);

#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
template <int rw = 0>
void prefetch(const void *addr) {
#if defined(__INTEL_COMPILER)
    __asm__("");
#endif
#ifdef __GNUC__
    _mm_prefetch((char *)addr, _MM_HINT_T0);
#else
    _mm_prefetch((char *)addr, 0);
#endif
}
#else
template <int rw = 0>
void prefetch(const void *addr) {
    __builtin_prefetch(addr, 0, rw);
}
#endif
}  // namespace builtin

// returns diagonal of given square
inline constexpr uint8_t diagonalOf(Square sq) { return 7 + square_rank(sq) - squareFile(sq); }

// returns anti diagonal of given square
inline constexpr uint8_t antiDiagonalOf(Square sq) { return square_rank(sq) + squareFile(sq); }

uint8_t manhattenDistance(Square sq1, Square sq2);

/// @brief get the color of the square
/// @param square
/// @return light = true
bool getSquareColor(Square square);

/// @brief get the piecetype of a piece
/// @param piece
/// @return the piecetype
inline constexpr PieceType typeOfPiece(const Piece piece) { return PieceToPieceType[piece]; }

[[maybe_unused]] static std::atomic<int64_t> means[2];
[[maybe_unused]] static std::atomic<int64_t> min[2];
[[maybe_unused]] static std::atomic<int64_t> max[2];

[[maybe_unused]] void mean_of(int v);
[[maybe_unused]] void min_of(int v);
[[maybe_unused]] void max_of(int v);

void print_mean();

/// @brief adjust the outputted score
/// @param score
/// @return a new score used for uci output
std::string outputScore(int score);

/// @brief prints the new uci info
/// @param score
/// @param depth
/// @param seldepth
/// @param nodes
/// @param tbHits
/// @param time
/// @param pv
void uciOutput(int score, int depth, uint8_t seldepth, U64 nodes, U64 tbHits, int time,
               std::string pv, int hashfull);

/// @brief makes a Piece from only the piece type and color
/// @param type
/// @param c
/// @return new Piece
Piece makePiece(PieceType type, Color c);

/// @brief prints any bitboard
/// @param bb
void printBitboard(U64 bb);

bool sameColor(int sq1, int sq2);
