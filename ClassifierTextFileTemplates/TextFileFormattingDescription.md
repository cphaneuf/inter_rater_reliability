# Standard Text File
(e.g., for a transcription of a video-taped discussion)

The text file that is read into the CommandLineClassifier (as it is currently implemented), CLC.cpp, should be formatted as follows:

## Number
`2` should be replaced by the number of ‘testing sessions’ pasted into the text file.
```
2 = number of sessions in this file
```

## Header
`MVI_2`, `2`, `TEST`, `ResearcherName1`, and `ResearcherName2` should be replaced by the session-specific details. Note: if the text file was only created by 1 member of the research team (i.e. their work was not reviewed by another team member), only `ResearcherName1` is needed. 
```
VIDEO: MVI_2
Session: 2
Type: TEST
Coder: ResearcherName1 REVIEWED BY ResearcherName2
QUESTION: 1
```

## Question and Verbal Responses
* It is recommended that prompting/clarifying questions be labeled as `Experimenter`, but any non-participant ID will do
*	Responses vary by the number of subjects in each session (can have subjects A-F, but can also have any subset of these subjects)
*	Each _verbal_ response ends in punctuation and is surrounded by “”
* Each response is transcribed exactly as heard (including  contractions, slang, etc.)
* Keep in mind, each response will need to be rated by CommandLineClassifier users as one of the following, according to the criteria set forth by the project manager in the question body: <br>
-1 = anti/negative <br>
0 = neutral <br>
1  =  pro/affirmative <br>
```
QUESTION: 1
This is the body of the first question that was asked of participants during a focus group style discussion?
2C: "Something that subject 2C says."
2A: "Something that subject 2A says."
2F: "Something that subject 2F says."
Experimenter: "The body of a prompting or clarifying question?"
2D: "Something that subject 2D says."
```

## Question and Nonverbal Responses
* Each _nonverbal_ response is encapsulated by ()
```
QUESTION: 5
This is the body of the fifth question that was asked of participants during a focus group style discussion?
2F: (nods yes)
2D: (shakes head no)
```

## End of File
`EOF` shoud be the last line of the text file.
```
EOF
```
