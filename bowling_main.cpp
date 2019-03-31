#include<iostream>

using namespace std;


class Player{
    int score;
    string scorecard;

    public:
    Player(){
        score = 0;
        scorecard = "";
    }
    int get_score(int, int);
    int print_score();
    void print_scorecard();
    void start_score(){
        scorecard+='{';
    }
    void end_score(){
        scorecard+="},";
    }

};

int max_score = 0;
int max_player = 0;

int Player::get_score(int max, int n){
    int temp;
    cin >> temp;
    if(temp > max){
        cout<<"OOps wrong score.. Score out of Bounds, considering this score to be 0"<<endl;
        temp = 0;
    }
    if(temp == 10 && n==1){
        score+=20;
        scorecard+="X,";
    }
    else if(temp == max){
        score+=(max+5);
        scorecard+="/,";
    }
    else{
        score+=temp;
        scorecard+='0'+temp;
        scorecard+=',';
    }
    return temp;
}


int Player::print_score(){
    return score;
}



void Player::print_scorecard(){
    cout<<scorecard<<"            ---> "<<score<<endl;
}



void scorecard(Player p[], int n){
    cout<<endl<<"Scorecard"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"P"<<i+1<<":  ";
        p[i].print_scorecard();
    }
    cout<<endl;
}



void gameplay(Player p[], int n, int rounds, int round){

    for(int player = 0; player < n; player++){
        p[player].start_score();
        int fchance, schance, tchance, lchance, remaining, remaining2;
        
        //In last round
        if(round == rounds-1){
            cout<<"Enter Score for Player"<<player+1<<" - Chance 1: ";
            fchance = p[player].get_score(10, 1);
            
            remaining = (((10-fchance)+9)%10)+1;
            
            cout<<"Enter Score for Player"<<player+1<<" - Chance 2: ";
            if(remaining == 10)
                schance = p[player].get_score(remaining,2);
            else
                schance = p[player].get_score(remaining, 1);

            if(schance == remaining){
                cout<<"Enter Score for Player"<<player+1<<" - Chance 3: ";
                tchance = p[player].get_score(10,1);
            }
            else if(fchance == 10){
                cout<<"Enter Score for Player"<<player+1<<" - Chance 3: ";
                tchance = p[player].get_score(10-schance, 1);
            }
            remaining2 = (((10-tchance)+9)%10)+1; 
            if(schance == remaining && remaining != 10){
                cout<<"Enter Score for Player"<<player+1<<" - Chance 4: ";
                lchance = p[player].get_score(remaining2,1);
            }
            else if(schance == remaining && remaining == 10 && fchance == 0){
                 cout<<"Enter Score for Player"<<player+1<<" - Chance 4: ";
                lchance = p[player].get_score(remaining2,1);

            }
        }
        else{
            cout<<"Enter Score for Player"<<player+1<<" - Chance 1: ";
            fchance = p[player].get_score(10,1);
            if(fchance == 10){
                p[player].end_score();
                scorecard(p,n);
                continue;
            }
            cout<<"Enter Score for Player"<<player+1<<" - Chance 2: ";
            schance = p[player].get_score(10-fchance, 2);
        }
        p[player].end_score();
        
        scorecard(p,n);

        if(p[player].print_score() > max_score){
            max_score = p[player].print_score();
            max_player = player;
        }

    }
}



void print_result(Player p[]){
    cout<<endl<<endl;
    cout<<"WINNER: "<<endl;
    cout<<"P"<<max_player+1<<" - "<<max_score<<" points"<<endl;
}



int main(){
    //Number of players
    int n;
    int rounds;

    cout<<"Number of players: ";
    cin>>n;

    cout<<"Number of rounds: ";
    cin>>rounds;

    //Create an array of n players;
    Player p[n];

    for(int round = 0; round < rounds; round++){
        cout<<"Round "<<round+1<<":"<<endl;
        // Will make function for this separately
        gameplay(p, n, rounds, round); 
    }

    print_result(p);
    return 0;
}
