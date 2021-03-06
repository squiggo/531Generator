#include "531.h"

Generator::Generator() {
    std::cout << "Welcome to 5/3/1 generator!" << std::endl;
}

void Generator::getMaxes() { // Update maxes
    std::cout << "You will now enter your 1RM for the main lifts." << std::endl
              << "The lifts will not display as your 1RM, but but" << std::endl
              << "as your training max. Your training max is 90% " << std::endl
              << "of your 1RM. This is the max used in the 531 t-" << std::endl
              << "raining program." << std::endl;
    std::cout << "Squat : ";
    std::cin >> maxes[squat];
    std::cout << "Bench : ";
    std::cin >> maxes[bench];
    std::cout << "Deadlift : ";
    std::cin >> maxes[deadlift];
    std::cout << "OHP : ";
    std::cin >> maxes[ohp];
    tMax[squat] = (maxes[squat] * 0.9);
    tMax[bench] = maxes[bench] * 0.9;
    tMax[deadlift] = maxes[deadlift] * 0.9;
    tMax[ohp] = maxes[ohp] * 0.9;

    std::ofstream Saves("Maxes.txt", std::ofstream::out);
    Saves << tMax[squat] << std::endl;
    Saves << tMax[bench] << std::endl;
    Saves << tMax[deadlift] << std::endl;
    Saves << tMax[ohp] << std::endl;
    Saves.close();
}

void Generator::generateProgramFromCustomMaxes(int squatTMax, int benchTMax,
                                               int deadlidtTMax, int ohpTMax) {
    for (int i = 0; i < 4; i++) {
        if (maxes[i] == 0) {
            std::cout
                << "You need to enter your maxes first.\nDo that by choosing "
                   "\"update maxes\"\nat the main menu.\n";
            return;
        }
    }
    generateSets("Squat", 1, tMax[squat]);
    generateSets("Bench", 1, tMax[bench]);
    generateSets("Deadlift", 1, tMax[deadlift]);
    generateSets("OHP", 1, tMax[ohp]);
    std::cout << "WEEK 2:\tWEEK 2:\tWEEK 2:\tWEEK 2:\tWEEK 2:\tWEEK 2:"
              << std::endl;
    generateSets("Squat", 2, tMax[squat]);
    generateSets("Bench", 2, tMax[bench]);
    generateSets("Deadlift", 2, tMax[deadlift]);
    generateSets("OHP", 2, tMax[ohp]);
    std::cout << "WEEK 3:\tWEEK 3:\tWEEK 3:\tWEEK 3:\tWEEK 3:\tWEEK 3:"
              << std::endl;
    generateSets("Squat", 3, tMax[squat]);
    generateSets("Bench", 3, tMax[bench]);
    generateSets("Deadlift", 3, tMax[deadlift]);
    generateSets("OHP", 3, tMax[ohp]);
    std::cout << "DELOAD:\tDELOAD:\tDELOAD:\tDELOAD:\tDELOAD:\tDELOAD:"
              << std::endl;
    generateSets("Squat", 4, tMax[squat]);
    generateSets("Bench", 4, tMax[bench]);
    generateSets("Deadlift", 4, tMax[deadlift]);
    generateSets("OHP", 4, tMax[ohp]);
}

void Generator::generateSets(const char name[], int week, int tMax) {
    std::cout << "\t\tWeek" << week << std::endl;
    std::cout << "\t" << name << " : " << std::endl;
    if (week != 4) {
        std::cout << "\tWarmup: " << std::endl;
        std::cout << "\t    Set 1 : " << tMax * 0.4 << " x 5" << std::endl;
        std::cout << "\t    Set 2 : " << tMax * 0.5 << " x 5" << std::endl;
        std::cout << "\t    Set 3 : " << tMax * 0.6 << " x 3" << std::endl;
    }
    for (int i = 4; i < 7; i++) {
        std::cout << "\t    Set " << i << " : "
                  << checkForWeekAndReturnKG(week, i - 3, tMax) << " x "
                  << checkForWeekAndReturnSets(week, i - 3) << std::endl;
    }
}

