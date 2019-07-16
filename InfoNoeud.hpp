#pragma once

enum InfoNoeud
{
    PasInfo, // Grimper dans l'arbre si la precedence du noeud actuel est SUPERIEUR OU EGAL à celui du nouveau noeud
    PasserMontee, // Insertion à droite direct du noeud actuel sans grimper dans l'arbre
    AssociatifDroite // Grimper dans l'arbre si la precedence du noeud actuel est STRICTEMENT SUPERIEUR à celui du nouveau noeud
};