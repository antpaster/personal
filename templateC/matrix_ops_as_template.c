/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          13.09.17 г. APasternak
 ** ИЗМЕНЕН:         13.09.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 13.09.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  matrix_ops_as_template.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 13.09.17
 ** \brief Matrix operations templates realization
 */

#ifdef T
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Transposing template
 * \param[ in, out] matrix Pointer to the transposed matrix
 * \param[ in] rowCount Matrix row count
 * \param[ in] columnCount Matrix column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input pointer */
int TEMPLATE( transpose, T)( T *matrix, const size_t rowCount, const size_t columnCount) {
    if( matrix) {
        T temp;
        T *currAddr;
        T *currAddrExtra;

        size_t i, j = 0, k;

        const size_t pairArraySize = rowCount * columnCount;

        /* Index repeating flags array */
        uint8_t repeatFlagArray[ pairArraySize];
        uint8_t *currRepeatFlag;
        memset( repeatFlagArray, 0, pairArraySize * sizeof( uint8_t));

        /* The array of the pairs of the indexes */
        TindexPair pairArray[ pairArraySize];
        TindexPair *currIndexPairAddr;
        TindexPair *currIndexPairAddrExtra;

        /* Index pair array filling */
        for( i = 0; i < pairArraySize; ++i) {
            currIndexPairAddr = pairArray + i;
            currIndexPairAddr->iRow = i / rowCount;
            currIndexPairAddr->iColumn = i % rowCount;
        }

        for( i = 0; i < rowCount + columnCount; ++i) {
            currIndexPairAddr = pairArray + j;

            /* Assigning new index pair */
            if( currIndexPairAddr->iRow != currIndexPairAddr->iColumn) {
                currIndexPairAddr = pairArray + j;
                currIndexPairAddr->iRow = i;
                currIndexPairAddr->iColumn = ( i % rowCount) * rowCount + i / rowCount;

                /* Finding out if there was a index pair with same values of row or column */
                for( k = 0; k <= j; ++k) {
                    currIndexPairAddrExtra = pairArray + k;
                    if( ( currIndexPairAddrExtra->iRow == currIndexPairAddr->iColumn)
                        || ( currIndexPairAddr->iRow == currIndexPairAddrExtra->iColumn)) {

                        /* Setting the current repeat flag */
                        currRepeatFlag = repeatFlagArray + j;
                        *currRepeatFlag = 1;
                        break;
                    }
                }

                currRepeatFlag = repeatFlagArray + j;
                if( !( *currRepeatFlag)) {

                    /* Swap the T array variables */
                    currAddr = matrix + currIndexPairAddr->iRow;
                    temp = *currAddr;

                    currAddrExtra = matrix + currIndexPairAddr->iColumn;
                    *currAddr = *currAddrExtra;

                    *currAddrExtra = temp;
                }
            }

            ++j;
        }

        return 0;
    }

    return 1;
}

/*! Matrix inversion template
 * \param[ out] result Pointer to the inverted matrix
 * \param[ in] matrix Pointer to the input matrix, rowCount * ( 2 * rowCount)
 * \param[ in] rowCount Matrix row count
 * \param[ in] columnCount Matrix column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input pointer, 2 - inverse matrix does not exist */
