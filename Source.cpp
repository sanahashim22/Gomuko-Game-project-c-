#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<ctime>
using namespace std;
const int capacity = 100;

void init(char b[][capacity], int& dim, char sym[capacity], char pname[][100], int& nop, int& turn,int& wincount) {
	cout << "Enter dim (0...19): " << endl;
	cin >> dim;
	char arr = '-';
	for (int r = 0; r < dim; r++) {

		for (int c =0 ; c < dim; c++)
		{
		      b[r][c] = arr;
			  cout << b[r][c] << " ";
		}
		cout << endl;
	}
	cout << "enter nop" << endl;
	cin >> nop;

	for (int i = 0; i < nop; i++) {
		cout << "Enter player name : ";
		cin >> pname[i];
		cout << "Enter symbol : ";
		cin >> sym[i];
	}
	cout << "Enter winning count : " ;
	cin >> wincount;
	turn = rand() % nop;
}
void printBoard(char b[][capacity], int dim) {
	system("cls");
	for (int r = 0; r < dim; r++) {
		for (int c =0 ; c < dim; c++)
		{
			cout << b[r][c] << " ";
		}
		cout << endl;
	}
}
void turnMsg(char pname[]) {
	cout << pname << "'s turn : " << endl;
}
bool isvalid(char b[][capacity],int dim, int pr, int pc) {
	if (pr<0 || pr>dim) {
		return false;
	}
	if (pc<0 || pc>dim) {
		return false;
	}
	if (b[pr][pc] != '-') {
		return false;
	}
	return true;
}
int selectPosition(char b[][capacity],int& pr, int& pc, int dim) {
	cout << "enter row (1...{dim}) " << endl;
	cin >> pr;
	cout << "enter col (1...{dim}) " << endl;
	cin >> pc;
	pr -= 1;
	pc -= 1;
	while (!isvalid(b, dim, pr, pc)) {
		cout << "Wrong input....." << endl;
		cout << "enter row (1...{dim}) " << endl;
		cin >> pr;
		cout << "enter col (1...{dim}) " << endl;
		cin >> pc;
		pr -= 1;
		pc -= 1;
	}
	return pr, pc;
}
void placeMove(char b[][capacity], int pr, int pc, int dim, char sym) {
	b[pr][pc] = sym;
}
int turnChange(int& turn, int nop) {
	turn == (turn + 1) % nop;
	return turn;
}
bool horiz(char b[][capacity],int pr,int pc,int dim,int wincount,char sym) {
	if (pc + wincount - 1 >= dim) {
		return false;
	}
	for (int i = 0; i < wincount; i++) {
		if (b[pr][pc + i] != sym) {
			return false;
		}
	}
	return true;

}
bool vert(char b[][capacity], int pr, int pc, int dim, int wincount, char sym) {
	if (pr + wincount - 1 >= dim) {
		return false;
	}
	for (int i = 0; i < wincount; i++) {
		if (b[pr + i][pc] != sym) {
			return false;
		}
	}
	return true;

}
bool diag_left(char b[][capacity], int pr, int pc, int dim, int wincount, char sym) {
	if (pr + wincount - 1 >= dim || pc + wincount - 1 >= dim) {
		return false;
	}
	for (int i = 0; i < wincount; i++) {
		if (b[pr + i][pc + i] != sym) {
			return false;
		}
	}
	return true;

}
bool diag_rig(char b[][capacity], int pr, int pc, int dim, int wincount, char sym) {
	if (pr + wincount - 1 > dim || pc - (wincount - 1) < 0 ) {
		return false;
	}
	for (int i = 0; i < wincount; i++) {
		if (b[pr + i][pc - i] != sym) {
			return false;
		}
	}
	return true;
}
bool iswin(char b[][capacity],int dim,char sym, int wincount) {
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			if (horiz(b, r, c, dim, wincount, sym) ||
				vert(b, r, c, dim, wincount, sym) ||
				diag_left(b, r, c, dim, wincount, sym) ||
				diag_rig(b, r, c, dim, wincount, sym)) {
				return true;
			}
		}
	}

	return false;
}
bool draw(char b[][capacity], int dim) {
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			if (b[r][c] == '-')
				return false;
		}
	}
	return true;
}
void main1() {
	//const int capacity = 100;
	char b[capacity][capacity], sym[capacity], pname[capacity][100];
	int dim=0, nop, turn=0, pr=0, pc=0,winCount,winner = -1;
	bool game = false;
	init(b,dim,sym,pname,nop,turn,winCount);
//	printBoard(b, dim);
	do {
		srand(time(0));
		if (turn == 0) {
			printBoard(b, dim);
		//	cout << turn << endl;
			cout << endl;
			turnMsg(pname[turn]);
			pr, pc = selectPosition(b, pr, pc, dim);
			placeMove(b, pr, pc, dim, sym[turn]);
			printBoard(b, dim);
			game = iswin(b, dim, sym[turn], winCount);
			if (game) {
				winner = turn;
			}
			if (!game) {
				game = draw(b, dim);
			}
			if (!game) {
				turn = turnChange(turn, nop);
				turn++;
			}
			
		}
		else {
			printBoard(b, dim);
			//cout << turn << endl;

			cout << endl;
			turnMsg(pname[turn]);
			pr, pc = selectPosition(b, pr, pc, dim);
			placeMove(b, pr, pc, dim, sym[turn]);
			printBoard(b, dim);
			game = iswin(b, dim, sym[turn], winCount);
			if (game) {
				winner = turn;
			}
			if (!game) {
			  game = draw(b, dim);
			}
			if (!game) {
				turn = turnChange(turn, nop);
				turn--;
			}
		}
	} while (!game);

	if (winner == -1) {
		cout << "Game draw...." << endl;
	}
	else {
		cout << "Winner is : " << pname[winner];
	}
}


