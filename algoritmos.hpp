#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <experimental/random>
#include "class.hpp"
#include "ttable.hpp"

using namespace std;
using namespace std::chrono;

unsigned expanded = 0;
unsigned generated = 0;
TranspositionTable TTable(8388593);

vector<state_t> child_vector(state_t state, PlayerData player) {
    vector<state_t> movement;
    state_t new_state;

    for (int i = 0; i < 7; i++)
    {
        if (state.CheckDown(columnOrder[i]))
        {
            new_state = state.MakeMove(player, columnOrder[i]);
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

int negamax_alphabeta(state_t state, int depth, int alpha, int beta,  Players players, int turn){
    
    //check_time(st);
    int score;
    ++generated;

    if (state.CheckDraw()) 
    {
        return 0;
    }

    if (check_children(state, players.turn(turn))) {
        return (state.width*state.height+1 - state.moves)/2;
    }

    int max = (state.width*state.height-1 - state.moves)/2;	
    if(int info = TTable.get(state.key()))
    max = info + state.min_score - 1;

    if(beta > max) {
    beta = max;                     
    if(alpha >= beta) return beta;  
    }

    // si no es estado terminal, expande
    ++expanded;
    score = numeric_limits<int>::min();
    // generando movimientos validos
    vector<state_t> child_states = child_vector(state, players.turn(turn));
    
    for (state_t child : child_states) 
    {
        score = -negamax_alphabeta(child, depth - 1, -beta, -alpha, players, -turn);
        if(score >= beta) return score;  
        if(score > alpha) alpha = score; 
    }

    TTable.put(state.key(), alpha - state.min_score + 1);

    return alpha;
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

struct NT
{
	Node n;
	int t;
};

NT tree_policy(Node node, Players players, int turn, float factor)
{
    while (!node.state.CheckDraw() && node.state.GetWinner(players) == 0)
    {
        if (!node.FullyExplored())
        {
            NT r = {expand(node, players.turn(turn)), -turn};
            return r;
        }
        else
        {
            node = best_child(node, factor);
            turn = -turn;
        }
    }
    NT r = {node, turn};
    return r;
}

float default_policy(state_t state, Players players, int turn) 
{
    while (!state.CheckDraw() && state.GetWinner(players))
    {
        state = state.RandMove(players.turn(turn));
        turn = -turn;
    }
    return state.GetWinner(players);
}

void backup(Node node, float reward, Players players, int turn)
{
    while (true)
    {
        node.visits++;
        node.reward -= turn * reward;
        turn = -turn;
        if (node.parent == nullptr)
        {
            break;
        }
        node = *node.parent;
    }
}

Node MCTS(int max_iter, Node root, float factor, Players players)
{
    for (int i = 0; i < max_iter; i++)
    {
        NT r = tree_policy(root, players, 1, factor);
        float reward = default_policy(r.n.state, players, r.t);
        backup(r.n, reward, players, r.t);
    }
    
    return best_child(root, 0);
}