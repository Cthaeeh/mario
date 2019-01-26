#ifndef COUCHMODEL_H
#define COUCHMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <QString>


class CouchModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CouchModel(QObject *parent);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex & index, const QVariant & value, int role);

    Qt::ItemFlags flags(const QModelIndex & index) const override;


    bool isFull();

    void addPlayer (const QString name);

    void clear ();

    std::vector<std::pair<QString ,int>> updates();

private:

    std::vector<std::pair<QString ,int>> playerUpdates_;

};

#endif // COUCHMODEL_H
