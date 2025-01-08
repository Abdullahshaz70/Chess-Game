#include<iostream>
#include<math.h>
#include<fstream>
#include<conio.h>
#include<string>
#include<windows.h>
#include<ctime>
using namespace std;
#define GRID_SIZE 8
#define ROWS 100
#define COLS 100
#define MAX_MOVES 1000
enum COLOR {
	BLACK, WHITE
};
struct piece {
	char type;
	COLOR color;
	bool (*islegal)(piece* [][GRID_SIZE], int, int, int, int) {};
	void (*Draw)(int, int, char, COLOR);

};
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void color(int textColor, int backgroundColor = 0) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = (backgroundColor << 4) | (textColor & 0x0F);
	SetConsoleTextAttribute(hConsole, color);
}


void draw_pawn(int sr, int sc, char sym, COLOR Color) {

	color(18);
	int i = 4;
	gotoRowCol(sr + 1, sc + i);
	cout << sym;

	gotoRowCol(sr + 2, sc - 1 + i);
	cout << sym << sym << sym;

	if (Color == BLACK)
		color(20);
	else
		color(22);


	gotoRowCol(sr + 3, sc - 2 + i);
	cout << sym << sym << sym << sym << sym;


	gotoRowCol(sr + 4, sc - 1 + i);
	cout << sym << sym << sym;

	color(18);
	gotoRowCol(sr + 5, sc + i);
	cout << sym;

	gotoRowCol(sr + 6, sc - 3 + i + 1);
	cout << sym << sym << sym << sym << sym;

}
void draw_rook(int sr, int sc, char sym, COLOR Color) {
	color(18);
	int i = 4;
	gotoRowCol(sr + 1, sc + 1);
	cout << sym;
	gotoRowCol(sr + 1, sc + 3);
	cout << sym;
	gotoRowCol(sr + 1, sc + 5);
	cout << sym;


	if (Color == BLACK)
		color(20);
	else
		color(22);

	gotoRowCol(sr + 1 + 1, sc + 2);
	cout << sym << sym << sym;
	gotoRowCol(sr + 2 + 1, sc + 2);
	cout << sym << sym << sym;
	gotoRowCol(sr + 3 + 1, sc + 2);
	cout << sym << sym << sym;


	color(18);
	gotoRowCol(sr + 5, sc + 1);
	cout << sym << sym << sym << sym << sym;
	gotoRowCol(sr + 6, sc + 1);
	cout << sym << sym << sym << sym << sym;





}
void draw_horse(int sr, int sc, char sym, COLOR Color) {
	color(18);
	gotoRowCol(sr + 1, sc + 2);
	cout << sym << sym << sym;

	if (Color == BLACK)
		color(20);
	else
		color(22);

	gotoRowCol(sr + 2, sc + 1);
	cout << sym << sym << sym << sym << sym;

	gotoRowCol(sr + 3, sc + 5);
	cout << sym;

	gotoRowCol(sr + 4, sc + 4);
	cout << sym;


	gotoRowCol(sr + 5, sc + 3);
	cout << sym;

	color(18);
	gotoRowCol(sr + 6, sc + 1);
	cout << sym << sym << sym << sym << sym;


}
void draw_bishop(int sr, int sc, char sym, COLOR Color) {
	color(18);

	gotoRowCol(sr + 1, sc + 3);
	cout << sym;

	gotoRowCol(sr + 2, sc + 2);
	cout << sym << sym << sym;

	if (Color == BLACK)
		color(20);
	else
		color(22);
	gotoRowCol(sr + 3, sc + 1);
	cout << sym << sym << sym << sym << sym;

	gotoRowCol(sr + 4, sc + 1);
	cout << sym << sym << sym << sym << sym;

	color(18);
	gotoRowCol(sr + 5, sc + 3);
	cout << sym;

	gotoRowCol(sr + 6, sc + 1);
	cout << sym << sym << sym << sym << sym;


}
void draw_queen(int sr, int sc, char sym, COLOR Color) {
	color(18);

	gotoRowCol(sr + 1, sc + 3);
	cout << sym;

	if (Color == BLACK)
		color(20);
	else
		color(22);
	gotoRowCol(sr + 2, sc + 1);
	cout << sym << sym << sym << sym << sym;

	gotoRowCol(sr + 3, sc + 1);
	cout << sym << sym << sym << sym << sym;

	gotoRowCol(sr + 4, sc + 1);
	cout << sym << sym << sym << sym << sym;

	color(18);

	gotoRowCol(sr + 5, sc + 3);
	cout << sym;

	gotoRowCol(sr + 6, sc + 1);
	cout << sym << sym << sym << sym << sym;

}
void draw_king(int sr, int sc, char sym, COLOR Color) {
	color(18);
	gotoRowCol(sr + 1, sc + 1);
	cout << sym;
	gotoRowCol(sr + 1, sc + 3);
	cout << sym;
	gotoRowCol(sr + 1, sc + 5);
	cout << sym;

	if (Color == BLACK)
		color(20);
	else
		color(22);

	gotoRowCol(sr + 2, sc + 1);
	cout << sym << sym << sym << sym << sym;

	gotoRowCol(sr + 3, sc + 1);
	cout << sym << sym << sym << sym << sym;

	gotoRowCol(sr + 4, sc + 1);
	cout << sym << sym << sym << sym << sym;

	color(18);

	gotoRowCol(sr + 5, sc + 3);
	cout << sym;

	gotoRowCol(sr + 6, sc + 1);
	cout << sym << sym << sym << sym << sym;

}

