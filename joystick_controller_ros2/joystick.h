#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QDialog>


namespace Ui {
class joystick; // Forward declaration of the UI class
}


class joystick : public QDialog
{
    Q_OBJECT

public:
    explicit joystick(QWidget *parent = nullptr);
    ~joystick();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void joystickMoved(double xPercent, double yPercent);

private slots:
    void on_pushButton_clicked();

private:

//    joystick *my_joystick;
     Ui::joystick *ui; // Declare the UI member pointer

    QPointF center;  // Center of the joystick
    QPointF handle;  // Position of the handle
    qreal radius;    // Radius of the joystick
    bool isDragging; // Is the joystick being dragged?

    QPointF constrainToCircle(const QPointF &point);
};

#endif // JOYSTICK_H
