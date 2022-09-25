#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setFixedSize(this->size());
    connect(ui->line_no_term, SIGNAL(editingFinished()), SLOT(first_rule()));
}
void MainWindow::get_rules()
{
    line_rules = ui->text_rules->toPlainText().split("\n");
}

void MainWindow::get_term_symbols()
{
    term_symbols = ui->line_term->text().split(",");
}

void MainWindow::get_no_term_symbols()
{
    no_term_symbols = ui->line_no_term->text().split(",");
}

void MainWindow::first_rule()
{
    QStringList no_term_loc;
    ui->comboBox_first_symb->clear();
    no_term_loc = ui->line_no_term->text().split(",");
    for(int i = 0; i < no_term_loc.size(); i++){
        ui->comboBox_first_symb->addItem(no_term_loc[i]);
    }
}

void MainWindow::on_start_button_clicked()
{
    get_no_term_symbols();
    get_term_symbols();
    get_rules();
    max_size = ui->spinBox->value();
    symb_null = ui->radioButton_null->isChecked();
    ui->text_output->clear();
}

void MainWindow::on_comboBox_first_symb_activated(const QString &arg1)
{
    first_rule_symb = arg1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


