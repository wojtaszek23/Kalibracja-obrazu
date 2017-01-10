
#include <windows.h>
#include <math.h> 
#include <stdio.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "matematyka.h"
#include "operacje.h"


using namespace std;
using namespace cv;

//bool przetwarzanie=false; //zostawic to na po oddaniu pracy inzynierskiej

LPSTR NazwaKlasy = "Klasa Okienka";
LPSTR NazwaKlasy2 = "Klasa Okienka2";
LPSTR NazwaKlasy3 = "Klasa Okienka3";

LPSTR Rzutowanie = "Rzutowanie"; 
LPSTR Negatyw = "Negatyw";
LPSTR KonwersjaRGB= "Konwersja RGB";
LPSTR Kontrast= "Kontrast";
LPSTR SkalaSzarosci= "Skala szaroúci";
LPSTR ZmianaRozmiaru= "Zmiana rozmiaru";
LPSTR Rotacja= "Rotacja prostokπtna";


MSG Komunikat;
HWND UchwytOknaAplikacji;
HWND UchwytOknaRzutowania;
HWND UchwytEtykietaR[4];
HWND UchwytRozdzielczosc[6];
HWND UchwytRozdzielczoscOk;
HWND UchwytOknoNazw;
HWND UchwytOknoOperacji;
HWND UchwytRzutowanie;
HWND UchwytPrzyciskPlikiOdczytPlik;
HWND UchwytPrzyciskPlikiOdczytPliki;
HWND UchwytPrzyciskPlikiZapis;
HWND UchwytPrzyciskPlikiZaladowaniePliku;
HWND UchwytPrzyciskAutorzy;
HWND UchwytPrzyciskPomoc;
HWND UchwytIloscPlikow;
HWND UchwytRadio[13];
HWND UchwytRadio2[6];
HWND UchwytCzyszczenie;
HWND UchwytKontury[12];
HWND UchwytWymiary[5];
HWND UchwytZmianaKonturow;
/*
//zostawic to na po oddaniu pracy
HWND UchwytOknaPrzetwarzania;
HWND UchwytZapisane;
HWND UchwytDoZapisu;
HWND UchwytObecnaSciezka;
HWND UchwytPrzyciskPrzetwarzanie1;
HWND UchwytPrzyciskPrzetwarzanie2;
HFONT UchwytCzcionka;
*/


HDC hdcRzutowania;
HDC hdcAplikacji;
//HDC hdcPrzetwarzania; //zostawic to na po oddaniu pracy inzynierskiej



const int ID_CHECKBOX=1;
const int ID_BUTTON=2;
const int ID_EDIT[6]={3, 4, 5, 6, 15, 16};
const int ID_BUTTON2=7;
const int ID_BUTTON3=8;
const int ID_BUTTON4=9;
const int ID_COMBOBOX=10;
const int ID_BUTTON5=11;
const int ID_BUTTON6=12;
const int ID_BUTTON7=13;
const int ID_EDIT5=14;
const int ID_RADIO[7]={17, 18, 19, 20, 21, 22, 23};
const int ID_BUTTON8= 30;
const int ID_RADIO2[6]={31, 32, 33, 34, 35, 36};
const int ID_EDIT2[12]={37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48};
const int ID_EDIT3[5]={49, 50, 51, 52, 53};
const int ID_BUTTON9=54;
const int ID_EDIT21=55;
const int ID_EDIT22=56;
const int ID_EDIT23=57;
const int ID_BUTTON21=58;
const int ID_BUTTON22=59;


//POINT pozycja;
int rozdzielczosc[4];
POINT punkty[6];
int iloscPunktow=0;
int limitPunktow=6;
int liczbaObrazow;
int liczba1=0;
int liczba2=0;
int index_pc1=-1;//poczatek cyfr
int index_pc2=-1;//poczatek cyfr
int index_kropka1=-1;
int index_kropka2=-1;
unsigned int iloscPlikow;
POINT staryPkt;
HPEN Kontur, DomyslnePioro;

HBITMAP hbmTest;
BITMAP bmTest;

char nazwaPliku1[MAX_PATH] = {0};
char nazwaPliku2[MAX_PATH]= {0};
char wybor=-1;



CvMat* Macierz;
Mat* Macierz_zrodlo;
Mat* Macierz_cel;


POINT A, B, C, D, E, F, a, b, c, d, e, f;

void Obl_index_kropka1()
{
		//zczytanie indexu dla kropki, tylko za pierwszym razem, po wybraniu sciezek plikow
	for(int i=0;i<MAX_PATH;i++)
	{
		if(nazwaPliku1[i]==0)
		{
		for(int j=i-1;j>=0;j--)
		{
			if(nazwaPliku1[j]=='.')
			{
				index_kropka1=j;
				break;
			}
		}
		break;
		}
	}
}

void Obl_index_kropka2()
{
		//zczytanie indexu dla kropki, tylko za pierwszym razem, po wybraniu sciezek plikow
	for(int i=0;i<MAX_PATH;i++)
	{
		if(nazwaPliku2[i]==0)
		{
		for(int j=i-1;j>=0;j--)
		{
			if(nazwaPliku2[j]=='.')
			{
				index_kropka2=j;
				break;
			}
		}
		break;
		}
	}
}
void Obl_liczba_cyfry1()
{
	//zczytanie indexu dla pierwszej cyfry, tylko za pierwszym razem, po wybraniu sciezek plikow
	int z=1;
	for(int k=index_kropka1-1;k>=0;k--)
	{
		if(!(nazwaPliku1[k]>=48&&nazwaPliku1[k]<=57))
			{
				for(int l=index_kropka1-1;l>k;l--)
					{
						liczba1=liczba1+(nazwaPliku1[l]-48)*z;
						z=z*10;
					}
			index_pc1=k+1;
			break;
			}
	}
}

void Obl_liczba_cyfry2()
{
	//zczytanie indexu dla pierwszej cyfry, tylko za pierwszym razem, po wybraniu sciezek plikow
	int z=1;
	for(int k=index_kropka2-1;k>=0;k--)
	{
		if(!(nazwaPliku2[k]>=48&&nazwaPliku2[k]<=57))
			{
				for(int l=index_kropka2-1;l>k;l--)
					{
						liczba2=liczba2+(nazwaPliku2[l]-48)*z;
						z=z*10;
					}
			index_pc2=k+1;
			break;
			}
	}
}
void Obl_cyfra_znak1()
{
	//konwersja liczby w nazwie sciezki do pliku, z uwzglednieniem poczatku i konca ciagu cyfr
	for(int i=index_kropka1-1;i>=index_pc1;i--)
	{
		nazwaPliku1[i]=liczba1%10+48;
		liczba1=liczba1/10;	
	}
}


