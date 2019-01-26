#include "couchwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QLabel>

CouchWidget::CouchWidget(QWidget *parent, int capacity)
    : QWidget(parent),
      table_(new QTableView(this)),
      couchModel_(new CouchModel(this, capacity))
{
    auto layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Couch"));
    layout->addWidget(table_);

    table_->setModel(couchModel_);

    setMinimumWidth(600);
    setMinimumHeight(200);
    setLayout(layout);
}

CouchModel* CouchWidget::model()
{
    return couchModel_;
}
