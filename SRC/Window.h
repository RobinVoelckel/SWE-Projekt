#pragma once
#include <windows.h>
#include <fstream>
#include "Text_Data.h"

LRESULT CALLBACK FensterProc(HWND, UINT, WPARAM, LPARAM);	//CallBack definiert

const char	Fehler[] = "Es Fehlt noch mindetens eine Angabe",
			überschrift[] = "Bitte füllen Sie alle Zeilen aus, damit wir eine bessere Übersicht der Angestellten erstellen können.",
			Vorname[] = "Wie ist ihr Vorname?",
			Nachname[]= "Wie lautet ihr Nachname?",
			Abteilung[] = "In welcher Abteilung arbeiten Sie?",
			Arbeit[] = "Welche Arbeit verrrichten Sie ?",
			Anweisung[] = "Danach drücken Sie bitte auf den Button \"Bestätigen\".";

//Fenster Konstanten
const int Width =  GetSystemMetrics(SM_CXSCREEN)/2.5,
          Height = GetSystemMetrics(SM_CYSCREEN)/3;

const int	Fragenanzahl = 4, 
			Zeilenabstand = 50, 
			Top_ab = 80, 
			Seiten_ab = 10, 
			Eingabefeldlänge = 300,
			Eingabefeldhöhe = 20;

//Hilfs Variablen
char eingabe[3][Eingabefeldlänge];
int check_eingabe;

//Variablen declarierung
HWND	eingabefelder[3],
		button,
		text;

static TCHAR const szAppFeName[] = "Umfrage";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int ShowWd){
    
    HWND				hWnd;									//Variablen declarierung
    MSG					msg;									//Variablen declarierung
    WNDCLASSEX			window;									//Variablen declarierung

//Fensterstruktur
    window.cbSize        = sizeof (window);						//Größe des Fensters
    window.style         = CS_HREDRAW | CS_VREDRAW;				//Fenstergröße veränderbar und bleibt zerntriert
    window.lpfnWndProc   = &FensterProc;						//Zuweisung wie die msg sich verhalten soll über der Main def.
    window.cbClsExtra    = 0;									//Zusätzliche Speicherresservierung für die Classe
    window.cbWndExtra    = 0;									//Zusätzliche Speicherresservierung für das Fenster
    window.hInstance     = hInstance;							//Zuweisung der HINSTANCE (bewegliches Fenster in  diesem Fall)
    window.hIcon         = LoadIcon(NULL, IDI_QUESTION);		//Icon Zuweisen
    window.hCursor       = LoadCursor(NULL, IDC_ARROW);			//Art des Cursores Zuweisung
    window.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);	//HintergrundFarbe definieren
    window.lpszMenuName  = NULL;								//
    window.lpszClassName = szAppFeName;							//
    window.hIconSm       = window.hIcon;						//Fenstersymbol oben links in der Ecke festlegen

    if (RegisterClassEx(&window) == 0){
        MessageBox(NULL, "Ein Fehler trat ein!", szAppFeName, MB_OK | MB_ICONERROR);
        return -1;
    }

//Fenster variablen
    hWnd = CreateWindow(        
		szAppFeName,							// Name des Fensters
		szAppFeName,							// Titel des Fensters
		WS_SYSMENU | WS_CAPTION					//
		| WS_BORDER | WS_EX_OVERLAPPEDWINDOW,   // Stil des Fensters
		Width/2,								// X-Position des Fensters
		Height/2,								// Y-Position des Fensters
		Width, Height,							// Breite und Höhe des Fenstes
		HWND_DESKTOP,							// was für ein Fenster soll erzeugt werden (Unterfenster)
		NULL,									// Menü
		hInstance,								// Instanz des FensterApp
		NULL);									// reserviert für weitere Parameter

