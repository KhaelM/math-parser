#include "Noeud.hpp"

double factoriel(double n)
{
    long i, resultat = 1, m = (long)n;
    for (i = 1; i <= m; i++)
        resultat *= i;
    return (double)resultat;
}

void detruire_noeud(Noeud *noeud)
{
    if(noeud == NULL)
        return;
    detruire_noeud(noeud->gauche);
    detruire_noeud(noeud->droite);
    memset(noeud, 0, sizeof(Noeud));
    delete noeud;
}

void detruire_arbre(void *arbre)
{
    detruire_noeud((Noeud *) arbre);
}

Noeud *inserer_element_dans_noeud(Noeud *actuel, Noeud element, InfoNoeud info)
{
    Noeud *noeud;

    /* Etape:4 On remonte l'arbre ou non */
    if(info != PasserMontee)
    {

        if(info != AssociatifDroite) // PasInfo
        {
            // Associatif à gauche
            while (actuel->precedence >= element.precedence)
            {
                actuel = actuel->parent;
            }
        }
        else
        {
            // Associatif à droite
            while (actuel->precedence > element.precedence)
            {
                actuel = actuel->parent;
            }
        }
    }

    /* Etape 5: on crée, ajuste/supprime les noeuds de l'arbre */
    if(element.id == PARENTHESE_FERMANTE)
    {
        // On est sur un noeud de type '('
        noeud = actuel->parent;
        noeud->droite = actuel->droite;
        if(actuel->droite != NULL)
            actuel->droite->parent = noeud;

        // Suppression du '('
        memset(actuel, 0, sizeof(Noeud));
        free(actuel);

        // Etape6 : le noeud parent devient le noeud actuel
        actuel = noeud;
    }
    else
    {
        // Création du noeud
        noeud = new Noeud;
        *noeud = element;
        noeud->droite = NULL;

        // ajoute le noeud
        noeud->gauche = actuel->droite;
        if(actuel->droite != NULL)
        {
            actuel->droite->parent = noeud;
        }
        actuel->droite = noeud;
        noeud->parent = actuel;
        // Etape 6 : le nouveau noeud devient le noeud actuel
        actuel = noeud;
    }

    return actuel;
}

void *construire_arbre(const char *expression)
{
    int i; // Pour vérifier si le caractère actuel est un nombre et si les caractères suivant aussi
    char c; // Pour décomposer l'expression char par char
    char nombre[MAX_CHAR_FOR_NUMBER+1]; // Un nombre contient MAX_CHAR_FOR_NUMBER caractères max
    InfoNoeud infoNoeud;
    IdNoeud idElementPrecedent; // id representant le type de l'élément précedant dans l'expression
    Noeud noeud; // Noeud qu'on va insérer à chaque itération
    Noeud *actuel;
    Noeud racine = {};

    /*  Initialisation de l'arbre avec comme élément racine '(' */
    racine.precedence = 1;
    racine.id = PARENTHESE_OUVRANTE;
    racine.droite = NULL;
    racine.gauche = NULL;

    idElementPrecedent = PARENTHESE_OUVRANTE;
    actuel = &racine;

    /* Parsing de l'expression */
    while (1)
    {
        infoNoeud = PasInfo;
        noeud.precedence = 10; // Précedence le plus élevé correspondant à un nombre

        c = *expression++; // récupère le caractère actuel tout en pointant vers le prochain caractère

        if(c == '\0') // Si on arrive à la fin de l'expression
            break;
        else if(c == ' ' || c == '\t' || c == '\r' || c == '\n') // on se débarasse des espaces superflux
        {
            continue;
        }
        else if( c == '(')
        {
            noeud.id = PARENTHESE_OUVRANTE;
            noeud.precedence = 1;
            infoNoeud = PasserMontee;
        }
        else if(c == ')')
        {
            noeud.id = PARENTHESE_FERMANTE;
            noeud.precedence = 1;
            infoNoeud = AssociatifDroite;
        }
        else if(c == '+')
        {
            if(idElementPrecedent == NOMBRE || idElementPrecedent == FACTORIEL || idElementPrecedent == PARENTHESE_FERMANTE)
            {
                noeud.id = ADDITION;
                noeud.precedence = 2;
            }
            else
            {
                noeud.id = POSITIF;
                noeud.precedence = 3;
                infoNoeud = PasserMontee;
            }
        }
        else if(c == '-')
        {
            if(idElementPrecedent == NOMBRE || idElementPrecedent == FACTORIEL || idElementPrecedent == PARENTHESE_FERMANTE)
            {
                noeud.id = SOUSTRACTION;
                noeud.precedence = 2;
            }
            else
            {
                noeud.id = NEGATIF;
                noeud.precedence = 3;
                infoNoeud = PasserMontee;
            }
        }
        else if(c == '*')
        {
            noeud.id = MULTIPLICATION;
            noeud.precedence = 4;
        }
        else if(c == '/')
        {
            noeud.id = DIVISION;
            noeud.precedence = 4;
        }
        else if(c == '^')
        {
            noeud.id = EXPOSANT;
            noeud.precedence = 5;
            infoNoeud = AssociatifDroite;
        }
        else if(c == '!')
        {
            noeud.id = FACTORIEL;
            noeud.precedence = 6;
        }
        else if(0 == memcmp(expression - 1, "sin", 3)) // on a incrementer le pointeur donc -1
        {
            expression += 2; // Si on a "sin(" le pointeur est sur 'i' et on le place sur '('
            noeud.id = SIN;
        }
        else if (0 == memcmp(expression - 1, "cos", 3))
        {
            expression += 2;
            noeud.id = COS;
        }
        else if (0 == memcmp(expression - 1, "tan", 3))
        {
            expression += 2;
            noeud.id = TAN;
        }
        else if (0 == memcmp(expression - 1, "pi", 2))
        {
            expression += 1; // Pointeur placé sur i, donc on le place sur le prochain caractère
            noeud.nombre = M_PI;
            noeud.id = NOMBRE;
        }
        else if ('0' <= c && c <= '9') // On vérifie si les prochains caractères sont aussi des nombres
        {
            i = 0;
            while (1)
            {
                nombre[i++] = c;
                if(i+1 == sizeof(nombre)) // On garde de la place pour le caractère '\0'
                    break;

                c = *expression; // On regarde le caractère suivant si c'est un caractère
                if (('0' <= c && c <= '9') || c == '.')
                    expression++;
                else
                    break;
            }
            nombre[i] = '\0';
            sscanf(nombre, "%lf", &noeud.nombre);
            noeud.id = NOMBRE;
        }
        else // Caractère non reconnu
        {
            std::string errorMesage = std::string("Caractère ") + c + std::string(" non reconnu");
            throw  std::runtime_error(errorMesage);
        }

        idElementPrecedent = noeud.id;
        actuel = inserer_element_dans_noeud(actuel, noeud, infoNoeud);
    }

    // On supprime la parenthèse ouvrante initialisé
    if(racine.droite != NULL)
        racine.droite->parent = NULL;

    return racine.droite;
}

