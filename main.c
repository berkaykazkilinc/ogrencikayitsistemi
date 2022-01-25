#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define BINARY_DOSYA "veri.dat"
#define TEXT_DOSYA "index.txt"

// YASAR BERKAY KAZKILINC

struct kayit
{
    int ogrNo;
    int dersKodu;
    int puan;
};

void menuListele();
void secimUygula(int secim);
void txtToBin(int searchNo);
void txtToBin2();
void kayitEkle();
void indeksDosyasiniGoster();
void indeksDosyasiniSil();
void binDosyaOlustur();
void kayitSilme();
void kayitGuncelleText();
void kayitBul();
void CopyBin2Text();
int binarySearch(struct kayit dizi[], int low,int high, int aranan);
void kayitGuncelleBinary(int numara, int ders_kodu, struct kayit guncellenen_kisi);

int main()
{
    int secim = -1;
    while(secim != 0)
    {
        menuListele();
        scanf("%d", &secim);
        secimUygula(secim);
    }

    return 0;
}

void menuListele()
{

    printf("\n| 1: Bin Dosyasi Olustur\n");
    printf("| 2: Index Dosyasi Olustur\n");
    printf("| 3: Kayit Ekle\n");
    printf("| 4: Binary Dosyasini Text Dosyasina Aktar\n");
    printf("| 5: Binary Verilerini Goster\n");
    printf("| 6: Text Dosyasi Verilerini Goster\n");
    printf("| 7: Kayit Bul\n");
    printf("| 8: Kayit Guncelle\n");
    printf("| 9: Kayit Sil\n");
    printf("|10: Indeks Dosyasini Sil\n");
    printf("| 0: Cikis\n");
    printf("-------------------------\n");
    printf("| Secim?: ");
}

void secimUygula(int secim)
{
    switch (secim)
    {
    case 0:
        exit(1);
        break;
    case 1:
        binDosyaOlustur();
        break;
    case 2:
    {
        indexDosyasiOlustur();
        break;

    }
    case 3:
    {
        struct kayit ogr;
        printf("no - ders kodu - puan: (Bir degeri girdikten sonra enter tusuna basiniz)\n");
        scanf("%d  %d  %d",&ogr.ogrNo,&ogr.dersKodu,&ogr.puan);
        kayitEkle(ogr);
        break;
    }
    case 4:
    {
        CopyBin2Text();
        break;

        case 5:
        {
            veriDosyasiniGoster();
            break;

        }
        case 6:
        {
            indeksDosyasiniGoster();
            break;

        }
        case 7:
        {
            kayitBul();
            break;

        }
    }
    case 8:
    {
        kayitGuncelleText();
        break;
    }
    case 9:
    {
        kayitSilme();
        break;

    }
    case 10:
    {
        indeksDosyasiniSil();
        break;
    }
    default:
        printf("yanlis secim\n");
    }
}

void kayitEkle(struct kayit ogr)
{
    FILE *dosya;

    if((dosya=fopen(BINARY_DOSYA,"a"))== NULL)
    {
        printf("dosya acilamadi");
        exit(1);
    }
    fwrite(&ogr,sizeof(struct kayit),1,dosya);
    fclose(dosya);
}

