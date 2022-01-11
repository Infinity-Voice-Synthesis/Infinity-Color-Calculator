#include "ColorSelection.h"

ColorSelection::ColorSelection(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMouseTracking(true);
    this->setWindowIcon(QIcon(":/ColorSelection/LOGO.png"));
    this->setMinimumSize(800, 600);
    //this->maincolor.setHsv(359, 255, 255 * this->seedMain);
    this->maincolor.setHsv(359, 255 * this->seedMain, 255);
}

void ColorSelection::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    QPoint&& pos = QCursor::pos();
    if (
        pos.x() >= this->width() * this->hMargin && pos.x() <= this->width() * (1 - this->hMargin) &&
        pos.y() >= this->height() * this->vMargin && pos.y() <= this->height() * (1 - this->vMargin)
        ) {
        this->setCursor(Qt::CursorShape::PointingHandCursor);
    }
    else {
        this->setCursor(Qt::CursorShape::ArrowCursor);
    }
    this->update();
}

void ColorSelection::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        QPoint&& pos = event->pos();
        if (
            pos.x() >= this->width() * this->hMargin && pos.x() <= this->width() * (1 - this->hMargin) &&
            pos.y() >= this->height() * this->vMargin && pos.y() <= this->height() * (1 - this->vMargin)
            ) {
            this->lPressed = true;
            this->setCursor(Qt::CursorShape::ClosedHandCursor);
        }
        else {
            this->dark = !this->dark;
            int h = 0;
            int s = 0;
            int v = 0;
            this->maincolor.getHsv(&h, &s, &v);
            if (this->dark) {
                this->maincolor.setHsv(h, s, 255 * this->seedMain);
            }
            else {
                this->maincolor.setHsv(h, 255 * this->seedMain, v);
            }
            this->update();
        }
    }
}

void ColorSelection::mouseMoveEvent(QMouseEvent* event)
{
    QPoint&& pos = event->pos();
    if (
        pos.x() >= this->width() * this->hMargin && pos.x() <= this->width() * (1 - this->hMargin) &&
        pos.y() >= this->height() * this->vMargin && pos.y() <= this->height() * (1 - this->vMargin)
        ) {
        if (this->lPressed) {
            this->setCursor(Qt::CursorShape::ClosedHandCursor);
        }
        else {
            this->setCursor(Qt::CursorShape::PointingHandCursor);
        }
    }
    else {
        if (this->lPressed) {
            this->setCursor(Qt::CursorShape::PointingHandCursor);
        }
        else {
            this->setCursor(Qt::CursorShape::ArrowCursor);
        }
    }
}

void ColorSelection::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (this->lPressed) {
            QPoint&& pos = event->pos();
            if (
                pos.x() >= this->width() * this->hMargin && pos.x() <= this->width() * (1 - this->hMargin) &&
                pos.y() >= this->height() * this->vMargin && pos.y() <= this->height() * (1 - this->vMargin)
                ) {
                this->setCursor(Qt::CursorShape::OpenHandCursor);
                this->showDialog();
            }
            else {
                this->setCursor(Qt::CursorShape::ArrowCursor);
            }
            this->lPressed = false;
        }
    }
}

void ColorSelection::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QColor backColor = this->getBackColor(this->maincolor);
    QColor frontColor = this->getFrontColor(this->maincolor);

    if (this->dark) {
        painter.fillRect(0, 0, this->width(), this->height(), QColor(30, 30, 30));
    }
    else {
        painter.fillRect(0, 0, this->width(), this->height(), QColor(240, 240, 240));
    }

    painter.fillRect(this->width() * this->hMargin, this->height() * this->vMargin, this->width() * (1 - 2 * this->hMargin), this->height() * (1 - 2 * this->vMargin), backColor);
    painter.fillRect(this->width() * this->hMargin, this->height() * this->vMargin, this->width() * (1 - 2 * this->hMargin), this->height() * this->topBar, this->maincolor);

    QPen pen;
    pen.setWidth(4);
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setColor(frontColor);
    painter.setPen(pen);

    QPolygon poly1;
    for (int i = 0; i <= 10; i++) {
        if (i % 2) {
            QPoint point(this->width() * this->hMargin + ((this->width() * (1 - 2 * this->hMargin)) / 10) * i, this->height() * (this->vMargin + 0.15));
            poly1.append(point);
        }
        else {
            QPoint point(this->width() * this->hMargin + ((this->width() * (1 - 2 * this->hMargin)) / 10) * i, this->height() * (1 - (this->vMargin + 0.15)));
            poly1.append(point);
        }
    }

    painter.drawPolyline(poly1);

    QBrush brush;
    brush.setColor(frontColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    painter.setBrush(brush);
    pen.setWidth(0);
    painter.setPen(pen);

    QPoint pointc(this->width() * this->hMargin + ((this->width() * (1 - 2 * this->hMargin)) / 10 / 4), this->height() * (this->vMargin + 0.5 * this->topBar));
    painter.drawEllipse(pointc, (int)(this->height() * this->topBar * 0.25), (int)(this->height() * this->topBar * 0.25));
}

void ColorSelection::showDialog()
{
    QColor color = QColorDialog::getColor(this->maincolor, this, "Select Main Color");
    if (color.isValid()) {
        int h = 0;
        int s = 0;
        int v = 0;
        color.getHsv(&h, &s, &v);
        if (this->dark) {
            this->maincolor.setHsv(h, s, 255 * this->seedMain);
        }
        else {
            this->maincolor.setHsv(h, 255 * this->seedMain, v);
        }
        
    }
    this->update();
}

QColor ColorSelection::getBackColor(const QColor& mainColor)
{
    int h = 0;
    int s = 0;
    int v = 0;
    mainColor.getHsv(&h, &s, &v);
    QColor color;
    if (this->dark) {
        color.setHsv(h, s, 255 * this->seedBack);
    }
    else {
        color.setHsv(h, 255 * this->seedBack, v);
    }
    return color;
}

QColor ColorSelection::getFrontColor(const QColor& mainColor)
{
    int h = 0;
    int s = 0;
    int v = 0;
    mainColor.getHsv(&h, &s, &v);
    QColor color;
    if (this->dark) {
        color.setHsv(h, s, 255 * this->seedFront);
    }
    else {
        color.setHsv(h, 255 * this->seedFront, v);
    }
    return color;
}
