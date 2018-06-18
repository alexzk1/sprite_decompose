#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::retranslate()
{
    ui->retranslateUi(this);
}

void AboutDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    ui->title->setText(QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
}
