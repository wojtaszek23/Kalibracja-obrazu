#ifndef OPERACJE_H
#define OPERACJE_H

#include <windows.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "matematyka.h"


using namespace std;
using namespace cv;

void Trojkat( Mat* Obraz_zrodlo, Mat* Obraz_cel, Odcinek A_C, Odcinek B_C, Odcinek AC, Odcinek BC )
{
	POINT pocz;
	POINT koniec;
	int get_x;
	int get_y;
	int krok;
	int liczba_krokow;
	int Y1;
	int Y2;
	bool pocz1_kon2=true;
	if(AC.get_x1()==AC.get_x2())
	{
		pocz1_kon2=false;
	}
	if(A_C.get_y2()<=A_C.get_y1())
	{
		Y1=A_C.get_y2();
		Y2=A_C.get_y1();
	}
	else
	{
		Y1=A_C.get_y1();
		Y2=A_C.get_y2();
	};
	if(pocz1_kon2==true)
	{
		for( int j= Y1; j<Y2; j++ )
		{
			liczba_krokow= B_C.Oblicz_x(j) - A_C.Oblicz_x(j);
			pocz.x= AC.get_x1() + przyblizenie_wartosci ( (AC.get_dlugosc()) * float ( float (A_C.Oblicz_x(j) - A_C.get_x1()) / float (A_C.get_l()) ) );
			koniec.y= BC.get_y1() + przyblizenie_wartosci ( (BC.get_dlugosc()) * float ( float (j - B_C.get_y1() ) / float (B_C.get_h()) ) );
			pocz.y= AC.get_y1();
			koniec.x= BC.get_x2();
			for(int i= A_C.Oblicz_x(j);i<=B_C.Oblicz_x(j);i++)
			{
				krok= i - A_C.Oblicz_x(j);
				get_x= pocz.x + przyblizenie_wartosci( ( float (( koniec.x - pocz.x ) * krok ) / float( liczba_krokow ) ) );
				get_y= pocz.y + przyblizenie_wartosci( ( float (( koniec.y - pocz.y ) * krok ) / float( liczba_krokow ) ) );
				if(get_x<0)get_x=0;
				if(get_y<0)get_y=0;
				Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(get_y, get_x);
				Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
				zmienna2=zmienna;
			}
		}
	}


	else
	{
		for( int j= Y1; j<Y2; j++ )
		{
			liczba_krokow= B_C.Oblicz_x(j) - A_C.Oblicz_x(j);
			pocz.x= AC.get_x1();
			koniec.y= BC.get_y1();
			pocz.y= AC.get_y1() + przyblizenie_wartosci ( (AC.get_dlugosc()) * float ( float (j - A_C.get_y1()) / float (A_C.get_h()) ) );
			koniec.x= BC.get_x1() + przyblizenie_wartosci ( (BC.get_dlugosc()) * float ( float (B_C.Oblicz_x(j) - B_C.get_x1()) / float (B_C.get_l()) ) );
			
			for(int i= A_C.Oblicz_x(j);i<=B_C.Oblicz_x(j);i++)
			{
				krok= i - A_C.Oblicz_x(j);
				get_x= pocz.x + przyblizenie_wartosci ( ( float (( koniec.x - pocz.x ) * krok ) / float( liczba_krokow ) ) );
				get_y= pocz.y + przyblizenie_wartosci ( ( float (( koniec.y - pocz.y ) * krok ) / float( liczba_krokow ) ) );
				if(get_x<0)get_x=0;
				if(get_y<0)get_y=0;
				Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(get_y, get_x);
				Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
				zmienna2=zmienna;
			}
		}
	};

}
void Trapez( Mat* Obraz_zrodlo, Mat* Obraz_cel, Odcinek A_B, Odcinek D_C, Odcinek AB, Odcinek DC)	
{
	POINT pocz;
	POINT koniec;
	int krok;
	int liczba_krokow;
	int get_x;
	int get_y;	
	for( int j=A_B.get_y1(); j<=A_B.get_y2(); j++ )
	{		
		liczba_krokow= D_C.Oblicz_x(j) - A_B.Oblicz_x(j);
		pocz.x=AB.get_x1();
		pocz.y= AB.get_y1() + przyblizenie_wartosci( AB.get_dlugosc() * ( float ( j-A_B.get_y1() ) / float ( A_B.get_h() ) ) ); 
		koniec.y= DC.get_y1() + przyblizenie_wartosci( DC.get_dlugosc() * ( float ( j-D_C.get_y1() ) / float ( D_C.get_h() ) ) );
		koniec.x=DC.get_x1();
		for( int i=A_B.Oblicz_x(j); i<=D_C.Oblicz_x(j); i++ )
		{
			krok= i-A_B.Oblicz_x(j);
			get_x= pocz.x + przyblizenie_wartosci ( ( float (( koniec.x - pocz.x ) * krok ) / float( liczba_krokow ) ) );
			get_y= pocz.y + przyblizenie_wartosci ( ( float (( koniec.y - pocz.y ) * krok ) / float( liczba_krokow ) ) );
			if(get_x<0)get_x=0;
			if(get_y<0)get_y=0;
				Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(get_y, get_x);
				Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
				zmienna2=zmienna;
		}
	}	
}

