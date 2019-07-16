#include "MainWindow.h"
#include "TreeWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    _expression = new QLineEdit;
    QFormLayout *expressionLayout = new QFormLayout;
    expressionLayout->addRow(QString::fromUtf8("Expression mathématique:"), _expression);

    _resultButton = new QPushButton("Afficher resultat");
    _binaryTreeButton= new QPushButton("Afficher arbre binaire");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(_resultButton);
    buttonLayout->addWidget(_binaryTreeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(expressionLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle(QString::fromUtf8("Michael Randria - Parseur Mathématique"));
    resize(500,100);

    QObject::connect(_resultButton, SIGNAL(clicked(bool)), this, SLOT(displayResult()));
    QObject::connect(_binaryTreeButton, SIGNAL(clicked(bool)), this, SLOT(displayTree()));
}


void MainWindow::displayResult()
{
    void *arbre = NULL;
    double resultat;
    try {
        QString expressionInQt = _expression->text();
        if(expressionInQt.isEmpty()) {
            throw std::runtime_error("Vous devez indiquer une expression pour obtenir un résulat.");
        }
        QByteArray byteArray = expressionInQt.toLocal8Bit();
        const char* expression = byteArray.data();
        arbre = construire_arbre(expression);
        resultat = evaluer_arbre(arbre);
        QMessageBox::information(this, QString::fromUtf8("Résultat"), _expression->text() + " = " + QString::number(resultat));
    } catch(const std::exception &e) {
        QMessageBox::critical(this, QString::fromUtf8("Résultat"), QString::fromUtf8(e.what()));
    }
    detruire_arbre(arbre);
}

void MainWindow::displayTree()
{
    void *arbre = NULL;
    try {
        QString expressionInQt = _expression->text();
        if(expressionInQt.isEmpty()) {
            throw std::runtime_error("Vous devez indiquer une expression pour obtenir un résulat.");
        }
        QByteArray byteArray = expressionInQt.toLocal8Bit();
        const char* expression = byteArray.data();
        arbre = construire_arbre(expression);
        QString text = QString::fromStdString(afficher_arbre(arbre));
        TreeWindow *tree = new TreeWindow(text, this);
        tree->exec();

    } catch(const std::exception &e) {
        QMessageBox::critical(this, QString::fromUtf8("Résultat"), QString::fromUtf8(e.what()));
    }
    detruire_arbre(arbre);
}
