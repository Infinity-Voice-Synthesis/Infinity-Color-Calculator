#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QColorDialog>
#include <QMouseEvent>
#include <QCursor>
#include <QRgb>

class ColorSelection final : public QMainWindow
{
    Q_OBJECT

public:
    ColorSelection(QWidget *parent = Q_NULLPTR);

private:
    QColor maincolor;

    const double hMargin = 0.2;
    const double vMargin = 0.2;

    const double topBar = 0.05;

    const double seedFront = 0.8;
    const double seedMain = 0.45;
    const double seedBack = 0.35;

    bool lPressed = false;

    void showDialog();

    QColor getMainColor(const QColor& mainColor);
    QColor getBackColor(const QColor& mainColor);
    QColor getFrontColor(const QColor& mainColor);

    bool dark = false;

protected:
    void resizeEvent(QResizeEvent* event)override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void paintEvent(QPaintEvent* event)override;
};
