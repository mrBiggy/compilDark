#include "compiledark.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CompileDark w;
    w.show();

    return a.exec();
}
