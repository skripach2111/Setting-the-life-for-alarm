#ifndef SERVICESADDEDITDIALOG_H
#define SERVICESADDEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "databasemodule.h"

namespace Ui {
class ServicesAddEditDialog;
}

class ServicesAddEditDialog : public QDialog
{
    Q_OBJECT
    QDataWidgetMapper *mapper;

    bool checkInput();

public:
    explicit ServicesAddEditDialog(QDataWidgetMapper *mapper, QWidget *parent = nullptr);
    ~ServicesAddEditDialog();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ServicesAddEditDialog *ui;
};

#endif // SERVICESADDEDITDIALOG_H
