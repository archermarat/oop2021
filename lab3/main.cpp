#include <iostream>
#include "room.h"
#include "main.h"


int choice_check(int &num, int range1, int range2) {
    while (!(std::cin >> num) || num < range1 || num > range2) {
        std::cout << "Oops, you're wrong. Try again!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}

typedef int (*Menu_Processing_Function_Pointer)(hotel::Table &);

struct Menu_Option {
    char choice;
    char const *p_selection_text;
    Menu_Processing_Function_Pointer p_processing_function;
};

static const Menu_Option table_menu[] =
        {
                {'0', "Go to hotel menu",},
                {'1', "Add the room",    DialogTableAdd},
                {'2', "Delete the room", DialogTableDelete},
                {'3', "Show the table",  DialogTablePrint}
        };

static const Menu_Option hotel_menu[] =
        {
                {'0', "Quit",},
                {'1', "Registration",    DialogResidentAdd},
                {'2', "Eviction",        DialogResidentDelete},
                {'3', "Show free rooms", DialogPrintFreeRooms},
        };

static const size_t quantity_selections_table_menu =
        sizeof(table_menu) / sizeof(table_menu[0]);

static const size_t quantity_selections_hotel_menu =
        sizeof(hotel_menu) / sizeof(hotel_menu[0]);


int DialogTableAdd(hotel::Table &table) {
    int number, k;
    hotel::Type type;
    std::cout << "Enter the room number you want to add\n";
    choice_check(number, 0, 100);
    std::cout << "Choose a room type\n1. Suite\n2. Single\n3. Multi-Bed Room\n";
    choice_check(k, 1, 3);
    if (k == 1) type = hotel::SUITE;
    else if (k == 2) type = hotel::SINGLE_ROOM;
    else type = hotel::MULTI_BED_ROOM;
    try {
        table.AddElement(number, type);
    }
    catch (const std::exception &e) {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    return 1;
}

int DialogTableDelete(hotel::Table &table) {
    int number;
    std::cout << "Enter the room number you want to delete\n";
    choice_check(number, 0, 100);
    table.DeleteElement(number);
    return 1;
}

int DialogTablePrint(hotel::Table &table) {
    table.PrintTable();
    return 1;
}

int DialogResidentAdd(hotel::Table &table) {
    int number;//, day, month, year;
    char slash;
    hotel::Info info;
    std::cout << "Enter the number of room you want to take\n";
    choice_check(number, 0, 100);
    if (table.FindElement(number) != nullptr) {
        std::cout << "Enter Day/Month/Year of registration and amount of days to reserve\n";
        std::cin >> info.day >> slash >> info.month >> slash >> info.year >> info.number_of_lodging_nights;
        while (!std::cin.good()) {
            std::cout << "You're wrong. Try again!";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> info.day >> slash >> info.month >> slash >> info.year >> info.number_of_lodging_nights;
        }
        try {
            if ((*table.FindElement(number)).second->GetType() == hotel::SUITE) {
                hotel::Suite *suite;
                suite = dynamic_cast<hotel::Suite *>(((*table.FindElement(number)).second));
                std::cout << "How many residents register?\n";
                choice_check(number, 1, 2);
                suite->SetNumberOfResidents(number);
                suite->TakeRoom(info);
            } else {
                (*table.FindElement(number)).second->TakeRoom(info);
            }
        }
        catch (const std::exception &e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
    } else {
        std::cout << "Room does not exist" << std::endl;
    }
    return 1;
}

int DialogResidentDelete(hotel::Table &table) {
    int number, room;
    hotel::Type type;
    std::cout << "Enter the number of room you want to vacate\n";
    choice_check(number, 0, 100);
    if (table.FindElement(number) != nullptr) {
        try {
            type = (*table.FindElement(number)).second->GetType();
            if (type == hotel::MULTI_BED_ROOM) {
                hotel::Multi *multi;
                multi = dynamic_cast<hotel::Multi *>(((*table.FindElement(number)).second));
                multi->PrintInfo();
                std::cout << "Please, choose room to vacate\n";
                choice_check(room, 0, multi->GetNumberOfResidents());
                std::cout << "Total cost: " << multi->RemoveResident(room) << std::endl;
            } else {
                std::cout << "Total cost: " << (*table.FindElement(number)).second->VacateRoom() << std::endl;
            }
        }
        catch (const std::exception &e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
    } else {
        std::cout << "Room does not exist" << std::endl;
    }
    return 1;
}

int DialogPrintFreeRooms(hotel::Table &table) {
    table.PrintFreeRooms();
    return 1;
}

int main() {
    int choice = 1;
    hotel::Table table;
    while (choice) {
        for (const auto &k: table_menu) {
            std::cout << k.choice << ". " << k.p_selection_text << "\n";
        }
        choice_check(choice, 0, quantity_selections_table_menu - 1);
        if (choice == 0) break;
        Menu_Processing_Function_Pointer p_function = table_menu[choice].p_processing_function;
        (p_function)(table);
    }

    choice = 1;
    while (choice) {
        for (const auto &k: hotel_menu) {
            std::cout << k.choice << ". " << k.p_selection_text << "\n";
        }
        choice_check(choice, 0, quantity_selections_hotel_menu - 1);
        if (choice == 0) break;
        Menu_Processing_Function_Pointer p_function = hotel_menu[choice].p_processing_function;
        (p_function)(table);

    }

    return EXIT_SUCCESS;
}