void printB(piece* B[][GRID_SIZE]) {
	char sym = -37;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			gotoRowCol(30 + i, 130 + j);

			if (B[i][j] != nullptr) {
				char p = B[i][j]->type;

				if (B[i][j]->color == BLACK)
					color(8);

				else if (B[i][j]->color == WHITE)
					color(15);

				cout << p;
			}
			else {
				color(7);
				cout << '.';
			}
		}
	}
}

void display_turn(string n) {
	gotoRowCol(20, 130);
	cout << n << " turns!";
}
int turn_change(int n) {
	return (n % 2) + 1;
}

void box333(int sr, int sc, bool Color) {
	if (Color)
		color(0);
	else
		color(19);

	char sym = -37;
	for (int r = 0; r < GRID_SIZE; r++) {
		for (int c = 0; c < GRID_SIZE; c++) {
			gotoRowCol(sr + r, sc + c);
			cout << sym;
		}
	}
}
void grid() {
	for (int r = 0; r < GRID_SIZE; r++) {
		for (int c = 0; c < GRID_SIZE; c++) {
			int sr = r * GRID_SIZE;
			int sc = c * GRID_SIZE;
			bool color = (r + c) % 2 == 0;
			box333(sr, sc, color);
		}
	}
}
void calculate_grid_index(piece* B[][GRID_SIZE]) {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			gotoRowCol(i * 8 + 4, j * 8 + 4);

			if (B[i][j] != nullptr) {
				char p = B[i][j]->type;
				if (B[i][j]->color == BLACK) {
					color(8);
				}
				else if (B[i][j]->color == WHITE) {
					color(15);
				}
				B[i][j]->Draw(i * 8, j * 8, -37, B[i][j]->color);
			}
		}
	}
}

void calculate_Array_index(int& r, int& c) {
	r = r / GRID_SIZE;
	c = c / GRID_SIZE;

}
bool isValid(int r, int c, piece* B[][GRID_SIZE], int turn, int r1, int c1) {
	if (r < 0 or r >= 63 or c < 0 or c >= 63 or r1 < 0 or r1 >= 63 or c1 < 0 or c1 >= 63)
		return false;

	COLOR color;
	if (turn == 1) {
		color = BLACK;
	}
	else {
		color = WHITE;
	}

	if (B[r][c] == nullptr or B[r][c]->color != color)
		return false;


	if (B[r1][c1] == nullptr or B[r1][c1]->type == '.' or B[r1][c1]->color != color)
		return true;


	return false;
}

void box(int sr, int sc) {
	color(5);
	char sym = -37;
	for (int r = 1; r < GRID_SIZE - 1; r++) {
		for (int c = 1; c < GRID_SIZE - 1; c++) {
			gotoRowCol(sr + r, sc + c);
			cout << sym;

		}
	}
}
void remove_box(int sr, int sc) {
	for (int r = 1; r < GRID_SIZE - 1; r++) {
		for (int c = 1; c < GRID_SIZE - 1; c++) {
			gotoRowCol(sr + r, sc + c);
			cout << " ";

		}
	}
}

