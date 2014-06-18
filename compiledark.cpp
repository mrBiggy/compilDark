#include <QTimer>
#include <QDebug>
#include <QString>
#include <math.h>
#include "compiledark.h"



CompileDark::CompileDark(QWidget *parent) :
    QGLWidget(parent),
    geese_size(30),
    point(0),
    wax(500),
    way(500),
    singling(false),
    ispressPressClose(false)
{
    geese_coord();
    setFormat(QGLFormat(QGL::DoubleBuffer)); // двойная буферизация
    glDepthFunc(GL_LEQUAL); //буфер глубины

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(geese_coord()));
    timer->start(750);
}

CompileDark::~CompileDark()
{

}

void CompileDark::initializeGL()
{
    qglClearColor(Qt::black);
}

void CompileDark::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    wax = nWidth;
    way = nHeight;
}

void CompileDark::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION);    // устанавливаем матрицу
    glLoadIdentity();   // загружаем матрицу
    glOrtho(0, wax, way, 0, 1, 0); // одготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qglColor(Qt::white);
    QString text = "вы набрали ";
    text += QString::number(point);
    text += " очков:";

    //renderText(10, 10, 0, &text, QFont(), 2000);
    renderText(20.0, 20.0, 0.0, text);

    if(ispressPressClose) {
        drawPressButton();
    } else drawButton();


    geese(); // рисуем объект

    if(singling == true)
        singling_lb();

    self_cursor();

    swapBuffers();
}

void CompileDark::keyPressEvent(QKeyEvent *ke)
{
    switch(ke->key()) {
    case Qt::Key_Space:
        geese_coord();
        break;
    }
    updateGL();
}
void CompileDark::mouseMoveEvent(QMouseEvent *me)
{
    cax = me->x();
    cay = me->y();
    updateGL();
}

void CompileDark::mousePressEvent(QMouseEvent *me)
{
    // При нажатии левой кнопки мыши определяем попали мы в гуся или нет?
    if(me->button() == Qt::LeftButton) {
        if(me->x() > gdx && me->y() < gdy+geese_size) {
            point++;
            geese_coord();
        }
        // Нажатие на кнопку выход
        if(me->x() > wax-120 && me->y() < way-10) {
            qDebug() << "Close button pressed";
            //drawPressButton();
            ispressPressClose = true;
        } else ispressPressClose = false;
    }

    // Если была нажата левая кнопка мыши, получаем начальные координаты выделения
    if(me->button() == Qt::LeftButton) {
        singling = true;
        cbx = me->x();
        cby = me->y();
        updateGL();
    } else {
        singling = false;
    }
    updateGL();
}

void CompileDark::mouseReleaseEvent(QMouseEvent *me)
{
    // Если отпускаем левую кнопку мыши - удалить выделение
    if(singling == true && me->button() == Qt::LeftButton) {
        singling = false;
    }
    if(ispressPressClose == true && me->button() == Qt::LeftButton) {
        abort();
        ispressPressClose = false;
    }
    updateGL();
}

void CompileDark::self_cursor()
{
    glBegin(GL_POLYGON);
        glColor3f(1,0,0);// Цвет курсора
        // Координаты курсора
        glVertex2f(cax, cay);
        glVertex2f(cax+20, cay+20);
        glVertex2f(cax+8, cay+20);
        glVertex2f(cax, cay+30);
    glEnd();
}

void CompileDark::singling_lb()
{
    glBegin(GL_POLYGON);
       glColor4f(0,1,0, 0.25);// Цвет выделенной области
       // Координаты выделенной области
       glVertex2f(cbx, cby);
       glVertex2f(cax, cby);
       glVertex2f(cax, cay);
       glVertex2f(cbx, cay);
    glEnd();
}

void CompileDark::geese()
{
    glBegin(GL_LINE_LOOP);
        glColor3f(0,0,1); // цвет выделенной области
        // координаты выделенной области
        /*int N = 12;
        for (int i = 0; i < N; i++) {
            float angle = 2 * M_PI * i / N;
            glVertex2f(cos(angle), sin(angle));
        }*/
        glVertex2f(gdx, gdy);
        glVertex2f(gdx+geese_size, gdy);
        glVertex2f(gdx+geese_size, gdy+geese_size);
        glVertex2f(gdx, gdy+geese_size);
    glEnd();
}

void CompileDark::geese_coord()
{
    gdx = (rand() % (wax - geese_size*2)) + geese_size;
    gdy = (rand() % (way - geese_size*2)) + geese_size;
    qDebug() << gdx << "," << gdy;
    updateGL();
}

void CompileDark::drawButton()
{
    glBegin(GL_POLYGON);
        glColor4f(0,1,0, 0.25); // цвет выделенной области
        // координаты выделенной области
        glVertex2f(wax-120, way-40);
        glVertex2f(wax-10, way-40);
        glVertex2f(wax-10, way-10);
        glVertex2f(wax-120, way-10);
    glEnd();
    qglColor(Qt::yellow);
    QString text = "Close";
    renderText(wax-85, way-20, 0.0, text);
}

void CompileDark::drawPressButton()
{
    glBegin(GL_POLYGON);
        glColor4f(0,1,1, 0.25); // цвет выделенной области
        // координаты выделенной области
        glVertex2f(wax-120, way-40);
        glVertex2f(wax-10, way-40);
        glVertex2f(wax-10, way-10);
        glVertex2f(wax-120, way-10);
    glEnd();
    qglColor(Qt::darkYellow);
    QString text = "Close";
    renderText(wax-85, way-20, 0.0, text);
}














