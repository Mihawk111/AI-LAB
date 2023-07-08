#include <bits/stdc++.h>
using namespace std;


// Piece Types ...
#define KING 'K'
#define QUEEN 'Q'
#define BISHOP 'B'
#define HORSE 'H'
#define ROOK 'R'
#define PAWN 'P'
#define EMPTY_TYPE 'E'


// Piece Identifiers ...
// string WHITE_KING("♔ ");
string WHITE_KING("WK");
string WHITE_QUEEN("WQ");
string WHITE_BISHOP("WB");
string WHITE_HORSE("WH");
string WHITE_ROOK("WR");
string WHITE_PAWN("WP");

string BLACK_KING("BK");
string BLACK_QUEEN("BQ");
string BLACK_BISHOP("BB");
string BLACK_HORSE("BH");
string BLACK_ROOK("BR");
string BLACK_PAWN("BP");

// string WHITE_EMPTY("==");
// string BLACK_EMPTY("||");
string EMPTY("--");


// Player Identifiers ...
#define WHITE 'W'
#define BLACK 'B'
vector<int> NO_MOVE({-1, -1, -1, -1});


// Game Scores ...
#define SCORE_WIN 100
#define SCORE_LOSE -100
#define SCORE_DRAW 0

unordered_map<char, int> pieceScore({
    {KING, 0}, 
    {QUEEN, 10}, 
    {BISHOP, 4}, 
    {HORSE, 5}, 
    {ROOK, 3}, 
    {PAWN, 1}, 
});


bool isWhitePiece(string &piece){ return piece[0] == 'W'; }
bool isBlackPiece(string &piece){ return piece[0] == 'B'; }
// bool isEmptyPiece(string &piece){ return piece[0] == '=' || piece[0] == '|'; }
bool isEmptyPiece(string &piece){ return piece[0] == '-'; }
char getPiecePlayer(string &piece){ return isEmptyPiece(piece)? EMPTY_TYPE: piece[0]; }


char getPieceType(string &piece){ return (isEmptyPiece(piece))? EMPTY_TYPE: piece[1]; }


void initializeChessBoard(vector<vector<string>> &b)
{
    b.resize(8);
    for(vector<string> &v: b) v.resize(8), fill(v.begin(), v.end(), EMPTY);




    b[0][0] = BLACK_ROOK;
    b[0][1] = BLACK_HORSE;
    b[0][2] = BLACK_BISHOP;
    b[0][3] = BLACK_QUEEN;
    b[0][4] = BLACK_KING;
    b[0][5] = BLACK_BISHOP;
    b[0][6] = BLACK_HORSE;
    b[0][7] = BLACK_ROOK;

    b[1][0] = BLACK_PAWN;
    b[1][1] = BLACK_PAWN;
    b[1][2] = BLACK_PAWN;
    b[1][3] = BLACK_PAWN;
    b[1][4] = BLACK_PAWN;
    b[1][5] = BLACK_PAWN;
    b[1][6] = BLACK_PAWN;
    b[1][7] = BLACK_PAWN;




    b[7][0] = WHITE_ROOK;
    b[7][1] = WHITE_HORSE;
    b[7][2] = WHITE_BISHOP;
    b[7][3] = WHITE_QUEEN;
    b[7][4] = WHITE_KING;
    b[7][5] = WHITE_BISHOP;
    b[7][6] = WHITE_HORSE;
    b[7][7] = WHITE_ROOK;

    b[6][0] = WHITE_PAWN;
    b[6][1] = WHITE_PAWN;
    b[6][2] = WHITE_PAWN;
    b[6][3] = WHITE_PAWN;
    b[6][4] = WHITE_PAWN;
    b[6][5] = WHITE_PAWN;
    b[6][6] = WHITE_PAWN;
    b[6][7] = WHITE_PAWN;
}


void displayChessBoard(vector<vector<string>> &b){ for(int i = 0; i < 8; i++) { for(int j = 0; j < 8; j++) cout << b[i][j] << "  ";  cout << endl << endl; } }