void veriDosyasiniGoster()
{
    FILE *dosya;
    if((dosya=fopen(BINARY_DOSYA,"r"))== NULL)
    {
        printf("dosya acilamadi");
        exit(1);
    }

    printf("\nListe\n");
    printf("Ogrenci No----Ders Kodu-----Puan\n");
    struct kayit ogrenci;
    size_t sayi = fread(&ogrenci,sizeof(struct kayit),1,dosya);
    while(sayi > 0)
    {
         if(ogrenci.ogrNo>9)
        {
            printf("%d             %d           %d\n",ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
        else{
            printf("%d              %d           %d\n",ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
        sayi = fread(&ogrenci,sizeof(struct kayit),1,dosya);
    }

    fclose(dosya);
}

void indeksDosyasiniGoster()
{
    FILE *dosya;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("dosya acilamadi");
        exit(1);
    }
    printf("\nListe\n");
    printf("Ogrenci No----Ders Kodu-----Puan\n");
    while(!feof(dosya))
    {
        struct kayit ogrenci;
        fscanf(dosya,"%d %d %d\n",&ogrenci.ogrNo,&ogrenci.dersKodu,&ogrenci.puan);
        if(ogrenci.ogrNo>9)
        {
            printf("%d             %d           %d\n",ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
        else{
            printf("%d              %d           %d\n",ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
    }

    fclose(dosya);
}

void indeksDosyasiniSil()
{
    remove(TEXT_DOSYA);
}

void binDosyaOlustur()
{
    FILE * dosya;
    if ((dosya = fopen(BINARY_DOSYA, "wb+")) == NULL)
    {
        printf("Dosya Acilamadi!\n");
        exit(1);
    }
    else
    {
        printf("Dosya Olusturuldu!\n");
    }

    fclose(dosya);
}

void indexDosyasiOlustur()
{
    FILE * dosya;
    if ((dosya = fopen(TEXT_DOSYA, "wb+")) == NULL)
    {
        printf("Dosya Acilamadi!\n");
        exit(1);
    }
    else
    {
        printf("Dosya Olusturuldu!\n");
    }

    fclose(dosya);
}

void kayitBul()
{
    FILE *fraf;
    int low=0, gecicino;
    struct kayit p, temp;
    int i,size;

    if ((fraf = fopen(BINARY_DOSYA,"rb")) == NULL)
    {
        return 0;
    }

    fseek(fraf, 0,SEEK_END );
    size = ftell(fraf);
    size /= sizeof(struct kayit);
    fseek(fraf, 0, SEEK_SET);

    struct kayit A[size];

    for(i=0; i < size; i++)
    {
        fread(&A[i],sizeof(A),1,fraf);
    }

    int x,y;
    for (x = 0 ; x < ( size- 1 ); x++)
    {
        for (y = 0 ; y < size - x - 1; y++)
        {
            if (A[y].ogrNo > A[y+1].ogrNo)
            {
                temp = A[y];
                A[y] = A[y+1];
                A[y+1] = temp;
            }
        }
    }

    printf("Aramak istedigin no: ");
    scanf("%d",&gecicino);
    binarySearch(A,low,(size-1),gecicino);

    fclose(fraf);
}

int binarySearch(struct kayit dizi[],int low,int high ,int gecicino)
{

    low = 0;
    int mid = 0;
    int i;


    while(low<=high)
    {
        mid=(low+high)/2;
        if(dizi[mid].ogrNo == gecicino)
        {

            for(i = 0; i < high+1; i++)
            {

            if(dizi[i].ogrNo == gecicino){
                printf("%d %d %d",dizi[i].ogrNo,dizi[i].dersKodu,dizi[i].puan);
                printf("\n");
                }
            }
            return 1;

        }
        if(dizi[mid].ogrNo > gecicino)
        {

            high=mid-1;
        }
        else
        {

            low=mid+1;
        }

    }
    return -1;
}

void CopyBin2Text()
{
    FILE *fraf, *ftxt;
    int n;

    struct kayit p,t;
    int i,j;

    if ((fraf = fopen(BINARY_DOSYA,"rb")) == NULL)
        return 0;

    fseek(fraf, 0, SEEK_END);
    n = ftell(fraf);
    n = n / sizeof(struct kayit);
    fseek(fraf, 0, SEEK_SET);

    if ((ftxt = fopen(TEXT_DOSYA,"wt")) == NULL)
    {
        fclose(fraf);
        return 0;
    }

    struct kayit A[n];
    for(i=0; i<n; i++)
    {
        fread(&A[i],sizeof(A),1,fraf);
    }

    int x,y;
    for (x = 0 ; x < ( n- 1 ); x++)
    {
        for (y = 0 ; y < n - x - 1; y++)
        {
            if (A[y].ogrNo > A[y+1].ogrNo)
            {
                t = A[y];
                A[y] = A[y+1];
                A[y+1] = t;
            }
        }
    }

    for(i=0; i<n; i++)
    {
        fprintf(ftxt, "%d %d %d \n", A[i].ogrNo, A[i].dersKodu, A[i].puan);
    }

    fclose(ftxt);
    fclose(fraf);
}

void kayitSilme()
{
    FILE *dosya, *yedek;
    int numara, durum=0;
    struct kayit kisi;

    printf("\n-----Kayit Listesi-----\n");
    veriDosyasiniGoster();
    printf("\n");
    printf("\nSilinecek ogrencinin numarasini giriniz : ");
    scanf("%d",&numara);
    dosya = fopen(TEXT_DOSYA,"r");
    yedek = fopen("yedek.txt","w");

    if(dosya == NULL)
    {
        puts("Dosya acilamadi");
        exit(1);
    }
    while(!feof(dosya))
    {
        fscanf(dosya,"%d %d %d\n",&kisi.ogrNo,&kisi.dersKodu,&kisi.puan);
        if(numara != kisi.ogrNo)
        {
            fprintf(yedek,"%d %d %d\n",kisi.ogrNo,kisi.dersKodu,kisi.puan);

        }
        else durum=1;
    }

    fclose(dosya);
    fclose(yedek);

    if(durum == 1)
    {
        remove(TEXT_DOSYA);
        rename("yedek.txt",TEXT_DOSYA);
        puts("Silme islemi tamamlandi devam etmek icin bir tusa basin");
    }
    else
    {
        remove("yedek.txt");
        printf(" %d numarasinda bir ogrenci bulunamadi devam etmek icin bir tusa basin ...",numara);
    }

    getch();
    txtToBin(numara);
}

void txtToBin(int searchNo)
{
    FILE *fp;
    FILE *fp_tmp;
    int found=0;
    struct kayit birazuzun;

    fp=fopen(BINARY_DOSYA, "rb");
    if (!fp)
    {
        printf("Dosya Acilamadi %d", BINARY_DOSYA);
        return -1;
    }
    fp_tmp=fopen("tmp.bin", "wb");
    if (!fp_tmp)
    {
        printf("Dosya Acilamadi");
        return -1;
    }

    while (fread(&birazuzun,sizeof(struct kayit),1,fp) != NULL)
    {
        if (searchNo == birazuzun.ogrNo )
        {
            found=1;
        }
        else
        {
            fwrite(&birazuzun, sizeof(struct kayit), 1, fp_tmp);
        }
    }
    if (! found)
    {
        printf("No record(s) found with the requested name: %d\n\n", searchNo);
    }

    fclose(fp);
    fclose(fp_tmp);

    remove(BINARY_DOSYA);
    rename("tmp.bin", BINARY_DOSYA);
    printf("\n------Yeni Liste-------\n");
    veriDosyasiniGoster();

    return 0;
}

void txtToBin2()
{
    FILE *fp;
    FILE *fp_tmp;

    struct kayit birazuzun;

    fp=fopen(TEXT_DOSYA, "r");
    if (!fp)
    {
        printf("Dosya Acilamadi %d", TEXT_DOSYA);
        return -1;
    }

    fp_tmp=fopen("tmp.bin", "wb");

    if (!fp_tmp)
    {
        printf("Dosya Acilamadi");
        return -1;
    }

    while (fscanf(fp,"%d %d %d\n",&birazuzun.ogrNo,&birazuzun.dersKodu,&birazuzun.puan) != NULL)
    {

        fwrite(&birazuzun, sizeof(struct kayit), 1, fp_tmp);
    }


    fclose(fp);
    fclose(fp_tmp);

    remove(BINARY_DOSYA);
    rename("tmp.bin", BINARY_DOSYA);
    printf("\n------Yesni Liste-------\n");
    veriDosyasiniGoster();

    return 0;
}


void kayitGuncelleText()
{
    FILE *dosya ,*yedek;
    int numara, ders_kodu,durum=0;
    printf("\nBilgilerini degistireceginiz ogrencinin numarasini giriniz: ");
    scanf("%d",&numara);
    printf("\nBilgilerini degistireceginiz ogrencinin ders kodunu giriniz: ");
    scanf("%d",&ders_kodu);
    dosya = fopen(TEXT_DOSYA,"r");
    yedek = fopen("yedek.txt","w");
    struct kayit kisi;
    if(dosya == NULL)
    {
        printf("Dosya acilamadi");
        exit(1);
    }
    while(!feof(dosya))
    {
        fscanf(dosya,"%d %d %d\n",&kisi.ogrNo,&kisi.dersKodu,&kisi.puan);
        if(numara != kisi.ogrNo || ders_kodu != kisi.dersKodu)
        {
            fprintf(yedek,"%d %d %d\n",kisi.ogrNo,kisi.dersKodu,kisi.puan);

        }
        else
        {
            fflush(stdin);
            printf("Yeni Ogrencinin Notu : ");
            scanf("%d",&kisi.puan);
            printf("\n");
            fprintf(yedek,"%d %d %d\n",kisi.ogrNo,kisi.dersKodu,kisi.puan);
            kayitGuncelleBinary(numara, ders_kodu, kisi);
            durum=1;
        }
    }
    fclose(dosya);
    fclose(yedek);
    if(durum == 1)
    {
        remove(TEXT_DOSYA);
        rename("yedek.txt",TEXT_DOSYA);
        printf("Ogrenci bilgileri text dosyasinda degistirildi devam etmek icin bir tusa basin...");
    }
    else
    {
        remove("yedek.txt");
        printf("Ilgili ogrenci text dosyasinda bulunamadi devam etmek icin bir tusa basin...");
    }
    fflush(stdin);
    getch();

}

void kayitGuncelleBinary(int numara, int ders_kodu, struct kayit guncellenen_kisi)
{
    FILE *dosya ,*yedek;
    int durum=0;

    dosya = fopen(BINARY_DOSYA,"rb");
    yedek = fopen("temp.dat","wb");
    struct kayit kisi;
    if(dosya == NULL)
    {
        printf("Dosya acilamadi");
        exit(1);
    }

    size_t endOfFile = fread(&kisi,sizeof(struct kayit),1,dosya);
    while(endOfFile > 0)
    {

        if(numara != kisi.ogrNo || ders_kodu != kisi.dersKodu)
        {
            fwrite(&kisi,sizeof(struct kayit),1,yedek);

        }
        else
        {
            fwrite(&guncellenen_kisi,sizeof(struct kayit),1,yedek);
            durum=1;
        }
        endOfFile = fread(&kisi,sizeof(struct kayit),1,dosya);
    }
    fclose(dosya);
    fclose(yedek);
    if(durum == 1)
    {
        remove(BINARY_DOSYA);
        rename("temp.dat",BINARY_DOSYA);
        printf("Ogrenci bilgileri binary dosyada degistirildi devam etmek icin bir tusa basin...\n");
    }
    else
    {
        remove("temp.dat");
        printf("Ilgili ogrenci binary dosyada bulunamadi devam etmek icin bir tusa basin...\n");
    }
    fflush(stdin);
    getch();
}
