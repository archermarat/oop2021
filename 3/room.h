#ifndef LAB4_ROOM_H
#define LAB4_ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include "container.h"

#include "cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"


namespace hotel {
    typedef struct Info {
        int day;
        int month;
        int year;
        int number_of_lodging_nights;

        friend std::ostream &operator<<(std::ostream &out, const Info &a) {
            out << "Date: " << a.day << "/" << a.month << "/" << a.year;
            out << "; Lodging nights: " << a.number_of_lodging_nights << std::endl;
            return out;
        };
    } Info;

    enum Type {
        SUITE = 0,
        SINGLE_ROOM,
        MULTI_BED_ROOM
    };

    class Room {
    protected:
        bool occupancy_; //занятость. 0 - свободно, 1 - занято
        std::vector<Info> living_info_; //информация о госте
        int daily_subsistence_allowance_; //суточные
    public:
        Room(int cost);

        virtual ~Room() = default;;


        virtual Type GetType() const = 0;

        bool GetOccupancy() const { return occupancy_; };

        int GetDSA() const { return daily_subsistence_allowance_; };

        virtual int GetNumberOfResidents() const = 0;


        void PrintTableElement(std::ostream &cout = std::cout) const;

        virtual void PrintInfo(std::ostream &cout = std::cout) const = 0;

        virtual void TakeRoom(Info info) = 0;

        virtual int VacateRoom() = 0;

        friend std::ostream &operator<<(std::ostream &out, Room *a) {
            a->PrintInfo(out);
            return out;
        };
    };


    class Single : public Room {
    public:
        Single() : Room(300) {};

        virtual ~Single() = default;;

        Type GetType() const override { return SINGLE_ROOM; };

        int GetNumberOfResidents() const override { if (occupancy_) return 1; else return 0; };

        void PrintInfo(std::ostream &cout = std::cout) const override { PrintTableElement(cout); };

        void TakeRoom(Info info) override { Room::TakeRoom(info); };

        int VacateRoom() override {
            return Room::VacateRoom();
        };
    };

    class Suite : public Room {
    private:
        int number_of_rooms_;
        int number_of_residents_;
    public:
        Suite(int number);

        virtual ~Suite() = default;;

        int GetNumberOfRooms() const { return number_of_rooms_; };

        int GetNumberOfResidents() const override { return number_of_residents_; };

        Type GetType() const override { return SUITE; };

        void SetNumberOfResidents(int n);

        void TakeRoom(Info info) override { Room::TakeRoom(info); };
        int VacateRoom() override {
            int sum = Room::VacateRoom();
            sum *= number_of_residents_;
            number_of_residents_ = 0;
            return sum;
        };

        void PrintInfo(std::ostream &cout = std::cout) const override {
            PrintTableElement(cout);
            cout << "Number of rooms: " <<
                 number_of_rooms_ << "\nNumber of residents: " << number_of_residents_ << std::endl;
        };

    };

    class Multi : public Room {
    private:
        int number_of_rooms_;
        int number_of_free_rooms_;
    public:
        Multi(int number);

        virtual ~Multi() = default;;

        int GetNumberOfRooms() const { return number_of_rooms_; };

        int GetNumberOfResidents() const override { return (number_of_rooms_ - number_of_free_rooms_); };

        Type GetType() const override { return MULTI_BED_ROOM; };

        int GetNumberOfFreeRooms() const { return number_of_free_rooms_; };

        void TakeRoom(Info info) override;

        int VacateRoom() override {
            int sum = Room::VacateRoom();
            number_of_free_rooms_ = number_of_rooms_;
            return sum;
        };

        void PrintInfo(std::ostream &cout = std::cout) const override;

        int RemoveResident(int i);
    };

    typedef container::MyContainer<int, Room *> TableElement;

    class Table {
    private:
        TableElement room_;
    public:
        Table() = default;

        void AddElement(int number, Type type);

        void DeleteElement(int number);

        TableElement::Iterator FindElement(int number) const;

        friend std::ostream &operator<<(std::ostream &out, const TableElement &a) {
            for (const auto &it: a) {
                out << it.first << " ";
                it.second->PrintTableElement();
            }
            return out;
        }

        void PrintTable();

        void PrintFreeRooms();
    };


}

#endif //LAB4_ROOM_H
