/**
 * Модуль snakemessagebox.h
 * Автор: Хохлов Тимофей <xoxlow.timofey@yandex.ru>
 *
 * Методы класса SnakeMessageBox:
 *
 * SnakeMessageBox - конструктор класса;
 * exec - вывод диалогового окна на экран.
 *
 * Поле класса SnakeMessageBox:
 * msg - диалоговое окно.
 */

#ifndef SNAKEMESSAGEBOX_H
#define SNAKEMESSAGEBOX_H

#include <QMessageBox>

class SnakeMessageBox
{
public:
    SnakeMessageBox();
    void exec(bool success, QString title, QString text);
    QMessageBox msg;
};

#endif // SNAKEMESSAGEBOX_H
