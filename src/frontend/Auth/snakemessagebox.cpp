/**
 * Модуль snakemessagebox.cpp
 * Автор: Хохлов Тимофей <xoxlow.timofey@yandex.ru>
 */

#include "snakemessagebox.h"

/**
 * Метод SnakeMessageBox
 *
 * Конструктор класса, устанавливает стили диалогового окна.
 */

SnakeMessageBox::SnakeMessageBox()
{

    msg.setStyleSheet("QMessageBox {"
                      "  background-color: #00ff00;"
                      "  background-image: url(:/auth-bg);"
                      "}"
                      "QMessageBox QLabel {"
                      "  color: #fff;"
                      "}"
                      "QMessageBox QPushButton {"
                      "  width: 100px;"
                      "  height: 32px;"
                      "  border-radius: 16px;"
                      "  background-color: #77ff77;"
                      "  color: #3e7857;"
                      "}"
                    );


}

/**
 * Метод exec
 *
 * Выводит диалоговое окно на экран.
 *
 * Формальные параметры:
 *
 * success - успешно ли действие или нет;
 * title - заголовок диалогового окна;
 * text - Текст диалогового окна.
 */

void SnakeMessageBox::exec(bool success, QString title, QString text)
{
    msg.setWindowTitle(title);
    msg.setText(text);

    if (success)
        msg.setIconPixmap(QPixmap(":/victory_splash"));
    else
        msg.setIconPixmap(QPixmap(":/game_over_splash"));

    msg.exec();
}
