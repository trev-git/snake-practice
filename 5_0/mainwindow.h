#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QString>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }

QT_END_NAMESPACE

struct wall
{
private:
    int start_x, end_x, start_y, end_y;
public:
    wall(int start_x, int end_x, int start_y, int end_y)
    {
        this->start_x=start_x;
        this->end_x=end_x;
        this->start_y=start_y;
        this->end_y=end_y;
    }

};

class level
{
public:
    int num_level;
    QString level_background;
    QVector <wall> walls;
    level(int num_level, QString level_background, QVector <wall> walls)
    {
        this->num_level=num_level;
        this->level_background=level_background;
        this->walls=walls;
    }

};

class Snake     // класс для описания сегментов тела
{

public:

    Snake(QWidget *parent = nullptr);
    void setup(int cor_x,int cor_y);
    ~Snake();

    int cor_x=0;    //координата сегмента по х
    int cor_y=0;    //координата сегмента по у
    QRect snake_frame;      // прямоугольник для отрисовки сегмента

private:


};

class Game : public QWidget
{
    Q_OBJECT

private:
    Ui::Game *ui;
    QVector<Snake> snake;       // вектор сегментов тела
    QRect head;                 // прямоугольник голы

    int step_snake_IM_stuk_Help_me=0;     //последнее направление движения(последняя клавиша нажатая)

    bool step=false;    //было ли определено направление в текущем шагу
    int timer_id = 100; // хранит таймер
    int dir_x = 0;      //направление движеня по х
    int dir_y = 1;     //направление движеня по у
    int cor_x=0;        //координата по х
    int cor_y=0;        //координата по у
    int score=0;


    int angle;
    QImage def_body, first_body, headpic, turn_body;
    QString link_head = ":/new/Snake/default_sprite.png",
    link_def_body = ":/new/Snake/body_segment_default.png",
    link_first_body = ":/new/Snake/body_segment_after_head.png",
    link_turn_body = ":/new/Snake/body_segment_on_turn_right.png";

    bool aple=false;    // определяет, существует ли яблоко в данный момент
    QRect fruit_obj;       // прямоугольник яблока
    QVector<QString> links_fruits = {":/new/Fruits/apple.png", ":/new/Fruits/Banana.png", ":/new/Fruits/orange.png", ":/new/Fruits/pear.png"};
    int types_of_fruits_now;

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    void drawSnake();
    void drawBody();
    void f_angle_head(int &angle_head);
    void transform_image(QImage &target_pic, QString link, int angle);
    void aplleSpawn();
    void eat();
    void keyPressEvent(QKeyEvent *ev);
    void paintEvent(QPaintEvent *ev);
    void timerEvent(QTimerEvent *ev);

};




#endif // MAINWINDOW_H
