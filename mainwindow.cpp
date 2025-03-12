#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    city c;
    c.name = "lol";
    c.x = 100;
    c.y = 100;
    c.people = 10;
    cities.push_back(c);
    c.name = "popopopopopop";
    c.x = 300;
    c.y = 100;
    c.people = 1000;
    cities.push_back(c);
    c.name = "sdlkjf";
    c.x = 60;
    c.y = 60;
    c.people = 60;
    cities.push_back(c);
    road r;
    r.c1 = 0;
    r.c2 = 1;
    r.cost = 0;
    r.selected = false;
    roads.push_back(r);

    r.c1 = 1;
    r.c2 = 2;
    r.cost = 0;
    r.selected = false;
    roads.push_back(r);

    r.c1 = 0;
    r.c2 = 2;
    r.cost = 0;
    r.selected = true;
    roads.push_back(r);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p;
    p.begin(this);
    int x = ui->label->x(), y = ui->label->y()+ui->label->height();
    int w = ui->label->width(),h = ui->label->height();
    p.translate(x,y);
    p.scale(1,-1);

    p.save();
    p.setBrush(Qt::white);
    p.setPen(Qt::white);
    p.drawRect(0,0,w, h);
    p.restore();
    p.save();
    p.translate(30,15);
    p.save();
   // w -= 30; h -= 15;
    QColor color(Qt::gray);
    color.setAlpha(30);
    p.setPen(color);
    int currectw = w/8.6;
    int currecth = h/8.6;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8 ; y++){
            p.drawRect(x*currectw,y * currecth,currectw,currecth);
        }
    }
    p.restore();
    drawROAD(p);
    paintcity(p);
    p.restore();

    p.end();
}

void MainWindow::paintcity(QPainter &p)
{
    for(auto i : cities){
        if(i.people > 100){
            drawBIG(p,i);
        }
        else if(i.people < 50){
            drawSMALL(p,i);
        }
        else {
            drawMIDDLE(p,i);
        }
    }
}

void MainWindow::drawBIG(QPainter &p,city c)
{
    p.save();
    p.setBrush(Qt::blue);
    p.drawEllipse(c.x-15,c.y-15,30,30);
    p.restore();
    p.save();
    int delta = c.name.size();
    delta/=2;
    p.translate(c.x-delta * 7, c.y + 18);
    p.scale(1,-1);
    p.drawText(0,0, c.name);
    p.restore();
}

void MainWindow::drawSMALL(QPainter &p, city c)
{
    p.save();
    p.setBrush(Qt::green);
    p.drawEllipse(c.x-5,c.y-5,10,10);
    p.restore();
    p.save();
    int delta = c.name.size();
    delta/=2;
    p.translate(c.x-delta * 7, c.y + 12);
    p.scale(1,-1);
    p.drawText(0,0, c.name);
    p.restore();
}

void MainWindow::drawMIDDLE(QPainter &p, city c)
{
    p.save();
    p.setBrush(Qt::red);
    p.drawEllipse(c.x-10,c.y-10,20,20);
    p.restore();
    p.save();
    int delta = c.name.size();
    delta/=2;
    p.translate(c.x-delta * 7, c.y + 15);
    p.scale(1,-1);
    p.drawText(0,0, c.name);
    p.restore();
}

void MainWindow::drawROAD(QPainter &p)
{
    for(auto i : roads){
        p.save();
        QPen pen;
        pen.setWidth(2);
        if(i.selected){
            pen.setColor(Qt::red);

        }
        p.setPen(pen);
        p.drawLine(cities[i.c1].x,cities[i.c1].y, cities[i.c2].x,cities[i.c2].y);
        p.restore();
    }
}

void MainWindow::findWAY(int c1, int c2)
{
    QQueue<int> q;
    visited.clear();
    QVector<int> rrr(cities.size(), -1);
    cost.clear();
    cost = QVector<int>(cities.size(), 1000000);
    cost[c1] = 0;
    q.push_front(c1);
    while(!q.empty()){
        int i = q.back();
        q.pop_back();
        for(auto j : roads){
            if(j.c1 == i){
                if(cost[j.c2] > cost[i] + j.cost){
                    cost[j.c2] = cost[i] + j.cost;
                    visited[j.c2] = i;
                    if(rrr[j.c2] == -1 && j.c2 != c2){
                    q.push_front(j.c2);
                    rrr[j.c2] = 1;
                    }
                }
            }
        }
    }
    for(int i = c2; i != c1;){
        for(auto j : roads){
            if(j.c2 == i && j.c1 == visited[i]){
                j.selected = true;
                i = visited[i];
            }
        }
    }
}
