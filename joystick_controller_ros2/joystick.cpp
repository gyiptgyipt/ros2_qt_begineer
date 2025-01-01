#include "joystick.h"
#include "ui_joystick.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <math.h>
#include <QDebug>


#include <cmath>


//joystick::joystick(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::joystick)
//{
//    ui->setupUi(this);
//}

joystick::joystick(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::joystick), // Initialize the UI pointer
          center(150, 150), // Initialize the joystick center
          handle(150, 150), // Initialize the handle position
          radius(100),      // Initialize the joystick radius
          isDragging(false) // Initialize the dragging flag
    {
        ui->setupUi(this);  // Setup the UI
        setFixedSize(300, 300); // Set the widget size



    }

void joystick::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draw joystick boundary
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(center, radius, radius);

    // Draw joystick handle
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(handle, 20, 20); // Handle size
}

void joystick::mousePressEvent(QMouseEvent *event)
{
    if ((std::sqrt(std::pow(event->pos().x() - center.x(), 2) +
               std::pow(event->pos().y() - center.y(), 2))) <= radius)
    {
        isDragging = true;
        handle = constrainToCircle(event->pos());
        update();
    }
}

void joystick::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        handle = constrainToCircle(event->pos());

        // Emit joystick position as a percentage
        double xPercent = (handle.x() - center.x()) / radius;
        double yPercent = (center.y() - handle.y()) / radius; // Inverted y-axis
        emit joystickMoved(xPercent, yPercent);

        update();
    }
}

void joystick::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (isDragging)
    {
        isDragging = false;
        handle = center; // Reset to center
        emit joystickMoved(0, 0); // Joystick at rest
        update();
    }
}

QPointF joystick::constrainToCircle(const QPointF &point)
{
    QPointF direction = point - center;
    qreal distance = std::sqrt(std::pow(direction.x(), 2) + std::pow(direction.y(), 2));
    if (distance > radius)
    {
        direction /= distance; // Normalize
        return center + direction * radius;
    }
    return point;
}

joystick::~joystick()
{
    delete ui;
}

void joystick::on_pushButton_clicked()
{
    this->close();
}



//void joystick::on_pushButton_clicked()
//{
//    this->close();
//}








