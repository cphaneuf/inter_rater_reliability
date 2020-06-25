//
//  main.cpp
//  model
//
//  Created by Camille Phaneuf on 1/8/19.
//  Copyright © 2019 Camille Phaneuf. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct subject {
    string q1;
    int q1_code;
    string q2;
    int q2_code;
    string q3;
    int q3_code;
    string q4;
    int q4_code;
    string q5;
    int q5_code;
    subject() : q1(""), q1_code(-1),
    q2(""), q2_code(-1),
    q3(""), q3_code(-1),
    q4(""), q4_code(-1),
    q5(""), q5_code(-1) {}
};

class completeData {
public:
    
    ////////////////////////////////////
    /////////// DATA MEMBERS ///////////
    ////////////////////////////////////
    
    unordered_map<string, subject> subjects;
    vector<char> sessions;
    vector<string> responses;
    
    ////////////////////////////////////
    ///////// MEMBER FUNCTIONS /////////
    ////////////////////////////////////
    
    /// Functions to Store Responses ///
    
    int store_responses(ifstream &responses, char &letter, int num_s, int num_q) {
        // Experimenter was prompting (do not store)
        if (letter != 'A' && letter != 'B' && letter != 'C' &&
            letter != 'D' && letter != 'E' && letter != 'F') {
            string reprompt = "";
            getline(responses, reprompt);
            return 0;
        } // if
        
        string response = "";
        getline(responses, response);
        string fullID = to_string(num_s) + letter;
        
        // If subject key does not exist in the hash table, declare and add a new subject...
        if (subjects.find(fullID) == subjects.end()) {
            subject temp;
            if (num_q == 1) {
                temp.q1 = response;
            }
            else if (num_q == 2) {
                temp.q2 = response;
            }
            else if (num_q == 3) {
                temp.q3 = response;
            }
            else if (num_q == 4) {
                temp.q4 = response;
            }
            else if (num_q == 5) {
                temp.q5 = response;
            }
            subjects[fullID] = temp;
        } // if
        // ...but if the subject already exists in the hash table, append
        else {
            if (num_q == 1) {
                subjects[fullID].q1.append(response);
            }
            else if (num_q == 2) {
                subjects[fullID].q2.append(response);
            }
            else if (num_q == 3) {
                subjects[fullID].q3.append(response);
            }
            else if (num_q == 4) {
                subjects[fullID].q4.append(response);
            }
            else if (num_q == 5) {
                subjects[fullID].q5.append(response);
            }
        } // else
        
        return 0;
    } // store_responses()
    
    int process_question(ifstream &text, int session_number, int question_number) {
        string first = "";
        text >> first;
        
        while (first != "QUESTION:" && first != "VIDEO:" && first != "EOF") {
            char last_char = first[first.length() - 2];
            store_responses(text, last_char, session_number, question_number);
            text >> first;
        } // while
        
        return 0;
    } // process_question()
    
    int process_session() {
        cout << "Please type the name of the file you wish to process, then press 'return' or 'enter' after responding:" << endl;
        string filename = "";
        cin >> filename;
        
        ifstream file;
        file.open(filename);
        
        if (file.is_open()) {
            int num_sessions = 0;
            file >> num_sessions;
            string rem_txt = "";
            getline(file, rem_txt);
            
            for (int i = 0; i < num_sessions; ++i) {
                // Get the video label
                string vid = "";
                file.ignore();
                getline(file, vid);
                
                // Get the session number
                string sess = "";
                file >> sess;
                int sess_num = 0;
                file >> sess_num;
                
                // Get the experimental condition
                string tp = "";
                file >> tp;
                string cond = "";
                file >> cond;
                
                // Store the experimental condition
                if (cond[0] == 'C') {
                    sessions.push_back('C');
                }
                else {
                    sessions.push_back('T');
                }
                
                // Get the coder information
                string cods = "";
                file.ignore();
                getline(file, cods);
                
                // Base decisions off of experimental condition
                if (cond[0] == 'C') {
                    string q = "";
                    file >> q;
                    for (int j = 0; j < 5; ++j) {
                        // Get the question number
                        int q_num = 0;
                        file >> q_num;
                        // Get the question
                        string full_q = "";
                        file.ignore();
                        getline(file, full_q);
                        // Get subject responses
                        process_question(file, sess_num, q_num);
                    } // for
                } // if CONTROL
                else {
                    string q = "";
                    file >> q;
                    for (int k = 0; k < 4; ++k) {
                        // Get the question number
                        int q_num = 0;
                        file >> q_num;
                        // Get the question
                        string full_q = "";
                        file.ignore();
                        getline(file, full_q);
                        // Get subject responses
                        process_question(file, sess_num, q_num);
                    } // for
                } // else TEST
            } // for
            file.close();
        } // if
        
        else {
            cout << "ABORT: Unable to open file.";
        } // else
        
        return 0;
    } // process_session()
    