void Kalibracja( Mat* Obraz_zrodlo, Mat* Obraz_cel, POINT A, POINT B, POINT C, POINT D, POINT a, POINT b, POINT c, POINT d )
{ 
	Odcinek AB(a.x,a.y,b.x,b.y);
	Odcinek BC(b.x,b.y,c.x,c.y);
	Odcinek DC(d.x,d.y,c.x,c.y);
	Odcinek AD(a.x,a.y,d.x,d.y);
	Odcinek A_B(A.x,A.y,B.x,B.y);
	Odcinek B_C(B.x,B.y,C.x,C.y);
	Odcinek D_C(D.x,D.y,C.x,C.y);
	Odcinek A_D(A.x,A.y,D.x,D.y);
	char ksztalt_wykresu;
	
	if(A.y<=D.y)			// Lewy górny róg skalibrowanego zdjêcia znajduje siê nad poziomem prawego górnego rogu.
	{
		if(D.y<B.y)			// Prawy górny róg jest po³o¿ony wy¿ej od lewego dolnego.
		{
			if(B.y<=C.y)	// Lewy dolny róg jest wy¿ej od prawego dolnego.
			{
				ksztalt_wykresu=0;
			}
			else			// (C.y<B.y) Prawy dolny róg jest wy¿ej od lewego dolnego.
			{
				ksztalt_wykresu=1;
			};
		}
		else				// (B.y<=C.y) Lewy dolny róg jest wy¿ej od prawego dolnego.
		{
			ksztalt_wykresu=2;
		};
	}
	else					// (D.y<A.y) Prawy górny róg jest wy¿ej od lewego górnego. 
	{
		if(A.y<=C.y)		// Lewy górny róg jest wy¿ej od prawego dolnego.
		{
			if(B.y<=C.y)		// Lewy dolny róg jest wy¿ej od prawego dolnego.
			{
				ksztalt_wykresu=3;
			}
			else			// (C.y<B.y) Prawy dolny róg jest wy¿ej od lewego dolnego.
			{
				ksztalt_wykresu=4;
			};
		}
		else				//(C.y<A.y) Prawy dolny róg jest wy¿ej od lewego górnego.
		{
			ksztalt_wykresu=5;
		};
	}



		if(ksztalt_wykresu==0)
		{
			Odcinek A_E( A_B.get_x1(), A_B.get_y1(), A_B.Oblicz_x(A_D.get_y2()), A_D.get_y2() );  
			Odcinek AE ( a.x, a.y, a.x, a.y + przyblizenie_wartosci( (AB.get_dlugosc()*A_E.get_dlugosc())/A_B.get_dlugosc() ) );
			Trojkat ( Obraz_zrodlo, Obraz_cel, A_E, A_D, AE, AD );	
			
			Odcinek E_B( A_E.get_x2(), A_E.get_y2(), A_B.get_x2(), A_B.get_y2() );
			Odcinek D_F( D_C.get_x1(), D_C.get_y1(), D_C.Oblicz_x(A_B.get_y2()), A_B.get_y2() );
			Odcinek EB ( b.x, AE.get_y2(), b.x, b.y );
			Odcinek DF ( d.x, d.y , c.x , d.y + przyblizenie_wartosci( (DC.get_dlugosc()*D_F.get_dlugosc())/D_C.get_dlugosc() ) );
			Trapez ( Obraz_zrodlo, Obraz_cel, E_B, D_F, EB, DF ); 
			
			Odcinek F_C( D_F.get_x2(), D_F.get_y2(), B_C.get_x2(), B_C.get_y2() );	
			Odcinek FC ( DF.get_x2(), DF.get_y2(), c.x, c.y );
			Trojkat ( Obraz_zrodlo, Obraz_cel, B_C, F_C, BC, FC );
		}

		else if(ksztalt_wykresu==1)
		{
			Odcinek A_E( A_B.get_x1(), A_B.get_y1(), A_B.Oblicz_x(A_D.get_y2()), A_D.get_y2() );  
			Odcinek AE ( a.x, a.y, a.x, a.y + przyblizenie_wartosci( (AB.get_dlugosc()*A_E.get_dlugosc())/A_B.get_dlugosc() ) );
			Trojkat ( Obraz_zrodlo, Obraz_cel, A_E, A_D, AE, AD );
			
			Odcinek E_F( A_E.get_x2(), A_E.get_y2(), A_B.Oblicz_x(B_C.get_y2()), B_C.get_y2() ); 
			Odcinek EF ( a.x, AE.get_y2(), a.x, AE.get_y2() + przyblizenie_wartosci( (AB.get_dlugosc()*E_F.get_dlugosc())/A_B.get_dlugosc() ) );
			Trapez ( Obraz_zrodlo, Obraz_cel, E_F, D_C, EF, DC );

			Odcinek F_B( E_F.get_x2(), E_F.get_y2(), B.x, B.y);
			Odcinek FB ( b.x, EF.get_y2(), b.x, b.y );
			Trojkat ( Obraz_zrodlo, Obraz_cel, F_B, B_C, FB, BC );
		}

		
		//dla przypadku==2 zrobie, jesli bedzie czas, trzeba ustawic w funkcji Trapez() zmienny pocz.x i zmienny koniec.x, zalezne od obecnego wiersza dla zrodla.
		else if(ksztalt_wykresu==2)
		{
			MessageBox(NULL, "Program nie posiada algorytmu dla tego przypadku wierzcho³ków.", NULL, NULL);		
		}
		

		else if(ksztalt_wykresu==3)
		{
			Odcinek D_F( D_C.get_x1(), D_C.get_y1(), D_C.Oblicz_x(A_D.get_y1()), A_D.get_y1() );
			Odcinek DF ( d.x, d.y, d.x, d.y + przyblizenie_wartosci( (DC.get_dlugosc()*D_F.get_dlugosc())/D_C.get_dlugosc() ) );
			Trojkat ( Obraz_zrodlo, Obraz_cel, A_D, D_F, AD, DF );

			Odcinek F_E( D_F.get_x2(), D_F.get_y2(), D_C.Oblicz_x(A_B.get_y2()) , A_B.get_y2() );
			Odcinek FE ( DF.get_x2(), DF.get_y2(), DF.get_x1(), DF.get_y2() + przyblizenie_wartosci( (DC.get_dlugosc()*F_E.get_dlugosc())/D_C.get_dlugosc() ) ); 
			Trapez (Obraz_zrodlo, Obraz_cel, A_B, F_E, AB, FE);
	
			Odcinek E_C( F_E.get_x2(), F_E.get_y2(), C.x, C.y );
			Odcinek EC ( FE.get_x2(), FE.get_y2(), c.x, c.y );
			Trojkat ( Obraz_zrodlo, Obraz_cel, B_C, E_C, BC, EC );
		}

		else if(ksztalt_wykresu==4)
		{
			Odcinek D_E( D_C.get_x1(), D_C.get_y1(), D_C.Oblicz_x(A_D.get_y1()), A_D.get_y1() );  
			Odcinek DE ( d.x, d.y, d.x, d.y + przyblizenie_wartosci( (DC.get_dlugosc()*D_E.get_dlugosc())/D_C.get_dlugosc() ) );
			Trojkat ( Obraz_zrodlo, Obraz_cel, A_D, D_E, AD, DE );
			
			Odcinek A_F( A_B.get_x1(), A_B.get_y1(), A_B.Oblicz_x(C.y), C.y );
			Odcinek E_C( D_E.get_x2(), D_E.get_y2(), C.x, C.y );
			Odcinek AF ( a.x, a.y, a.x, a.y + przyblizenie_wartosci( (AB.get_dlugosc()*A_F.get_dlugosc())/A_B.get_dlugosc() ) );
			Odcinek EC ( d.x, DE.get_y2(), c.x , c.y );
			Trapez ( Obraz_zrodlo, Obraz_cel, A_F, E_C, AF, EC ); 

			Odcinek F_B( A_F.get_x2(), A_F.get_y2(), B.x, B.y);
			Odcinek FB ( AF.get_x2(), AF.get_y2(), b.x, b.y );
			Trojkat ( Obraz_zrodlo, Obraz_cel, F_B, B_C, FB, BC );
		}
		else if(ksztalt_wykresu==5)
		{
			MessageBox(NULL, "Program nie posiada algorytmu dla tego przypadku wierzcho³ków.", NULL, NULL);
		}
		else
		{
			MessageBox(NULL,"Podane wierzcho³ki s¹ nieprawid³owe",NULL,NULL);
		};
}

