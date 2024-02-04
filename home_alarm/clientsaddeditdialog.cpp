#include "clientsaddeditdialog.h"
#include "ui_clientsaddeditdialog.h"

bool ClientsAddEditDialog::checkInput()
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

ClientsAddEditDialog::ClientsAddEditDialog(QDataWidgetMapper *mapper, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsAddEditDialog)
{
    ui->setupUi(this);

    ui->label_error_pib->setVisible(false);
    ui->label_error_phone_number->setVisible(false);
    ui->label_error_address->setVisible(false);

    this->mapper = mapper;
    mapper->addMapping(ui->lineEdit_pib, (int)CLIENTS::PIB);
    mapper->addMapping(ui->lineEdit_address, (int)CLIENTS::ADDRESS);
    mapper->addMapping(ui->lineEdit_phoneNumber, (int)CLIENTS::PHONE_NUMBER);
    mapper->setCurrentIndex(mapper->currentIndex());
}

ClientsAddEditDialog::~ClientsAddEditDialog()
{
    delete ui;
}

void ClientsAddEditDialog::on_pushButton_save_clicked()
{
    if(!checkInput())
        return;

    mapper->submit();
    this->accept();
    close();
}


void ClientsAddEditDialog::on_pushButton_cancel_clicked()
{
    mapper->revert();
    close();
}

