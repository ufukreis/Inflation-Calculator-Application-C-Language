#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URUN_SAYISI 20

struct Urun
{
    char Adi[30];
    char Birimi[10];
    char Marka[20];
    char Alan[20];
    double Fiyat2010;
    double Fiyat2020;
    double Fiyat2022;
    double OnYillikFiyatDegisimi;
    double OnIkiYillikFiyatDegisimi;
    int AsgariUcretIleKacAdet2010;
    int AsgariUcretIleKacAdet2020;
    int AsgariUcretIleKacAdet2022;
    double AlimGucuDegisimi10;
    double AlimGucuDegisimi12;
};

double onYillikFiyatDegisimiHesapla(struct Urun urun)
{
    double fiyatDegisimi = (((100.0 * urun.Fiyat2020) / urun.Fiyat2010) - 100.0);
    return fiyatDegisimi;
}

double onIkiYillikFiyatDegisimiHesapla(struct Urun urun)
{
    double fiyatDegisimi = (((100.0 * urun.Fiyat2022) / urun.Fiyat2010) - 100.0);
    return fiyatDegisimi;
}

int asgariUcretIleAlimHesapla(double urunFiyat, const double asgariUcret)
{
    int alinabilirAdet = asgariUcret / urunFiyat;
    return alinabilirAdet;
}

double alimGucuDegisimiHesapla10(struct Urun urun)
{
    double alimGucuDegisimi = (((100.0 * urun.AsgariUcretIleKacAdet2020) / urun.AsgariUcretIleKacAdet2010) - 100.0);
    return alimGucuDegisimi;
}

double alimGucuDegisimiHesapla12(struct Urun urun)
{
    double alimGucuDegisimi = (((100.0 * urun.AsgariUcretIleKacAdet2022) / urun.AsgariUcretIleKacAdet2010) - 100.0);
    return alimGucuDegisimi;
}

double asgariUcretDegisimiHesapla(double asgari1, double asgari2)
{
    double asgariUcretDegisimi = (((100.0 * asgari2) / asgari1) - 100.0);
    return asgariUcretDegisimi;
}

void asgariUcretDegisimiYazdir(FILE *stream, double asgari2010, double asgari2020, double asgari2022)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nAsgari Ucret Degisimi (%%)\n");

    fprintf(stream, "\t2010 Asgari Ucret: %0.2f TL\n", asgari2010);
    fprintf(stream, "\t2020 Asgari Ucret: %0.2f TL\n", asgari2020);
    fprintf(stream, "\t2022 Asgari Ucret: %0.2f TL\n", asgari2022);
    fprintf(stream, "\t10 Yillik Asgari Ucret Degisimi: %%%.2f\n", asgariUcretDegisimiHesapla(asgari2010, asgari2020));
    fprintf(stream, "\t12 Yillik Asgari Ucret Degisimi: %%%.2f\n", asgariUcretDegisimiHesapla(asgari2010, asgari2022));
}

void alimGucuEnAzArtanYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nAlim Gucu En Az Artan Ürün (%%)\n");
    double minAlimGucuArtisi = 999999;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].AlimGucuDegisimi12 < minAlimGucuArtisi)
        {
            minAlimGucuArtisi = urunler[i].AlimGucuDegisimi12;
            index = i;
        }
    }
    fprintf(stream, "\t%s (%s)\n", urunler[index].Adi, urunler[index].Birimi);
    fprintf(stream, "\t2010 Alinabilir: %d Adet %s\n", urunler[index].AsgariUcretIleKacAdet2010, urunler[index].Birimi);
    fprintf(stream, "\t2020 Alinabilir: %d Adet %s\n", urunler[index].AsgariUcretIleKacAdet2020, urunler[index].Birimi);
    fprintf(stream, "\t2022 Alinabilir: %d Adet %s\n", urunler[index].AsgariUcretIleKacAdet2022, urunler[index].Birimi);
    fprintf(stream, "\t12 Yillik Alim Gucu Degisimi: %%%.2f\n", minAlimGucuArtisi);
    minAlimGucuArtisi = 999999;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].AlimGucuDegisimi10 < minAlimGucuArtisi)
        {
            minAlimGucuArtisi = urunler[i].AlimGucuDegisimi10;
            index = i;
        }
    }
    fprintf(stream, "\t10 Yillik Alim Gucu Degisimi: %%%.2f\n", minAlimGucuArtisi);
    fprintf(stream, "\t10 Yillik Fiyat Degisimi: %%\%.2f\n", urunler[index].OnYillikFiyatDegisimi);
    fprintf(stream, "\t12 Yillik Fiyat Degisimi: %%\%.2f\n", urunler[index].OnIkiYillikFiyatDegisimi);
}

void alimGucuEnCokArtanYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nAlim Gucu En Çok Artan Ürün (%%)\n");
    double maxAlimGucuArtisi = -1;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].AlimGucuDegisimi12 > maxAlimGucuArtisi)
        {
            maxAlimGucuArtisi = urunler[i].AlimGucuDegisimi12;
            index = i;
        }
    }

    fprintf(stream, "\t%s (%s)\n", urunler[index].Adi, urunler[index].Birimi);
    fprintf(stream, "\t2010 Alinabilir: %d Adet %s\n", urunler[index].AsgariUcretIleKacAdet2010, urunler[index].Birimi);
    fprintf(stream, "\t2020 Alinabilir: %d Adet %s\n", urunler[index].AsgariUcretIleKacAdet2020, urunler[index].Birimi);
    fprintf(stream, "\t2022 Alinabilir: %d Adet %s\n", urunler[index].AsgariUcretIleKacAdet2022, urunler[index].Birimi);
    fprintf(stream, "\t12 Yillik Alim Gucu Degisimi: %%%.2f\n", maxAlimGucuArtisi);
    maxAlimGucuArtisi = -1;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].AlimGucuDegisimi10 > maxAlimGucuArtisi)
        {
            maxAlimGucuArtisi = urunler[i].AlimGucuDegisimi10;
            index = i;
        }
    }

    fprintf(stream, "\t10 Yillik Alim Gucu Degisimi: %%%.2f\n", maxAlimGucuArtisi);
    fprintf(stream, "\t10 Yillik Fiyat Degisimi: %%\%.2f\n", urunler[index].OnYillikFiyatDegisimi);
    fprintf(stream, "\t12 Yillik Fiyat Degisimi: %%\%.2f\n", urunler[index].OnIkiYillikFiyatDegisimi);
}

void ortalamaFiyatArtisiYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");
    fprintf(stream, "\nOrtalama Fiyat Artisi (%%)\n");
    double ortalamaArtis = 0;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        ortalamaArtis += urunler[i].OnYillikFiyatDegisimi;
    }
    ortalamaArtis /= (i - 1);

    fprintf(stream, "\t10 Yillik Fiyat Artisi: %%%.2f\n", ortalamaArtis);
    ortalamaArtis = 0;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        ortalamaArtis += urunler[i].OnIkiYillikFiyatDegisimi;
    }
    ortalamaArtis /= (i - 1);

    fprintf(stream, "\t12 Yillik Fiyat Artisi: %%%.2f\n", ortalamaArtis);
}

void ortalamaAlimGucuYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");
    fprintf(stream, "\nOrtalama Alim Gucu Degisimi (%%)\n");
    double ortalamaArtis = 0;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        ortalamaArtis += urunler[i].AlimGucuDegisimi10;
    }
    ortalamaArtis /= (i - 1);

    fprintf(stream, "\t10 Yillik Alim Gucu: %%%.2f\n", ortalamaArtis);
    ortalamaArtis = 0;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        ortalamaArtis += urunler[i].AlimGucuDegisimi12;
    }
    ortalamaArtis /= (i - 1);

    fprintf(stream, "\t12 Yillik Alim Gucu: %%%.2f\n", ortalamaArtis);
}

void fiyatiEnAzArtanYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nFiyatı En Az Artan Ürün (%%)\n");
    double minFiyatArtisi = 999999;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].OnYillikFiyatDegisimi < minFiyatArtisi)
        {
            minFiyatArtisi = urunler[i].OnYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t%s\n", urunler[index].Adi);
    fprintf(stream, "\t2010 Fiyati: %.2f TL\n", urunler[index].Fiyat2010);
    fprintf(stream, "\t2020 Fiyati: %.2f TL\n", urunler[index].Fiyat2020);
    fprintf(stream, "\t2022 Fiyati: %.2f TL\n", urunler[index].Fiyat2022);
    fprintf(stream, "\t10 Yillik Fiyat Artisi: %%\%.2f\n", minFiyatArtisi);
    minFiyatArtisi = 999999;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].OnIkiYillikFiyatDegisimi < minFiyatArtisi)
        {
            minFiyatArtisi = urunler[i].OnIkiYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t12 Yillik Fiyat Artisi: %%\%.2f\n", minFiyatArtisi);
}

void fiyatiEnCokArtanYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nFiyatı En Çok Artan Ürün (%%)\n");
    double maxFiyatArtisi = -1;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].OnYillikFiyatDegisimi > maxFiyatArtisi)
        {
            maxFiyatArtisi = urunler[i].OnYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t%s (%s)\n", urunler[index].Adi, urunler[index].Birimi);
    fprintf(stream, "\t2010 Fiyati: %.2f TL\n", urunler[index].Fiyat2010);
    fprintf(stream, "\t2020 Fiyati: %.2f TL\n", urunler[index].Fiyat2020);
    fprintf(stream, "\t2022 Fiyati: %.2f TL\n", urunler[index].Fiyat2022);
    fprintf(stream, "\t10 Yillik Fiyat Artisi: %%%.2f\n", maxFiyatArtisi);
    maxFiyatArtisi = -1;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (urunler[i].OnIkiYillikFiyatDegisimi > maxFiyatArtisi)
        {
            maxFiyatArtisi = urunler[i].OnIkiYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t12 Yillik Fiyat Artisi: %%%.2f\n", maxFiyatArtisi);
}

void fiyatiEnCokArtanGidaYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nFiyatı En Çok Artan Gida Malzemesi (%%)\n");
    double maxFiyatArtisi = -1;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (strcmp(urunler[i].Alan, "Gida") == 0 && urunler[i].OnYillikFiyatDegisimi > maxFiyatArtisi)
        {
            maxFiyatArtisi = urunler[i].OnYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t%s (%s)\n", urunler[index].Adi, urunler[index].Birimi);
    fprintf(stream, "\t2010 Fiyati: %.2f TL\n", urunler[index].Fiyat2010);
    fprintf(stream, "\t2020 Fiyati: %.2f TL\n", urunler[index].Fiyat2020);
    fprintf(stream, "\t2022 Fiyati: %.2f TL\n", urunler[index].Fiyat2022);
    fprintf(stream, "\t10 Yillik Fiyat Artisi: %%%.2f\n", maxFiyatArtisi);
    maxFiyatArtisi = -1;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (strcmp(urunler[i].Alan, "Gida") == 0 && urunler[i].OnIkiYillikFiyatDegisimi > maxFiyatArtisi)
        {
            maxFiyatArtisi = urunler[i].OnIkiYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t12 Yillik Fiyat Artisi: %%%.2f\n", maxFiyatArtisi);
}

void fiyatiEnCokArtanYakitYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "\nFiyatı En Çok Artan Yakit Malzemesi (%%)\n");
    double maxFiyatArtisi = -1;
    int index = 0;
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (strcmp(urunler[i].Alan, "Yakit") == 0 && urunler[i].OnYillikFiyatDegisimi > maxFiyatArtisi)
        {
            maxFiyatArtisi = urunler[i].OnYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t%s (%s)\n", urunler[index].Adi, urunler[index].Birimi);
    fprintf(stream, "\t2010 Fiyati: %.2f TL\n", urunler[index].Fiyat2010);
    fprintf(stream, "\t2020 Fiyati: %.2f TL\n", urunler[index].Fiyat2020);
    fprintf(stream, "\t2022 Fiyati: %.2f TL\n", urunler[index].Fiyat2022);
    fprintf(stream, "\t10 Yillik Fiyat Artisi: %%%.2f\n", maxFiyatArtisi);
    maxFiyatArtisi = -1;
    index = 0;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        if (strcmp(urunler[i].Alan, "Yakit") == 0 && urunler[i].OnIkiYillikFiyatDegisimi > maxFiyatArtisi)
        {
            maxFiyatArtisi = urunler[i].OnIkiYillikFiyatDegisimi;
            index = i;
        }
    }

    fprintf(stream, "\t12 Yillik Fiyat Artisi: %%%.2f\n", maxFiyatArtisi);
}

