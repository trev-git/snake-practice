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
#include <QTimer>
#include <chrono>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }

QT_END_NAMESPACE

struct wall
{
    int start_x, end_x, start_y, end_y;

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
    int num_fruits, fruits_for_next_level;
    QString link_pic_background;
    QVector <wall> walls;
    level(int num_fruits, int fruits_for_next_level, QString link_pic_background, QVector <wall> walls)
    {
        this->num_fruits=num_fruits;
        this->fruits_for_next_level=fruits_for_next_level;
        this->link_pic_background=link_pic_background;
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
   // Ui::Game *ui;
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
    QPoint last_direction;


    int angle, head_angle, distance_segm, head_x, head_y;
    QImage grap_obj;
    QString link_head = ":/new/Snake/default_sprite.png",
    link_def_body = ":/new/Snake/body_segment_default.png",
    link_first_body = ":/new/Snake/body_segment_after_head.png",
    link_turn_body = ":/new/Snake/body_segment_on_turn_right.png";

    bool aple=false;    // определяет, существует ли яблоко в данный момент
    bool correct_coordinates=true;
    bool use_spechial_fruits=false;
    QRect fruit_obj;       // прямоугольник яблока
    QVector<QString> links_fruits = {":/new/Fruits/apple.png", ":/new/Fruits/pear.png", ":/new/Fruits/orange.png", ":/new/Fruits/Banana.png"};
    int types_of_fruits_now;
    int balanc_fruit;
    int time_use_fruits=0;
    int change_speed;
    int time_for_special_fruits=5000;

    QVector<level> levels {{1,5,":/new/biom/hill_Level_1.png",{}},
                           {2,8,":/new/biom/iceland_Level_3.png",{{90,110, 160, 420},{100,280, 150,170}}},
                           {4,13, ":/new/biom/castle.png" ,{{200,220,40,100}, {200,400,90,100}, {0,160,180,200},  {220,400,180,200}, {0, 160, 270, 280}, {150, 160, 280, 320}}}};
    //Перерисовать правую верхнюю стенку кастл левел.
    int level_now = 0;
    QImage break_skin;
    QImage level_skin;
    QPalette palette;

    QLabel *label;

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    void background_draw();
    void drawSnake();
    void drawBody();
    void transform_image(QImage &target_pic, QString link, int angle);
    void aplleSpawn();
    void eat();
    void keyPressEvent(QKeyEvent *ev);
    void paintEvent(QPaintEvent *ev);
    void timerEvent(QTimerEvent *ev);
};




#endif // MAINWINDOW_H
