#include <iostream>
using namespace std;

class node{
public:
    char grid[3][3];
    int path_cost;
    int total_cost;
    int visited;
    char moves[100];
    node* next;
    node(){
        path_cost=-1;
        total_cost=-1;
        next=NULL;
        visited=0;
    }
};

class Puzzle{
private:
    node* top;
    char initial_grid[3][3];
    char goal_grid[3][3];
public:
    Puzzle();
    int huristic_manhattan(char current_grid[3][3]);
    void add_neighbours(node* temp);
    void get();
    void solve();
    void print_result(node* res);
    void print_grid(char g[3][3]);
    void print_steps(node* res);
    void swap(char& c1,char&c2);
    int not_on_que(char temp[3][3]);
    void add_to_que(char grid[3][3],node* pre,char move);
    node* select_best_node();

};
Puzzle::Puzzle(){
    top=NULL;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            initial_grid[i][j]='-';
            goal_grid[i][j]='-';
        }
    }
}

int Puzzle::not_on_que(char temp[3][3]){
    node* curr=top;
    while(curr!=NULL){
        int flag=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(temp[i][j]!=curr->grid[i][j]){
                    flag=1;
                }
            }
        }
        if(flag!=1){
            return 0;
        }
        curr=curr->next;
    }
    return 1;
}

void Puzzle::add_to_que(char grid[3][3], node *pre, char move) {
    node* curr=new node();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            curr->grid[i][j]=grid[i][j];
        }
    }
    curr->next=top;
    top=curr;
    strcpy(curr->moves,pre->moves);
    curr->path_cost=pre->path_cost+1;
    curr->moves[curr->path_cost-1]=move;
    curr->total_cost=curr->path_cost + huristic_manhattan(curr->grid);
}

node* Puzzle::select_best_node(){
    node* curr=top;
    int min=100000;
    node* ret=NULL;
    while(curr!=NULL){
        if(curr->visited!=1 && curr->total_cost<min){
            min=curr->total_cost;
            ret=curr;
        }
        curr=curr->next;
    }
    if(ret!=NULL){
        ret->visited=1;
    }
    return ret;
}


int Puzzle::huristic_manhattan(char current_grid[3][3]){
    int ret=0;
    char temp;
    int k=0,l=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp=current_grid[i][j];
            if(temp=='x'){
                continue;
            }
            int flag=0;
            for(k=0;k<3 && flag==0;k++){
                for(l=0;l<3 && flag==0;l++){
                  if(goal_grid[k][l]==temp){
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

void Puzzle::add_neighbours(node* temp){
    char temp_grid[3][3];
    int pos_x=-1,pos_y=-1;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                temp_grid[i][j]=temp->grid[i][j];
        }
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(temp->grid[i][j]=='x'){
                pos_x=i;
                pos_y=j;
                break;
            }
        }
    }
    if(pos_y!=0){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y-1]);
        if(not_on_que(temp_grid)){
            add_to_que(temp_grid,temp,'L');
        }
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y-1]);
    }
    if(pos_y!=2){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y+1]);
        if(not_on_que(temp_grid)){
            add_to_que(temp_grid,temp,'R');
        }
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x][pos_y+1]);
    }
    if(pos_x!=0){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x-1][pos_y]);
        if(not_on_que(temp_grid)){
            add_to_que(temp_grid,temp,'U');
        }
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x-1][pos_y]);
    }
    if(pos_x!=2){
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x+1][pos_y]);
        if(not_on_que(temp_grid)){
            add_to_que(temp_grid,temp,'D');
        }
        swap(temp_grid[pos_x][pos_y],temp_grid[pos_x+1][pos_y]);
    }

}


void Puzzle::get(){
    char temp;
    node* new_node=new node();
    top=new_node;
    cout<<"Enter initial state of grid"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>temp;
            initial_grid[i][j]=temp;
            new_node->grid[i][j]=temp;
        }
    }
    cout<<"Enter goal state of grid"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>temp;
            goal_grid[i][j]=temp;
        }
    }
    new_node->path_cost=0;
    new_node->total_cost=huristic_manhattan(new_node->grid);
}

void Puzzle::solve(){

    while(1){
        node* temp=select_best_node();
        if(temp==NULL){
            cout<<"No solution to the problem"<<endl;
            break;
        }
        if(huristic_manhattan(temp->grid)==0){
            print_result(temp);
        }
        else{
            add_neighbours(temp);
        }

    }
}

void Puzzle::print_result(node* res){
    char ch;
    cout<<"Initial state"<<endl;
    print_grid(initial_grid);
    cout<<"Moves taken"<<endl;
    for(int i=0;i< res->path_cost;i++){
        cout<<res->moves[i]<<"\t";
    }
    cout<<endl;
    cout<<"final state"<<endl;
    print_grid(goal_grid);
    cout<<"Print steps(Y/N)?"<<endl;
    cin>>ch;
    if(ch=='y' || ch=='Y'){
        print_steps(res);
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

void Puzzle::print_steps(node* res){
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
    for(int i=0;i<res->path_cost;i++){
        switch(res->moves[i]){
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
    return 0;
}