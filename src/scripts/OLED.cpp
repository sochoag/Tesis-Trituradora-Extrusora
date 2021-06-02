#include "headers/OLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#define logo1_width 56
#define logo1_height 35

static const unsigned char logo1[] = {
    0x00, 0x00, 0x00, 0xce, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xdf, 0x0f,
    0x00, 0x00, 0x00, 0x00, 0xfe, 0x9f, 0x7f, 0x00, 0x00, 0x00, 0x80, 0xff,
    0x3f, 0xff, 0x01, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0xfe, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfc, 0x0b, 0x00, 0x00, 0xfc, 0x1f, 0x00, 0xf8, 0x39,
    0x00, 0x00, 0xfe, 0x1f, 0x00, 0xf0, 0x7d, 0x00, 0x80, 0xff, 0x0f, 0x3c,
    0xf0, 0xfc, 0x00, 0xc0, 0xff, 0x87, 0x80, 0xe0, 0xfc, 0x03, 0xe0, 0xff,
    0x03, 0x7e, 0xc2, 0xfe, 0x07, 0xf0, 0xff, 0x81, 0xff, 0x04, 0xfe, 0x0f,
    0xf8, 0x3f, 0xc0, 0x07, 0x08, 0xff, 0x1f, 0xfc, 0x07, 0xe8, 0x03, 0x00,
    0xff, 0x3f, 0x7c, 0xe0, 0xe0, 0xf7, 0x07, 0xff, 0x3f, 0x0e, 0xfe, 0xf0,
    0xff, 0x17, 0xff, 0x7f, 0xc0, 0xff, 0x74, 0x7f, 0x06, 0xff, 0x7f, 0xfc,
    0xff, 0x34, 0x00, 0x06, 0xff, 0x3f, 0xfe, 0xff, 0x34, 0x00, 0x06, 0xff,
    0x03, 0xfe, 0xff, 0xf4, 0xff, 0x07, 0x3f, 0x70, 0xfc, 0xff, 0xe0, 0xff,
    0x17, 0x07, 0x3e, 0xfc, 0xff, 0x00, 0xe0, 0x03, 0xe0, 0x1f, 0xf8, 0xff,
    0x00, 0xe0, 0x0b, 0xfc, 0x1f, 0xf0, 0x7f, 0x90, 0xff, 0x85, 0xff, 0x0f,
    0xe0, 0x7f, 0x22, 0x7f, 0xc0, 0xff, 0x07, 0xc0, 0x7f, 0x06, 0x00, 0xe1,
    0xff, 0x03, 0x80, 0x7f, 0x0f, 0x62, 0xf0, 0xff, 0x01, 0x00, 0x7e, 0x1f,
    0x00, 0xf8, 0x7f, 0x00, 0x00, 0x3c, 0x3f, 0x00, 0xf8, 0x3f, 0x00, 0x00,
    0x38, 0x7f, 0x00, 0x00, 0x08, 0x00, 0x00, 0xa0, 0x7f, 0xfe, 0x3f, 0x00,
    0x00, 0x00, 0x80, 0xff, 0xfc, 0xff, 0x01, 0x00, 0x00, 0x00, 0xfe, 0xf9,
    0x7f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfb, 0x0f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x73, 0x00, 0x00, 0x00
};

Oled::Oled(void)
{
    init();
}

void Oled::init()
{
    u8g2.begin();
    dibujarFrames();
}

void Oled::dibujarFrames()
{
    u8g2.drawFrame(0, 0, 128, 16);
    u8g2.drawFrame(0, 16, 128, 47);
}

void Oled::limpiarIconos()
{
    u8g2.setDrawColor(0);
    u8g2.drawBox(105, 19, 8, 28);
    u8g2.setDrawColor(1);
}

void Oled::limpiarVariables()
{
    u8g2.setDrawColor(0);
    u8g2.drawBox(65, 22, 20, 37);
    u8g2.setDrawColor(1);
}

