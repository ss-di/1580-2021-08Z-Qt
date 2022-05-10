#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t1 = new QTimer();
    connect(t1, SIGNAL(timeout()), this, SLOT(Alarm1()));
    t1 -> start(10);

    t2 = new QTimer();
    connect(t2, SIGNAL(timeout()), this, SLOT(Alarm2()));
    t2 -> start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    t1 -> stop();
}

void MainWindow::Alarm1()
{
    cnt += 1;
    QString s;
    s.setNum(cnt);
    ui -> lblCount -> setText(s);
    if (napr == 1){
        x += 1;
        if (x > 700)
            napr = 2;
    } else {
        x -= 1;
        if (x < 100)
            napr = 1;
    }
    repaint();
}

void MainWindow::Alarm2()
{
    x2 = 200 + r*cos(fi);
    y2 = 200 - r*sin(fi);
    fi += 1 * M_PI / 180;
    repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if (e->buttons() & Qt::LeftButton) {
        ui -> lblX -> setText(QString::number(e->pos().x()));
        ui -> lblY -> setText(QString::number(e->pos().y()));
        x = e->pos().x();
        y = e->pos().y();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    if (e->buttons() & Qt::LeftButton) {
        x = e->pos().x();
        y = e->pos().y();
    }
}


void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter p(this);
    p.drawLine(10, 20, 1000, 40);
    p.drawPoint(20, 30);
    p.setBrush(QBrush(Qt::red, Qt::CrossPattern));
    p.drawRect(20, 40, 50, 100);
    p.setPen(Qt::red);
    p.drawEllipse(x2, y2, 50, 100);
    p.drawArc(140, 40, 100, 100, 30*16, 150*16);
    p.setBrush(Qt::green);
    p.drawPie(x, y, 100, 100, 30*16, 150*16);
    //p.setPen(Qt::DashDotDotLine);
    p.setPen(QPen(QBrush(Qt::blue, Qt::Dense3Pattern),
                  5.5));
    p.drawChord(10, 150, 100, 100, 30*16, 100*16);
    p.drawText(105, 90, "Hello");
    p.eraseRect(10, 10, 50, 50);
}