void Kalibracja_6pkt( Mat* Obraz_zrodlo, Mat* Obraz_cel, POINT A, POINT B, POINT C, POINT D, POINT E, POINT F, POINT a, POINT b, POINT c, POINT d, POINT e, POINT f )
{
	Kalibracja( Obraz_zrodlo , Obraz_cel , A , B , C , D , a , b , c , d );
	Kalibracja( Obraz_zrodlo , Obraz_cel , D , C , F , E , d , c , f , e );		  
}

void Zmiana_Rozmiaru( Mat* Obraz_zrodlo , Mat* Obraz_cel, int w, int h )
{
resize( *Obraz_zrodlo, *Obraz_cel, cvSize( w, h ), 0, 0, INTER_NEAREST );
};

void RBBR( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{    
	uchar r;
	uchar g;
	uchar b;

	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{			
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);			
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			zmienna2.val[0]=r;
			zmienna2.val[1]=g;
			zmienna2.val[2]=b;
		};
	};
};

void GBBG( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	uchar r;
	uchar g;
	uchar b;
	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);			
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			zmienna2.val[0]=g;
			zmienna2.val[1]=b;
			zmienna2.val[2]=r;
		}
	};
};

void RGGR( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
			zmienna2.val[0]=b;
			zmienna2.val[1]=r;
			zmienna2.val[2]=g;
		}
	};
};

