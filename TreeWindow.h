#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class TreeWindow : public QDialog
{
public:
    TreeWindow(QString &text, QWidget *parent);

private:
    QTextEdit *_resultat;
    QPushButton *_fermer;
};

#endif // TREEWINDOW_H
