#include "BMP.h"

void BitMapInicializar(BitMap* BM)
{
    /* poner toda la memoria a cero */
    memset(BM,0,sizeof(BitMap));

    /* tipo de fichero = "BM" */
    BM->CabeceraFichero.Tipo = 0x4D42;

    /* los planos siempre son 1 */
    BM->CabeceraBitMap.Planos = 1;
}

unsigned long BitMapCpy(BitMap* destino, BitMap* origen)
{
    unsigned long flags = 0;
    unsigned long bytesporfila;
    long int nbytes;

    /* evitar autoasignacion */
    if(destino == origen)
        return BITMAP_INTENTO_AUTOASIGNACION;

    /* copiar la cabeceras de fichero y de bit map */
    memcpy(&(destino->CabeceraFichero),&(origen->CabeceraFichero),sizeof(BMPCabeceraDeFichero));
    memcpy(&(destino->CabeceraBitMap),&(origen->CabeceraBitMap),sizeof(BMP4CabeceraDeBitMap));

    /* Comprobamos la paleta */
    /* si la version es superior a la de windows 2.x ... */
    if(origen->TipoBitMap >= BITMAP_TIPO_BMP_3)
    {
        /* si el origen tiene paleta */
        if(origen->Paleta.NumColores)
        {
            /* comprobar , borrar y asignar, si procede, la paleta de destino */
            if(destino->Paleta.NumColores)
            {
                free(destino->Paleta.Array);
                destino->Paleta.NumColores = 0;
            }
            if(
                !(
                    destino->Paleta.Array = (BMPElementoPaletaDeColor*)
                                                    malloc(
                                                        origen->Paleta.NumColores *
                                                        sizeof(BMPElementoPaletaDeColor)
                                                          )
                 )
               )
            {
                flags |= BITMAP_MEMORIA_INSUFICIENTE;
                destino->Paleta.NumColores = 0;
            }
            else
            {
                destino->Paleta.NumColores = origen->Paleta.NumColores;

                memcpy(destino->Paleta.Array, origen->Paleta.Array,
                        sizeof(BMPElementoPaletaDeColor) * destino->Paleta.NumColores);
            }
        }
    }
    else /* la version 2.x no soporta paleta de color */
    {
        /* si el destino tiene paleta, borrarla */
        if(destino->Paleta.Array)
        {
            free(destino->Paleta.Array);
            destino->Paleta.Array = NULL;
            destino->Paleta.NumColores = 0;
        }
    }

    destino->TipoBitMap = origen->TipoBitMap;

    if(destino->Imagen.Array)
    {
        free(destino->Imagen.Array);
    }

    if(!origen->Imagen.Array)
        return BITMAP_IMAGEN_VACIA;

    switch(origen->CabeceraBitMap.BitsPorPixel)
    {
        case  1:
        case  4:
        case  8:
        case 24:
        case 32:

            bytesporfila=(origen->CabeceraBitMap.Ancho * origen->CabeceraBitMap.BitsPorPixel) / 8;

            if((origen->CabeceraBitMap.Ancho * origen->CabeceraBitMap.BitsPorPixel) % 8)
                bytesporfila++;

            if(origen->CabeceraBitMap.Alto < 0)
                nbytes = -1;
            else
                nbytes = 1;

            nbytes = bytesporfila * origen->CabeceraBitMap.Alto;

            if(!(destino->Imagen.Array = (unsigned char*)malloc(nbytes * sizeof(unsigned char))))
            {
                if(destino->Paleta.Array)
                {
                    free(destino->Paleta.Array);
                    destino->Paleta.Array = NULL;
                    destino->Paleta.NumColores = 0;
                }

                return BITMAP_MEMORIA_INSUFICIENTE;
            }

            memcpy(destino->Imagen.Array, origen->Imagen.Array, nbytes);

            break;

        default:
            return BITMAP_NUMERO_BITS_INCORRECTO;
    }

    return flags;
}

