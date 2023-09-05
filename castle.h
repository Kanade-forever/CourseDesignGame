#ifndef CASTLE_H
#define CASTLE_H
#include<QString>

class Castle
{
public:
    Castle();
    Castle(QString name,int _treasure);
    QString castle_name;
    int treasure;

    void set_treasure(int _treasure);
    int get_treasure();
    QString get_name();
};

#endif // CASTLE_H
