library(arules)
library(arulesViz)
library(tidyverse)

# Reading transactions
df <- read.transactions("Desktop/BE - Sem 1/CL-VII/Part B/Assignment 7/Groceries.csv", sep=",")

# View Transaction
inspect(df[1:10])

# summarize whole data set
summary(df)

# Frequency plot of top 15 items
itemFrequencyPlot(df, topN=15, type="absolute")

# Get the rules
rules = apriori(df, parameter = list(supp = 0.03, conf = 0.3))

# Summarize the rules
summary(rules)

# Print the rules
inspect(rules[1:10])

# Sort the rules by confidence
rules = sort(rules, by = "confidence")
options(digits = 2)

inspect(rules[1:10])

# Inspect the redundant rules
rules[is.redundant(rules)]
inspect(rules[is.redundant(rules)])

inspect(rules[1:10])

# Plot the graphs for the rules
plot(rules, method = "graph", engine = "interactive")
plot(rules, method = "paracoord")
plot(rules, method = "matrix", control = list(reorder = "none"))
plot(rules)