unsigned long BitMapCargarCabeceraFichero(BMPCabeceraDeFichero *BMPCF, FILE *f)
{
    rewind(f);

    if(fread(&(BMPCF->Tipo),sizeof(unsigned short), 1, f) < 1)
        return BITMAP_NO_FICHERO_BMP;

    if( BMPCF->Tipo % 0x100 != 'B' || BMPCF->Tipo / 0x100 != 'M')
        return BITMAP_NO_FICHERO_BMP;

    if(fread(&(BMPCF->Longitud), sizeof(unsigned long), 1, f) < 1)
        return BITMAP_FICHERO_INCOMPLETO;

    if(fread(&(BMPCF->Reservado1), sizeof(unsigned short), 1, f) < 1)
        return BITMAP_FICHERO_INCOMPLETO;

    if(fread(&(BMPCF->Reservado2), sizeof(unsigned short), 1, f) < 1)
        return BITMAP_FICHERO_INCOMPLETO;

    if(fread(&(BMPCF->OffsetImagen), sizeof(unsigned long), 1, f) < 1)
        return BITMAP_FICHERO_INCOMPLETO;

    return 0;
}

unsigned long BitMapCargarCabeceraBitMap(BMP4CabeceraDeBitMap* BMPCBM, FILE *f)
{
    rewind(f);

    fseek(f, BITMAP_TAM_CABECERA_FICHERO_BMP, SEEK_SET);

    if(fread(&(BMPCBM->Longitud), sizeof(unsigned long), 1, f) < 1)
        return BITMAP_FICHERO_INCOMPLETO;

    fseek(f, BITMAP_TAM_CABECERA_FICHERO_BMP, SEEK_SET);

    switch(BMPCBM->Longitud)
    {
        case BITMAP_TAM_CABECERA_BMP4:
            fseek(f, BITMAP_TAM_CABECERA_BMP3, SEEK_CUR);

            if(fread(&(BMPCBM->MascaraRojo), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->MascaraVerde), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->MascaraAzul), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->MascaraAlpha), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->TipoEC), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->RojoX), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->RojoY), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->RojoZ), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->VerdeX), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->VerdeY), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->VerdeZ), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->AzulX), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->AzulY), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->AzulZ), sizeof(long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->GammaRojo), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->GammaVerde), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->GammaAzul), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            fseek(f, BITMAP_TAM_CABECERA_FICHERO_BMP, SEEK_SET);

        /*   　　　　　　　 VOY AQUI !!!!!!!!!!!!!!!*/

        case BITMAP_TAM_CABECERA_BMP3:
            fseek(f, BITMAP_TAM_CABECERA_BMP2, SEEK_CUR);

            if(fread(&(BMPCBM->Compresion), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->LongitudBitMap), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->ResolucionHorizontal), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->ResolucionVertical), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->ColoresUsados), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            if(fread(&(BMPCBM->ColoresImportantes), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            fseek(f, BITMAP_TAM_CABECERA_FICHERO_BMP, SEEK_SET);

        case BITMAP_TAM_CABECERA_BMP2:

            if(fread(&(BMPCBM->Longitud), sizeof(unsigned long), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            BMPCBM->Ancho = 0;
            BMPCBM->Alto = 0;

            if(BMPCBM->LongitudBitMap == BITMAP_TAM_CABECERA_BMP2)
            {
                if(fread(&(BMPCBM->Ancho), sizeof(short int), 1, f) < 1)
                    return BITMAP_FICHERO_INCOMPLETO;
                if(fread(&(BMPCBM->Alto), sizeof(short int), 1, f) < 1)
                    return BITMAP_FICHERO_INCOMPLETO;
            }
            else
            {
                if(fread(&(BMPCBM->Ancho), sizeof(long), 1, f) < 1)
                    return BITMAP_FICHERO_INCOMPLETO;
                if(fread(&(BMPCBM->Alto), sizeof(long), 1, f) < 1)
                    return BITMAP_FICHERO_INCOMPLETO;
            }

            if(fread(&(BMPCBM->Planos), sizeof(unsigned short), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;
            if(fread(&(BMPCBM->BitsPorPixel), sizeof(unsigned short), 1, f) < 1)
                return BITMAP_FICHERO_INCOMPLETO;

            fseek(f, BITMAP_TAM_CABECERA_FICHERO_BMP, SEEK_SET);
    }

    fseek(f, BMPCBM->Longitud, SEEK_CUR);

    return 0;
}

unsigned long
BitMapCargarPaleta(BMPPaletaDeColor* BMPPC, unsigned short bpp, unsigned long LCBM, FILE *f)
{
    unsigned long i;
    int n;

    switch(bpp)
    {
        case 1:
            n = 2;
            break;
        case 4:
            n = 16;
            break;
        case 8:
            n = 256;
            break;
        default:
            n = 0;
            break;
    }

    fseek(f, BITMAP_TAM_CABECERA_FICHERO_BMP + LCBM, SEEK_SET);

    if(n)
    {
     if(!(BMPPC->Array=(BMPElementoPaletaDeColor *)malloc(sizeof(BMPElementoPaletaDeColor) * n)))
     {
         return BITMAP_MEMORIA_INSUFICIENTE;
     }
    }

    for(i=0 ; i < n ; i++)
    {
        fread(&(BMPPC->Array[i].B), sizeof(unsigned char), 1, f);
        fread(&(BMPPC->Array[i].G), sizeof(unsigned char), 1, f);
        fread(&(BMPPC->Array[i].R), sizeof(unsigned char), 1, f);
        fread(&(BMPPC->Array[i].Cero), sizeof(unsigned char), 1, f);
    }

    BMPPC->NumColores = n;

    return 0;
}

unsigned long BitMapCargarImagen(BitMap* BM, FILE *f)
{
    long int i,nbytes = 1, bytesporfila;
    unsigned char dif,cero;

    if(BM->CabeceraBitMap.Longitud >= BITMAP_TAM_CABECERA_BMP2 && BM->CabeceraBitMap.Compresion)
        return BITMAP_COMPRESION_NO_IMPLEMENTADA;

    if(BM->CabeceraBitMap.Ancho == 0 || BM->CabeceraBitMap.Alto == 0)
        return BITMAP_IMAGEN_VACIA;

    if(BM->Imagen.Array)
    {
        free(BM->Imagen.Array);
        BM->Imagen.Array = NULL;
    }

    bytesporfila = (BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) / 8;

    if((BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) % 8)
        bytesporfila += 1;

    if(BM->CabeceraBitMap.Alto < 0)
        nbytes *= -1;

    nbytes *= BM->CabeceraBitMap.Alto * bytesporfila;

    if(!(BM->Imagen.Array = (unsigned char *) malloc(nbytes * sizeof(unsigned char))))
        return BITMAP_MEMORIA_INSUFICIENTE;

    dif = (4 - bytesporfila % 4) % 4;

    fseek(f,BM->CabeceraFichero.OffsetImagen, SEEK_SET);

    for(i=0 ; i < nbytes ; i += bytesporfila)
    {
        if(BM->CabeceraBitMap.Alto > 0)
            fread(&(BM->Imagen.Array[nbytes - i - bytesporfila]),
                    sizeof(unsigned char) * bytesporfila, 1, f);
        else
            fread(&(BM->Imagen.Array[i]), sizeof(unsigned char) * bytesporfila, 1, f);

        fread(&cero, sizeof(unsigned char), dif, f);
    }

    return 0;
}

unsigned long BitMapCargarDesdeFichero(BitMap* BM, const char* nomfichero)
{
    FILE *f;
    unsigned long flags=0;

    if(!(f=fopen(nomfichero,"rb")))
        return BITMAP_IMPOSIBLE_ABRIR_FICHERO;

    if((flags |= BitMapCargarCabeceraFichero(&(BM->CabeceraFichero), f)))
    {
        fclose(f);
        return flags;
    }

    if((flags |= BitMapCargarCabeceraBitMap(&(BM->CabeceraBitMap), f)))
    {
        fclose(f);
        return flags;
    }

    switch(BM->CabeceraBitMap.Longitud)
    {
        case BITMAP_TAM_CABECERA_BMP2:
            BM->TipoBitMap = BITMAP_TIPO_BMP_2;
            break;
        case BITMAP_TAM_CABECERA_BMP3:
            BM->TipoBitMap = BITMAP_TIPO_BMP_3;
            break;
        case BITMAP_TAM_CABECERA_BMP4:
            BM->TipoBitMap= BITMAP_TIPO_BMP_4;
            break;
        default:
            fclose(f);
            return BITMAP_NO_FICHERO_BMP;
    }

    if(BM->TipoBitMap >= BITMAP_TIPO_BMP_2 && BM->CabeceraBitMap.Compresion)
    {
        fclose(f);
        return BITMAP_COMPRESION_NO_IMPLEMENTADA;
    }

    if((flags |= BitMapCargarPaleta(&(BM->Paleta), BM->CabeceraBitMap.BitsPorPixel,
                                      BM->CabeceraBitMap.Longitud, f)))
    {
        fclose(f);
        return flags;
    }

    if((flags |= BitMapCargarImagen(&(*BM), f)))
    {
        if(BM->Paleta.Array)
        {
            free(BM->Paleta.Array);
            BM->Paleta.Array = NULL;
            BM->Paleta.NumColores = 0;
        }

        fclose(f);

        return flags;
    }

    fclose(f);

    return 0;
}

unsigned long BitMapGuardarEnFichero(BitMap* BM, const char* nomfichero)
{
    FILE *f;
    unsigned char dif;
    unsigned long i, bytesporfila;
    long int nbytes;
    unsigned char cero = 0;

    if(BM->TipoBitMap >= BITMAP_TIPO_BMP_2 && BM->CabeceraBitMap.Compresion)
        return BITMAP_COMPRESION_NO_IMPLEMENTADA;

    if(BM->CabeceraBitMap.Ancho == 0 || BM->CabeceraBitMap.Alto == 0)
        return BITMAP_IMAGEN_VACIA;

    if(!BM->Imagen.Array)
        return BITMAP_IMAGEN_VACIA;

    if(BM->Paleta.NumColores && !BM->Paleta.Array)
        return BITMAP_PALETA_VACIA;

    if(!(f=fopen(nomfichero,"wb")))
    {
        return BITMAP_IMPOSIBLE_ABRIR_FICHERO;
    }

    fwrite(&(BM->CabeceraFichero.Tipo), sizeof(unsigned short), 1, f);
    fwrite(&(BM->CabeceraFichero.Longitud), sizeof(unsigned long), 1, f);
    fwrite(&(BM->CabeceraFichero.Reservado1), sizeof(unsigned short), 1, f);
    fwrite(&(BM->CabeceraFichero.Reservado2), sizeof(unsigned short), 1, f);
    fwrite(&(BM->CabeceraFichero.OffsetImagen), sizeof(unsigned long), 1, f);

    fwrite(&(BM->CabeceraBitMap.Longitud), sizeof(unsigned long), 1, f);

    if(BM->TipoBitMap == BITMAP_TIPO_BMP_2)
    {
        fwrite(&(BM->CabeceraBitMap.Ancho), sizeof(short int), 1, f);
        fwrite(&(BM->CabeceraBitMap.Alto), sizeof(short int), 1, f);
    }
    else
    {
        fwrite(&(BM->CabeceraBitMap.Ancho), sizeof(long int), 1, f);
        fwrite(&(BM->CabeceraBitMap.Alto), sizeof(long int), 1, f);
    }
    fwrite(&(BM->CabeceraBitMap.Planos), sizeof(unsigned short), 1, f);
    fwrite(&(BM->CabeceraBitMap.BitsPorPixel), sizeof(unsigned short), 1, f);

    if(BM->TipoBitMap > BITMAP_TIPO_BMP_2)
    {
        fwrite(&(BM->CabeceraBitMap.Compresion), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.LongitudBitMap), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.ResolucionHorizontal), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.ResolucionVertical), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.ColoresUsados), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.ColoresImportantes), sizeof(unsigned long), 1, f);
    }

    if(BM->TipoBitMap > BITMAP_TIPO_BMP_3)
    {
        fwrite(&(BM->CabeceraBitMap.MascaraRojo), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.MascaraVerde), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.MascaraAzul), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.MascaraAlpha), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.TipoEC), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.RojoX), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.RojoY), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.RojoZ), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.VerdeX), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.VerdeY), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.VerdeZ), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.AzulX), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.AzulY), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.AzulZ), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.GammaRojo), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.GammaVerde), sizeof(unsigned long), 1, f);
        fwrite(&(BM->CabeceraBitMap.GammaAzul), sizeof(unsigned long), 1, f);
    }

    if(BM->Paleta.NumColores)
    {
        for(i=0 ; i < BM->Paleta.NumColores ; i++)
        {
            fwrite(&(BM->Paleta.Array[i].B),sizeof(unsigned char),1,f);
            fwrite(&(BM->Paleta.Array[i].G),sizeof(unsigned char),1,f);
            fwrite(&(BM->Paleta.Array[i].R),sizeof(unsigned char),1,f);
            fwrite(&(BM->Paleta.Array[i].Cero),sizeof(unsigned char),1,f);
        }
    }

    bytesporfila = (BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) / 8;

    if((BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) % 8)
        bytesporfila +=1;

    if(BM->CabeceraBitMap.Alto < 0)
    {
        nbytes = -1;
    }
    else
        nbytes = 1;

    nbytes *= BM->CabeceraBitMap.Alto * bytesporfila;

    dif = ( 4 - bytesporfila % 4 ) % 4;

    for(i=0 ; i < nbytes ; i += bytesporfila)
    {
        if(BM->CabeceraBitMap.Alto > 0)
        {
            fwrite(&(BM->Imagen.Array[nbytes - i - bytesporfila]),
                     sizeof(unsigned char) * bytesporfila, 1, f);
        }
        else
        {
            fwrite(&(BM->Imagen.Array[i]), sizeof(unsigned char) * bytesporfila, 1, f);
        }

        fwrite(&cero,sizeof(unsigned char),dif,f);
    }

    fclose(f);

    return 0;
}

