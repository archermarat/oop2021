#ifndef LAB4_ROOM_H
#define LAB4_ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace hotel {
    typedef struct Info {
        int day;
        int month;
        int year;
        int number_of_lodging_nights;
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

        //void SetOccupancy(bool occupancy) {occupancy_ = occupancy;};
        //virtual void SetDSA() = 0;

        void PrintTableElement() const;

        virtual void PrintInfo() const = 0;

        virtual void TakeRoom(Info info) = 0;

        virtual int VacateRoom() = 0;

        friend std::ostream &operator<<(std::ostream &out, const Info &a);
    };


    class Single : public Room {
    public:
        Single() : Room(300) {};

        virtual ~Single() = default;;

        Type GetType() const override { return SINGLE_ROOM; };

        int GetNumberOfResidents() const override { if (occupancy_) return 1; else return 0; };

//        void SetDSA() override {daily_subsistence_allowance_ = 300;};

        void PrintInfo() const override { PrintTableElement(); };

        void TakeRoom(Info info) override { Room::TakeRoom(info); };

        int VacateRoom() override {
            Room::VacateRoom();
            return 1;
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

        //void SetDSA() override {daily_subsistence_allowance_ = number_of_rooms_ * 600;};
        //void SetNumberOfRooms(int n);
        void SetNumberOfResidents(int n);

        void TakeRoom(Info info) override { Room::TakeRoom(info); }; //?????????????????????????
        int VacateRoom() override {
            int sum = Room::VacateRoom();
            number_of_residents_ = 0;
            return sum * number_of_residents_;
        };

        void PrintInfo() const override {
            PrintTableElement();
            std::cout << "Number of rooms: " <<
                      number_of_rooms_ << "\n Number of residents: " << number_of_residents_;
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

        void PrintInfo() const override;

        int RemoveResident(int i);
    };


    class Table {
    private:
        std::map<int, Room *> room_;
    public:
        Table() = default;

        void AddElement(int number, Type type);

        void DeleteElement(int number);

//        TableElement::iterator FindElement(int number);
        std::map<int, Room *>::const_iterator FindElement(int number) const;

        friend std::ostream &operator<<(std::ostream &out, const std::map<int, Room *> &a) {
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