int Generator::checkForWeekAndReturnSets(int week, int reps) {
    switch (week) {
    case 1:
        return 5;
    case 2:
        return 3;
    case 3:
        switch (reps) {
        case 1:
            return 5;
        case 2:
            return 3;
        case 3:
            return 1;
        }
    case 4:
        return 5;
    default:
        break;
    }
    return -1;
}

double Generator::checkForWeekAndReturnKG(int week, int set, int tMax) {
    switch (week) {
    case 1:
        switch (set) {
        case 1:
            return tMax * 0.65;
        case 2:
            return tMax * 0.75;
        case 3:
            return tMax * 0.85;
        default:
            break;
        }
        break;
    case 2:
        switch (set) {
        case 1:
            return tMax * 0.7;
        case 2:
            return tMax * 0.8;
        case 3:
            return tMax * 0.9;
        default:
            break;
        }
        break;
    case 3:
        switch (set) {
        case 1:
            return tMax * 0.75;
        case 2:
            return tMax * 0.85;
        case 3:
            return tMax * 0.95;
        default:
            break;
        }
        break;
    case 4:
        switch (set) {
        case 1:
            return tMax * 0.4;
        case 2:
            return tMax * 0.5;
        case 3:
            return tMax * 0.6;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return 0.0;
}

void Generator::generateCSVSets(const char name[], int week, int tMax,
                                std::ofstream& File) {

    File << "Week" << week << std::endl;
    File << name << ": " << std::endl;
    if (week != 4) {
        File << "Set 1 :," << tMax * 0.4 << ", x 5" << std::endl;
        File << "Set 2 :," << tMax * 0.5 << ", x 5" << std::endl;
        File << "Set 3 :," << tMax * 0.6 << ", x 3" << std::endl;
    }
    for (int i = 4; i < 7; i++) {
        File << "Set " << i << " :,"
             << checkForWeekAndReturnKG(week, i - 3, tMax) << ", x "
             << checkForWeekAndReturnSets(week, i - 3) << std::endl;
    }
}

void Generator::createCSVFile() {
    // Eror checking
    for (int i = 0; i < 4; i++) {
        if (maxes[i] == 0) {
            std::cerr << "Error! You have to have entered your maxes!"
                      << std::endl;
            return;
        }
        if (tMax[i] == 0) {
            std::cerr
                << "Error! tMax's not initalized. Have you entered your maxes?"
                << std::endl;
            return;
        }
    }

    std::ofstream File("program.csv", std::ofstream::out); // Open program.csv
    if (File.fail()) {                                     // Errorcheck
        std::cout << "An error occured while opening program.csv" << std::endl;
        return;
    }
    // Generates the sets
    generateCSVSets("Squat", 1, tMax[squat], File);
    generateCSVSets("Bench", 1, tMax[bench], File);
    generateCSVSets("Deadlift", 1, tMax[deadlift], File);
    generateCSVSets("OHP", 1, tMax[ohp], File);
    generateCSVSets("Squat", 2, tMax[squat], File);
    generateCSVSets("Bench", 2, tMax[bench], File);
    generateCSVSets("Deadlift", 2, tMax[deadlift], File);
    generateCSVSets("OHP", 2, tMax[ohp], File);
    generateCSVSets("Squat", 3, tMax[squat], File);
    generateCSVSets("Bench", 3, tMax[bench], File);
    generateCSVSets("Deadlift", 3, tMax[deadlift], File);
    generateCSVSets("OHP", 3, tMax[ohp], File);
    generateCSVSets("Squat", 4, tMax[squat], File);
    generateCSVSets("Bench", 4, tMax[bench], File);
    generateCSVSets("Deadlift", 4, tMax[deadlift], File);
    generateCSVSets("OHP", 4, tMax[ohp], File);
}

void Generator::make1RM() {
    float weight = 0.0f;
    int reps = 0;
    float oneRM = 0.0f;
    std::cout << "Weight lifted: ";
    std::cin >> weight;
    if (weight <= 0.0f) {
        std::cout << "You need to enter a number. E.g 42.5" << std::endl;
        return;
    }
    std::cout << "Reps: ";
    std::cin >> reps;
    if (reps <= 0) {
        std::cout << "You need to enter a number. E.g. 5" << std::endl;
        return;
    }
    oneRM = weight * (36.0f / (37.0f - float(reps)));

    std::cout << "Your 1RM is =~ " << oneRM << std::endl;
}