int TEMPLATE( inverse, T)( T *result, const T *matrix, const size_t rowCount) {

    if( matrix) {
        uint8_t flag = 1;
        T t;
        T chas;
        T temp;
        T bufMatr[ 2 * rowCount];
        T *currBufAddr;
        T *currAddr;
        T *currAddrExtra;

        int i, j, k, p;

        /* Local copy of the input matrix */
        T workMatrix[ 2 * rowCount * rowCount];
        for( i = 0; i < 2 * rowCount * rowCount; ++i) {
            currAddr = workMatrix + i;
            *currAddr = *( matrix + i);
        }

        for( i = 0; i < rowCount; ++i) {
            if( ( 0 == *( workMatrix + i * rowCount + i)) && ( rowCount - 1 != i)) {
                flag = 0;

                for( j = i + 1; j < rowCount; ++j) {

                    if( 0 != *( workMatrix + j * rowCount + i)) {

                        for( k = 0; k < 2 * rowCount; ++k) {
                            currBufAddr = bufMatr + k;
                            currAddr = workMatrix + j * rowCount + k;
                            *currBufAddr = *currAddr;

                            currAddrExtra = workMatrix + i * rowCount + k;
                            *currAddr = *currAddrExtra;

                            *currAddrExtra = *currBufAddr;
                        }
                        flag = 1;
                        break;
                    }
                    else {
                        flag = 0;
                    }
                }
            }
        }

        if( flag) {
            /* Gauss-Jordan method straight way */
            for( i = 0; i < rowCount; ++i) {
                t = *( workMatrix + i * rowCount + i);

                for( j = i; j < 2 * rowCount + 1; ++j) {
                    currAddr = workMatrix + i * rowCount + j;
                    *currAddr /= ( fabs( t) > F_NULL) ? t : F_NULL;
                }

                for( k = i + 1; k < rowCount; ++k) {
                    chas = *( workMatrix + k * rowCount + i);

                    for( p = i; p < 2 * rowCount + 1; ++p) {
                        currAddr = workMatrix + k * rowCount + p;
                        currAddrExtra = workMatrix + i * rowCount + p;
                        *currAddr -= ( *currAddrExtra) * chas;
                    }
                }
            }

            /* Gauss-Jordan method backward way */
            for( i = rowCount - 2; i >= 0; --i) {
                for( k = i; k >= 0; --k) {
                    currAddr = workMatrix + k * rowCount + i + 1;
                    chas = *currAddr;

                    for( j = 0; j < 2 * rowCount + 1; ++j) {
                        currAddr = workMatrix + k * rowCount + j;
                        *currAddr -= *( workMatrix + ( i + 1) * rowCount + j) * chas;
                    }
                }
            }

            for( i = 0; i < rowCount; ++i) {
                for( j = 0; j < rowCount; ++j) {
                    currAddr = result + i * rowCount + j;
                    *currAddr = *( workMatrix + i * rowCount + j + rowCount + 1);
                }
            }

            /*double **imatr=new double *[n];//Îáðàòíàÿ ìàòðèöà
    for(int i=0;i<n;i++)
    {
      imatr[i]=new double[n];
      for(int j=0;j<n;j++)
        imatr[i][j]=matr[i][j+n+1];
    }*/

        }
        else {
            printf( "\nInverse matrix cannot be calculated!");
            return 2;
        }

        return 0;
    }

    /*double t,chas;
  int flag=1;
  double *buf=new double[2*n];//Ñòðîêà-áóôåð ïðè ïåðåñòàíîâêå
  for(int i=0;i<n;i++)
  {
    if ((mas[i][i]==0)&&(i!=n-1))//Ïðîâåðêà íà ñóùåñòâîâàíèå îáðàòíîé ìàòðèöû
    {
      flag=0;
      for(int j=i+1;j<n;j++)
      {
        if (mas[j][i]!=0)
        {
          for(int k=0;k<2*n;k++)//Ïåðåñòàíîâêà ñòðîê
          {
            buf[k]=mas[j][k];
            mas[j][k]=mas[i][k];
            mas[i][k]=buf[k];
          }
          flag=1;
          break;
        }
        else
          flag=0;
      }
    }
  }
  if (flag)//Ïðÿìîé õîä
  {
    for(int i=0;i<n;i++)//i - èíäåêñ ñòîëáöà (ñòðîêè) èñêëþ÷àåìîé ïåðåìåííîé
    {
      t=mas[i][i];
      for(int j=i;j<2*n+1;j++)//j - èíäåêñ ñòîëáöà
        mas[i][j]/=t;
      for(int k=i+1;k<n;k++)//öèêë-èñêëþ÷åíèå i-òîé ïåðåìåííîé èç íèæåëåæàùèõ ñòðîê, k - èíäåêñ ñòðîêè
      {
        chas=mas[k][i];
        for(int p=i;p<2*n+1;p++)
          mas[k][p]-=mas[i][p]*chas;
      }
    }
    cout<<"\nÌàòðèöà, ïðåîáðàçîâàííàÿ ïðÿìûì õîäîì:"<<endl<<endl;
    out(mas,n,2*n+1);
    cout<<"--------------------------------------------------------------------------------";
    //Îáðàòíûé õîä
    for(int i=n-2;i>=0;i--)//i - èíäåêñ ñòîëáöà èñêëþ÷àåìîé ïåðåìåííîé
      for(int k=i;k>=0;k--)//k - èíäåêñ ñòðîê-èñêëþ÷åíèé
      {
        chas=mas[k][i+1];
        for(int j=0;j<2*n+1;j++)//j - èíäåêñ ñòîëáöîâ â ãåíåðèðóåìîé îáðàòíîé ìàòðèöå
          mas[k][j]-=mas[i+1][j]*chas;
      }
    cout<<"\nÌàòðèöà, ïðåîáðàçîâàííàÿ îáðàòíûì õîäîì:"<<endl<<endl;
    out(mas,n,2*n+1);
    cout<<"--------------------------------------------------------------------------------";
    }
    else
    {
      cout<<"Ìàòðèöà âûðîæäåííàÿ, îáðàòíîé íå ñóùåñòâóåò!"<<endl<<endl;
      det=0;//Îïðåäåëèòåëü âûðîæäåííîñòè ìàòðèöû
    }*/

    return 1;
}

/*! Matrix multiplication template
 * \param[ out] result Pointer to the multiplication result matrix
 * \param[ in] mult1 Pointer to the first matrix-multiplier
 * \param[ in] mult2 Pointer to the second matrix-multiplier
 * \param[ in] mult1rowCount 1st matrix-multiplier row count
 * \param[ in] commonSize 1st matrix-multiplier column count or 2nd matrix-multiplier row count
 * \param[ in] mult2columnCount 2nd matrix-multiplier column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input or output pointer */