    ///// User Interface Functions /////

    int print_prompt(string sub_number, char question_number) {
        if (question_number == '1') {
            cout << "Q: " << "Question 1 body, part A." << endl;
            cout << "A: " << subjects[sub_number].q1 << endl;
            cout << "---" << endl;
            cout << "Question 1 body, part B." << endl;
            cout << "(0 = NO, 1 = YES, 2 = UNCLEAR)" << endl;
            cout << "Please press 'return' or 'enter' after responding." << endl;
        } // if
        
        else if (question_number == '2') {
            cout << "Q: " << "Question 2 body, part A." << endl;
            cout << "A: " << subjects[sub_number].q2 << endl;
            cout << "---" << endl;
            cout << "Question 2 body, part B." << endl;
            cout << "(0 = NO, 1 = YES, 2 = UNCLEAR)" << endl;
            cout << "Please press 'return' or 'enter' after responding." << endl;
        } // else if
        
        else if (question_number == '3') {
            cout << "Q: " << "Question 3 body, part A." << endl;
            cout << "A: " << subjects[sub_number].q3 << endl;
            cout << "---" << endl;
            cout << "Question 3 body, part B." << endl;
            cout << "(0 = NO, 1 = YES, 2 = UNCLEAR)" << endl;
            cout << "Please press 'return' or 'enter' after responding." << endl;
        } // else if
        
        else if (question_number == '4') {
            cout << "Q: " << "Question 4 body, part A." << endl;
            cout << "A: " << subjects[sub_number].q4 << endl;
            cout << "---" << endl;
            cout << "Question 4 body, part B." << endl;
            cout << "(0 = NO, 1 = YES, 2 = UNCLEAR)" << endl;
            cout << "Please press 'return' or 'enter' after responding." << endl;
        } // else if
        
        else if (question_number == '5') {
            cout << "Q: " << "Question 5 body, part A." << endl;
            cout << "A: " << subjects[sub_number].q5 << endl;
            cout << "---" << endl;
            cout << "Question 5 body, part B." << endl;
            cout << "(0 = NO, 1 = YES, 2 = UNCLEAR)" << endl;
            cout << "Please press 'return' or 'enter' after responding." << endl;
        } // else if
        
        return 0;
    } // print_prompt()
    