bool is_horizontal(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec) {
	return sr == er;
}
bool is_vertical(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec) {
	return sc == ec;
}
bool is_diagnaol(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec) {
	int dr = abs(sr - er);
	int dc = abs(sc - ec);
	return dr == dc;
}

bool horizontal_path_clear(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec) {
	int hehe;
	if (sc < ec)
		hehe = 1;
	else
		hehe = -1;
	for (int i = sc + hehe; i != ec; i += hehe)
		if (B[sr][i] != nullptr)
			return false;

	return true;
}
bool vertical_path_clear(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec) {
	int hehe = -1;
	if (sr < er)
		hehe = 1;

	for (int r = sr + hehe; r != er; r += hehe)
		if (B[r][sc] != nullptr)
			return false;

	return true;
}
bool diagonal_path_clear(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec) {
	int dr = er - sr;
	int dc = ec - sc;

	int hehe_r = 0;
	if (dr > 0)
		hehe_r = 1;

	else if (dr < 0)
		hehe_r = -1;


	int hehe_c = 0;
	if (dc > 0)
		hehe_c = 1;

	else if (dc < 0)
		hehe_c = -1;


	int i = sr + hehe_r;
	int j = sc + hehe_c;

	while (i != er and j != ec) {
		if (B[i][j] != nullptr)
			return false;

		i += hehe_r;
		j += hehe_c;
	}

	return true;
}

bool rook_islegal(piece* p[][GRID_SIZE], int sr, int sc, int er, int ec) {
	if (is_horizontal(p, sr, sc, er, ec))
		return horizontal_path_clear(p, sr, sc, er, ec);

	else if (is_vertical(p, sr, sc, er, ec))
		return vertical_path_clear(p, sr, sc, er, ec);
	return false;
}
bool knight_islegal(piece* p[][GRID_SIZE], int sr, int sc, int er, int ec) {
	int dr = abs(sr - er);
	int dc = abs(sc - ec);
	return (dr == 2 and dc == 1) or (dr == 1 and dc == 2);
}
bool pawn_islegal(piece* p[][GRID_SIZE], int sr, int sc, int er, int ec) {
	if (p[sr][sc]->color == WHITE) {
		if (sr - 1 == er and sc == ec and p[er][ec] == nullptr)
			return true;

		if (sr == 6 and sr - 2 == er and sc == ec and p[er][ec] == nullptr and p[sr - 1][sc] == nullptr)
			return true;

		if (sr - 1 == er and abs(sc - ec) == 1 and p[er][ec] != nullptr and p[er][ec]->color == BLACK)
			return true;

	}
	else if (p[sr][sc]->color == BLACK) {
		if (sr + 1 == er and sc == ec and p[er][ec] == nullptr)
			return true;

		if (sr == 1 and sr + 2 == er and sc == ec and p[er][ec] == nullptr and p[sr + 1][sc] == nullptr)
			return true;

		if (sr + 1 == er and abs(sc - ec) == 1 and p[er][ec] != nullptr and p[er][ec]->color == WHITE)
			return true;

	}
	return false;
}
bool bishop_islegal(piece* p[][GRID_SIZE], int sr, int sc, int er, int ec) {
	if (is_diagnaol(p, sr, sc, er, ec))
		return diagonal_path_clear(p, sr, sc, er, ec);

	return false;
}
bool queen_islegal(piece* p[][GRID_SIZE], int sr, int sc, int er, int ec) {
	if (is_horizontal(p, sr, sc, er, ec) or is_vertical(p, sr, sc, er, ec) or is_diagnaol(p, sr, sc, er, ec)) {
		if (is_horizontal(p, sr, sc, er, ec))
			return horizontal_path_clear(p, sr, sc, er, ec);

		else if (is_vertical(p, sr, sc, er, ec))
			return vertical_path_clear(p, sr, sc, er, ec);

		else if (is_diagnaol(p, sr, sc, er, ec))
			return diagonal_path_clear(p, sr, sc, er, ec);

	}
	return false;
}
bool king_islegal(piece* p[][GRID_SIZE], int sr, int sc, int er, int ec) {
	int dr = abs(sr - er);
	int dc = abs(sc - ec);
	if ((dr <= 1 and dc <= 1) and !(dr == 0 and dc == 0))
		return true;

	return false;
}

