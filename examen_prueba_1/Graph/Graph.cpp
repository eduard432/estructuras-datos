#include <iostream>
using namespace std;

const int MAX_CIUDADES = 6;

class GrafoCarreteras {
private:
    double tiempo[MAX_CIUDADES][MAX_CIUDADES];
    char nombres[MAX_CIUDADES][20];

    void copiarNombre(int indice, const char* nombre) {
        int i = 0;
        while (nombre[i] != '\0' && i < 19) {
            nombres[indice][i] = nombre[i];
            i++;
        }
        nombres[indice][i] = '\0';
    }

    void inicializarMatriz() {
        for (int i = 0; i < MAX_CIUDADES; i++) {
            for (int j = 0; j < MAX_CIUDADES; j++) {
                if (i == j) {
                    tiempo[i][j] = 0.0;     // 0 horas a sí misma
                } else {
                    tiempo[i][j] = -1.0;    // sin carretera directa
                }
            }
        }
    }

    void agregarCarretera(int a, int b, double horas) {
        // Grafo NO dirigido
        tiempo[a][b] = horas;
        tiempo[b][a] = horas;
    }

public:
    GrafoCarreteras() {
        copiarNombre(0, "Mexico");
        copiarNombre(1, "Toluca");
        copiarNombre(2, "Morelia");
        copiarNombre(3, "Guadalajara");
        copiarNombre(4, "Puebla");
        copiarNombre(5, "Queretaro");

        inicializarMatriz();

        // Carreteras (ejemplo, horas aproximadas)
        agregarCarretera(0, 1, 1.0);   // Mexico - Toluca
        agregarCarretera(1, 2, 2.0);   // Toluca - Morelia
        agregarCarretera(0, 4, 2.0);   // Mexico - Puebla
        agregarCarretera(0, 5, 2.5);   // Mexico - Queretaro
        agregarCarretera(5, 3, 3.0);   // Queretaro - Guadalajara
        agregarCarretera(2, 3, 2.5);   // Morelia - Guadalajara
        // Puebla sin conexión directa a Guadalajara en este ejemplo
    }

    void imprimirCiudades() {
        cout << "Indice  -  Ciudad\n";
        for (int i = 0; i < MAX_CIUDADES; i++) {
            cout << "  " << i << "     -  " << nombres[i] << "\n";
        }
    }

    double tiempoTotalConexionesDirectas(int origen) {
        double suma = 0.0;
        
        for(int j = 0; j < MAX_CIUDADES - 1; j++) {
          if(j == origen) continue;
          double t = tiempo[origen][j];
          if(t > 0) {
            suma += t;
          }
        }

        // TODO:
        // Recorre todas las ciudades j de 0 a MAX_CIUDADES-1.
        // - Ignora j == origen (no contamos la ciudad consigo misma).
        // - Lee el valor t = tiempo[origen][j].
        // - Si t > 0 (hay carretera directa), súmalo a 'suma'.
        //
        // Al final, regresa 'suma'.

        return suma; // cambiar por la suma correcta
    }

    const char* obtenerNombre(int indice) {
        return nombres[indice];
    }
};

// ===================== MAIN =====================

int main() {
    GrafoCarreteras grafo;

    cout << "Ciudades en el grafo:\n";
    grafo.imprimirCiudades();

    cout << "\nTiempo total de conexiones directas desde cada ciudad:\n\n";

    for (int ciudad = 0; ciudad < MAX_CIUDADES; ciudad++) {
        double total = grafo.tiempoTotalConexionesDirectas(ciudad);
        cout << grafo.obtenerNombre(ciudad)
             << ": " << total << " horas en total de carreteras directas\n";
    }

    return 0;
}