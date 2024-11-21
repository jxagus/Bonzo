
#include <iostream>
#include "funciones.h"

using namespace std;

void dibujarDado(int d)
{
    cout<<" +-------+"<<endl;
    switch (d)
    {
    case 1:
        cout<<" |       |"<<endl;
        cout<<" |   O   |"<<endl;
        cout<<" |       |"<<endl;
        break;
    case 2:
        cout<<" | O     |"<<endl;
        cout<<" |       |"<<endl;
        cout<<" |     O |"<<endl;
        break;
    case 3:
        cout<<" | O     |"<<endl;
        cout<<" |   O   |"<<endl;
        cout<<" |     O |"<<endl;
        break;
    case 4:
        cout<<" | O   O |"<<endl;
        cout<<" |       |"<<endl;
        cout<<" | O   O |"<<endl;
        break;
    case 5:
        cout<<" | O   O |"<<endl;
        cout<<" |   O   |"<<endl;
        cout<<" | O   O |"<<endl;
        break;
    case 6:
        cout<<" | O   O |"<<endl;
        cout<<" | O   O |"<<endl;
        cout<<" | O   O |"<<endl;
        break;
    }
    cout<<" +-------+"<<endl;
}

void dibujarDadosEnLinea(int dados[], int cantDados)
{
    string linea1 = "  ", linea2 = "  ", linea3 = "  ", linea4 = "  ";

    for(int x=0; x<cantDados; x++)
    {
        linea1+="+-------+ ";
        switch (dados[x])
        {
        case 1:
            linea2+="|       | ";
            linea3+="|   O   | ";
            linea4+="|       | ";
            break;
        case 2:
            linea2+="| O     | ";
            linea3+="|       | ";
            linea4+="|     O | ";
            break;
        case 3:
            linea2+="| O     | ";
            linea3+="|   O   | ";
            linea4+="|     O | ";
            break;
        case 4:
            linea2+="| O   O | ";
            linea3+="|       | ";
            linea4+="| O   O | ";
            break;
        case 5:
            linea2+="| O   O | ";
            linea3+="|   O   | ";
            linea4+="| O   O | ";
            break;
        case 6:
            linea2+="| O   O | ";
            linea3+="| O   O | ";
            linea4+="| O   O | ";
            break;
        }
    }
    cout<<endl;
    cout<<linea1<<endl;
    cout<<linea2<<endl;
    cout<<linea3<<endl;
    cout<<linea4<<endl;;
    cout<<linea1<<endl; //Se repite la misma linea que abre los dados para que los cierre.
}

int tirarDado()
{
    return rand()%6+1;
}

void solicitarNombres(string &nombre1, string &nombre2)
{
    char confirmar = 'N';
    while (toupper(confirmar) != 'S')
    {
        cout<<" Antes de comenzar a jugar deben registrar sus nombres:" << endl;
        cout<<endl<<" Primer jugador: ";
        cin>>nombre1;
        cout<<endl<<" Segundo jugador: ";
        cin>> nombre2;
        cout<<endl<<" ¿Desea confirmar los nombres ingresados? (S/N): ";
        cin>> confirmar;
        cout<<"--------------------------------------------------------"<<endl;
        cout<< endl;
    }

    cout<<"Nombres de los jugadores registrados: "<<nombre1<<" vs "<<nombre2<<endl;
}

void definirPrimerJugador(string nombre1, string  nombre2, string nombres[])
{

    cout<<endl<<"--------------------------------------------------------"<<endl<<endl;
    cout<<" Ahora solo nos resta definir que jugador comenzará, \n para eso debemos tirar un dado ¿Estas de acuerdo?"<<endl<<endl;
    system("pause");
    int dado = tirarDado();
    cout<<endl;
    dibujarDado(dado);
    cout<<endl;
    if(dado%2==0)
    {
        cout<<"Toco un dado par, comenzará a jugar: "<<nombre1<<endl<<endl;
        nombres[0]=nombre1;
        nombres[1]=nombre2;
    }
    else
    {
        cout<<"Toco un dado impar, comenzará a jugar: "<<nombre2<<endl<<endl;
        nombres[0]=nombre2;
        nombres[1]=nombre1;
    }
    system("pause");
}