unsigned long BitMapObtenerPixel(BitMap* BM,BMPPixel *Pixel,unsigned long fila,unsigned long col)
{
    unsigned long bytesporfila, indice;

    if(fila < 0 || fila >= BM->CabeceraBitMap.Alto)
        return BITMAP_INDICE_FUERA_DE_RANGO;
    if(col < 0 || col >= BM->CabeceraBitMap.Ancho)
        return BITMAP_INDICE_FUERA_DE_RANGO;

    bytesporfila = (BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) / 8;

    if((BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) % 8)
        bytesporfila++;

    switch(BM->CabeceraBitMap.BitsPorPixel)
    {
        case 1:

            if(BM->Imagen.Array[(fila * bytesporfila) + col / 8] & (1 << (7 - col % 8)))
                indice = 1;
            else
                indice = 0;

            Pixel->B = BM->Paleta.Array[indice].B;
            Pixel->G = BM->Paleta.Array[indice].G;
            Pixel->R = BM->Paleta.Array[indice].R;

            break;

        case 4:

            if(col % 2)
                indice = BM->Imagen.Array[(fila * bytesporfila) + col / 2] & 0x0F;
            else
                indice = BM->Imagen.Array[(fila * bytesporfila) + col / 2] >> 4;

            Pixel->B = BM->Paleta.Array[indice].B;
            Pixel->G = BM->Paleta.Array[indice].G;
            Pixel->R = BM->Paleta.Array[indice].R;

            break;

        case 8:

            indice = BM->Imagen.Array[fila * bytesporfila + col];

            Pixel->B = BM->Paleta.Array[indice].B;
            Pixel->G = BM->Paleta.Array[indice].G;
            Pixel->R = BM->Paleta.Array[indice].R;

            break;

        case 24:

            Pixel->B = BM->Imagen.Array[(fila * BM->CabeceraBitMap.Ancho + col) * 3];
            Pixel->G = BM->Imagen.Array[(fila * BM->CabeceraBitMap.Ancho + col) * 3 + 1];
            Pixel->R = BM->Imagen.Array[(fila * BM->CabeceraBitMap.Ancho + col) * 3 + 2];

            break;

        case 32:

            Pixel->B = BM->Imagen.Array[(fila * BM->CabeceraBitMap.Ancho + col) * 4];
            Pixel->G = BM->Imagen.Array[(fila * BM->CabeceraBitMap.Ancho + col) * 4 + 1];
            Pixel->R = BM->Imagen.Array[(fila * BM->CabeceraBitMap.Ancho + col) * 4 + 2];

            break;
    }

    return 0;
}

