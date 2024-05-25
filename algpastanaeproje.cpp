/* Sami Yi�it Uncu 2212721051
Pastane otomasyonu
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct pastane {
    char pastaneAdi[80];
    int gelenAdet;
    int kalanAdet;
    int fiyat;
    pastane* link;
};

pastane* head = NULL;

void arama();
void stokEkle();
void stokListeleme();
void pastaneSatis();
void stokSilme();
void stokDuzenle();
void dashline();
void dosyadanYukle();
void dosyayaKaydet();

int main() {
    setlocale(LC_ALL, "Turkish");
    char menu;
    dosyadanYukle();
    do {
        system("cls");
        cout << "|************Ana Men�***********|" << endl;
        dashline();
        cout << "|   Yapaca��n�z i�lemi se�in  |" << endl;
        dashline();
        cout << "|    1 - �r�n Ekleme     |" << endl;
        dashline();
        cout << "|    2 - Stok Listeleme         |" << endl;
        dashline();
        cout << "|    3 - �r�n sat���      |" << endl;
        dashline();
        cout << "|    4 - Stok Silme             |" << endl;
        dashline();
        cout << "|    5 - Stok D�zenleme         |" << endl;
        dashline();
        cout << "|    6 - �r�n Arama      |" << endl;
        dashline();
        cout << "|    7 - ��k��                  |" << endl;
        cout << "|_______________________________|" << endl;
        char islemSecme;
		islemSecme = getche();
        
        switch (islemSecme) {
            case '1': {
                system("cls");
                stokListeleme();
				stokEkle();
                break;
            }
            case '2': {
            	system("cls");
                stokListeleme();
                break;
            }
            case '3': {
            	system("cls");
            	stokListeleme();
                pastaneSatis();
                break;
            }
            case '4': {
            	system("cls");
            	stokListeleme();
                stokSilme();
                break;
            }
            case '5': {
            	system("cls");
            	stokListeleme();
                stokDuzenle();
                break;
            }
            case '6':{
            	system("cls");
            	arama();
				break;
			}
            case '7':{
            	system("cls");
            	menu = 'h';
                cout << "Programdan ��kt�n�z!" << endl;
				break;
			}
        }
        if(islemSecme!='7'){
        cout << "Ana men�ye d�nmek istiyorsanyz (e), ��kmak istiyorsan�z (h) bas�n�z." << endl;
        menu = getche();
		}
    } while (menu == 'e' || menu == 'E');
    

    dosyadanYukle();
    return 0;
}


void arama() {
    char aranan[80];
    cout << "Aranacak �r�n Ad�n� Giriniz: ";
    cin >> aranan;

    pastane* yedek = head;
    bool bulundu = false;
    while (yedek != NULL) {
        if (strcasecmp(yedek->pastaneAdi, aranan) == 0) {
            cout << "�r�n Ad�: " << yedek->pastaneAdi << endl;
            cout << "�r�n Fiyat�: " << yedek->fiyat << endl;
            cout << "�r�n Sto�u: " << yedek->gelenAdet << endl;
            cout << "--------------------------------------" << endl;
            bulundu = true;
            break;
        }
        yedek = yedek->link;
    }

    if (!bulundu) {
        cout << "Arana �r�n bulunamad�." << endl;
    }
} 

void stokEkle() {
    char secim;
    int cesit = 0;

    do {
        pastane* yeni = new pastane();
        cout << "Sto�a Girilecek �r�n Ad�n� Giriniz" << endl;
        cin >> yeni->pastaneAdi;
        pastane* yedek = head;
        bool bulundu = false;
        while (yedek != NULL) {
        if (strcasecmp(yedek->pastaneAdi, yeni->pastaneAdi) == 0) {
            bulundu = true;
            break;
        }
        yedek = yedek->link;
    }
    if(bulundu == false){
        cout << "Sto�a Girilecek �r�n Adetini Giriniz" << endl;
        cin >> yeni->gelenAdet;
        cout << "Sto�a Girilecek �r�n�n Adet Fiyat�n� Giriniz" << endl;
        cin >> yeni->fiyat;
        yeni->kalanAdet = yeni->gelenAdet;
        yeni->link = head;
        head = yeni;
        cesit++;
        cout << "Sto�a Ba�ka Kay�t Yap�lacak m�? (e/h)" << endl;
        secim = getche();
        cout << endl;
        dosyayaKaydet();
    }else{cout << "Stokta Zaten Var!" << endl; break;}
	} while (secim == 'e' || secim == 'E');
	if(cesit!=0){
    cout << cesit << " �e�it �r�n Sto�a Girildi.." << endl;}
}


void stokListeleme() {
    pastane* yedek = head;
    int index = 1;

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }

    while (yedek != NULL) {
        cout << index++ << ". �r�n Bilgileri" << endl;
        cout << "�r�n Ad�: " << yedek->pastaneAdi << endl;
        cout << "�r�n Fiyat�: " << yedek->fiyat << endl;
        cout << "�r�n'�n �uanki Sto�u: " << yedek->gelenAdet << endl;
        cout << "--------------------------------------" << endl;
		yedek = yedek->link;
    }
}


void pastaneSatis() {
    char pastaneadi[80];
    cout << "Sat�lacak �r�n�n Ad�n� Giriniz" << endl;
    cin >> pastaneadi;

    pastane* yedek = head;
    pastane* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->pastaneAdi, pastaneadi) != 0) {
        once = yedek;
        yedek = yedek->link;
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }

    cout << "Sat�lacak �r�n Bilgileri" << endl;
    cout << "�r�n Ad�: " << yedek->pastaneAdi << endl;
    cout << "�r�n Fiyat�: " << yedek->fiyat << endl;
    cout << "�r�n �uanki Sto�u: " << yedek->gelenAdet << endl;
    cout << endl;

    int satis;
    cout << "Ka� Adet Sat�laca��n� Giriniz: ";
    cin >> satis;
    cout << endl;

    int ucret = 0;

    if (satis > yedek->gelenAdet) {
        cout << "�stenilen Adetten az stok var. T�m stok sat�ld�." << endl;
        ucret = yedek->gelenAdet * yedek->fiyat;
        cout << "Sat�� Tutar�: " << ucret << endl;
        yedek->gelenAdet = 0;
        dosyayaKaydet();
    } else {
        ucret = satis * yedek->fiyat;
        cout << "Sat�� Tutar�: " << ucret << endl;
        yedek->gelenAdet -= satis;
        dosyayaKaydet();
    }

    if (yedek->gelenAdet == 0) {
        cout << "Stok s�f�rland��� i�in �r�n silindi." << endl;
        if (once == NULL) {
            head = yedek->link;
        } else {
            once->link = yedek->link;
        }
        delete yedek;
    }
}

void stokSilme() {
    char pastaneadi[80];
    cout << "Silinecek �r�n Ad�n� Giriniz" << endl;
    cin >> pastaneadi;

    pastane* yedek = head;
    pastane* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->pastaneAdi, pastaneadi) != 0) {
        once = yedek;
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }
    cout << "Silinecek �r�n Bilgileri" << endl;
    cout << "�r�n Ad�: " << yedek->pastaneAdi << endl;
    cout << "�r�n Fiyat�: " << yedek->fiyat << endl;
    cout << "�r�n �uanki Sto�u: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "Stoktan Silinecek �r�n bu mu? (e/h)" << endl;
    secim = getche();
    cout << endl;

    if (secim == 'e' || secim == 'E') {
        if (once == NULL) {
            head = yedek->link;
        } else {
            once->link = yedek->link;
        }
        delete yedek;
        cout << "Stok Silindi" << endl;
        dosyayaKaydet();
    } else {
        cout << "Stok Silme �ptal Edildi" << endl;
    }
}


void stokDuzenle() {
    char pastaneadi[80];
    cout << "D�zeltilecek �r�n Ad�n� Giriniz" << endl;
    cin >> pastaneadi;

    pastane* yedek = head;

    while (yedek != NULL && strcasecmp(yedek->pastaneAdi, pastaneadi) != 0) {
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }

    cout << "D�zeltilecek �r�n Bilgileri" << endl;
    cout << "�r�n Ad�: " << yedek->pastaneAdi << endl;
    cout << "�r�n Fiyaty: " << yedek->fiyat << endl;
    cout << "�r�n �uanki Sto�u: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "D�zeltilecek �r�n Bu mu? (e/h)" << endl;
    secim = getche();
    cout << endl;

    if (secim == 'e' || secim == 'E') {
        cout << "Yeni �r�n Ad�n� Giriniz" << endl;
        cin >> yedek->pastaneAdi;
        cout << "�r�n Adetini Giriniz" << endl;
        cin >> yedek->gelenAdet;
        cout << "Yeni �r�n'�n 1 Adetinin Fiyat�n� Giriniz" << endl;
        cin >> yedek->fiyat;
        yedek->kalanAdet = yedek->gelenAdet;
        cout << "Stok D�zeltildi" << endl;
        dosyayaKaydet();
    } else {
        cout << "Stok D�zeltme �ptal Edildi" << endl;
    }
}

void dashline() {
    cout << "|-------------------------------|" << endl;
}

void dosyadanYukle() {
    ifstream file("stok.dat", ios::binary);
    if (!file.is_open()) return;

    while (true) {
        pastane* yeni = new pastane();
        file.read((char*)yeni, sizeof(pastane));
        if (file.eof()) {
            delete yeni;
            break;
        }
        yeni->link = head;
        head = yeni;
    }
    file.close();
}

void dosyayaKaydet() {
    ofstream file("stok.dat", ios::binary | ios::trunc);
    pastane* yedek = head;
    while (yedek != NULL) {
        file.write((char*)yedek, sizeof(pastane));
        yedek = yedek->link;
    }
    file.close();
}

