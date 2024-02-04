#include "servicesaddeditdialog.h"
#include "ui_servicesaddeditdialog.h"

bool ServicesAddEditDialog::checkInput()
{
    bool flag = true;

    if(ui->lineEdit_title->text().isEmpty())
    {
        ui->label_error_title->setVisible(true);
        ui->label_error_title->setText("Помилка! Поле пусте!");
        flag = false;
    }
    else
        ui->label_error_title->setVisible(false);

    if(ui->plainTextEdit_equipment->toPlainText().isEmpty())
    {
        ui->label_error_equipment->setVisible(true);
        ui->label_error_equipment->setText("Помилка! Поле пусте!");
        flag = false;
    }
    else
        ui->label_error_equipment->setVisible(false);

    if(ui->plainTextEdit_description->toPlainText().isEmpty())
    {
        ui->label_error_description->setVisible(true);
        ui->label_error_description->setText("Помилка! Поле пусте!");
        flag = false;
    }
    else
        ui->label_error_description->setVisible(false);

    if(ui->doubleSpinBox_cost->value() <= 0)
    {
        ui->label_error_cost->setVisible(true);
        ui->label_error_cost->setText("Помилка! Некорекне значення!");
        flag = false;
    }
    else
        ui->label_error_cost->setVisible(false);

    return flag;
}

ServicesAddEditDialog::ServicesAddEditDialog(QDataWidgetMapper *mapper, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServicesAddEditDialog)
{
    ui->setupUi(this);

    ui->label_error_title->setVisible(false);
    ui->label_error_equipment->setVisible(false);
    ui->label_error_description->setVisible(false);
    ui->label_error_cost->setVisible(false);

    this->mapper = mapper;
    mapper->addMapping(ui->lineEdit_title, (int)SERVICES::TITLE);
    mapper->addMapping(ui->plainTextEdit_equipment, (int)SERVICES::EQUIPMENT);
    mapper->addMapping(ui->plainTextEdit_description, (int)SERVICES::DESCRIPTION);
    mapper->addMapping(ui->doubleSpinBox_cost, (int)SERVICES::PRICE);
    mapper->setCurrentIndex(mapper->currentIndex());
}

ServicesAddEditDialog::~ServicesAddEditDialog()
{
    delete ui;
}

void ServicesAddEditDialog::on_pushButton_save_clicked()
{
    if(!checkInput())
        return;

    mapper->submit();
    accept();
    close();
}


void ServicesAddEditDialog::on_pushButton_cancel_clicked()
{
    mapper->revert();
    close();
}

