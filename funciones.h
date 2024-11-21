#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Funciones para usar en el juego
// mostrar la palabra Bonzo y una linea encima del juego
    void bonzoylinea (){
        cout << "BONZO" << endl << "----------------------------------" << endl;
    }

    void dobleEndl (){
        cout<<endl;
        cout<<endl;
    }
// 1 - JUGAR
/// Funcion para pedir nombres
    int pedir_nombres(string& PJ1, string& PJ2) {
        int num = 0;
        while (num != 1) {
            system("cls");
            bonzoylinea();
            cout << "Antes de comenzar deben registrar sus nombres: " << endl << endl;

            cout << "Nombre jugador N1? ";
            cin >> PJ1;
            cout << "Nombre jugador N2? ";
            cin >> PJ2;

            cout << endl << "Desean confirmar nombres?" << endl;
            cout << "1 = Si     2 = No" << endl;
            cout<<endl;

            cin >> num;

            if (num != 1) {
                cout << "No se registraron los nombres. Intente nuevamente." << endl;
                cout<<endl;
            }
        }

        cout << "¡¡¡¡¡Que comience el juego!!!!!" << endl;
        cout<<endl;
        return num;
        }

/// Función para ver quién empieza el juego
    int quien_empieza(string& PJ1,string& PJ2) {
        system("cls");
        int num;
        bonzoylinea();
        cout<< "Lanzaremos un dado para saber quien tiene el saque"<<endl;
        cout<< "Dado impar comienza "<<PJ1<<", dado par comienza "<<PJ2<<endl;
        cout<<endl;
        system("pause");

        system("cls");

        if (num % 2 == 0) {
            bonzoylinea();
            cout<<"Valor del dado: "<<num<<endl;
            cout << "El jugador "<<PJ2<<" comienza primero" << endl;
            dobleEndl ();
            system("pause");
            return 2;
        } else {
            bonzoylinea();
            cout<<"Valor del dado: "<<num<<endl;
            cout << "El jugador "<<PJ1<<" comienza primero" << endl;
            dobleEndl ();
            system("pause");
            return 1;
        }
}

// Funcion para lanzar los dados
    void tirar_dados(int v_dados[], int tam) {
        for (int i = 0; i < tam; i++) {
        v_dados[i] = (rand() % 6) + 1;
        }
    }

// Funcion para mostrar los valores de los dados
    void mostrar_dados(int v_dados[], int tam) {
        for (int i = 0; i < tam; i++) {
        cout << v_dados[i] << "     ";
        }
        cout << endl;
    }

