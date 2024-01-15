#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, l, r;
    cin >> n >> l >> r;
    int dx[4] = {0,0,-1,1};
    int dy[4] = {-1,1,0,0};
    int ans = 0;
    int is_move,count,x,y,tox,toy,summation[2500],number[2500];
    vector <vector <int>> guild(n,vector<int>(n,-1)); // 각 국가별연합 정보
    vector<vector <int>> map(n,vector<int>(n,0));
    queue <pair<int,int>> q;
    
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin >> map[i][j];
        }
    }
    
    while(true){
        for (int i =0;i<n;i++){
            for (int j=0;j<n;j++){
                guild[i][j] = -1;
            }
        }
        for (int i =0;i<2500;i++){
            summation[i] = 0;
            number[i] = 0;
        }
        count = 0; // 국가 연합 개수 정보
        is_move = 0; // 하루동안 인구 이동이 일어난 여부
        
        for (int i=0; i<n;i++){
            for (int j=0; j<n;j++){
                q.push(make_pair(i,j));
                while(!q.empty()){
                    y = q.front().first;
                    x = q.front().second;
                    q.pop();
                    if (guild[y][x]==-1){
                        
                        guild[y][x] = count;
                        summation[count]+= map[y][x];
                        number[count]++;
                        
                        for (int k=0;k<4;k++){
                            tox = x+dx[k];
                            toy = y+dy[k];
                            
                            if (tox >=0 && tox <n && toy >=0 && toy < n){
                                if (abs(map[y][x]-map[toy][tox]) >= l && abs(map[y][x]-map[toy][tox])<=r){
                                    is_move = 1;
                                    q.push(make_pair(toy,tox));
                                }
                            }
                        }
                    }

                }
                count++;

            }
            
        }
        
        // 인구 이동
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if (guild[i][j]!=-1){
                    map[i][j] = int(summation[guild[i][j]] / number[guild[i][j]]);
                }
            }
        }
        
        if (is_move==0) break; // 인구 이동이 일어나지 않았다면 종료
        else ans++; // 인구 이동이 일어났다면 하루 추가
    }
    
    cout << ans << '\n';;
    
    // for (int i=0;i<n;i++){
    //     for (int j=0;j<n;j++){
    //         cout << map[i][j] << '\t';
    //     }
    //     cout << '\n';
    // }
    return 0;
}
