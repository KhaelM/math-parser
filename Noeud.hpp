#pragma once

#include <cstring>
#include <math.h>
#include <cstdio>
#include <stdexcept>
#include <exception>

#include "IdNoeud.hpp"
#include "InfoNoeud.hpp"

#define MAX_CHAR_FOR_NUMBER 10
#define INDENTATIONS 10

struct Noeud
{
    IdNoeud id;
    unsigned int precedence;
    double nombre;
    Noeud *gauche, *droite, *parent;
};

double factoriel(double n);
void detruire_noeud(Noeud *noeud);
void detruire_arbre(void *arbre);
Noeud *inserer_element_dans_noeud(Noeud *actuel, Noeud element, InfoNoeud info);
void *construire_arbre(const char *expression);
std::string afficher_noeud(const Noeud *noeud, unsigned int indentation);
std::string afficher_arbre(const void *arbre);
double evaluer_noeud(const Noeud *noeud);
double evaluer_arbre(const void *arbre);
