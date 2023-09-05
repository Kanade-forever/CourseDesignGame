#ifndef MAP_H
#define MAP_H

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QColorDialog>
#include <QString>
#include <QDebug>
#include <QList>
#include"road.h"
#include"castle.h"
#include"traveler.h"

#endif // MAP_H
class map{
    public:
        map();
        int castle_number;
        int road_number;
        int** arc_road;//无向图邻接矩阵
        int** arc;
        bool* visited;//各个城堡是否被访问过
        QList<Castle> castle;
        QList<Road>   road;
        QList<int> life_path;//最多生命的路径
        QList<int> treasure_path;//最多财宝的路径
        Traveler traveler;

        void Creat_Map(QFile *file);
        void More_Treasure();
        void More_Life();
        void dfs(int&max_treasure,int castle,int temp_length,int&length,int*temp_path,int*path);
        QList<int> Get_Castle(int n);
        QList<int> Get_Danger(int n);

};
