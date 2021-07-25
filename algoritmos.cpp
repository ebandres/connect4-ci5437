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
    for (int i = 1; i <= 7; i++)
    {
        if (state.CheckDown(i))
        {
            // Revisar como se hace move en el proyecto 2
        }
    }
}

int negamax(state_t state, int depth, PlayerData player1, PlayerData player2, time_point<high_resolution_clock> st){
    
    //check_time(st);

    ++generated;

    if (state.CheckDraw()) // DRAW
    {
        return 0;
    }

    // si no es estado terminal, expande
    ++expanded;
    int alpha = numeric_limits<int>::min();
    // generando movimientos validos
    vector<state_t> child_states = child_vector(state, player1);
    
    for (state_t child : child_states) 
    {
        alpha = max(alpha, -negamax(child, depth - 1, player2, player1, st));
    }

    return alpha;
};