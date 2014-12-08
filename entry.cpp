#include "entry.h"
#include "ui_entry.h"
#include "QtMath"

EntryWidget::EntryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // Create the scene and store it as a class member
    this->scene = new QGraphicsScene(this);
    // Se the canvas's scene to the newly created scene
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
    // Get number of repitions/levels
    n = this->ui->repititionsInput->value();
    // Get the angle to transform each time
    // This is half of the angle which seperates branches
    // Set it as a member
    this->angle = (this->ui->angleInput->value() / 2);
    // Get the length of the first branches
    l = this->ui->lengthInput->value();
    // Get the length multiplier and store it as a member
    this->k = this->ui->multiplierInput->value();
    // Begin the recursion starting at (0,0) pointing straight up
    this->step(n, 0, 0, l, 90);
}

void EntryWidget::on_exitButton_clicked()
{
    // Close the main window when the exit button is clicked
    this->close();
}

void EntryWidget::on_clearButton_clicked()
{
    // Clear the scene of lines when the clear button is clicked
    this->scene->clear();
}

void EntryWidget::step(const int &n, const double &x, const double &y, const double &l, const double &angle)
{
    // If we aren't at the deepest level
    if(n > 0){
        // Create two temporary lines to perform the point transformation calculations of length l starting
        // at the end of the previous line (x,y)
        QLineF* line1 = new QLineF(x, y, x, y - l);
        QLineF* line2 = new QLineF(x, y, x, y - l);
        // Set the angle of both lines to the angle of the previous line +/- the angle offset
        // as received from user input earlier
        line1->setAngle(angle + this->angle);
        line2->setAngle(angle - this->angle);
        // Create variabels to store the data of the lines before...
        qreal lx, ly, langle, rx, ry, rangle;
        lx = line1->x2();
        ly = line1->y2();
        langle = line1->angle();
        rx = line2->x2();
        ry = line2->y2();
        rangle = line2->angle();
        // ...deleting the lines from memory. I extract the line information
        // from the lines and then delete them because passing the lines themselves
        // through the stack during recursion seems complicated in regards to having
        // to preform memory management. So, to avoid that hassle, I simply pass the
        // line data to QGraphicsScene::addLine which probably just create a QLineF
        // object anyway but it'll let me delegate the memory management to the
        // QGraphicsScene.
        delete line1;
        delete line2;
        // Draw the lines
        this->scene->addLine(x, y, lx, ly);
        this->scene->addLine(x, y, rx, ry);
        // And recurse!
        // We pass n-1 to representing moving down a layer.
        // We start at the endpoints of the lines we created here
        // We shorten the line by the multilier k received from user input earlier
        // And we pass the absolute angles of the lines
        this->step(n-1, lx, ly, l * this->k, langle);
        this->step(n-1, rx, ry, l * this->k, rangle);
    }
}

/**
 * Will clear and draw if the autoCheckBox is checked
 */
void EntryWidget::autoUpdate()
{
    if(this->ui->autoCheckBox->isChecked()){
        // We call click on the buttons instead of directly calling their handlers
        // for the sake of consistency and convention. For example, if the button's
        // are disabled, these will do nothing as the should.
        this->ui->clearButton->click();
        this->ui->drawButton->click();
    }
}

// The next handlers just call autoUpdate whenever any of the inputs are modified.

void EntryWidget::on_angleInput_editingFinished()
{
    this->autoUpdate();
}

void EntryWidget::on_lengthInput_editingFinished()
{
    this->autoUpdate();
}

void EntryWidget::on_multiplierInput_editingFinished()
{
    this->autoUpdate();
}

void EntryWidget::on_repititionsInput_editingFinished()
{
    this->autoUpdate();
}

void EntryWidget::on_autoCheckBox_clicked()
{
    this->autoUpdate();
}
