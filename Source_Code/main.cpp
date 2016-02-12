#include "richest_in_the_world.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Richest_in_the_world w;
    w.show();

    return a.exec();
}