void Obl_cyfra_znak2()
{
	//konwersja liczby w nazwie sciezki do pliku, z uwzglednieniem poczatku i konca ciagu cyfr
	for(int i=index_kropka2-1;i>=index_pc2;i--)
	{
		nazwaPliku2[i]=liczba2%10+48;
		liczba2=liczba2/10;	
	}
}


void Ustawianie()
{
	iloscPunktow=0;
	ShowWindow(UchwytZmianaKonturow,SW_HIDE);
	for(int i=0;i<6;i++)
	{
	ShowWindow( UchwytRadio2[i], SW_HIDE );
	SendMessage( UchwytRadio2[i], BM_SETCHECK, BST_UNCHECKED, NULL );
	};
	for(int i=0;i<12;i++)
	{
		SetWindowText(UchwytKontury[i],"");
		ShowWindow(UchwytKontury[i],SW_HIDE);
	};
	for(int i=0;i<5;i++)
	{
		SetWindowText(UchwytWymiary[i],"");
		ShowWindow(UchwytWymiary[i],SW_HIDE);
	};
	if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_CHECKBOX))
	{
		ShowWindow(UchwytOknaRzutowania,SW_HIDE);
		ShowWindow(UchwytOknaRzutowania,SW_SHOW);
	}
	UpdateWindow(UchwytOknaAplikacji);
}



LRESULT CALLBACK ObslugaOknaAplikacji(HWND UchwytOkna, UINT zdarzenie, WPARAM klawisz, LPARAM mysz);
LRESULT CALLBACK ObslugaOknaRzutowania(HWND UchwytOkna, UINT zdarzenie, WPARAM klawisz, LPARAM mysz);
//LRESULT CALLBACK ObslugaOknaPrzetwarzania(HWND UchwytOkna, UINT zdarzenie, WPARAM klawisz, LPARAM mysz);//zostawic na po oddaniu pracy inzynierskiej


WNDCLASSEX KlasaOkna(WNDPROC obslZdarz, HINSTANCE instancjaProgramu, int ikona, 
					 HCURSOR kursor, HBRUSH tlo, LPCTSTR menu, LPCTSTR nazwaKlasy, int ikonka)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = 0;
	wc.lpfnWndProc = obslZdarz;
	wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instancjaProgramu;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = tlo;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = nazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );    
	RegisterClassEx( & wc );
	return wc;
};

void WyborNazwyPlikuOdczyt()
{
  OPENFILENAME struktura = {0};
  char aktualnyFolder[MAX_PATH] = {0};
  
 
  GetCurrentDirectory(MAX_PATH, aktualnyFolder);
 
  struktura.lStructSize = sizeof(OPENFILENAME);
  struktura.hwndOwner = GetDesktopWindow();
  struktura.lpstrFile = nazwaPliku1;
  struktura.nMaxFile = MAX_PATH;
  struktura.lpstrInitialDir = aktualnyFolder;
  struktura.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT;
 
  GetOpenFileName(&struktura);
  SendMessage( UchwytOknoNazw, CB_ADDSTRING, 0, (LPARAM) nazwaPliku1 );
}

void WyborNazwyPlikuZapis()
{
  OPENFILENAME struktura = {0};
  char aktualnyFolder[MAX_PATH] = {0};

  GetCurrentDirectory(MAX_PATH, aktualnyFolder);
 
  struktura.lStructSize = sizeof(OPENFILENAME);
  struktura.hwndOwner = GetDesktopWindow();
  struktura.lpstrFile = nazwaPliku2;
  struktura.nMaxFile = MAX_PATH;
  struktura.lpstrInitialDir = aktualnyFolder;
  struktura.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_PATHMUSTEXIST;
 
  if (GetSaveFileName(&struktura))
   MessageBox(GetDesktopWindow(), nazwaPliku2, "Wybrano", MB_OK);
}

 
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	punkty[0].x=punkty[0].y=-10;
	HBRUSH tloAplikacji= CreateSolidBrush( RGB(128,128,128) );//( RGB(50,200,120) ); //( RGB(80,150,220));
	HBRUSH tloRzutowania= CreateSolidBrush( RGB(0,0,0));
	//HBRUSH tloPrzetwarzania= CreateSolidBrush( RGB(80,150,220) );//zostawic to na po oddaniu pracy inzynierskiej	

	WNDCLASSEX ObiektKlasyOkna1= KlasaOkna(ObslugaOknaAplikacji,hInstance,NULL,NULL,tloAplikacji,NULL,NazwaKlasy,NULL);	
	WNDCLASSEX ObiektKlasyOkna2= KlasaOkna(ObslugaOknaRzutowania,hInstance,NULL,NULL,tloRzutowania,NULL,NazwaKlasy2,NULL);
	//WNDCLASSEX ObiektKlasyOkna3= KlasaOkna(ObslugaOknaPrzetwarzania,hInstance,NULL,NULL,tloPrzetwarzania,NULL,NazwaKlasy3,NULL);
	//zostawic to na po oddaniu pracy inzynierskiej

	UchwytOknaAplikacji= CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Kalibracja obrazu", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
    50, 50, 750, 550, NULL, NULL, hInstance, NULL );

	UchwytOknaRzutowania=CreateWindowEx( NULL, NazwaKlasy2, "", WS_POPUP,
    rozdzielczosc[0], rozdzielczosc[1], rozdzielczosc[2], rozdzielczosc[3], NULL, NULL, hInstance, NULL );

