#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //读取文件构建地图
    QFile file(QFileDialog::getOpenFileName(this,"选择打开的地图文件","* txt"));
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"waring","地图构建失败");
    }
    m.Creat_Map(&file);

    begin = false;

    ui->setupUi(this);//打开ui
    //将城堡存储在列表中方便操作
    castle.push_back(ui->castle_0);
    castle.push_back(ui->castle_1);
    castle.push_back(ui->castle_2);
    castle.push_back(ui->castle_3);
    castle.push_back(ui->castle_4);
    castle.push_back(ui->castle_5);
    castle.push_back(ui->castle_6);
    castle.push_back(ui->castle_7);
    castle.push_back(ui->castle_8);
    castle.push_back(ui->castle_9);
    castle.push_back(ui->castle_10);
    castle.push_back(ui->castle_11);
    castle.push_back(ui->castle_12);
    castle.push_back(ui->castle_13);
    castle.push_back(ui->castle_14);

//    emit(castle[0]->clicked());发射一个点击castle[0]的信号

    ui->health_bar->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start(){
    //开始游戏时的初始化
    begin = true;//开始游戏

    ui->next_castle->clear();
    last_castle_closed.clear();
    this->Clear_Castle_Color();
    this->Set_Closed_Castle_Color({1,2});
    this->m.traveler.health = 100;
    this->m.traveler.treasure = 0;
    this->path.clear();
    //设置所有城堡未访问
    for(int i=0;i<this->m.castle_number;i++){
        this->m.visited[i] = false;
    }
    //设置起点为A
    last_castle_closed.push_back(1);
    last_castle_closed.push_back(2);
    m.traveler.current_castle = 0;
    ui->castle_0->setStyleSheet("QPushButton{background-color:rgba(240,120,100,1)}");
    ui->castle_1->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");
    ui->castle_2->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");
    this->path.push_back(0);
    ui->next_castle->append("B 财宝:200 危险:15");
    ui->next_castle->append("C 财宝:100 危险:10");
    //设置traveler初始状态
    ui->health_bar->setVisible(true);
    this->Set_Traveler(100,0);
}

//自由游戏选项
void MainWindow::on_actionFreePlay_triggered()
{
    this->start();
}

//最多宝藏选项
void MainWindow::on_actionMoreTreasure_triggered()
{
    this->start();
    this->m.More_Treasure();
    QThread::sleep(1);
    for(int i=0;i<this->m.treasure_path.length();i++){
        emit(castle[m.treasure_path[i]]->clicked());
        QThread::sleep(1);
    }
    emit(castle[14]->clicked());
}

//最多生命选项
void MainWindow::on_actionMoreLife_triggered()
{
    this->start();
    this->m.More_Life();
    QThread::sleep(1);
    for(int i=this->m.life_path.length()-2;i>=0;i--){
        emit(castle[m.life_path[i]]->clicked());
        QThread::sleep(1);
    }
    emit(castle[14]->clicked());
}

//设置相邻城堡颜色函数
void MainWindow::Set_Closed_Castle_Color(QList<int> l){
    for(int i=0;i<l.length();i++){
        switch (l[i]) {
            case 0: ui->castle_0->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 1: ui->castle_1->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 2: ui->castle_2->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 3: ui->castle_3->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 4: ui->castle_4->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 5: ui->castle_5->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 6: ui->castle_6->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 7: ui->castle_7->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 8: ui->castle_8->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 9: ui->castle_9->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 10: ui->castle_10->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 11: ui->castle_11->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 12: ui->castle_12->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 13: ui->castle_13->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
            case 14: ui->castle_14->setStyleSheet("QPushButton{background-color:rgba(50,120,200,1)}");break;
        }
    }
}

//清空城堡颜色
void MainWindow::Clear_Castle_Color(){
    ui->castle_0->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_1->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_2->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_3->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_4->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_5->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_6->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_7->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_8->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_9->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_10->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_11->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_12->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_13->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
    ui->castle_14->setStyleSheet("QPushButton{background-color:rgba(225,225,225,1)}");
}

