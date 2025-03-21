#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


//enumero los casos de severidad
enum severidad{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};
void logMessage(string mensaje, int NivelSeveridad){

ofstream logFile("log.txt", std::ios::app); // Abrimos en modo append 
// Convertir el nivel de severidad en texto
string gravedad;
try{
    switch (NivelSeveridad) {
        case DEBUG: gravedad = "[DEBUG] "; break;
        case INFO: gravedad = "[INFO] "; break;
        case WARNING: gravedad = "[WARNING] "; break;
        case ERROR: gravedad = "[ERROR] "; break;
        case CRITICAL: gravedad = "[CRITICAL] "; break;
        default: throw "severidad no indicada";//excepcion por si no hay severidad 
    }

// Escribir en el archivo de log
logFile << gravedad << mensaje << std::endl;
logFile.close();
}catch (const char* e) { // Captura la excepcion
    std::cout << "Error: " << e << std::endl;
    }

}

void logMessage(string Mensage_de_Error, string Archivo, int Línea_de_Código){
ofstream logFile("log.txt", std::ios::app);

logFile << "[ERROR] " << Mensage_de_Error << " Archivo: " << Archivo << " linea: " << Línea_de_Código<< std::endl;
logFile.close();    
}

void logMessage(string Mensaje_De_Acceso, string Nombre_de_Usuario){
ofstream logFile("log.txt", std::ios::app);

logFile << "[SECURITY] " << Mensaje_De_Acceso << " to " << Nombre_de_Usuario<< std::endl;
logFile.close();
}

//ejemplo funcion intenta dividir por 0
void ejemploReal() {
    try {
        int x=0;
        int y =3;
        if (x==0) {//chequea que la division no sea 0
            throw runtime_error("division por 0");//lanza excepcion
        }
        else{
            cout << y/x << std::endl;
        }
    } catch (const runtime_error& e) {
        logMessage(e.what(), __FILE__, __LINE__); // Registrar el error en el log
        std::cout << "Se ha registrado un error en el log. Terminando la ejecución." << std::endl;
      //exit(1); // Finalizar la ejecución del programa con código de error
    }
}

int main(){
    
    logMessage("Este es un mensaje de depuración.", 6);
    logMessage("El sistema ha iniciado correctamente.", INFO);
    logMessage("Uso de memoria superior al 80%.", WARNING);
    logMessage("Error al conectar con la base de datos.", ERROR);
    logMessage("Fallo crítico: el sistema se apagará.", CRITICAL);
    // Registro de un error con archivo y línea
    logMessage("Fallo al cargar configuración.", "arch1", 16);

    // Registro de acceso de usuario
    logMessage("access granted", "usuario_admin");
    logMessage("access denied", "hacker123");

    ejemploReal();
    return 0;
}