int lanzarDados(int dados[], int cantDados)
{
    int sumaDeDados = 0;
    for(int x=0; x<cantDados; x++)
    {
        dados[x]= tirarDado();
        sumaDeDados += dados[x];
    }

    return sumaDeDados;
}

int contarRepeticionesDeNumeroProhibido(int numeroPrhibido, int dados[], int cantDados)
{
    int cont= 0;
    for (int x=0; x<cantDados; x++)
    {
        if(numeroPrhibido == dados[x])
        {
            cont ++;
        }
    }

    return cont;
}

bool dadosIguales(int dados[])
{
    return dados[0]==dados[1] && dados[1]==dados[2];
}

void comenzarJuego(string nombres[], int puntos[], int cantBonzos[], int cantLanzamientosExitosos[])
{
    int cantDadosRonda[2][6]= {{3, 3, 3, 3, 3, 3},{3, 3, 3, 3, 3, 3}};
    int dados[3] = {}, puntosPorRonda[2], puntosPorLanzada, opc, lanzadasExitosas;
    char confirmar;

    for(int ronda = 1; ronda<=6; ronda++)
    {
        for(int x=0; x<2; x++)
        {
            confirmar = 'S';
            puntosPorRonda[x] = 0;
            lanzadasExitosas = 0;

            while(toupper(confirmar) != 'N')
            {
                system("cls");
                cout<<endl<<"[[[[[[[[[[[[[[[[[  RONDA: "<<ronda<<"  ]]]]]]]]]]]]]]]]]";
                cout<<endl<<"  -----------------------------------------" <<endl<<endl;
                cout<<"          -- Turno de: "<<nombres[x]<<" --"<<endl;
                cout<<"      -- Puntos totales al momento: "<<puntos[x]<<" --"<<endl;
                cout<<"     -- Cantidad de dados disponibles: "<<cantDadosRonda[x][ronda-1]<<" --"<<endl<<endl;

                puntosPorLanzada = lanzarDados(dados, cantDadosRonda[x][ronda-1]);
//                if(ronda==2) //Prueba para que toquen tres numeros prohibidos.
//                {
//                    dados[0]=2;
//                    dados[1]=2;
//                    dados[2]=2;
//                }
                dibujarDadosEnLinea(dados, cantDadosRonda[x][ronda-1]);

                switch(contarRepeticionesDeNumeroProhibido(ronda, dados, cantDadosRonda[x][ronda-1]))
                {
                case 0:
                    if(cantDadosRonda[x][ronda-1]==3 && dadosIguales(dados))
                    {
                        cantBonzos[x]++;
                        char opc = 'C';
                        cout<<endl<<"Obtuviste BONZO VE A DORMIR puedes elegir entre las siguientes opciones: "<<endl;
                        cout<<"   - Quitarle un dado al oponente: A"<<endl;
                        cout<<"   - Duplicar los puntos de esta tirada: B"<<endl;
                        while(toupper(opc)!= 'A' && toupper(opc)!= 'B')
                        {
                            cout<<" Eliga entre la opción A o la opción B: ";
                            cin>>opc;
                        }
                        switch (toupper(opc))
                        {
                        case 'A':
                            if(x==0)
                            {
                                cantDadosRonda[1][ronda]=2;
                            }
                            else
                            {
                                cantDadosRonda[0][ronda+1]=2;
                            }
                            cout<<"   << ¡Se quito un dado al oponente! >>"<<endl;;
                            break;
                        case 'B':
                            puntosPorLanzada=puntosPorLanzada*2;
                            cout<<"<< Se duplicaron los puntos obtenidos en esta lanzada de dados. >>"<<endl;;
                            break;
                        }
                    }
                    lanzadasExitosas++;
                    puntosPorRonda[x] += puntosPorLanzada;
                    cout<<endl<<" Lanzada exitosa n°: "<<lanzadasExitosas<<endl;
                    cout<<" Se obtuvieron "<<puntosPorLanzada<<" puntos en esta tirada"<<endl;
                    cout<<" Puntos acumulados al momento en la ronda: "<<puntosPorRonda[x]<<endl;
                    cout<<endl<<" ¿Desea lanzar los dados una vez más? (S/N) ";
                    cin>>confirmar;

                    break;
                case 1:

                    cout<<endl<<"           ¡Obtuviste 1 número prohibido! \n Perdes el turno y tus puntos acumulados en esta ronda."<<endl<<endl;

                    puntosPorRonda[x] = 0;
                    lanzadasExitosas = 0;
                    confirmar = 'N';
                    system("pause");
                    break;
                case 2:

                    cout<<endl<<"        ¡Obtuviste 2 números prohibidos! \n Perdes el turno y tus puntos acumulados en esta ronda,\n    ¡La próxima ronda solo tendrás 2 dados!"<<endl<<endl;
                    puntosPorRonda[x] = 0;
                    lanzadasExitosas = 0;
                    confirmar = 'N';
                    cantDadosRonda[x][ronda]=2;
                    system("pause");
                    break;
                case 3:

                    cout<<endl<<"        ¡Obtuviste 3 números prohibidos! \n      Pierdes el juego... =C"<<endl<<endl;
                    puntos[x]=0;
                    cantLanzamientosExitosos[x] = 0;
                    cantBonzos[x]=0;
                    system("pause");
                    return;
                    break;
                }
            }
            puntos[x]+=puntosPorRonda[x];
            if(lanzadasExitosas>cantLanzamientosExitosos[x])
            {
                cantLanzamientosExitosos[x]=lanzadasExitosas;
            }
        }

        system("cls");
        cout<<endl<<"--------------------------------------------------------"<<endl;
        cout<<endl<<"        -- Puntajes obtenidos en la ronda "<<ronda<<" -- "<<endl;
        cout<<"                - "<<nombres[0]<<": "<<puntosPorRonda[0]<<" -   "<<endl;
        cout<<"                - "<<nombres[1]<<": "<<puntosPorRonda[1]<<" -   "<<endl;
        cout<<endl<<"--------------------------------------------------------"<<endl;
        system("pause");
        system("cls");
    }
}

