/**
 * Модуль Database.h
 * Автор: Хохлов Тимофей <xoxlow.timofey@yandex.ru>
 *
 * Интерфейс для базы данных (БД) SQLite3 на основе QSqlDatabase
 *
 * Методы класса Database:
 *
 * Database - конструктор класса для инициализации подключения к БД;
 * ~Database - деструктор класса для закрытия подключения к БД;
 * addHighscore - интерфейс для добавления нового рекорда в БД;
 * userSignUp - интерфейс для регистрации пользователя;
 * userLogin - интерфейс для авторизации пользователя;
 * generateSHA256 - генерация хеша SHA256.
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class Database
{
public:
    Database(QString const &databaseName);
    ~Database();
    void addHighscore(int score, int level, int userId);
    void userSignUp(std::string username, std::string password);
    bool userLogin(std::string username, std::string password);
    static std::string generateSHA256(std::string const &str);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
