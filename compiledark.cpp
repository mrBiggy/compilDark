#include "compiledark.h"
#include "ui_compiledark.h"

CompileDark::CompileDark(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompileDark)
{
    ui->setupUi(this);
}

CompileDark::~CompileDark()
{
    delete ui;
}
