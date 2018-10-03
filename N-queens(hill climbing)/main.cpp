#include <iostream>
#include<ctime>
#define queens 8
#define max_iterations 10
using namespace std;

class Board{
private:
    int board[queens][queens];
    int queens_position[queens];
public:
    void print_board();
    void initialize_board(int iter);
    int solve();
    int huristic();
    void replace_queen(int i,int j);
};
void Board::initialize_board(int iter){
    iter++;
    iter*=100;
    srand(time(0));
    for(int i=0;i<queens;i++){
        for(int j=0;j<queens;j++){
            board[i][j]=0;
        }
    }
    for(int i=0;i<queens;i++){
        int temp=rand()%iter;
        queens_position[i]= temp % 8;
        board[queens_position[i]][i]=1;
    }
}

int Board::huristic(){
    int ret=0;
    for(int i=0;i<queens;i++){
        int count=0;
        for(int j=0;j<queens;j++){
            if(board[i][j]==1){
                count++;
            }
        }
        if(count>1){
            ret+=((count-1)*(count))/2;
        }
    }
    int temp=queens*2 -2;
    for(int k=1;k<temp-1;k++){
        int count=0;
        for(int i=0;i<queens;i++){
            for(int j=0;j<queens;j++){
                if(i+j==k && board[i][j]==1){
                    count++;
                }
            }
        }
        if(count>1){
            ret+=(count*(count-1))/2;
        }
    }
    int high=queens-1;
    int low=-high;
    for(int k=high-1;k>low;k--){
        int count=0;
        for(int i=0;i<queens;i++){
            for(int j=0;j<queens;j++){
                if(i-j==k && board[i][j]==1){
                    count++;
                }
            }
        }
        if(count>1){
            ret+=(count*(count-1))/2;
        }
    }


    return ret;
}

void Board::replace_queen(int i, int j){
    for(int k=0;k<queens;k++){
        board[k][j]=0;
    }
    board[i][j]=1;
    queens_position[j]=i;
}

int Board::solve(){
    int iter=max_iterations;
    while(iter--){
        initialize_board(iter);
        int min=huristic();
        cout<<"ITERATION : "<<max_iterations-iter<<endl;
        cout<<"initially huristic value : "<<min<<endl;
        print_board();
        for(int j=0;j<queens;j++){
            cout<<"Iterating column : "<<j<<endl;
            for(int i=0;i<queens;i++){
                int previous_position=queens_position[j];
                replace_queen(i,j);
                int temp=huristic();
                if(temp<min){
                    cout<<"better position found with huristic value : "<<temp<<endl;
                    print_board();
                    min=temp;
                    if(min==0){
                        return 0;
                    }
                }
                else{
                    cout<<"No improvemet huristic value :"<<temp<<endl;
                    //print_board();
                    replace_queen(previous_position,j);
                }
            }
        }
    }
    return -1;
}

void Board::print_board(){
    for(int i=0;i<queens;i++){
        for(int j=0;j<queens;j++){
            cout<<board[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main() {
    Board obj;
    if(obj.solve()==0){
        cout<<"Solved successfully.."<<endl;
    }
    else{
        cout<<"Encountered local maxima "<<max_iterations<<" times"<<endl;
    }
    return 0;
}
