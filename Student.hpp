#ifndef StudentH
#define StudentH

class _student : public Person {
    private:
        int exam;
        vector<int> hw;
        double finalAvg, finalMed;
    
    public:
        _student() : exam(0), finalAvg(0), finalMed(0) {Person::fname = "", Person::lname = "";}
        _student(string _fname, string _lname, int exam, vector<int> hw, double finalAvg, double finalMed) : exam(exam), finalAvg(finalAvg), finalMed(finalMed) {fname = _fname, lname = _lname;}
        _student(const _student &s) : exam(s.getExam()), finalAvg(s.getAvg()), finalMed(s.getMed()) {
            hw.reserve(s.getHw().size());

            for(auto a : s.getHw()){
                hw.push_back(a);
            }
        }

        _student& operator=(const _student &s){

            if(&s == this) return *this;

            fname = s.getFname();
            lname = s.getLname();
            exam = s.getExam();
            finalAvg = s.getAvg();
            finalMed = s.getMed();
            hw.clear();
            hw.shrink_to_fit();
            hw.reserve(s.getHw().size());

            for(int a : s.getHw()) {
                hw.push_back(a);
            }

            return *this;

        }

        ~_student(){}

        _student(string fname, string lname, int exam, vector<int> hw);
        inline string getFname() const { return fname; }
        inline string getLname() const { return lname; }
        inline void setFname(string name) { _student::fname = name; }
        inline void setLname(string surname) { _student::lname = surname; }
        inline int getExam() const { return exam; }
        inline std::vector<int> getHw() const { return hw; }
        inline double getAvg() const { return finalAvg; }
        inline double getMed() const { return finalMed; }
        inline void setExam(int exam) { _student::exam = exam; }
        inline void addNd(int grade) { hw.push_back(grade); }
        inline void setHw(std::vector<int> hw) { _student::hw = hw; }
        inline void setAvg(double vid) { _student::finalAvg = vid; }
        inline void setMed(double med) { _student::finalMed = med; }
};

#endif