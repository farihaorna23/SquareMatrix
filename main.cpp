#include<iostream>
#include"SquareMatrix.h"

using namespace std;

//g++ -std=c++11 main.cpp -o pi
void Test1()
{
   SquareMatrix<short> mat;
   
   if (mat.size() != 0)
   {
      cout << "ERROR: Either the default constructor or size() are faulty\n";
      cout << "Test1 is stoped\n";
      return;
   }

   mat.resize(4);
   if (mat.size() != 4)
   {
      cout << "ERROR: Either a resize() or size() are faulty\n";
      cout << "Test1 is stoped\n";
      return;
   }

   mat.at(3, 3) = 456;
   if (mat.at(3, 3) != 456)
   {
      cout << "ERROR: at() is faulty\n";
      cout << "Test1 is stoped\n";
      return;
   }

   mat.resize(5);

   cout << "test 1 is passed\n";
}

template<typename T>
void SetMatrix(SquareMatrix<T>& m, int size, T value)
{
   m.resize(size);
   for (int i{ 0 }; i < size; i++)
      for (int j{ 0 }; j < size; j++)
         m.at(i, j) = value;
}

void Test2()
{
   SquareMatrix<int> m1;
   SetMatrix<int>(m1, 6, 8);

   SquareMatrix<int> m2;
   SetMatrix<int>(m2, 6, 8);

   if(not (m1==m2))
   {
      cout << "ERROR: operator== is faulty\n";
      cout << "Test2 is stoped\n";
      return;
   }

   SetMatrix<int>(m2, 5, 8);
   if (m1 == m2)
   {
      cout << "ERROR: operator== is faulty\n";
      cout << "Test2 is stoped\n";
      return;
   }

   SetMatrix<int>(m2, 7, 8);
   if (m1 == m2)
   {
      cout << "ERROR: operator== is faulty\n";
      cout << "Test2 is stoped\n";
      return;
   }

   SetMatrix<int>(m2, 6, 6);
   if (m1 == m2)
   {
      cout << "ERROR: operator== is faulty\n";
      cout << "Test2 is stoped\n";
      return;
   }

   cout << "test 2 is passed\n";
}

void Test3()
{
   SquareMatrix<double> m1;
   SetMatrix<double>(m1, 5, 4.0);

   SquareMatrix<double> m2{ m1 };

   if(not (m1==m2))
   {
      cout << "ERROR: copy constructor is faulty\n";
      cout << "Test3 is stoped\n";
      return;
   }

   SquareMatrix<double> m3{ move(m1) };

   if (not (m3 == m2))
   {
      cout << "ERROR: move constructor is faulty\n";
      cout << "Test3 is stoped\n";
      return;
   }

   cout << "test 3 is passed\n";
}


