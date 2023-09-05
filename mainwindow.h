#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include <QPushButton>
#include <QThread>
#include"map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionFreePlay_triggered();

    void on_actionMoreTreasure_triggered();

    void on_actionMoreLife_triggered();

    void on_castle_0_clicked();

    void on_castle_1_clicked();

    void on_castle_2_clicked();

    void on_castle_3_clicked();

    void on_castle_4_clicked();

    void on_castle_5_clicked();

    void on_castle_6_clicked();

    void on_castle_7_clicked();

    void on_castle_8_clicked();

    void on_castle_9_clicked();

    void on_castle_10_clicked();

    void on_castle_11_clicked();

    void on_castle_12_clicked();

    void on_castle_13_clicked();

    void on_castle_14_clicked();

protected:
    void start();
    void Set_Closed_Castle_Color(QList<int> l);//设置点击城堡相邻城堡颜色
    void Clear_Castle_Color();//清空城堡颜色
    void Click_Castle(int n);
    void Game_Over();
    void Set_Traveler(int health,int treasure);

    Ui::MainWindow *ui;
    QList<int> last_castle_closed;
    QList<QPushButton*> castle;
    map m;
    QList<int> path;//勇者前进路线

    bool begin;
};

#endif // MAINWINDOW_H
