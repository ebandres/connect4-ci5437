#include "algoritmos.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, const char **argv)
{
	int option = 0;
	string seq = "";
	if (argc > 1)
	{
		option = atoi(argv[1]);
		if (argc > 2)
		{
			seq = argv[2];
		}
	}
	else
	{
		cout << "No arguments\nCorrect syntax: ./connect4 <option> <initial state>" << endl
			 << "Options: 1 - MCTS VS NEGAMAX" << endl
			 << "         2 - MCTS VS MCTS" << endl
			 << "         3 - NEGAMAX VS PLAYER" << endl
			 << "         4 - MCTS VS PLAYER" << endl
			 << "         5 - NEGAMAX VS NEGAMAX" << endl;
		exit(1);
	}

	PlayerData playerOne, playerTwo;
	state_t b, move;
	pair<state_t, int> nega;
	
	int columnChoice;
	int turn = 1;
	int choice;

	//cout << "Welcome to Connect 4" << endl

	// inicializo dos jugadores, y su tipo de ficha unica.
	switch (option)
	{
	case 1:
		//cout << "MCTS VS NEGAMAX" << endl;
		strcpy(playerOne.playerName, "MCTS");
		strcpy(playerTwo.playerName, "NEGAMAX");
		break;
	
	case 2:
		//cout << "MCTS VS MCTS" << endl;
		strcpy(playerOne.playerName, "MCTS 1");
		strcpy(playerTwo.playerName, "MCTS 2");
		break;
	
	case 3:
		//cout << "NEGAMAX VS PLAYER" << endl;
		strcpy(playerOne.playerName, "NEGAMAX");
		strcpy(playerTwo.playerName, "PLAYER");
		break;

	case 4:
		//cout << "MCTS VS PLAYER" << endl;
		strcpy(playerOne.playerName, "MCTS");
		strcpy(playerTwo.playerName, "PLAYER");
		break;

	case 5:
		//cout << "NEGAMAX VS NEGAMAX" << endl;
		strcpy(playerOne.playerName, "NEGAMAX 1");
		strcpy(playerTwo.playerName, "NEGAMAX 2");
		break;
	}

	playerOne.playerPiece = 'X';
	playerTwo.playerPiece = 'O';

	Players players(playerOne, playerTwo);

	FillBoard(b, seq, players, turn);
	//FillBoard(b, "123", players, turn);

	cout << "Initial state: " << endl;
	b.BoardPrint();

	int iters = 5000;
	float factor = 1;
	Node root(b);
	root.is_root = true;
	pair<state_t, Node> next_move = {b, root};

	time_point<high_resolution_clock> start_time = high_resolution_clock::now();
	if (option == 1) // MCTS VS NEGAMAX
	{
		while (true)
		{
			//next_move.first.BoardPrint();
			if (next_move.first.CheckDraw() || next_move.first.GetWinner(players) != 0)
				break;

			if (turn == 1)
			{

				Node result = MCTS(iters, &(next_move.second), factor, players, turn);
				next_move = {result.state, result};
				turn = -1;
			}
			else
			{

				nega = negamax_alphabeta(next_move.first, 15, -200, 200, players, turn);
				Node root(nega.first);
				root.is_root = true;
				next_move = {nega.first, root};
				turn = 1;
			}
		}
	}

	else if (option == 2) // MCTS VS MCTS
	{

		Node result = MCTS(iters, &root, factor, players, turn);

		while (true)
		{
			if (result.state.CheckDraw() || result.state.GetWinner(players) != 0)
				break;

			result = MCTS(iters, &result, factor, players, turn);
		}

		next_move.first = result.state;
	}

	else if (option == 3) // NEGAMAX VS PLAYER
	{

		while (true)
		{
			b.BoardPrint();
			if (b.CheckDraw() || b.GetWinner(players) != 0)
				break;

			if (turn == 1)
			{
				b = negamax_alphabeta(b, 15, -200, 200, players, turn).first;
				turn = -1;
			}
			else
			{
				choice = b.PlayerTurn(playerTwo);
				b = b.MakeMove(playerTwo, choice);
				turn = 1;
			}
		}
		next_move.first = b;
	}

	else if (option == 4) // MCTS VS PLAYER
	{

		while (true)
		{
			next_move.first.BoardPrint();
			if (next_move.first.CheckDraw() || next_move.first.GetWinner(players) != 0)
				break;

			if (turn == 1)
			{
				Node result = MCTS(iters, &(next_move.second), factor, players, turn);
				next_move = {result.state, result};
				turn = -1;
			}
			else
			{
				choice = b.PlayerTurn(playerTwo);
				b = next_move.first.MakeMove(playerTwo, choice);
				Node root(b);
				root.is_root = true;
				next_move = {b, root};
				turn = 1;
			}
		}
	}

	else if (option == 5) // NEGAMAX VS NEGAMAX
	{
		while (true)
		{
			//b.BoardPrint();
			if (b.CheckDraw() || b.GetWinner(players) != 0)
				break;
			b = negamax_alphabeta(b, 15, -200, 200, players, turn).first;
			turn = -turn;
		}
		next_move.first = b;
	}

	duration<double> elapsed_time = high_resolution_clock::now() - start_time;

	cout << "Last state: " << endl;
	next_move.first.BoardPrint();

	cout << "\nInitial state: " << seq << endl;
	int winner = next_move.first.GetWinner(players);
	if (winner == 1)
	{
		cout << "WINNER: " << playerOne.playerName << " " << playerOne.playerPiece << endl;
	}
	else if (winner == -1)
	{
		cout << "WINNER: " << playerTwo.playerName << " " << playerTwo.playerPiece << endl;
	}
	else if (next_move.first.CheckDraw())
	{
		cout << "DRAW" << endl;
	}

	cout << "Time: " << elapsed_time.count() << " seconds" << endl;

	return 0;
}
