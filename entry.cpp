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
    double angle, l, kl, kx, ky;
    n = this->ui->repititionsInput->value();
    angle = qDegreesToRadians(this->ui->angleInput->value());
    l = this->ui->lengthInput->value();
    kl = this->ui->multiplierInput->value();
    kx = qSin(angle / 2);
    ky = qCos(angle / 2);
    this->step(n, 0, 0, l, kx, ky, kl);
}

void EntryWidget::on_exitButton_clicked()
{
    this->close();
}

void EntryWidget::on_clearButton_clicked()
{
    this->scene->clear();
}

void EntryWidget::step(const int &n, const double &x, const double &y, const double &l, const double &kx, const double &ky, const double &kl)
{
    if(n > 0){
        double dx, dy, nx1, nx2, ny;
        dx = l * kx;
        dy = l * ky;
        nx1 = x + dx;
        nx2 = x - dx;
        ny = y - dy;
        this->scene->addLine(x, y, nx1, ny);
        this->scene->addLine(x, y, nx2, ny);
        this->step(n-1, nx1, ny, l * kl, kx, ky, kl);
        this->step(n-1, nx2, ny, l * kl, kx, ky, kl);
    }
}
