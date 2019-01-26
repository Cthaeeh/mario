#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <vector>

struct Player
{
    QString name;
    int goldMedals;
    int silverMedals;
    int bronzeMedals;

    int score() const
    {
        return 3*goldMedals + 2 * silverMedals + 1* bronzeMedals;
    }

    Player(QString name)
        :name(name),
        goldMedals(0),
        silverMedals(0),
        bronzeMedals(0)
    {

    }
};

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum Medal {
        Gold,
        Silver,
        Bronze
    };

    MyModel(QObject *parent);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addPlayer (const QString &name);

    void addMedal (const QString &name, Medal medal);

    std::vector<QString> getPlayersSorted();

private:
    std::vector<Player> players_;

};


#endif // MYMODEL_H
