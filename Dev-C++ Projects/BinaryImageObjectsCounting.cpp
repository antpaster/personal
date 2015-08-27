#include <iostream>
#include <conio.h>

using namespace std;

struct scanMask
{
	int A, B, C;
};

int main()
{
	int  imageMatr[13][11] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	     					  0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0,
							  0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
							  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
							  0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
							  0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							  0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
							  0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
							  0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0,
							  0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
							  0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0,
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	 
	int kn = 0, km = 0, curr = 1;
	scanMask ABC;
	
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 11; j++)
		{
			kn = j - 1;
   	 		if (kn < 0)
   	 		{
      			kn = 1;
      			ABC.B = 0;
  			}
    		else
     			ABC.B = imageMatr[i][kn];
    		km = i - 1;
    		if (km < 0)
    		{
      			km = 1;
      			ABC.C = 0;
  			}
    		else
      			ABC.C = imageMatr[km][j];
    		ABC.A = imageMatr[i][j];
    		if (ABC.A != 0) 
				if (ABC.B == 0 && ABC.C == 0) // Если вокруг нашего пикселя пусто а он не пуст - то это повод подумать о новом объекте
        		{
					curr++;
        			imageMatr[i][j] = curr;
        		}
    			else 
					if (ABC.B != 0 && ABC.C == 0)
        				imageMatr[i][j] = ABC.B;
    				else
						if (ABC.B == 0 && ABC.C != 0)
        					imageMatr[i][j] = ABC.C;
    					else
							if (ABC.B != 0 && ABC.C != 0)        
        						if (ABC.B == ABC.C)
          							imageMatr[i][j] = ABC.B;
        						else
        						{
        							imageMatr[i][j] = ABC.B;
          							for (int i = 1; i <= 13; i++)
										for (int j = 1; j <= 11; j++)
											if (imageMatr[i][j] == ABC.C)
												imageMatr[i][j] == ABC.B;
        						}
        }
	
	cout << "The image is:" << endl << endl;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
			cout <<imageMatr[i][j];
		cout << endl;
	}
	
	cout << endl << "Objects' count: " << curr << endl;
	getch();
	return 0;
}
