#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QShowEvent>
#include <QWidget>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QWidget
{
    Q_OBJECT

  public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog() override;

    void retranslate();

  protected:
    void showEvent(QShowEvent *event) override;

  private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