//Abfrage Schleife
	if (!hWnd) return 0;

	ShowWindow(hWnd, ShowWd);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)){

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

//Windows-Prozedur zur Bearbeitung von Nachrichten
LRESULT CALLBACK FensterProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	HDC			hdc;			//Variablen declarierung
	PAINTSTRUCT	ps;             //Variablen declarierung

	//Auf was soll in dem Fenster reagiert werden
	switch (msg) {

		//Schließen
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		//Textfelder erzeugen
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			//SetTextColor( hdc, RGB( 220, 100, 0));    
			TextOut(hdc, Seiten_ab, Top_ab - 75, überschrift, sizeof(überschrift));
			TextOut(hdc, Seiten_ab, Top_ab - 57, Anweisung, sizeof(Anweisung));
			TextOut(hdc, Seiten_ab, Top_ab - 23, Vorname, sizeof(Vorname));
			TextOut(hdc, Seiten_ab, Top_ab + 27, Nachname, sizeof(Nachname));
			TextOut(hdc, Seiten_ab, Top_ab + 77, Abteilung, sizeof(Abteilung));
			TextOut(hdc, Seiten_ab, Top_ab + 127, Arbeit, sizeof(Arbeit));
			EndPaint(hWnd, &ps);
			return 0;

		//Zusatzfenster erstellen
		case WM_CREATE:

			//Texteingabefelder
			for (int i = 0; i < Fragenanzahl; i++) {
				eingabefelder[i] = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, Seiten_ab, Top_ab + (i*Zeilenabstand), Eingabefeldlänge, Eingabefeldhöhe, hWnd, NULL, NULL, NULL);
			}

			//Buttons erstellen
			CreateWindow("BUTTON", "Bestätigen", WS_BORDER | WS_CHILD | WS_VISIBLE, Width - 2 * (Width / 14), Height - 2 * (Height / 8.5), Width / 9, Height / 9, hWnd, (HMENU)1, NULL, NULL);
		return 0;

		//Tastertur einagbe
		case WM_CHAR:
			switch (wParam) {
				case  VK_RETURN:

				break;
			}
		//break of Key-Reaction
			break;

		//Reaction definieren
		case WM_COMMAND:
			//Button reaktion
			switch (LOWORD(wParam)) {
			case 1:
				//Test : steht etwas in dem Eingabefeld
				for (int i = 0; i < Fragenanzahl; i++) {

					//Prüfen ob etwas im Texteingabefeld steht --> Checkvariable = 0
					if (!GetWindowText(eingabefelder[i], &eingabe[i][0], Eingabefeldlänge)) {
						check_eingabe = 0;
						i = Fragenanzahl;

						//Wenn etwas in dem Texteingabefeld steht steigt die Checkvariable an
					}
					else {
						check_eingabe++;
					}
				}

				//Wenn die Checkbvariable = 0 ist (Zurück)
				if (!check_eingabe) {
					::MessageBox(hWnd, Fehler, "Achtung", MB_OK | MB_ICONEXCLAMATION);

					//Wenn die Checkvariable != 0 ist (Weiter)
				}
				else {
					//verarbeiten();
					int antwort = ::MessageBox(hWnd, "Vielen Dank für die Informationen\n\nWenn sie noch eine Kartei anlgen wollen drücken sie bitte auf 'Ja'.\n\nUm den Vorgang zu Beenden drücken sie bitte auf 'NEIN'\n\nMöchten sie die Erstellung der aktuellen Datei abbrechen drücken sie bitte auf 'Schließen'", "Danke", MB_YESNOCANCEL | MB_ICONINFORMATION);
					switch (antwort) {

						//Erstellt die Kartei und lässt das Fenster offen für eine weitere erstellung einer Kartei
						case IDYES:
							Text_Data::Text_Data(eingabe);
						break;

						//Funktion Verarbeiten wird ausgeführt
						case IDNO:
							Text_Data::Text_Data(eingabe);
							PostQuitMessage(0);
						break;

						//Beende den Vorgang bevor die Kartei erstellt wird
						case IDCANCEL:
							PostQuitMessage(0);
						break;

					}
					//break of Case 1:
					break;
				//Else Ende
				}
			//Switch Ende
			}
		//return of Case WM_COMMAND
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}