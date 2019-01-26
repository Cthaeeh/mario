#include "couchwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QLabel>

CouchWidget::CouchWidget(QWidget *parent)
    : QWidget(parent),
      table_(new QTableView(this)),
      couchModel_(new CouchModel(this))
{
    auto layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Couch"));
    layout->addWidget(table_);

    table_->setModel(couchModel_);

    setMinimumWidth(500);
    setMinimumHeight(200);
    setLayout(layout);
}

CouchModel* CouchWidget::model()
{
    return couchModel_;
}
