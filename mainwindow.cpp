#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setFixedSize(this->size());
    connect(ui->line_no_term, SIGNAL(editingFinished()), SLOT(first_rule_slot()));
    connect(ui->action_sample, SIGNAL(triggered()), SLOT(sample_slot()));
    connect(ui->action_input, SIGNAL(triggered()), SLOT(input_slot()));
}
void MainWindow::get_rules()
{
    rules_map.clear();
    QStringList line_rules;
    if(!ui->text_rules->toPlainText().isEmpty()){
        line_rules = ui->text_rules->toPlainText().split("\n");
        QStringList one_line_rule;
        QStringList rules;
        for(int i = 0; i < line_rules.size(); i++){
            one_line_rule = line_rules[i].split("->");
            rules = one_line_rule[1].split("|");
            //qDebug() <<rules;
            for(int j = 0; j < rules.size(); j++){
                rules_map.insert(one_line_rule[0],rules[j]);
            }
        }
    }
    //qDebug()<<rules_map;
}

void MainWindow::get_term_symbols()
{
    term_symbols = ui->line_term->text().split(",");
}

void MainWindow::get_no_term_symbols()
{
    no_term_symbols = ui->line_no_term->text().split(",");
}
void MainWindow::clear_data()
{
    ui->line_no_term->clear();
    ui->line_term->clear();
    ui->text_output->clear();
    ui->text_rules->clear();
    // ui->comboBox_first_symb->clear();
}
void MainWindow::lock_input(bool flag)
{
    ui->line_no_term->setReadOnly(flag);
    ui->line_term->setReadOnly(flag);
    ui->text_output->setReadOnly(flag);
    ui->text_rules->setReadOnly(flag);
    //ui->comboBox_first_symb->setEnabled(!flag);
    ui->radioButton_null->setEnabled(!flag);
    ui->spinBox->setEnabled(!flag);

}
void MainWindow::first_rule_slot()
{
    QStringList no_term_loc;
    ui->comboBox_first_symb->clear();
    no_term_loc = ui->line_no_term->text().split(",");
    for(int i = 0; i < no_term_loc.size(); i++){
        ui->comboBox_first_symb->addItem(no_term_loc[i]);
    }
}

void MainWindow::sample_slot()
{
    clear_data();
    lock_input(true);
    ui->line_no_term->setText("A,B,C");
    ui->text_rules->setText("A->aBC|BaC\nB->dC|f\nC->aA|B");
    ui->spinBox->setValue(6);
}
void MainWindow::input_slot()
{
    clear_data();
    lock_input(false);
}
void MainWindow::on_start_button_clicked()
{
    get_no_term_symbols();
    get_term_symbols();
    get_rules();
    max_size = ui->spinBox->value();
    symb_null = ui->radioButton_null->isChecked();
    ui->text_output->clear();
    generation_chains();
}
//void on-<object name>-<signal name>(<signal parameters>);

void MainWindow::on_comboBox_first_symb_activated(const QString &arg1)
{
    first_rule_symb = arg1;
}
void MainWindow::generation_chains()
{
    QStringList chains = rules_map.values(first_rule_symb);
    QStringList chains_next_step;
    QStringList answer;
    QString chain;
    QStringList rule_variants;
    bool flag_no_term = false;
    short int size_chain_term = 0;
    qDebug() << chains;
    for(; chains.size() > 0;){
        flag_no_term = false;
        size_chain_term = 0;
        for(int num_word_chain = 0; num_word_chain < chains[0].size(); num_word_chain++){
            if(!rules_map.uniqueKeys().contains((QString)chains[0][num_word_chain])){
                size_chain_term++;
            }else{
                flag_no_term = true;
            }
        }
        qDebug()<<flag_no_term;
        if(size_chain_term < max_size && flag_no_term){
            for(int num_word_chain = chains[0].size()-1; num_word_chain >= 0; num_word_chain--){
                if(rules_map.uniqueKeys().contains((QString)chains[0][num_word_chain])){

                    rule_variants = rules_map.values((QString)chains[0][num_word_chain]);
                    qDebug()<< "VAriant" <<rule_variants<< " SYMB "<< chains[0][num_word_chain];
                    qDebug() << chains[0];
                    for (int i = 0; i < rule_variants.size(); i++){
                        chain = chains[0].left(num_word_chain);
                        chain +=  rule_variants[i];
                        chain += chains[0].right(chains[0].size()-num_word_chain-1);
                        chains_next_step.push_back(chain);

                    }
                    qDebug() << chains_next_step;
                    break;
                }
            }
        }else if (!flag_no_term){
            answer.push_back(chains[0]);
        }
        chains.removeFirst();
        if(chains.size() == 0){
            chains = chains_next_step;
            chains_next_step.clear();
        }
    }
    qDebug() <<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<< answer;
}
MainWindow::~MainWindow()
{
    delete ui;
}


