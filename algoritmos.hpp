#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <experimental/random>
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

bool check_children(state_t state, PlayerData player) {
    vector<state_t> children = child_vector(state, player);

    for (state_t child : children) {
        if (child.CheckWinner(player)) {
            return true;
        }
    }

    return false;
}

int negamax_alphabeta(state_t state, int depth, int alpha, int beta,  PlayerData player1, PlayerData player2){
    
    //check_time(st);
    int score, val;
    ++generated;

    if (state.CheckDraw()) // DRAW
    {
        return 0;
    }

    if (check_children(state, player1)) {
        return (state.width*state.height+1 - state.moves)/2;
    }

    // si no es estado terminal, expande
    ++expanded;
    score = numeric_limits<int>::min();
    // generando movimientos validos
    vector<state_t> child_states = child_vector(state, player1);
    
    for (state_t child : child_states) 
    {
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

// Monte Carlo Tree Search

Node expand(Node node, PlayerData player)
{
    vector<int> tried_moves = node.children_move;
    vector<int> possible_moves = node.state.GetPossibleMoves();
    state_t s(node.state);
    int col;
    for (int i = 0; i < possible_moves.size(); i++)
    {
        col = possible_moves[i];
        if (find(tried_moves.begin(), tried_moves.end(), possible_moves[i]) == tried_moves.end())
        {
            s = s.MakeMove(player, possible_moves[i]);
            break;
        }
        
    }

    node.AddChild(s, col);
    return node.children[node.children.size() - 1];
}

Node best_child(Node node, float factor)
{
    float bestScore = numeric_limits<float>::min();
    vector<Node> bestChildren;

    for (int i = 0; i < node.children.size(); i++)
    {
        float f = node.children[i].reward / node.children[i].visits;
        float g = sqrt(log(2 * node.visits) / node.children[i].visits);
        float score = f + factor * g;

        if (score == bestScore)
        {
            bestChildren.push_back(node.children[i]);
        }
        else if (score > bestScore)
        {
            bestChildren.clear();
            bestChildren.push_back(node.children[i]);
            bestScore = score;
        }
    }
    
	int size = static_cast<int>(bestChildren.size());
    int choice = experimental::randint(0, size - 1);
    return bestChildren[choice];
}

pair<Node, PlayerData> tree_policy(Node node, PlayerData player, float factor)
{
    // Hacer cuando cambiemos PlayerData por algo mas usable
}

/* Hacer cuando cambiemos PlayerData por algo mas usable
 * ?? default_policy(state_t state, player) 
 * {
 *  
 * }
 * 
 * void backup(Node node, float reward, player)
 * {
 * 
 * }
 */