/// Función para iniciar el juego
void iniciar_juego(string& PJ1, string& PJ2, int comienzo, int& puntaje1, int& puntaje2, int& bonzo_cuenta1, int& bonzo_cuenta2, int& lanzamientos1, int& lanzamientos2, bool& perdedorTripleProhibido, string& perdedor) {

    int v_dados[3];
    int cant_dados[2] = {3, 3}; // Dados que cada jugador puede usar (por defecto 3)
    int penalizacion[2] = {0, 0}; // 0: Sin penalización, 1: Penalizado (2 dados en el próximo turno)
    int cantidadRondas = 0;

    system("cls");

    // WHILE principal para las rondas
    while (cantidadRondas < 6) {
        cantidadRondas++;

        //El for
        for (int jugador = 0; jugador < 2; jugador++) {
            int cantidad_prohibidos = 0;
            bonzoylinea();
            string jugador_actual = (jugador == 0) ? PJ1 : PJ2;
            cout << "Turno de: " << jugador_actual << endl;
            cout << "Ronda #" << cantidadRondas << " - Numero prohibido: " << cantidadRondas << endl;

            // Mostrar puntajes actuales
            cout << "PUNTAJE ACTUAL DE " << PJ1 << ": " << puntaje1 << endl;
            cout << "PUNTAJE ACTUAL DE " << PJ2 << ": " << puntaje2 << endl;

            int puntuacion_ronda = 0; // Puntos acumulados en esta ronda
            bool finalizar_turno = false;

            // Aplicar penalizacion de dados si corresponde
            if (penalizacion[jugador] == 1) {
                cant_dados[jugador] = 2;
                penalizacion[jugador] = 0; // Penalizacion solo dura un turno
            }

            do {
                tirar_dados(v_dados, cant_dados[jugador]);
                cout << "Dados: ";
                mostrar_dados(v_dados, cant_dados[jugador]);
                cout<< endl;

                int cantidad_prohibidos = 0;
                for (int i = 0; i < cant_dados[jugador]; i++) {
                    if (v_dados[i] == cantidadRondas) {
                        cantidad_prohibidos++;
                    }
                }

                ///Jugando con dos dados
                if (cant_dados[jugador] == 2) {
                    if (cantidad_prohibidos == 2) {
                        cout << "¡Ambos dados muestran el numero prohibido! Pierdes todos los puntos acumulados hasta ahora." << endl;


                        if (jugador == 0) {
                            puntaje1 = 0;
                        } else {
                            puntaje2 = 0;
                        }
                        finalizar_turno = true; /// Finaliza el turno, pero no descalifica

                    } else if (v_dados[0] == v_dados[1] && v_dados[0] != cantidadRondas) {
                        cout << "¡Dos dados iguales pero no es Bonzo, ve a dormir! Solo sumas los puntos." << endl;
                        puntuacion_ronda += v_dados[0] + v_dados[1]; // Sumar puntos de los dos dados




                    } else {
                        /// Sumar los puntos de los dados si no hay condiciones especiales
                        puntuacion_ronda += v_dados[0] + v_dados[1];
                        cout << "Puntaje acumulado en esta tirada: " << puntuacion_ronda << endl;
                    }
                } else { // Regla estandar: jugando con tres dados




                    ///JUGANDO CON TRES DADOS
                    if (cantidad_prohibidos == 1) {
                        cout << "¡Numero prohibido! Pierdes todos los puntos acumulados en esta ronda." << endl;
                         puntuacion_ronda = 0;
                        //if (jugador == 0) {
                          //  puntaje1 = 0;
                        //} else {
                           // puntaje2 = 0;
                        //}
                        finalizar_turno = true;




                    } else if (cantidad_prohibidos == 2) {
                        cout << "¡Doble numero prohibido! Pierdes todos los puntos acumulados y en la proxima ronda lanzaras con dos dados." << endl; ///CON 2 DADOS
                        penalizacion[jugador] = 1; // Penalización para el próximo turno
                        if (jugador == 0) {
                            puntaje1 = 0;
                        } else {
                            puntaje2 = 0;
                        }
                        finalizar_turno = true;




                    } else if (cantidad_prohibidos == 3) {
                    cout << "¡Triple numero prohibido! Has perdido automaticamente el juego." << endl;

                    // Marcar al jugador actual como perdedor por triple prohibido
                    perdedorTripleProhibido = true;
                    if (jugador == 0) {
                            perdedor = PJ1;  //asigna PJ1 como perdedor
                        } else {
                            perdedor = PJ2;  //asigna PJ2 como perdedor
                        }


                    // Asignar puntaje final a 0
                    if (jugador == 0) {
                            puntaje1 = 0;
                        } else {
                            puntaje2 = 0;
                        }

                    return; // Termina el juego




                    } else if (v_dados[0] == v_dados[1] && v_dados[1] == v_dados[2]) {
                        cout << "¡Bonzo, ve a dormir! Triples dados iguales. Puntaje triplicado." << endl;
                        //puntuacion_ronda += 3 * v_dados[0];
                        puntuacion_ronda = puntuacion_ronda + (3* v_dados[0])*2;
                    } else {
                        // Sumar los puntos de los dados si no hay números prohibidos
                        for (int i = 0; i < cant_dados[jugador]; i++) {
                            puntuacion_ronda += v_dados[i];
                        }
                        cout << "Puntaje acumulado en esta tirada: " << puntuacion_ronda << endl;
                    }
                }

                // Preguntar si desea continuar
                if (!finalizar_turno) {
                    int opc;
                    cout << "¿Quieres seguir tirando? (1= Sí   |   0= No): ";
                    cin >> opc;

                    if (opc == 0) {
                        if (jugador == 0) {
                            puntaje1 += puntuacion_ronda;
                            lanzamientos1++;
                        } else {
                            puntaje2 += puntuacion_ronda;
                            lanzamientos2++;
                        }
                        finalizar_turno = true;
                    }
                }
            } while (!finalizar_turno);

            // Restaurar dados a 3 si no hay penalización
            if (cant_dados[jugador] == 2 && penalizacion[jugador] == 0) {
                cant_dados[jugador] = 3;
            }

            // Fin del turno del jugador
            cout << "Puntaje acumulado total de " << jugador_actual << ": " << (jugador == 0 ? puntaje1 : puntaje2) << endl;
            dobleEndl();
            system("pause");
            system("cls");
        }
    }

    // Fin del juego, mostrar estadísticas
    cout << "¡El juego ha terminado!" << endl;
    cout << "PUNTAJE FINAL DE " << PJ1 << ": " << puntaje1 << endl;
    cout << "PUNTAJE FINAL DE " << PJ2 << ": " << puntaje2 << endl;


    if (puntaje1 > puntaje2) {
        cout << "¡Ganador: " << PJ1 << "!" << endl;
    } else if (puntaje2 > puntaje1) {
        cout << "¡Ganador: " << PJ2 << "!" << endl;
    } else {
        cout << "Empate entre ambos jugadores." << endl;
    }

    system("pause");
    system("cls");
}


