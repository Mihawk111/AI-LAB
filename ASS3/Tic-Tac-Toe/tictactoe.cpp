#include <bits/stdc++.h>
using namespace std;

#define CROSS 'X'
#define CRISS 'O'
#define EMPTY '_'
#define DRAW 'D'


#define SCORE_WIN 200
#define SCORE_LOSE -200
#define SCORE_DRAW 1
#define PATH_WIN 2
#define PATH_LOSE -2


pair<int, int> NO_MOVE(-1, -1);


char curGameState(vector<vector<char>> &b)
{
    for(char turn: {CROSS, CRISS})
    {
        if(b[1][1] == turn)
        {
            if((b[0][0] == turn && b[2][2] == turn) || 
               (b[0][2] == turn && b[2][0] == turn) || 
               (b[0][1] == turn && b[2][1] == turn) || 
               (b[1][0] == turn && b[1][2] == turn)) return turn;
        }

        if((b[0][0] == turn && ((b[0][1] == turn && b[0][2] == turn) || (b[1][0] == turn && b[2][0] == turn))) || 
           (b[2][2] == turn && ((b[2][1] == turn && b[2][0] == turn) || (b[1][2] == turn && b[0][2] == turn)))) return turn;
    }

    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(b[i][j] == EMPTY) return EMPTY;
    return DRAW;
}


int computeScore(vector<vector<char>> &b, char turn)
{
    // Check extremes ...
    char status = curGameState(b);
    if(status == DRAW) return SCORE_DRAW;
    else if(status != EMPTY) return (status == turn)? SCORE_WIN: SCORE_LOSE;
    


    int score = 0;
    for(vector<pair<int, int>> path: vector<vector<pair<int, int>>>({
        {{0, 0}, {1, 0}, {2, 0}}, {{0, 1}, {1, 1}, {2, 1}}, {{0, 2}, {1, 2}, {2, 2}}, 
        {{0, 0}, {0, 1}, {0, 2}}, {{1, 0}, {1, 1}, {1, 2}}, {{2, 0}, {2, 1}, {2, 2}}, 
        {{0, 0}, {1, 1}, {2, 2}}, {{2, 0}, {1, 1}, {0, 2}}
    }))
    {
        int numTurn = 0, numEmpty = 0;
        for(char entry: {b[path[0].first][path[0].second], b[path[1].first][path[1].second], b[path[2].first][path[2].second]})
            if(entry == turn) numTurn++; else if(entry == EMPTY) numEmpty++;

        if(numTurn + numEmpty == 3 && numEmpty && numEmpty != 3) score += PATH_WIN;
        else if(!numTurn && numEmpty && numEmpty != 3) score += PATH_LOSE;
    }

    return score;
}


pair<int, pair<int, int>> minMaxHelper(int curDepth, bool doMax, char aiTurn, char playerTurn, vector<vector<char>> &b)
{
    // returns score , <row, column> to give turn ...

    char curState = curGameState(b);

    // Prune it ...
    if(curDepth == 1 || curState != EMPTY) return {computeScore(b, aiTurn), NO_MOVE};

    int minMax = (doMax)? INT_MIN: INT_MAX, childVal; pair<int, int> move = NO_MOVE;
    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(b[i][j] == EMPTY)
    {
        b[i][j] = (doMax)? aiTurn: playerTurn;
        childVal = minMaxHelper(curDepth - 1, !doMax, aiTurn, playerTurn, b).first;
        if(doMax){ if(childVal > minMax) minMax = childVal, move = {i, j}; }
        else{      if(childVal < minMax) minMax = childVal, move = {i, j}; }
        minMax = (doMax)? (max(minMax, childVal)): (min(minMax, childVal));
        b[i][j] = EMPTY;
    }

    return {minMax, move};
}

bool updateNextMove(vector<vector<char>> &b, int maxDepth, char aiTurn, char playerTurn)
{
    pair<int, pair<int, int>> p = minMaxHelper(maxDepth, true, aiTurn, playerTurn, b);

    if(p.second == NO_MOVE) return false;

    b[p.second.first][p.second.second] = aiTurn;
    return true;
}


void printBoard(vector<vector<char>> &b)
{
    for(int i = 0; i < 3; i++) { for(int j = 0; j < 3; j++) cout << b[i][j] << " "; cout << endl; }
}


int main()
{
    vector<vector<char>> board(3, vector<char>(3, EMPTY));

    int maxDepth, x, y; char aiTurn, playerTurn, choice, curState;
    cout << "Enter max depth of game tree: ";
    cin >> maxDepth;
    cout << "Do you want to start first? (Enter y for yes, anything else for no): ";
    cin >> choice;
    cout << endl << "Player inputs are 1 indexed ..." << endl << endl;

    if(choice == 'y')
    {
        aiTurn = CRISS, playerTurn = CROSS;
        while(true)
        {
            cout << "Enter your input <row, column>: ";
            cin >> x >> y; x--, y--;
            board[x][y] = playerTurn;
            cout << "YOU GAVE MOVE -->" << endl;
            printBoard(board); cout << endl << endl << endl;

            curState = curGameState(board);
            if(curState != EMPTY)
            {
                if(curState == playerTurn) cout << "Player Wins !!!" << endl;
                else if(curState == aiTurn) cout << "AI Wins !!!" << endl;
                else cout << "Draw !!!" << endl;

                break;
            }

            // _______________________________________________________________________

            updateNextMove(board, maxDepth, aiTurn, playerTurn);
            cout << "AI GAVE MOVE -->" << endl;
            printBoard(board); cout << endl << endl << endl;

            curState = curGameState(board);
            if(curState != EMPTY)
            {
                if(curState == playerTurn) cout << "Player Wins !!!" << endl;
                else if(curState == aiTurn) cout << "AI Wins !!!" << endl;
                else cout << "Draw !!!" << endl;

                break;
            }
        }
    }
    else
    {
        aiTurn = CROSS, playerTurn = CRISS;
        while(true)
        {
            updateNextMove(board, maxDepth, aiTurn, playerTurn);
            cout << "AI GAVE MOVE -->" << endl;
            printBoard(board); cout << endl << endl << endl;

            curState = curGameState(board);
            if(curState != EMPTY)
            {
                if(curState == playerTurn) cout << "Player Wins !!!" << endl;
                else if(curState == aiTurn) cout << "AI Wins !!!" << endl;
                else cout << "Draw !!!" << endl;

                break;
            }

            // _______________________________________________________________________

            cout << "Enter your input <row, column>: ";
            cin >> x >> y; x--, y--;
            board[x][y] = playerTurn;
            cout << "YOU GAVE MOVE -->" << endl;
            printBoard(board); cout << endl << endl << endl;

            curState = curGameState(board);
            if(curState != EMPTY)
            {
                if(curState == playerTurn) cout << "Player Wins !!!" << endl;
                else if(curState == aiTurn) cout << "AI Wins !!!" << endl;
                else cout << "Draw !!!" << endl;

                break;
            }
        }
    }

    cout << endl << "--> Game Done !!!" << endl;


    return 0;
}