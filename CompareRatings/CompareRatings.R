### This script compares the transcription ratings of 2 independent RAs ###

# Load required packages
library(dplyr)

# Set working directory
setwd("/Users/camillephaneuf/Desktop/Undergrad Research/KrugerLab/inter_rater_reliability/CompareRatings")

# Read in data from Coders 1 and 2
coder1 <- read.csv("Coder1Output.csv")
coder2 <- read.csv("Coder2Output.csv")

# Ensure that there are the same number of rows and columns in coder1 and coder2
if (nrow(coder1) != nrow(coder2)) {
  print("WARNING: unequal number of rows from each coder. Abort.")
} else {
  print("Proceed.")
}
if (ncol(coder1) != ncol(coder2)) {
  print("WARNING: unequal number of columns from each coder. Abort.")
} else {
  print("Proceed.")
}

# Make df shell
SubjectID <- as.character(coder1$SubjectID) 
df <- data.frame("SubjectID" = SubjectID,
                 "Q1Response" = coder1$Q1Response,
                 "Q2Response" = coder1$Q2Response,
                 "Q3Response" = coder1$Q3Response,
                 "Q4Response" = coder1$Q4Response,
                 "Q5Response" = coder1$Q5Response,
                 "Coder1Q1" = coder1$CoderQ1,
                 "Coder1Q2" = coder1$CoderQ2,
                 "Coder1Q3" = coder1$CoderQ3,
                 "Coder1Q4" = coder1$CoderQ4,
                 "Coder1Q5" = coder1$CoderQ5,
                 "Coder2Q1" = coder2$CoderQ1,
                 "Coder2Q2" = coder2$CoderQ2,
                 "Coder2Q3" = coder2$CoderQ3,
                 "Coder2Q4" = coder2$CoderQ4,
                 "Coder2Q5" = coder2$CoderQ5)
df$MasterQ1 <- c("")
df$MasterQ2 <- c("")
df$MasterQ3 <- c("")
df$MasterQ4 <- c("")
df$MasterQ5 <- c("")

# Fill 'Master' columns of df
disagreement_count <- 0
for (i in 1:nrow(df)) {
  # Question 1
  if (df$Coder1Q1[i] == df$Coder2Q1[i]) {
    df$MasterQ1[i] <- df$Coder1Q1[i]
  } else {
    df$MasterQ1[i] <- -2
    disagreement_count <- disagreement_count + 1
  }
  # Question 2
  if (df$Coder1Q2[i] == df$Coder2Q2[i]) {
    df$MasterQ2[i] <- df$Coder1Q2[i]
  } else {
    df$MasterQ2[i] <- -2
    disagreement_count <- disagreement_count + 1
  }
  # Question 3
  if (df$Coder1Q3[i] == df$Coder2Q3[i]) {
    df$MasterQ3[i] <- df$Coder1Q3[i]
  } else {
    df$MasterQ3[i] <- -2
    disagreement_count <- disagreement_count + 1
  }
  # Question 4
  if (df$Coder1Q4[i] == df$Coder2Q4[i]) {
    df$MasterQ4[i] <- df$Coder1Q4[i]
  } else {
    df$MasterQ4[i] <- -2
    disagreement_count <- disagreement_count + 1
  }
  # Question 5
  if (df$Coder1Q5[i] == df$Coder2Q5[i]) {
    df$MasterQ5[i] <- df$Coder1Q5[i]
  } else {
    df$MasterQ5[i] <- -2
    disagreement_count <- disagreement_count + 1
  }
} 

# Print disagreement count
if (disagreement_count == 1) {
  print("There is 1 disagreement to be resolved, in-person, by the 2 independent RAs.")
} else {
  print(paste("There are", disagreement_count, "disagreements to be resolved, in-person, by the 2 independent RAs."))
}

# Output file CombinedOutput.csv
write.csv(df, file = "CombinedOutput.csv", row.names = FALSE)
