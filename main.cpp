#include "compiledark.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CompileDark w;
    w.setWindowTitle("Qt OpenGL");
    w.setGeometry(100, 100, 500, 500);
    w.show();
    w.setMouseTracking(true);
    w.setCursor(QCursor(Qt::BlankCursor));

    return a.exec();
}
