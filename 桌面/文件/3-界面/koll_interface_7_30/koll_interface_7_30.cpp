#include "koll_interface_7_30.h"
#include "ui_koll_interface_7_30.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>

char ReciveMessage[1024];
char SendMessage[1024];

koll_interface_7_30::koll_interface_7_30(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::koll_interface_7_30)
{    ui->setupUi(this);

    /*时间设置*/
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    /*电机状态设置*/
    motor_state="disconnect";
    /*状态设置*/
    build_communication(motor_state);
    /*标题按钮设置*/
    titlebutton_state="home";
    titlebutton_state_old="0";
    /*初始化到首页*/
    ui->middle_interface->setCurrentIndex(1);
    /*标题栏按键刷新*//*时间设置*/
    QTimer *timer_title = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate_title()));
    timer->start(10);


    ui->pushButton_home->setStyleSheet("QPushButton        {border-image: url(:/image/2-1.1-首页.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-1.2-首页.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-1.3-首页.png);}");
    ui->pushButton_init->setStyleSheet ("QPushButton       {border-image: url(:/image/2-2.1-初始.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-2.2-初始.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-2.3-初始.png);}");
    ui->pushButton_diagnosis->setStyleSheet("QPushButton   {border-image: url(:/image/2-3.1-诊断.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-3.2-诊断.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-3.3-诊断.png);}");
    ui->pushButton_prepare->setStyleSheet("QPushButton     {border-image: url(:/image/2-4.1-准备.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-4.2-准备.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-4.3-准备.png);}");
    ui->pushButton_operation->setStyleSheet("QPushButton   {border-image: url(:/image/2-5.1-手术.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-5.2-手术.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-5.3-手术.png);}");
    ui->pushButton_analysis->setStyleSheet("QPushButton    {border-image: url(:/image/2-6.1-分析.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-6.2-分析.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-6.3-分析.png);}");
    ui->pushButton_monitor->setStyleSheet("QPushButton     {border-image: url(:/image/2-7.1-监控.png)}"
                                       "QPushButton:hover  {border-image: url(:/image/2-7.2-监控.png);}"
                                       "QPushButton:pressed{border-image: url(:/image/2-7.3-监控.png);}");
    monitor_lamp("red");

    /*监控界面按键初始化*/
//    ui->pushButton_monitor_start->setStyleSheet("QPushButton{font:15pt ;border-radius:5px;color:white;background-color: rgb(68, 144, 217);border:2px solid #3878b4;}""QPushButton:hover{background-color: rgb(56, 120, 180);border:2px solid #000000;}""QPushButton:pressed{font:16pt;}" "QPushButton:disabled{background-color: rgb(148, 148, 148);color:black;border:none;}");
//    ui->pushButton_monitor_end->setStyleSheet("QPushButton{font:15pt ;border-radius:5px;color:white;background-color: rgb(68, 144, 217);border:2px solid #3878b4;}""QPushButton:hover{background-color: rgb(56, 120, 180);border:2px solid #000000;}""QPushButton:pressed{font:16pt;}" "QPushButton:disabled{background-color: rgb(148, 148, 148);color:black;border:none;}");
//    ui->pushButton_monitor_return0->setStyleSheet("QPushButton{font:15pt ;border-radius:5px;color:white;background-color: rgb(68, 144, 217);border:2px solid #3878b4;}""QPushButton:hover{background-color: rgb(56, 120, 180);border:2px solid #000000;}""QPushButton:pressed{font:16pt;}" "QPushButton:disabled{background-color: rgb(148, 148, 148);color:black;border:none;}");
//    ui->pushButton_monitor_start_pos->setStyleSheet("QPushButton{font:15pt ;border-radius:5px;color:white;background-color: rgb(68, 144, 217);border:2px solid #3878b4;}""QPushButton:hover{background-color: rgb(56, 120, 180);border:2px solid #000000;}""QPushButton:pressed{font:16pt;}" "QPushButton:disabled{background-color: rgb(148, 148, 148);color:black;border:none;}");
//    ui->pushButton_t->setStyleSheet("QPushButton{font:15pt ;border-radius:5px;color:white;background-color: rgb(68, 144, 217);border:2px solid #3878b4;}""QPushButton:hover{background-color: rgb(56, 120, 180);border:2px solid #000000;}""QPushButton:pressed{font:16pt;}" "QPushButton:disabled{background-color: rgb(148, 148, 148);color:black;border:none;}");
//    //ui->pushButton_monitor_upload->setStyleSheet("QPushButton{font:15pt ;border-radius:5px;color:white;background-color: rgb(68, 144, 217);border:2px solid #3878b4;}""QPushButton:hover{background-color: rgb(56, 120, 180);border:2px solid #000000;}""QPushButton:pressed{font:16pt;}" "QPushButton:disabled{background-color: rgb(148, 148, 148);color:black;border:none;}");

    /*Force Sensor Init*/
    timer_force = new QTimer(this);
    connect(timer_force,SIGNAL(timeout()),this,SLOT(Force_show()));

    memset(SendMessage,'\0',sizeof(1024*sizeof(char)));

}

