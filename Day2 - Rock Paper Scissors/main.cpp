#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/* Global Variables for RPS */
char OPPONENT_ROCK = 'A';
char OPPONENT_PAPER = 'B';
char OPPONENT_SCISSORS = 'C';

char YOU_LOSE = 'X';
char YOU_DRAW = 'Y';
char YOU_WIN = 'Z';

int ROCK_SCORE = 1;
int PAPER_SCORE = 2;
int SCISSORS_SCORE = 3;

int WIN = 6;
int DRAW = 3;
int LOSS = 0;

/* get individual outcomes for each scenario and store it */
/* in vector outcomes */
void get_total_score(ifstream &fp, vector<int> &outcomes){
    string line;
    char opponent, you;
    int counter = 0;
    while(getline(fp, line)){
        int outcome = 0;
        /* get opponent and your character */
        opponent = line[0];
        you = line[2];

        /* opponent throws rock */
        if(opponent == OPPONENT_ROCK){
            /* youre supposed to lose */
            if(you == YOU_LOSE){
                outcome += SCISSORS_SCORE;
                outcome += LOSS;

            /* youre supposed to draw */
            }else if(you == YOU_DRAW){
                outcome += ROCK_SCORE;
                outcome += DRAW;

            /* youre supposed to win */
            }else{
                outcome += PAPER_SCORE;
                outcome += WIN;
            }
        /* opponent throws paper */
        }else if(opponent == OPPONENT_PAPER){
            /* youre supposed to lose */
            if(you == YOU_LOSE){
                outcome += ROCK_SCORE;
                outcome += LOSS;

            /* youre supposed to draw */
            }else if(you == YOU_DRAW){
                outcome += PAPER_SCORE;
                outcome += DRAW;

            /* youre supposed to win */
            }else{
                outcome += SCISSORS_SCORE;
                outcome += WIN;
            }
        /* opponent throws scissors */
        }else if(opponent == OPPONENT_SCISSORS){
            /* youre supposed to lose */
            if(you == YOU_LOSE){
                outcome += PAPER_SCORE;
                outcome += LOSS;

            /* youre supposed to draw */
            }else if(you == YOU_DRAW){
                outcome += SCISSORS_SCORE;
                outcome += DRAW;

            /* youre supposed to win */
            }else{
                outcome += ROCK_SCORE;
                outcome += WIN;
            }
        }

        outcomes.push_back(outcome);
        /* increment scenario */
        counter++;
    }
}

int main(int argc, char* argv[]){
    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening  file!" << endl;
        exit(EXIT_FAILURE);
    }

    /* Vector containing outcomes for each RPS scenario */
    vector<int> outcomes;

    /* get individual scores */
    get_total_score(fp, outcomes);

    /* loop through individual outcomes and add up the total score */
    int total = 0;
    for(int i = 0; i < outcomes.size(); i++){
        total += outcomes[i];
    }

    cout << "Total Score: " << total << endl;

    return 0;
}
