#include "main.hpp"
#include "windows.h"
#include "psapi.h"

int main(int argc, char* argv[]){

    std::chrono::steady_clock::time_point programStart = std::chrono::steady_clock::now();
	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);

    double timeElapsed = 0;

    char choice;
    vector<_student> Students;
    bool isFileReaded = false, manualInput = false, params = false;

    vector<int> fsizes = { 1000, 10000, 100000, 1000000, 10000000};

    generateDirectories("data");
    generateDirectories("data/input");
    generateDirectories("data/output");

    if(argc > 1) {

        checkForInputFiles(fsizes, timeElapsed);

        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "v") == 0 || strcmp(argv[i], "d") == 0 || strcmp(argv[i], "l") == 0) {
                params = true;
            }
        }
        if(params) {

            for(int i = 1; i < argc; i++){
                for (int j = 0; j < fsizes.size(); j++){

                    double benchmarking = 0;
                    
                    if(strcmp(argv[i], "v") == 0){

                        vector<_student> Students;

                        automated(Students, fsizes[j], timeElapsed, benchmarking);

                        clockStart = std::chrono::steady_clock::now();
                        
                        auto iterator = std::stable_partition(Students.begin(), Students.end(), _checkIfWinner());
                        std::vector<_student> vargsiukai(std::make_move_iterator(iterator), std::make_move_iterator(Students.end()));
                        Students.erase(iterator, Students.end());

                        std::sort(Students.begin(), Students.end(), _check);
                        std::sort(vargsiukai.begin(), vargsiukai.end(), _check);

                        timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                        benchmarking += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                        
                        std::cout << "Duomenu rusiavimas i kategorijas uztruko " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << " s" << std::endl;
                        
                        outputToFile(Students, vargsiukai, argv[i], std::to_string(fsizes[j]), benchmarking);

                    }

                    if(strcmp(argv[i], "d") == 0){
                        
                        std::deque<_student> Students;

                        automated(Students, fsizes[j], timeElapsed, benchmarking);

                        clockStart = std::chrono::steady_clock::now();

                        auto iterator = std::stable_partition(Students.begin(), Students.end(), _checkIfWinner());
                        std::deque<_student> vargsiukai(std::make_move_iterator(iterator), std::make_move_iterator(Students.end()));
                        std::sort(Students.begin(), Students.end(), _check);
                        std::sort(vargsiukai.begin(), vargsiukai.end(), _check);

                        timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                        benchmarking += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                        
                        std::cout << "Duomenu rusiavimas i kategorijas uztruko " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << " s" << std::endl;

                        outputToFile(Students, vargsiukai, argv[i], std::to_string(fsizes[j]), benchmarking);

                    }

                    if(strcmp(argv[i], "l") == 0){

                        std::list<_student> Students;

                        automated(Students, fsizes[j], timeElapsed, benchmarking);
                        
                        clockStart = std::chrono::steady_clock::now();

                        auto iterator = std::stable_partition(Students.begin(), Students.end(), _checkIfWinner());
                        std::list<_student> vargsiukai(std::make_move_iterator(iterator), std::make_move_iterator(Students.end()));
                        Students.sort(_check);
                        vargsiukai.sort(_check);

                        timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                        benchmarking += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

                        std::cout << "Duomenu rusiavimas i kategorijas uztruko " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << " s" << std::endl;
                    
                        outputToFile(Students, vargsiukai, argv[i], std::to_string(fsizes[j]), benchmarking);

                    }

                }
            }
        }
        else {
            cout << "Ivesti netinkami parametrai!" << endl << "Programa baigia darba!" <<endl;
            exit(1);
        }
    }

    else {
        cout << "Ar norite duomenis irasinet rankiniu budu? (t/n) (Pasirinkus [N] visi veiksmai bus atliekami su failais) "; cin >> choice;
        checkInput(choice);

        if(tolower(choice) == 't'){
            manualInput = true;
            cin.ignore();
            while(true){

                addStudent(Students);

                cout << "Ar norite prideti dar 1 studenta? (t/n) "; cin >> choice;
                cin.ignore();
                checkInput(choice);

                if(tolower(choice) == 'n'){
                    break;
                }
                else if(tolower(choice) == 't'){
                    continue;
                }

            }
        }
        else if(tolower(choice) == 'n'){

            cout << "Ar norite generuoti duomenu failus? (t/n) (Pasirinkus [N], jus galesite pasirinkti faila skaitymui) "; cin >> choice;
            checkInput(choice);

            if(tolower(choice) == 't') {
                
                for(int s : fsizes) {
                    cout << "Ar norite generuoti " << s << " studentu duomenu faila? (t/n) "; cin >> choice;
                    checkInput(choice); 

                    if(tolower(choice) == 't') {
                        clockStart = std::chrono::steady_clock::now();
                        generateInputFile(s);
                        cout << endl << "Failo studentai" << s << ".txt generavimas uztruko " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
                        timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                    }
                    else if(tolower(choice) == 'n') {
                        continue;
                    }
                }

            }
            else if(tolower(choice) == 'n'){
                string selectedFile = selectFile();
                clockStart = std::chrono::steady_clock::now();
                readSelectedFile(Students, selectedFile);
                cout << endl << "Failo studentai" << selectedFile << ".txt nuskaitymas uztruko " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
                timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
                isFileReaded = true;
            }
        }

        if(!isFileReaded && !manualInput){
            string selectedFile = selectFile();
            clockStart = std::chrono::steady_clock::now();
            readSelectedFile(Students, selectedFile);
            cout << endl << "Failo studentai" << selectedFile << ".txt nuskaitymas uztruko " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
            timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
        }

        std::sort(Students.begin(), Students.end(), _check);

        // Rezultatu skaiciavimas
        clockStart = std::chrono::steady_clock::now();
        for(int i = 0; i < Students.size(); i++) {

            double avg = 0;
            for(auto grade : Students[i].getHw()){
                avg += grade;
            }
            avg /= Students[i].getHw().size();

            Students[i].setAvg(0.4 * avg + 0.6 * Students[i].getExam());
            Students[i].setMed(calcMed(Students[i].getHw()) * 0.4 + Students[i].getExam() * 0.6);
        }
        cout << "Galutiniu balu skaiciavimas uztruko: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
        timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

        // Rusiavimas
        vector<_student> kietiakai, vargsiukai;

        cout << "Studentus norite rusiuoti pagal vidurki (t) ar pagal mediana (n)? "; cin >> choice;
        checkInput(choice);

        if(tolower(choice) == 't'){
            clockStart = std::chrono::steady_clock::now();
            for(auto s : Students) {

                if(s.getAvg() <= 4.9){
                    vargsiukai.push_back(s);
                }
                else {
                    kietiakai.push_back(s);
                }
            }
            cout << "Duomenu rusiavimas i 2 kategorijas uztruko: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
            timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            clockStart = std::chrono::steady_clock::now();
            outputAvg(kietiakai, "data/output/kietiakai.txt");
            outputAvg(vargsiukai, "data/output/vargsiukai.txt");
            cout << "Duomenu isvedimas i du naujus failus uztruko: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
            timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
        }
        else if(tolower(choice) == 'n') {
            clockStart = std::chrono::steady_clock::now();
            for(auto s : Students) {
                if(s.getMed() <= 4.9){
                    vargsiukai.push_back(s);
                }
                else {
                    kietiakai.push_back(s);
                }
            }
            cout << "Duomenu rusiavimas i 2 kategorijas uztruko: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
            timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            clockStart = std::chrono::steady_clock::now();
            outputMed(kietiakai, "data/output/kietiakai.txt");
            outputMed(vargsiukai, "data/output/vargsiukai.txt");
            cout << "Duomenu isvedimas i du naujus failus uztruko: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << endl;
            timeElapsed += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
        }
    }


    cout << endl << "Visi programos veiksmai uztruko " << timeElapsed << "s" <<endl;
    cout << "Programos gyvavimo laikas: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - programStart).count() << " s.";

    return 0;
}

