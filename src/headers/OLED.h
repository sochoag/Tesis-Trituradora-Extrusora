#ifndef OLEDClass
#define OLEDClass

#include <U8g2lib.h>
#include <Wire.h>

class Oled
{
    private:
        void dibujarFrames(void);
        void limpiarIconos(void);
        void limpiarVariables(void);
        void limpiarBarra(void);
        void limpiarPantalla(void);
        void mostrarStatus(void);
        void cambiarImagen(const unsigned char imagen[], byte height, byte width);
        void cambiarTitulo(String titulo);
        void barraCarga(byte porcentaje);
        void escribirVariables(int tempExt, byte RPMTrit, byte RPMExt, int fila);
    public:
        Oled(void);
        void init(void);
        byte i=0;
        void paginaInicial();
        void paginaCargando();
        void paginaMonitor();
};

#endif