void recalcularPuntos(int puntos[], int cantBonzos[], int cantLanzamientosExitosos[])
{
    for(int x=0; x<2; x++)
    {
        puntos[x] += cantBonzos[x]*5;
        puntos[x] += (puntos[x]/50)*3;
    }
    if(cantLanzamientosExitosos[0]>cantLanzamientosExitosos[1])
    {
        puntos[0]+=5;
    }
    else
    {
        if(cantLanzamientosExitosos[1]>cantLanzamientosExitosos[0])
        {
            puntos[1]+=5;
        }
        else
        {
            puntos[0]+=5;
            puntos[1]+=5;
        }
    }
}

void mostrarPuntosDeLaPartida(string nombres[], int puntos[],int cantBonzos[], int cantLanzamientosExitosos[])
{
    cout<<"   Hito                    "<<nombres[0]<<"      "<<nombres[1]<<endl;
    cout<<"   -----------------------------------------------"<<endl;
    cout<<"   Puntos                    "<<puntos[0]<<"         "<<puntos[1]<<endl;
    cout<<"   Cant. 50 puntos           "<<puntos[0]/50<<"          "<<puntos[1]/50<<"    (x3)"<<endl;
    cout<<"   Bonzo, ve a dormir        "<<cantBonzos[0]<<"          "<<cantBonzos[1]<<"    (x5)"<<endl;
    cout<<"   Lanzamientos exitosos     "<<cantLanzamientosExitosos[0]<<"          "<<cantLanzamientosExitosos[1]<<"    (x5)"<<endl;
    recalcularPuntos(puntos, cantBonzos, cantLanzamientosExitosos);
    cout<<"   Puntos finales            "<<puntos[0]<<"         "<<puntos[1]<<endl;
}