    int process_choice() {
        int max_it = int(responses.size());
        for (int i = 0; i < max_it; ++i) {
            int max = int(responses.size()) - 1;
            int rand_num = 0;
            if (max != 0) {
                rand_num = rand() % max;
            } 
            string rand_str = responses[rand_num];
            string sub_lookup = rand_str.substr(0, 2);
            char q_lookup = rand_str[2];
            
            // Use sub_lookup and q_lookup to find the answer and print out the prompt
            cout << endl << endl;
            print_prompt(sub_lookup, q_lookup);
            
            // Get the user's choice and store their response
            while (true) {
                string choice = "";
                cin >> choice;
                if (choice == "0") {
                    if (q_lookup == '1') {
                        subjects[sub_lookup].q1_code = 0;
                    }
                    else if (q_lookup == '2') {
                        subjects[sub_lookup].q2_code = 0;
                    }
                    else if (q_lookup == '3') {
                        subjects[sub_lookup].q3_code = 0;
                    }
                    else if (q_lookup == '4') {
                        subjects[sub_lookup].q4_code = 0;
                    }
                    else if (q_lookup == '5') {
                        subjects[sub_lookup].q5_code = 0;
                    }
                    break;
                } // if
                else if (choice == "1") {
                    if (q_lookup == '1') {
                        subjects[sub_lookup].q1_code = 1;
                    }
                    else if (q_lookup == '2') {
                        subjects[sub_lookup].q2_code = 1;
                    }
                    else if (q_lookup == '3') {
                        subjects[sub_lookup].q3_code = 1;
                    }
                    else if (q_lookup == '4') {
                        subjects[sub_lookup].q4_code = 1;
                    }
                    else if (q_lookup == '5') {
                        subjects[sub_lookup].q5_code = 1;
                    }
                    break;
                } // else if
                else if (choice == "2") {
                    if (q_lookup == '1') {
                        subjects[sub_lookup].q1_code = 2;
                    }
                    else if (q_lookup == '2') {
                        subjects[sub_lookup].q2_code = 2;
                    }
                    else if (q_lookup == '3') {
                        subjects[sub_lookup].q3_code = 2;
                    }
                    else if (q_lookup == '4') {
                        subjects[sub_lookup].q4_code = 2;
                    }
                    else if (q_lookup == '5') {
                        subjects[sub_lookup].q5_code = 2;
                    }
                    break;
                } // else if
                else {
                    cout << "************************************************************************************" << endl;
                    cout << "*** Please choose a valid response (0, 1, or 2). The question is repeated below: ***" << endl;
                    cout << "************************************************************************************" << endl;
                    print_prompt(sub_lookup, q_lookup);
                } // else
            } // while

            // Remove item from list since the response has been coded
            responses.erase(responses.begin() + rand_num);
        } // for
        
        return 0;
    } // process_choice()
    
    int make_response_list() {
        // Iterate through subjects to generate a list of all responses; for each question a subject answered, add it to the total list of responses
        for (pair<string, subject> sub : subjects) {
            if (!sub.second.q1.empty()) {
                string code = sub.first + "1";
                responses.push_back(code);
            } // if Q1
            
            if (!sub.second.q2.empty()) {
                string code = sub.first + "2";
                responses.push_back(code);
            } // if Q2
            
            if (!sub.second.q3.empty()) {
                string code = sub.first + "3";
                responses.push_back(code);
            } // if Q3
            
            if (!sub.second.q4.empty()) {
                string code = sub.first + "4";
                responses.push_back(code);
            } // if Q4
            
            if (!sub.second.q5.empty()) {
                string code = sub.first + "5";
                responses.push_back(code);
            } // if Q5
        } // for
        
        // Once all responses are compiled, randomly select an item from the list and remove it
        process_choice();
        
        return 0;
    } // make_response_list()
    
