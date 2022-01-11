#include "ColorSelection.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorSelection w;
    w.show();
    return a.exec();
}
