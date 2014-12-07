#include "entry.h"
#include "ui_entry.h"
#include "QtMath"

EntryWidget::EntryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);
    this->ui->canvas->setScene(this->scene);
}

EntryWidget::~EntryWidget()
{
    delete ui;
}

void EntryWidget::on_drawButton_clicked()
{
    int n;
    double l;
    n = this->ui->repititionsInput->value();
    this->angle = (this->ui->angleInput->value() / 2);
    l = this->ui->lengthInput->value();
    this->k = this->ui->multiplierInput->value();
    this->step(n, 0, 0, l, 90);
}

void EntryWidget::on_exitButton_clicked()
{
    this->close();
}

void EntryWidget::on_clearButton_clicked()
{
    this->scene->clear();
}

void EntryWidget::step(const int &n, const double &x, const double &y, const double &l, const double &angle)
{
    if(n > 0){
        QLineF* line1 = new QLineF(x, y, x, y - l);
        QLineF* line2 = new QLineF(x, y, x, y - l);
        line1->setAngle(angle + this->angle);
        line2->setAngle(angle - this->angle);
        qreal lx, ly, langle, rx, ry, rangle;
        lx = line1->x2();
        ly = line1->y2();
        langle = line1->angle();
        rx = line2->x2();
        ry = line2->y2();
        rangle = line2->angle();
        delete line1;
        delete line2;
        this->scene->addLine(x, y, lx, ly);
        this->scene->addLine(x, y, rx, ry);
        this->step(n-1, lx, ly, l * this->k, langle);
        this->step(n-1, rx, ry, l * this->k, rangle);
    }
}
