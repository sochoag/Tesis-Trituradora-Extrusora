#ifndef ConexionClass
#define ConexionClass

#include <WiFiManager.h>
#include <Losant.h>
#include <WiFiClient.h>

class Conexion
{
    private:
        //const char* LOSANT_DEVICE_ID = "60a6c59e6b358000068b3a38";
        const char* LOSANT_ACCESS_KEY = "2c1d7495-dbfd-46a0-b643-a86a9c5eb61d";
        const char* LOSANT_ACCESS_SECRET = "4b404c08640e148b3495e2ac5469356ca7bd35dc297da424e00424091b7a4323";
        void init(void);
        WiFiManager wm;
        WiFiClient wifiClient;
        //LosantDevice device;
    public:
        int i = 0;
        Conexion();
        bool autoConnect(void);
        void report();
        friend void handleCommand(LosantCommand *command);
};

#endif