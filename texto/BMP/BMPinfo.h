/*
    INFORMACION SOBRE LA ESTRUCTURA DE UN FICHERO BMP Y LAS FUNCIONES DE MANIPULACION
    =================================================================================

    El fichero BMP:
    ===============

        Secciones:
        ----------
            + Cabecera de fichero:
                - Tipo de fichero (WORD): Siempre contiene los caracteres BM.
                - Longitud de fichero (DWORD).
                - 2 campos WORD que siempre son cero.
                - DWORD: Posicion dentro del fichero donde comienza la informacion de la imagen.

            + Cabecera del mapa de bits:

                Todas las versiones: (v. 2, 3 y 4)

                - DWORD: Longitud de la cabecera del mapa de bits.
                - short(*): Numero de pixeles por fila.
                - short(*): Numero de filas. Si es negativo las filas se almacenan de arriba a abajo,
                         si es positivo, las filas se almacenan en orden inverso.

                - WORD: Numero de planos. No se que es, pero siempre vale uno.
                - WORD: Bits por pixel. Solo puede tomar los valores 1, 4, 8, 24 o 32 ¿¿16 no??

                A partir de la version 2: (v. 3 y 4)

                - DWORD: Tipo de compresion. 0->Sin compresion, 1->RLE8, 2->RLE4, 3->Bitfields.
                - DWORD: Longitud en bytes del bitmap teniendo en cuenta la alineacion con DWORD
                         que tienen que tener las filas.
                         Si no hay compresion este campo vale cero.
                - long: Resolucion horizontal en pixeles por metro. ¿Para que sirve?
                - long: Resolucion vertical en pixeles por metro. ¿Para que sirve?
                - DWORD: Numero de colores de la paleta de color. (Si bits por pixel < 24)
                - DWORD: Colores importantes de la paleta de color. ¿Para que sirve?

                A partir de la version 3: (v. 4)
                (Los siguientes campos los incluyo, aunque no tengo inguna descripcion de su
                funcion o utilizacion).

                - DWORD: Mascara del color rojo.
                - DWORD: Mascara del color verde.
                - DWORD: Mascara del color azul.
                - DWORD: Mascara alfa.
                - DWORD: Tipo de ¿espacio de color? ¿color de espacio?

                - DWORD: Coordenada X del ultimo punto rojo.
                - DWORD: Coordenada Y del ultimo punto rojo.
                - DWORD: Coordenada Z del ultimo punto rojo.

                - DWORD: Coordenada X del ultimo punto verde.
                - DWORD: Coordenada Y del ultimo punto verde.
                - DWORD: Coordenada Z del ultimo punto verde.

                - DWORD: Coordenada X del ultimo punto azul.
                - DWORD: Coordenada Y del ultimo punto azul.
                - DWORD: Coordenada Z del ultimo punto azul.

                - DWORD: Gamma del color rojo.
                - DWORD: Gamma del color verde.
                - DWORD: Gamma del color azul.

            (*) Estos valores son de tipo long para versiones posteriores a la segunda.

            + Paleta de color: Tiene 2^(bits por pixel) elementos con la siguiente estructura
                - BYTE: valor del color rojo.
                - BYTE: valor del color verde.
                - BYTE: valor del color azul.
                - BYTE: Siempre vale cero.

                Los datos se almacenan en orden inverso BGR y el valor a cero.

            + Datos de la imagen:
                Contiene los datos de la imagen con la siguiente estructura:

                - 1 bit por pixel: Cada bit representa un pixel.
                                   0 -> Representa el primer elemento de la paleta de color.
                                   1 -> Representa el segundo elemento de la paleta de color.

                - 4 bits por poxel: Los valores de cada nible (0..15) son el indice de uno de los
                                    colores de la paleta de color.

                - 8 bits por pixel: Los valores de cada byte (0..255) son el indice de uno de los
                                    colores de la paleta de color.

                - 24 bits por pixel: Grupos de tres bytes son la representacion de un pixel en
                                     formato RGB. Los datos se almacenan en orden inverso: BGR.

                - 32 bits por pixel: Igual que 24 bitis por pixel, pero cada grupo BGR se separa
                                     con un byte con valor cero.

                Los datos almacenados en el fichero, se almacenan por filas, y si hiciese falta,
                cada fila se rellena con bytes con valor cero hasta alcanzar un numero de bytes
                multiplo de cuatro.

        La representacion de estos datos que manejan las siguientes funciones se puede ver en el
        fichero BMP.h

void BitMapInicializar(BitMap* BM):
-----------------------------------

    Establece todos los valores a cero (punteros a NULL), y los valores por defecto con el valor
que les corresponde.

    Antes de utilizar cualquier dato del tipo BitMap, es imprescindible utilizar esta funcion para
evitar errores en tiempo de ejecucion debidos a la incorrecta inicializacion de los miembros del
tipo BitMap.


unsigned long BitMapCpy(BitMap* destino, BitMap* origen):
---------------------------------------------------------

    Copia los datos contenidos en el mapa de bits origen, en destino.


unsigned long BitMapCargarCabeceraFichero(BMPCabeceraDeFichero *BMPCF, FILE *f):
--------------------------------------------------------------------------------

    Carga desde un fichero los datos de la cabecera del fichero que se pasa como argumento.


unsigned long BitMapCargarCabeceraBitMap(BMP4CabeceraDeBitMap* BMPCBM, FILE *f):
--------------------------------------------------------------------------------

    Carga desde un fichero los datos de la cabecera del bitmap que se pasa como argumento.


unsigned long
BitMapCargarPaleta(BMPPaletaDeColor* BMPPC, unsigned short bpp, unsigned long LCBM, FILE *f):
---------------------------------------------------------------------------------------------

    Carga desde un fichero los datos de la paleta del fichero que se pasa como argumento.


unsigned long BitMapCargarImagen(BitMap* BM, FILE *f):
------------------------------------------------------

    Dado un mapa de bits correctamente inicializado, carga los datos de la imagen desde el fichero
al que apunta f.

    Los datos de la imagen son cargados por filas, omitiendo siempre los bytes de relleno que
pudiera haber, y siempre se cargan empezando por la fila superior y terminando con la inferior.


unsigned long BitMapCargarDesdeFichero(BitMap* BM, const char* nomfichero):
---------------------------------------------------------------------------

    Carga desde un fichero los datos del bitmap desde el fichero que se pasa como argumento.


unsigned long BitMapGuardarEnFichero(BitMap* BM, const char* nomfichero):
-------------------------------------------------------------------------

    Guarda los datos del bitmap que se pasa como argumento en el fichero con el nombre indicado.


unsigned long PaletaReemplazarPixel(BMPPaletaDeColor* Paleta, BMPPixel* Pixel, long pos):
-----------------------------------------------------------------------------------------

    Cambia en la pelata de color el pixel indicado por el parametro pos, por el pixel indicado
representado por el parametro Pixel, si este no estubiese repetido ya en una posicion distinta de
pos.


long PaletaObtenerIndicePixel(BMPPaletaDeColor* Paleta, BMPPixel* Pixel):
-------------------------------------------------------------------------

    Dada la representacion de un pixel en RGB, lo busca en la paleta de color, y devuelve el
indice que ocupa en ella. Si no se encuentra el pixel la funcion devualve -1.


unsigned long BitMapObtenerPixel(BitMap* BM,BMPPixel *Pixel,unsigned long fila,unsigned long col):
--------------------------------------------------------------------------------------------------

    Devuelve en Pixel los valores RGB del pixel que esta en la fila fila y columna col.


unsigned long
BitMapEscribirPixel(BitMap* BM,struct BMPPixel* Pixel,unsigned long fila,unsigned long col):
--------------------------------------------------------------------------------------------

    Establece el pixel de la fila fila y columna col, con los valores del pixel Pixel.


unsigned long BitMapConvertir(BitMap* BM,unsigned long modo):
-------------------------------------------------------------

    Conversiones de la imagen entre distintos bits de profundida y color o escala de grises.
    ¡¡¡ESTA FUNCION NO ESTA IMPLEMENTADA!!!


unsigned long BitMapEscibirFila(BitMap* BM,unsigned char* datos, unsigned long fila):
-------------------------------------------------------------------------------------

    Dado un mapa de bits correctamente construido, escribe los datos que contiene el buffer datos
en la fila indicada por el parametro fila.


unsigned long BitMapCrear(BitMap* BM, BMPPaletaDeColor* paleta, unsigned char* datos):
--------------------------------------------------------------------------------------

    A partir de los datos contenidos en BM, construyes un mapa de bits que contiene los datos de
paleta y de imagen pasados a la funcion con los parametros paleta y datos respectivamente.

    Los datos minimos que tiene que contener BM son:
        + BM->CabeceraBitMap.Ancho
        + BM->CabeceraBitMap.Alto
        + BM->CabeceraBitMap.BitsPorPixel
        + BM->TipoBitMap (BITMAP_TIPO_BMP_2, BITMAP_TIPO_BMP_3 o BITMAP_TIPO_BMP_4)

    Si  BM contiene datos de la paleta o de imagen, estos se eliminaran de forma automatica.

    Si paleta el NULL y BM->CabeceraBitMap.BitsPorPixel < 24, se proporcionara una paleta por
defecto en escala de grises.

    Si datos es NULL, todos los valores de la imagen se inicializaran a cero por defecto.


void BitMapFinalizar(struct BitMap *BM):
----------------------------------------

    Libera la memoria asignada dinamicamente y llama a la funcion BitMapInicializar para asegurar
la integridad del paramtro BM en posteriores utilizaciones.

 */
