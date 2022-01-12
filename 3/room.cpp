#include <iostream>
#include "container.h"
#include "room.h"


std::ostream &operator<<(std::ostream &out, const hotel::Type &t) {
    switch (t) {
        case hotel::SUITE:
            return (out << "SUITE");
        case hotel::SINGLE_ROOM:
            return (out << "SINGLE ROOM");
        case hotel::MULTI_BED_ROOM:
            return (out << "MULTI-BED ROOM");
    }
    return (out);
}

void hotel::Room::PrintTableElement(std::ostream& cout) const {
    cout << "\nType: " << GetType() << "; Occupancy: " << occupancy_ << std::endl;
}

hotel::Room::Room(int cost) : occupancy_(false) {
    if (cost < 0)
        throw std::logic_error("Cost < 0");
    daily_subsistence_allowance_ = cost;
}

void hotel::Room::TakeRoom(Info info) {
    if (occupancy_) {
        throw std::logic_error("Room is occupied");
    }
    occupancy_ = true;
    living_info_.push_back(info);
}

int hotel::Room::VacateRoom() {
    occupancy_ = false;
    int cost = daily_subsistence_allowance_ * living_info_[0].number_of_lodging_nights;
    for (auto it = living_info_.begin(); it != living_info_.end();) {
        it = living_info_.erase(it);
    }
    return cost;
}

void hotel::Table::AddElement(int number, Type type) {
    auto it = room_.find(number);
    int number_of_rooms;
    if (it == room_.end()) {
        if (type == 0) {
            std::cout << "Enter the number of rooms in Suite (>= 2) : ";
            while (!(std::cin >> number_of_rooms) || number_of_rooms < 2) {
                std::cout << "Oops, You're wrong! Try again\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            room_.emplace(std::make_pair(number, new Suite(number_of_rooms)));
            return;
        } else if (type == 1)
            room_.emplace(std::make_pair(number, new Single()));
        else if (type == 2) {
            std::cout << "Enter the number of rooms in Multi-Bed room: (2-4) ";
            while (!(std::cin >> number_of_rooms) || number_of_rooms < 2 || number_of_rooms > 4) {
                std::cout << "Oops, You're wrong! Try again\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            room_.emplace(std::make_pair(number, new Multi(number_of_rooms)));
        }

    } else std::cout << "Room with that number is already exists" << std::endl;
}

void hotel::Table::DeleteElement(int number) {
    container::iterator<int, Room*> it = FindElement(number);
    if (it != room_.end()) {
        room_.erase(it);
        std::cout << "Room with number " << number << " was deleted" << std::endl;
    } else std::cout << "Room with that number doesn't exist" << std::endl;
}

void hotel::Table::PrintTable() {
    container::iterator<int, Room*> it = room_.begin();
    for (; it != room_.end(); ++it) {
        std::cout << "Number: " << (*it).first << " ";
        std::cout << (*it).second;
    }
}

void hotel::Table::PrintFreeRooms() {
    container::iterator<int, Room*> it = room_.begin();
    for (; it != room_.end(); it++)
        if (!(*it).second->GetOccupancy()) {
            std::cout << "Number: " << (*it).first << " ";
            std::cout << (*it).second;
        }
}

container::MyContainer<int, hotel::Room*>::Iterator hotel::Table::FindElement(int number) const {
    container::iterator<int, Room*> it = room_.find(number);
    if(it != room_.end()) {
    while((*it).first != number) it++;
    }
    return it;
}


hotel::Suite::Suite(int number) : Room(number * 600), number_of_residents_(0) {
    if (number < 2) {
        throw std::logic_error("too small amount of rooms for Suite");
    }
    number_of_rooms_ = number;
}

void hotel::Suite::SetNumberOfResidents(int n) {
    if (n < 1 || n > 2) {
        throw std::logic_error("Incorrect number of residents for Suite");
    }
    number_of_residents_ = n;
}

void hotel::Multi::TakeRoom(Info info) {
    if (!number_of_free_rooms_) {
        throw std::logic_error("Room is full");
    }
    living_info_.push_back(info);
    number_of_free_rooms_--;
    if (!number_of_free_rooms_) occupancy_ = true;
}

int hotel::Multi::RemoveResident(int i) {
    int sum;
    sum = living_info_[i].number_of_lodging_nights * daily_subsistence_allowance_;
    auto it = living_info_.begin();
    for (int k = 0; k < i; k++) it++;
    living_info_.erase(it);
    number_of_free_rooms_++;
    if (number_of_free_rooms_ == number_of_rooms_)
        occupancy_ = false;
    return sum;
}

hotel::Multi::Multi(int number) : Room(200) {
    if (number < 2) {
        throw std::logic_error("too small amount of rooms for Suite");
    }
    number_of_rooms_ = number;
    number_of_free_rooms_ = number_of_rooms_;
}

void hotel::Multi::PrintInfo(std::ostream& cout) const {
    PrintTableElement();
    std::for_each(living_info_.begin(), living_info_.end(), [&cout](const Info n) { cout << n ; });
}


