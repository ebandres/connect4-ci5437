#include "algoritmos.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
	PlayerData playerOne, playerTwo;
	state_t b;
	pair<state_t, int> nega;
	

	int columnChoice;
	int win;
	int full;
	int trueWidth = 7;
	int trueLength = 6;
	int turn = 1;

	cout << "Welcome to Connect 4" << endl
		 << endl;

	// inicializo dos jugadores, y su tipo de ficha unica.
	strcpy(playerOne.playerName, "PlayerOne");
	playerOne.playerPiece = 'X';

	strcpy(playerTwo.playerName, "PlayerTwo");
	playerTwo.playerPiece = 'O';

	Players players(playerOne, playerTwo);

	FillBoard(b, "6223121131332157157", players, turn);
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
	while (true)
	{
		next_move.first.BoardPrint();
		if (next_move.first.CheckDraw() || next_move.first.GetWinner(players) != 0) break;

		if (turn == 1) {

			Node result = MCTS(iters, &(next_move.second), factor, players, turn);
			next_move  = {result.state, result};
			turn = -1;

		} else {

			nega = negamax_alphabeta(next_move.first, 15, -1, 1, players, turn);
			Node root(nega.first);
			root.is_root = true;
			next_move = {nega.first, root};
			turn = 1;
		}

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

	
	
	// 	cout << "REVERSING THROUGH ---------" << endl;
	// Node *p = &result;
	// do
	// {
	// 	p->state.BoardPrint();
	// 	p = p->parent;
	// } while (!p->is_root);
	
		
}
	// centinelas de tablero.
// 	full = 0;
// 	win = 0;
// 	b.BoardPrint();
// 	do
// 	{
// 		// turno del primer jugador.
// 		columnChoice = b.PlayerTurn(playerOne);
// 		if (b.CheckDown(columnChoice))
// 		{
// 			next_move = b.MakeMove(playerOne, columnChoice);
// 		}
// 		cout << b.width*b.height+1 << endl;
// 		next_move.BoardPrint();
// 		b.BoardPrint();
// 		if (next_move.CheckWinner(playerOne))
// 		{
// 			WinnerMessage(playerOne);
// 			break;
// 		}

// 		// turno del segundo jugador.
// 		columnChoice = b.PlayerTurn(playerTwo);
// 		if (b.CheckDown(columnChoice))
// 		{
// 			b.MakeMove(playerTwo, columnChoice);
// 		}
		
// 		b.BoardPrint();
// 		if (b.CheckWinner(playerTwo))
// 		{
// 			WinnerMessage(playerTwo);
// 			break;
// 		}

// 		// comprondo si esta llena la tabla para salir.
// 		if (b.CheckDraw())
// 		{
// 			cout << "Draw! Full Board" << endl;
// 			break;
// 		}

// 	} while (true);
// 	return 0;
// }