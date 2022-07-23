#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iomanip>
//#include <iomanip>
//#include <cmath>


class Matrix
{
public:
   double** Mat_1;
   int cols_num, rows_num;

    Matrix()
    {
       std::cout<<"Конструктор для "<<this<<std::endl;
    };
    
    Matrix(int n, int m)
    {
        std::cout<<"Конструкторр для "<<this<<std::endl;
        cols_num = n;
        rows_num = m;

        Mat_1 = new double*[n];   //Создание столбца указателей (Динамическая память)
        if(Mat_1 == NULL)
        {
            std::cout<<"\n Не хватает оперативной памяти под строки"; //Проверка наличия нужного количества непрерывной памяти
            exit(1);
        }
        for(int i=0;i<n;i++)
        {
            Mat_1[i] = new double [m];
            if (Mat_1[i]==NULL)
            {
                std::cout<<"\n Не хватает оперативной памяти под столбцы"; //Проверка наличия нужного количества непрерывной памяти
                exit(1);
            }
        }

        for (int i=0; i<n; i++)
        for (int j=0; j<m; j++) 
         {
             Mat_1[i][j] = 0;
        }
        
    };

    /*Matrix(const Matrix &Mat_ref) Конструктор копирования
    {
        rows_num = Mat_ref.rows_num;
        cols_num = Mat_ref.cols_num;
        Mat_1 = new double*[rows_num];
        for(int i = 0; i < rows_num; i++){
            Mat_1[i] = new double[cols_num];
            for(int j = 0; j < cols_num; j++)
                Mat_1[i][j] = Mat_ref.Mat_1[i][j];
            }
    } */


    void Generate(int n, int m)
    {
        cols_num = n;
        rows_num = m;

        this -> Mat_1 = new double*[n];   //Создание столбца указателей (Динамическая память)
        if(Mat_1 == NULL)
        {
            std::cout<<"\n Не хватает оперативной памяти под строки"; //Проверка наличия нужного количества непрерывной памяти
            exit(1);
        }
        for(int i=0;i<n;i++)
        {
            Mat_1[i] = new double [m];
            if (Mat_1[i]==NULL)
            {
                std::cout<<"\n Не хватает оперативной памяти под столбцы"; //Проверка наличия нужного количества непрерывной памяти
                exit(1);
            }
        }

        for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)   Mat_1[i][j] = double(rand() % 10);    //Создание матрицы с рандомными значениями [0..9]

        std::cout<<"Сгенерирована матрица "<<this<<std::endl;
        std::cout<<"Размер матрицы "<<n<<" x "<<m<<std::endl;
        std::cout<<""<<std::endl;

        /*for (int i=0;i<n;i++)
        {
            for (int j=0;j<m;j++) std::cout<<Mat_1[i][j]<<"\t";
            std::cout<<""<<std::endl;
        }*/

        std::cout<<std::endl;
        

        //for (int i=0;i<m+1;i++)    delete Mat_1[i];
        //delete[] Mat_1; //Очистка выделенной динамической памяти

        

    }

    void read_from_file(std::string file_name)
    {
        double a;

        std::ofstream log;
        log.open("log_read.txt");
        log << "Открыт файл log_read.txt \n";

        std::ifstream file;        
        file.open(file_name);
        log << "Открыт файл "<< file_name << "\n";

        for (int i = 0; i < cols_num; i++)
            for (int j = 0; j < rows_num; j++)
            {
                file >> Mat_1[i][j];
            }
        log << "Матрица считана \n";
        file.close();
        log << "Закрыт файл " << file_name << "\n";
        log.close();

    }

    // Поиск определителя
double Determinant()  
{
    int i = 0;
    int n = cols_num;
    int m = rows_num;
    double det = 1;

    try
    {
    while (n != 2)
    {
        i = 0;
        while (Mat_1[i][0] == 0) //определение строки i с 1м ненулевым элементом и прибавление его к 1му элементу 1й строки
        {
            //std::cout<<Mat_1[i][0]<<std::endl;
            i++;
        }

    if (i != 0)
        for (int j = 0;j<m;j++) Mat_1[0][j] += Mat_1[i][j]; //Прибавляем элементы iй строки к элементам 1й


        det *= Mat_1[0][0]; // 1й множитель определителя

        double koef;

    for (int i = 1;i<n;i++) if (Mat_1[i][0] != 0)
    {
        koef = - Mat_1[i][0]/double(Mat_1[0][0]);

        for (int j = 0;j<m;j++)
        {
            Mat_1[i][j] += Mat_1[0][j] * koef;
        }
        //std::cout<<"Koef "<<koef<<std::endl;
    }

    //std::cout<<"Koef "<<koef<<std::endl;

    for (int i = 1;i<n;i++)
    {
        for (int j = 0; j<m-1;j++)
        {
            Mat_1[i-1][j] = Mat_1[i][j+1];

        }
    }
    
    n--;
    m--;

    //std::cout<<"Det "<<det<<std::endl;

   /*for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++) std::cout<<Mat_1[i][j]<<"\t";
        //std::cout<<""<<std::endl;
    }
    //std::cout<<""<<std::endl;*/
    }

    //std::cout<<n<<" "<<m<<std::endl;

    det = det * (Mat_1[0][0] * Mat_1[1][1] - Mat_1[0][1] * Mat_1[1][0]);

    //std::cout<<" "<<std::endl;
    //std::cout<<"Det "<<det<<std::endl;
    return det;

}
    catch(const std::exception& e)
    {
        std::cout <<"Error" << '\n';
        std::cerr << e.what() << '\n';
	system("pause");
    } 
    return det;
}