int TEMPLATE( matr_multiply, T)( T *result, const T *mult1, const T *mult2,
    const size_t mult1rowCount, const size_t commonSize, const size_t mult2columnCount) {

    if( result && mult1 && mult2) {
        int i, j, k;
        T *currAddr;
        
        for( i = 0; i < mult1rowCount; ++i) {
            for( j = 0; j < mult2columnCount; ++j) {
                currAddr = result + i * mult1rowCount + j;
                *currAddr = 0;

                for( k = 0; k < commonSize; ++k) {
                    *currAddr += *( mult1 + i * mult1rowCount + k)
                            * ( *( mult2 + k * commonSize + j));
                }
            }
        }

        return 0;
    }

    return 1;
}

/*! Matrix without iRow row and iColumn column gaining, auxiliary to the matrix inversion function
 * \param[ out] result Pointer to the result matrix
 * \param[ in] sourceMatr Pointer to the source matrix
 * \param[ in] iRow Row for deleting index
 * \param[ in] iColumn Column for deleting index
 * \param[ in] rowCount Row (column) count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input or output pointer */
int TEMPLATE( matrIjLess, T)( T *result, const T* sourceMatr, const size_t iRow,
    const size_t iColumn, const size_t rowCount) {

    if( result && sourceMatr) {
        size_t ki, kj, di = 0, dj;
        T *currResultAddr;
        T *currSourceMatrAddr;

        for( ki = 0; ki < rowCount - 1; ++ki) {
            if( ki == iRow) {
                /* Row index checking */
                di = 1;
            }

            dj = 0;

            for( kj = 0; kj < rowCount - 1; ++kj) {
                if( kj == iColumn) {
                    /* Column index checking */
                    dj = 1;
                }
                
                currResultAddr = result + ki * rowCount + kj;
                currSourceMatrAddr = sourceMatr + ( ki + di) * rowCount + kj + dj;
                *currResultAddr = *currSourceMatrAddr;
                //            result[ ki][ kj] = sourceMatr[ ki + di][ kj + dj];
            }
        }

        return 0;
    }

    return 1;
}

/* Recursive matrix determinant calculation template
 * \param[ out] result Pointer to the variable which holds the determinant value
 * \param[ in] matrix Pointer to the matrix
 * \param[ in] rowCount Matrix row count
 * \param[ in] order Matrix order
 ***************************************************************************************************
 * \return: 0 - ok, 1 - null input pointer, 2 - bad matrix order */
int TEMPLATE( determine, T)( T *result, const T *matrix, const size_t rowCount, const int order) {
    if( matrix) {
        size_t i, j = 0, k = 1, n = rowCount - 1;

        /* Assist matrix - copy of the input one for the beginning */
        T assistMatr[ rowCount * rowCount];
        T *currAddr;
        T *currAddrAssist;
        for( i = 0; i < rowCount * rowCount; ++i) {
            currAddr = matrix + i;
            currAddrAssist = assistMatr + i;
            *currAddrAssist = *currAddr;
        }

        if( order < 1) {
            printf( "\nDeterminant is uncalculable! Order is %d", order);
            return 2;
        }
        else if( 1 == order) {
            *result = *matrix;
        }
        else if( 2 == order) {
            *result = *matrix * ( *( matrix + rowCount + 1))
                - ( *( matrix + rowCount)) * ( *( matrix + 1));
        }
        else {
            for( i = 0; i < order; ++i) {
                TEMPLATE( matrIjLess, T)( matrix, assistMatr, i, 0, order);
                *result += k * ( *( matrix + i * rowCount))
                    * TEMPLATE( determine, T)( assistMatr, assistMatr, rowCount, n);
                k = -k;
            }
        }

        return 0;
    }

    return 1;

    /*// Рекурсивное вычисление определителя
    int Determinant(int **mas, int m) {
      int i, j, d, k, n;
      int **p;
      p = new int*[m];
      for (i = 0; i<m; i++)
        p[i] = new int[m];
      j = 0; d = 0;
      k = 1; //(-1) в степени i
      n = m - 1;
      if (m<1) cout << "Определитель вычислить невозможно!";
      if (m == 1) {
        d = mas[0][0];
        return(d);
      }
      if (m == 2) {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
        return(d);
      }
      if (m>2) {
        for (i = 0; i<m; i++) {
          GetMatr(mas, p, i, 0, m);
          cout << mas[i][j] << endl;
          PrintMatr(p, n);
          d = d + k * mas[i][0] * Determinant(p, n);
          k = -k;
        }
      }
      return(d);
    }
    // Основная функция
    int main() {
      int m, i, j, d;
      int **mas;
      system("chcp 1251");
      system("cls");
      cout << "Введите размерность квадратной матрицы: ";
      cin >> m;
      mas = new int*[m];
      for (i = 0; i<m; i++) {
        mas[i] = new int[m];
        for (j = 0; j<m; j++) {
          cout << "mas[" << i << "][" << j << "]= ";
          cin >> mas[i][j];
        }
      }
      PrintMatr(mas, m);
      d = Determinant(mas, m);
      cout << "Определитель матрицы равен " << d;
      cin.get(); cin.get();
      return 0;
    }

    return 1;*/
}

#endif

#endif
