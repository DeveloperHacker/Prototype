#include <QtWidgets>
#include <QtCore>
#include "Application/mainwindow.h"

#include "Core/light.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();

}
