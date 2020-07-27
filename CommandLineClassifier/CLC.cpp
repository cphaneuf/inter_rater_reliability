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
#include <ctime>
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
        }

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
        }
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
        }

        return 0;
    } // store_responses()

    int process_question(ifstream &text, int session_number, int question_number) {
        string first = "";
        text >> first;

        while (first != "QUESTION:" && first != "VIDEO:" && first != "EOF") {
            char last_char = first[first.length() - 2];
            store_responses(text, last_char, session_number, question_number);
            text >> first;
        }

        return 0;
    } // process_question()

    int process_session() {
        cout << "Please type the name of the file you wish to process, then press 'return' or 'enter' after responding:\n";
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

                // Store the experimental condition (control, test)
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

                // Base decisions off of experimental condition (if control, else test)
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
                    }
                }
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
                    }
                }
            }
            file.close();
        }

        else {
            cout << "ABORT: Unable to open file.";
        }

        return 0;
    } // process_session()

    ///// User Interface Functions /////

    int print_prompt(string sub_number, char question_number) {
        if (question_number == '1') {
            cout << "Q: " << "Question 1 body, part A.\n";
            cout << "A: " << subjects[sub_number].q1 << "\n";
            cout << "---\n";
            cout << "Question 1 body, part B.\n";
        }

        else if (question_number == '2') {
            cout << "Q: " << "Question 2 body, part A.\n";
            cout << "A: " << subjects[sub_number].q2 << "\n";
            cout << "---\n";
            cout << "Question 2 body, part B.\n";
        }

        else if (question_number == '3') {
            cout << "Q: " << "Question 3 body, part A.\n";
            cout << "A: " << subjects[sub_number].q3 << "\n";
            cout << "---\n";
            cout << "Question 3 body, part B.\n";
        }

        else if (question_number == '4') {
            cout << "Q: " << "Question 4 body, part A.\n";
            cout << "A: " << subjects[sub_number].q4 << "\n";
            cout << "---\n";
            cout << "Question 4 body, part B.\n";
        }

        else if (question_number == '5') {
            cout << "Q: " << "Question 5 body, part A.\n";
            cout << "A: " << subjects[sub_number].q5 << "\n";
            cout << "---\n";
            cout << "Question 5 body, part B.\n";
        }

        cout << "(0 = NO, 1 = YES, 2 = UNCLEAR)\n";
        cout << "Please press 'return' or 'enter' after responding.\n";

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
            cout << "\n\n";
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
                }
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
                }
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
                }
                else {
                    cout << "************************************************************************************\n";
                    cout << "*** Please choose a valid response (0, 1, or 2). The question is repeated below: ***\n";
                    cout << "************************************************************************************\n";
                    print_prompt(sub_lookup, q_lookup);
                }
            }

            // Remove item from list since the response has been coded
            responses.erase(responses.begin() + rand_num);
        }

        return 0;
    } // process_choice()

    int make_response_list() {
        // Iterate through subjects to generate a list of all responses; for each question a subject answered, add it to the total list of responses
        for (pair<string, subject> sub : subjects) {
            // Q1
	          if (!sub.second.q1.empty()) {
                string code = sub.first + "1";
                responses.push_back(code);
            }

	          // Q2
            if (!sub.second.q2.empty()) {
                string code = sub.first + "2";
                responses.push_back(code);
            }

	          // Q3
            if (!sub.second.q3.empty()) {
                string code = sub.first + "3";
                responses.push_back(code);
            }

	          // Q4
            if (!sub.second.q4.empty()) {
                string code = sub.first + "4";
                responses.push_back(code);
            }

	          // Q5
            if (!sub.second.q5.empty()) {
                string code = sub.first + "5";
                responses.push_back(code);
            }
        }

        // Once all responses are compiled, randomly select an item from the list and remove it
        process_choice();

        return 0;
    } // make_response_list()

    int print() {
        cout << "TESTING THE COMMANDLINECLASSIFIER:\n";

        vector<string> subs_sess1{"1A", "1B", "1C", "1D", "1E", "1F"};
        vector<string> subs_sess2{"2A", "2B", "2C", "2D", "2E", "2F"};
        int num_subs = 6;

        // SESSION 1 - responses
        for (int q1_it = 0; q1_it < num_subs; ++q1_it) {
          cout << subjects[subs_sess1[q1_it]].q1 << "\n";
        }
        for (int q2_it = 0; q2_it < num_subs; ++q2_it) {
          cout << subjects[subs_sess1[q2_it]].q2 << "\n";
        }
        for (int q3_it = 0; q3_it < num_subs; ++q3_it) {
          cout << subjects[subs_sess1[q3_it]].q3 << "\n";
        }
        for (int q4_it = 0; q4_it < num_subs; ++q4_it) {
          cout << subjects[subs_sess1[q4_it]].q4 << "\n";
        }
        for (int q5_it = 0; q5_it < num_subs; ++q5_it) {
          cout << subjects[subs_sess1[q5_it]].q5 << "\n";
        }

        // SESSION 1 - coding
        for (int q1_it = 0; q1_it < num_subs; ++q1_it) {
          cout << subjects[subs_sess1[q1_it]].q1_code << "\n";
        }
        for (int q2_it = 0; q2_it < num_subs; ++q2_it) {
          cout << subjects[subs_sess1[q2_it]].q2_code << "\n";
        }
        for (int q3_it = 0; q3_it < num_subs; ++q3_it) {
          cout << subjects[subs_sess1[q3_it]].q3_code << "\n";
        }
        for (int q4_it = 0; q4_it < num_subs; ++q4_it) {
          cout << subjects[subs_sess1[q4_it]].q4_code << "\n";
        }
        for (int q5_it = 0; q5_it < num_subs; ++q5_it) {
          cout << subjects[subs_sess1[q5_it]].q5_code << "\n";
        }

        // SESSION 2 - responses
        for (int q1_it = 0; q1_it < num_subs; ++q1_it) {
          cout << subjects[subs_sess2[q1_it]].q1 << "\n";
        }
        for (int q2_it = 0; q2_it < num_subs; ++q2_it) {
          cout << subjects[subs_sess2[q2_it]].q2 << "\n";
        }
        for (int q3_it = 0; q3_it < num_subs; ++q3_it) {
          cout << subjects[subs_sess2[q3_it]].q3 << "\n";
        }
        for (int q4_it = 0; q4_it < num_subs; ++q4_it) {
          cout << subjects[subs_sess2[q4_it]].q4 << "\n";
        }
        for (int q5_it = 0; q5_it < num_subs; ++q5_it) {
          cout << subjects[subs_sess2[q5_it]].q5 << "\n";
        }

        // SESSION 2 - coding
        for (int q1_it = 0; q1_it < num_subs; ++q1_it) {
          cout << subjects[subs_sess2[q1_it]].q1_code << "\n";
        }
        for (int q2_it = 0; q2_it < num_subs; ++q2_it) {
          cout << subjects[subs_sess2[q2_it]].q2_code << "\n";
        }
        for (int q3_it = 0; q3_it < num_subs; ++q3_it) {
          cout << subjects[subs_sess2[q3_it]].q3_code << "\n";
        }
        for (int q4_it = 0; q4_it < num_subs; ++q4_it) {
          cout << subjects[subs_sess2[q4_it]].q4_code << "\n";
        }
        for (int q5_it = 0; q5_it < num_subs; ++q5_it) {
          cout << subjects[subs_sess2[q5_it]].q5_code << "\n";
        }

        return 0;
    } // print()

    ////// Save Output Functions //////

    int write_to_file() {
        // Get current date/time and add to file name, so that every data file name is unique and never gets overwritten
        time_t date_time;
        time(&date_time);
        string data_filename_pt1 = "data_";
        string data_filename_pt2 = data_filename_pt1.append(ctime(&date_time));
        string data_filename_pt3 = data_filename_pt2.append(".csv");
        ofstream data;
        data.open(data_filename_pt3);

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
        }

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
        }

        data.close();
        return 0;
    } // write_to_file()
};

int main(int argc, const char * argv[]) {
    completeData DATA;

    // Get running mode from user
    bool run_program = true;
    cout << "Do you want to run in debug mode? Type y or n, then press 'return' or 'enter' after responding.\n";
    char debug_mode = '';
    cin >> debug_mode;
    if (debug_mode == 'y') {
      cout << "Debug mode, activated!\n";
    }
    else if (debug_mode == 'n') {
      cout << "Proceeding without debugging.\n";
    }
    else {
      cout << "ABORT: Unable to detect mode. Try running the CommandLineClassifier again.";
      run_program = false;
    }

    if (run_program) {
      // Direct control flow to 'Functions to Store Responses'
      DATA.process_session();

      // Direct control flow to 'User Interface Functions'
      DATA.make_response_list();

      // Test storage
      if (debug_mode == 'y') {
        DATA.print();
      }

      // Direct control flow to 'Save Output Functions'
      DATA.write_to_file();

      // Print closing statement
      cout << "\n\nThank you for using the CommandLineClassifier program. The file data.csv has been generated in your directory.\n";
    }

    return 0;
} // main()
