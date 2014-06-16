#ifndef COMPILEDARK_H
#define COMPILEDARK_H

#include <QMainWindow>

namespace Ui {
class CompileDark;
}

class CompileDark : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompileDark(QWidget *parent = 0);
    ~CompileDark();

private:
    Ui::CompileDark *ui;
};

#endif // COMPILEDARK_H
