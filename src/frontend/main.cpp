#include <QApplication>

#include "authform.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    AuthForm w;
    w.show();
    return a.exec();
}