long PaletaObtenerIndicePixel(BMPPaletaDeColor* Paleta, BMPPixel* Pixel)
{
    unsigned long i;

    if(!Paleta->NumColores)
        return -1;

    for(i=0 ; i < Paleta->NumColores ; i++)
    {
        if(
            Pixel->R == Paleta->Array[i].R &&
            Pixel->G == Paleta->Array[i].G &&
            Pixel->B == Paleta->Array[i].B
        )
            return i;
    }

    return -1;
}

unsigned long PaletaReemplazarPixel(BMPPaletaDeColor* Paleta, BMPPixel* Pixel, long pos)
{
    long i;

    if(!Paleta->NumColores)
        return BITMAP_PALETA_VACIA;

    if(pos >= Paleta->NumColores)
        return BITMAP_INDICE_FUERA_DE_RANGO;

    for(i=0 ; i < Paleta->NumColores ; i++)
    {
        if(
            Paleta->Array[i].R == Pixel->R &&
            Paleta->Array[i].G == Pixel->G &&
            Paleta->Array[i].B == Pixel->B &&
            i != pos
        )
            break;
    }

    if(i < Paleta->NumColores)
        return BITMAP_PIXEL_REPETIDO;

    Paleta->Array[pos].R = Pixel->R;
    Paleta->Array[pos].G = Pixel->G;
    Paleta->Array[pos].B = Pixel->B;

    return 0;
}

