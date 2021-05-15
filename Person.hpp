  
#ifndef PersonH
#define PersonH

class Person {
protected:
    string fname;
    string lname;
    
public:
    virtual ~Person() = 0;
    string getfname() const { return fname; }
    std::string getlname() const { return lname; }
    void setfname(std::string fname) { Person::fname = fname; }
    void setlname(std::string lname) { Person::lname = lname; }
};

inline Person::~Person() {
}

#endif