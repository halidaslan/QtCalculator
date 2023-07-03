#include "calculator.h"
#include "ui_calculator.h"


double calcVal = 0.0;
bool mulTrigger = false;
bool divTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

double memAddVal = 0.0;
bool memTrigger = false;
double solution = 0.0;


Calculator::Calculator(QWidget *parent):
      QMainWindow(parent),
      ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(clicked()), this,
            SLOT(ClearDisplay()));

    connect(ui->MemAdd, SIGNAL(clicked()), this,
            SLOT(MemAdd()));
    connect(ui->MemClear, SIGNAL(clicked()), this,
            SLOT(MemClear()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
    ui->Display->setText(butVal);
    } else
    {
    QString newVal = displayVal + butVal;
    double dblNewVal = newVal.toDouble();
    ui->Display->setText(QString::number(dblNewVal, 'g',16));

    }
}

void Calculator::MathButtonPressed(){
    mulTrigger = false;
    divTrigger = false;
    addTrigger = false;
    subTrigger = false;
    memTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        mulTrigger = true;
    } else if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    }else {
        memTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    //double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || mulTrigger || divTrigger){
    if(addTrigger){
        solution = calcVal + dblDisplayVal;
    } else if(subTrigger){
        solution = calcVal - dblDisplayVal;
    } else if(mulTrigger){
        solution = calcVal * dblDisplayVal;
    } else if(divTrigger){
        solution = calcVal / dblDisplayVal;
    }
  }
    ui->Display->setText(QString::number(solution));
    if(memTrigger){
        memAddVal = solution;
        ui->Display->setText("45");
    }
}


void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}


void Calculator::ClearDisplay(){
    if(ui->Clear){
        ui->Display->setText("0");
    }
}
void Calculator::MemAdd(){
    //double solution = 0.0;
    //double memAddVal = 0.0;
    QString displayVal = ui->Display->text();

    if(memTrigger){
        double dblDisplayVal = displayVal.toDouble();
        memAddVal = dblDisplayVal + memAddVal;
    }
    ui->Display->setText(QString::number(memAddVal));
}
void Calculator::MemClear(){
    if(ui->MemClear){
    memAddVal = 0.0;
    solution = 0.0;
    ui->Display->setText("0");
    }


}










