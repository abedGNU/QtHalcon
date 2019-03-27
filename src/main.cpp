#include "mainwindow.h"
#include <QApplication>

/**
 * @brief
 * @param
 * @return
 * @todo
 * @date
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
