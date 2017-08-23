#include <algorithm>
#include <iostream>
#include <vector>

/*
 * Pseudocode:
 *
 * - Look at all the cells involved in threats and posibilities. Sort them by
 *   a heuristicall score and keep the top 20 (or another resonable number).
 *
 * - Alternative: Go through each cell, place the piece there, and compute a
 *   heuristical score for the move by looking at the number of threats, and
 *   opportunities. Keep only the top 20 moves (or another resonable number).
 *
 * - For each move, go a level deeper, and search again for the best moves.
 *   After reaching the maximum depth level return the score for the best move.
 */

using std::abs;
using std::all_of;
using std::begin;
using std::cerr;
using std::cout;
using std::end;
using std::endl;
using std::string;
using std::transform;
using std::vector;

typedef signed char player_t;
typedef unsigned char move_t;
struct threat_t {
    player_t pattern[10];
    bool mask[10];
    int pattern_len;
    int score;
};

const move_t size = 15;
const move_t cells = size * size;
const player_t black = 1;
const player_t white = -1;
const player_t blank = 0;

#include "threats.h"

#define CHECK_AND_ADD_THREAT(format) \
    is_threat = true; \
    for (int k = 0; k < pattern_len; k++) { \
        if (board[format] != pattern[k]) { \
            is_threat = false; \
            break; \
        } \
    } \
    if (is_threat) { \
        for (int k = 0; k < pattern_len; k++) { \
            if (mask[k]) { \
                threats.push_back(format); \
            } \
        } \
    }

void getThreats(
    vector<move_t> &threats,
    player_t (&board)[cells],
    player_t *pattern,
    bool *mask,
    int pattern_len
) {
    int max_len = size - pattern_len;
    bool is_threat = true;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= max_len; j++) {
            // Horizontally.
            CHECK_AND_ADD_THREAT((i * size + j + k));
            // Vertically.
            CHECK_AND_ADD_THREAT((j + k) * size + i);
        }
    }

    for (int i = 0; i <= max_len; i++) {
        for (int j = 0; j <= i; j++) {
            // Diagonal 1 and below.
            CHECK_AND_ADD_THREAT((i + k) * size + j + k);
            // Diagonal 2 and below.
            CHECK_AND_ADD_THREAT((i + k + 1) * size - j - k - 1);
        }
    }

    for (int i = 0; i < max_len; i++) {
        for (int j = i + 1; j <= max_len; j++) {
            // Above diagonal 1.
            CHECK_AND_ADD_THREAT((i + k) * size + j + k);
            // Above diagonal 2.
            CHECK_AND_ADD_THREAT((i + k + 1) * size - j - k - 1);
        }
    }
}

void getMoves(vector<move_t>& moves, player_t (&board)[cells], player_t player) {
    // If the board is blank, the best move is the center cell.
    if (all_of(begin(board), end(board), [](player_t x) { return x == blank; })) {
        moves.push_back(cells / 2);
        return;
    }

    vector<move_t> threats;

    for (int i = 0; i < n_threats; i++) {
        threat_t th = possible_threats[player + 1][i];
        threats.clear();

        getThreats(threats, board, th.pattern, th.mask, th.pattern_len);

        if (threats.size()) {
            for (auto x: threats) {
                moves.push_back(x);
            }
            return;
        }
    }

    // Out of ideas.
    moves.push_back(255);
}

int getScore(player_t (&board)[cells], player_t player) {
    int ret = 0;

    vector<move_t> threats;

    for (int i = 0; i < n_threats; i++) {
        threat_t th = possible_threats[player + 1][i];
        threats.clear();

        getThreats(threats, board, th.pattern, th.mask, th.pattern_len);

        if (threats.size() && abs(th.score) >= 500000) {
            return th.score;
        }

        ret += threats.size() * th.score;
    }

    return ret;
}

void cmdPlay(player_t (&board)[cells], player_t player) {
    vector<move_t> moves;

    getMoves(moves, board, player);

    for (auto x : moves) {
        cout << (int) x << ' ';
    }
    cout << endl;
}

void cmdScore(player_t (&board)[cells], player_t player) {
    cout << getScore(board, player) << endl;
}

void cmdScores(player_t (&board)[cells], player_t player) {
    vector<int> scores;

    for (int i = 0; i < cells; i++) {
        if (board[i]) {
            cout << "0 ";
        } else {
            board[i] = player;
            cout << getScore(board, player) << ' ';
            board[i] = 0;
        }
    }

    cout << endl;
}

void cmdThreats(
    player_t (&board)[cells],
    player_t *pattern,
    bool *mask,
    int pattern_len
) {
    vector<move_t> threats;

    getThreats(threats, board, pattern, mask, pattern_len);

    for (auto x : threats) {
        cout << (int) x << ' ';
    }

    cout << endl;
}

void cmdWon(player_t (&board)[cells]) {
    player_t xPattern[5] = {1, 1, 1, 1, 1};
    player_t oPattern[5] = {-1, -1, -1, -1, -1};
    bool mask[5] = {true, false, false, false, false};

    vector<move_t> threats;

    getThreats(threats, board, xPattern, mask, 5);
    if (threats.size() > 0) {
        cout << "x" << endl;
        return;
    }

    threats.clear();

    getThreats(threats, board, oPattern, mask, 5);
    if (threats.size() > 0) {
        cout << "o" << endl;
        return;
    }

    cout << "." << endl;
}

int main(int argc, char **argv) {
    vector<string> args(argv + 1, argv + argc);
    string cmd = args[0];

    if (argc < 3) {
        cerr << "Bad number of arguments." << endl;
        return 1;
    }

    if (
        cmd == "play" || cmd == "threats" || cmd == "won" || cmd == "score" ||
        cmd == "scores"
    ) {
        player_t board[cells];

        // Transform board string to -1, 0, and 1.
        transform(args[1].begin(), args[1].end(), board, [](player_t x) {
            return x == 'x' ? black : x == 'o' ? white : blank;
        });

        if (cmd == "play" || cmd == "score" || cmd == "scores") {
            player_t player = args[2] == "x" ? black : white;
            if (cmd == "play") {
                cmdPlay(board, player);
            } else if (cmd == "score") {
                cmdScore(board, player);
            } else if (cmd == "scores") {
                cmdScores(board, player);
            }
        } else if (cmd == "threats") {
            player_t *pattern = new player_t[args[2].length()];
            bool *mask = new bool[args[2].length()];
            // Transform pattern string to -1, 0, and 1.
            transform(args[2].begin(), args[2].end(), pattern, [](player_t x) {
                return x == 'x' ? black : x == 'o' ? white : blank;
            });
            transform(args[3].begin(), args[3].end(), mask, [](char x) {
                return x == 'm';
            });
            cmdThreats(board, pattern, mask, args[2].length());
            delete pattern;
            delete mask;
        } else if (cmd == "won") {
            cmdWon(board);
        }

        return 0;
    }

    cerr << "Unknown command." << endl;
    return 1;
}
