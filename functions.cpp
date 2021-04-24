#include "main.hpp"


unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::uniform_real_distribution<double> distribution (1, 11);

bool _check(_student &a, _student &b){

    return a.getLname() < b.getLname();

}

bool _checkAvg(_student &a, _student &b){
    return a.getAvg() < b.getAvg();
}

bool doFileExist(string fileName) {
    std::ifstream f(fileName.c_str());
	return f.good();
}

bool _checkIfWinner(_student s) {
    return s.getAvg() >= 5;
}

void checkForInputFiles(vector<int> fsizes, double& timeElapsed) {
    for(int i = 0; i < fsizes.size(); i++){
        string fileName = "data/input/studentai" + std::to_string(fsizes.at(i)) + ".txt";

        if(!doFileExist(fileName)){
            cout << "Generuojamas studentai" << fsizes.at(i) << ".txt duomenu failas..." << endl;
            clockStart = std::chrono::steady_clock::now();
            generateInputFile(fsizes.at(i));
            timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
            cout << endl << "Failo studentai" << fsizes.at(i) << ".txt generavimas uztruko " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << " s" << endl;
        }
    }
}

void checkInput(char& choice) {

	while (cin.fail() || tolower(choice) != 't' && tolower(choice) != 'n'){
		if (cin.fail())
			cout << "Ivestis netinkama (Ivedete skaiciu)" << endl;
		else if(tolower(choice) != 't' && tolower(choice) != 'n')
			cout << "Neteisingas pasirinkimas! Galimi pasirinkimai: t (taip) arba n (ne)!" << endl;

		cin.clear();
		cin.ignore(256, '\n');
		cout << "Pakartokite ivedima (t/n): ";
		cin >> choice;
	}
}

void checkInput(int &input) {

	while (cin.fail() || input < 0 || input > 10){
		if (cin.fail())
			cout << "Ivestis netinkama (Ivedete raide)" << endl;
		else if(input < 0)
			cout << "Skaicius negali buti mazesnis uz 0!" << endl;
        else if(input > 10)
            cout << "Skaicius negali buti didesnis uz 10!" << endl;

		cin.clear();
		cin.ignore(256, '\n');
		cout << "Iveskite skaiciu is naujo: ";
		cin >> input;
	}
}

int RandomGrade(){
    return distribution(generator);
}

void generateGrades(int n, vector<int> &hw) {
    for(int i = 0; i < n; i++){
        hw.push_back(RandomGrade());
    }
}

void generateInputFile(int n){
    string fileName = "studentai" + std::to_string(n) + ".txt";
    std::ofstream output;

	output.open("data/input/" + fileName);
	output << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" ;

	int noOfHomework = 20;

	for (int i = 0; i < noOfHomework; i++)
	{
		output << std::setw(7) << "ND" + std::to_string(i + 1);
	}
	output << std::setw(7) << "Egz." << std::endl;

	for (int i = 0; i < n; i++)
	{
		int grades = RandomGrade();
		output << std::setw(20) << "Vardas" + std::to_string(i + 1) << std::setw(20) << "Pavarde" + std::to_string(i + 1);

		for (int i = 0; i < noOfHomework; i++)
		{
			output << std::setw(7) << RandomGrade();
		}
		output << std::setw(7) << RandomGrade();
		if(i != n - 1) output << std::endl;
	}
	output.close();
}

double calcAvg(vector<int> hw, int egz) {

    double sum = 0;

    for(int a : hw){
        sum += a;
    }

    return 0.4 * (sum / hw.size()) + 0.6 * egz;
}

double calcMed(vector<int> hw){ 

    double median = 0;

    for (int i = 0; i < hw.size(); i++){

        if (hw.size() % 2 == 1)
            median = hw[hw.size() / 2];

        else median = (hw[hw.size() / 2] + hw[hw.size() / 2 - 1]) / 2;
    }

    return median;
}

void generateDirectories(std::string directory){
	try {
		int dir = _mkdir(directory.c_str());

		if (dir == 0)
			std::cout << "Sukurtas aplankas " + directory << std::endl;
		else if(dir != 0 && errno == EEXIST){
        }
		else throw(1);
	}
	catch (int err){
		std::cout << "Ivyko klaida aplankalu kurimo metu! Programa nutraukia veikla.";
		exit(1);
	}
}

