#include "quick_phrase.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuickPhrase w;
    w.show();
    return a.exec();
}
