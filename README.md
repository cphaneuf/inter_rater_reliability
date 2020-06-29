# README

## PURPOSE
A command line utility (referred to throughout this README as CommandLineClassifier) designed to promote inter-rater reliability of psychological data.

## MOTIVATION
Psychological data often requires 'coding' by researchers, and it is good practice for:
1. The data to be 'anonymous' to those coding it, and
2. The data to be 'reviewed' by > 1 researcher.
The CommandLineClassifier supports both of these practices through an easy-to-use command line utility.

## USE CASES
Thus far, the CommandLineClassifier has been used for a project titled *The Need for TLC: Tender Loving Cellphone*. A recent poster of this work (PhaneufJuhaszKruger2019.pdf) can be found in the root directory of this repository. Here are some other possible use cases for the CommandLineClassifier:
1. __Observational Data__ 2+ researchers 'code' transcriptions of behavior/commentary in video recordings
2. __Survey Data__ 2+ researchers 'code' fill-in-the-blank survey responses 
3. __Imaging Data__ 2+ researchers quality assess imaging data
4. __Video Data__ 2+ researchers 'code' behavior/commentary in video recordings

In all of these cases, it is important for researchers to reach a consensus on their codings, ratings, etc. The CommandLineUtility streamlines this process.

__NOTE:__ Items 3 and 4 require additional development for image or video display, but these changes can be built upon the current framework. While knowledge of C++ is not necessary for using the CommandLineClassifier, it is necessary for adding features.

## INTRODUCTION
The CommandLineClassifier program supports:
1. Reading in a transcribed text file, formatted according to textfile_template.txt (more information about how the file should be formatted is described in ClassifierTextFileTemplates/TextFileFormattingDescription)
2. Storing the participant information contained in the text file
3. Allowing the user to 'tag' or 'code' the contents of the text file, line by line  

__NOTE:__ When the user is prompted to 'tag' or 'code' at the command line, only the data is presented; participants are completely de-identified from the user's perspective

4. Storing the user's responses, as they relate to the participant information
5. Outputting a file (data.csv) which contains the participant information matched to the user's responses, formatted according to datafile_template.csv

## COMMANDLINECLASSIFIER IMPLEMENTATION OVERVIEW
The program begins by prompting the user to enter the name of a (.txt) file. This file should be stored in the same directory as main.cpp. Afterward, the user will simply follow along with the prompts as provided on the screen.  

__Data Structures__  
*subject* struct stores the comments associated with a particular participant AND the user's 'tags' or 'codes' for those comments.  
*completeData* class contains 3 data members and 9 functions, divided according to the sets below. Control flow between these sets of functions is directed by main().
* Functions to Store Responses
* User Interface Functions
* Save Output Functions

__Core Functionality__  
*store_responses()* is a Function to Store Responses that saves the participant comments into individual subjects, which are stored collectively in a dictionary.  
*process_question()* is a Function to Store Responses that handles the reading of participant comments to a single question.  
*process_session()* is a Function to Store Responses that reads in the file header, and processes the appropriate number of questions (according to test condition).  
*print_prompt()* is a User Interface Function that prints a question-answer pair and prompts the user to make a decision.  
*process_choice()* is a User Interface Function that manages the selection of a question-answer pair and stores the user's choice.  
*make_response_list()* is a User Interface Function that compiles a list of all of the participant comments.  
*print()* (see Debugging, below)  
*write_to_file()* is a Save Output Function that iterates through the dictionary of subjects and prints out its contents into data.csv.  
*main()* declares an instance of completeData, manages the control flow of the program, and prints a concluding message.  

__Current Implementation__ \
CommandLineClassifier/CommandLineClassifier/main.cpp supports text files with:
1. 5 question types, with parts A and B for each question
2. up to 6 participants, each labeled MN (where M is an integer and N is a letter belonging to the set \[A,F])
3. 2 participant groups ('conditions': CONTROL and TEST), where one group has questions 1, 2, 3, 4, and 5, and the other group answers questions 1, 2, 3, and 5

An example question, asked in PhaneufJuhaszKruger2019.pdf is as follows. \
Question X body, part A: "When is it not appropriate to use a cell phone? Among certain people? In certain locations? In particular situations?" \
Question X body, part B" "Does this answer demonstrate awareness of cell phone etiquette?" 

Before running this program, be sure to modify the following to match the content/structure of your project:
* change the templated question bodies in CommandLineClassifier/CommandLineClassifier/main.cpp
* modify the number of questions, participants, and/or conditions

