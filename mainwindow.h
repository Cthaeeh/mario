#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include "mymodel.h"
#include "couchwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:


    QPushButton *addPlayerBut_;
    QPushButton *submitBut_;
    QTableView  *table_;
    QLabel *roundLabel_;
    MyModel *myModel_;

    std::vector<CouchWidget *> couches_;

private slots:

    void addPlayer();
    void submit();
};

#endif // MAINWINDOW_H
