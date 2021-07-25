#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include "class.hpp"

using namespace std;
using namespace std::chrono;

unsigned expanded = 0;
unsigned generated = 0;

vector<state_t> child_vector(state_t state, PlayerData player) {
    vector<state_t> movement;
    state_t new_state;

    for (int i = 1; i <= 7; i++)
    {
        if (state.CheckDown(i))
        {
            new_state = state.MakeMove(player, i);
            movement.push_back(new_state);
        }
    }

    return movement;
}

int negamax_alphabeta(state_t state, int depth, int alpha, int beta,  PlayerData player1, PlayerData player2){
    
    //check_time(st);
    int score, val;
    ++generated;

    if (state.CheckDraw()) // DRAW
    {
        return 0;
    }



    // si no es estado terminal, expande
    ++expanded;
    score = numeric_limits<int>::min();
    // generando movimientos validos
    vector<state_t> child_states = child_vector(state, player1);
    
    for (state_t child : child_states) 
    {
        if (child.CheckWinner(player1)) {
            //child.BoardPrint();
            return (state.width*state.height+1 - state.moves)/2;
        }

        val = -negamax_alphabeta(child, depth - 1, -beta, -alpha, player2, player1);
        score = max(score,val);
        alpha = max(alpha,val);
        if (alpha >= beta)
        {
            break;
        } 
    }

    return score;
};