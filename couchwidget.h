#ifndef COUCHWIDGET_H
#define COUCHWIDGET_H

#include <QTableView>
#include "couchmodel.h"

class CouchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CouchWidget(QWidget *parent = 0);


    CouchModel* model();
private:

    QTableView *table_;
    CouchModel *couchModel_;



signals:

public slots:
};

#endif // COUCHWIDGET_H
