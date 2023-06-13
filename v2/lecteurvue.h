#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>

#include "lecteur.h"
#include "apropos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class lecteurvue; }
QT_END_NAMESPACE

// Classe lecteurvue qui représente l'interface utilisateur principale de l'application
class lecteurvue : public QMainWindow
{
    Q_OBJECT

public:
    lecteurvue(QWidget *parent = nullptr);  // Constructeur de la fenêtre principale
    ~lecteurvue();  // Destructeur de la fenêtre principale

// déclaration des slots public pour gérer les événements d'interface utilisateur
public slots:
    void lancer();       // Démarre le diaporama
    void arreter();      // Arrête le diaporama
    void precedent();    // Passe à l'image précédente
    void suivant();      // Passe à l'image suivante
    void modeManuel();   // Configure le lecteur en mode manuel
    void modeAuto();     // Configure le lecteur en mode automatique
    void quitter();      // Ferme l'application
    void charger();      // Charge un nouveau diaporama
    void enlever();      // Enlève le diaporama actuel
    void vitesse();      // Modifie la vitesse de défilement du diaporama
    void aProposDe();    // Ouvre la boîte de dialogue "À propos de"

private:
    Ui::lecteurvue *ui;     // Pointeur vers l'interface utilisateur
    aPropos *aProposDlg;    // Pointeur vers la boîte de dialogue "À propos de"
    Lecteur monLecteur;     // Objet lecteur qui gère le diaporama
};
#endif // LECTEURVUE_H
