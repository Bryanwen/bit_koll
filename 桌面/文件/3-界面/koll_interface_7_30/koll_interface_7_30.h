#ifndef koll_interface_7_30_H
#define koll_interface_7_30_H
#include "Fsensor.h"
#include "koll_tcp.h"

#include <QMainWindow>
#include <QTimer>
#include <qdatetime.h>
#include <QDialog>
#include <QString>
#include <QDebug>//调试
#include <QMessageBox> //消息对话框
#include <QWidget>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <stdio.h>
#include<iostream>
#include<cstring>
using namespace std;
extern char SendMessage[1024];
extern char ReciveMessage[1024];

namespace Ui {
class koll_interface_7_30;
}

class koll_interface_7_30 : public QMainWindow
{
    Q_OBJECT

public:
    explicit koll_interface_7_30(QWidget *parent = 0);
    ~koll_interface_7_30();
    RESPONSE resp;
    QString motor_state;
    QString titlebutton_state;
    QString titlebutton_state_old;
    QTimer *timer_force;
    float Fsensor[6];



private slots:


    void timerUpdate();

    void Force_show();

    void timerUpdate_title();

    void on_pushButton_init_clicked();

    void on_pushButton_home_clicked();

    void on_pushButton_diagnosis_clicked();

    void on_pushButton_prepare_clicked();

    void on_pushButton_operation_clicked();

    void on_pushButton_analysis_clicked();

    void on_pushButton_monitor_clicked();

    void monitor_lamp(QString mlampcolor);

    void build_communication(QString build);

    void return_title_button(QString old);

    
    void on_motorcontrol4_14_clicked();

    void on_motorcontrol4_13_clicked();

    void on_groupBox_17_clicked();

    void on_motorcontrol4_28_clicked();

    void on_motorcontrol4_26_clicked();


    void on_motorcontrol4_6_clicked();

    void on_pushButton_analysis_1_28_clicked();

    void on_pushButton_analysis_1_25_clicked();

    void on_pushButton_analysis_1_18_clicked();


    void on_motorcontrol4_6_clicked(bool checked);

private:
    Ui::koll_interface_7_30 *ui;

};

#endif // koll_interface_7_30_H