void readFile(vector<_student> &Students){

    try{

        std::ifstream input(file);

        if(!input){
            throw 1;
        }

        if(input.eof()){
            throw 4;
        }

        _student student;

        string line, name, surname;
        int val;
        vector<int> grades;

        input.ignore(255, '\n');

        while(true){

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

                grades.push_back(val);
            }

            grades.pop_back();
            student.setExam(val);
            student.setHw(grades);

            Students.push_back(student);
            grades.clear();

            if(input.eof()){
                break;
            }

        }

        input.close();

    }
    catch(int e) {

        switch (e)
        {
        case 1:
            cout << "Failas nerastas" << endl;
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

string selectFile() {

    int choice;

    cout << "Pasirinkite faila, kuri norite skaityti: "
        << endl << "(1) studentai1000.txt"
        << endl << "(2) studentai10000.txt"
        << endl << "(3) studentai100000.txt"
        << endl << "(4) studentai1000000.txt"
        << endl << "(5) studentai10000000.txt"
        << endl; cin >> choice;


    switch (choice){
        case 1:
            return "1000";
            break;
        case 2:
            return "10000";
            break;
        case 3:
            return "100000";
            break;
        case 4:
            return "1000000";
            break;
        case 5:
            return "10000000";
            break;
    
        default:
            cout << "Jusu ivestas pasirinkimas neteisingas!" << endl;
            exit(1);
            break;
    }

    return "0";
}

// void readSelectedFile(vector<_student> &Students, string file) {

//     std::ifstream input;
//     string fileName = "studentai" + file + ".txt";

//     _student student;

//     string line;
//     int val;
//     vector<int> grades;

//     try{
//         input.open("data/input/" + fileName);
//         if(!input){
//             throw 1;
//         }
//         if(input.eof()){
//             throw 2;
//         }
// 	    input.ignore(256, '\n');

//         while(!input.eof()){
//             input >> student.fname >> student.lname;
//             getline(input, line);
//             std::istringstream str(line);

//             if(!str){
//                 throw 2;
//             }

//             int val;
//             while(str >> val){

//                 if(val < 1 || val > 10){
//                     throw 3;
//                 }

//                 grades.push_back(val);
//             }

//             grades.pop_back();
//             student.exam = val;
//             student.hw = grades;

//             Students.push_back(student);
//             grades.clear();
//         }
//     }
//         catch(int e) {
//             switch (e)
//             {
//             case 1:
//                 cout << "Nepavyko atidaryti failo" << endl;
//                 break;
//             case 2:
//                 cout << "Neteisingas failo formatas" << endl;
//                 break;
//             case 3:
//                 cout << "Pazymys nepriklauso intervalui [1, 10]" << endl;
//                 break;
//             case 4:
//                 cout << "Failas tuscias" << endl;
//                 break;
            
//             default:
//                 cout << "Programos klaida" << endl;
//                 break;
//             }

//         cout << "Programa baigia darba ";
//         exit(1);
//     }


    
// }

void addStudent(vector<_student> &Students) {

    srand(time(0));

    _student stud;
    int gr, exam;
    int n = 0; // n yra kaip iterator toje dalyje, kai yra nezinomas pazymiu kiekis
    vector<int> hw;
    char choice;
    string name, surname;

    cout << "Iveskite studento varda: ";
    getline(cin, name);
    stud.setFname(name);
    
    cout << "Iveskite studento pavarde: ";
    getline(cin, surname);
    stud.setLname(surname);

    cout << "Ar yra zinomas namu darbu pazymiu skaicius? (t/n) ";
    cin >> choice;
    checkInput(choice);

    if(tolower(choice) == 't'){

        cout << "Iveskite namu darbu pazymiu kieki: "; cin >> n;
        checkInput(n);

        cout << "Ar norite patys ivesti pazymius uz namu darbus? (t/n) "; cin >> choice; cout << '\n';
        checkInput(choice);

        if(tolower(choice) == 't'){
            for(int i = 0; i < n; i++){
                cout << "Iveskite " << i + 1 << "-a pazymi: ";
                cin >> gr;
                checkInput(gr);
                hw.push_back(gr);
            }
        }
        else if(tolower(choice) == 'n'){
            generateGrades(n, hw);
        }

    }else if(tolower(choice) == 'n'){

        cout << "Ar norite patys ivesti pazymius uz namu darbus? (t/n) "; cin >> choice; cout << '\n';

        if(tolower(choice) == 't'){

            cout << "Noredami baigti pazymiu ivedima, iveskite 0" << endl;

            while(true){
                
                cout << "Iveskite " << n + 1 << "-a pazymi: "; cin >> gr;
                checkInput(gr);

                if(gr == 0){
                    break;
                }
                else {
                    n++;
                    hw.push_back(gr);
                }

            }
        }else if(tolower(choice) == 'n'){
            n = rand() % 11;

            if(n != 0) {
                generateGrades(n, hw);
            }
        }
    }

    cout << "Ar norite patys ivesti egzamino vertinima? (t/n) "; cin >> choice; cout<< '\n';
    checkInput(choice);

    if(tolower(choice) == 't'){
        cout << "Iveskite egzamino vertinima: "; cin >> exam;
        checkInput(exam);
        stud.setExam(exam);
    }
    else if(tolower(choice) == 'n'){
        stud.setExam(rand() % 10 + 1);
        cout << "Sugeneruotas egzamino vertinimas: " << stud.getExam() << '\n';
    }

    stud.setHw(hw);

    Students.push_back(stud);

}

void outputAvg(vector<_student> Students, string file) {
    std::ofstream output(file);
    output << std::left
        << std::setw(20) << "Pavarde"
        << std::setw(15) << "Vardas"
        << std::setw(10) << "Galutinis (Vid.)"
        << std::endl
        << std::string(65, '-')
        << std::endl;

    for (int i = 0; i < Students.size(); i++){          
        output << std::left
            << std::setw(20) << Students[i].getLname()
            << std::setw(15) << Students[i].getFname()
            << std::setw(15) << std::setprecision(2) << Students[i].getAvg()
            << std::endl;
    }
}

void outputMed(vector<_student> Students, string file) {
    std::ofstream output(file);
    output << std::left
        << std::setw(20) << "Pavarde"
        << std::setw(15) << "Vardas"
        << std::setw(10) << "Galutinis (Med.)"
        << std::endl
        << std::string(65, '-')
        << std::endl;

    for (int i = 0; i < Students.size(); i++){          
        output << std::left
            << std::setw(20) << Students[i].getLname()
            << std::setw(15) << Students[i].getFname()
            << std::setw(15) << std::setprecision(2) << Students[i].getMed()
            << std::endl;
    }
}