void MainWindow::Click_Castle(int n){
    if(!begin){
        QMessageBox::warning(this,"无法点击","游戏尚未开始!");
        return;
    }
    if(this->m.traveler.current_castle == n){
        QMessageBox::warning(this,"无法通行!","勇者已经在这座城堡");
        return;
    }
    //判断是否可以由上一个城堡到达所点击的城堡
    bool If_Reach = false;
    for(int i=0;i<last_castle_closed.length();i++){
        if(last_castle_closed[i] == n){
            If_Reach = true;break;
        }
    }
    if(!If_Reach){
        QMessageBox::warning(this,"无法通行!","没有道路无法到达!");
        return;
    }
    //若可以到达
    last_castle_closed.clear();//重新记录该城堡的相邻城堡
    ui->next_castle->clear();
    QString message;
    QList<int> l = m.Get_Castle(n);//相邻的城堡
    QList<int> danger = m.Get_Danger(n);//相邻道路的危险
    for(int i=0;i<l.length();i++){
        //保存相邻城堡信息
        message.append(m.castle[l[i]].castle_name+" 财宝:"+QString::number(this->m.visited[l[i]]?0:m.castle[l[i]].treasure)+" 风险:"+QString::number(danger[i])+'\n');
        last_castle_closed.push_back(l[i]);
    }
    this->Clear_Castle_Color();
    this->Set_Closed_Castle_Color(l);
    ui->next_castle->setText(message);//显示相邻城堡信息
    this->castle[n]->setStyleSheet("QPushButton{background-color:rgba(240,120,100,1)}");
    this->path.push_back(n);
    this->m.traveler.current_castle = n;

    //进行traveler状态的运算
    int last = path[path.length()-2];
    this->m.traveler.health-=this->m.arc_road[last][n];
    if(this->m.traveler.health<=0||n == 14){
        if(n == 14&&this->m.traveler.health>0)this->m.traveler.treasure+=this->m.castle[n].get_treasure();
        Game_Over();
    }
    if(!this->m.visited[n]&&n!=14&&this->m.traveler.health>0){
        this->m.traveler.treasure+=this->m.castle[n].get_treasure();
    }
    this->Set_Traveler(this->m.traveler.health,this->m.traveler.treasure);
    this->m.visited[n] = true;//结束判定后设置该城堡已访问
}

//显示勇者数据
void MainWindow::Set_Traveler(int health, int treasure){
    ui->traveler_status->clear();
    ui->traveler_status->setText("当前生命:""\n""\n""当前财宝:");
    ui->health_bar->setValue(health);
    ui->traveler_status->append(QString::number(treasure));
}

void MainWindow::Game_Over(){
    begin = false;
    QMessageBox message(this);
    message.setMinimumSize(150,75);
    QString path;
    for(int i=0;i<this->path.length()-1;i++){
        path.append(this->m.castle[this->path[i]].get_name()+"->");
    }
    path.append(this->m.castle[14].get_name());
    if(this->m.traveler.health<=0){
        this->Set_Traveler(0,this->m.traveler.treasure);
        message.setWindowTitle("游戏失败!");
        message.setText("勇者已死亡，请点击开始处选择游戏模式重新开始!""\n""最终获取的财宝数为:"+QString::number(this->m.traveler.treasure)+"\n"+path);
        message.exec();
    }
    else {
        message.setWindowTitle("成功到达终点!");
        message.setText("勇者已成功到达终点,请点击开始处选择游戏模式重新开始!""\n""最终获取财宝数为:"+QString::number(this->m.traveler.treasure)
                        +"\n""剩余生命值为:"+QString::number(this->m.traveler.health)+"\n"+path);

        message.exec();
    }
}

//城堡点击槽函数
void MainWindow::on_castle_0_clicked(){
    Click_Castle(0);
}

void MainWindow::on_castle_1_clicked(){
    Click_Castle(1);
}

void MainWindow::on_castle_2_clicked(){
    Click_Castle(2);
}

void MainWindow::on_castle_3_clicked(){
    Click_Castle(3);
}

void MainWindow::on_castle_4_clicked(){
    Click_Castle(4);
}

void MainWindow::on_castle_5_clicked(){
    Click_Castle(5);
}

void MainWindow::on_castle_6_clicked(){
    Click_Castle(6);
}

void MainWindow::on_castle_7_clicked(){
    Click_Castle(7);
}

void MainWindow::on_castle_8_clicked(){
    Click_Castle(8);
}

void MainWindow::on_castle_9_clicked(){
    Click_Castle(9);
}

void MainWindow::on_castle_10_clicked(){
    Click_Castle(10);
}

void MainWindow::on_castle_11_clicked(){
    Click_Castle(11);
}

void MainWindow::on_castle_12_clicked(){
    Click_Castle(12);
}

void MainWindow::on_castle_13_clicked(){
    Click_Castle(13);
}

void MainWindow::on_castle_14_clicked(){
    Click_Castle(14);
}
