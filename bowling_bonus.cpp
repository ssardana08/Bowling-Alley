#include<iostream>
#include<vector>

using namespace std;


class Player{
    int score;
    string scorecard;
    vector<int> track;

    public:
    Player(){
        score = 0;
        scorecard = "";
    }
    int get_score(int);
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

int Player::get_score(int max){
    int temp;
    cin >> temp;
    if(temp > max){
        cout<<"OOps wrong score.. Score out of Bounds, considering this score to be 0"<<endl;
        temp = 0;
    }
    if(temp == 10){
        score+=10;
        scorecard+="X,";
        track.push_back(10);
    }
    else if(temp == max){
        score+=(max);
        scorecard+="/,";
        track.push_back(-1);
    }
    else{
        score+=temp;
        scorecard+='0'+temp;
        scorecard+=',';
        track.push_back(temp);
    }
    if(track.size() > 1 && track[track.size()-2] == -1){
       score+=temp;
    }
    if(track.size() > 1 && track[track.size()-2] == 10){
        score+=temp;
        //score+=track[track.size()-2];
    }
    if(track.size() > 2 && track[track.size()-3] == 10){
        score+=temp;
        //score+=track[track.size()-2];
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
            fchance = p[player].get_score(10);
            
            remaining = (((10-fchance)+9)%10)+1;
            
            cout<<"Enter Score for Player"<<player+1<<" - Chance 2: ";
            schance = p[player].get_score(remaining);

            if(schance == remaining){
                cout<<"Enter Score for Player"<<player+1<<" - Chance 3: ";
                tchance = p[player].get_score(10);
            }
            else if(fchance == 10){
                cout<<"Enter Score for Player"<<player+1<<" - Chance 3: ";
                tchance = p[player].get_score(10-schance);
            }
            remaining2 = (((10-tchance)+9)%10)+1; 
            if(schance == remaining && remaining != 10){
                cout<<"Enter Score for Player"<<player+1<<" - Chance 4: ";
                lchance = p[player].get_score(remaining2);
            }
        }
        else{
            cout<<"Enter Score for Player"<<player+1<<" - Chance 1: ";
            fchance = p[player].get_score(10);
            if(fchance == 10){
                p[player].end_score();
                scorecard(p,n);
                continue;
            }
            cout<<"Enter Score for Player"<<player+1<<" - Chance 2: ";
            schance = p[player].get_score(10-fchance);
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