void init(piece* B[GRID_SIZE][GRID_SIZE], int& n) {
	char blackPieces[] = { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };
	char whitePieces[] = { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };


	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			B[i][j] = nullptr;
		}
	}

	for (int i = 0; i < GRID_SIZE; i++) {
		B[0][i] = new piece{ blackPieces[i], BLACK };
		switch (blackPieces[i]) {
		case 'R': B[0][i]->islegal = rook_islegal;
			B[0][i]->Draw = draw_rook;
			break;

		case 'N': B[0][i]->islegal = knight_islegal;
			B[0][i]->Draw = draw_horse;
			break;

		case 'B': B[0][i]->islegal = bishop_islegal;
			B[0][i]->Draw = draw_bishop;
			break;

		case 'Q': B[0][i]->islegal = queen_islegal;
			B[0][i]->Draw = draw_queen;
			break;

		case 'K': B[0][i]->islegal = king_islegal;
			B[0][i]->Draw = draw_king;
			break;
		}

		B[1][i] = new piece{ 'p', BLACK };
		B[1][i]->islegal = pawn_islegal;
		B[1][i]->Draw = draw_pawn;
	}


	for (int i = 0; i < GRID_SIZE; i++) {
		B[7][i] = new piece{ whitePieces[i], WHITE };
		switch (whitePieces[i]) {
		case 'R': B[7][i]->islegal = rook_islegal;
			B[7][i]->Draw = draw_rook;
			break;

		case 'N': B[7][i]->islegal = knight_islegal;
			B[7][i]->Draw = draw_horse;
			break;

		case 'B': B[7][i]->islegal = bishop_islegal;
			B[7][i]->Draw = draw_bishop;
			break;

		case 'Q': B[7][i]->islegal = queen_islegal;
			B[7][i]->Draw = draw_queen;
			break;

		case 'K': B[7][i]->islegal = king_islegal;
			B[7][i]->Draw = draw_king;
			break;
		}


		B[6][i] = new piece{ 'P', WHITE };
		B[6][i]->islegal = pawn_islegal;
		B[6][i]->Draw = draw_pawn;
	}

	n = 2;
}

void remove_board(bool** highlight, int r, int c) {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {

			if (highlight[i][j]) {
				remove_box(i * GRID_SIZE, j * GRID_SIZE);

			}
		}
		cout << endl;
	}
}
void printBoard(bool** highlight) {

	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (highlight[i][j]) {
				box(i * GRID_SIZE, j * GRID_SIZE);
			}
		}
		cout << endl;
	}
}

bool** computeHighlight(piece* B[][GRID_SIZE], int r, int c) {
	if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE) {
		return nullptr;
	}

	bool** highlight = new bool* [GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; ++i) {
		highlight[i] = new bool[GRID_SIZE] {false};
	}

	if (B[r][c] != nullptr) {
		for (int i = 0; i < GRID_SIZE; ++i) {
			for (int j = 0; j < GRID_SIZE; ++j) {
				if (B[r][c]->islegal(B, r, c, i, j)) {
					highlight[i][j] = true;

				}
			}
		}
	}

	return highlight;
}
void delete_Highlight(bool** highlight) {
	for (int i = 0; i < GRID_SIZE; ++i) {
		delete[] highlight[i];
	}
	delete[] highlight;
}

bool isInCheck(piece* B[][GRID_SIZE], COLOR color) {
	int kingRow = -1, kingCol = -1;


	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (B[i][j] != nullptr && B[i][j]->type == 'K' && B[i][j]->color == color) {
				kingRow = i;
				kingCol = j;
				break;
			}
		}
		if (kingRow != -1) break;
	}


	if (kingRow == -1 || kingCol == -1) {
		return false;
	}


	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (B[i][j] != nullptr && B[i][j]->color != color) {
				if (B[i][j]->islegal(B, i, j, kingRow, kingCol)) {
					return true;
				}
			}
		}
	}

	return false;
}
bool isSelfCheck_purana(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec, COLOR playerColor) {

	piece* temp = B[er][ec];
	B[er][ec] = B[sr][sc];
	B[sr][sc] = nullptr;

	bool check = isInCheck(B, playerColor);


	B[sr][sc] = B[er][ec];
	B[er][ec] = temp;

	return check;
}

