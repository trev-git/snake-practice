#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QString>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QLabel>
#include <QRect>
#define FIELD_WIDTH 400         // ширина поля
#define FIELD_HEIGHT 400        // высота поля
#define SEGMENT_WIDTH 20        //ширина сегмента тела змейки
#define SEGMENT_HEIGHT 20       //высота сегмента тела змейки
// версия 0.5.2

int spawnx=360;                 //координата спавна яблока по х
int spawny=360;                 //... по у



Snake::Snake(QWidget *parent)

{

}


void Snake::setup(int cor_x,int cor_y)          //функция устанавливает первичные координаты для сегмента тела и создает объект класса Qrect для его отрисовки
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
   // , ui(new Ui::Game)
{
  //  ui->setupUi(this);
    resize(FIELD_WIDTH, FIELD_HEIGHT);  // создание поля заданного размера
    this->cor_x=40;        //FIELD_WIDTH / 2;        //начальные координаты змейки по х
    this->cor_y=40;       //FIELD_HEIGHT / 2;       // ... по у
    this->head=QRect(this->cor_x,this->cor_y, SEGMENT_WIDTH, SEGMENT_HEIGHT); // создание сегмента-головы по заданным координатам и заданного размера
    change_speed = 190;

    this->timer_id = startTimer(change_speed);       //частота смены кадров. де факто скорость

    Snake s(nullptr);                       // создание первого сегмента тела
    s.setup(this->cor_x-20*dir_x,this->cor_y-20*dir_y);
    snake.push_back(s);
    background_draw();

    label = new QLabel();
}

Game::~Game()
{
    //delete ui;
}




void Game::paintEvent(QPaintEvent *ev)      // функция, что отрисовывает элементы во включенных функциях
{
    Q_UNUSED(ev);

    drawSnake();
    aplleSpawn();
}

void Game::background_draw()
{
    level_skin.load(levels[level_now].link_pic_background);
    palette.setBrush(QPalette::Window, level_skin);
    this->setPalette(palette);
}

