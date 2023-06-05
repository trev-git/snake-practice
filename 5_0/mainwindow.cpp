#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QString>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#define FIELD_WIDTH 400         // ширина поля
#define FIELD_HEIGHT 400        // высота поля
#define SEGMENT_WIDTH 20        //ширина сегмента тела змейки
#define SEGMENT_HEIGHT 20       //высота сегмента тела змейки
// версия 0.5.2

int spawnx=230;                 //координата спавна яблока по х
int spawny=90;                 //... по у



Snake::Snake(QWidget *parent)

{

}


void Snake::setup(int cor_x,int cor_y)          //фуекция устанавливает первичные координаты для сегмента тела и создает объект класса Qrect для его отрисовки
{
    this->snake_frame=QRect(cor_x, cor_y, SEGMENT_WIDTH, SEGMENT_HEIGHT);
    this->cor_x=cor_x;
    this->cor_y=cor_y;
}

Snake::~Snake()
{

}


Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    resize(FIELD_WIDTH, FIELD_HEIGHT);  // создание поля заданного размера
    this->cor_x=50;        //FIELD_WIDTH / 2;        //начальные координаты змейки по х
    this->cor_y=50;       //FIELD_HEIGHT / 2;       // ... по у
    this->head=QRect(this->cor_x,this->cor_y, SEGMENT_WIDTH, SEGMENT_HEIGHT); // создание сегмента-головы по заданным координатам и заданного размера

    this->timer_id = startTimer(180);       //частота смены кадров. де факто скорость

    Snake s(nullptr);                       // создание первого сегмента тела
    s.setup(this->cor_x-20*dir_x,this->cor_y-20*dir_y);
    snake.push_back(s);
    QVector<level> levels {{3,":/new/biom/iceland_Level_3.png", {{90,110, 160, 420},{100,300, 150,170} } }};
    QImage level_skin (levels[0].level_background);
    QPalette palette;
    palette.setBrush(QPalette::Window, level_skin);
    this->setPalette(palette);

}


Game::~Game()
{
    delete ui;
}




void Game::paintEvent(QPaintEvent *ev)      // функция, что отрисовывает элементы во включенных функциях
{
    Q_UNUSED(ev);

    drawSnake();
    aplleSpawn();
}






     void Game::drawBody()       // функция по отрисовке тела
     {
         snake[0].snake_frame.moveTo(this->cor_x-20*dir_x, this->cor_y-20*dir_y);   // перемещение первого сегмента на нужную позицию
         QPainter paint(this);
         f_angle_head(angle);
         transform_image(first_body, link_first_body, angle); //Для отрисовки поворота нужны координаты головы
         paint.drawImage(snake[0].snake_frame, first_body);

         for (int j=1;j<snake.size();j++)        // цикл перемещения и отрисовки всего остального тела
         {
             // QRegion (snake[j-1].snake_frame);

         snake[j].snake_frame.moveTo(snake[j-1].cor_x, snake[j-1].cor_y);    // перемещение сегмента
         QPainter painta(this);
         f_angle_head(angle);
         transform_image(def_body, link_def_body, angle);
         painta.drawImage(snake[j].snake_frame, def_body);
         }

         for (int j=1;j<snake.size();j++)        // цикл запоминания текущих координат сегментов тела
         {
             if ((head.x()==snake[j].snake_frame.x() && head.y()==snake[j].snake_frame.y()) )  // проверка на столкновение головы с сегментом
             {
                 QMessageBox m;
                 m.setText("jyf clj[kf");

                 close();
                 m.exec();
             }
             snake[j].cor_x=snake[j].snake_frame.x();
             snake[j].cor_y=snake[j].snake_frame.y();

         }

         snake[0].cor_x=snake[0].snake_frame.x();            // запоминание текущих координат 1-го сегмента тела
         snake[0].cor_y=snake[0].snake_frame.y();
     }

void Game::drawSnake()      // функция перемещения и отрисовки головы
{
       // цвет головы
    //for (auto &i:head)
    //{

/*
 * пишешь QImage имя_объекта("путь к файлу на компе или в ресурсах");
 *painter.drawImage(в какой объект QRect нужно вписать изображение. объект QImage с самим изображением);
 *\\ painter - объект класса QPainter, который сейчас рисует. ТЕ в aplleSpawn вместо painter стоит pain
 *\\получившееся изображение будет выглядеть маленьким. Это связано так же с тем, что жоня говна кусок и не обрезал нормально кадры.
 * потом, когда все поменяшь , можешь поиграться с размерами поля и секментов, что бы все вышлядело нормуль
 * когда заменишь графику для головы и фрукта - пришли фоточку, а лучше кружочек ил видео.
 * нужны для этого мои файлы с движком и ресурсы твои, ибо с ними проще. свои нароботки можешь оставить при себе
*/
        head.moveTo((head.x()) + (FIELD_WIDTH / SEGMENT_WIDTH) * dir_x, (head.y()) + (FIELD_WIDTH / SEGMENT_HEIGHT) * dir_y);
// перемещение сегмента головы
        cor_x+=dir_x*20;        //запоминание координат текуших головы
        cor_y+=dir_y*20;

        QPainter painter(this);
        f_angle_head(angle);
        transform_image(headpic, link_head, angle);
        painter.drawImage(head, headpic);
        //painter.drawRect(head);
        painter.end();// отрисовка головы
       //repaint();
        drawBody();
        qWarning() << cor_x << cor_y;
   // }
}