koll_interface_7_30::~koll_interface_7_30()
{
    delete ui;
}
//同时完成时间更新与标题栏状态更新
void koll_interface_7_30::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_time->setText(str);
    //标题栏状态更新
}


void koll_interface_7_30::timerUpdate_title()
{
    if(titlebutton_state=="home" &&  titlebutton_state_old!="home")
    {
        ui->pushButton_home->setStyleSheet("QPushButton        {border-image: url(:/image/2-1.2-首页.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-1.2-首页.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-1.3-首页.png);}");
        return_title_button(titlebutton_state_old);
        titlebutton_state_old="home";
    }
    if(titlebutton_state=="init" &&  titlebutton_state_old!="init")
    {
        ui->pushButton_init->setStyleSheet("QPushButton        {border-image: url(:/image/2-2.2-初始.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-2.2-初始.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-2.3-初始.png);}");
         return_title_button(titlebutton_state_old);
        titlebutton_state_old="init";
    }
    if(titlebutton_state=="diagnosis" &&  titlebutton_state_old!="diagnosis")
    {
        ui->pushButton_diagnosis->setStyleSheet("QPushButton        {border-image: url(:/image/2-3.2-诊断.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-3.2-诊断.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-3.3-诊断.png);}");
         return_title_button(titlebutton_state_old);
        titlebutton_state_old="diagnosis";
    }
    if(titlebutton_state=="prepare" &&  titlebutton_state_old!="prepare")
    {
        ui->pushButton_prepare->setStyleSheet("QPushButton        {border-image: url(:/image/2-4.2-准备.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-4.2-准备.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-4.3-准备.png);}");
         return_title_button(titlebutton_state_old);
        titlebutton_state_old="prepare";
    }
    if(titlebutton_state=="operation" &&  titlebutton_state_old!="operation")
    {
        ui->pushButton_operation->setStyleSheet("QPushButton        {border-image: url(:/image/2-5.2-手术.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-5.2-手术.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-5.3-手术.png);}");
         return_title_button(titlebutton_state_old);
        titlebutton_state_old="operation";
    }
    if(titlebutton_state=="analysis" &&  titlebutton_state_old!="analysis")
    {
        ui->pushButton_analysis->setStyleSheet("QPushButton        {border-image: url(:/image/2-6.2-分析.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-6.2-分析.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-6.3-分析.png);}");
         return_title_button(titlebutton_state_old);
        titlebutton_state_old="analysis";
    }
    if(titlebutton_state=="monitor" &&  titlebutton_state_old!="monitor")
    {
        ui->pushButton_monitor->setStyleSheet("QPushButton        {border-image: url(:/image/2-7.2-监控.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-7.2-监控.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-7.3-监控.png);}");
         return_title_button(titlebutton_state_old);
        titlebutton_state_old="monitor";
    }

}

