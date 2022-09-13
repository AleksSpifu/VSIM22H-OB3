#include "mainwindow.h"
#include <QApplication>
//#include "trianglesurface.h"

int main(int argc, char *argv[])
{
   /* TriangleSurface t;
    t.construct();
    t.writeFile("sinxy.txt");*/
    //Forces the usage of desktop OpenGL
    //Attribute must be set before Q(Gui)Application is constructed:
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    //Makes an Qt application
    QApplication a(argc, argv);

    //Makes the Qt MainWindow and shows it.
    MainWindow w;
    w.show();

    return a.exec();
}
