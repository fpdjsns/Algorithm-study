#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int T, V, E;
vector<vector<pair<int,double>>> adj;    //  <정점, 가중치>

double dijkstra() {
    vector<double> dist(V+1, 0.0);
    dist[0]=1.0;

    priority_queue<pair<double, int>> PQ;  //  <가중치, 정점>
    PQ.push(make_pair(-1.0, 0));

    while(!PQ.empty()){
        double cost = -PQ.top().first;
        int here = PQ.top().second;
        PQ.pop();

        //  만약 지금 꺼낸 것보다 기존의 경로가 더 짧다면 지금 꺼낸 것을 무시한다.
        if(dist[here] < cost) continue;
        //  인접한 정점을 모두 조사한다.
        for(int i=0;i<adj[here].size();i++){
            int there = adj[here][i].first;
            double thereDist = cost * adj[here][i].second;
            //  더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
            if(dist[there] == 0.0 || dist[there] > thereDist){
                dist[there] = thereDist;
                PQ.push(make_pair(-dist[there], there));
            }
        }
    }
    return dist[V-1];
}

int main(int argc, const char * argv[]) {
    cin >> T;
    while(T--){
        cin>>V>>E;
        adj.clear();
        adj.resize(V+1);
        for(int i=0;i<E;i++){
            int a,b;
            double c;
            cin >> a >> b >> c;
            adj[a].push_back(make_pair(b,c));
            adj[b].push_back(make_pair(a,c));
        }
        printf("%.10f\n",dijkstra());
    }
    return 0;
}