bool isSelfCheck(piece* B[][GRID_SIZE], int sr, int sc, int er, int ec, COLOR playerColor) {

	return false;
}

bool checkmate(piece* B[][GRID_SIZE], COLOR currentColor) {

	int kingRow = -1, kingCol = -1;
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (B[i][j] != nullptr and B[i][j]->type == 'K' and B[i][j]->color == currentColor) {
				kingRow = i;
				kingCol = j;
				break;
			}
		}
		if (kingRow != -1)
			break;
	}


	if (kingRow == -1 or kingCol == -1)
		return false;

	if (!isInCheck(B, currentColor))
		return false;



	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (B[i][j] != nullptr && B[i][j]->color == currentColor) {

				for (int x = 0; x < GRID_SIZE; ++x) {
					for (int y = 0; y < GRID_SIZE; ++y) {
						if (B[i][j]->islegal(B, i, j, x, y)) {

							piece* temp = B[x][y];
							B[x][y] = B[i][j];
							B[i][j] = nullptr;


							if (!isInCheck(B, currentColor)) {

								B[i][j] = B[x][y];
								B[x][y] = temp;
								return false;
							}


							B[i][j] = B[x][y];
							B[x][y] = temp;
						}
					}
				}
			}
		}
	}


	return true;
}

char promotePawn() {
	char choice;
	gotoRowCol(70, 130);
	cout << "Promote your pawn to (Q)ueen, (R)ook, (B)ishop, or (K)night: ";
	cin >> choice;

	gotoRowCol(70, 130);
	cout << "                                                              ";

	choice = toupper(choice);

	while (choice != 'Q' and choice != 'R' and choice != 'B' and choice != 'K') {
		gotoRowCol(70, 130);
		cout << "Invalid choice. Please choose (Q)ueen, (R)ook, (B)ishop, or (K)night: ";
		cin >> choice;
		gotoRowCol(70, 130);
		cout << "                                                                       ";
		choice = toupper(choice);
	}

	return choice;
}
void handlePawnPromotion(piece* B[GRID_SIZE][GRID_SIZE], int r1, int c1, COLOR color) {
	char promotedPiece = promotePawn();
	piece* newPiece = new piece;

	if (promotedPiece == 'Q') {
		newPiece->type = 'Q';
		newPiece->color = color;
		newPiece->islegal = queen_islegal;
		newPiece->Draw = draw_queen;
	}
	else if (promotedPiece == 'R') {
		newPiece->type = 'R';
		newPiece->color = color;
		newPiece->islegal = rook_islegal;
		newPiece->Draw = draw_rook;
	}
	else if (promotedPiece == 'B') {
		newPiece->type = 'B';
		newPiece->color = color;
		newPiece->islegal = bishop_islegal;
		newPiece->Draw = draw_bishop;
	}
	else if (promotedPiece == 'K') {
		newPiece->type = 'N';
		newPiece->color = color;
		newPiece->islegal = knight_islegal;
		newPiece->Draw = draw_horse;
	}

	B[r1][c1] = newPiece;
}


void saveBoard(piece* B[GRID_SIZE][GRID_SIZE], int turn) {
	ofstream rdr("a.txt");

	if (!rdr.is_open()) {
		cout << "Failed to open file!" << endl;
		return;
	}

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (B[i][j] != nullptr) {
				if (B[i][j]->color == BLACK)
					rdr << (char)toupper(B[i][j]->type) << " ";
				else
					rdr << (char)tolower(B[i][j]->type) << " ";
			}
			else {
				rdr << ". ";
			}
		}
		rdr << endl;
	}

	rdr << turn << endl;
	rdr.close();
}
void loadBoard(piece* B[GRID_SIZE][GRID_SIZE], int& turn) {
	ifstream rdr("a.txt");

	if (!rdr.is_open()) {
		cout << "Failed to open the save file!" << endl;
		return;
	}

	char ch;
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			rdr >> ch;

			if (ch != '.') {
				piece* newPiece = new piece;
				newPiece->type = ch;
				newPiece->color = (ch >= 'A' && ch <= 'Z') ? BLACK : WHITE;

				switch (toupper(ch)) {
				case 'R': newPiece->islegal = rook_islegal;
					newPiece->Draw = draw_rook; break;
				case 'N': newPiece->islegal = knight_islegal;
					newPiece->Draw = draw_horse; break;
				case 'B': newPiece->islegal = bishop_islegal;
					newPiece->Draw = draw_bishop; break;
				case 'Q': newPiece->islegal = queen_islegal;
					newPiece->Draw = draw_queen; break;
				case 'K': newPiece->islegal = king_islegal;
					newPiece->Draw = draw_king; break;
				case 'P': newPiece->islegal = pawn_islegal;
					newPiece->Draw = draw_pawn; break;
				default:
					delete newPiece;
					newPiece = nullptr;
					break;
				}

				B[i][j] = newPiece;
			}
			else {
				B[i][j] = nullptr;
			}
		}
	}

	rdr >> turn;
	rdr.close();
}

