#include "keywindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *window = new MainWindow(0);
    window->show();
//    asm("mov eax, eax  mov ebx, ebx");
    return a.exec();
}
