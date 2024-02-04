#include "managersaddeditdialog.h"
#include "ui_managersaddeditdialog.h"

bool ManagersAddEditDialog::checkInput()
{
    bool flag = true;

    if(ui->lineEdit_pib->text().isEmpty())
    {
        ui->label_error_pib->setVisible(true);
        ui->label_error_pib->setText("Помилка! Поле пусте!");
        flag = false;
    }
    else
        ui->label_error_pib->setVisible(false);
    // TODO: Добавить проверку на формат мобильного номера (оператор и длина)
    if(ui->lineEdit_phoneNumber->text().isEmpty())
    {
        ui->label_error_phone_number->setVisible(true);
        ui->label_error_phone_number->setText("Помилка! Поле пусте!");
        flag = false;
    }
    else
        ui->label_error_phone_number->setVisible(false);

    if(ui->lineEdit_address->text().isEmpty())
    {
        ui->label_error_address->setVisible(true);
        ui->label_error_address->setText("Помилка! Поле пусте!");
        flag = false;
    }
    else
        ui->label_error_address->setVisible(false);

    return flag;
}

ManagersAddEditDialog::ManagersAddEditDialog(QDataWidgetMapper *mapper, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagersAddEditDialog)
{
    ui->setupUi(this);

    this->mapper = mapper;
    mapper->addMapping(ui->lineEdit_pib,(int)MANAGERS::PIB);
    mapper->addMapping(ui->lineEdit_address, (int)MANAGERS::ADDRESS);
    mapper->addMapping(ui->lineEdit_phoneNumber, (int)MANAGERS::PHONE_NUMBER);
    mapper->setCurrentIndex(mapper->currentIndex());

    ui->label_error_pib->setVisible(false);
    ui->label_error_phone_number->setVisible(false);
    ui->label_error_address->setVisible(false);
}

ManagersAddEditDialog::~ManagersAddEditDialog()
{
    delete ui;
}

void ManagersAddEditDialog::on_pushButton_save_clicked()
{
    if(!checkInput())
        return;

    mapper->submit();
    this->accept();
    close();
}


void ManagersAddEditDialog::on_pushButton_cancel_clicked()
{
    mapper->revert();
    close();
}