void koll_interface_7_30::return_title_button(QString old)
{
    if(old=="home")
    {
        ui->pushButton_home->setStyleSheet("QPushButton        {border-image: url(:/image/2-1.1-首页.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-1.2-首页.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-1.3-首页.png);}");
    }
    if(old=="init")
    {
        ui->pushButton_init->setStyleSheet("QPushButton        {border-image: url(:/image/2-2.1-初始.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-2.2-初始.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-2.3-初始.png);}");
    }
    if(old=="diagnosis")
    {
        ui->pushButton_diagnosis->setStyleSheet("QPushButton        {border-image: url(:/image/2-3.1-诊断.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-3.2-诊断.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-3.3-诊断.png);}");
    }
    if(old=="prepare")
    {
        ui->pushButton_prepare->setStyleSheet("QPushButton        {border-image: url(:/image/2-4.1-准备.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-4.2-准备.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-4.3-准备.png);}");
    }
    if(old=="operation")
    {
        ui->pushButton_operation->setStyleSheet("QPushButton        {border-image: url(:/image/2-5.1-手术.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-5.2-手术.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-5.3-手术.png);}");
    }
    if(old=="analysis")
    {
        ui->pushButton_analysis->setStyleSheet("QPushButton        {border-image: url(:/image/2-6.1-分析.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-6.2-分析.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-6.3-分析.png);}");
    }
    if(old=="monitor")
    {
        ui->pushButton_monitor->setStyleSheet("QPushButton        {border-image: url(:/image/2-7.1-监控.png)}"
                                           "QPushButton:hover  {border-image: url(:/image/2-7.2-监控.png);}"
                                           "QPushButton:pressed{border-image: url(:/image/2-7.3-监控.png);}");
    }
}

void koll_interface_7_30::on_pushButton_init_clicked()
{

     ui->middle_interface->setCurrentIndex(1);
     titlebutton_state="init";

}

void koll_interface_7_30::on_pushButton_home_clicked()
{
     ui->middle_interface->setCurrentIndex(0);
     titlebutton_state="home";
}

void koll_interface_7_30::on_pushButton_diagnosis_clicked()
{
     ui->middle_interface->setCurrentIndex(2);
     titlebutton_state="diagnosis";
}

void koll_interface_7_30::on_pushButton_prepare_clicked()
{
     ui->middle_interface->setCurrentIndex(3);
     titlebutton_state="prepare";
}

void koll_interface_7_30::on_pushButton_operation_clicked()
{
     ui->middle_interface->setCurrentIndex(4);
     titlebutton_state="operation";
}

void koll_interface_7_30::on_pushButton_analysis_clicked()
{
     ui->middle_interface->setCurrentIndex(5);
     titlebutton_state="analysis";
}

void koll_interface_7_30::on_pushButton_monitor_clicked()
{
     ui->middle_interface->setCurrentIndex(6);
     titlebutton_state="monitor";
}

void koll_interface_7_30::monitor_lamp(QString mlampcolor)
{
    if (mlampcolor=="green")
    {
        ui->frame_motor1_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_motor2_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_motor3_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_motor4_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_motor5_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_motor6_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_force1_lamp ->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
        ui->frame_force2_lamp ->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
    }
    if (mlampcolor=="yellow")
    {
        ui->frame_motor1_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_motor2_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_motor3_lamp->setStyleSheet("QFrameQFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_motor4_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_motor5_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_motor6_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_force1_lamp ->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
        ui->frame_force2_lamp ->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
    }
    if (mlampcolor=="red")
    {
        ui->frame_motor1_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_motor3_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_motor4_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_motor5_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_motor2_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_motor6_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_force1_lamp ->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
        ui->frame_force2_lamp ->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
    }

}



void koll_interface_7_30::build_communication(QString build)
{
    if(build=="connect")
    {
        ui->label_state->setText("已经连接");
        ui->frame_state_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.1-绿灯.png)}");
    }
    if(build=="disconnect")
    {
        ui->label_state->setText("尚未连接");
        ui->frame_state_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.3-红灯.png)}");
    }
    if(build=="fault")
    {
        ui->label_state->setText("出现故障");
        ui->frame_state_lamp->setStyleSheet("QFrame{border-image: url(:/image/3-1.2-黄灯.png)}");
    }
}



void koll_interface_7_30::on_motorcontrol4_14_clicked()
{
   timer_force->start(100);
}

