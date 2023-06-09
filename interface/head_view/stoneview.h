#ifndef STONEVIEW_H
#define STONEVIEW_H
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../../head/Card.h"
#include "../../head/Board.h"

class VueBorne : public QPushButton
{
    Q_OBJECT
public:
    //deux constructeurs differents
    explicit VueBorne(/*const Stone& s,*/ QWidget *parent = nullptr);
    const Stone& getCarte() const { return *borne; }
    void setNb(int i){nb = i;}
protected:
           //void paintEvent(QPaintEvent *event) override;
private:
    const Stone* borne=nullptr;
    QPen pen;
    QBrush brush;
    int nb;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void borneClicked(int i);
public slots:
private slots:
    void clickedEvent() { emit borneClicked(nb);}
};






#endif // STONEVIEW_H
