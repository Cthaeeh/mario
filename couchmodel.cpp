#include "couchmodel.h"
#include <iostream>

CouchModel::CouchModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}


int CouchModel::rowCount(const QModelIndex &parent) const
{
    return 4;
}

int CouchModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant CouchModel::data (const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return index.row() < playerUpdates_.size() ? playerUpdates_.at(index.row()).first : QString();
        case 1:
            return index.row() < playerUpdates_.size() ? playerUpdates_.at(index.row()).second : -1;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant CouchModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("place:");
                }
            }
            if (orientation == Qt::Vertical) {
                switch (section)
                {
                case 0:
                    return QString("Player 1");
                case 1:
                    return QString("Player 2");
                case 2:
                    return QString("Player 3");
                case 3:
                    return QString("Player 4");
                }
            }
        }
        return QVariant();
}

bool CouchModel::setData(const QModelIndex & i, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        if (i.column() == 1 && i.row() < playerUpdates_.size()) {
            std::cout << "try" << std::endl;
            try {
                int place = value.toInt();
                if (place < 0 || place > 4)
                    return false;
                playerUpdates_.at(i.row()).second = place;

                auto topLeft = index(0,0);
                auto bottomRight = index(playerUpdates_.size(),2);

                emit dataChanged(topLeft, bottomRight);
                return true;
            } catch(...) {
                return false;
            }
        }
    }
    return false;
}

Qt::ItemFlags CouchModel::flags(const QModelIndex & index) const
{
    if (index.column() == 1)
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    else
        return QAbstractTableModel::flags(index);;
}

void CouchModel::addPlayer (const QString name)
{
    if (!isFull())
        playerUpdates_.push_back({name,0});
    emit layoutChanged();
}

void CouchModel::clear ()
{
    playerUpdates_.clear();
}

bool CouchModel::isFull() {
    return playerUpdates_.size() >= 4;
}

std::vector<std::pair<QString ,int>> CouchModel::updates()
{
    return playerUpdates_;
}