    int print() {
        cout << "TESTING THE TERMAINAL APPLICATION:" << endl;
        
        // SESSION 1 - responses
        cout << subjects["1A"].q1 << endl;
        cout << subjects["1B"].q1 << endl;
        cout << subjects["1C"].q1 << endl;
        cout << subjects["1D"].q1 << endl;
        cout << subjects["1E"].q1 << endl;
        cout << subjects["1F"].q1 << endl;
        cout << subjects["1A"].q2 << endl;
        cout << subjects["1B"].q2 << endl;
        cout << subjects["1C"].q2 << endl;
        cout << subjects["1D"].q2 << endl;
        cout << subjects["1E"].q2 << endl;
        cout << subjects["1F"].q2 << endl;
        cout << subjects["1A"].q3 << endl;
        cout << subjects["1B"].q3 << endl;
        cout << subjects["1C"].q3 << endl;
        cout << subjects["1D"].q3 << endl;
        cout << subjects["1E"].q3 << endl;
        cout << subjects["1F"].q3 << endl;
        cout << subjects["1A"].q4 << endl;
        cout << subjects["1B"].q4 << endl;
        cout << subjects["1C"].q4 << endl;
        cout << subjects["1D"].q4 << endl;
        cout << subjects["1E"].q4 << endl;
        cout << subjects["1F"].q4 << endl;
        cout << subjects["1A"].q5 << endl;
        cout << subjects["1B"].q5 << endl;
        cout << subjects["1C"].q5 << endl;
        cout << subjects["1D"].q5 << endl;
        cout << subjects["1E"].q5 << endl;
        cout << subjects["1F"].q5 << endl;
        
        // SESSION 1 - coding
        cout << subjects["1A"].q1_code << endl;
        cout << subjects["1B"].q1_code << endl;
        cout << subjects["1C"].q1_code << endl;
        cout << subjects["1D"].q1_code << endl;
        cout << subjects["1E"].q1_code << endl;
        cout << subjects["1F"].q1_code << endl;
        cout << subjects["1A"].q2_code << endl;
        cout << subjects["1B"].q2_code << endl;
        cout << subjects["1C"].q2_code << endl;
        cout << subjects["1D"].q2_code << endl;
        cout << subjects["1E"].q2_code << endl;
        cout << subjects["1F"].q2_code << endl;
        cout << subjects["1A"].q3_code << endl;
        cout << subjects["1B"].q3_code << endl;
        cout << subjects["1C"].q3_code << endl;
        cout << subjects["1D"].q3_code << endl;
        cout << subjects["1E"].q3_code << endl;
        cout << subjects["1F"].q3_code << endl;
        cout << subjects["1A"].q4_code << endl;
        cout << subjects["1B"].q4_code << endl;
        cout << subjects["1C"].q4_code << endl;
        cout << subjects["1D"].q4_code << endl;
        cout << subjects["1E"].q4_code << endl;
        cout << subjects["1F"].q4_code << endl;
        cout << subjects["1A"].q5_code << endl;
        cout << subjects["1B"].q5_code << endl;
        cout << subjects["1C"].q5_code << endl;
        cout << subjects["1D"].q5_code << endl;
        cout << subjects["1E"].q5_code << endl;
        cout << subjects["1F"].q5_code << endl;
        
        // SESSION 2 - responses
        cout << subjects["2A"].q1 << endl;
        cout << subjects["2B"].q1 << endl;
        cout << subjects["2C"].q1 << endl;
        cout << subjects["2D"].q1 << endl;
        cout << subjects["2E"].q1 << endl;
        cout << subjects["2F"].q1 << endl;
        cout << subjects["2A"].q2 << endl;
        cout << subjects["2B"].q2 << endl;
        cout << subjects["2C"].q2 << endl;
        cout << subjects["2D"].q2 << endl;
        cout << subjects["2E"].q2 << endl;
        cout << subjects["2F"].q2 << endl;
        cout << subjects["2A"].q3 << endl;
        cout << subjects["2B"].q3 << endl;
        cout << subjects["2C"].q3 << endl;
        cout << subjects["2D"].q3 << endl;
        cout << subjects["2E"].q3 << endl;
        cout << subjects["2F"].q3 << endl;
        cout << subjects["2A"].q4 << endl;
        cout << subjects["2B"].q4 << endl;
        cout << subjects["2C"].q4 << endl;
        cout << subjects["2D"].q4 << endl;
        cout << subjects["2E"].q4 << endl;
        cout << subjects["2F"].q4 << endl;
        cout << subjects["2A"].q5 << endl;
        cout << subjects["2B"].q5 << endl;
        cout << subjects["2C"].q5 << endl;
        cout << subjects["2D"].q5 << endl;
        cout << subjects["2E"].q5 << endl;
        cout << subjects["2F"].q5 << endl;
        
        // SESSION 2 - coding
        cout << subjects["2A"].q1_code << endl;
        cout << subjects["2B"].q1_code << endl;
        cout << subjects["2C"].q1_code << endl;
        cout << subjects["2D"].q1_code << endl;
        cout << subjects["2E"].q1_code << endl;
        cout << subjects["2F"].q1_code << endl;
        cout << subjects["2A"].q2_code << endl;
        cout << subjects["2B"].q2_code << endl;
        cout << subjects["2C"].q2_code << endl;
        cout << subjects["2D"].q2_code << endl;
        cout << subjects["2E"].q2_code << endl;
        cout << subjects["2F"].q2_code << endl;
        cout << subjects["2A"].q3_code << endl;
        cout << subjects["2B"].q3_code << endl;
        cout << subjects["2C"].q3_code << endl;
        cout << subjects["2D"].q3_code << endl;
        cout << subjects["2E"].q3_code << endl;
        cout << subjects["2F"].q3_code << endl;
        cout << subjects["2A"].q4_code << endl;
        cout << subjects["2B"].q4_code << endl;
        cout << subjects["2C"].q4_code << endl;
        cout << subjects["2D"].q4_code << endl;
        cout << subjects["2E"].q4_code << endl;
        cout << subjects["2F"].q4_code << endl;
        cout << subjects["2A"].q5_code << endl;
        cout << subjects["2B"].q5_code << endl;
        cout << subjects["2C"].q5_code << endl;
        cout << subjects["2D"].q5_code << endl;
        cout << subjects["2E"].q5_code << endl;
        cout << subjects["2F"].q5_code << endl;
        
        return 0;
    } // print()
    
