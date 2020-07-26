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
