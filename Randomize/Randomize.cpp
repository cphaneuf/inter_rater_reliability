//
//  main.cpp
//  Randomize
//
//  Created by Camille Phaneuf on 1/31/19.
//  Copyright © 2019 Camille Phaneuf. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <vector>
using namespace std;

int main() {
    int num = -1;
    cout << "How many text files need to be analyzed?\n";
    cin >> num;
    
    vector<int> files;
    for (int i = 1; i <= num; ++i) {
        files.push_back(i);
    }
    
    unsigned seed = 0;
    shuffle(files.begin(), files.end(), default_random_engine(seed));
    
    cout << "\n";
    cout << "****************************************************************\n";
    cout << "*** BELOW ARE THE FILES THAT SHOULD BE CONCATENATED TOGETHER ***\n";
    cout << "****************************************************************\n";
    
    int files_size = int(files.size());
    int all_encompassing_it = 0;
    int left_to_print = files_size;
    
    while (all_encompassing_it < files_size) {
        int max_it = 0;
        if (left_to_print >= 5) {
            max_it = 5;
        }
        else {
            max_it = left_to_print;
        }
        
        cout << "The next " << max_it << " files that should be concatenated together are:\n";
        for (int j = 0; j < max_it; ++j) {
            cout << files[all_encompassing_it] << "\n";
            ++all_encompassing_it;
            --left_to_print;
        }
    }
    
    cout << "\n";
    cout << "Thanks for using Randomize to prepare for CommandLineClassifier!\n";
    
    return 0;
} // main()