//	UchwytOknaPrzetwarzania= CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy3, "Przetwarzanie obrazÛw", WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX ,
//    50, 50, 750, 550, NULL, NULL, hInstance, NULL );    //zostawic to na po oddaniu pracy inzynierskiej

	UchwytRozdzielczosc[0]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,570,400,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT[0],hInstance,NULL);
	UchwytRozdzielczosc[1]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,650,400,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT[1],hInstance,NULL);
	UchwytRozdzielczosc[2]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,570,440,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT[2],hInstance,NULL);
	UchwytRozdzielczosc[3]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,650,440,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT[3],hInstance,NULL);
	
	UchwytRozdzielczosc[4]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED|WS_BORDER|ES_READONLY,
		25,470,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT[4],hInstance,NULL);
	UchwytRozdzielczosc[5]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED|WS_BORDER|ES_READONLY,
		100,470,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT[5],hInstance,NULL);
	
	UchwytRozdzielczoscOk= CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","Zatwierdzenie rozdzielczoúci",WS_CHILD|WS_VISIBLE|WS_BORDER,
		505,475,200,25,UchwytOknaAplikacji,(HMENU) ID_BUTTON,hInstance,NULL);

	UchwytRzutowanie= CreateWindowEx(NULL,"BUTTON",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|BS_CHECKBOX,680,375,15,15,UchwytOknaAplikacji,(HMENU) ID_CHECKBOX,hInstance,NULL);
	
	UchwytKontury[0]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,610,135,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[0],hInstance,NULL);

	UchwytKontury[1]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,685,135,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[1],hInstance,NULL);
	
	UchwytKontury[2]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,610,175,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[2],hInstance,NULL);

	UchwytKontury[3]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,685,175,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[3],hInstance,NULL);

	UchwytKontury[4]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,610,215,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[4],hInstance,NULL);

	UchwytKontury[5]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,685,215,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[5],hInstance,NULL);

	UchwytKontury[6]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,610,255,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[6],hInstance,NULL);

	UchwytKontury[7]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,685,255,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[7],hInstance,NULL);

	UchwytKontury[8]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,610,295,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[8],hInstance,NULL);

	UchwytKontury[9]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,685,295,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[9],hInstance,NULL);

	UchwytKontury[10]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,610,335,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[10],hInstance,NULL);

	UchwytKontury[11]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,685,335,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT2[11],hInstance,NULL);

	UchwytWymiary[0]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,400,225,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT3[0],hInstance,NULL);

	UchwytWymiary[1]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,480,225,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT3[1],hInstance,NULL);

	UchwytWymiary[2]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,400,275,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT3[2],hInstance,NULL);

	UchwytWymiary[3]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,480,275,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT3[3],hInstance,NULL);

	UchwytWymiary[4]=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,400,325,40,20,UchwytOknaAplikacji,(HMENU) ID_EDIT3[4],hInstance,NULL);

	UchwytZmianaKonturow=CreateWindowEx(NULL,"BUTTON","Zmiana konturÛw",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_MULTILINE,
		460,315,75,40,UchwytOknaAplikacji,(HMENU) ID_BUTTON9,hInstance,NULL);

			ShowWindow(UchwytZmianaKonturow,SW_HIDE);

				for(int i=0;i<12;i++)
			{
				ShowWindow(UchwytKontury[i],SW_HIDE);
			}

				for(int i=0;i<5;i++)
			{
				ShowWindow(UchwytWymiary[i],SW_HIDE);
			}

	//UchwytOknoObrazow=CreateWindowEx(WS_EX_CLIENTEDGE,"LISTBOX",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,460,40,250,300,UchwytOknaAplikacji,NULL,hInstance,NULL);
	UchwytOknoNazw=CreateWindowEx(WS_EX_CLIENTEDGE,"COMBOBOX",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|CBS_DROPDOWN|CBS_AUTOHSCROLL,
		100,35,250,300,UchwytOknaAplikacji, (HMENU) ID_COMBOBOX,hInstance,NULL);
	//SendMessage( UchwytOknoNazw, CB_ADDSTRING, 0, (LPARAM) "sciezki zaladowanych nazw" );



	UchwytPrzyciskPlikiOdczytPlik=CreateWindowEx(NULL,"BUTTON","Za≥adowanie grafiki\ndo wyúwietlenia",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_MULTILINE,
		15,105,150,40,UchwytOknaAplikacji,(HMENU) ID_BUTTON2,hInstance,NULL);

	UchwytRadio[0]= CreateWindowEx(NULL, "BUTTON", Rzutowanie, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON|WS_GROUP, 
		200, 105, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[0], hInstance, NULL); 

	UchwytRadio[1]= CreateWindowEx(NULL, "BUTTON", KonwersjaRGB, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		200, 145, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[1], hInstance, NULL); 
	
	UchwytRadio[2]= CreateWindowEx(NULL, "BUTTON", Negatyw, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		200, 185, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[2], hInstance, NULL);

	UchwytRadio[3]= CreateWindowEx(NULL, "BUTTON", ZmianaRozmiaru, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		200, 225, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[3], hInstance, NULL);

	UchwytRadio[4]= CreateWindowEx(NULL, "BUTTON", Kontrast, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		200, 265, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[4], hInstance, NULL);

	UchwytRadio[5]= CreateWindowEx(NULL, "BUTTON", SkalaSzarosci, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		200, 305, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[5], hInstance, NULL);
	
	UchwytRadio[6]= CreateWindowEx(NULL, "BUTTON", Rotacja, WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		200, 345, 150, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO[6], hInstance, NULL);


	UchwytRadio2[0]= CreateWindowEx(NULL, "BUTTON", "", WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON|WS_GROUP, 
		370, 105, 155, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO2[0], hInstance, NULL);
	ShowWindow(UchwytRadio2[0],SW_HIDE);

	UchwytRadio2[1]= CreateWindowEx(NULL, "BUTTON", "", WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		370, 145, 155, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO2[1], hInstance, NULL);
	ShowWindow(UchwytRadio2[1],SW_HIDE);

	UchwytRadio2[2]= CreateWindowEx(NULL, "BUTTON", "", WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		370, 185, 155, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO2[2], hInstance, NULL);
	ShowWindow(UchwytRadio2[2],SW_HIDE);

	UchwytRadio2[3]= CreateWindowEx(NULL, "BUTTON", "", WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		370, 225, 155, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO2[3], hInstance, NULL);
	ShowWindow(UchwytRadio2[3],SW_HIDE);

	UchwytRadio2[4]= CreateWindowEx(NULL, "BUTTON", "", WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 
		370, 265, 155, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO2[4], hInstance, NULL);
	ShowWindow(UchwytRadio2[4],SW_HIDE);

	UchwytRadio2[5]= CreateWindowEx(NULL, "BUTTON", "", WS_CHILD|WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON|WS_TABSTOP, 
		370, 305, 155, 20, UchwytOknaAplikacji, (HMENU) ID_RADIO2[5], hInstance, NULL);
	ShowWindow(UchwytRadio2[5],SW_HIDE);
	

	UchwytPrzyciskPlikiOdczytPliki=CreateWindowEx(NULL,"BUTTON","£adowanie grafik\ndo operacji",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_MULTILINE,
		15,155,150,40,UchwytOknaAplikacji,(HMENU) ID_BUTTON7,hInstance,NULL);
	
	UchwytIloscPlikow= CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,60,200,50,20,UchwytOknaAplikacji,(HMENU) ID_EDIT5,hInstance,NULL);


	UchwytPrzyciskPlikiZapis=CreateWindowEx(NULL,"BUTTON","Wykonanie operacji i zapis do plikÛw",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_MULTILINE,
		15,230,150,40,UchwytOknaAplikacji,(HMENU) ID_BUTTON3,hInstance,NULL);
	
	UchwytPrzyciskPlikiZaladowaniePliku=CreateWindowEx(NULL,"BUTTON","Zapis do pliku wyúwietlanej grafiki",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_MULTILINE,
		15,280,150,40,UchwytOknaAplikacji,(HMENU) ID_BUTTON4,hInstance,NULL);
	
	UchwytCzyszczenie=CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","Czyszczenie zawartoúci okna rzutowania",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_MULTILINE,
		15,340,150,60,UchwytOknaAplikacji,(HMENU) ID_BUTTON8,hInstance,NULL);

	/*
	UchwytZapisane=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_READONLY,305,100,70,25,UchwytOknaPrzetwarzania,
		(HMENU) ID_EDIT21, hInstance, NULL);

	UchwytDoZapisu=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_READONLY,430,100,70,25,UchwytOknaPrzetwarzania,
		(HMENU) ID_EDIT22, hInstance, NULL);

	UchwytObecnaSciezka=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_READONLY,150,250,430,25,UchwytOknaPrzetwarzania,
		(HMENU) ID_EDIT23, hInstance, NULL);

	UchwytPrzyciskPrzetwarzanie1=CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Przerwanie operacji", WS_CHILD|WS_VISIBLE|WS_BORDER,
		150, 350, 150, 25, UchwytOknaPrzetwarzania, (HMENU) ID_BUTTON21, hInstance, NULL);

	UchwytPrzyciskPrzetwarzanie2=CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "OK", WS_CHILD|WS_VISIBLE|WS_BORDER,
		350, 350, 150, 25, UchwytOknaPrzetwarzania, (HMENU) ID_BUTTON22, hInstance, NULL);

	ShowWindow(UchwytPrzyciskPrzetwarzanie2,SW_HIDE);
	//zostawic to na po oddaniu pracy inzynierskiej
	*/
	
	
	UchwytPrzyciskAutorzy=CreateWindowEx(NULL,"BUTTON","Autorzy",WS_CHILD|WS_VISIBLE|WS_BORDER,15,10,60,20,UchwytOknaAplikacji,(HMENU) ID_BUTTON5,hInstance,NULL);
	UchwytPrzyciskPomoc=CreateWindowEx(NULL,"BUTTON","Pomoc",WS_CHILD|WS_VISIBLE|WS_BORDER,15,40,60,20,UchwytOknaAplikacji,(HMENU) ID_BUTTON6,hInstance,NULL);

	//
	SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT[0],0,false);
	SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT[1],0,false);
	SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT[2],0,false);
	SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT[3],0,false);
	SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT5,1,false);
	//

	hdcAplikacji=GetDC(UchwytOknaAplikacji);
	//hdcPrzetwarzania=GetDC(UchwytOknaPrzetwarzania);//zostawic to na po oddaniu pracy inzynierskiej

	ShowWindow(UchwytOknaAplikacji,nCmdShow);
	UpdateWindow(UchwytOknaAplikacji);
	ShowWindow(UchwytOknaRzutowania,SW_HIDE);
	UpdateWindow(UchwytOknaRzutowania);
	hdcRzutowania = GetDC(UchwytOknaRzutowania);
	//ShowWindow(UchwytOknaPrzetwarzania,SW_HIDE);//zostawic to na po oddaniu pracy inzynierskiej
	//UpdateWindow(UchwytOknaPrzetwarzania);
				
	Kontur = CreatePen( PS_SOLID, 2, 0xFF00FF );
	
	

		while( GetMessage( & Komunikat, NULL, 0, 0 ) )
		{			
			TranslateMessage( & Komunikat );
			DispatchMessage( & Komunikat );
		}

		DeleteObject(tloAplikacji);
		DeleteObject(tloRzutowania);
    return Komunikat.wParam;
}

