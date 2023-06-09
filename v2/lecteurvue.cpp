#include "lecteurvue.h"
#include "apropos.h"
#include "ui_lecteurvue.h"

#include <QPixmap>
#include <QDebug>

lecteurvue::lecteurvue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lecteurvue)
{
    monLecteur.changerDiaporama(1);
    ui->setupUi(this);
    QString lien = QString::fromStdString(monLecteur.imageCourante()->getChemin()); // transformation d'un string en QString
    QPixmap image(lien);
    ui->lbImage->setPixmap(image); // ajout de l'image au label
    ui->statusbar->showMessage(lien); // affichage du chemin dans la statusbar

    // connexion des boutons avec les slots appropriés
    connect(ui->bLancer, SIGNAL(clicked()), this, SLOT(lancer()));
    connect(ui->bArreter, SIGNAL(clicked()), this, SLOT(arreter()));
    connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
    connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(suivant()));
    connect(ui->bManuel, SIGNAL(clicked()), this, SLOT(modeManuel()));
    connect(ui->bAuto, SIGNAL(clicked()), this, SLOT(modeAuto()));

    // connexion des items avec les slots appropriés
    connect(ui->actionQuitter, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()));
    connect(ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(charger()));
    connect(ui->actionEnlever_diaporama, SIGNAL(triggered()), this, SLOT(enlever()));
    connect(ui->actionVitesse_de_defilement, SIGNAL(triggered()), this, SLOT(vitesse()));
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(aProposDe()));
}

lecteurvue::~lecteurvue()
{
    delete ui;
}

// définition du slot pour démarrer la diapositive
void lecteurvue::lancer() {
    qDebug() << "lancer";    
}

// définition du slot pour arrêter la diapositive
void lecteurvue::arreter() {
    qDebug() << "arreter";
}

// définition du slot pour revenir à la diapositive précédente
void lecteurvue::precedent() {
    qDebug() << "precedent";
    monLecteur.reculer();
    QString lien = QString::fromStdString(monLecteur.imageCourante()->getChemin()); // transformation d'un string en QString
    QPixmap image(lien);
    ui->lbImage->setPixmap(image); // ajout de l'image au label
    ui->statusbar->showMessage(lien); // affichage du chemin dans la statusbar
}

// définition du slot pour passer à la diapositive suivante
void lecteurvue::suivant() {
    qDebug() << "suivant";
    monLecteur.avancer();
    QString lien = QString::fromStdString(monLecteur.imageCourante()->getChemin()); // transformation d'un string en QString
    QPixmap image(lien); // création d'une QPixmap à partir du lien de l'image
    ui->lbImage->setPixmap(image); // ajout de l'image au label
    ui->statusbar->showMessage(lien); // affichage du chemin dans la statusbar
}

// définition du slot pour activer le mode manuel
void lecteurvue::modeManuel() {
    qDebug() << "mode manuel";
}

// définition du slot pour activer le mode automatique
void lecteurvue::modeAuto() {
    qDebug() << "mode automatique";
}

// définition du slot pour démarrer la diapositive
void lecteurvue::quitter() {
    qDebug() << "quitter";
}

// définition du slot pour charger la diapositive
void lecteurvue::charger() {
    qDebug() << "charger";
}

// définition du slot pour enlever la diapositive
void lecteurvue::enlever() {
    qDebug() << "enlever";
}

// définition du slot pour changer la vitesse
void lecteurvue::vitesse() {
    qDebug() << "vitesse";
}

// définition du slot pour afficher le dialog a propos de...
void lecteurvue::aProposDe() {
    qDebug() << "a propos de";
    aPropos aProposDlg(this);
    aProposDlg.exec();
}

