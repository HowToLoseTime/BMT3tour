#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPaintEvent>
#include<QVector>
#include<QString>
#include<QQueue>
struct city{
    int x, y, people;
    QString name;
};
struct road{
    int c1,c2;
    int cost;
    bool selected;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
private:

    QVector<city> cities;
    QVector<road> roads;
    QVector<int> visited;
    QVector<int> cost;
    Ui::MainWindow *ui;
    void paintcity(QPainter &p);
    void drawBIG(QPainter &p, city c);
    void drawSMALL(QPainter &p,city c);
    void drawMIDDLE(QPainter &p,city c);
    void drawROAD(QPainter &p);
    void findWAY(int c1, int c2);
};
#endif // MAINWINDOW_H