void Game::drawBody()       // функция по отрисовке тела
     {
         snake[0].snake_frame.moveTo(this->cor_x-20*dir_x, this->cor_y-20*dir_y);   // перемещение первого сегмента на нужную позицию
         QPainter paint(this);
         transform_image(grap_obj, link_first_body, angle); //Для отрисовки поворота нужны координаты головы
         paint.drawImage(snake[0].snake_frame, grap_obj);
         head_angle = angle;
         last_direction.setX(dir_x);
         last_direction.setY(dir_y);
         for (int j=1;j<snake.size();j++)        // цикл перемещения и отрисовки всего остального тела
         {
             // QRegion (snake[j-1].snake_frame);
             snake[j].snake_frame.moveTo(snake[j-1].cor_x, snake[j-1].cor_y);    // перемещение сегмента
             QPainter painta(this);
             if (j==1)
             {
                 distance_segm=abs(head_y-snake[j].snake_frame.y());
                 if ((last_direction.x()==-1)&&(head_y>snake[j].snake_frame.y()))//Вниз и влево
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(0);
                         last_direction.setY(1);
                         angle = 180;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=0;
                     head_angle=angle;
                 }
                 else if ((last_direction.x()==-1)&&(head_y<snake[j].snake_frame.y())) //Вверх и влево
                 {
                     if(distance_segm==20)
                         {
                         last_direction.setX(0);
                         last_direction.setY(-1);
                         angle = 90;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=0;
                     head_angle=angle;
                 }
                 else if ((last_direction.x()==1)&&(head_y>snake[j].snake_frame.y())) //Вниз и вправо
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(0);
                         last_direction.setY(1);
                         angle = 270;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=0;
                     head_angle=angle;
                 }
                 else if ((last_direction.x()==1)&&(head_y<snake[j].snake_frame.y())) //Вверх и вправо
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(0);
                         last_direction.setY(-1);
                         angle = 0;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=0;
                     head_angle=angle;
                 }
                 else if ((last_direction.y()==-1)&&(head_x>snake[j].snake_frame.x())) //Направо и вверх
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(1);
                         last_direction.setY(0);
                         angle = 180;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=90;
                     head_angle=angle;
                 }
                 else if ((last_direction.y()==-1)&&(head_x<snake[j].snake_frame.x())) //Налево и вверх
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(-1);
                         last_direction.setY(0);
                         angle = 270;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=90;
                     head_angle=angle;
                 }
                 else if ((last_direction.y()==1)&&(head_x>snake[j].snake_frame.x())) //Направо и вниз
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(1);
                         last_direction.setY(0);
                         angle = 90;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=90;
                     head_angle=angle;
                 }
                 else if ((last_direction.y()==1)&&(head_x<snake[j].snake_frame.x())) //Налево и вниз
                 {
                     if(distance_segm==20)
                     {
                         last_direction.setX(-1);
                         last_direction.setY(0);
                         angle = 0;
                         transform_image(grap_obj, link_turn_body, angle);
                         painta.drawImage(snake[j-1].snake_frame, grap_obj);
                     }
                     angle=90;
                     head_angle=angle;

                 }
                 else
                 {
                     angle=head_angle;
                 }
             }
             else
             {
                distance_segm=abs(snake[j-2].snake_frame.y()-snake[j].snake_frame.y());
                if ((last_direction.x()==-1)&&((snake[j-2].snake_frame.y()>snake[j].snake_frame.y())))//Вниз и влево
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(0);
                        last_direction.setY(1);
                        angle = 180;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=0;
                    head_angle=angle;
                }
                else if ((last_direction.x()==-1)&&(snake[j-2].snake_frame.y()<snake[j].snake_frame.y())) //Вверх и влево
                {
                    if(distance_segm==20)
                        {
                        last_direction.setX(0);
                        last_direction.setY(-1);
                        angle = 90;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=0;
                    head_angle=angle;
                }
                else if ((last_direction.x()==1)&&(snake[j-2].snake_frame.y()>snake[j].snake_frame.y())) //Вниз и вправо
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(0);
                        last_direction.setY(1);
                        angle = 270;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=0;
                    head_angle=angle;
                }

                else if ((last_direction.x()==1)&&(snake[j-2].snake_frame.y()<snake[j].snake_frame.y())) //Вверх и вправо
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(0);
                        last_direction.setY(-1);
                        angle = 0;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                                        angle=0;
                    head_angle=angle;
                }
                else if ((last_direction.y()==-1)&&(snake[j-2].snake_frame.x()>snake[j].snake_frame.x())) //Направо и вверх
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(1);
                        last_direction.setY(0);
                        angle = 180;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=90;
                    head_angle=angle;
                }
                else if ((last_direction.y()==-1)&&(snake[j-2].snake_frame.x()<snake[j].snake_frame.x())) //Налево и вверх
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(-1);
                        last_direction.setY(0);
                        angle = 270;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=90;
                    head_angle=angle;
                }
                else if ((last_direction.y()==1)&&(snake[j-2].snake_frame.x()>snake[j].snake_frame.x())) //Направо и вниз
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(1);
                        last_direction.setY(0);
                        angle = 90;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=90;
                    head_angle=angle;
                }
                else if ((last_direction.y()==1)&&(snake[j-2].snake_frame.x()<snake[j].snake_frame.x())) //Налево и вниз
                {
                    if(distance_segm==20)
                    {
                        last_direction.setX(-1);
                        last_direction.setY(0);
                        angle = 0;
                        transform_image(grap_obj, link_turn_body, angle);
                        painta.drawImage(snake[j-1].snake_frame, grap_obj);
                    }
                    angle=90;
                    head_angle=angle;

                }
                else
                {
                    angle=head_angle;
                }
             }
             transform_image(grap_obj, link_def_body, angle);
             painta.drawImage(snake[j].snake_frame, grap_obj);
         }
         for (int j=1;j<snake.size();j++)        // цикл запоминания текущих координат сегментов тела
         {
             if ((head.x()==snake[j].snake_frame.x() && head.y()==snake[j].snake_frame.y()) )  // проверка на столкновение головы с сегментом
             {
                 label->close();
                 QMessageBox m;
                 m.setText("jyf clj[kf");

                 close();
                 m.exec();
             }
             snake[j].cor_x=snake[j].snake_frame.x();
             snake[j].cor_y=snake[j].snake_frame.y();

             snake[0].cor_x=snake[0].snake_frame.x();            // запоминание текущих координат 1-го сегмента тела
             snake[0].cor_y=snake[0].snake_frame.y();

         }
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
    head.moveTo((head.x()) + (FIELD_WIDTH / SEGMENT_WIDTH) * dir_x, (head.y()) + (FIELD_WIDTH / SEGMENT_HEIGHT) * dir_y);// перемещение сегмента головы
        cor_x+=dir_x*20;        //запоминание координат текуших головы
        cor_y+=dir_y*20;
        angle = 0;
        if (dir_y == 1)
            angle = 180;
        else if (dir_x==1)
            angle = 90;
        else if (dir_x==-1)
            angle = 270;
        QPainter painter(this);
        transform_image(grap_obj, link_head, angle);
        painter.drawImage(head, grap_obj);
        //painter.drawRect(head);
        painter.end();// отрисовка головы
       //repaint();
        head_x=head.x();
        head_y=head.y();
        drawBody();
   // }
}

