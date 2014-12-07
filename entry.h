#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class Widget;
}

class EntryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EntryWidget(QWidget *parent = 0);
    ~EntryWidget();

private slots:
    void on_drawButton_clicked();

    void on_exitButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    double k = 0.8;
    double angle = 60.0;
    void step(const int &n, const double &x, const double &y, const double &l, const double &angle);
};

#endif // ENTRY_H
