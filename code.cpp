#include <iostream>
#include <vector>
#include <string.h>
#include <chrono> //计算运行时间需要的。
using namespace std;
using namespace chrono;

//0代表此位置存在x，-1代表不存在

int create_table_time(long long n, int x, int y){
    int *dp = new int[n+1];
    dp[1] = x;
    for(int i = 2; i <= n; i++){
        if(i & 1){ //i%2!=0
            dp[i] = min(dp[i-1] + x, dp[(i-1)/2] + x + y);
        }
        else{
            dp[i] = min(dp[i-1] + x, dp[i/2] + y);
        }
    }
    return dp[n];
}

string process(int n){
    string result;
    while (n != 0 && n >= 4){
        if(n & 1){
            n = n - 1;
            result = "I" + result;
        }
        else{
            n = n/2;
            result = "C"+ result;
        }
    }
    if(n == 4) result = "IIC"+ result;
    else if(n == 3) result = "III"+ result;
    else if(n == 2) result = "II" + result;
    else if(n == 1) result = "I" + result;
    return result;
}
int count(int list[], int num, int n){//
    int co = 0;
    for(int i = 0; i < n; i++){
        if(list[i] == num){
            co++;
        }
    }
    return co;
}

pair<int,int> find_chess(int list[], int pos, int n){ //找当前棋子右端最近的棋子位置
    int left = -2; int right = -2;
    for(int i = pos+1; i < n; i++){
        if(list[i] == 0){ //当前棋子右端最近的棋子位置
            right = i;
            break;
        }
    }
    for(int i = pos-1; i >= 0; i--){
        if(list[i] == 0){ //当前棋子左端最近的棋子位置
            left = i;
            break;
        }
    }
    return make_pair(left, right);
}

void print_board(int list[], int n){
    for(int i = 1; i < n+1; i++){
        if(list[i] == -1){
            cout << ".";
        } else { cout << "x";}
    }
    cout << endl;
}

void command_process(vector<int> comm, vector<string> comm_2, int p, int n){ //comm保存棋子的位置，comm_2保存L或R指令
    int list[n]; memset(list, 0, sizeof(list)); //棋盘，先把所有位置设为0即没有棋子。

    for(int i = 0; i < p; i++){ //处理一个一个指令
        int pos = comm[i]; //指令中的棋子的位置
        string com = comm_2[i]; //指令中的L/R
        pair<int,int> left_right_ches;
        if(list[pos] == -1 || (comm[i] == 1 && comm_2[i] == "L") || 
          (comm[i] == n && comm_2[i] == "R") || pos < 0 || pos > n){ //不合格指令
            cout << "Illegal Operatio" << endl; 
            continue;
        }
        else if(com == "L"){ //指令是L时
            list[pos] = -1;
            list[pos - 1] = 0;
            left_right_ches = find_chess(list, pos-1, n);
        }
        else if(com == "R"){ //指令是R时
            list[pos] = -1;
            list[pos + 1] = 0;
            left_right_ches = find_chess(list, pos+1, n);
        }

        int num_ches = count(list, 0, n);
        cout << num_ches << " " << left_right_ches.first << " " << left_right_ches.second << endl;
    }
    print_board(list, n);
}  

int main(){
    //初始化 - 输入
    long long n; int x; int y; cin >> n >> x >> y; 
    int p; cin >> p;
    vector<int> command; vector<string> command_2; //第二问的中的指令，command保存棋子的位置，command_2保存L或R指令
    for(int i = 0; i < p; i++){
        int z; string zz;
        cin >> z >> zz;
        command.push_back(z);
        command_2.push_back(zz);
    }

    auto start = system_clock::now();//开始计算代码运行时间

    cout << create_table_time(n,x,y) << endl; 
    string res = process(n);
    cout << res << endl;
    command_process(command, command_2, p, n);   


    auto end = system_clock::now(); //代买运行结束，输出运行时间
    auto duration = duration_cast<microseconds>(end - start);
    cout <<  "Spent " 
        << double(duration.count()) * microseconds::period::num / microseconds::period::den 
        << " seconds" << endl; 
    return 0;
}