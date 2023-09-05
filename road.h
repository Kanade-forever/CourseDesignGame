#ifndef ROAD_H
#define ROAD_H


class Road
{
public:
    Road();
    Road(int begin,int end,int danger);
    int start;
    int end;
    int danger;
};

#endif // ROAD_H
