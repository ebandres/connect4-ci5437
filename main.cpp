#include "algoritmos.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, const char **argv)
{
	int option = 0;
	if( argc > 1 ) option = atoi(argv[1]);

	PlayerData playerOne, playerTwo;
	state_t b, move;
	pair<state_t, int> nega;
	

	int columnChoice;
	int win;
	int full;
	int trueWidth = 7;
	int trueLength = 6;
	int turn = 1;
	int choice;

	cout << "Welcome to Connect 4" << endl
		 << endl;

	// inicializo dos jugadores, y su tipo de ficha unica.
	strcpy(playerOne.playerName, "PlayerOne");
	playerOne.playerPiece = 'X';

	strcpy(playerTwo.playerName, "PlayerTwo");
	playerTwo.playerPiece = 'O';

	Players players(playerOne, playerTwo);

	FillBoard(b, "5465124267522111164", players, turn);
	//FillBoard(b, "123", players, turn);
	
	b.BoardPrint();
    time_point<high_resolution_clock> start_time = high_resolution_clock::now();

	//pair<state_t, int> nega = negamax_alphabeta(b, 15, -1, 1, players, turn);
	//cout << nega.second << endl;
	//exit(0);
	int iters = 5000;
	float factor = 1;
	Node root(b);
	//Node result;
	root.is_root = true;
	pair<state_t, Node> next_move = {b, root};
	//Node result = MCTS(iters, &root, factor, players, turn);
	if (option == 1) {
		while (true)
		{
			next_move.first.BoardPrint();
			if (next_move.first.CheckDraw() || next_move.first.GetWinner(players) != 0) break;

			if (turn == 1) {

				Node result = MCTS(iters, &(next_move.second), factor, players, turn);
				next_move  = {result.state, result};
				turn = -1;

			} else {

				nega = negamax_alphabeta(next_move.first, 15, -200, 200, players, turn);
				Node root(nega.first);
				root.is_root = true;
				next_move = {nega.first, root};
				turn = 1;
			}
		}
	}

	else if (option == 2) {

		Node result = MCTS(iters, &root, factor, players, turn);

		while (true) {
			if (result.state.CheckDraw() || result.state.GetWinner(players) != 0) break;

			result = MCTS(iters, &result, factor, players, turn);
		}

		next_move.first = result.state;	
	}

	else if (option == 3) {

		while (true) {
			b.BoardPrint();
			if (b.CheckDraw() || b.GetWinner(players) != 0) break;

			if (turn == 1) {
				b = negamax_alphabeta(b, 15, -200, 200, players, turn).first;
				turn = -1;

			} else {
				choice = b.PlayerTurn(playerTwo);
				b = b.MakeMove(playerTwo, choice);
				turn = 1;
			}
		}
		next_move.first = b;	
	}

	else if (option == 4) {

			while (true) {
			next_move.first.BoardPrint();
			if (next_move.first.CheckDraw() || next_move.first.GetWinner(players) != 0) break;

			if (turn == 1) {
				Node result = MCTS(iters, &(next_move.second), factor, players, turn);
				next_move  = {result.state, result};
				turn = -1;

			} else {
				choice = b.PlayerTurn(playerTwo);
				b = next_move.first.MakeMove(playerTwo, choice);
				Node root(b);
				root.is_root = true;
				next_move = {b, root};
				turn = 1;
			}
		}

	}

	else if (option == 5) {
		while (true) {
			b.BoardPrint();
			if (b.CheckDraw() || b.GetWinner(players) != 0) break;
			b = negamax_alphabeta(b, 15, -200, 200, players, turn).first;
			turn = -turn;
		}
		next_move.first = b;
	}

	cout << "DONE?" << endl;
	next_move.first.BoardPrint();
	int winner = next_move.first.GetWinner(players);
	if (winner == 1)
	{
		cout << "WINNER: MTCS X" << endl;
	}
	else if (winner == -1)
	{
		cout << "WINNER: NEGAMAX O" << endl;
	}
	else if (next_move.first.CheckDraw())
	{
		cout << "DRAW" << endl;
	}

    duration<double> elapsed_time = high_resolution_clock::now() - start_time;
	cout << "Time: " << elapsed_time.count() << " seconds" << endl;
