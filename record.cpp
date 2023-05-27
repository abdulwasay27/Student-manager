#include <iostream>
#include <iomanip>
#include <fstream>
#include "record.h"
using namespace std;

Record::Record(char *str)
{
      fileName = str;
      ofstream myFile(fileName);
      studentSize = 20;
      addressSize = 30;
      student = new char[studentSize];
      address = new char[addressSize];
      myFile.close();
}
int Record::record_Input()
{
      char student[studentSize], address[addressSize];
      cout << "For how many students do you wish to enter the data? ";
      cin >> students;

      ofstream myFile(fileName, ios::app);
      if (!myFile.is_open())
            cout << "\nThe file could not be opened successfully.\n";

      for (int i = 0; i < students; i++)
      {
            cin.ignore();
            cout << "\nEnter name of student " << i + 1 << ": ";
            cin.getline(student, studentSize);

            myFile << student << "\n";

            cout << "\nEnter address of student " << i + 1 << ": ";
            cin.getline(address, addressSize);
            myFile << address << "\n";

            cout << "\nEnter age of student " << i + 1 << ": ";
            cin >> age;
            myFile << age << "\n";

            cout << "\nEnter CGPA of student " << i + 1 << ": ";
            cin >> CGPA;
            myFile << CGPA << "\n~\n";
      }
      myFile.close();
      return 0;
}
void Record::record_Display()
{
      ifstream myFile(fileName);
      char *display = new char[100]{0};
      char ch;
      if (!myFile.is_open())
      {
            cout << "\nCould not open file correctly\n";
            return;
      }
      for (int i = 0; i < students; i++)
      {
            myFile >> ch;
            if (ch == '~')
            {
                  i--;
                  continue;
            }
            cout << "Details of student " << i + 1 << endl;
            myFile.getline(display, 100);
            cout << "Name: " << display << endl;
            myFile.getline(display, 100);
            cout << "Address: " << display << endl;
            myFile.getline(display, 100);
            cout << "Age: " << display << endl;
            myFile.getline(display, 100);
            cout << "CGPA: " << display << endl
                 << endl;
      }
      myFile.close();
}
int Record::record_Search()
{
      ifstream myFile(fileName);
      if (!myFile.is_open())
      {
            cout << "\nCould not open file correctly.\n";
            return 0;
      }

      char *str = new char[studentSize];
      cin.ignore();
      cout << "Enter the name of student: ";
      cin.getline(str, studentSize);

      while (!myFile.eof())
      {
            myFile.getline(student, studentSize);
            if (*str == *student)
            {
                  myFile.getline(address, addressSize);
                  myFile >> age >> CGPA;
                  cout << student << endl;
                  cout << address << endl;
                  cout << age << endl;
                  cout << CGPA << endl;
            }
      }
      myFile.close();
}
void Record::record_Replace()
{
      char *compare = new char[studentSize]{0};
      char *data = new char[100]{0};
      bool found = false;
      float no = 0, count = 0;
      cin.ignore();
      cout << "Enter the name of student: ";
      cin.getline(compare, studentSize);
      cout << endl;
      ifstream iFile(fileName);
      ofstream oFile("temporary");
      if (!iFile.is_open())
      {
            cout << "Error opening file. " << endl;
            return;
      }
      while (iFile.getline(data, 100))
      {
            if (found)
            {
                  count++;
            }
            if (count == 4)
            {
                  count = 0;
                  found = false;
            }
            if (*compare == *data)
            {
                  found = true;

                  cout << "Enter new name: ";
                  cin.getline(data, 100);

                  oFile << data << endl;
                  cout << "Enter new address: ";
                  cin.getline(data, 100);

                  oFile << data << endl;
                  cout << "Enter new age: ";
                  cin >> no;

                  oFile << no << endl;
                  cout << "Enter new CGPA: ";
                  cin >> no;
                  oFile << no << endl;
            }
            else if (!found)
                  oFile << data << endl;
      }
      iFile.close();
      oFile.close();
      remove(fileName);
      rename("temporary", fileName);
      delete[] data;
      delete[] compare;
}
int Record::record_Count()
{
      ifstream myFile(fileName);
      char ch;
      int count = 0;
      if (!myFile.is_open())
      {
            cout << "Error opening file. " << endl;
            return -1;
      }
      while (myFile >> ch)
      {
            if (ch == '~')
                  count++;
      }

      cout << endl
           << "The number of records are: " << count << endl;
      myFile.close();
      return count;
}
int Record::delete_Record()
{
      char *data = new char[100]{0};
      char *delStudent = new char[studentSize];
      int count = 0;
      cin.ignore();
      cout << "Enter name of student whose record you wish to delelte: ";
      cin.getline(delStudent, studentSize);
      cout << endl;
      bool found = false;
      ifstream iFile(fileName);
      ofstream oFile("temporary");
      while (iFile.getline(data, 100))
      {
            if (*data == *delStudent)
                  found = true;

            if (found)
            {
                  if (data[0] == '~')
                        found = false;
            }
            else
            {
                  oFile << data << endl;
            }
      }
      iFile.close();
      oFile.close();
      remove(fileName);
      rename("temporary", fileName);
      delete data;
      data = 0;
}
int Record::record_Insert()
{
      cin.ignore();
      cout << "Enter name of student: ";
      cin.getline(student, studentSize);

      cout << endl
           << "Enter address: ";
      cin.getline(address, addressSize);

      cout << endl
           << "Enter age: ";
      cin >> age;

      cout << endl
           << "Enter CGPA: ";
      cin >> CGPA;

      ofstream myFile(fileName, ios::app);
      if (!myFile.is_open())
      {
            cout << "Error opening file. ";
            return -1;
      }
      myFile << student << endl
             << address << endl
             << age << endl
             << CGPA << endl
             << "~";
      myFile.close();
}
Record::~Record()
{
      delete[] fileName;
      delete[] student;
      delete[] address;
}
int main()
{
      char *filename = new char[10];
      cout << "Enter the file name: ";
      cin >> filename;
      cin.ignore();
      Record obj(filename);
      int n = 0;
      bool running = true;
      while (running)
      {
            cout << "Which operation do you wish to perform? ";
            cout << endl
                 << "1. Record input" << endl;
            cout << endl
                 << "2. Record Insert" << endl;
            cout << endl
                 << "3. Record Delete" << endl;
            cout << endl
                 << "4. Record Search" << endl;
            cout << endl
                 << "5. Record Count" << endl;
            cout << endl
                 << "6. Record Replace" << endl;
            cout << endl
                 << "7. Record Display" << endl;
            cin >> n;
            switch (n)
            {
            case 1:
            {
                  obj.record_Input();
                  break;
            }
            case 2:
            {
                  obj.record_Insert();
                  break;
            }
            case 3:
            {
                  obj.delete_Record();
                  break;
            }
            case 4:
            {
                  obj.record_Search();
                  break;
            }
            case 5:
            {
                  obj.record_Count();
                  break;
            }
            case 6:
            {
                  obj.record_Replace();
                  break;
            }
            case 7:
            {
                  obj.record_Display();
                  break;
            }
            }
            char choice='y';
            cout<<"Do you wish to perform more operations? (y/n)";
            if(choice=='y' || choice=='Y')
            continue;
            else
            break;

      }

}