void Oled::limpiarBarra()
{
    u8g2.setDrawColor(0);
    u8g2.drawBox(3, 50, 123, 10);
    u8g2.setDrawColor(1);
}

void Oled::limpiarPantalla()
{
    u8g2.setDrawColor(0);
    u8g2.drawBox(1, 17, 126, 45);
    u8g2.setDrawColor(1);
}

void Oled::mostrarStatus()
{
    u8g2.setFontMode(0);
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.drawStr(10, 26, "Conexion Wifi");
    u8g2.drawStr(10, 36, "Conexion Server");
    u8g2.drawStr(10, 46, "Fin Carreras");
    u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
    limpiarIconos();
    u8g2.drawGlyph(90, 27, 0x00f7);
    u8g2.drawGlyph(90, 37, 0x010e);
    u8g2.drawGlyph(90, 47, 0x0118);
    u8g2.drawGlyph(105, 27, i >= 25 ? 0x0073 : 0x011b);
    u8g2.drawGlyph(105, 37, i >= 50 ? 0x0073 : 0x011b);
    u8g2.drawGlyph(105, 47, i >= 75 ? 0x0073 : 0x011b);
}

void Oled::cambiarImagen(const unsigned char imagen[], byte height, byte width)
{
    limpiarPantalla();
    u8g2.drawXBMP((128 - width) / 2, 16 + (47 - height) / 2, width, height, imagen);
}

void Oled::cambiarTitulo(String titulo)
{
    u8g2.setFont(u8g2_font_nerhoe_tf);
    u8g2.setFontRefHeightAll();
    u8g2.setDrawColor(0);
    u8g2.drawBox(1, 1, 126, 14);
    u8g2.setDrawColor(1);
    u8g2.drawStr((u8g2.getDisplayWidth() - u8g2.getUTF8Width(titulo.c_str())) / 2, 12, titulo.c_str());
}

void Oled::barraCarga(byte porcentaje)
{
    limpiarBarra();
    u8g2.drawFrame(2, 51, 124, 10);
    u8g2.drawBox(2, 51, 124 * porcentaje / 100, 10);
    String porc = String(porcentaje) + " %";
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.setFontMode(1);
    u8g2.setDrawColor(2);
    u8g2.drawStr((u8g2.getDisplayWidth() - u8g2.getUTF8Width(porc.c_str())) / 2, 59, porc.c_str());
}

void Oled::escribirVariables(int tempExt, byte RPMTrit, byte RPMExt, int fila)
{
    u8g2.setFontMode(0);
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setFontRefHeightAll();
    u8g2.drawStr(5, 28, "T.Extrusor:");
    u8g2.drawStr(5, 38, "Triturador:");
    u8g2.drawStr(5, 48, "Extrusora:");
    u8g2.drawStr(5, 58, "Filamento:");
    u8g2.drawStr(90, 28, "Celsius");
    u8g2.drawStr(90, 38, "RPM");
    u8g2.drawStr(90, 48, "RPM");
    u8g2.drawStr(90, 58, "Gramos");
    limpiarVariables();
    u8g2.drawStr(65, 28, String(tempExt).c_str());
    u8g2.drawStr(65, 38, String(RPMTrit).c_str());
    u8g2.drawStr(65, 48, String(RPMTrit).c_str());
    u8g2.drawStr(65, 58, String(fila).c_str()); 
}

void Oled::paginaInicial()
{
    cambiarTitulo("Trituradora - Extrusora");
    cambiarImagen(logo1, logo1_height, logo1_width);
    u8g2.sendBuffer();
    limpiarPantalla();
}

void Oled::paginaCargando()
{
    cambiarTitulo("Cargando");
    mostrarStatus();
    barraCarga(i);
    u8g2.sendBuffer();
    limpiarPantalla();
}

void Oled::paginaMonitor()
{
    cambiarTitulo("Estados");
    escribirVariables(random(300),random(100), random(100), random(1000));
    u8g2.sendBuffer();
}