LRESULT CALLBACK ObslugaOknaAplikacji(HWND UchwytOkna, UINT zdarzenie, WPARAM klawisz, LPARAM mysz)
{
	switch(zdarzenie)
	{


		case WM_MOUSEMOVE:
			SetWindowText(UchwytRozdzielczosc[4],"");
			SetWindowText(UchwytRozdzielczosc[5],"");			
		break;

		case WM_COMMAND:
			
			switch(klawisz)
			{
				
				case ID_BUTTON9:
					for(int i=0;i<=iloscPunktow;i++)
						{
						punkty[i].x=GetDlgItemInt(UchwytOknaAplikacji,ID_EDIT2[2*i],NULL,false);
						punkty[i].y=GetDlgItemInt(UchwytOknaAplikacji,ID_EDIT2[2*i+1],NULL,false);
						};
					if(IsDlgButtonChecked(UchwytOkna,ID_CHECKBOX))
					{
						ShowWindow(UchwytOknaRzutowania,SW_HIDE);
						ShowWindow(UchwytOknaRzutowania,SW_SHOW);
						UpdateWindow(UchwytOknaRzutowania);
					}					
				break;

				case 17://ID_RADIO[0]=17
					Ustawianie();
					 ShowWindow(UchwytRadio2[0],SW_SHOW);
					SetWindowText(UchwytRadio2[0],"Kalibracja 4pkt");
					 ShowWindow(UchwytRadio2[1],SW_SHOW);
					SetWindowText(UchwytRadio2[1],"Kalibracja 6pkt");
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);				
				break;

				case 18://ID_RADIO[1]=18
					Ustawianie();
					 ShowWindow(UchwytRadio2[0],SW_SHOW);
					SetWindowText(UchwytRadio2[0],"    R=>B | B=>R");
					 ShowWindow(UchwytRadio2[1],SW_SHOW);
					SetWindowText(UchwytRadio2[1],"    G=>B | B=>G");
					 ShowWindow(UchwytRadio2[2],SW_SHOW);
					SetWindowText(UchwytRadio2[2],"    R=>G | G=>R");
					 ShowWindow(UchwytRadio2[3],SW_SHOW);
					SetWindowText(UchwytRadio2[3],"R=>G | G=>B | B=>R");
					 ShowWindow(UchwytRadio2[4],SW_SHOW);
					SetWindowText(UchwytRadio2[4],"R=>B | B=>G | G=>R");
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;

				case 19:
					//MessageBox(NULL,"negatyw",NULL,NULL);
					wybor=7;
					Ustawianie();
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;

				case 20:
					//MessageBox(NULL,"zmiana rozmiaru",NULL,NULL);
					wybor=8;
					Ustawianie();
					ShowWindow(UchwytWymiary[0],SW_SHOW);
					ShowWindow(UchwytWymiary[1],SW_SHOW);
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;

				case 21:
					//MessageBox(NULL,"kontrast",NULL,NULL);
					wybor=9;
					Ustawianie();
					ShowWindow(UchwytWymiary[1],SW_SHOW);
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;

				case 22:
					//MessageBox(NULL,"skala szaroúci",NULL,NULL);
					wybor= 10;
					Ustawianie();	
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;
				
				case 23:
					//MessageBox(NULL,"rotacja prostokπtna",NULL,NULL);
					wybor=11;
					Ustawianie();
					ShowWindow(UchwytRadio2[0],SW_SHOW);
					SetWindowText(UchwytRadio2[0],"ObrÛt w prawo o 90");
					 ShowWindow(UchwytRadio2[1],SW_SHOW);
					SetWindowText(UchwytRadio2[1],"ObrÛt w lewo o 90");
					 ShowWindow(UchwytRadio2[2],SW_SHOW);
					SetWindowText(UchwytRadio2[2],"ObrÛt o 180");
					 ShowWindow(UchwytRadio2[3],SW_SHOW);
					SetWindowText(UchwytRadio2[3],"ObrÛt wokÛ≥ X");
					ShowWindow(UchwytRadio2[4],SW_SHOW);
					SetWindowText(UchwytRadio2[4],"ObrÛt wokÛ≥ Y");
					ShowWindow(UchwytRadio2[5],SW_SHOW);
					SetWindowText(UchwytRadio2[5],"ObrÛt wokÛ≥ XY");
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;
				
				case 31:
					
					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[0]))
					{
						if(IsDlgButtonChecked(UchwytOkna,ID_CHECKBOX))
						{
							ShowWindow(UchwytOknaRzutowania,SW_HIDE);
							ShowWindow(UchwytOknaRzutowania,SW_SHOW);
						};
						wybor=0;
						limitPunktow=4;
						for(int i=0;i<8;i++)
							{
							ShowWindow(UchwytKontury[i],SW_SHOW);
							};
						for(int i=8;i<12;i++)
							{
							ShowWindow(UchwytKontury[i],SW_HIDE);
							}
						for(int i=0;i<4;i++)
							{
							ShowWindow(UchwytWymiary[i],SW_SHOW);
							}
							ShowWindow(UchwytWymiary[4],SW_HIDE);
							ShowWindow(UchwytZmianaKonturow,SW_SHOW);
					};
					
					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[1]))
					{
						wybor=2;
					};
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break; 

				case 32: //ID_RADIO2[1]
					
					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[0]))
					{
						if(IsDlgButtonChecked(UchwytOkna,ID_CHECKBOX))
						{
							ShowWindow(UchwytOknaRzutowania,SW_HIDE);
							ShowWindow(UchwytOknaRzutowania,SW_SHOW);
						};
						wybor=1;
						limitPunktow=6;
						for(int i=0;i<12;i++)
						{
						ShowWindow(UchwytKontury[i],SW_SHOW);
						}
					
						for(int i=0;i<5;i++)
						{
						ShowWindow(UchwytWymiary[i],SW_SHOW);
						}
					ShowWindow(UchwytZmianaKonturow,SW_SHOW);
					};

					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[1]))
					{
						wybor=3;
					};
					
					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;

				case 33:
					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[1]))
					{
						wybor=4;
					};

					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;
				
				case 34:
					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[1]))
					{
						wybor=5;
					};

					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;

				case 35:
					if(IsDlgButtonChecked(UchwytOkna,ID_RADIO[1]))
					{
						wybor=6;
					};

					ShowWindow(UchwytOkna,SW_SHOWMINIMIZED);
					ShowWindow(UchwytOkna,SW_SHOWNORMAL);
				break;


				case ID_CHECKBOX:
				
					if(!IsDlgButtonChecked(UchwytOkna,ID_CHECKBOX))
					{
						CheckDlgButton( UchwytOkna, ID_CHECKBOX, BST_CHECKED );
						ShowWindow(UchwytOknaRzutowania,SW_SHOW);
						UpdateWindow(UchwytOknaRzutowania);
					}
					else
					{
						CheckDlgButton( UchwytOkna, ID_CHECKBOX, BST_UNCHECKED );
						ShowWindow(UchwytOknaRzutowania,SW_HIDE);
						UpdateWindow(UchwytOknaRzutowania);
					};
				break;

				case ID_BUTTON:
					
					for(int i=0;i<4;i++)
					{
						rozdzielczosc[i]=GetDlgItemInt(UchwytOkna,ID_EDIT[i],NULL,false);
					}
					SetWindowPos(UchwytOknaRzutowania, HWND(0),rozdzielczosc[0],rozdzielczosc[1],rozdzielczosc[2],rozdzielczosc[3],NULL);

				break;
				
				case ID_BUTTON2:
					WyborNazwyPlikuOdczyt();
				break;
			
				case ID_BUTTON3:
					GetWindowText(UchwytOknoNazw,nazwaPliku1,MAX_PATH);                    //wybrana w innym miejscu sciezka do ladowanego pliku

					if(nazwaPliku1[0]==0)
					{
						MessageBox(NULL,"Przed wykonaniem operacji naleøy wybraÊ ürÛd≥owπ úcieøkÍ pliku graficznego","Uwaga",NULL);
						break;
					}
					iloscPlikow=GetDlgItemInt(UchwytOknaAplikacji,ID_EDIT5,NULL,false);    //ilosc obrazow do operacji
					WyborNazwyPlikuZapis();             //funkcja opdowiadajaca za wybranie nazwy pliku do zapisu, gotowy szablon winapi
					Obl_index_kropka1();                //index dla kropki przed rozszerzeniem
					Obl_index_kropka2();
					Obl_liczba_cyfry1();                //opisane ponizej w komentarzu, ale nieistotne
					Obl_liczba_cyfry2();


					for(unsigned int i=0;i<=iloscPlikow;i++)
					{
					//SetDlgItemInt(UchwytOknaPrzetwarzania,ID_EDIT22,iloscPlikow,false);//zostawic to na po oddaniu pracy inzynierskiej
					//SetWindowText( UchwytObecnaSciezka, nazwaPliku1 );
					//przetwarzanie=true;
					//ShowWindow(UchwytOkna,SW_HIDE);
					//ShowWindow(UchwytOknaPrzetwarzania,SW_SHOW);

					Macierz = cvLoadImageM(nazwaPliku1,1); 
					Macierz_zrodlo=new cv::Mat(Macierz,true);
					Macierz_zrodlo->convertTo(*Macierz_zrodlo,CV_8UC3);
					Macierz_cel=new cv::Mat(Macierz_zrodlo->rows,Macierz_zrodlo->cols,Macierz_zrodlo->type(),cvScalarAll(0));
#pragma region operacje				
					switch(wybor)
					{
						case 0:
							
							A.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[0],NULL,false);
							A.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[1],NULL,false);
							B.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[2],NULL,false);
							B.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[3],NULL,false);
							C.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[4],NULL,false);
							C.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[5],NULL,false);
							D.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[6],NULL,false);
							D.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[7],NULL,false);
							
							a.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[0],NULL,false);
							a.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,false);
							b.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[0],NULL,false);
							b.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[3],NULL,false);
							c.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[2],NULL,false);
							c.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[3],NULL,false);
							d.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[2],NULL,false);
							d.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,false);
							Kalibracja( Macierz_zrodlo , Macierz_cel , A , B , C , D , a , b , c , d );
						break;
						
						case 1:
							A.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[0],NULL,false);
							A.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[1],NULL,false);
							B.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[2],NULL,false);
							B.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[3],NULL,false);
							C.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[4],NULL,false);
							C.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[5],NULL,false);
							F.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[6],NULL,false);
							F.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[7],NULL,false);
							E.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[8],NULL,false);
							E.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[9],NULL,false);
							D.x=GetDlgItemInt(UchwytOkna,ID_EDIT2[10],NULL,false);
							D.y=GetDlgItemInt(UchwytOkna,ID_EDIT2[11],NULL,false);

							a.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[0],NULL,false);
							a.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,false);
							b.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[0],NULL,false);
							b.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[3],NULL,false);
							c.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[4],NULL,false);
							c.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[3],NULL,false);
							d.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[4],NULL,false);
							d.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,false);
							e.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[2],NULL,false);
							e.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,false);
							f.x=GetDlgItemInt(UchwytOkna,ID_EDIT3[2],NULL,false);
							f.y=GetDlgItemInt(UchwytOkna,ID_EDIT3[3],NULL,false);
							Kalibracja_6pkt( Macierz_zrodlo , Macierz_cel , A , B , C , D , E , F , a , b , c , d , e , f );
						break;
						
						case 2:
							RBBR ( Macierz_zrodlo , Macierz_cel );
						break;

						case 3:
							GBBG ( Macierz_zrodlo , Macierz_cel );
						break;

						case 4:
							RGGR ( Macierz_zrodlo , Macierz_cel );
						break;

						case 5:
							RGGBBR ( Macierz_zrodlo , Macierz_cel );
						break;

						case 6:
							RBBGGR ( Macierz_zrodlo , Macierz_cel );
						break;

						case 7:
							negatyw( Macierz_zrodlo , Macierz_cel );
						break;

						case 8:
							Zmiana_Rozmiaru( Macierz_zrodlo, Macierz_cel, 
								GetDlgItemInt(UchwytOkna,ID_EDIT3[0],NULL,false),GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,false));
						break;

						case 9:
							kontrast ( Macierz_zrodlo, Macierz_cel, GetDlgItemInt(UchwytOkna,ID_EDIT3[1],NULL,true));
						break;

						case 10:
							Skala_Szarosci(Macierz_zrodlo, Macierz_cel);
						break;

						case 11:
							if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[0]))
							{
								Obrot_prawo_90 ( Macierz_zrodlo , Macierz_cel );
							};

							if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[1]))
							{
								Obrot_lewo_90 ( Macierz_zrodlo , Macierz_cel );
							};

							if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[2]))
							{
								Obrot_180 ( Macierz_zrodlo , Macierz_cel );
							};

							if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[3]))
							{
								Obrot_X ( Macierz_zrodlo , Macierz_cel );
							};

							if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[4]))
							{
								Obrot_Y ( Macierz_zrodlo , Macierz_cel );
							};

							if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[5]))
							{
								Obrot_XY ( Macierz_zrodlo , Macierz_cel );
							};

						break;
					};
					#pragma endregion
					*Macierz=*Macierz_cel;	

					cvSaveImage(nazwaPliku2,Macierz); //nazwaPliku2- nazwa zapisywanego
					//SetDlgItemInt(UchwytOknaPrzetwarzania,ID_EDIT21,i+1,false);//zostawic to na po oddaniu pracy inzynierskiej
					Macierz_zrodlo->release();//zwalnianie pamieci, wiadomo
					Macierz_cel->release();
					cvReleaseMat(&Macierz);
					Obl_cyfra_znak1();   //oblicza znaki z cyfr liczby, nieistotne
					Obl_cyfra_znak2();	 //-||-
					Obl_liczba_cyfry1(); //oblicza liczbe ze znakow cyfrowych, bo poprzednie 2 funkcje dzialaja na zmiennej liczba, tez nieistotne
					Obl_liczba_cyfry2(); //-||-					
					liczba1++;
					liczba2++;	
					
					//if(przetwarzanie==false) break;//zostawic to na po oddaniu pracy inzynierskiej
					
					};
					liczba1=0;
					liczba2=0;
				break;

				case ID_BUTTON4:   //zaladowanie pliku					
					//
					break;

				case ID_BUTTON5:
					
				break;
				
				case ID_BUTTON6:

				break;

				case ID_BUTTON7:
					WyborNazwyPlikuOdczyt();					
				break;
			}
			break;