unsigned long
BitMapEscribirPixel(BitMap* BM,struct BMPPixel* Pixel,unsigned long fila,unsigned long col)
{
    long indice;
    unsigned long bytesporfila;
    unsigned char mascara;

    if(fila < 0 || fila >= BM->CabeceraBitMap.Alto)
        return BITMAP_INDICE_FUERA_DE_RANGO;
    if(col < 0 || col >= BM->CabeceraBitMap.Ancho)
        return BITMAP_INDICE_FUERA_DE_RANGO;

    bytesporfila = (BM->CabeceraBitMap.BitsPorPixel * BM->CabeceraBitMap.Ancho) / 8;

    if((BM->CabeceraBitMap.BitsPorPixel * BM->CabeceraBitMap.Ancho) % 8)
        bytesporfila++;

    switch(BM->CabeceraBitMap.BitsPorPixel)
    {
        case 2:

            mascara = (1 << (7 - col));

            if((indice = PaletaObtenerIndicePixel(&(BM->Paleta), Pixel)) < 0)
                return BITMAP_PIXEL_INEXISTENTE;

            if(indice == 0)
            {
                mascara = (~mascara);

                BM->Imagen.Array[fila * bytesporfila + col / 8] &= mascara;
            }
            else
            {
                BM->Imagen.Array[fila * bytesporfila + col / 8] |= mascara;
            }

            break;

        case 4:

            if((indice = PaletaObtenerIndicePixel(&(BM->Paleta), Pixel)) < 0)
                return BITMAP_PIXEL_INEXISTENTE;

            mascara = indice;

            if(col%2)
            {
                BM->Imagen.Array[fila * bytesporfila + col / 2] &= 0xF0;
                BM->Imagen.Array[fila * bytesporfila + col / 2] |= indice;
            }
            else
            {
                BM->Imagen.Array[fila * bytesporfila + col / 2] &= 0x0F;
                BM->Imagen.Array[fila * bytesporfila + col / 2] |= (indice << 4);
            }

            break;

        case 8:

            if((indice = PaletaObtenerIndicePixel(&(BM->Paleta), Pixel)) < 0)
                return BITMAP_PIXEL_INEXISTENTE;

            BM->Imagen.Array[fila * bytesporfila + col] = indice;

            break;

        case 24:

            BM->Imagen.Array[fila * bytesporfila + 3 * col] = Pixel->B;
            BM->Imagen.Array[fila * bytesporfila + 3 * col + 1] = Pixel->G;
            BM->Imagen.Array[fila * bytesporfila + 3 * col + 2] = Pixel->R;

            break;

        case 32:

            BM->Imagen.Array[fila * bytesporfila + 4 * col] = Pixel->B;
            BM->Imagen.Array[fila * bytesporfila + 4 * col + 1] = Pixel->G;
            BM->Imagen.Array[fila * bytesporfila + 4 * col + 2] = Pixel->R;

            break;

        default:
            return BITMAP_NUMERO_BITS_INCORRECTO;
    }

    return 0;
}

