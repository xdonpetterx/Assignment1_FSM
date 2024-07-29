#pragma once

#include <chrono>
#include <iostream>
#include <array>
#include <thread>

struct GameTime {
    std::chrono::year gt_year;
    std::chrono::month gt_month;
    std::chrono::weekday gt_wd;
    std::chrono::day gt_day;
    std::chrono::hours gt_hour; //No std::chrono::hour
    std::chrono::minutes gt_minute; //std::chrono::minutes
    std::chrono::seconds gt_seconds;

    std::array<std::string, 12> Months{"January", "February", "March", "April", "May", "June",
                                       "July", "August", "September", "October", "November", "December"};

    std::array<std::string, 7> WeekDays{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
                                        "Sunday"};
};

unsigned int setDaysInMonth(struct GameTime gt, unsigned int days_in_month){
    switch (gt.gt_month.operator unsigned int()) {
        case 1:
            if ((gt.gt_year.operator int() % std::chrono::year(4).operator int() == 0
                 and gt.gt_year.operator int() % std::chrono::year(100).operator int() != 0)
                or (gt.gt_year.operator int() % std::chrono::year(400).operator int() == 0))
                days_in_month = 29;
            else
                days_in_month = 28;
            break;
        case 3:
            days_in_month = 30;
            break;
        case 5:
            days_in_month = 30;
            break;
        case 8:
            days_in_month = 30;
            break;
        case 10:
            days_in_month = 30;
            break;
        default:
            days_in_month = 31;
    }
    return days_in_month;
}

int scratch(){
    auto today = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(today);
    std::tm *t = std::localtime(&tt);

    GameTime gt;

    gt.gt_year = std::chrono::year(t->tm_year + 1900);
    gt.gt_month = std::chrono::month(t->tm_mon);
    gt.gt_wd = std::chrono::weekday(t->tm_wday - 1);
    gt.gt_day = std::chrono::day(t->tm_mday);
    gt.gt_hour = std::chrono::hours(t->tm_hour);
    gt.gt_minute = std::chrono::minutes(t->tm_min);

    std::cout << "Local time is: ";
    std::cout << gt.WeekDays[gt.gt_wd.c_encoding()] << ", " << gt.Months[gt.gt_month.operator unsigned int()]
              << ", " << gt.gt_day << ", " << gt.gt_year
              << ". Time: " << gt.gt_hour.count() << ":" << gt.gt_minute.count() << std::endl;

    gt.gt_hour = std::chrono::hours(0);
    gt.gt_minute = std::chrono::minutes(0);

    std::cout << "Game starting at: ";
    std::cout << gt.WeekDays[gt.gt_wd.c_encoding()] << ", " << gt.Months[gt.gt_month.operator unsigned int()]
              << ", " << gt.gt_day << ", " << gt.gt_year
              << ". Time: " << gt.gt_hour.count() << ":" << gt.gt_minute.count() << std::endl;

    auto start = std::chrono::system_clock::now();
    int multiplier = 60000;

    unsigned int days_in_month = 0;

    while (true) {
        auto current = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = current - start;

        gt.gt_minute = duration_cast<std::chrono::minutes>(elapsed_seconds * multiplier);
        if (gt.gt_minute >= std::chrono::minutes(60)){
            gt.gt_minute = std::chrono::minutes(0);
            gt.gt_hour++;
        }
        if (gt.gt_hour >= std::chrono::hours(24)){
            gt.gt_hour = std::chrono::hours(0);
            gt.gt_day++;
            gt.gt_wd++;
        }
        if (gt.gt_wd.c_encoding() > std::chrono::weekday(6).c_encoding()){
            gt.gt_wd = std::chrono::weekday(0);
        }
        days_in_month = setDaysInMonth(gt, days_in_month);
        if (gt.gt_day > std::chrono::day(days_in_month)){
            gt.gt_day = std::chrono::day(1);
            gt.gt_month++;
        }
        if (gt.gt_month.operator unsigned int() > 11){
            gt.gt_month = std::chrono::month(0);
            gt.gt_year++;
        }

        std::cout << "Game time: ";
        std::cout << gt.WeekDays[gt.gt_wd.c_encoding()] << ", " << gt.Months[gt.gt_month.operator unsigned int()]
                  << ", " << gt.gt_day << ", " << gt.gt_year
                  << ". Time: " << gt.gt_hour.count() << ":" << gt.gt_minute.count() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds (10));
    }
}