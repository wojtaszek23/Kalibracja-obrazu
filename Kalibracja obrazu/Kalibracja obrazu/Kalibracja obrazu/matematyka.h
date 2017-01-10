#ifndef MATEMATYKA_H
#define MATEMATYKA_H

#include <math.h> 
int przyblizenie_wartosci(float liczba_zmiennoprzecinkowa)
	{
		int liczba_calkowita=int(liczba_zmiennoprzecinkowa);
		float reszta= liczba_zmiennoprzecinkowa- float(liczba_calkowita);
		if(reszta>=0.5) liczba_calkowita++;
		return liczba_calkowita;
	}

class Odcinek
{
private:
	bool zmienna_x1,zmienna_x2,zmienna_y1,zmienna_y2,zmienna_l,zmienna_h,zmienna_a,zmienna_b,zmienna_dlugosc;
	int x1;
	int y1;
	int x2;
	int y2;
	int l;
	int h;
	float a;
	float b;
	float dlugosc;

public:
	
	int przyblizenie_wartosci(float liczba_zmiennoprzecinkowa)
	{
		int liczba_calkowita=int(liczba_zmiennoprzecinkowa);
		float reszta= liczba_zmiennoprzecinkowa- float(liczba_calkowita);
		if(reszta>=0.5) liczba_calkowita++;
		return liczba_calkowita;
	}

	float Oblicz_a()
	{
		if(x1-x2==0) 
		{a=0;}
		else
		{
		a=float(y1-y2)/float(x1-x2);
		};
		zmienna_a=true;
		return a;
	}
	
	float Oblicz_b()
	{
		b=y1-a*x1;
		zmienna_b=true;
		return b;
	}
	
	int Oblicz_l()
	{
		l=x2-x1;
		zmienna_l=true;
		return l;
	}
	
	int Oblicz_h()
	{
		h=y2-y1;
		zmienna_h=true;
		return h;
	}
	
	float Oblicz_dlugosc()
	{
		dlugosc=sqrt(float((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
		zmienna_dlugosc=true;
		return dlugosc;
	}

	void UstawParametry(int X1, int Y1, int X2, int Y2)
	{
		x1=X1;
		zmienna_x1=true;
		y1=Y1;
		zmienna_y1=true;
		x2=X2;
		zmienna_x2=true;
		y2=Y2;
		zmienna_y2=true;
		Oblicz_a();
		Oblicz_b();
		Oblicz_l();
		Oblicz_h();
		Oblicz_dlugosc();
	}
	Odcinek()
	{
		a=b=dlugosc=0;
		x1=x2=y1=y2=l=h=0;
		a=b=0;
		Parametry(false);
	}

	bool Parametry(bool wartosc)
	{
		zmienna_x1=zmienna_x2=zmienna_y1=zmienna_y2=zmienna_l=zmienna_h=zmienna_a=zmienna_b=zmienna_dlugosc=wartosc;
		return wartosc;
	}
	
	Odcinek(int X1, int Y1, int X2, int Y2)
	{
		UstawParametry(X1,Y1,X2,Y2);
	}
	int get_x1()
	{
		return x1;
	}
	int get_y1()
	{
		return y1;
	}
	int get_x2()
	{
		return x2;
	}
	int get_y2()
	{
		return y2;
	}
	float get_a()
	{
		if(zmienna_a==false) {Oblicz_a();}
		return a;
	}
	float get_b()
	{
		if(zmienna_b==false) Oblicz_b();
		return b;
	}
	int get_l()
	{
		if(zmienna_l==false) Oblicz_l();
		return l;
	}
	
	int get_h()
	{
		if(zmienna_h==false) Oblicz_h();
		return h;
	}
	float get_dlugosc()
	{
		if(zmienna_dlugosc==false) Oblicz_dlugosc();
		return dlugosc;
	}
	int Oblicz_x(int y)
	{
		if(x1==x2) 
		{
		return x1;
		}
		else
		{
		float X=(float(y)-b)/a;
		int x=int(X);
		return x;
		};
	}
};



#endif