void Game::transform_image(QImage &target_pic, QString link, int angle)
{
    QImage *pic = new QImage();
    pic->load(link);
    target_pic=pic -> transformed(QTransform().rotate(angle));
}

void Game::keyPressEvent(QKeyEvent *ev) // функция перехвата сигнала с клавиатуры
{
    if ((this->cor_x>FIELD_HEIGHT || this->cor_x<0) || (this->cor_y>FIELD_WIDTH || this->cor_y<0)) // проверка на выход за границы поля
    {
        this->close(); // закрытие окна
    }

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
    QRegion(this->fruit_obj);  // то самое обновление
    aple=false;
    correct_coordinates=false;
    while (correct_coordinates == false)
    {       spawnx=20*QRandomGenerator::global()->bounded(20);  // генерация случайных координат по х
            spawny=20*QRandomGenerator::global()->bounded(20);  //... по у
            if (levels[level_now].walls.size()==0)
            {
                correct_coordinates = true;
            }
            else
            {
                for (int i=0;i<levels[level_now].walls.size(); i++)
                {
                    if(((spawnx>=levels[level_now].walls[i].start_x)&&(spawnx<=levels[level_now].walls[i].end_x))&&
                            ((spawny<=levels[level_now].walls[i].start_y)&&(spawny>=levels[level_now].walls[i].end_y)))
                    {
                        correct_coordinates=false;
                    break;
                    }
                    else
                        correct_coordinates = true;
                }
            }
            for (int i=0; i<snake.size();i++)
            {

                if ((i==0)&&(head.x()!=spawnx)&&(head.y()!=spawny))
                {
                   correct_coordinates = true;
                }
                if ((snake[i].cor_x!=spawnx)&&(snake[i].cor_y!=spawny))
                {
                   correct_coordinates = true;
                }
                else
                {
                    correct_coordinates = false;
                }
            }
    }
    types_of_fruits_now=QRandomGenerator::global()->bounded(levels[level_now].num_fruits);
    score++;
    if (score==levels[level_now].fruits_for_next_level)
    {
        time_use_fruits=0;
        score=0;
        use_spechial_fruits = false;
        level_now++;
        snake.resize(1);
        step_snake_IM_stuk_Help_me=Qt::Key_Down;
        this->dir_x = 0;
        this->dir_y = 1;
        this->cor_x=40;        //FIELD_WIDTH / 2;        //начальные координаты змейки по х
        this->cor_y=40;       //FIELD_HEIGHT / 2;       // ... по у
        this->head=QRect(this->cor_x,this->cor_y, SEGMENT_WIDTH, SEGMENT_HEIGHT); // создание сегмента-головы по заданным координатам и заданного размера
        Snake s(nullptr);                       // создание первого сегмента тела
        s.setup(this->cor_x-20*dir_x,this->cor_y-20*dir_y);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        background_draw();
        eat();
    }
    else
    {
        Snake s(nullptr);
        s.setup(snake.last().snake_frame.x()-20*dir_x*snake.size(),snake.last().snake_frame.y()-20*dir_y*snake.size());
        snake.push_back(s);     //добавление нового сегмента
    }
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
    //if(aple==false)
    //{
      // label->setText(" ");
    //}

    label->setWindowFlag(Qt::SplashScreen); //убираем рамки
    label->setAttribute(Qt::WA_TranslucentBackground);
    //setStyleSheet c помощью него задаем размеры, цвет текста
    label->setStyleSheet("QLabel {color : red; font-size:17px}");
    balanc_fruit=levels[level_now].fruits_for_next_level-score;
    QString text = "До следующего уровня: " + QString::number(balanc_fruit);
    label->setText(text);
    //А тут мой минихак с заданием width и height под размер текста
    label->adjustSize();
    int w = label->width();
    int h =  label->height();
    //0, 0 - координаты куда будем текст помещать
    label->setGeometry(40,60, w, h);
    label->adjustSize();
    label->show();

aple=true;
aplleSpawn();
    Q_UNUSED(ev);

QKeyEvent ke(QEvent::KeyPress,step_snake_IM_stuk_Help_me,Qt::NoModifier);   // эмуляция нажатия последней клавиши
step=true;
    //drawSnake();
    repaint();

    if (((this->cor_x==spawnx) && (this->cor_y==spawny))/*|| (snake[0].cor_x==spawnx && snake[0].cor_y==spawny)*/&& aple==true )//проверка съедения яблока
    {
        if ((level_now==levels.size())&&(balanc_fruit==1))
        {
            QMessageBox mess;
            mess.setText("Ты помедил!\n Молодец!");
            this->close();  // закрытие окна
            mess.exec();
        }
        switch(types_of_fruits_now)
        {
        case 1:
            change_speed = 150;
            use_spechial_fruits = true;
            break;
        case 2:
            change_speed = 250;
            use_spechial_fruits = true;
        default:
            change_speed = 190;
            use_spechial_fruits = false;
        }
        eat();
    }
    if ((use_spechial_fruits == true)||(time_use_fruits!=0))
    {

        if (time_use_fruits<=time_for_special_fruits)
        {
            time_use_fruits+=change_speed;
        }
        else
        {
            time_use_fruits=0;
            change_speed=190;
            use_spechial_fruits=false;
        }
    }
    else
        change_speed=190;
        //if(QRandomGenerator::global()->bounded(10)>3)
        //{
           // killTimer(timer_id);
           //timer_id=startTimer(frame_update);}

QMessageBox mess;


    if ((head.x()>FIELD_HEIGHT || head.x()<0) || (head.y()>FIELD_WIDTH || head.y()<0))      // проверка выхода за границы поля
    {
        QString score_str=QString::number(score);
        mess.setText("Ты помер. твой счет " + score_str);
        this->close();  // закрытие окна
        mess.exec();
    }

    for (int i=0;i<levels[level_now].walls.size(); i++)
    {
        if(((head.x()<levels[level_now].walls[i].start_x)||(head.x()>levels[level_now].walls[i].end_x))||
           ((head.y()<levels[level_now].walls[i].start_y)||(head.y()>levels[level_now].walls[i].end_y)))
            {
                correct_coordinates=true;
            }
        else
            {
                correct_coordinates=false;
                break;
            }
    }
    if (correct_coordinates==false)
    {   QString score_str=QString::number(score);
        mess.setText("Ты помер. твой счет " + score_str);
        this->close();  // закрытие окна
        mess.exec();
    }
    killTimer(timer_id);
    this->timer_id = startTimer(change_speed);
    qWarning() << level_now << change_speed << types_of_fruits_now << time_use_fruits;
}
