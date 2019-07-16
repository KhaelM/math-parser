#include "TreeWindow.h"

TreeWindow::TreeWindow(QString &text, QWidget *parent = 0) : QDialog(parent)
{
    _resultat = new QTextEdit;
    _resultat->setPlainText(text);
    _resultat->setReadOnly(true);

    _fermer = new QPushButton("Fermer");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_resultat);
    mainLayout->addWidget(_fermer);

    setWindowTitle(QString::fromUtf8("Schéma arbre binaire"));
    setLayout(mainLayout);
    resize(400,400);

    connect(_fermer, SIGNAL(clicked()), this, SLOT(accept()));
}
