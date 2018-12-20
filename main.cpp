#include <iostream>
#include "Tablero.h"
#include <cassert>

using namespace std;

int main()
{
    cout << "*****------------------------------------------------*****" << endl;
    cout << "*************-------                  -------*************" << endl;
    cout << "********************     AMAZONAS     ********************" << endl;
    cout << "*************-------                  -------*************" << endl;
    cout << "*****------------------------------------------------*****" << endl << endl;

    cout << "Configuracion del juego: " << endl << endl;
    cout << "    *Ingrese la profundidad de exploracion (de 1 a 30): ";
    int prof = 0;
    cin >> prof;
    assert (prof >= 1 && prof <= 30);
    cout << endl;
    cout << "    *Evaluar el juego...: " << endl;
    cout << "       1. Por cantidad de movimientos restantes del adversario" << endl;
    cout << "       2. Por puntuacion en base a la vulnerabilidad de las reinas" << endl;
    cout << "       Opcion? ";
    int opcion = 0;
    cin >> opcion;
    cout << endl;
    assert (opcion == 1 || opcion == 2);
    cout << endl;

    cout << "----INICIO DEL JUEGO-----" << endl << endl;
    Tablero<Reina> t;

    t.configurar_inicio();
    t.mostrar_tablero();

    while (!t.tablero_lleno()){
        int columna, col_origen, disparo_c, fila, fil_origen, disparo_f;
        char col, c_origen, disp_c;

        cout << "Su movimiento: " << endl;
        cout << "  Reina a mover: ";
        cin >> fil_origen >> c_origen;
        cout << endl;
        cout << "  Ingrese su movimiento: ";
        cin >> fila >> col;
        cout << endl;
        cout << "  Disparo a: ";
        cin >> disparo_f >> disp_c;
        cout << endl;

        columna = t.decodificador(col);
        col_origen = t.decodificador(c_origen);
        disparo_c = t.decodificador(disp_c);

        if (!t.hay_reina(fil_origen - 1, col_origen))
            cout << "No hay una reina en la posicion elegida" << endl << endl;
        else
            if (!t.reina_roja(fil_origen - 1, col_origen))
                cout << "No podes mover las reinas azules" << endl << endl;
            else{
                bool movio = false; //Booleano que controla si el rojo movio o no una ficha. De esta manera se si azul debe o no jugar.
                t.realizar_movimiento(fil_origen - 1, col_origen, fila - 1, columna, disparo_f - 1, disparo_c, movio);
                t.mostrar_tablero();
                if (movio){
                    cout << "Movimiento Azul: " << endl << endl;
                    t.mueve_azul(prof, opcion);
                    t.mostrar_tablero();
                }else
                    cout << "Ingrese nuevamente su movimiento: " << endl;
            }

        if (t.fin_del_juego())
            break;
    }

    if (t.tablero_lleno())
        cout << "Empate" << endl;
    else if (t.gano_rojo())
            cout << "¡Ganaste! Tu puntaje fue " << t.puntaje() << endl << "¡Felicitaciones!" << endl;
        else
            cout << "Perdiste. Las reinas azules te ganaron con un puntaje de " << t.puntaje() << endl << "¡Buena suerte la proxima!" << endl;

    return 0;
}
