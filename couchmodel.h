#ifndef COUCHMODEL_H
#define COUCHMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <QString>

struct Result
{
    QString name;
    int placeRound1;
    int placeRound2;
    int placeRound3;
    int placeRound4;

    std::vector<int> asVec()
    {
        return {placeRound1,placeRound2,placeRound3,placeRound4};
    }
};


class CouchModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CouchModel(QObject *parent, int capacity);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex & index, const QVariant & value, int role);

    Qt::ItemFlags flags(const QModelIndex & index) const override;

    bool isFull();

    void addPlayer (const QString name);

    void clear ();

    std::vector<Result> results();

private:

    std::vector<Result> results_;
    int capacity_;

};

#endif // COUCHMODEL_H