unsigned long BitMapConvertir(BitMap* BM,unsigned long modo)
{
    return 0;
}

unsigned long BitMapEscibirFila(BitMap* BM,unsigned char* datos, unsigned long fila)
{
    unsigned char byte=0;
    unsigned long i, j, bytesporfila;

    bytesporfila = (BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) / 8;

    if((BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) % 8)
        bytesporfila++;

    switch(BM->CabeceraBitMap.BitsPorPixel)
    {
        case 1:
            for(i=0 ; i < bytesporfila ; i++)
            {
                byte = 0;

                for(j=0 ; j < 8 ; j++)
                {
                    if(8 * i + j < BM->CabeceraBitMap.Ancho)
                    {
                        byte <<= 1;
                        byte |= datos[8 * i + j];
                    }
                    else
                    {
                        byte <<= (8 - BM->CabeceraBitMap.Ancho % 8) % 8;
                        break;
                    }
                }

                BM->Imagen.Array[bytesporfila * fila + i] = byte;
            }
            break;
        case 4:
            for(i=0 ; i < bytesporfila ; i++)
            {
                byte = 0;

                for(j=0 ; j < 2 ; j++)
                {
                    if(2 * i + j < BM->CabeceraBitMap.Ancho)
                    {
                        byte <<= 4;
                        byte |= datos[2 * i + j];
                    }
                    else
                    {
                        byte <<= (BM->CabeceraBitMap.Ancho % 2) * 4;
                        break;
                    }
                }

                BM->Imagen.Array[bytesporfila * fila + i] = byte;
            }
            break;
        case 8:
            for(i=0 ; i < bytesporfila ; i++)
            {
                BM->Imagen.Array[bytesporfila * fila + i] = datos[i];
            }
            break;
        case 24:
            for(i=0 ; i < BM->CabeceraBitMap.Ancho ; i++)
            {
                BM->Imagen.Array[bytesporfila * fila + 3 * i] = datos[3 * i + 2];
                BM->Imagen.Array[bytesporfila * fila + 3 * i + 1] = datos[3 * i + 1];
                BM->Imagen.Array[bytesporfila * fila + 3 * i + 2] = datos[3 * i];
            }
            break;
        case 32:
            for(i=0 ; i < BM->CabeceraBitMap.Ancho ; i++)
            {
                BM->Imagen.Array[bytesporfila * fila + 4 * i] = datos[2];
                BM->Imagen.Array[bytesporfila * fila + 4 * i + 1] = datos[1];
                BM->Imagen.Array[bytesporfila * fila + 4 * i + 2] = datos[0];
                BM->Imagen.Array[bytesporfila * fila + 4 * i + 3] = 0;

                datos += 3;
            }
            break;
    }

    return 0;
}