## USING THE PROGRAM, STEP 1: Randomize the Text Files with an Auxiliary Script
For example, it may be desirable for transcriptions of behavior/commentary in video recordings to be randomized, so behavior/commentary is not 'coded' chronologically. As in the case of PhaneufJuhaszKruger2019.pdf, the authors did not want research assistants to 'code' transcriptions sequentially because 'coding' the current behavior/commentary in question could be biased by the preceeding behavior/commentary; the authors aimed to adopt the most conservative approach possible when processing their observational data. Listed here are the instructions for combining and randomizing standard transcription text files to create a single text file that can be fed into the command line utility. This series of steps should be completed by a project manager (not a researcher that will later be 'coding' the text files). 
1. Navigate to the CommandLineClassifier/Randomize directory.
2. Compile the program to make an executable, named main.
<pre><code>$ sudo g++ -std=c++11 -o main main.cpp  
</code></pre>
3. Run the newly generated executable, responding appropriately to the prompts.
<pre><code>$ ./main
</code></pre>
4. Make a new text file named textM.txt, where M is a number, starting at 1 and increasing by 1 for each new file made.
5. Concatenate the files, according to the directions shown in the terminal window. Specifically: \
  a. Start the file with: N = number of sessions in this file \
  b. Copy and paste in the instructed session files, with an enter space between them \
  c. End the file with: EOF

## USING THE PROGRAM, STEP 2: Use the CommandLineClassifier to 'Code' the Randomized Text Files
Listed here are the instructions for 'coding' the randomized text files using the command line utility. This series of steps should be completed by 2+ researchers (not the project manager from Step 1). 
1. Move text files to be 'coded' into CommandLineClassifier/CommandLineClassifier.
2. Compile the program to make an executable, named main.
<pre><code>$ sudo g++ -o main main.cpp  
</code></pre>
3. Run the newly generated executable.
<pre><code>$ ./main
</code></pre>
4. After the program runs, data.csv will be created. If you would like to run the program again, rename data.csv so that it does not get overwritten by the forthcoming data.csv file.

## USING THE PROGRAM, STEP 3: Compare the 'Codings' or 'Ratings' from 2+ Independent Researchers
Once all (2+) researchers have finished using the CommandLineClassifier (i.e. all text files have been independently 'coded'), follow these instructions.
1. Compile all of researcher 1’s raw data files into a singular file named Coder1Output.csv (see example in CompareRatings directory).
2. Compile all of researcher 2’s raw data files into a singular file named Coder2Output.csv (see example in CompareRatings directory).
3. Open Coder1Output.csv and Coder2Output.csv in Microsoft Excel (or equivalent). If you find yourself viewing 'garbled characters' in Excel, the developer found this article to be helpful: https://support.collaborativedrug.com/hc/en-us/articles/115004625563-CSV-import-in-Excel-with-garbled-characters.
4. Sort Coder1Output.csv and Coder2Output.csv by SubjectID: \
  a. (In Excel) Data > Sort > A to Z \
  b. Save files 
5. Open CompareRatings/CompareRatings.R in RStudio.
6. Update the path to your working directory at 'YOUR PATH HERE' in CompareRatings.R.
7. Run CompareRatings.R in RStudio; take note of Quality Control console output.
8. CombinedOutput.csv is produced by CompareRatings.R; to make it more readable (especially if it is a large file), consider these modifications in Excel: \
  a. Highlight the content of the ‘Master’ columns (Home > Conditional Formatting > Highlight Cells Rules > Equal To… > -2) \
  b. Highlight the Coder1 output blue; highlight the Coder2 output green
9. Resolve items in CombinedOutput.csv that are highlighted in red: \
  a. Have 'coding' researchers meet to come to an agreement on 'coding' designation, or \
  b. Have project manager make final decision on 'coding' designation
10. Make the appropriate changes to reflect unanimous, final decisions; save final data file as CombinedOutput_resolved.csv. 

__*CombinedOutput_resolved.csv is the final product of this command line utility and its associated data processing scripts.*__

## DEBUGGING
Built-in debugging tools are included in the CommandLineClassifier program. To start, in CommandLineClassifier/CommandLineClassifier/main.cpp, uncomment...
<pre><code>DATA.print();
</code></pre>
...in main(). This will allow a call to print() in class completeData, which tests the success of:
1. Storing the participant information contained in the text file
2. Storing the user's responses, as they relate to the participant information  
See the terminal window for the output, which should be compared to the chosen input (.txt) file.

## TECHNICAL, GENERAL
You must remake the main executable after changes to its corresponding main.cpp are completed and saved. To remove the current executable, type:
<pre><code>$ rm main
</code></pre>
You may be prompted in regards to the removal of main. If so, simply type:
<pre><code>$ yes
</code></pre>

## CONTACT
If you have any questions about the use of this program, or its generalizable functionality, please contact its developer Camille Phaneuf (cphaneuf@umich.edu). To cite PhaneufJuhaszKruger2019.pdf, please use: 

Juhasz, D., Phaneuf, C.V., & Kruger, D. J. (2019, March). The need for TLC (tender loving cell phone): comparing cell phone attitudes, experiences, and behaviors in undergraduates. Poster, International Convention for Psychological Science, Paris, France. 

The authors (Camille Phaneuf, cphaneuf@umich.edu; Dora Juhasz, djuhasz@umich.edu; Dr. Daniel Kruger, kruger@umich.edu) are happy to discuss this work, and will update this README when a preprint of this project is available.
