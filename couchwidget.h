#ifndef COUCHWIDGET_H
#define COUCHWIDGET_H

#include <QTableView>
#include "couchmodel.h"

class CouchWidget : public QWidget
{
    Q_OBJECT
public:
    CouchWidget(QWidget *parent = 0, int capacity = 4);


    CouchModel* model();
private:

    QTableView *table_;
    CouchModel *couchModel_;



signals:

public slots:
};

#endif // COUCHWIDGET_H