bool dekho_king_hai(piece* B[][GRID_SIZE]) {
	bool white_king_hai = false;
	bool black_king_hai = false;


	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (B[i][j] != nullptr) {
				if (B[i][j]->type == 'K' or B[i][j]->type == 'k') {
					if (B[i][j]->color == WHITE)
						white_king_hai = true;

					else if (B[i][j]->color == BLACK)
						black_king_hai = true;

				}
			}
		}
	}

	return !(white_king_hai and black_king_hai);
}

void menu() {
	cout << "1. NEW GAME" << endl;
	cout << "2. SAVE" << endl;
	cout << "0. QUIT" << endl;
}
void draw_save_button() {
	int sr = 2;
	int sc = 195;
	char sym = -37;

	color(14);

	gotoRowCol(sr - 1, sc);
	cout << sym;

	gotoRowCol(sr, sc - 1);
	cout << sym << sym << sym;

	gotoRowCol(sr + 1, sc - 2);
	cout << sym << sym << " " << sym << sym;

	gotoRowCol(sr + 2, sc - 1);
	cout << sym << sym << sym;

	gotoRowCol(sr + 3, sc);
	cout << sym;

}
void displayChessBackground() {
	cout << "\n\n\n";
	cout << "           #######################           "<<endl;
	cout << "          ##                     ##        " << endl;
	cout << "         ##                       ##       " << endl;
	cout << "        ##       CHESS GAME        ##      " << endl;
	cout << "         ##                       ##       " << endl;
	cout << "          ##                     ##        " << endl;
	cout << "           ######################           " << endl;
	cout << "\n\n\n";
}
void showInstructions() {
	color(5);
	cout << "Chess Game Instructions:\n";
	cout << "1. The game is played between two players.\n";
	cout << "2. Players take turns to move their pieces on the board.\n";
	cout << "3. The goal is to checkmate your opponent's king.\n";
	cout << "4. Each piece has its own movement rules:\n";
	cout << "   - King: One square in any direction.\n";
	cout << "   - Queen: Any number of squares in any direction.\n";
	cout << "   - Rook: Any number of squares vertically or horizontally.\n";
	cout << "   - Bishop: Any number of squares diagonally.\n";
	cout << "   - Knight: Moves in an 'L' shape (two squares in one direction and then one square perpendicular).\n";
	cout << "   - Pawn: Moves one square forward, but captures diagonally.\n";
	cout << "5. The game ends when a king is checkmated, or a draw is declared.\n";
	
	color(3);
	cout << " 6. Undo tub hi karo , agar goti na maari ho, warna game aur pc ka hawala aap per \n";
	color(5);
	cout << "\nPress any key to return to the menu.\n";
	_getch(); // Wait for user to press a key
}

piece* boardHistory[MAX_MOVES][GRID_SIZE][GRID_SIZE]; 
int currentState = 0;
char currentPlayer = 'W'; 
bool undo_kar_sakte_hain = false; 
void saveState(piece* B[GRID_SIZE][GRID_SIZE]) {
	if (currentState < MAX_MOVES - 1) {
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				boardHistory[currentState][i][j] = B[i][j];
			}
		}
		currentState++;
		undo_kar_sakte_hain = true; 
	}
}
bool undo(piece* B[GRID_SIZE][GRID_SIZE]) {
	if (undo_kar_sakte_hain && currentState > 1) { 
		currentState--;
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				B[i][j] = boardHistory[currentState - 1][i][j];
			}
		}
		undo_kar_sakte_hain = false;
		return true;
	}
	return false; 
}

