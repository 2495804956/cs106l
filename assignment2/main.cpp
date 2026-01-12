/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "STUDENT TODO"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::ifstream ifs(filename);
  std::set<std::string> applicants;

  if(!ifs.is_open()){
    return applicants;
  }

  std::string line;
  std::string whitespace = "\r\t\n";
  while(std::getline(ifs,line)){
    auto start = line.find_first_not_of(whitespace);
    if(start == std::string::npos){
      continue;  // empty or whitespace
    }
    auto end = line.find_last_not_of(whitespace);
    std::string name = line.substr(start,end-start+1);
    if(!name.empty()){
      applicants.insert(name);
    }  
  }
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> matches;

  auto get_initials = [](const std::string& name){
    std::istringstream iss(name);
    std::string initials;
    std:: string word;
    while(iss >> word){
      if(!word.empty()){
        initials += word[0]; 
      }
    }
    return initials;
  };

  std::string target = get_initials(name);
  for(const auto& student : students){
    if(get_initials(student) == target){
      matches.push(&student);
    }
  }

  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  if (matches.empty()) return "NO MATCHES FOUND.";

  // Choose the shortest name (fewest characters). Tie-breaker: lexicographical order.
  const std::string* best = nullptr;
  std::vector<const std::string*> items;
  while (!matches.empty()) {
    items.push_back(matches.front());
    matches.pop();
  }

  for (const std::string* p : items) {
    if (p == nullptr) continue;
    if (best == nullptr) {
      best = p;
      continue;
    }
    if (p->size() < best->size()) best = p;
    else if (p->size() == best->size() && *p < *best) best = p;
  }

  if (best) return *best;
  return "NO MATCHES FOUND.";
  
}


/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