void koll_interface_7_30::on_motorcontrol4_13_clicked()
{
    timer_force->stop();
    ui->lineEdit_Fx->setText("");ui->progressBar_Fx->setValue(0);
    ui->lineEdit_Fy->setText("");ui->progressBar_Fy->setValue(0);
    ui->lineEdit_Fz->setText("");ui->progressBar_Fz->setValue(0);
    ui->lineEdit_Tx->setText("");ui->progressBar_Tx->setValue(0);
    ui->lineEdit_Ty->setText("");ui->progressBar_Ty->setValue(0);
    ui->lineEdit_Tz->setText("");ui->progressBar_Tz->setValue(0);
    ui->lineEdit_FSstate->setText("");
}
void koll_interface_7_30::Force_show()
{
    int FSinit=Fsensor_init ();
    if(FSinit==0)
        ui->lineEdit_FSstate->setText("Connecting");
    else if(FSinit==-1)
        ui->lineEdit_FSstate->setText("Socket Error");
    else if(FSinit==-2)
        ui->lineEdit_FSstate->setText("Connect Error");
    else
        ui->lineEdit_FSstate->setText("?Error");
    float *F;
    F=Fdata_get();
    QString str1 = QString::number(F[0],'f',4);ui->lineEdit_Fx->setText(str1);ui->progressBar_Fx->setValue(fabs(F[0]));
    QString str2 = QString::number(F[1],'f',4);ui->lineEdit_Fy->setText(str2);ui->progressBar_Fy->setValue(fabs(F[1]));
    QString str3 = QString::number(F[2],'f',4);ui->lineEdit_Fz->setText(str3);ui->progressBar_Fz->setValue(fabs(F[2]));
    QString str4 = QString::number(F[3],'f',4);ui->lineEdit_Tx->setText(str4);ui->progressBar_Tx->setValue(fabs(F[3]));
    QString str5 = QString::number(F[4],'f',4);ui->lineEdit_Ty->setText(str5);ui->progressBar_Ty->setValue(fabs(F[4]));
    QString str6 = QString::number(F[5],'f',4);ui->lineEdit_Tz->setText(str6);ui->progressBar_Tz->setValue(fabs(F[5]));
    Fsensor_colse();

}

void koll_interface_7_30::on_groupBox_17_clicked()
{

}

void koll_interface_7_30::on_motorcontrol4_28_clicked()
{
    int FSinit=Fsensor_ping();
    if(FSinit==0)
        ui->sensor_status->setText("Ping[192.168.1.120] OK");
    else if(FSinit==-1)
        ui->sensor_status->setText("Socket Error");
    else if(FSinit==-2)
        ui->manipulator_status->setText("Connect Error");
    else
        ui->sensor_status->setText("?Error");
}

void koll_interface_7_30::on_motorcontrol4_26_clicked()
{
    int KollSinit=kolltcp_ping();
    if(KollSinit==0)
        ui->manipulator_status->setText("Ping[192.168.1.100] OK");
    else if(KollSinit==-1)
        ui->manipulator_status->setText("Socket Error");
    else if(KollSinit==-2)
        ui->manipulator_status->setText("Connect Error");
    else
        ui->manipulator_status->setText("?Error");
}



void koll_interface_7_30::on_motorcontrol4_6_clicked()
{
    system("gnome-terminal");
     // system("gnome-terminal -x bash -c ' '&");

}

void koll_interface_7_30::on_pushButton_analysis_1_28_clicked()
{
    ui->TCP_tset_recv->setText("Ping OK Wating Client...");
    int KollSinit=kolltcp_init();
    if(KollSinit==0)
    {
        build_communication("connect");
        ui->TCP_tset_recv->setText("Connect to Koll");
    }
    else if(KollSinit==-1)
        ui->TCP_tset_recv->setText("Socket Error");
    else if(KollSinit==-2)
        ui->TCP_tset_recv->setText("Connect Error");
    else
        ui->TCP_tset_recv->setText("?Error");
}

void koll_interface_7_30::on_pushButton_analysis_1_25_clicked()
{
    kolltcp_close();
    ui->TCP_tset_recv->setText("Stop TCP with Koll");
}

void koll_interface_7_30::on_pushButton_analysis_1_18_clicked()
{
    QString send = ui->TCP_tset_send->text();
    pthread_mutex_lock(&mut);
    strcpy(SendMessage ,send.toLocal8Bit().data());
    pthread_mutex_unlock(&mut);
    QTime t;
    t.start();
    while(t.elapsed()<2);

    pthread_mutex_lock(&mut_rec);
    QString qStr=QString::fromStdString(ReciveMessage);
    ui->TCP_tset_recv_2->setText(qStr);
    pthread_mutex_unlock(&mut_rec);

//    system("gnome-terminal -x bash -c 'ssh root@192.168.1.100 ./kollmorgen'&");

}




void koll_interface_7_30::on_motorcontrol4_6_clicked(bool checked)
{
     system("gnome-terminal");

}