void Test4()
{
   SquareMatrix<double> m1;
   SetMatrix<double>(m1, 5, 4.0);

   SquareMatrix<double> m2;
   
   m2 = m1;
   if(not (m2==m1))
   {
      cout << "ERROR: copy assignment is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   SquareMatrix<double> m3;
   SetMatrix<double>(m3, 10, 20);

   m3 = m2;
   if (not (m3 == m2))
   {
      cout << "ERROR: copy assignment is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   SquareMatrix<double> empty_mat;
   m3 = empty_mat;

   SquareMatrix<double> m4;

   m4 = move(m1);
   
   SquareMatrix<double> m5;
   SetMatrix<double>(m5, 9, 19);

   m5 = move(m2);
   if (not (m4 == m5))
   {
      cout << "ERROR: move assignment is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   m5 = empty_mat;

   SquareMatrix<double> m6;
   SetMatrix<double>(m6, 5, 4.0);
   m6 = m6;
   if (m6.at(4,4)!=4.0)
   {
      cout << "ERROR: copy assignment (self-assignment obj1=obj1) is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   SquareMatrix<double> m7;
   SetMatrix<double>(m7, 5, 7.0);
   m7 = move(m7);
   if (m7.at(4, 4) != 7.0)
   {
      cout << "ERROR: move assignment (self-assignment obj1=move(obj1) ) is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   SquareMatrix<double> m8, m9, m10;
   SetMatrix<double>(m10, 7, 12.0);
   m8 = m9 = m10;

   if (not (m8 == m9))
   {
      cout << "ERROR: copy assignment is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   SetMatrix<double>(m10, 7, 3.0);
   m8 = m9 = move(m10);

   if (not (m8 == m9))
   {
      cout << "ERROR: move assignment is faulty\n";
      cout << "Test4 is stoped\n";
      return;
   }

   cout << "test 4 is passed\n";
}

void Test5()
{
   SquareMatrix<int> m1;
   SetMatrix<int>(m1, 5, 3);

   SquareMatrix<int> m2;
   SetMatrix<int>(m2, 5, 4);

   SquareMatrix<int> m3;
   m3 = m1 + m2;

   bool ok{ true };
   if (m3.size() != 5)
      ok = false;
   for (int i{ 0 }; i < 5; i++)
      for (int j{ 0 }; j < 5; j++)
         if (m3.at(i, j) != 7)
            ok = false;

   if(ok==false)
   {
      cout << "ERROR: operator+ is faulty\n";
      cout << "Test5 is stoped\n";
      return;
   }

   cout << "test 5 is passed\n";
}

int main()
{
   Test1();
   Test2();
   Test3();
   Test4();
   Test5();

   //*********New Test cases **************
    //g++ -std=c++11 Test_2.cpp -o hi
    
    SquareMatrix<int> sqm;
    sqm.allocate(5);
    SquareMatrix<int> sq;
    
    //Testing Default Constructor (W)   Paramterized Constructor(W)   Display(W)  fillMatrix(W)    Destructor(W)

    //cout << "Testing  Default Paramterized Display fillMatrix Destructor Size: " << endl;
    
    cout << "sqm display 5*5: " << endl;
    
    sqm.print_matrix();

      
    cout << "sq 0*0: "<<endl;
    //sq.print_matrix();//--->gives segmentation fault. Doesn't give segementation fault when i comment this out.

    cout << "sqm size 5: " << sqm.size() << endl;
    cout << "sqm size 0: " << sq.size() << endl;
    

    SquareMatrix<int> sqma;
    sqma.allocate(4);
    sqma.fill(5);
    cout<< "Display 4*4 fill 5: " <<endl;
    sqma.print_matrix();

   
    //Resize
    cout << "Testing Resize"<<endl;
    SquareMatrix<int> res;
    res.allocate(2);
    res.fill(10);
    cout<<"print resize: "<<endl;
    res.print_matrix();
    
    
    cout<<"after resize fx: "<<endl;
    res.resize(1);    
    res.print_matrix();       
    
    //Test Equality Operator    == (W)
    SquareMatrix<int> sww;
    SquareMatrix<int> smww;
    cout << "When matrizes are same 0: "<<(sww == smww) << endl;    //T 1
    SquareMatrix<int> sqy;
    sqy.allocate(4);
    SquareMatrix<int> sqmy;
    sqmy.allocate(4);
    cout << "When matrizes are same: "<<(sqy == sqmy) << endl;   //T 1
    SquareMatrix<int> sqtu;
    sqtu.allocate(4);
    sqtu.fill(10);
    SquareMatrix<int> sqmtu;
    sqmtu.allocate(4);
    sqmtu.fill(10);
    cout << "When matrizes are same w fillMatrix "<<(sqtu == sqmtu) << endl;  //T 1
    SquareMatrix<int> sqto;
    sqto.allocate(5);
    sqto.fill(10);
    SquareMatrix<int> sqmto;
    sqmto.allocate(4);
    sqmto.fill(10);
    cout << "When matrizes are not same w fillMatrix "<<(sqto == sqmto) << endl;  //F0
    SquareMatrix<int> sqtos;
    sqtos.allocate(5);
    sqtos.fill(5);
    SquareMatrix<int> sqmtos;
    sqmtos.allocate(5);
    sqmtos.fill(10);
    cout << "When matrizes are same w diff fillMatrix "<<(sqtos == sqmtos) << endl;  //F0


    SquareMatrix<int> tot; 
    tot.allocate(4);
    tot.fill(10); 
    tot.print_matrix();  //displays all 10s
    SquareMatrix<int> ip;
    ip.allocate(4);
    ip.fill(5);        //new matrix with all 5s
    tot = ip;
    tot.print_matrix();
    
    
    //Test Add Operator += (W)      //How to test add operator
    cout <<endl<<"Testing Add operator and move assign"<<endl;
    SquareMatrix<int> siya(2);
    siya.fill(4);
    siya.print_matrix();
    
    SquareMatrix<int> smile(2);
    smile.fill(-1);
    smile.print_matrix();
    
    SquareMatrix<int> smqe(2);//------>gives segmentation fault
    smqe = (smile + siya);
    smqe.print_matrix();

    
    //Test at
    cout <<endl<<"Testing At and move"<<endl;
    SquareMatrix<int> sqmgh;
    sqmgh.allocate(4);
    sqmgh.fill(5);
    cout<< "before changing:  "<< sqmgh.at(0,1)<<endl;
    sqmgh.at(0,1) = 9;
    cout<< "after changing:  "<<sqmgh.at(0,1)<<endl;
    sqmgh.print_matrix();
    cout<<sqmgh.at(0,1);
    cout<<sqmgh.at(1,0);
    cout<<sqmgh.at(0,0);
    cout<<sqmgh.at(1,1);
    
   
    //Test Copy Constructor (W)
    cout << "Copy Constructor"<<endl;
    SquareMatrix<int> sqmcopy;
    sqmcopy.allocate(4);
    sqmcopy.fill(10);
    SquareMatrix<int> sqeel(sqmcopy);
    sqmcopy.print_matrix();
	cout<<endl;
    sqeel.print_matrix();

  
    //Testing Copy Assignment  (W)
    cout << "Copy Assignment"<<endl;
    SquareMatrix<int> sqmassi(4);
    sqmassi.fill(10);
    cout<<endl;
	sqmassi.print_matrix();
    SquareMatrix<int> sqassignment;//--->segmentation fault
    sqassignment = sqmassi;
	cout<<endl;
    sqassignment.print_matrix();


   return 0;
}