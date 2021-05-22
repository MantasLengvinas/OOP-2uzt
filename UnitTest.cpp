#define CATCH_CONFIG_MAIN
#include "main.hpp"

TEST_CASE("Testing student class") {

    _student stud;

    REQUIRE(stud.getHw().size() == 0);
    SECTION("Set name and surname") {
        stud.setfname("Name");
        stud.setlname("Surname");

        REQUIRE(stud.getfname() == "Name");
        REQUIRE(stud.getlname() == "Surname");
    }
    SECTION("Adding one grade") {
        stud.setOneHw(10);

        REQUIRE(stud.getHw().size() == 1);
        REQUIRE(stud.getHw().at(0) == 10);
    }
    SECTION("Adding multiple grades") {
        vector<int> grades{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        stud.setHw(grades);

        REQUIRE(stud.getHw().size() == 10);
        REQUIRE(stud.getHw() == grades);
    }
}