std::string afficher_noeud(const Noeud *noeud, unsigned int indentation)
{
    unsigned int i;
    char nombre[20];
    const char *str;
    if(noeud == NULL)
        return "";

    switch (noeud->id)
    {
        case NOMBRE:
            if((long) noeud->nombre == noeud->nombre)   // Si c'est un entier
                sprintf(nombre, "%.0f", noeud->nombre);
            else
                sprintf(nombre, "%.2f", noeud->nombre);
            str = nombre;
            break;
        case PARENTHESE_OUVRANTE:
            str = "(";
            break;
        case POSITIF:
            str = "+ve";
            break;
        case NEGATIF:
            str = "-ve";
            break;
        case ADDITION:
            str = "+";
            break;
        case SOUSTRACTION:
            str = "-";
            break;
        case MULTIPLICATION:
            str = "*";
            break;
        case DIVISION:
            str = "/";
            break;
        case EXPOSANT:
            str = "^";
            break;
        case FACTORIEL:
            str = "!";
            break;
        case SIN:
            str = "sin";
            break;
        case COS:
            str = "cos";
            break;
        case TAN:
            str = "tan";
            break;
        default:
            str = "error";
    }

    std::string result = "";
    for(i = 0; i < indentation; i++) {
        result += " ";
    }
    result += str + std::string("\n");

    return afficher_noeud(noeud->droite, indentation + INDENTATIONS) + result + afficher_noeud(noeud->gauche, indentation + INDENTATIONS);
}

std::string afficher_arbre(const void *arbre)
{
    return afficher_noeud((const Noeud *)arbre, INDENTATIONS);
}

double evaluer_noeud(const Noeud *noeud)
{
    double gauche, droite;
    if(noeud == NULL)
        return 0;

    gauche = evaluer_noeud(noeud->gauche);
    droite = evaluer_noeud(noeud->droite);

    switch (noeud->id)
    {
    case POSITIF:
        return +droite;
    case NEGATIF:
        return -droite;
    case ADDITION:
        return gauche + droite;
    case SOUSTRACTION:
        return gauche - droite;
    case MULTIPLICATION:
        return gauche * droite;
    case DIVISION:
        return gauche / droite;
    case EXPOSANT:
        return pow(gauche, droite);
    case FACTORIEL:
        return factoriel(gauche);
    case SIN:
        return sin(droite);
    case COS:
        return cos(droite);
    case TAN:
        return tan(droite);
    default:
        return noeud->nombre;
    }
}


double evaluer_arbre(const void *arbre)
{
    return evaluer_noeud((const Noeud *)arbre);
}
