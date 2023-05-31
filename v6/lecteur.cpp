#include "lecteur.h"
#include "database.h"

Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

void Lecteur::avancer()
{
    _posImageCourante = (_posImageCourante + 1) % nbImages();
}

void Lecteur::reculer()
{
    _posImageCourante = (_posImageCourante - 1) % nbImages();
}

void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(pNumDiaporama); // charge le diaporama courant
    }
}

void Lecteur::chargerDiaporama(unsigned int pNumDiaporama)
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    DataBase *db;
    db = new DataBase;
    db->openDataBase();

    QSqlQuery query;
    Image* imageACharger;

    QString insertions="SELECT DD.rang, F.nomFamille, D.titrePhoto, D.uriPhoto FROM Diapos D JOIN DiaposDansDiaporama DD ON D.idphoto = DD.idDiapo JOIN Diaporamas Dia ON Dia.idDiaporama = DD.idDiaporama JOIN Familles F ON F.idFamille = D.idFam WHERE Dia.idDiaporama = ?";
    query.prepare(insertions);
    query.addBindValue(pNumDiaporama);

    if (query.exec()) {
               while (query.next()) {
                   //ui->tableWidget->setItem(row,0, new QTableWidgetItem(query.value(1).toString()));
                   imageACharger = new Image(query.value(0).toInt(),
                                             query.value(1).toString().toStdString(),
                                             query.value(2).toString().toStdString(),
                                             ".." + query.value(3).toString().toStdString());
                   _diaporama.push_back(imageACharger);
               }
       } else {
               qDebug() << "Lecteur.cpp" << query.lastError().text();
       }
    db->closeDataBase();
    // tri à bulles pour trier les images
    int n = _diaporama.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (_diaporama[j]->getRang() > _diaporama[j+1]->getRang()) {
                    // Échange de deux pointeurs d'images
                    Image* temp = _diaporama[j];
                    _diaporama[j] = _diaporama[j+1];
                    _diaporama[j+1] = temp;
                }
            }
        }
	 
     _posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void Lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;
}

void Lecteur::afficher()
{
    /* affiche les information sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    if (numDiaporamaCourant() == 0 ) {
        cout << "Diaporama vide" << endl;
    } else {
        if (nbImages() > 0) {
            _diaporama[_posImageCourante]->afficher();
        } else {
            cout << "Diaporama vide";
        }
    }
}

unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

Image *Lecteur::imageCourante()
{
    if (numDiaporamaCourant() == 0 || nbImages() == 0) {
        return nullptr;
    } else {
        return _diaporama[_posImageCourante];
    }
}

unsigned int Lecteur::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}

void Lecteur::setImageCourante(int image)
{
    _posImageCourante = image % nbImages();
}