#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

#include "Noeud.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void displayResult();
    void displayTree();
private:
    QLineEdit *_expression;
    QPushButton *_resultButton;
    QPushButton *_binaryTreeButton;
};

#endif // MAINWINDOW_H
