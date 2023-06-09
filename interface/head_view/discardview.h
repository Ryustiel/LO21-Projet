#ifndef DISCARDVIEW_H
#define DISCARDVIEW_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
//#include "../../head/Card.h"
//inclure la classe Discard

/*
class DiscardView : public QPushButton
{
    Q_OBJECT
public:
    //DiscardView(const Card& c, QWidget *parent = nullptr);
    explicit DiscardView(QWidget *parent = nullptr);

protected:
    void dessiner(QPainter& painter); //methode pour dessiner le visuel de la carte
    void paintEvent(QPaintEvent *event) override;

private:
    //un vecteur de VueCarte ??
    QPen pen;
    QBrush brush;

signals:
    void carteClicked(VueCarte*);

public slots:

private slots:
    void clickedEvent() {
        emit carteClicked(this);
        qDebug() << "card CLICK";
    }
};
*/


#endif // DISCARDVIEW_H