    ////// Save Output Functions //////
    
    int write_to_file() {
        ofstream data;
        data.open("data.csv");
        
        // Print header
        data << "SubjectID,Q1Response,Q2Response,Q3Response,Q4Response,Q5Response,CoderQ1,CoderQ2,CoderQ3,CoderQ4,CoderQ5,\n";
        
        // Remove commas
        unordered_map<string, subject>::iterator clean = subjects.begin();
        while (clean != subjects.end()) {
            (clean->second.q1).erase(remove(clean->second.q1.begin(), clean->second.q1.end(), ','), clean->second.q1.end());
            (clean->second.q2).erase(remove(clean->second.q2.begin(), clean->second.q2.end(), ','), clean->second.q2.end());
            (clean->second.q3).erase(remove(clean->second.q3.begin(), clean->second.q3.end(), ','), clean->second.q3.end());
            (clean->second.q4).erase(remove(clean->second.q4.begin(), clean->second.q4.end(), ','), clean->second.q4.end());
            (clean->second.q5).erase(remove(clean->second.q5.begin(), clean->second.q5.end(), ','), clean->second.q5.end());
            ++clean;
        } // while
        
        // Print contents
        unordered_map<string, subject>::iterator it = subjects.begin();
        while (it != subjects.end()) {
            data << it->first << "," << it->second.q1 << ","
                              << it->second.q2 << ","
                              << it->second.q3 << ","
                              << it->second.q4 << ","
                              << it->second.q5 << ","
                              << it->second.q1_code << ","
                              << it->second.q2_code << ","
                              << it->second.q3_code << ","
                              << it->second.q4_code << ","
                              << it->second.q5_code << ","
                              << "\n";
            ++it;
        } // while
        
        data.close();
        return 0;
    } // write_to_file()
};

int main(int argc, const char * argv[]) {
    completeData DATA;
    
    // Direct control flow to 'Functions to Store Responses'
    DATA.process_session();
    
    // Direct control flow to 'User Interface Functions'
    DATA.make_response_list();
    
    // Test storage
    // DATA.print();
    
    // Direct control flow to 'Save Output Functions'
    DATA.write_to_file();
    
    // Print closing statement
    cout << endl << endl;
    cout << "Thank you for using the CommandLineClassifier program. The file data.csv has been generated in your directory." << endl;
    
    return 0;
} // main()
