/**
 * Модуль database.cpp
 * Автор: Хохлов Тимофей <xoxlow.timofey@yandex.ru>
 */

#include <QSqlQuery>
#include <format>
#include <stdexcept>
#include <QDebug>
#include <QSqlError>
#include <openssl/sha.h>
#include <sstream>

#include "database.h"

/**
 * Метод Database
 *
 * Создаёт новое подключение к БД.
 *
 * Формальный параметр:
 *
 * databaseName - название БД.
 */

Database::Database(QString const &databaseName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    db.open();
    qDebug() << db.isOpen();
}

/**
 * Метод ~Database
 *
 * Закрывает существующее подключение к БД.
 */

Database::~Database()
{
    db.close();
}

/**
 * Метод addHighscore
 *
 * Добавляет новый рекорд в таблицу HighScore.
 *
 * Формальные параметры:
 *
 * level - уровень;
 * score - количество очков;
 * userId - ID пользователя.
 *
 * Локальная переменная:
 *
 * q - запрос к БД.
 */

void Database::addHighscore(int level, int score, int userId)
{
    QSqlQuery q(QString::fromStdString(std::format("INSERT INTO HighScore (level, score, userId) VALUES ({}, {}, {})", level, score, userId)), db);
    q.prepare("INSERT INTO HighScore (level, score, userId) VALUES (:level, :score, :userId)");
    q.bindValue(":level", level);
    q.bindValue(":score", score);
    q.bindValue(":userId", userId);
    if (!q.exec()) throw std::runtime_error("Не удалось занести ваш рекорд в базу данных!");
}

/**
 * Метод userSignUp
 *
 * Регистрирует нового пользователя в БД.
 *
 * Формальные параметры:
 *
 * username - никнейм пользователя;
 * password - пароль пользователя.
 *
 * Локальная переменная:
 *
 * q - запрос к БД.
 */

void Database::userSignUp(std::string username, std::string password)
{
    QSqlQuery q(db);
    q.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");
    q.bindValue(":username", QString::fromStdString(username));
    q.bindValue(":password", QString::fromStdString(generateSHA256(password)));

    if (!q.exec()) throw std::runtime_error("Не удалось занести пользователя в базу данных!");
}

/**
 * Метод userLogin
 *
 * Авторизация пользователя.
 *
 * Формальные параметры:
 *
 * username - имя пользователя;
 * password - пароль пользователя.
 *
 * Локальные переменные:
 *
 * q - запрос к БД.
 */

bool Database::userLogin(std::string username, std::string password)
{
    QSqlQuery q(db);
    q.prepare("SELECT username, password FROM Users WHERE username LIKE :username AND password LIKE :password");
    q.bindValue(":username", QString::fromStdString(username));
    q.bindValue(":password", QString::fromStdString(generateSHA256(password)));
    if (!q.exec()) throw std::runtime_error("Не удалось получить пользователей!");

    if (q.next())
    {
        qDebug() << "Пользователь авторизован!";
        return true;
    }

    return false;
}

/**
 * Метод generateSHA256
 *
 * Генерирует хеш на основе алгоритма SHA-256.
 *
 * Формальный параметр:
 *
 * str - строка, которую надо хешировать.
 *
 * Локальные переменные:
 *
 * hash - хранилище хеша;
 * ss - поток строки для помещения хеша;
 */

std::string Database::generateSHA256(std::string const &str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char *>(str.c_str()), str.length(), hash);

    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return ss.str();
}
