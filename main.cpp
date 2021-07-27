#include "algoritmos.hpp"

using namespace std;

int main()
{
	PlayerData playerOne, playerTwo;
	state_t b;
	state_t next_move;

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
	playerOne.playerPiece = 'O';

	strcpy(playerTwo.playerName, "PlayerTwo");
	playerTwo.playerPiece = 'X';

	Players players(playerOne, playerTwo);

	FillBoard(b, "32751571231557", players, turn);
	b.BoardPrint();

	int value = negamax_alphabeta(b, 15, -1, 1, players, turn);
	cout << value << endl;
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