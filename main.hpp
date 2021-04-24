#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <random>
#include <io.h>
#include <direct.h>
#include <list>
#include <deque>
#include <iterator>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

#include "Student.hpp"

const char file[] = "kursiokai.txt"; //Duomenu failo pavadinimas
const char outputFile[] = "output.txt"; //Rezultatu failo pavadinimas

static std::chrono::steady_clock::time_point clockStart;

bool _check(_student &a, _student &b);
bool _checkAvg(_student &a, _student &b);
bool _checkIfWinner(_student s);
void checkInput(char& choice);
void checkInput(int &input);
void readFile(vector<_student> &Students);
void generateDirectories(std::string directory);
void generateGrades(int n, vector<int> &arr);
void generateInputFile(int n);
void checkForInputFiles(vector<int> fsizes, double& timeElapsed);
string selectFile();
//void readSelectedFile(vector<_student> &Students, string file);
double calcAvg(vector<int> hw, int egz);
double calcMed(vector<int> hw);
void addStudent(vector<_student> &Students);
void outputMed(vector<_student> Students, string file);
void outputAvg(vector<_student> Students, string file);

template <class T> 
void readSelectedFile(T& Students, string fileSize){
    
    std::ifstream input;
    string fileName = "studentai" + fileSize + ".txt";

    _student student;

    string line, name, surname;
    int val;
    double avg = 0;
    vector<int> grades;

    try{
        input.open("data/input/" + fileName);
        if(!input){
            throw 1;
        }
        if(input.eof()){
            throw 2;
        }
	    input.ignore(256, '\n');

        while(!input.eof()){
            input >> name >> surname;
            student.setFname(name);
            student.setLname(surname);
            getline(input, line);
            std::istringstream str(line);

            if(!str){
                throw 2;
            }

            int val;
            while(str >> val){

                if(val < 1 || val > 10){
                    throw 3;
                }

                avg += val;
                grades.push_back(val);
            }

            grades.pop_back();
            student.setExam(val);
            student.setHw(grades);

            avg /= grades.size();

            student.setAvg(0.4 * avg + 0.6 * student.getExam());
            student.setMed(calcMed(student.getHw()) * 0.4 + student.getExam() * 0.6);

            Students.push_back(student);
            grades.clear();
        }
    }
        catch(int e) {
            switch (e)
            {
            case 1:
                cout << "Nepavyko atidaryti failo" << endl;
                break;
            case 2:
                cout << "Neteisingas failo formatas" << endl;
                break;
            case 3:
                cout << "Pazymys nepriklauso intervalui [1, 10]" << endl;
                break;
            case 4:
                cout << "Failas tuscias" << endl;
                break;
            
            default:
                cout << "Programos klaida" << endl;
                break;
            }

        cout << "Programa baigia darba ";
        exit(1);
    }
}

template <class T>
void automated(T& Students, int fileSize, double& timeEllapsed, double &benchmarking) {

    cout << "Nuskaitomas " << fileSize << " dydzio failas" << endl;
    clockStart = std::chrono::steady_clock::now();
    readSelectedFile(Students, std::to_string(fileSize));
    timeEllapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
    benchmarking += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
    std::cout << fileSize << " dydzio failo nuskaitymas uztruko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << " s" << std::endl;
}

// Sort using two containers: vargsiukai ant kietiakai

template <class T>
void sortIntoCategoriesUsingTwoContainers(T& Students, T& kietiakai, T& vargsiukai){
    for (auto it = Students.begin(); it != Students.end(); ++it){
		if (it->finalAvg >= 5.00)
			kietiakai.push_back(*it);
		else vargsiukai.push_back(*it);
	}
}

template <class T>
void sortIntoCategories(T& Students, T& vargsiukai){

    for(auto it = Students.begin(); it != Students.end(); ++it){

        if(it->finalAvg >= 5){
            vargsiukai.assign(Students.begin(), it);
            Students.erase(Students.begin(), it);
            break;
        }
    }

}

template <class T>
void writeToFile(T& arr, std::ostream& output) {
	output << std::left
		<< std::setw(20) << "Pavarde"
		<< std::setw(15) << "Vardas"
		<< std::setw(10) << "Galutinis " << "(Vid.)" << "\n"
		<< std::string(65, '-')
		<< "\n";

	for (auto const& a : arr)
	{
		output << std::left
			<< std::setw(20) << a.getLname()
			<< std::setw(15) << a.getFname()
			<< std::setw(15) << std::fixed << std::setprecision(2) << a.getAvg()
			<< "\n";
	}
}

template <class T>
void outputToFile(T& a, T& b, char container[], string fileSize, double& benchmarking) {

    string contName;

    switch(container[0]){
        case 'v':
            contName = "vector";
            break;
        case 'd':
            contName = "deque";
            break;
        case 'l':
            contName = "list";
            break;

    }

    cout << "Duomenu nuskaitymas i " << 
        contName << 
        " ir rusiavimas i kategorijas uztruko " << 
        benchmarking << " s" << endl;

    std::ofstream output;
    benchmarking = 0;

    cout << endl << "Duomenys irasomi i faila.." << endl;
    output.open("data/output/kietiakai_" + contName + fileSize + ".txt");
    writeToFile(a, output);
    output.close();

    output.open("data/output/vargsiukai_" + contName + fileSize + ".txt");
    writeToFile(b, output);
    output.close();

    cout << "Duomenu irasymas sekmingas" << endl << endl;

}

#endif