#pragma region rysOknApl
		case WM_PAINT:
						
			PAINTSTRUCT ps;
			hdcAplikacji = BeginPaint(UchwytOkna, &ps);
			SetBkColor(hdcAplikacji, RGB(128,128,128));

			ExtTextOut(hdcAplikacji,402,400,NULL,NULL,"WspÛ≥rzÍdne rzutnika:   (",lstrlen("WspÛ≥rzÍdne rzutnika:   ("),NULL);
			ExtTextOut(hdcAplikacji,610,400,NULL,NULL,"X   :",lstrlen("X   :"),NULL);
			ExtTextOut(hdcAplikacji,690,400,NULL,NULL,"Y)",lstrlen("Y)"),NULL);
			ExtTextOut(hdcAplikacji,394,440,NULL,NULL,"RozdzielczoúÊ rzutnika:   (",lstrlen("RozdzielczoúÊ rzutnika:   ("),NULL);
			ExtTextOut(hdcAplikacji,610,440,NULL,NULL,"X   :",lstrlen("X   :"),NULL);
			ExtTextOut(hdcAplikacji,690,440,NULL,NULL,"Y)",lstrlen("Y)"),NULL);
			ExtTextOut(hdcAplikacji,100,10,NULL,NULL,"Wyszukane grafiki do operacji:",lstrlen("Wyszukane grafiki do operacji:"),NULL);
			ExtTextOut(hdcAplikacji,520,375,NULL,NULL,"Widoczne rzutowanie:",lstrlen("Widoczne Rzutowanie:"),NULL);
			ExtTextOut(hdcAplikacji,15,200,NULL,NULL,"IloúÊ:",lstrlen("IloúÊ:"),NULL);
			ExtTextOut(hdcAplikacji,20,420,NULL,NULL,"Pozycja myszy",lstrlen("Pozycja myszy"),NULL);
			ExtTextOut(hdcAplikacji,10,440,NULL,NULL,"na ekranie rzutowania:",lstrlen("na ekranie rzutowania:"),NULL);
			ExtTextOut(hdcAplikacji,10,470,NULL,NULL,"X:",lstrlen("X:"),NULL);
			ExtTextOut(hdcAplikacji,85,470,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			
			if(((IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[0])||IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[1]))&&IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO[0])))
			{

			ExtTextOut(hdcAplikacji,370,185,NULL,NULL,"èrÛd≥owy obraz:",lstrlen("èrÛd≥owy obraz:"),NULL);
			ExtTextOut(hdcAplikacji,370,205,NULL,NULL,"Poczπtek:",lstrlen("Poczπtek:"),NULL);
			ExtTextOut(hdcAplikacji,370,255,NULL,NULL,"Koniec:",lstrlen("Koniec:"),NULL);

			ExtTextOut(hdcAplikacji,535,105,NULL,NULL,"WspÛ≥rzÍdne wierzcho≥kÛw:",lstrlen("WspÛ≥rzÍdne wierzcho≥kÛw:"),NULL);
			
			ExtTextOut(hdcAplikacji,570,135,NULL,NULL,"A:  (X:",lstrlen("A:  (X:"),NULL);
			ExtTextOut(hdcAplikacji,670,135,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,728,135,NULL,NULL,")",lstrlen(")"),NULL);

			ExtTextOut(hdcAplikacji,570,175,NULL,NULL,"B:  (X:",lstrlen("B:  (X:"),NULL);
			ExtTextOut(hdcAplikacji,670,175,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,728,175,NULL,NULL,")",lstrlen(")"),NULL);

			ExtTextOut(hdcAplikacji,570,215,NULL,NULL,"C:  (X:",lstrlen("C:  (X:"),NULL);
			ExtTextOut(hdcAplikacji,670,215,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,728,215,NULL,NULL,")",lstrlen(")"),NULL);

			ExtTextOut(hdcAplikacji,570,255,NULL,NULL,"D:  (X:",lstrlen("D:  (X:"),NULL);
			ExtTextOut(hdcAplikacji,670,255,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,728,255,NULL,NULL,")",lstrlen(")"),NULL);

			ExtTextOut(hdcAplikacji,380,225,NULL,NULL,"X:",lstrlen("X:"),NULL);
			ExtTextOut(hdcAplikacji,460,225,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,380,275,NULL,NULL,"X:",lstrlen("X:"),NULL);
			ExtTextOut(hdcAplikacji,460,275,NULL,NULL,"Y:",lstrlen("Y:"),NULL);

			};

			if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO2[1])&&IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO[0]))
			{
			ExtTextOut(hdcAplikacji,370,305,NULL,NULL,"årodek:",lstrlen("årodek:"),NULL);
			ExtTextOut(hdcAplikacji,380,325,NULL,NULL,"X:",lstrlen("X:"),NULL);

			ExtTextOut(hdcAplikacji,570,295,NULL,NULL,"E:  (X:",lstrlen("E:  (X:"),NULL);
			ExtTextOut(hdcAplikacji,670,295,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,728,295,NULL,NULL,")",lstrlen(")"),NULL);

			ExtTextOut(hdcAplikacji,570,335,NULL,NULL,"F:  (X:",lstrlen("F:  (X:"),NULL);
			ExtTextOut(hdcAplikacji,670,335,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			ExtTextOut(hdcAplikacji,728,335,NULL,NULL,")",lstrlen(")"),NULL);
			};

			if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO[3]))
			{
			ExtTextOut(hdcAplikacji,390,135,NULL,NULL,"Nowe wymiary",lstrlen("Nowe wymiary:"),NULL);
			ExtTextOut(hdcAplikacji,390,175,NULL,NULL,"szerokoúci oraz wysokoúci:",lstrlen("szerokoúci oraz wysokoúci:"),NULL);
			ExtTextOut(hdcAplikacji,398,205,NULL,NULL,"X:",lstrlen("X:"),NULL);
			ExtTextOut(hdcAplikacji,475,205,NULL,NULL,"Y:",lstrlen("Y:"),NULL);
			};

			if(IsDlgButtonChecked(UchwytOknaAplikacji,ID_RADIO[4]))
			{
			ExtTextOut(hdcAplikacji,390,135,NULL,NULL,"WartoúÊ kontrastu",lstrlen("WartoúÊ kontrastu"),NULL);
			ExtTextOut(hdcAplikacji,390,165,NULL,NULL,"w zakresie od -255 do 255,",lstrlen("w zakresie od -255 do 255,"),NULL);
			ExtTextOut(hdcAplikacji,390,195,NULL,NULL,"gdzie 0 oznacza wartoúÊ domyúlnπ:",lstrlen("gdzie 0 oznacza wartoúÊ domyúlnπ:"),NULL);
			};

			EndPaint(UchwytOkna, &ps);	
		break;
