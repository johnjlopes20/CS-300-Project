//============================================================================
// Name        : CS 300 Project Two.cpp
// Author      : John Lopes, April 21, 2024
// Version     : 1.0
// Copyright   : Copyright © 2024 SNHU COCE
// Description : Algorithms and Data structures to Solve Basic Programming Problems
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include "Models/Courses.h"

// Function to parse course data from the input text file
void parseCourseData(const std::string& filePath, std::vector<Course>& courses) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string courseId, courseName, prerequisite;
        std::vector<std::string> prerequisites;
        std::getline(ss, courseId, ',');
        std::getline(ss, courseName, ',');
        while (std::getline(ss, prerequisite, ',')) {
            if (!prerequisite.empty()) {
                prerequisites.push_back(prerequisite);
            }
        }
        Course course(courseId, courseName, prerequisites);
        courses.push_back(course);
    }
    file.close();
}

// Function to load courses into the binary search tree
void loadCourses(const std::vector<Course>& courses, Courses& coursesBst) {
    for (const auto& course : courses) {
        coursesBst.Insert(course);
    }
}

// Function to display the course list
void printCourseList(const Courses& coursesBst) {
    coursesBst.InOrder();
}

// Function to display course information based on course number
void printCourseInfo(const Courses& coursesBst, const std::string& courseNumber) {
    Course course = coursesBst.Search(courseNumber);
    if (!course.getCourseId().empty()) {
        displayCourse(course);
    } else {
        std::cout << "Course " << courseNumber << " not found." << std::endl;
    }
}

int main() {
    std::vector<Course> courses;
    parseCourseData("course_data.txt", courses); // Assuming course data file is "course_data.txt"
    Courses coursesBst;
    loadCourses(courses, coursesBst);

    std::cout << "Welcome to the course planner." << std::endl << std::endl;

    int choice = 0;
    while (choice != 9) {
        std::cout << "  1. Load Data Structure" << std::endl;
        std::cout << "  2. Print Course List" << std::endl;
        std::cout << "  3. Print Course" << std::endl;
        std::cout << "  9. Exit" << std::endl << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Load Data Structure
                std::cout << "Data structure loaded successfully." << std::endl;
                break;
            case 2:
                // Print Course List
                std::cout << "Here is a sample schedule:" << std::endl << std::endl;
                printCourseList(coursesBst);
                break;
            case 3:
                // Print Course
                std::cout << "What course do you want to know about? ";
                std::string courseNumber;
                std::cin >> courseNumber;
                printCourseInfo(coursesBst, courseNumber);
                break;
            case 9:
                std::cout << "Good bye." << std::endl;
                break;
            default:
                std::cout << choice << " is not a valid option." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
        std::cout << std::endl;
    }

    return 0;
}

