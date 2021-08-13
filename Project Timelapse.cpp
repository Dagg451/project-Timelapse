#include<iostream>
#include<windows.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

/*
	Proyecto Timelapse
	v. 1.0.1	Mid 21.8
	Por Dagger451
*/

class clock 
{
	public:
		clock(int hh, int mm, int ss, int ch, int cm, int cs) {
			setTime(hh, mm, ss);
			setCycle(ch, cm, cs);
		}
		
		void setTime(int hh, int mm, int ss) {
			time[0] = hh; time[1] = mm; time[2] = ss;
		}
		
		void setCycle(int hh, int mm, int ss) {
			cycle[0] = hh; cycle[1] = mm; cycle[2] = ss;
		}
		
		float setDayDuration(float hh, float mm, float ss) {
			dayDur[0] = hh; dayDur[1] = mm; dayDur[2] = ss;
			float durSegReal = (dayDur[0] * 3600) + (dayDur[1] * 60) + dayDur[2];
			float durSegFict = (cycle[0] * cycle[1] * cycle[2]);
			float ficSeg_ms = (durSegReal / durSegFict) * 1000;
			msInt = ficSeg_ms;
			return ficSeg_ms;
		}
		
		void printCurrent() {
			cout << introCurrent << time[0] << inter << time[1] << inter << time[2] << endl;
		}
		
		void printConfig() {
			printCurrent();
			cout << " Configuracion de tiempo:	Horas:		" << dayDur[0] << "	Horas por dia:	" << cycle[0] << endl;
			cout << " 				Minutos:	" << dayDur[1] << "	Min. por hora:	" << cycle[1] << endl;
			cout << "				Segundos:	" << dayDur[2] << "	Seg. por min.:	" << cycle[2] << endl;
			cout << "				tick (ms):	" << msInt << endl;
		}	
		
		void printAnimated() {
			cout << " Presione cualquier tecla para terminar..." << endl;
			while(!kbhit()) {
				if(time[2] >= cycle[2]) {
					time[2] = 0;
					time[1]++;
				}
				if(time[1] >= cycle[1]) {
					time[1] = 0;
					time[0]++;
				}
				if(time[0] >= cycle[0]) {
					time[0] = 0;
				}
				cout << time[0] << inter << time[1] << inter << time[2] << endl;
				Sleep(msInt);
				time[2]++;
			}
		}
		
	private:
		
		int time[3] = {0,0,0};
		int cycle[3] = {24,60,60};
		float dayDur[3] = {24,0,0};
		float msInt = 1000;
		string inter = ":";
		string introCurrent = " Hora actual: ";
};