#pragma endregion
		case WM_CLOSE:
			DestroyWindow(UchwytOknaRzutowania);
//			DestroyWindow(UchwytOknaPrzetwarzania); //zostawic to na po oddaniu pracy inzynierskiej
			DestroyWindow( UchwytOkna );
		break;
        
		case WM_DESTROY:
			SelectObject( hdcRzutowania, DomyslnePioro );
			DeleteObject( Kontur );
			ReleaseDC( UchwytOknaRzutowania, hdcRzutowania );
			PostQuitMessage( 0 );
		break;
        
		default:
			return DefWindowProc( UchwytOkna, zdarzenie, klawisz, mysz );
	}
	return 0;
}


LRESULT CALLBACK ObslugaOknaRzutowania(HWND UchwytOkna, UINT zdarzenie, WPARAM klawisz, LPARAM mysz)
{
	switch(zdarzenie)
	{	

		case WM_MOUSEMOVE:
			SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT[4],LOWORD(mysz),false);
			SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT[5],HIWORD(mysz),false);
		break;
		
		case WM_LBUTTONDOWN:
					if((wybor==0||wybor==1)&&iloscPunktow<=limitPunktow-1)
					{
						SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT2[2*iloscPunktow],LOWORD(mysz),false);
						SetDlgItemInt(UchwytOknaAplikacji,ID_EDIT2[2*iloscPunktow+1],HIWORD(mysz),false);
						punkty[iloscPunktow].x=GetDlgItemInt(UchwytOknaAplikacji,ID_EDIT2[2*iloscPunktow],NULL,false);
						punkty[iloscPunktow].y=GetDlgItemInt(UchwytOknaAplikacji,ID_EDIT2[2*iloscPunktow+1],NULL,false);
						iloscPunktow++;
						RedrawWindow(UchwytOkna,NULL,NULL,RDW_INVALIDATE);				
					}					
		break;
						
		case WM_PAINT:
			PAINTSTRUCT ps;
			hdcRzutowania = BeginPaint(UchwytOkna, &ps);
			DomyslnePioro =( HPEN ) SelectObject( hdcRzutowania, Kontur );

					if(wybor==0||wybor==1)
					{
						if(iloscPunktow>0)
						{
						SetPixel(hdcRzutowania,punkty[0].x-1, punkty[0].y-1,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x-1, punkty[0].y+1,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x-1, punkty[0].y,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x+1, punkty[0].y-1,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x, punkty[0].y-1,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x, punkty[0].y,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x+1, punkty[0].y,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x+1, punkty[0].y+1,0xFF00FF);
						SetPixel(hdcRzutowania,punkty[0].x, punkty[0].y+1,0xFF00FF);
						MoveToEx( hdcRzutowania, punkty[0].x, punkty[0].y, NULL );
						};		
							for(int i=0;i<iloscPunktow;i++)
							{
								if(i<limitPunktow)
								{
								LineTo( hdcRzutowania, punkty[i].x, punkty[i].y );	
								}
							}
							if(iloscPunktow==limitPunktow)
							{
								LineTo( hdcRzutowania, punkty[0].x, punkty[0].y );
								if(limitPunktow==6)
								{
								MoveToEx( hdcRzutowania, punkty[5].x, punkty[5].y, NULL );
								LineTo( hdcRzutowania, punkty[2].x, punkty[2].y );
								}
							}
					}
					
				EndPaint(UchwytOkna,&ps);
		break;
		

		default:
			return DefWindowProc( UchwytOkna, zdarzenie, klawisz, mysz );
	}
	return 0;
}

