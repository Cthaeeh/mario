#include "mymodel.h"
#include <iostream>
#include <algorithm>

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}


int MyModel::rowCount(const QModelIndex &parent) const
{
    return players_.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant MyModel::data (const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        std::cout << "Dispay role" << std::endl;
        switch(index.column()) {
        case 0:
            return players_.at(index.row()).name;
        case 1:
            return players_.at(index.row()).goldMedals;
        case 2:
            return players_.at(index.row()).silverMedals;
        case 3:
            return players_.at(index.row()).bronzeMedals;
        case 4:
            return players_.at(index.row()).score();
        default:
            return QVariant();
        }
    }
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("gold");
                case 2:
                    return QString("silber");
                case 3:
                    return QString("bronze");
                case 4:
                    return QString("score");
                }
            }
        }
        return QVariant();
}

void MyModel::addPlayer (const QString &name)
{

    players_.push_back(Player(name));

    auto topLeft = index(0,0);
    auto bottomRight = index(players_.size(),5);

    emit dataChanged(topLeft,bottomRight);
    emit layoutChanged();
}

bool MyModel::playerExists (const QString &name)
{
    for (auto &player : players_) {
        if (player.name == name)
            return true;
    }
    return false;
}

void MyModel::addMedal (const QString &name, Medal medal)
{
    for (auto &player : players_) {
        if (player.name == name) {
            switch(medal){
            case Gold:
                player.goldMedals++;
                break;
            case Silver:
                player.silverMedals++;
                break;
            case Bronze:
                player.bronzeMedals++;
                break;
            }
        }
    }
    emit layoutChanged();
}

bool is_better(const Player& a, const Player& b)
{
    return a.score() > b.score();
}

std::vector<QString> MyModel::getPlayersSorted()
{
     std::sort(players_.begin(), players_.end(), is_better);

     std::vector<QString> names;
     for (auto player : players_){
         names.push_back(player.name);
     }

     return names;
}