int main ()
{
	int timeSet[3] = {0,0,0};
	int cycleSet[3] = {24,60,60};
	float dayDurSet[3] = {24,0,0};
	string titles[3] = {" horas: "," minutos: "," segundos: "};
	float ms_interval = 1000;
	clock r0(timeSet[0],timeSet[1],timeSet[2],cycleSet[0],cycleSet[1],cycleSet[2]);
	
	bool active = true;
	bool subActive = false;
	int menu;
	int subMenu;
	
	while(active == true) {
		cout << "	Menu principal" << endl << endl;
		cout << " 1. Ayuda" << endl << " 2. Revisar configuracion actual" << endl;
		cout << " 3. Configuracion completa" << endl << " 4. Configuracion especifica" << endl;
		cout << " 5. Iniciar reloj actual" << endl << " 6. Salir" << endl << endl << " >>";
		
		cin >> menu;
		
		switch(menu) {
			case 1: // Ayuda
				cout << endl << " || Ayuda || " << endl;
				cout << " Proyecto Timelapse v. 1.0.1	Mid 21.08 " << endl;
				cout << " Por Dagger451 " << endl << endl;
				cout << " Relojes digitales de ciclo variable y escala personalizable:" << endl;
				cout << " Los relojes generados por el programa tienen el formato hh:mm:ss" << endl;
				cout << " Cada reloj tiene un ciclo de dia, este se establece en tiempo real" << endl;
				cout << " Por ejemplo: 1 dia ficticio (ciclo) = 27 horas reales, entonces tenemos" << endl;
				cout << " Duracion del ciclo: 27 horas, 0 minutos y 0 segundos" << endl << endl;
				cout << " Luego esta la escala o la configuracion del ciclo" << endl;
				cout << " Esta configura las propiedades de las unidades de tiempo" << endl;
				cout << " Por ejemplo, la duracion de un ciclo diario en horas ficticias," << endl;
				cout << " la duracion de una hora en minutos y la de un minuto en segundos" << endl;
				cout << " Por ejemplo: 10 horas por dia, 100 minutos por hora, 100 segundos por minuto." << endl;
				cout << " El programa calculara el intervalo de tiempo que toma un segundo ficticio" << endl;
				cout << " y generara un reloj digital con el tick que corresponde. Ej: 100 ms por segundo" << endl << endl;
				system("pause");
				break;
			case 2: // Print config
				r0.printConfig();
				system("pause");
				break;
			case 3: // Cycle -> Duration -> Time
				cout << " Ingresar duracion del ciclo en tiempo ficticio: " << endl;
				for(int i = 0; i < 3; i++) {
					cout << titles[i];
					cin >> cycleSet[i];
				}
				r0.setCycle(cycleSet[0],cycleSet[1],cycleSet[2]);
				cout << endl << " Ingresar duracion del ciclo en tiempo real: " << endl;
				for(int i = 0; i < 3; i++) {
					cout << titles[i];
					cin >> dayDurSet[i];
				}
				r0.setDayDuration(dayDurSet[0],dayDurSet[1],dayDurSet[2]);
				cout << endl << " Ingresar hora de inicio en el reloj ficticio: " << endl;
				for(int i = 0; i < 3; i++) {
					cout << titles[i];
					cin >> timeSet[i];
				}
				r0.setTime(timeSet[0],timeSet[1],timeSet[2]);
				cout << endl;
				break;
			case 4: // Nested Switch
				subActive = true;
				
				while(subActive == true) {
					cout << endl << " Elegir configuracion especifica: " << endl;
					cout << " 1. Tiempo ficticio" << endl << " 2. Tiempo real" << endl;
					cout << " 3. Hora de inicio" << endl << " 4. Cancelar" << endl << endl;
					
					cin >> subMenu;
					
					switch(subMenu) {
						case 1: // Cycle
							cout << " Ingresar duracion del ciclo en tiempo ficticio: " << endl;
							for(int i = 0; i < 3; i++) {
								cout << titles[i];
								cin >> cycleSet[i];
							}
							r0.setCycle(cycleSet[0],cycleSet[1],cycleSet[2]);
							break;
						case 2: // Duration
							cout << endl << " Ingresar duracion del ciclo en tiempo real: " << endl;
							for(int i = 0; i < 3; i++) {
								cout << titles[i];
								cin >> dayDurSet[i];
							}
							r0.setDayDuration(dayDurSet[0],dayDurSet[1],dayDurSet[2]);
							break;
						case 3: // Time
							cout << endl << " Ingresar hora de inicio en el reloj ficticio: " << endl;
							for(int i = 0; i < 3; i++) {
								cout << titles[i];
								cin >> timeSet[i];
							}
							r0.setTime(timeSet[0],timeSet[1],timeSet[2]);							
							break;
						case 4: // Cancel
							subActive = false;
							break;
					}
				
				}

				break;
			case 5: // Begin
				cout << endl << " ----- Iniciando reloj ----- " << endl;
				r0.printAnimated();
				break;
			case 6: // Exit, break while
				cout << " Cerrando programa..." << endl;
				active = false;
				break;
		}
	}
	
	return 0;
}
