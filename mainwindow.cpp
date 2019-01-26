#include "mainwindow.h"
#include <QGridLayout>
#include <QWidget>
#include <QInputDialog>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      addPlayerBut_(new QPushButton("Add Player",this)),
      submitBut_(new QPushButton("Submit",this)),
      roundLabel_(new QLabel("Round 1",this)),
      table_(new QTableView(this)),
      myModel_(new MyModel(this)),
      couches_({new CouchWidget(this),
                new CouchWidget(this),
                new CouchWidget(this),
                new CouchWidget(this)})

{
    auto layout = new QGridLayout();
    layout->addWidget(addPlayerBut_,0,0,1,1);
    layout->addWidget(roundLabel_,0,1,1,1);
    layout->addWidget(submitBut_,0,2,1,1);

    auto yPos = 1;
    for (auto couch : couches_) {
        layout->addWidget(couch,yPos++,0,1,3);
    }

    layout->addWidget(new QLabel("Tabelle:",this),0,4,1,1);
    layout->addWidget(table_,1,4,4,1);
    table_->setMinimumWidth(500);
    table_->setMinimumHeight(600);

    layout->setSpacing(10);

    table_->setModel(myModel_);

    auto widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(addPlayerBut_,&QPushButton::clicked,
            this,&MainWindow::addPlayer);

    connect(submitBut_,&QPushButton::clicked,
            this,&MainWindow::submit);
}



MainWindow::~MainWindow()
{

}


void MainWindow::addPlayer()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Player","Insert Player name",QLineEdit::Normal,"asdf",&ok);
    if (ok && !name.isEmpty()) {
        // TODO ensure player does not already exist ..
        if (myModel_->playerExists(name)) {
            QMessageBox msgBox;
            msgBox.setText("Player exists already");
            msgBox.exec();
        } else {
            myModel_->addPlayer(name);
            for (auto couch : couches_) {
                if (!couch->model()->isFull()) {
                    couch->model()->addPlayer(name);
                    return;
                }
            }
            QMessageBox msgBox;
            msgBox.setText("Couches are full, ask programmer to implement more couches.");
            msgBox.exec();
        }

    }
}


void MainWindow::submit()
{

    // Update the standings
    for (auto couch : couches_) {
        for (auto playerUpdate : couch->model()->updates()) {
            switch(playerUpdate.second) {
            case 1:
                myModel_->addMedal(playerUpdate.first,MyModel::Gold);
                break;
            case 2:
                myModel_->addMedal(playerUpdate.first,MyModel::Silver);
                break;
            case 3:
                myModel_->addMedal(playerUpdate.first,MyModel::Bronze);
                break;
            default:
                break;
            }
        }
    }

    // Clear the couches
    for (auto couch : couches_) {
        couch->model()->clear();
    }

    // Sort players back on couches.
    for (auto playerName : myModel_->getPlayersSorted()){
        for (auto couch : couches_) {
            if (!couch->model()->isFull()) {
                couch->model()->addPlayer(playerName);
                break;
            }
        }
    }
}
