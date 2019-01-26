#include "couchmodel.h"
#include <iostream>

CouchModel::CouchModel(QObject *parent, int capacity)
    :QAbstractTableModel(parent),
     capacity_(capacity)
{

}


int CouchModel::rowCount(const QModelIndex &parent) const
{
    return capacity_;
}

int CouchModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant CouchModel::data (const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return index.row() < results_.size() ? results_.at(index.row()).name : QString();
        case 1:
            return index.row() < results_.size() ? results_.at(index.row()).placeRound1 : -1;
        case 2:
            return index.row() < results_.size() ? results_.at(index.row()).placeRound2 : -1;
        case 3:
            return index.row() < results_.size() ? results_.at(index.row()).placeRound3 : -1;
        case 4:
            return index.row() < results_.size() ? results_.at(index.row()).placeRound4 : -1;
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
                    return QString("map 1:");
                case 2:
                    return QString("map 2:");
                case 3:
                    return QString("map 3:");
                case 4:
                    return QString("map 4:");
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
        if (i.column() >= 1 && i.column() <= 4 && i.row() < results_.size()) {
            std::cout << "try" << std::endl;
            try {
                int place = value.toInt();
                if (place < 0 || place > 4)
                    return false;
                switch (i.column()) {
                case 1:
                 results_.at(i.row()).placeRound1 = place;
                    break;
                case 2:
                 results_.at(i.row()).placeRound2 = place;
                 break;
                case 3:
                 results_.at(i.row()).placeRound3 = place;
                 break;
                case 4:
                 results_.at(i.row()).placeRound4 = place;
                 break;
                }


                auto topLeft = index(0,0);
                auto bottomRight = index(results_.size(),5);

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
    if (index.column() >= 1 || index.column() <=4)
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    else
        return QAbstractTableModel::flags(index);;
}

void CouchModel::addPlayer (const QString name)
{
    if (!isFull())
        results_.push_back({name,0,0,0,0});
    emit layoutChanged();
}

void CouchModel::clear ()
{
    results_.clear();
}

bool CouchModel::isFull() {
    return results_.size() >= capacity_;
}

std::vector<Result> CouchModel::results()
{
    return results_;
}
