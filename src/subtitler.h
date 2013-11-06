#ifndef SUBTITLER_H
#define SUBTITLER_H

#include <QMainWindow>

namespace Ui {
    class Subtitler;
}

class Subtitler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Subtitler(QWidget *parent = 0);
    ~Subtitler();

private:
    Ui::Subtitler *ui;
};

#endif // SUBTITLER_H
