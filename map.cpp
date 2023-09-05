#include "map.h"

map::map()
{
    castle_number = 0;
    road_number = 0;
}

void map::Creat_Map(QFile* file){
    QString data = file->readLine();
    QStringList data_list = data.split(" ");
    castle_number = data_list[0].toInt();
    road_number = data_list[1].toInt();
    //读取城堡数据
    for(int i=0;i<castle_number;i++){
        QString data = file->readLine();
        QStringList data_list = data.split(" ");
        Castle c(data_list[0],data_list[1].toInt());
        castle.push_back(c);
    }
    //读取道路数据
    for(int i=0;i<road_number;i++){
        QString data = file->readLine();
        QStringList data_list = data.split(" ");
        Road r(data_list[0].toInt(),data_list[1].toInt(),data_list[2].toInt());
        road.push_back(r);
    }
    //读取完数据关闭文件下一步对数据加工
    file->close();
    //将道路信息存储到邻接矩阵
    arc_road = new int*[castle_number];
    arc      = new int*[castle_number];
    for(int i=0;i<castle_number;i++){
        arc_road[i] = new int[castle_number];
        arc[i] = new int[castle_number];
        for(int j=0;j<castle_number;j++){
            arc_road[i][j] = int(INFINITY);
            arc[i][j] = int(INFINITY);
        }
    }
    for(int i=0;i<road_number;i++){
        arc_road[road[i].start][road[i].end] = road[i].danger;
        arc_road[road[i].end][road[i].start] = road[i].danger;
        arc[road[i].start][road[i].end] = road[i].danger;
    }
    //城堡是否访问数组
    visited = new bool[castle_number];
}

void map::More_Treasure(){
    this->treasure_path.clear();
    int *temp_path = new int[this->castle_number+1];temp_path[castle_number] = castle_number;
    int *path      = new int[this->castle_number];
    int max_treasure = 0;
    int length = 0;
    dfs(max_treasure,0,0,length,temp_path,path);
    for(int i=0;i<length-1;i++){
        this->treasure_path.push_back(path[i]);
    }
}

void map::dfs(int&max_treasure, int castle, int temp_length, int&length, int *temp_path, int *path){
    if(castle == 14){
        int health = 100,treasure = 0;
        for(int i=1;i<temp_length;i++){
            health-=arc_road[temp_path[i]][temp_path[i-1]];
        }
        if(health>0){
            for(int i=0;i<temp_length-1;i++){
                treasure+=this->castle[temp_path[i]].get_treasure();
            }
            if(treasure>max_treasure){
                max_treasure = treasure;
                length = temp_length;
                for(int i=0;i<length-1;i++){
                    path[i] = temp_path[i];
                }
            }
        }
    }
    else{
        for(int i=0;i<this->castle_number;i++){
            if(arc[castle][i] != int(INFINITY)){
                temp_path[temp_length] = i;
                dfs(max_treasure,i,temp_length+1,length,temp_path,path);
            }
        }
    }
}

void map::More_Life(){
    this->life_path.clear();
    //使用Dijkstra算法计算"最短路径"(即危险值最小的的路径)
    int minval;
    int v,u;
    bool* tag = new bool[castle_number];
    for(int i=0;i<castle_number;i++){
        tag[0] = false;
    }
    int *path = new int[castle_number];
    int *dist = new int[castle_number];

    for(v=0;v<castle_number;v++){
        dist[v] = arc_road[0][v];
        if(dist[v] == int(INFINITY)){
            path[v] = -1;
        }
        else {
            path[v] = 0;
        }
    }
    tag[0] = true;
    for(int i=1;i<castle_number;i++){
        minval = int(INFINITY);
        u = 0;
        for(v=0;v<castle_number;v++){
            if(!tag[v] && dist[v]<minval){
                u = v;
                minval = dist[v];
            }
        }
        tag[u] = true;
        for(int j =0;j<this->Get_Castle(u).length();j++){
            v = this->Get_Castle(u)[j];
            if(!tag[v] && minval+arc_road[u][v]<dist[v]){
                dist[v] = minval+arc_road[u][v];
                path[v] = u;
            }
        }
    }
    for(int i=path[castle_number-1];i!=-1;i=path[i]){
        this->life_path.push_back(i);
    }
}

QList<int> map::Get_Castle(int n){
    QList<int> l;
    for(int i=0;i<road_number;i++){
        if(road[i].start == n) l.push_back(road[i].end);
        if(road[i].end == n) l.push_back(road[i].start);
    }
    return l;
}

//获取与n相邻道路的危险
QList<int> map::Get_Danger(int n){
    QList<int> l;
    for(int i=0;i<castle_number;i++){
        if(arc_road[n][i]!=int(INFINITY)){
            l.push_back(arc_road[n][i]);
        }
    }
    return l;
}

