#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QWidget>

namespace Ui {
class dialogAbout;
}

class dialogAbout : public QWidget
{
    Q_OBJECT
    
public:
    explicit dialogAbout(QWidget *parent = 0);
    ~dialogAbout();
    
private:
    Ui::dialogAbout *ui;
};

#endif // DIALOGABOUT_H
