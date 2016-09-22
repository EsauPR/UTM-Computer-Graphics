#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BITMAP_TAM
#define BITMAP_TAM

#   define BITMAP_TAM_CABECERA_FICHERO_BMP 14L

#   define BITMAP_TAM_CABECERA_BMP2        16L
#   define BITMAP_TAM_CABECERA_BMP3        40L
#   define BITMAP_TAM_CABECERA_BMP4       108L

#   define BITMAP_TAM_ELEMENTO_PALETA       4L

#   define BITMAP_TAM_PIXEL                 3L

#endif

#ifndef BITMAP_TIPO
#define BITMAP_TIPO

#   define BITMAP_TIPO_BMP_2 1L
#   define BITMAP_TIPO_BMP_3 2L
#   define BITMAP_TIPO_BMP_4 4L

#endif

#ifndef BITMAP_MODOS
#define BITMAP_MODOS

#   define BITMAP_MODO_MONO   1L
#   define BITMAP_MODO_4BIT   2L
#   define BITMAP_MODO_8BIT   4L
#   define BITMAP_MODO_GRIS   8L
#   define BITMAP_MODO_24BIT 16L
#   define BITMAP_MODO_32BIT 32L

#endif

#ifndef BITMAP_COMPRESION
#define BITMAP_COMPRESION

#   define BITMAP_RLE8 1
#   define BITMAP_RLE4 2

#endif

#ifndef BITMAP_MENSAGES
#define BITMAP_MENSAGES

#   define BITMAP_MEMORIA_INSUFICIENTE          1L
#   define BITMAP_INTENTO_AUTOASIGNACION        2L
#   define BITMAP_INDICE_FUERA_DE_RANGO         4L
#   define BITMAP_IMPOSIBLE_ABRIR_FICHERO       8L
#   define BITMAP_TIPO_BMP_DESCONOCIDO         16L
#   define BITMAP_NO_FICHERO_BMP               32L
#   define BITMAP_FICHERO_INCOMPLETO           64L
#   define BITMAP_NUMERO_BITS_INCORRECTO      128L
#   define BITMAP_IMAGEN_VACIA                256L
#   define BITMAP_COMPRESION_NO_IMPLEMENTADA  512L
#   define BITMAP_TIPO_INCORRECTO            1024L
#   define BITMAP_PALETA_VACIA               2048L
#   define BITMAP_PIXEL_INEXISTENTE          4096L
#   define BITMAP_PIXEL_REPETIDO             8192L
#   define BITMAP_DATOS_FUERA_DE_RANGO      16384L

#endif

struct BMPCabeceraDeFichero
{
    unsigned short Tipo; /* == BM*/
    unsigned long Longitud; /* longitud del fichero en bytes */
    unsigned short Reservado1; /* siempre 0 */
    unsigned short Reservado2; /* siempre 0 */
    unsigned long OffsetImagen; /* posicion del inicio de la informacion de la imagen */
};
typedef struct BMPCabeceraDeFichero BMPCabeceraDeFichero;

/*
 * CABECERA DE LA VERSION DOS PARA WINDOWS 2.x Y OS/2 1.x
 */

struct BMP2CabeceraDeBitMap
{
    unsigned long Longitud; /* longitud de la cabecera*/
    short int Ancho; /* anchura de la imagen en pixeles */
    short int Alto; /* >0 -> BottomUp  <0 ->UpBottom */
    unsigned short Planos; /* siempre 1 */
    unsigned short BitsPorPixel; /* 1, 4, 8 o 24 */
};
typedef struct BMP2CabeceraDeBitMap BMP2CabeceraDeBitMap;

/*
 * CABECERA DE LA VERSION TRES PARA WINDOWS 3.x y WINDOWS NT
 */

struct BMP3CabeceraDeBitMap
{
    unsigned long Longitud; /* longitud de la cabecera*/
    long int Ancho; /* anchura de la imagen en pixeles */
    long int Alto; /* >0 -> BottomUp  <0 ->UpBottom */
    unsigned short Planos; /* allways 1 */
    unsigned short BitsPorPixel; /* 1, 4, 8 or 24 */
    unsigned long Compresion; /* 0==NO 1==RLE8 2==RLE4 3==CampoDeBits (solo en NT) */
    unsigned long LongitudBitMap; /* Tamaño de la imagen en bytes. Si no hay compresion == 0*/
    long int ResolucionHorizontal; /* en pixeles por metro ¿¿¿¿???? */
    long int ResolucionVertical; /* en pixeles por metro ¿¿¿¿???? */
    unsigned long ColoresUsados; /* numero de colores de la tabla de colores si BitsPorPixel!=0*/
    unsigned long ColoresImportantes; /* ????????????? Dejar a cero */
};
typedef struct BMP3CabeceraDeBitMap BMP3CabeceraDeBitMap;

/*
 * CABECERA DE LA VERSION CUATRO
 */