void definirGanador(string nombres[], int puntos[], int cantBonzos[], int cantLanzamientosExitosos[])
{
    system("cls");
    cout<<endl<<"         [[[[[[[[[[[ FIN DEL JUEGO ]]]]]]]]]]]"<<endl;
    cout<<endl<<"--------------------------------------------------------"<<endl;
    mostrarPuntosDeLaPartida(nombres, puntos,cantBonzos, cantLanzamientosExitosos);

    cout<<endl<<endl<<"--------------------------------------------------------"<<endl<<endl;
    if(puntos[0]==puntos[1])
    {
        if(cantBonzos[0]>cantBonzos[1])
        {
            cout<<"      El ganador fue "<<nombres[0]<<" con "<<puntos[0]<<" puntos.";
        }
        else
        {
            if(cantBonzos[1]>cantBonzos[0])
            {
                cout<<"      El ganador fue "<<nombres[1]<<" con "<<puntos[1]<<" puntos.";
            }
            else
            {
                cout<<"         ¡Hubo un empate, nadie gana, nadie pierde!";
            }
        }
    }
    else
    {
        if(puntos[0]>puntos[1])
        {
            cout<<"   El ganador fue "<<nombres[0]<<" con "<<puntos[0]<<" puntos.";
        }
        else
        {
            cout<<"   El ganador fue "<<nombres[1]<<" con "<<puntos[1]<<" puntos.";
        }
    }
    cout<<endl<<endl<<"--------------------------------------------------------"<<endl;
    system("pause");
}

void guardarPartidaEnRanking(string nombres[], int puntos[], string rankingNombres[], int rankingPuntos[])
{
    rankingNombres[5]=nombres[0];
    rankingPuntos[5]=puntos[0];
    rankingNombres[6]=nombres[1];
    rankingPuntos[6]=puntos[1];
    ordenarRanking(rankingNombres, rankingPuntos);
}

void ordenarRanking(string nombres[], int puntos[])
{
    int auxPuntos;
    string auxNombres;
    for (int i = 0; i < 7 - 1; i++)
    {
        for (int j = 0; j < 7 - i - 1; j++)
        {
            if (puntos[j] < puntos[j + 1])
            {
                auxPuntos = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = auxPuntos;
                auxNombres = nombres[j];
                nombres[j] = nombres[j + 1];
                nombres[j + 1] = auxNombres;
            }
        }
    }
}

void jugar(int rankingPuntos[], string rankingNombres[])
{
    string nombre1, nombre2;
    string nombres[2];
    int puntos[2] = {};
    int cantLanzamientosExitosos[2] = {};
    int cantBonzos[2] = {};
    system("cls");
    cout<<"                      BONZO"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    solicitarNombres(nombre1, nombre2);
    definirPrimerJugador(nombre1, nombre2, nombres);
    comenzarJuego(nombres, puntos, cantBonzos, cantLanzamientosExitosos);
    definirGanador(nombres, puntos, cantBonzos, cantLanzamientosExitosos);
    guardarPartidaEnRanking(nombres, puntos, rankingNombres, rankingPuntos);
}

void mostrarEstadisticas(string nombres[], int puntos[])
{

    if(puntos[0]==0)
    {
        cout<<endl<<"      Aún no jugadores registrados. "<<endl;
    }
    else
    {
        cout<<"-------------------------------------------------------"<<endl;
        cout<<" PUESTO       -       PUNTOS       -        JUGADOR"<<endl;
        for(int x=0; x<5; x++)
        {
            if(puntos[x]!=0)
            {
                cout<<"    "<<x+1<<"         -        "<<puntos[x]<<"          -        "<<nombres[x]<<endl;
            }
        }
        cout<<"--------------------------------------------------------"<<endl;

    }
    system("pause");
}

void creditos()
{
    system("cls");

    cout<<endl<<"--------------------------------------------------------"<<endl;
    cout<<endl<<"                JUEGO REALIZADO POR:"<<endl;
    cout<<endl<<"               JAVIER AGUSTIN LARROCA"<<endl;
    cout<<endl<<"              Programación I - 2024 2C"<<endl;
    cout<<endl<<"--------------------------------------------------------"<<endl<<endl;
    system("pause");
}

bool finalizarJuego()
{
    char confirmar = 'C';

    cout<<endl<<" ¿Esta seguro que desea salir del juego? (S/N): ";
    cin>>confirmar;
    while(toupper(confirmar)!='N' && toupper(confirmar)!='S')
    {
        cout<<endl<<" Opción ingresada incorrecta. (S/N): ";
        cin>>confirmar;
    }
    if(toupper(confirmar)=='S')
    {
        cout<<endl<<"    ¡Muchas gracias por haber jugado BONZO! "<<endl;
        return false;
    }

    return true;
}
