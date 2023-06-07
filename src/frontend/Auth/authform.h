/**
 * Модуль authform.h
 * Автор: Хохлов Тимофей <xoxlow.timofey@yandex.ru>
 *
 * Форма авторизации
 *
 * Методы класса AuthForm:
 *
 * AuthForm - конструктор класса;
 * on_login_clicked - слот для обработки нажатия на кнопку;
 * on_signup_clicked - слот для обработки нажатия на кнопку;
 * ~AuthForm - деструктор класса.
 *
 * Поля класса AuthForm:
 *
 * ui - интерфейс программы;
 * db - база данных;
 * success - диалоговое окно успеха;
 * fail - диалоговое окно ошибки.
 */

#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>

#include "database.h"
#include "snakemessagebox.h"

namespace Ui {
class AuthForm;
}

class AuthForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

private slots:
    void on_login_clicked();

    void on_signup_clicked();

private:
    Ui::AuthForm *ui;
    Database db;
    SnakeMessageBox success;
    SnakeMessageBox fail;
};

#endif // AUTHFORM_H
