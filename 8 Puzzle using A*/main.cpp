#include <iostream>
using namespace std;

class Puzzle{
private:
    char initial_grid[3][3];
    char goal_grid[3][3];
    char curr_grid[3][3];
    int no_of_steps;
    char moves[100];
public:
    Puzzle();
    int huristic_manhattan(char current_grid[3][3]);
    char select_next_node();
    void get();
    void solve();
    void print_result();
    void print_grid(char g[3][3]);
    void print_steps();
    void swap(char& c1,char&c2);

};
Puzzle::Puzzle(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            initial_grid[i][j]='-';
            goal_grid[i][j]='-';
        }
    }
    no_of_steps=0;
}

int Puzzle::huristic_manhattan(char current_grid[3][3]){
    int ret=0;
    char temp;
    int k=0,l=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp=current_grid[i][j];
            int flag=0;
            for(k=0;k<3 && flag==0;k++){
                for(l=0;l<3 && flag==0;l++){
                  if(goal_grid[k][l]==current_grid[i][j]){
                      flag=1;
                  }
                }
            }
            k--;
            l--;
            ret+=abs(i-k);
            ret+=abs(j-l);
        }
    }
    return ret;
}

void Puzzle::swap(char& c1,char&c2){
    char temp=c1;
    c1=c2;
    c2=temp;
}

char Puzzle::select_next_node(){
    char temp_grid[3][3];
    int h_value[4]={-1,-1,-1,-1};
    int pos_x=-1,pos_y=-1;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                temp_grid[i][j]=curr_grid[i][j];
        }
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(curr_grid[i][j]=='x'){
                pos_x=i;
                pos_y=j;
                break;
            }
        }
    }
    char temp;
    if(pos_y!=0){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y-1]);
        h_value[0]=huristic_manhattan(temp_grid);
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y-1]);
    }
    if(pos_y!=2){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y+1]);
        h_value[1]=huristic_manhattan(temp_grid);
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y+1]);
    }
    if(pos_x!=0){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x-1][pos_y]);
        h_value[2]=huristic_manhattan(temp_grid);
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x-1][pos_y]);
    }
    if(pos_x!=2){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x+1][pos_y]);
        h_value[3]=huristic_manhattan(temp_grid);
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x+1][pos_y]);
    }
    int min=100;
    int index=-1;
    for(int i=0;i<4;i++){
        if(h_value[i]>-1 && h_value[i]<min){
            min=h_value[i];
            index=i;
        }
    }

    if(index==0){
        swap(curr_grid[pos_x][pos_y],curr_grid[pos_x][pos_y-1]);
        return 'L';
    }
    else if(index==1){
        swap(curr_grid[pos_x][pos_y],curr_grid[pos_x][pos_y+1]);
        return 'R';
    }
    else if(index==2){
        swap(curr_grid[pos_x][pos_y],curr_grid[pos_x-1][pos_y]);
        return 'U';
    }
    else if(index==3){
        swap(curr_grid[pos_x][pos_y],curr_grid[pos_x+1][pos_y]);
        return 'D';
    }

    return '-';
}


void Puzzle::get(){
    char temp;
    cout<<"Enter initial state of grid"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>temp;
            initial_grid[i][j]=temp;
            curr_grid[i][j]=temp;
        }
    }
    cout<<"Enter goal state of grid"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>temp;
            goal_grid[i][j]=temp;
        }
    }
}

void Puzzle::solve(){
    int hur=-1;

    while(hur!=0){
        moves[no_of_steps++]=select_next_node();
        cout<<moves[no_of_steps-1]<<"\t";
        hur=huristic_manhattan(curr_grid);
    }
}

void Puzzle::print_result(){
    char ch;
    cout<<"Initial state"<<endl;
    print_grid(initial_grid);
    cout<<"Moves taken"<<endl;
    for(int i=0;i<no_of_steps;i++){
        cout<<moves[i]<<"\t";
    }
    cout<<endl;
    cout<<"final state"<<endl;
    print_grid(goal_grid);
    cout<<"Print steps(Y/N)?"<<endl;
    cin>>ch;
    if(ch=='y' || ch=='Y'){
        print_steps();
    }
}

void Puzzle::print_grid(char g[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<g[i][j]<<"\t";
        }
        cout<<endl;
    }
}

void Puzzle::print_steps(){
    char temp[3][3];
    int x=-1,y=-1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp[i][j]=initial_grid[i][j];
            if(initial_grid[i][j]=='x'){
                x=i;
                y=j;
            }
        }
    }
    for(int i=0;i<no_of_steps;i++){
        switch(moves[i]){
            case 'L':
                cout<<"\nL"<<endl;
                swap(temp[x][y],temp[x][--y]);
                print_grid(temp);
                break;
            case 'R':
                cout<<"\nR"<<endl;
                swap(temp[x][y],temp[x][++y]);
                print_grid(temp);
                break;
            case 'U':
                cout<<"\nU"<<endl;
                swap(temp[x][y],temp[--x][y]);
                print_grid(temp);
                break;
            case 'D':
                cout<<"\nD"<<endl;
                swap(temp[x][y],temp[++x][y]);
                print_grid(temp);
                break;
        }
    }
}

int main() {
    Puzzle obj;
    obj.get();
    obj.solve();
    obj.print_result();
    return 0;
}