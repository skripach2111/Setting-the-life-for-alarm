#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QStyleFactory>
#include <QFile>

#include "databasemodule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QFile file(":/styles/home_alarm_style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    DatabaseModule dbm;

    if(!dbm.connect())
    {
        QMessageBox::critical(nullptr, "Критична помилка!", "Неможливо під'єднатися до бази даних.\nПрограму буде завершено.");
        return 1;
    }

    MainWindow w(&dbm);
    w.show();
    return a.exec();
}