bool moveBoard(int x1, int y1, int x2, int y2, vector<vector<string>> &b)
{
    if(isEmptyPiece(b[x1][y1])) return false;

    char playerTypeSrc = getPiecePlayer(b[x1][y1]);
    char playerTypeDest = getPiecePlayer(b[x2][y2]);

    if(playerTypeDest == playerTypeSrc) return false;
    
    b[x2][y2] = b[x1][y1], b[x1][y1] = EMPTY;
    return true;
}


vector<pair<int, int>> getPossibleMoves(int x, int y, vector<vector<string>> &b)
{
    string piece = b[x][y];
    if(isEmptyPiece(piece)) return {};

    char playerType = getPiecePlayer(piece), opponentType = (playerType == WHITE)? BLACK: WHITE, playerPieceType = getPieceType(piece);

    vector<pair<int, int>> allMoves;
    switch(playerPieceType)
    {
    case KING:
        for(int dx: {1, 0, -1}) for(int dy: {1, 0, -1})
        if((dx || dy) && x + dx >= 0 && x + dx < 8 && y + dy >= 0 && y + dy < 8 && getPiecePlayer(b[x + dx][y + dy]) != playerType) allMoves.push_back({x + dx, y + dy});

        break;
    
    
    case QUEEN:
        // Up ...
        for(int k = 1; k < 8; k++) 
        {
            if(x - k < 0 || getPiecePlayer(b[x - k][y]) == playerType) break;
            if(getPiecePlayer(b[x - k][y]) == opponentType){ allMoves.push_back({x - k, y}); break; }
            allMoves.push_back({x - k, y});
        }
        
        // Down ...
        for(int k = 1; k < 8; k++) 
        {
            if(x + k >= 8 || getPiecePlayer(b[x + k][y]) == playerType) break;
            if(getPiecePlayer(b[x + k][y]) == opponentType){ allMoves.push_back({x + k, y}); break; }
            allMoves.push_back({x + k, y});
        }

        // Left ...
        for(int k = 1; k < 8; k++) 
        {
            if(y - k < 0 || getPiecePlayer(b[x][y - k]) == playerType) break;
            if(getPiecePlayer(b[x][y - k]) == opponentType){ allMoves.push_back({x, y - k}); break; }
            allMoves.push_back({x, y - k});
        }

        // Right ...
        for(int k = 1; k < 8; k++) 
        {
            if(y + k >= 8 || getPiecePlayer(b[x][y + k]) == playerType) break;
            if(getPiecePlayer(b[x][y + k]) == opponentType){ allMoves.push_back({x, y + k}); break; }
            allMoves.push_back({x, y + k});
        }

        // Up - Right ...
        for(int k = 1; k < 8; k++) 
        {
            if(x - k < 0 || y + k >= 8 || getPiecePlayer(b[x - k][y + k]) == playerType) break;
            if(getPiecePlayer(b[x - k][y + k]) == opponentType){ allMoves.push_back({x - k, y + k}); break; }
            allMoves.push_back({x - k, y + k});
        }
        
        // Down - Right ...
        for(int k = 1; k < 8; k++) 
        {
            if(x + k >= 8 || y + k >= 8 || getPiecePlayer(b[x + k][y + k]) == playerType) break;
            if(getPiecePlayer(b[x + k][y + k]) == opponentType){ allMoves.push_back({x + k, y + k}); break; }
            allMoves.push_back({x + k, y + k});
        }

        // Up - Left ...
        for(int k = 1; k < 8; k++) 
        {
            if(x - k < 0 || y - k < 0 || getPiecePlayer(b[x - k][y - k]) == playerType) break;
            if(getPiecePlayer(b[x - k][y - k]) == opponentType){ allMoves.push_back({x - k, y - k}); break; }
            allMoves.push_back({x - k, y - k});
        }

        // Down - Left ...
        for(int k = 1; k < 8; k++) 
        {
            if(x + k >= 8 || y - k < 0 || getPiecePlayer(b[x + k][y - k]) == playerType) break;
            if(getPiecePlayer(b[x + k][y - k]) == opponentType){ allMoves.push_back({x + k, y - k}); break; }
            allMoves.push_back({x + k, y - k});
        }

        break;

    
    case BISHOP:
        // Up - Right ...
        for(int k = 1; k < 8; k++) 
        {
            if(x - k < 0 || y + k >= 8 || getPiecePlayer(b[x - k][y + k]) == playerType) break;
            if(getPiecePlayer(b[x - k][y + k]) == opponentType){ allMoves.push_back({x - k, y + k}); break; }
            allMoves.push_back({x - k, y + k});
        }
        
        // Down - Right ...
        for(int k = 1; k < 8; k++) 
        {
            if(x + k >= 8 || y + k >= 8 || getPiecePlayer(b[x + k][y + k]) == playerType) break;
            if(getPiecePlayer(b[x + k][y + k]) == opponentType){ allMoves.push_back({x + k, y + k}); break; }
            allMoves.push_back({x + k, y + k});
        }

        // Up - Left ...
        for(int k = 1; k < 8; k++) 
        {
            if(x - k < 0 || y - k < 0 || getPiecePlayer(b[x - k][y - k]) == playerType) break;
            if(getPiecePlayer(b[x - k][y - k]) == opponentType){ allMoves.push_back({x - k, y - k}); break; }
            allMoves.push_back({x - k, y - k});
        }

        // Down - Left ...
        for(int k = 1; k < 8; k++) 
        {
            if(x + k >= 8 || y - k < 0 || getPiecePlayer(b[x + k][y - k]) == playerType) break;
            if(getPiecePlayer(b[x + k][y - k]) == opponentType){ allMoves.push_back({x + k, y - k}); break; }
            allMoves.push_back({x + k, y - k});
        }

        break;

    
    case HORSE:
    int dx, dy;
        for(pair<int, int> p: vector<pair<int, int>>({{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}}))
        { dx = p.first, dy = p.second; if(x + dx >= 0 && x + dx < 8 && y + dy >= 0 && y + dy < 8 && getPiecePlayer(b[x + dx][y + dy]) != playerType) allMoves.push_back({x + dx, y + dy}); }

        break;

    
    case ROOK:
        // Up ...
        for(int k = 1; k < 8; k++) 
        {
            if(x - k < 0 || getPiecePlayer(b[x - k][y]) == playerType) break;
            if(getPiecePlayer(b[x - k][y]) == opponentType){ allMoves.push_back({x - k, y}); break; }
            allMoves.push_back({x - k, y});
        }
        
        // Down ...
        for(int k = 1; k < 8; k++) 
        {
            if(x + k >= 8 || getPiecePlayer(b[x + k][y]) == playerType) break;
            if(getPiecePlayer(b[x + k][y]) == opponentType){ allMoves.push_back({x + k, y}); break; }
            allMoves.push_back({x + k, y});
        }

        // Left ...
        for(int k = 1; k < 8; k++) 
        {
            if(y - k < 0 || getPiecePlayer(b[x][y - k]) == playerType) break;
            if(getPiecePlayer(b[x][y - k]) == opponentType){ allMoves.push_back({x, y - k}); break; }
            allMoves.push_back({x, y - k});
        }

        // Right ...
        for(int k = 1; k < 8; k++) 
        {
            if(y + k >= 8 || getPiecePlayer(b[x][y + k]) == playerType) break;
            if(getPiecePlayer(b[x][y + k]) == opponentType){ allMoves.push_back({x, y + k}); break; }
            allMoves.push_back({x, y + k});
        }

        break;

    
    case PAWN:
        if(playerType == WHITE)
        {
            if(x - 1 >= 0)
            {
                if(getPiecePlayer(b[x - 1][y]) == EMPTY_TYPE) allMoves.push_back({x - 1, y});
                if(y + 1 < 8 && getPiecePlayer(b[x - 1][y + 1]) == opponentType) allMoves.push_back({x - 1, y + 1});
                if(y - 1 >= 0 && getPiecePlayer(b[x - 1][y - 1]) == opponentType) allMoves.push_back({x - 1, y - 1});
            }
        }
        else
        {
            if(x + 1 < 8)
            {
                if(getPiecePlayer(b[x + 1][y]) == EMPTY_TYPE) allMoves.push_back({x + 1, y});
                if(y + 1 < 8 && getPiecePlayer(b[x + 1][y + 1]) == opponentType) allMoves.push_back({x + 1, y + 1});
                if(y - 1 >= 0 && getPiecePlayer(b[x + 1][y - 1]) == opponentType) allMoves.push_back({x + 1, y - 1});
            }
        }
        break;
    }

    return allMoves;
}