#ifndef INFOBOX_H
#define INFOBOX_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <iostream>

class InfoBox : public QWidget{
signals:
    void closing() {};
private:
    QLabel * txt;
    QPushButton * ok;
    QVBoxLayout* layout;
public:
    explicit InfoBox(QString text, QString wName) : QWidget() {
        setWindowTitle(wName);
        txt = new QLabel(text);
        ok = new QPushButton("ok");
        layout = new QVBoxLayout();
        layout->addWidget(txt);
        layout->addWidget(ok);
        connect(ok, &QPushButton::clicked, this, &InfoBox::close);
        setLayout(layout);
    };


    void closeEvent(QCloseEvent *bar){
        std::cout << "infobox dead" <<std::endl;
        emit closing();
    }

};

#endif // INFOBOX_H