/*Matrix Transpose()
{
    Matrix  Mat_trans(cols_num, rows_num);
    for(int i = 0; i < cols_num; i++)
        for (int j = 0; j < rows_num; j++)
            Mat_trans(i,j) = Mat_1[j][i]; 
    return Mat_trans;    
}*/
/*/Matrix Minor()
{
    Matrix Mat_Minor(cols_num, rows_num);
    for (int i = 0; i < Mat_Minor.cols_num; i++)
        for (int j = 0; j < Mat_Minor.rows_num; j++)
        {
            Mat_Minor(i,j) = ; 
        }B
}*/

double& operator()(int index1, int index2)
    {
	    return Mat_1[index1][index2];
    }

//Конструктор копирования
Matrix (Matrix &Mat)
{
    this->cols_num = Mat.cols_num;
    this->rows_num = Mat.rows_num;
    Mat_1 = new double*[Mat.cols_num];
    for (int i = 0; i < Mat.cols_num; i++)
    {
        Mat_1[i] = new double[Mat.rows_num];
        for (int j = 0; j < Mat.rows_num; j++) Mat_1[i][j] = Mat(i,j);
    } 
    std::cout<<"Копирование "<<this<<std::endl;
    
}


    //Вывод матрицы
    void Matrix_out()
    {
        std::cout<<"Размер матрицы "<<cols_num<<" x "<<rows_num<<std::endl;
        std::cout<<""<<std::endl;

        for (int i=0;i<cols_num;i++)
        {
            for (int j=0;j<rows_num;j++) std::cout<<Mat_1[i][j]<<"\t";
            std::cout<<""<<std::endl;
        }
    }
    
    
    Matrix& operator = (Matrix& Mat)
    {
        double **Mat_copy;
        this->cols_num = Mat.cols_num;
        this->rows_num = Mat.rows_num;
        Mat_copy = new double*[Mat.cols_num];
        for (int i = 0; i < Mat.cols_num; i++)
        {
            Mat_copy[i] = new double[Mat.rows_num];
            for (int j = 0; j < Mat.rows_num; j++) Mat_copy[i][j] = Mat(i,j);
        }
        Mat_1 = Mat_copy;
        return *this;
    }

   
    //Деструктор
   ~Matrix() 
    {
        std::cout<<"Деструктор для "<<this<<std::endl;
        for (int i = 0; i < rows_num; i++) delete[] Mat_1[i];
        delete[] Mat_1;
    };

};

 // Функция умножения матриц 5x5
    Matrix Multiply(Matrix ar1, Matrix ar2)  
    {
        Matrix ar3(ar1.rows_num, ar2.cols_num); //Создание указателя на указатель (Двухмерный массив)

        if(ar1.cols_num != ar2.rows_num)
        {
            std::cout<<"\n Несоответствие размерностей матриц"; //Проверка размерности матриц
            exit(1);
        }

        //ar3.Generate(ar1.rows_num, ar2.cols_num);
    
    
        // Цикл перемножения матриц 
        for (int i=0; i<ar1.cols_num; i++)
        {
             for (int j=0; j<ar2.rows_num; j++)
            {
                for (int z=0; z<ar2.rows_num; z++) 
                ar3(i,j) = ar3(i,j) + ar1(i,z) * ar2(z,j);
            }
    }

    return ar3; //Возвращаем результат умножения (Матрица)

    /*for (int i=0;i<n1+1;i++) delete ar3[i];
    delete[] ar3; //Очистка выделенной динамической памяти*/

   }

Matrix Transpose(Matrix &Mat)
{
    Matrix Mat_trans(Mat.cols_num, Mat.rows_num); 
    for(int i = 0; i < Mat_trans.cols_num; i++)
        for (int j = 0; j < Mat_trans.rows_num; j++)
            Mat_trans(i,j) = Mat(j,i); 
    return Mat_trans;    
}

int main()
{
    //srand(time(NULL));

    Matrix S1(5,5);
    Matrix S3;
    S1.Generate(5,5);
    S3 = S1;
    std::cout<<"Исходная матрица\n";
    S1.Matrix_out();
    std::cout<<"Транспонированная матрица\n";
    S3.Matrix_out();
    system("pause");
    return 0;
}
