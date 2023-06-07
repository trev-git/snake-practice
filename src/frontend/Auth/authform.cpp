/**
 * Модуль authform.cpp
 * Автор: Хохлов Тимофей <xoxlow.timofey@yandex.ru>
 */

#include <QMessageBox>
#include <QFile>

#include "authform.h"
#include "ui_authform.h"
#include "database.h"
#include "snakemessagebox.h"

/**
 * Метод AuthForm
 *
 * Конструктор класса AuthForm. Настраивает подключение к БД.
 *
 * Формальный параметр:
 *
 * parent - родитель окна.
 */

AuthForm::AuthForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthForm),
    db(Database("C:/Users/trev/snake-practice/users.db"))
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизация");
    this->setWindowIcon(QIcon(":/icon"));

    if (!db.isOpen())
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка открытия БД!");
    }
}

/**
 * Метод ~AuthForm
 *
 * Деструктор класса. Удаляет интерфейс программы.
 */

AuthForm::~AuthForm()
{
    delete ui;
}

/**
 * Метод on_login_clicked
 *
 * Обрабатывает нажатие на кнопку Login.
 *
 * Локальные переменные:
 *
 * username - имя пользователя;
 * password - пароль пользователя.
 * e - исключение.
 */

void AuthForm::on_login_clicked()
{
    std::string username = this->ui->username->text().toStdString();
    std::string password = this->ui->password->text().toStdString();

    try
    {
        if (!db.userLogin(username, password))
        {
            fail.exec(false, "Ошибка", "Не удалось войти! Проверьте имя пользователя или пароль.");
            return;
        }
        // здесь будет переход на MainMenu
        success.exec(true, "Успешно", "Авторизация успешна!");

    }
    catch (std::runtime_error &e)
    {
        fail.exec(false, "Ошибка", e.what());
    }
}

/**
 * Метод on_signup_clicked
 *
 * Обрабатывает нажатие на кнопку Sign Up.
 *
 * Локальные переменные:
 *
 * username - имя пользователя;
 * password - пароль пользователя.
 * e - исключение.
 */

void AuthForm::on_signup_clicked()
{
    std::string username = this->ui->username->text().toStdString();
    std::string password = this->ui->password->text().toStdString();

    try
    {
        db.userSignUp(username, password);
        success.exec(true, "Успешно!", "Регистрация успешна!");
    }
    catch (std::runtime_error &e)
    {
        fail.exec(false, "Ошибка", e.what());
    }
}
