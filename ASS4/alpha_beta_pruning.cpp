#include "game_constants.hpp"
using namespace std;


char curGameState(vector<vector<string>> &b)
{
    bool whiteKingFound = false, blackKingFound = false;
    for(int i = 0; i < 8; i++) for(int j = 0; j < 8; j++) if(b[i][j] == WHITE_KING) whiteKingFound = true; else if(b[i][j] == BLACK_KING) blackKingFound = true;

    if(!whiteKingFound) return BLACK;
    else if(!blackKingFound) return WHITE;
    else return EMPTY_TYPE;
}


int computeScore(vector<vector<string>> &b, char turn)
{
    // Check extremes ...
    char status = curGameState(b);
    if(status != EMPTY_TYPE) return (status == turn)? SCORE_WIN: SCORE_LOSE;


    // How many weighted pieces are left ...
    int score = 0;
    for(int i = 0; i < 8; i++) for(int j = 0; j < 8; j++) if(!isEmptyPiece(b[i][j]))
    score += pieceScore[getPieceType(b[i][j])] * ((getPiecePlayer(b[i][j]) == turn)? 1: -1);

    return score;
}


pair<int, vector<int>> minMaxHelper(int curDepth, bool doMax, char aiTurn, char playerTurn, vector<vector<string>> &b, int alpha = INT_MIN, int beta = INT_MAX)
{
    // returns score , <Src X, Src Y, Dest X, Dest Y> to give turn ...

    char curState = curGameState(b);

    // Prune it ...
    if(curDepth == 1 || curState != EMPTY_TYPE) return {computeScore(b, (doMax)? aiTurn: playerTurn), NO_MOVE};
    // if(curDepth == 1 || curState != EMPTY_TYPE) return {computeScore(b, aiTurn), NO_MOVE};

    int minMax = (doMax)? INT_MIN: INT_MAX, childVal; vector<int> move = NO_MOVE; char curPlayer = (doMax)? aiTurn: playerTurn; string srcPiece, destPiece;
    for(int i = 0; i < 8; i++) for(int j = 0; j < 8; j++) if(getPiecePlayer(b[i][j]) == curPlayer)
    {
        for(pair<int, int> curMove: getPossibleMoves(i, j, b))
        {
            srcPiece = b[i][j], destPiece = b[curMove.first][curMove.second];  // Remember ...
            moveBoard(i, j, curMove.first, curMove.second, b);

            childVal = minMaxHelper(curDepth - 1, !doMax, aiTurn, playerTurn, b, alpha, beta).first;
            if(doMax){ if(childVal == minMax){ if(rand() % 1) minMax = childVal, move = {i, j, curMove.first, curMove.second}; }
                if(childVal > minMax) minMax = childVal, move = {i, j, curMove.first, curMove.second}; alpha = max(alpha, minMax); }
            else{      if(childVal == minMax){ if(rand() % 1) minMax = childVal, move = {i, j, curMove.first, curMove.second}; }
                if(childVal < minMax) minMax = childVal, move = {i, j, curMove.first, curMove.second}; beta = min(beta, minMax); }

            b[i][j] = srcPiece; b[curMove.first][curMove.second] = destPiece;

            if(beta <= alpha) return {minMax, move};  // Alpha Beta Pruning ...
        }
    }

    return {minMax, move};
}


bool updateNextMove(vector<vector<string>> &b, int maxDepth, char aiTurn, char playerTurn)
{
    // Move Format -> {Src X, Src Y, Dest X, Dest Y}
    pair<int, vector<int>> p = minMaxHelper(maxDepth, true, aiTurn, playerTurn, b);

    if(p.second == NO_MOVE) return false;

    moveBoard(p.second[0], p.second[1], p.second[2], p.second[3], b);
    return true;
}


int main()
{
    // freopen("lol_ab.txt", "w", stdout);
    srand(time(0));
    vector<vector<string>> board;
    initializeChessBoard(board); // board[1][4] = EMPTY;




    char aiTurn = WHITE, playerTurn = BLACK; int cnt = 0;  // Depth = 7 (<1s) , 8 (2-3s)
    while(updateNextMove(board, 7, aiTurn, playerTurn) && cnt < 300)
    {
        cout << "Turn #" << ++cnt << " --> [" << ((cnt % 2)? "WHITE": "BLACK") << "]" << endl << endl;
        displayChessBoard(board);
        cout << endl << endl;
        cout << "___________________________________________________" << endl;
        cout << endl << endl;

        swap(aiTurn, playerTurn);

        getchar();
    }

    cout << "DONE !!!" << endl;




    // board[2][0] = WHITE_PAWN;
    // displayChessBoard(board);
    // cout << "Score: " << computeScore(board, WHITE) << endl;
    // cout << "Moves -> "; for(pair<int, int> move: getPossibleMoves(1, 1, board)) cout << "(" << (move.first + 1) << "," << (move.second + 1) << ") , "; cout << endl;
}