void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
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
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void init1(char a[][19], int d, string namep[], int nop, char sym[], int& tu)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            a[r][c] = '-';
        }
    }
    for (int r = 1; r < nop; r++)
    {
        cout << "Enter Player " << r << " name :";
        string a;
        cin >> a;
        namep[r] = a;
        cout << "Enter Player " << r << " symbol :";
        char b;
        cin >> b;
        sym[r] = b;
    }
    tu = rand() % nop;

}
void printboard1(char a[][19], int d)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            cout << a[r][c];
        }cout << "\n";
    }
}
void turnmsg1(string a)
{
    cout << a << "'s TURN! \n";
}
void selectposition(int pr, int pc, int d)
{

}
void placemove1(char a[][19], int pr, int pc, char sym)
{
    a[pr][pc] = sym;
}
void turnch(int& tu, int nop)
{
    tu = (tu + 1) % nop;
}
bool isvalid1(char a[][19], int d, int r, int c)
{
    return (r >= 0 && r < d) && (c >= 0 && c < d) && (a[r][c] == '-');
}
bool winhori(char a[][19], int d, int r, int c, char sym, int win)
{
    if (c + win > d)
        return false;
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r][c + i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winver(char a[][19], int d, int r, int c, char sym, int win)
{
    if (r + win > d)
        return false;
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r + i][c] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winLtoR(char a[][19], int d, int r, int c, char sym, int win)
{
    /*if ((c + win > d) or (r + win > d))
        return false;*/
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r + i][c + i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winRtoL(char a[][19], int d, int r, int c, char sym, int win)
{
    /*if ((c - win <0) or (r + win > d))
        return false;*/
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r + i][c - i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool win(char a[][19], int d, char smb[], int win, int t)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (winhori(a, d, r, c, smb[t], win))
                return true;
            if (winver(a, d, r, c, smb[t], win))
                return true;
            if (winLtoR(a, d, r, c, smb[t], win))
                return true;
            if (winRtoL(a, d, r, c, smb[t], win))
                return true;
        }
    }
    return false;
}
bool draw1(char a[][19], int d)
{
    int count = 0;
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (a[r][c] == '-')
                count++;
        }
    }
    if (count == 0)
        return true;
    else
        return false;
}
void computer(char a[][19], int d, int& R, int& C, char sym[], int winl, int turn, int nop)
{

    for (int w = winl; w > 1; w--)
    {
        for (int r = 0; r < d; r++)
        {
            for (int c = 0; c < d; c++)
            {
                if (isvalid1(a, d, r, c))
                {
                    a[r][c] = sym[turn];
                    if (win(a, d, sym, w, turn))
                    {
                        a[r][c] = '-';
                        R = r; C = c;

                    }
                    a[r][c] = '-';
                }
            }
        }int t2 = 0;
        if (turn < nop)
        {
            t2++;
            for (int r = 0; r < d; r++)
            {
                for (int c = 0; c < d; c++)
                {
                    if (isvalid1(a, d, r, c))
                    {
                        a[r][c] = sym[t2];
                        if (win(a, d, sym, w, t2))
                        {
                            a[r][c] = '-';
                            R = r; C = c;
                            return;
                        }
                        a[r][c] = '-';
                    }
                }
            }
        }
    }


}

void main2()
{
    char B[19][19];
    int dim, nop, turn = 0, row = 0, col = 0, winl = 0, gm = 0;
    cout << "Enter Dimention: ";
    cin >> dim;
    if (dim == 3)
    {
        winl = 3;
    }
    else
    {
        cout << "Enter win Lenght smaller then " << dim << "\n";
        cin >> winl;
    }
    cout << "Enter Number of Players: ";
    cin >> nop;

    const int l = 5;
    string PN[l];
    PN[0] = "Computer";
    char Sym[l];
    Sym[0] = '*';
    init1(B, dim, PN, nop, Sym, turn);
    while (gm == 0)
    {
        system("Cls");
        printboard1(B, dim); cout << "\n";
        turnmsg1(PN[turn]);
        if (turn == 0)
        {
            computer(B, dim, row, col, Sym, winl, turn, nop);
        }
        else {
            do
            {
                getRowColbyLeftClick(row, col);
            } while (!isvalid1(B, dim, row, col));
        }
        placemove1(B, row, col, Sym[turn]);
        if (win(B, dim, Sym, winl, turn))
        {
            system("Cls");
            printboard1(B, dim);
            cout << "\n\nPlayer " << turn + 1 << " " << PN[turn] << " WINS!\n\n";
            gm = 1;
        }
        if (draw1(B, dim))
        {
            system("Cls");
            printboard1(B, dim);
            cout << "\n\nGame Draw \n\n";
            gm = 1;
        }
        turnch(turn, nop);

    }
}



int main() {
    int choice;

    cout << "Enter 1 for player vs player game: " << endl;
    cout << "Enter 2 for player vs computer game: " << endl;
    cout << "Enter choice: " << endl;
    cin >> choice;
    if (choice == 1) {
        main1();
    }
    if (choice == 2) {
        main2();
    }


    return 0;
}