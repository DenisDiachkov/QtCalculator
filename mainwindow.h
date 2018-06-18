#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sstream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum OPERATION{NONE, MINUS, PLUS, MULTYPLY, DIVIDE};
private slots:
    void on_CLR_clicked();
    void on_EIGHT_clicked();
    void on_ZERO_clicked();
    void on_DZERO_clicked();
    void on_SIX_clicked();
    void on_ONE_clicked();
    void on_TWO_clicked();
    void on_THREE_clicked();
    void on_FOUR_clicked();
    void on_FIVE_clicked();
    void on_SEVEN_clicked();
    void on_NINE_clicked();
    void on_DIVIDE_clicked();
    void on_MULTIPLY_clicked();
    void on_PLUS_clicked();
    void on_MINUS_clicked();
    void on_EQUAL_clicked();
    void on_EQ_textChanged(const QString &arg1);
    void on_POINT_clicked();
    void on_REV_clicked();
    void on_ANS_clicked();
private:
    Ui::MainWindow *ui;
    void memNum();
    long double fn,
                sn;
    bool fnExist=false,
         snExist=false,
         dotStated=false,
         dotActivated=false,
         unar=false,
         blockUnar=false;
    OPERATION op=NONE;
};

#endif // MAINWINDOW_H
