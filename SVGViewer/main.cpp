#include "SVGViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SVGViewer w;
    w.show();
    return a.exec();
}
