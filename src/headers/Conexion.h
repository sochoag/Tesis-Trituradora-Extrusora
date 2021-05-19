#ifndef ConexionClass
#define ConexionClass

#include <WiFiManager.h>
#include <Losant.h>
#include <WiFiClientSecure.h>

class Conexion
{
    private:
        const char* LOSANT_DEVICE_ID = "6070cae9ca605a0007c7b119";
        const char* LOSANT_ACCESS_KEY = "e965fe6c-d0fc-4745-9aa3-e0b78d680ed2";
        const char* LOSANT_ACCESS_SECRET = "b2f24d891d40cc64a87c3fb0362a499dd701f70d00a7d31c494a0e99930fc600";
        void init(void);
        WiFiManager wm;
        WiFiClientSecure wifiClient;
        LosantDevice device;
    public:
        Conexion();
        bool autoConnect(void);
        void report();
        friend void handleCommand(LosantCommand *command);
};

#endif