// 2 - Función para mostrar estadísticas de los jugadores
void mostrar_estadisticas(string PJ1, string PJ2, int puntaje1, int puntaje2, int bonzo_cuenta1, int bonzo_cuenta2, int lanzamientos1, int lanzamientos2, bool perdedorTripleProhibido, string perdedor) {
    system("cls");
    bonzoylinea();
    cout << "ESTADÍSTICAS DEL JUEGO" << endl;
    cout << "----------------------------------" << endl;

    if (puntaje1 == 0 && puntaje2 == 0 && lanzamientos1 == 0 && lanzamientos2 == 0) {
        // Si no hay puntajes ni lanzamientos, significa que no han jugado
        cout << "Aun no hay estadísticas disponibles. ¡Juega primero!" << endl;
    } else {
        // Mostrar estadísticas de cada jugador
        cout << "Jugador 1: " << PJ1 << endl;
        cout << "Puntos Totales: " << puntaje1 << endl;
        cout << "Bonzo, Ve a Dormir obtenidos: " << bonzo_cuenta1 << endl;
        cout << "Lanzamientos Exitosos: " << lanzamientos1 << endl;
        cout << "----------------------------------" << endl;

        cout << "Jugador 2: " << PJ2 << endl;
        cout << "Puntos Totales: " << puntaje2 << endl;
        cout << "Bonzo, Ve a Dormir obtenidos: " << bonzo_cuenta2 << endl;
        cout << "Lanzamientos Exitosos: " << lanzamientos2 << endl;
        cout << "----------------------------------" << endl;

        // Mostrar ganador o empate
        if (puntaje1 > puntaje2) {
            cout << "¡Ganador: " << PJ1 << " con " << puntaje1 << " puntos!" << endl;
        } else if (puntaje2 > puntaje1) {
            cout << "¡Ganador: " << PJ2 << " con " << puntaje2 << " puntos!" << endl;
        } else {
            cout << "¡Empate entre " << PJ1 << " y " << PJ2 << " con " << puntaje1 << " puntos cada uno!" << endl;
        }

        // Mostrar mensaje si hubo un perdedor por triple número prohibido
        if (perdedorTripleProhibido) {
            cout << "¡" << perdedor << " perdio automáticamente por obtener triple número prohibido!" << endl;
        }
    }

    system("pause");
    system("cls");
}

// 4 - Función para confirmar salida
    int salida() {
        system("cls");
        bonzoylinea();
        int salir;
        cout << "¿Estás seguro de que deseas salir?" << endl;
        cout << "1= Si      0= No" <<endl;
        cin >> salir;
        if (salir == 1) {
            cout<<"Gracias por jugar, vuelva pronto!";
            exit(0);
        }else{
            system("cls");
        }
    return salir;
    }
// 3 - Función para mostrar créditos
    void mostrar_creditos() {
        system("cls");
        bonzoylinea();
        cout << "Juego programado por:" << endl;
        cout << "Acosta, Ramon Agustin" << endl;
        cout<<endl;
        system("pause");
        system("cls");

}

// Función para mostrar el menú principal
void mostrar_menu() {
    string PJ1, PJ2;
    int opc, comienzo, salir = 0;
    int puntaje1 = 0, puntaje2 = 0;
    int bonzo_cuenta1 = 0, bonzo_cuenta2 = 0;
    int lanzamientos1 = 0, lanzamientos2 = 0;

    while (salir == 0) {
        bonzoylinea();
        cout << "1 - JUGAR" << endl << "2 - ESTADISTICAS" << endl << "3 - CREDITOS" << endl << "---------------------------------" << endl << "0 - SALIR" << endl;
        cout << "Ingrese el número de opción que desea elegir: ";
        cin >> opc;


        bool perdedorTripleProhibido = false;
        string perdedor = "";

    switch (opc) {
        case 1:
            bonzoylinea();
            if (pedir_nombres(PJ1, PJ2) == 1) {
                comienzo = quien_empieza(PJ1, PJ2);
                iniciar_juego(PJ1, PJ2, comienzo, puntaje1, puntaje2, bonzo_cuenta1, bonzo_cuenta2, lanzamientos1, lanzamientos2, perdedorTripleProhibido, perdedor);
            }
            break;
        case 2:
            mostrar_estadisticas(PJ1, PJ2, puntaje1, puntaje2, bonzo_cuenta1, bonzo_cuenta2, lanzamientos1, lanzamientos2, perdedorTripleProhibido, perdedor);
            break;
        case 3:
            mostrar_creditos();
            break;
        case 0:
            salir = salida();
            break;
        default:
            cout << "Opción incorrecta, intenta nuevamente." << endl;
            break;
        }

        }
    }