unsigned long BitMapCrear(BitMap* BM, BMPPaletaDeColor* paleta, unsigned char* datos)
{
    unsigned char defpalette=1,dif;
    unsigned long i,bytesporfila;
    long int nbytes;

    if(BM->Paleta.Array)
    {
        free(BM->Paleta.Array);
        BM->Paleta.Array = NULL;
        BM->Paleta.NumColores = 0;
    }

    if(BM->Imagen.Array)
    {
        free(BM->Imagen.Array);
        BM->Imagen.Array = NULL;
    }

    switch(BM->TipoBitMap)
    {
        case BITMAP_TIPO_BMP_2:
            BM->CabeceraBitMap.Longitud = BITMAP_TAM_CABECERA_BMP2;
            break;
        case BITMAP_TIPO_BMP_3:
            BM->CabeceraBitMap.Longitud = BITMAP_TAM_CABECERA_BMP3;
            break;
        case BITMAP_TIPO_BMP_4:
            BM->CabeceraBitMap.Longitud = BITMAP_TAM_CABECERA_BMP4;
            break;
        default:
            return BITMAP_TIPO_INCORRECTO;
    }

    switch(BM->CabeceraBitMap.BitsPorPixel)
    {
        case 1:
            BM->Paleta.NumColores = 2;
            break;
        case 4:
            BM->Paleta.NumColores = 16;
            break;
        case 8:
            BM->Paleta.NumColores = 256;
            break;
        case 24:
            BM->Paleta.NumColores = 0;
            break;
        case 32:
            BM->Paleta.NumColores = 0;
            break;
        default:
            BM->Paleta.NumColores = 0;
            return BITMAP_NUMERO_BITS_INCORRECTO;
    }

    if(BM->CabeceraBitMap.BitsPorPixel < 24)
    {
        /* Creamos la paleta */
        if(paleta) /* si se nos ha proporcionado una paleta por defecto */
        {
            /* comprobamos que los datos sean correctos */
            if(BM->CabeceraBitMap.BitsPorPixel == 1 && paleta->NumColores ==2)
                defpalette = 0;
            if(BM->CabeceraBitMap.BitsPorPixel == 4 && paleta->NumColores ==16)
                defpalette = 0;
            if(BM->CabeceraBitMap.BitsPorPixel == 8 && paleta->NumColores ==256)
                defpalette = 0;
        }


        if(!(BM->Paleta.Array = (BMPElementoPaletaDeColor*)malloc(BM->Paleta.NumColores *
                                                            sizeof(BMPElementoPaletaDeColor))
           ))
        {
            return BITMAP_MEMORIA_INSUFICIENTE;
        }

        if(defpalette)
        {
            /* creamos una paleta por defecto*/

            for(i=0 ; i< BM->Paleta.NumColores ; i++)
            {
                BM->Paleta.Array[i].R = BM->Paleta.Array[i].G =  BM->Paleta.Array[i].B =
                i * 0xFF / (BM->Paleta.NumColores - 1);
            }
        }
        else
        {
            /* copiamos la paleta de los parametros */

            for(i=0 ; i< BM->Paleta.NumColores ; i++)
            {
                BM->Paleta.Array[i].R = paleta->Array[i].R;
                BM->Paleta.Array[i].G = paleta->Array[i].G;
                BM->Paleta.Array[i].B = paleta->Array[i].B;
            }
        }
    }
    /* else->no existe paleta */

    bytesporfila = (BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) / 8;

    if((BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.BitsPorPixel) % 8)
        bytesporfila++;

    if(BM->CabeceraBitMap.Alto < 0)
        nbytes = -1;
    else
        nbytes = 1;

    dif = (4 - bytesporfila % 4) / 4;

    BM->CabeceraFichero.Longitud = BITMAP_TAM_CABECERA_FICHERO_BMP +
                                  BM->CabeceraBitMap.Longitud +
                                  4 * sizeof(unsigned char) * BM->Paleta.NumColores +
                                  (bytesporfila + dif) * nbytes * BM->CabeceraBitMap.Alto;

    BM->CabeceraFichero.OffsetImagen = BITMAP_TAM_CABECERA_FICHERO_BMP +
                                  BM->CabeceraBitMap.Longitud +
                                  4 * sizeof(unsigned char) * BM->Paleta.NumColores;


    if(datos)
    {
        if(BM->CabeceraBitMap.BitsPorPixel < 24)
        {
            for(i=0 ; i < nbytes * BM->CabeceraBitMap.Ancho * BM->CabeceraBitMap.Alto ; i++)
            {
                if(datos[i] >= BM->Paleta.NumColores)
                {
                    free(BM->Paleta.Array);
                    BM->Paleta.Array = NULL;
                    BM->Paleta.NumColores = 0;

                    return BITMAP_DATOS_FUERA_DE_RANGO;
                }
            }
        }
    }

    nbytes = BM->CabeceraBitMap.Alto * bytesporfila;

    if(!(BM->Imagen.Array = (unsigned char *) malloc(sizeof(unsigned char) * nbytes)))
    {
        if(BM->Paleta.Array)
        {
            free(BM->Paleta.Array);
            BM->Paleta.Array = NULL;
            BM->Paleta.NumColores = 0;
        }

        return BITMAP_MEMORIA_INSUFICIENTE;
    }

    /*
     *                                 COPIA DE LA IMAGEN
     *                                 ==================
     *
     *     Los datos de imagen que se pasan a la funcion representan o bien los pixeles en RGB, o
     *  bien los indices de la paleta de colores, asi que si son los indices, habra que comvertir
     *  los datos a una imagen de 1, 4 u 8 bits por pixel.
     */

    if(!datos)
    {
        for(i=0 ; i < nbytes ; i++)
            BM->Imagen.Array[i] = 0;
        return 0;
    }

    switch(BM->CabeceraBitMap.BitsPorPixel)
    {
        case 1:
        case 4:

            for(i=0 ; i < nbytes / bytesporfila ; i++)
            {
                BitMapEscibirFila(BM, datos + i * BM->CabeceraBitMap.Ancho, i);
            }

            break;

        case 8:

            for(i=0 ; i < nbytes ; i++)
                BM->Imagen.Array[i] = datos[i];

            break;

        case 24:

            for(i=0 ; i < nbytes / 3 ; i++)
            {
                BM->Imagen.Array[3 * i] = datos[3 * i + 2];
                BM->Imagen.Array[3 * i + 1] = datos[3 * i + 1];
                BM->Imagen.Array[3 * i + 2] = datos[3 * i];
            }

            break;

        case 32:

            for(i=0 ; i < nbytes / 4 ; i++)
            {
                BM->Imagen.Array[4 * i] = datos[2];
                BM->Imagen.Array[4 * i + 1] = datos[1];
                BM->Imagen.Array[4 * i + 2] = datos[0];
                BM->Imagen.Array[4 * i + 3] = 0;

                datos += 3;
            }

            break;
    }

    return 0;
}


void BitMapFinalizar(struct BitMap *BM)
{
    if(BM->Paleta.Array)
    {
        free(BM->Paleta.Array);
        BM->Paleta.Array = NULL;
        BM->Paleta.NumColores = 0;
    }

    if(BM->Imagen.Array)
    {
        free(BM->Imagen.Array);
        BM->Imagen.Array = NULL;
    }

    /* dejar los datos "virgenes" */
    BitMapInicializar(&(*BM));

    return;
}