void RGGBBR( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
			zmienna2.val[0]=g;
			zmienna2.val[1]=r;
			zmienna2.val[2]=b;
		}
	};
};

void RBBGGR( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	 
	unsigned char r;
	unsigned char g;
	unsigned char b;
	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
			zmienna2.val[0]=r;
			zmienna2.val[1]=b;
			zmienna2.val[2]=g;
		}
	};
};

void negatyw( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
	
			zmienna2.val[0]=255-b;
			zmienna2.val[1]=255-g;
			zmienna2.val[2]=255-r;
		}
	};
};


void Skala_Szarosci( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	cvtColor( *Obraz_zrodlo , *Obraz_cel , CV_RGB2GRAY );
};

void kontrast( Mat* Obraz_zrodlo, Mat* Obraz_cel, int wartosc ) 
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	for(int j=0;j<Obraz_zrodlo->rows;j++)
	{
		for(int i=0;i<Obraz_zrodlo->cols;i++)
		{
			Vec3b zmienna = Obraz_zrodlo->at<Vec3b>(j, i);
			
			b=zmienna.val[0];
			g=zmienna.val[1];
			r=zmienna.val[2];
			
			Vec3b &zmienna2= Obraz_cel->at<Vec3b>(j, i);
	
			if(b+wartosc<0)
			{
				zmienna2.val[0]=0;
			}
			else if(b+wartosc>255)
			{
				zmienna2.val[0]=255;
			}
			else
			{
				zmienna2[0]=b+wartosc;
			};
			
			if(g+wartosc<0)
			{
				zmienna2.val[1]=0;
			}
			else if(g+wartosc>255)
			{
				zmienna2.val[1]=255;
			}
			else
			{
				zmienna2.val[1]=g+wartosc;
			};

			if(r+wartosc<0)
			{
				zmienna2.val[2]=0;
			}
			else if(r+wartosc>255)
			{
				zmienna2.val[2]=255;
			}
			else
			{
				zmienna2.val[2]=r+wartosc;
			};
		}
	};
};