int main() {
	displayChessBackground();
	menu();
	int ch;
	int z = 0;
	bool** highlight = nullptr;
	cin >> ch;
	system("cls");
	int r = 0, c = 0;
	int r1 = 0, c1 = 0;
	ifstream rdr("a.txt");
	piece* B[GRID_SIZE][GRID_SIZE];
	showInstructions();
	system("cls");
	int Turn = 0, number_of_players = 2;
	string names[2] = { "Player 1", "Player 2" };
	if (ch == 1)
		init(B, Turn);

	else if (ch == 2)
		loadBoard(B, Turn);
	else
		return 0;

	bool hehe_boi = true;
		
	do {
		grid();
		calculate_grid_index(B);
		saveState(B);
		printB(B);
		draw_save_button();
		display_turn(names[Turn % number_of_players]);
		bool validMove = false;
		bool just_making;

		do {

			getRowColbyLeftClick(r, c);
			// game save karega
			if (r >= 1 and r <= 6 and c <= 196 and c >= 192) {
				saveBoard(B, Turn);
				system("cls");
				Sleep(100);
				gotoRowCol(GRID_SIZE / 2, GRID_SIZE / 2);
				cout << "Game saved successfully!" << endl;
				Sleep(1000);
				return 0;
			}


			r /= GRID_SIZE;
			c /= GRID_SIZE;

			// highlight karega
			highlight = computeHighlight(B, r, c);
			printBoard(highlight);
			calculate_grid_index(B);
			saveState(B);
			getRowColbyLeftClick(r1, c1);
			remove_board(highlight, r, c);


			calculate_grid_index(B);
			saveState(B);
			r1 /= GRID_SIZE;
			c1 /= GRID_SIZE;

			if (isValid(r, c, B, Turn, r1, c1)) {
				if (B[r][c]->islegal(B, r, c, r1, c1)) {

					if (isSelfCheck(B, r, c, r1, c1, B[r][c]->color)) {
						gotoRowCol(10, 130);
						cout << "Move places your king in check!" << endl;
						Sleep(1000);
						gotoRowCol(10, 130);
						cout << "                             " << endl;
					}
					else {

						if (B[r1][c1] != nullptr)
							delete B[r1][c1];

						B[r1][c1] = B[r][c];
						B[r][c] = nullptr;
						validMove = true;


						//calculate_grid_index(B);

						COLOR opp_color;
						if (B[r1][c1]->color == WHITE)
							opp_color = BLACK;
						else
							opp_color = WHITE;

						if ((B[r1][c1]->type == 'P' and r1 == 0) or (B[r1][c1]->type == 'p' and r1 == GRID_SIZE - 1))
							handlePawnPromotion(B, r1, c1, B[r1][c1]->color);

						else if ((B[r1][c1]->type == 'P' and r1 == GRID_SIZE - 1) or (B[r1][c1]->type == 'p' and r1 == 0))
							handlePawnPromotion(B, r1, c1, B[r1][c1]->color);

						if (dekho_king_hai(B)) {
							system("cls");
							hehe_boi = false;
							cout << "Checkmate! " << names[Turn % number_of_players] << " wins hehehe!" << endl;
							break;
						}

						if (checkmate(B, opp_color)) {
							gotoRowCol(10, 130);
							cout << "Checkmate! " << names[Turn % number_of_players] << " wins!" << endl;
							hehe_boi = false;
							break;
						}

					
						bool boiz = false;
						calculate_grid_index(B);
						saveState(B);

						int t = time(0) + 1;
						int j = 0;

						for (int i = time(0); i < t; i = time(0)) {

							if (_kbhit()) {
								ch = _getch();
								if (ch == 'u') {
									if (undo(B)) {
										calculate_grid_index(B);
										saveState(B);
										boiz = true;
									}

								}
							}
						}

						if(!boiz){
							saveState(B);
							Turn = turn_change(Turn);
						}

				
					}
				}
				else {
					gotoRowCol(10, 130);
					cout << "Invalid move for this piece!" << endl;
					Sleep(1000);
					gotoRowCol(20, 130);
					cout << "                             " << endl;
				}
			}
			else {
				gotoRowCol(10, 130);
				cout << "Invalid move!" << endl;
				Sleep(1000);
				gotoRowCol(10, 130);
				cout << "                             " << endl;
			}

		} while (!validMove);


	} while (hehe_boi);


	
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			delete B[i][j];
		}
	}

	return 0;
}