void Game::f_angle_head(int &angle)
{
    angle = 0;
    if (dir_y == 1)
        angle = 180;
    else if (dir_x==1)
        angle = 90;
    else if (dir_x==-1)
        angle = 270;
}

void Game::transform_image(QImage &target_pic, QString link, int angle)
{
    QImage *pic = new QImage();
    pic->load(link);
    target_pic=pic -> transformed(QTransform().rotate(angle));
}

void Game::keyPressEvent(QKeyEvent *ev) // функция перехвата сигнала с клавиатуры
{
    int now=ev->key();      // запоминание только что нажатой клавиши

    if(now+2==step_snake_IM_stuk_Help_me||now-2==step_snake_IM_stuk_Help_me) // проверка на невозможноть задания обратного направления движения
    {

    }
    else{step_snake_IM_stuk_Help_me=now;}

if(step)        // условие, не позволяющее менять направление чеще, чем раз в шаг(на высоких скоростах не работает(?))
{
    switch (step_snake_IM_stuk_Help_me) //дешифровка сигнала с клавиши
    {
    case Qt::Key_Left:
        this->dir_x = -1;
        this->dir_y = 0;
        break;
    case Qt::Key_Right:
        this->dir_x = 1;
        this->dir_y = 0;
        break;
    case Qt::Key_Up:
        this->dir_x = 0;
        this->dir_y = -1;
        break;
    case Qt::Key_Down:
        this->dir_x = 0;
        this->dir_y = 1;
    }
    step=false;
}
    if ((this->cor_x>FIELD_HEIGHT || this->cor_x<0) || (this->cor_y>FIELD_WIDTH || this->cor_y<0)) // проверка на выход за границы поля
    {
        this->close(); // закрытие окна
    }
   // QPaintEvent(QRegion( head ),head);
    //drawSnake();
    //repaint();
    //update();
}

void Game::eat()        // функция поедания яблока. стиранмие яблока(обновлением его фрейма) и задает новые координаты для его спавна на случайной основе. добовляет новый сегмент телу
{
    score+=1;
        QRegion(this->fruit_obj);  // то самое обновление
        aple=false;
        do
        {   spawnx=20*QRandomGenerator::global()->bounded(20);  // генерация случайных координат по х
            spawny=20*QRandomGenerator::global()->bounded(20);  //... по у
            types_of_fruits_now=QRandomGenerator::global()->bounded(4);
        }
        while((((spawnx>=90)&&(spawnx<=110))&&((spawny>=160)&&(spawny<=420)))||(((spawnx>=100)&&(spawnx<=300))&&((spawny>=150)&&(spawny<=170))));

        Snake s(nullptr);
        s.setup(snake.last().snake_frame.x()-20*dir_x*snake.size(),snake.last().snake_frame.y()-20*dir_y*snake.size());
        snake.push_back(s);     //добавление нового сегмента
}

void Game::aplleSpawn() // функция спавна яблока
{
    QPainter pain(this);
    QImage fruit_pic(links_fruits[types_of_fruits_now]);
    fruit_obj=QRect(spawnx,spawny, SEGMENT_WIDTH, SEGMENT_HEIGHT); //задает координаты и размер яблоку
    pain.drawImage(fruit_obj, fruit_pic);  //отрисовывает яблоко
}
void Game::timerEvent(QTimerEvent *ev)      // функция ,срабатывающая по таймеру
{

aple=true;
aplleSpawn();
    Q_UNUSED(ev);

QKeyEvent ke(QEvent::KeyPress,step_snake_IM_stuk_Help_me,Qt::NoModifier);   // эмуляция нажатия последней клавиши
step=true;
    //drawSnake();
    repaint();

    if (((this->cor_x>=spawnx-10)&&(cor_x<=spawnx+10)) && ((this->cor_y>=spawny-10)&&(cor_y<=spawny+10)) /*|| (snake[0].cor_x==spawnx && snake[0].cor_y==spawny)*/&& aple==true)//проверка съедения яблока
    {
        eat();
        if(QRandomGenerator::global()->bounded(10)>3)
        {
            killTimer(timer_id);
            timer_id=startTimer(180);
        }

    }
QMessageBox mess;
    if ((this->cor_x>=FIELD_HEIGHT || this->cor_x<=0) || (this->cor_y>=FIELD_WIDTH || this->cor_y<=0))      // проверка выхода за границы поля
    {

        mess.setText("Ты помер");
        this->close();  // закрытие окна
        mess.exec();
    }
    if ((((this->cor_x>=90)&&(this->cor_x<=110))&&((this->cor_y>=160)&&(this->cor_y<=420)))||(((this->cor_x>=100)&&(this->cor_x<=300))&&((this->cor_y>=150)&&(this->cor_y<=170))))
    {   QString score_str=QString::number(score);
        mess.setText("Ты помер. твой счет " + score_str);
        this->close();  // закрытие окна
        mess.exec();
    }
}


//3 уровень
//нижняя стенка 100 по x, y от 420 до 160
//верхняя x от 100 до 300, y 160