void transponowanie( Mat* Obraz_zrodlo, Mat* Obraz_cel )
{
	
	resize( *Obraz_cel, *Obraz_cel, cvSize( Obraz_zrodlo->rows, Obraz_zrodlo->cols ), 0, 0, INTER_NEAREST );
	cv::transpose( *Obraz_zrodlo , *Obraz_cel );
}

void Obrot_prawo_90( Mat* Obraz_zrodlo , Mat* Obraz_cel )
{
	resize( *Obraz_cel, *Obraz_cel, cvSize( Obraz_zrodlo->rows, Obraz_zrodlo->cols ), 0, 0, INTER_NEAREST );
	for(int j=0;j<Obraz_cel->rows;j++)
	{
		for(int i=0;i<Obraz_cel->cols;i++)
		{
			Vec3b zmienna= Obraz_zrodlo->at<Vec3b>(Obraz_zrodlo->rows-i-1,j);
			Vec3b &zmienna2=Obraz_cel->at<Vec3b>(j,i);
			zmienna2=zmienna;
		}
	}
}

void Obrot_lewo_90( Mat* Obraz_zrodlo , Mat* Obraz_cel )
{
	resize( *Obraz_cel, *Obraz_cel, cvSize( Obraz_zrodlo->rows, Obraz_zrodlo->cols ), 0, 0, INTER_NEAREST );
	for(int j=0;j<Obraz_cel->rows;j++)
	{
		for(int i=0;i<Obraz_cel->cols;i++)
		{
			Vec3b zmienna= Obraz_zrodlo->at<Vec3b>(i,Obraz_zrodlo->cols-j-1);
			Vec3b &zmienna2=Obraz_cel->at<Vec3b>(j,i);
			zmienna2=zmienna;
		}
	}
}

void Obrot_180( Mat* Obraz_zrodlo , Mat* Obraz_cel )
{
	for(int j=0;j<Obraz_cel->rows;j++)
	{
		for(int i=0;i<Obraz_cel->cols;i++)
		{
			Vec3b zmienna= Obraz_zrodlo->at<Vec3b>(Obraz_zrodlo->rows-j-1,Obraz_zrodlo->cols-i-1);
			Vec3b &zmienna2=Obraz_cel->at<Vec3b>(j,i);
			zmienna2=zmienna;
		}
	}
}

void Obrot_X( Mat* Obraz_zrodlo , Mat* Obraz_cel )
{
	for(int j=0;j<Obraz_cel->rows;j++)
	{
		for(int i=0;i<Obraz_cel->cols;i++)
		{
			Vec3b zmienna= Obraz_zrodlo->at<Vec3b>(Obraz_zrodlo->rows-j-1,i);
			Vec3b &zmienna2=Obraz_cel->at<Vec3b>(j,i);
			zmienna2=zmienna;
		}
	}
}

void Obrot_Y( Mat* Obraz_zrodlo , Mat* Obraz_cel )
{
	for(int j=0;j<Obraz_cel->rows;j++)
	{
		for(int i=0;i<Obraz_cel->cols;i++)
		{
			Vec3b zmienna= Obraz_zrodlo->at<Vec3b>(j,Obraz_zrodlo->cols-i-1);
			Vec3b &zmienna2=Obraz_cel->at<Vec3b>(j,i);
			zmienna2=zmienna;
		}
	}
}

void Obrot_XY( Mat* Obraz_zrodlo , Mat* Obraz_cel )
{
	for(int j=0;j<Obraz_cel->rows;j++)
	{
		for(int i=0;i<Obraz_cel->cols;i++)
		{
			Vec3b zmienna= Obraz_zrodlo->at<Vec3b>(Obraz_zrodlo->rows-j-1,Obraz_zrodlo->cols-i-1);
			Vec3b &zmienna2=Obraz_cel->at<Vec3b>(j,i);
			zmienna2=zmienna;
		}
	}
}


#endif