#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->EQ->setValidator(new QRegExpValidator(QRegExp("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$")));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::memNum()
{
    dotActivated = false;
    unar = false;
    blockUnar=false;
    if(!fnExist && ui->EQ->text() != "")
    {
        std::stringstream ss(ui->EQ->text().toStdString());
        ss >> fn;
        ui->EQ->setPlaceholderText(ui->EQ->text() == "" ? "0" : ui->EQ->text());
        ui->EQ->setText("");
        fnExist = true;
    }
}
void MainWindow::on_ZERO_clicked() {
    if(ui->EQ->text()!="0" && ui->EQ->text()!="-0" )
        ui->EQ->setText(ui->EQ->text()+"0");
}
void MainWindow::on_DZERO_clicked(){
    if(ui->EQ->text()=="")
          ui->EQ->setText("0");
    else if(ui->EQ->text()!="0" && ui->EQ->text()!="-0")
        ui->EQ->setText(ui->EQ->text()+"00");
}
void MainWindow::on_ONE_clicked()  {ui->EQ->setText(ui->EQ->text() + "1");}
void MainWindow::on_TWO_clicked()  {ui->EQ->setText(ui->EQ->text() + "2");}
void MainWindow::on_THREE_clicked(){ui->EQ->setText(ui->EQ->text() + "3");}
void MainWindow::on_FOUR_clicked() {ui->EQ->setText(ui->EQ->text() + "4");}
void MainWindow::on_FIVE_clicked() {ui->EQ->setText(ui->EQ->text() + "5");}
void MainWindow::on_SIX_clicked()  {ui->EQ->setText(ui->EQ->text() + "6");}
void MainWindow::on_SEVEN_clicked(){ui->EQ->setText(ui->EQ->text() + "7");}
void MainWindow::on_EIGHT_clicked(){ui->EQ->setText(ui->EQ->text() + "8");}
void MainWindow::on_NINE_clicked() {ui->EQ->setText(ui->EQ->text() + "9");}
void MainWindow::on_DIVIDE_clicked()  { op = DIVIDE;   memNum(); }
void MainWindow::on_MULTIPLY_clicked(){ op = MULTYPLY; memNum(); }
void MainWindow::on_PLUS_clicked()    { op = PLUS;     memNum(); }
void MainWindow::on_MINUS_clicked()   {
    if(ui->EQ->text()=="" && !blockUnar)
    {
        unar=!unar;
        ui->EQ->setPlaceholderText((std::string(unar ? "-" : "") + "0").c_str());
        blockUnar=true;
        return;
    }
    op = MINUS;
    memNum();
}
void MainWindow::on_EQUAL_clicked()
{

    if(!snExist && ui->EQ->text() != "")
    {
        std::stringstream ss(ui->EQ->text().toStdString());
        ss >> sn;
        snExist=true;
    }
    if(!snExist)
        return;
    ui->EQ->setText("");
    dotActivated = false;
    blockUnar=true;
    switch(op)
    {
        case NONE: return;
        case PLUS: ui->EQ->setPlaceholderText(QString(std::to_string(fn=(fn+sn)).c_str())); break;
        case MINUS:ui->EQ->setPlaceholderText(QString(std::to_string(fn=fn-sn).c_str())); break;
        case MULTYPLY:ui->EQ->setPlaceholderText(QString(std::to_string(fn=fn*sn).c_str())); break;
        case DIVIDE:ui->EQ->setPlaceholderText(QString(std::to_string(fn=fn/sn).c_str())); break;
    }
}
void MainWindow::on_CLR_clicked()
{
    fnExist = snExist = dotActivated = unar = blockUnar = false;
    op = NONE;
    ui->EQ->setText("");
    fn = 0;
    ui->EQ->setPlaceholderText("0");
}
void MainWindow::on_EQ_textChanged(const QString &arg1)
{
    if(arg1!="")
    {
        fnExist = snExist = false;
        static bool unarAdded = false;
        if(ui->EQ->placeholderText()=="-0" && !unarAdded)
        {
            unarAdded = true;
            ui->EQ->setText("-"+ui->EQ->text());
            unarAdded = false;
        }
    }
    if(arg1=="inf" || arg1=="nan")
    {
        ui->EQ->setPlaceholderText(ui->EQ->text());
        ui->EQ->setText("");
    }
}
void MainWindow::on_POINT_clicked()
{
    if(dotActivated) return;
    dotActivated = true;
    ui->EQ->setText(ui->EQ->text()+".");
}
void MainWindow::on_REV_clicked()
{
    long double n;
    std::stringstream ss(ui->EQ->text().toStdString());
    ss >> n;
    n = 1.0L/n;
    ui->EQ->setText(std::to_string(n).c_str());
    ui->EQ->setPlaceholderText(std::to_string(n).c_str());
}
void MainWindow::on_ANS_clicked()
{
    if(ui->EQ->placeholderText()!="-0")
        ui->EQ->setText(ui->EQ->placeholderText());
}
