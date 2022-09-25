#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void get_rules();
    void get_term_symbols();
    void get_no_term_symbols();
private:
    QStringList no_term_symbols;
    QStringList term_symbols;
    QString first_rule_symb;
    QStringList line_rules;
    bool symb_null;
    short int max_size;
private slots:
    void first_rule();
    void on_start_button_clicked();
    void on_comboBox_first_symb_activated(const QString &arg1);
};
#endif // MAINWINDOW_H
