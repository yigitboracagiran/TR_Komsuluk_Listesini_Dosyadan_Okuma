#include <stdio.h>
#include <stdlib.h>

/* 
Yazar: Yigit Bora Cagiran
Komşuluk Listesini Dosyadan Okuma
Bu algoritmayla .txt uzantili dosyadaki komsuluk listesini, tek yonlu bagli liste seklinde elde ediyoruz.
.txt dosyasında; soldaki harfler ana dugumleri, sag taraflarindakiler ise komsularini ifade etmektedir.
Algoritmadaki yapiyi anlamak icin eklenen resmi incelemeniz rica edilir. 
*/

struct dugum{
    char dugumAdi; //Dugumun adi
    struct dugum *sonrakiDugum; //Komsuluk listesinde, tek yonlu bagli listeyle komsu dugumlerden sonrakininin yerini gosterir.
    int anaDugum; //Komsuluk listesindeki; ana dugumlerden birisiyse -> 1 , komsu dugumlerden birisiyse -> 0 
    struct dugum *sonrakiAnaDugum; //Komsuluk listesinde, tek yonlu bagli listeyle ana dugumlerden sonrakininin yerini gosterir.
};

FILE *dosya;
struct dugum *baslangic=NULL;
struct dugum *dugumGezici=NULL;
struct dugum *anaDugumGezici=NULL;
int kontrol=0;

void komsulukListesiniOlusturma(){ //Dosyadan karakterler okunup, bagli listeye eklenme fonksiyonu...
    char okunanKarakter=fgetc(dosya);
    char birOncekiKarakter='\n'; /*Ilk okunan karakterin ilk ana dugum olmasi ve ondan once okunan karakter olmamasi nedeniyle 
                                  algortimada sorun cikarmamasi icin onceki karakteri /n ile baslattim. */
    while(!feof(dosya)){ //Dosyadaki tum karakterler okunana kadar...
        if(okunanKarakter!='\n'&&okunanKarakter!=' '&&birOncekiKarakter=='\n'){ //Bu sartlar yerine getirilirse ana dugumdur.
            if(kontrol==0){ //Daha once dugum olusturulmadiysa...
                dugumGezici->anaDugum=1; //Ana dugum oldugunu ifade etmektedir.
                dugumGezici->dugumAdi=okunanKarakter; //Ilk eklenen ana dugumu ekleme algoritmasi...
                anaDugumGezici=dugumGezici;
                baslangic=anaDugumGezici;
                kontrol=1;
            }
            else{ //Daha once dugum olusturulduysa...
                anaDugumGezici->sonrakiAnaDugum=(struct dugum*)malloc(sizeof(struct dugum)); //Sonraki ana dugumleri ekleme algoritmasi...
                dugumGezici=anaDugumGezici->sonrakiAnaDugum; 
                dugumGezici->anaDugum=1; //Ana dugum oldugunu ifade etmektedir.
                dugumGezici->dugumAdi=okunanKarakter;
                anaDugumGezici=dugumGezici;
            }
            anaDugumGezici->sonrakiAnaDugum=NULL;
        }
        else if(okunanKarakter!='\n'&&okunanKarakter!=' '&&birOncekiKarakter!='\n'){ //Bu sartlar yerine getirilirse komsu dugumdur.
            dugumGezici->sonrakiDugum=(struct dugum*)malloc(sizeof(struct dugum));  //Komsu dugumleri ekleme algoritmasi...
            dugumGezici=dugumGezici->sonrakiDugum;
            dugumGezici->dugumAdi=okunanKarakter;
            dugumGezici->anaDugum=0; //Komsu dugum oldugunu ifade etmektedir.
            dugumGezici->sonrakiDugum=NULL;
        } 
        birOncekiKarakter=okunanKarakter;
        okunanKarakter=fgetc(dosya);
    }
}

void komsulukListesiniYazdirma(){ //Yapimizi ekrana yazdirma fonksiyonu...
    anaDugumGezici=baslangic;
    dugumGezici=anaDugumGezici;
    while(anaDugumGezici!=NULL){ /*Sirayla komsu dugumleri gezer, bir satirdaki komsu dugum bitince
                                  ise bir sonraki ana dugume gecip gezmeye devam eder.*/
        while(dugumGezici!=NULL){  
            if(dugumGezici->anaDugum==1){ //Ana dugumse...
                printf("%c->", dugumGezici->dugumAdi);
            }
            else{ //Komsu Dugumse...
                printf("%c-", dugumGezici->dugumAdi);
            }
            dugumGezici=dugumGezici->sonrakiDugum; 
        }
        printf("NULL\n");
        anaDugumGezici=anaDugumGezici->sonrakiAnaDugum;
        dugumGezici=anaDugumGezici;
    }
}

int main(){
    dosya=fopen("Komsuluk_Listesi.txt", "r"); //Dosya okumak icin aciliyor.
    if(dosya==NULL){
        printf("Dosya Bos!");
    }
    else{
        printf("Komsuluk Listesi:\n");
        baslangic=(struct dugum*)malloc(sizeof(struct dugum));
        dugumGezici=(struct dugum*)malloc(sizeof(struct dugum));
        anaDugumGezici=(struct dugum*)malloc(sizeof(struct dugum));
        dugumGezici=baslangic;
        anaDugumGezici=baslangic;
        komsulukListesiniOlusturma();
        komsulukListesiniYazdirma();
    }   
    fclose(dosya); //Dosya Kapatiliyor.
    free(baslangic);
    free(dugumGezici);
    free(anaDugumGezici);
    free(anaDugumGezici);
    return 0;
}