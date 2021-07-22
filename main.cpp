#include <iostream>
#include <cstring>
using namespace std;

// Estructura que almacena la data de los jugadores
struct PlayerData
{
	char playerName[25];
	char playerPiece;
};

int PlayerTurn( char board[][10], PlayerData activePlayer )
{
	int columnChoice;
	do
	{
        cout << "\n";
		cout << activePlayer.playerName << "'s Turn \n";
		cout << "Please enter the column number: ";
		cin  >> columnChoice;
        cout << "\n";

        // Si la primera fila en la columna seleccionada tiene una ficha, esta llena.
		while ( board[1][columnChoice] == 'O' || board[1][columnChoice] == 'X' )
		{
			cout << "Full column, please enter a different number: ";
			cin  >> columnChoice;
		}

	}while ( columnChoice < 1 || columnChoice > 7 );

return columnChoice;
}

void CheckDown ( char board[][10], PlayerData activePlayer, int columnChoice )
{
    // Chequea si existe una ficha debajo para apilar la siguiente.
	int length;
    int turn;

	length = 6;
	turn = 0;

	do 
	{
		if ( board[length][columnChoice] != 'O' && board[length][columnChoice] != 'X' )
		{
			board[length][columnChoice] = activePlayer.playerPiece;
			turn = 1;
		}
		else
		--length;
	}while (  turn != 1 );


}

void BoardPrint ( char board[][10] )
{
    // Realiza la impresion del estado del tablero.
	int rows = 6, columns = 7, i, ix;
	
    cout << " _______ " << endl;
	
	for(i = 1; i <= rows; i++)
	{
		cout << "|";
		for(ix = 1; ix <= columns; ix++)
		{
			if(board[i][ix] != 'X' && board[i][ix] != 'O')
				board[i][ix] = '*';

			cout << board[i][ix];
			
		}

		cout << "|" << endl;

	}
    cout << " ^^^^^^^ " << endl;
    cout << " 1234567 " << endl;

}

int CheckWinner ( char board[][10], PlayerData activePlayer )
{
	char Piece;
	int win;
	
	Piece = activePlayer.playerPiece;
	win = 0;

    // recorre toda la matriz en busca de las
    // 4 posibles combinaciones para activar
    // el centinela de victoria y terminar
    // la partica.
	for( int i = 8; i >= 1; --i )
	{
		
		for( int ix = 9; ix >= 1; --ix )
		{

			if( board[i][ix] == Piece   &&
				board[i][ix-1] == Piece &&
				board[i][ix-2] == Piece &&
				board[i][ix-3] == Piece )
			{
				win = 1;
			}

			if( board[i][ix] == Piece     &&
				board[i-1][ix-1] == Piece &&
				board[i-2][ix-2] == Piece &&
				board[i-3][ix-3] == Piece )
			{
				win = 1;
			}
					
			if( board[i][ix] == Piece   &&
				board[i-1][ix] == Piece &&
				board[i-2][ix] == Piece &&
				board[i-3][ix] == Piece )
			{	
				win = 1;
			}

			if ( board[i][ix] == Piece   &&
				 board[i][ix+1] == Piece &&
				 board[i][ix+2] == Piece &&
				 board[i][ix+3] == Piece )
			{
				win = 1;
			}

			if( board[i][ix] == Piece     &&
				board[i-1][ix+1] == Piece &&
				board[i-2][ix+2] == Piece &&
				board[i-3][ix+3] == Piece )
			{
				win = 1;
			}
		}
		
	}

return win;
}

int CheckDraw( char board[][10] )
{
	int full;
	full = 0;

    // recorre toda la tabla, si todas las posiciones son fichas
    // asigna un valor al centinela para declarar el empate y salir.
	for ( int i = 1; i <= 7; ++i )
	{
		if ( board[1][i] != '*' )
			++full;
	}

return full;
}

void WinnerMessage ( PlayerData activePlayer )
{
    // solo imprime un mensaje al ganador.
	cout << endl << activePlayer.playerName << " Wins!" << endl;
}


int PlayerTurn( char board[][10], PlayerData activePlayer );
void CheckDown ( char board[][10], PlayerData activePlayer, int columnChoice );
void BoardPrint ( char board[][10] );
int CheckWinner ( char board[][10], PlayerData activePlayer );
int CheckDraw( char board[][10] );
void WinnerMessage ( PlayerData activePlayer );

int main()
{
	PlayerData playerOne, playerTwo;
	int columnChoice; 
    int win;
    int full; 
	char board[9][10]; 
	int trueWidth = 7; 
	int trueLength = 6; 


	cout << "Welcome to Connect 4" << endl << endl;

    // inicializo dos jugadores, y su tipo de ficha unica.
    strcpy( playerOne.playerName, "PlayerOne" );
	playerOne.playerPiece = 'O';

	strcpy( playerTwo.playerName, "PlayerTwo" );
	playerTwo.playerPiece = 'X';
	
    // centinelas de tablero.
	full = 0;
	win = 0;
	BoardPrint( board );
	do
	{
        // turno del primer jugador.
		columnChoice = PlayerTurn( board, playerOne );
		CheckDown( board, playerOne, columnChoice );
		BoardPrint( board );
		win = CheckWinner( board, playerOne );
		if ( win == 1 )
		{
			WinnerMessage(playerOne);
            break;
		}

        // turno del segundo jugador.
		columnChoice = PlayerTurn( board, playerTwo );
		CheckDown( board, playerTwo, columnChoice );
		BoardPrint( board );
		win = CheckWinner( board, playerTwo );
		if ( win == 1 )
		{
			WinnerMessage(playerTwo);
			break;
		}

        // comprondo si esta llena la tabla para salir.
		full = CheckDraw( board );
		if ( full == 7 )
		{
			cout << "Draw! Full Board" << endl;
			break;
		}

	}while (true);
return 0;
}


