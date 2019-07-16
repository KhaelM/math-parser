#include <QApplication>
#include <QWidget>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setlocale(LC_NUMERIC, "C"); // sscanf fix


    MainWindow window;
    window.show();
        
    return app.exec();
}
