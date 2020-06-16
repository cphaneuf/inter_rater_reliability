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
1. Reading in a transcribed text file, formatted according to textfile_template.txt
2. Storing the participant information contained in the text file
3. Allowing the user to 'tag' or 'code' the contents of the text file, line by line  
__NOTE:__ When the user is prompted to 'tag' or 'code' at the command line, only the data is presented; participants are completely de-identified from the user's perspective
4. Storing the user's responses, as they relate to the participant information
5. Outputting a file (data.csv) which contains the participant information matched to the user's responses, formatted according to datafile_template.csv

## IMPLEMENTATION OVERVIEW
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

## DEBUGGING
Built-in debugging tools are included in this program. To start, in main.cpp, uncomment...
<pre><code>DATA.print();
</code></pre>
...in main(). This will allow a call to print() in class completeData, which tests the success of:
1. Storing the participant information contained in the text tile
2. Storing the user's responses, as they relate to the participant information  
See the terminal window for the output, which should be compared to the chosen input (.txt) file.

## RUNNING THE PROGRAM
Compile the program to make an executable, named main.
<pre><code>$ sudo g++ -o main main.cpp  
</code></pre>
Run the newly generated executable.
<pre><code>$ ./main
</code></pre>
After the program runs, data.csv will be created. If you would like to run the program again, simply type:
<pre><code>$ rm data.csv
$ rm main
</code></pre>
You may be prompted in regards to the removal of main. If so, simply type:
<pre><code>$ yes
</code></pre>

## CONTACT
If you have any questions about the use of this program, or its generalizable functionality, please contact its developer Camille Phaneuf (cphaneuf@umich.edu).