struct BMP4CabeceraDeBitMap
{
    unsigned long Longitud; /* longitud de la cabecera*/
    long int Ancho; /* anchura de la imagen en pixeles */
    long int Alto; /* >0 -> BottomUp  <0 ->UpBottom */
    unsigned short Planos; /* allways 1 */
    unsigned short BitsPorPixel; /* 1, 4, 8 or 24 */
    unsigned long Compresion; /* 0==NO 1==RLE8 2==RLE4 3==CampoDeBits (solo en NT) */
    unsigned long LongitudBitMap; /* Tamaño de la imagen en bytes. Si no hay compresion == 0*/
    long int ResolucionHorizontal; /* en pixeles por metro ¿¿¿¿???? */
    long int ResolucionVertical; /* en pixeles por metro ¿¿¿¿???? */
    unsigned long ColoresUsados; /* numero de colores de la tabla de colores si BitsPorPixel!=0*/
    unsigned long ColoresImportantes; /* ????????????? Dejar a cero */

    unsigned long MascaraRojo; /* ¿¿¿¿¿????? */
    unsigned long MascaraVerde; /* ¿¿¿¿¿????? */
    unsigned long MascaraAzul; /* ¿¿¿¿¿????? */
    unsigned long MascaraAlpha; /* ¿¿¿¿¿????? */
    unsigned long TipoEC; /* tipo de ¿espacio de color? ¿color de espacio? */

    /*
     * Coordenadas X, Y, ¿¿¿¿ Z ???? del ultimo punto rojo.
     */
    long int RojoX;
    long int RojoY;
    long int RojoZ;

    /*
     * Coordenadas X, Y, ¿¿¿¿ Z ???? del ultimo punto verde.
     */
    long int VerdeX;
    long int VerdeY;
    long int VerdeZ;

    /*
     * Coordenadas X, Y, ¿¿¿¿ Z ???? del ultimo punto azul.
     */
    long int AzulX;
    long int AzulY;
    long int AzulZ;

    unsigned long GammaRojo; /* valor de escala del gamma rojo */
    unsigned long GammaVerde; /* valor de escala del gamma verde */
    unsigned long GammaAzul; /* valor de escala del gamma azul */
};
typedef struct BMP4CabeceraDeBitMap BMP4CabeceraDeBitMap;

struct BMPElementoPaletaDeColor
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char Cero;
};
typedef struct BMPElementoPaletaDeColor BMPElementoPaletaDeColor;

struct BMPPaletaDeColor
{
    BMPElementoPaletaDeColor *Array;
    unsigned short NumColores;
};
typedef struct BMPPaletaDeColor BMPPaletaDeColor;

struct BMPPixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};
typedef struct BMPPixel BMPPixel;

struct BMPDatosDeImagen
{
    /* si BitsPorPixel < 24 representara los indices de la paleta sino sera el RGB */

    unsigned char *Array;
};
typedef struct BMPDatosDeImagen BMPDatosDeImagen;

struct BitMap
{
    BMPCabeceraDeFichero CabeceraFichero;

    BMP4CabeceraDeBitMap CabeceraBitMap;

    unsigned char TipoBitMap;

    BMPPaletaDeColor Paleta; /* solo si BitsPorPixel < 24 */
    BMPDatosDeImagen Imagen;
};
typedef struct BitMap BitMap;

void BitMapInicializar(BitMap* BM);

unsigned long BitMapCpy(BitMap* destino, BitMap* origen);

unsigned long BitMapCargarCabeceraFichero(BMPCabeceraDeFichero *BMPCF, FILE *f);

unsigned long BitMapCargarCabeceraBitMap(BMP4CabeceraDeBitMap* BMPCBM, FILE *f);

unsigned long
BitMapCargarPaleta(BMPPaletaDeColor* BMPPC, unsigned short bpp, unsigned long LCBM, FILE *f);

unsigned long BitMapCargarImagen(BitMap* BM, FILE *f);

unsigned long BitMapCargarDesdeFichero(BitMap* BM, const char* nomfichero);

unsigned long BitMapGuardarEnFichero(BitMap* BM, const char* nomfichero);

unsigned long PaletaReemplazarPixel(BMPPaletaDeColor* Paleta, BMPPixel* Pixel, long pos);

long PaletaObtenerIndicePixel(BMPPaletaDeColor* Paleta, BMPPixel* Pixel);

unsigned long BitMapObtenerPixel(BitMap* BM,BMPPixel *Pixel,unsigned long fila,unsigned long col);

unsigned long
BitMapEscribirPixel(BitMap* BM,struct BMPPixel* Pixel,unsigned long fila,unsigned long col);

unsigned long BitMapConvertir(BitMap* BM,unsigned long modo);

unsigned long BitMapEscibirFila(BitMap* BM,unsigned char* datos, unsigned long fila);

unsigned long BitMapCrear(BitMap* BM, BMPPaletaDeColor* paleta, unsigned char* datos);

void BitMapFinalizar(struct BitMap *BM);

#endif /* BMP_H */
