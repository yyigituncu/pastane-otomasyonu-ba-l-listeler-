/* Sami Yiðit Uncu 2212721051
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
        cout << "|************Ana Menü***********|" << endl;
        dashline();
        cout << "|   Yapacaðýnýz iþlemi seçin  |" << endl;
        dashline();
        cout << "|    1 - Ürün Ekleme     |" << endl;
        dashline();
        cout << "|    2 - Stok Listeleme         |" << endl;
        dashline();
        cout << "|    3 - Ürün satýþý      |" << endl;
        dashline();
        cout << "|    4 - Stok Silme             |" << endl;
        dashline();
        cout << "|    5 - Stok Düzenleme         |" << endl;
        dashline();
        cout << "|    6 - Ürün Arama      |" << endl;
        dashline();
        cout << "|    7 - Çýkýþ                  |" << endl;
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
                cout << "Programdan Çýktýnýz!" << endl;
				break;
			}
        }
        if(islemSecme!='7'){
        cout << "Ana menüye dönmek istiyorsanyz (e), Çýkmak istiyorsanýz (h) basýnýz." << endl;
        menu = getche();
		}
    } while (menu == 'e' || menu == 'E');
    

    dosyadanYukle();
    return 0;
}


void arama() {
    char aranan[80];
    cout << "Aranacak Ürün Adýný Giriniz: ";
    cin >> aranan;

    pastane* yedek = head;
    bool bulundu = false;
    while (yedek != NULL) {
        if (strcasecmp(yedek->pastaneAdi, aranan) == 0) {
            cout << "Ürün Adý: " << yedek->pastaneAdi << endl;
            cout << "Ürün Fiyatý: " << yedek->fiyat << endl;
            cout << "Ürün Stoðu: " << yedek->gelenAdet << endl;
            cout << "--------------------------------------" << endl;
            bulundu = true;
            break;
        }
        yedek = yedek->link;
    }

    if (!bulundu) {
        cout << "Arana ürün bulunamadý." << endl;
    }
} 

void stokEkle() {
    char secim;
    int cesit = 0;

    do {
        pastane* yeni = new pastane();
        cout << "Stoða Girilecek Ürün Adýný Giriniz" << endl;
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
        cout << "Stoða Girilecek Ürün Adetini Giriniz" << endl;
        cin >> yeni->gelenAdet;
        cout << "Stoða Girilecek Ürünün Adet Fiyatýný Giriniz" << endl;
        cin >> yeni->fiyat;
        yeni->kalanAdet = yeni->gelenAdet;
        yeni->link = head;
        head = yeni;
        cesit++;
        cout << "Stoða Baþka Kayýt Yapýlacak mý? (e/h)" << endl;
        secim = getche();
        cout << endl;
        dosyayaKaydet();
    }else{cout << "Stokta Zaten Var!" << endl; break;}
	} while (secim == 'e' || secim == 'E');
	if(cesit!=0){
    cout << cesit << " Çeþit Ürün Stoða Girildi.." << endl;}
}


void stokListeleme() {
    pastane* yedek = head;
    int index = 1;

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }

    while (yedek != NULL) {
        cout << index++ << ". Ürün Bilgileri" << endl;
        cout << "Ürün Adý: " << yedek->pastaneAdi << endl;
        cout << "Ürün Fiyatý: " << yedek->fiyat << endl;
        cout << "Ürün'ün Þuanki Stoðu: " << yedek->gelenAdet << endl;
        cout << "--------------------------------------" << endl;
		yedek = yedek->link;
    }
}


void pastaneSatis() {
    char pastaneadi[80];
    cout << "Satýlacak Ürünün Adýný Giriniz" << endl;
    cin >> pastaneadi;

    pastane* yedek = head;
    pastane* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->pastaneAdi, pastaneadi) != 0) {
        once = yedek;
        yedek = yedek->link;
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }

    cout << "Satýlacak Ürün Bilgileri" << endl;
    cout << "Ürün Adý: " << yedek->pastaneAdi << endl;
    cout << "Ürün Fiyatý: " << yedek->fiyat << endl;
    cout << "Ürün Þuanki Stoðu: " << yedek->gelenAdet << endl;
    cout << endl;

    int satis;
    cout << "Kaç Adet Satýlacaðýný Giriniz: ";
    cin >> satis;
    cout << endl;

    int ucret = 0;

    if (satis > yedek->gelenAdet) {
        cout << "Ýstenilen Adetten az stok var. Tüm stok satýldý." << endl;
        ucret = yedek->gelenAdet * yedek->fiyat;
        cout << "Satýþ Tutarý: " << ucret << endl;
        yedek->gelenAdet = 0;
        dosyayaKaydet();
    } else {
        ucret = satis * yedek->fiyat;
        cout << "Satýþ Tutarý: " << ucret << endl;
        yedek->gelenAdet -= satis;
        dosyayaKaydet();
    }

    if (yedek->gelenAdet == 0) {
        cout << "Stok sýfýrlandýðý için ürün silindi." << endl;
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
    cout << "Silinecek Ürün Adýný Giriniz" << endl;
    cin >> pastaneadi;

    pastane* yedek = head;
    pastane* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->pastaneAdi, pastaneadi) != 0) {
        once = yedek;
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }
    cout << "Silinecek Ürün Bilgileri" << endl;
    cout << "Ürün Adý: " << yedek->pastaneAdi << endl;
    cout << "Ürün Fiyatý: " << yedek->fiyat << endl;
    cout << "Ürün Þuanki Stoðu: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "Stoktan Silinecek Ürün bu mu? (e/h)" << endl;
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
        cout << "Stok Silme Ýptal Edildi" << endl;
    }
}


void stokDuzenle() {
    char pastaneadi[80];
    cout << "Düzeltilecek Ürün Adýný Giriniz" << endl;
    cin >> pastaneadi;

    pastane* yedek = head;

    while (yedek != NULL && strcasecmp(yedek->pastaneAdi, pastaneadi) != 0) {
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }

    cout << "Düzeltilecek Ürün Bilgileri" << endl;
    cout << "Ürün Adý: " << yedek->pastaneAdi << endl;
    cout << "Ürün Fiyaty: " << yedek->fiyat << endl;
    cout << "Ürün Þuanki Stoðu: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "Düzeltilecek Ürün Bu mu? (e/h)" << endl;
    secim = getche();
    cout << endl;

    if (secim == 'e' || secim == 'E') {
        cout << "Yeni Ürün Adýný Giriniz" << endl;
        cin >> yedek->pastaneAdi;
        cout << "Ürün Adetini Giriniz" << endl;
        cin >> yedek->gelenAdet;
        cout << "Yeni Ürün'ün 1 Adetinin Fiyatýný Giriniz" << endl;
        cin >> yedek->fiyat;
        yedek->kalanAdet = yedek->gelenAdet;
        cout << "Stok Düzeltildi" << endl;
        dosyayaKaydet();
    } else {
        cout << "Stok Düzeltme Ýptal Edildi" << endl;
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