/*
//zostawic to na po oddaniu pracy inzynierskiej
LRESULT CALLBACK ObslugaOknaPrzetwarzania(HWND UchwytOkna, UINT zdarzenie, WPARAM klawisz, LPARAM mysz)
{
	switch (zdarzenie)
	{

		case WM_COMMAND:

			switch (klawisz)
			{
				case ID_BUTTON21:
					przetwarzanie=false;
					ShowWindow(UchwytOknaPrzetwarzania,SW_HIDE);
					ShowWindow(UchwytOknaAplikacji,SW_SHOW);
				break;
			
				case ID_BUTTON22:
					przetwarzanie=false;
					ShowWindow(UchwytOknaPrzetwarzania,SW_HIDE);
					ShowWindow(UchwytOknaAplikacji,SW_SHOW);
				break;
			}

			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			hdcPrzetwarzania = BeginPaint(UchwytOkna, &ps);
			SetBkColor(hdcPrzetwarzania, RGB(80,150,220));
            UchwytCzcionka = CreateFont(30, 15, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Arial");

			SelectObject(hdcPrzetwarzania, UchwytCzcionka);
			SendMessage (UchwytOkna, WM_SETFONT, WPARAM (UchwytCzcionka), TRUE);
			ExtTextOut(hdcPrzetwarzania,100,100,NULL,NULL,"Przetworzono",lstrlen("Przetworzono"),NULL);
			ExtTextOut(hdcPrzetwarzania,400,100,NULL,NULL,"z",lstrlen("z"),NULL);
			ExtTextOut(hdcPrzetwarzania,520,100,NULL,NULL,"plikÛw.",lstrlen("plikÛw."),NULL);
			ExtTextOut(hdcPrzetwarzania,150,200,NULL,NULL,"Aktualnie przetwarzany obraz:",lstrlen("Aktualnie przetwarzany obraz:"),NULL);
			DeleteObject(UchwytCzcionka);
			EndPaint(UchwytOkna,&ps);
		break;
		
		default:
			return DefWindowProc( UchwytOkna, zdarzenie, klawisz, mysz );
	}
	return 0;
}

*/




