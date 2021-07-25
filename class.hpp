#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <cstring>
using namespace std;

// Estructura que almacena la data de los jugadores
struct PlayerData
{
	char playerName[25];
	char playerPiece;
};

class state_t
{
public:
	static const int width = 7;
	static const int height = 6;
	char board[9][10];
	int free_slots[width] = {6, 6, 6, 6, 6, 6, 6};
	unsigned int moves = 0;

	int PlayerTurn(PlayerData activePlayer);
	state_t MakeMove(PlayerData activePlayer, int columnChoice);
	bool CheckDown(int columnChoice);
	void BoardPrint(void);
	bool CheckWinner(PlayerData activePlayer);
	bool CheckDraw(void);
};

int state_t::PlayerTurn(PlayerData activePlayer)
{
	int columnChoice;
	do
	{
		cout << "\n";
		cout << activePlayer.playerName << "'s Turn \n";
		cout << "Please enter the column number: ";
		cin >> columnChoice;
		cout << "\n";

		// Si la primera fila en la columna seleccionada tiene una ficha, esta llena.
		while (board[1][columnChoice] == 'O' || board[1][columnChoice] == 'X')
		{
			cout << "Full column, please enter a different number: ";
			cin >> columnChoice;
		}

	} while (columnChoice < 1 || columnChoice > 7);

	return columnChoice;
}

state_t state_t::MakeMove(PlayerData activePlayer, int columnChoice) 
{
	state_t s(*this);
	s.board[free_slots[columnChoice - 1]][columnChoice] = activePlayer.playerPiece;
	s.free_slots[columnChoice - 1]--;
	s.moves++;

	return s;
}

bool state_t::CheckDown(int columnChoice)
{
	// Chequea si existe una ficha debajo para apilar la siguiente.
	return free_slots[columnChoice - 1] > 0;
}

void state_t::BoardPrint(void)
{
	// Realiza la impresion del estado del tablero.
	int rows = 6, columns = 7, i, ix;

	cout << " _______ " << endl;

	for (i = 1; i <= rows; i++)
	{
		cout << "|";
		for (ix = 1; ix <= columns; ix++)
		{
			if (board[i][ix] != 'X' && board[i][ix] != 'O')
				board[i][ix] = '*';

			cout << board[i][ix];
		}

		cout << "|" << endl;
	}
	cout << " ^^^^^^^ " << endl;
	cout << " 1234567 " << endl;
}

bool state_t::CheckWinner(PlayerData activePlayer)
{
	char Piece;

	Piece = activePlayer.playerPiece;

	// recorre toda la matriz en busca de las
	// 4 posibles combinaciones para activar
	// el centinela de victoria y terminar
	// la partica.
	for (int i = 8; i >= 1; --i)
	{

		for (int ix = 9; ix >= 1; --ix)
		{

			if (board[i][ix] == Piece &&
				board[i][ix - 1] == Piece &&
				board[i][ix - 2] == Piece &&
				board[i][ix - 3] == Piece)
			{
				return true;
			}

			if (board[i][ix] == Piece &&
				board[i - 1][ix - 1] == Piece &&
				board[i - 2][ix - 2] == Piece &&
				board[i - 3][ix - 3] == Piece)
			{
				return true;
			}

			if (board[i][ix] == Piece &&
				board[i - 1][ix] == Piece &&
				board[i - 2][ix] == Piece &&
				board[i - 3][ix] == Piece)
			{
				return true;
			}

			if (board[i][ix] == Piece &&
				board[i][ix + 1] == Piece &&
				board[i][ix + 2] == Piece &&
				board[i][ix + 3] == Piece)
			{
				return true;
			}

			if (board[i][ix] == Piece &&
				board[i - 1][ix + 1] == Piece &&
				board[i - 2][ix + 2] == Piece &&
				board[i - 3][ix + 3] == Piece)
			{
				return true;
			}
		}
	}

	return false;
}

bool state_t::CheckDraw(void)
{
	if (moves == 42) {
		return true;
	} else {
		return false;
	}
}

void WinnerMessage(PlayerData activePlayer)
{
	// solo imprime un mensaje al ganador.
	cout << endl
		 << activePlayer.playerName << " Wins!" << endl;
}


void FillBoard(state_t &state, string seq, PlayerData player1, PlayerData player2) 
{
PlayerData player;
for(unsigned int i = 0; i < seq.size(); i++) {
	int col = seq[i] - '1'; 
	col++;
	cout << col << endl;

	if (state.moves % 2 == 0) {
		player = player1;
	} else {
		player = player2;
	}

	state = state.MakeMove(player, col);
}
}

#endif