void urunleriYazdir(struct Urun *urunler, FILE *stream)
{
    fprintf(stream, "\n************************************************************\n");

    fprintf(stream, "Ürünler ve Fiyatları\n");
    int i;
    for (i = 0; i < URUN_SAYISI; i++)
    {
        fprintf(stream, "\t%s (%s)\n", urunler[i].Adi, urunler[i].Birimi);
        fprintf(stream, "\t%s\n", urunler[i].Alan);
        fprintf(stream, "\t2010 Fiyati: %.2f TL\n", urunler[i].Fiyat2010);
        fprintf(stream, "\t2020 Fiyati: %.2f TL\n", urunler[i].Fiyat2020);
        fprintf(stream, "\t2022 Fiyati: %.2f TL\n", urunler[i].Fiyat2022);
        fprintf(stream, "\t10 Yıllık Fiyat Degisimi: %%%.2f\n", urunler[i].OnYillikFiyatDegisimi);
        fprintf(stream, "\t12 Yıllık Fiyat Degisimi: %%%.2f\n", urunler[i].OnIkiYillikFiyatDegisimi);
        fprintf(stream, "\t2010 Alim Gucu: %d Adet %s\n", urunler[i].AsgariUcretIleKacAdet2010, urunler[i].Birimi);
        fprintf(stream, "\t2020 Alim Gucu: %d Adet %s\n", urunler[i].AsgariUcretIleKacAdet2020, urunler[i].Birimi);
        fprintf(stream, "\t2022 Alim Gucu: %d Adet %s\n", urunler[i].AsgariUcretIleKacAdet2022, urunler[i].Birimi);
        fprintf(stream, "\t10 Yıllık Alim Gucu Degisimi: %%%.2f\n", urunler[i].AlimGucuDegisimi10);
        fprintf(stream, "\t12 Yıllık Alim Gucu Degisimi: %%%.2f\n", urunler[i].AlimGucuDegisimi12);
        fprintf(stream, "-----------------------------\n");
    }
}

struct Urun dosyaOku(char *line)
{
    char *token;
    struct Urun urun;
    int counter = 0;
    for (token = strtok(line, ","); token && *token; token = strtok(NULL, ",\n"))
    {
        if (counter == 0)
        {
            strcpy(urun.Adi, token);
        }
        else if (counter == 1)
        {
            strcpy(urun.Marka, token);
        }
        else if (counter == 2)
        {
            strcpy(urun.Birimi, token);
        }
        else if (counter == 3)
        {
            strcpy(urun.Alan, token);
        }
        else if (counter == 4)
        {
            urun.Fiyat2010 = atof(token);
        }
        else if (counter == 5)
        {
            urun.Fiyat2020 = atof(token);
        }
        else if (counter == 6)
        {
            urun.Fiyat2022 = atof(token);
        }

        counter++;
    }

    urun.OnYillikFiyatDegisimi = onYillikFiyatDegisimiHesapla(urun);
    urun.OnIkiYillikFiyatDegisimi = onIkiYillikFiyatDegisimiHesapla(urun);

    const double asgari2010 = 576.57;
    const double asgari2020 = 2324.71;
    const double asgari2022 = 4253.40;
    urun.AsgariUcretIleKacAdet2010 = asgariUcretIleAlimHesapla(urun.Fiyat2010, asgari2010);
    urun.AsgariUcretIleKacAdet2020 = asgariUcretIleAlimHesapla(urun.Fiyat2020, asgari2020);
    urun.AsgariUcretIleKacAdet2022 = asgariUcretIleAlimHesapla(urun.Fiyat2022, asgari2022);
    urun.AlimGucuDegisimi10 = alimGucuDegisimiHesapla10(urun);
    urun.AlimGucuDegisimi12 = alimGucuDegisimiHesapla12(urun);

    return urun;
}

int main()
{
    FILE *stream = fopen("kaynak.txt", "r");

    char line[2048];
    struct Urun urunler[20];
    int counter = 0;
    while (fgets(line, 2048, stream))
    {
        char *tmp = strdup(line);
        urunler[counter] = dosyaOku(tmp);
        counter++;
        free(tmp);
    }
    fclose(stream);
    stream = fopen("hedef.txt", "w+");
    const double asgari2010 = 576.57;
    const double asgari2020 = 2324.71;
    const double asgari2022 = 4253.40;
    urunleriYazdir(urunler, stream);
    fiyatiEnCokArtanYazdir(urunler, stream);
    fiyatiEnAzArtanYazdir(urunler, stream);
    fiyatiEnCokArtanGidaYazdir(urunler, stream);
    fiyatiEnCokArtanYakitYazdir(urunler, stream);
    alimGucuEnCokArtanYazdir(urunler, stream);
    alimGucuEnAzArtanYazdir(urunler, stream);
    ortalamaFiyatArtisiYazdir(urunler, stream);
    ortalamaAlimGucuYazdir(urunler, stream);
    asgariUcretDegisimiYazdir(stream, asgari2010, asgari2020, asgari2022);
    fclose(stream);
}
