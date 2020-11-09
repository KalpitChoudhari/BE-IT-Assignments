#Libraries
library(Metrics) 
library(DAAG)


#Read the csv file
df<-read.csv("./Desktop/BE - Sem 1/CL-VII/Part B/Assignment 2/Real estate.csv",header=TRUE)

#Print the data frame
print(df)
View(df)

#Check for null values
is.na(df)

#Summary of the dataset
View(summary(df))

#Number of rows and columns
print(nrow(df))
print(ncol(df))

#Drop the index column for training
df<-df[c(2:8)]
View(df)
colnames(df)

#Rename columns
names(df)[1] <- "Date"
names(df)[2] <- "Age"
names(df)[3] <- "Distance"
names(df)[4] <- "Convenience"
names(df)[5] <- "Latitude"
names(df)[6] <- "Longitude"
names(df)[7] <- "Price"
colnames(df)
View(df)

#Train test split

set.seed(1)
ind<-sample(2,nrow(df),replace=TRUE,prob = c(0.8,0.2))


tdata<-df[ind==1,]
vdata<-df[ind==2,]

View(vdata)
View(tdata)


#Linear Regression

lin_age<-lm(Price~Age,data=tdata)
#View(lin_age)
lin_dist<-lm(Price~Distance,data=tdata)
#View(lin_dist)
lin_conv<-lm(Price~Convenience,data=tdata)
#View(lin_conv)
lin_lat<-lm(Price~Latitude,data=tdata)
#View(lin_lat)
lin_long<-lm(Price~Longitude,data=tdata)
#View(lin_long)

#Information about the Residuals,Coefficient and Values Plotted
summary(lin_age)
summary(lin_dist)
summary(lin_conv)
summary(lin_lat)
summary(lin_long)

#Relationship between features and Target
plot(tdata$Price~tdata$Age,xlab="Age",ylab ="Price")
abline(lin_age)

plot(tdata$Price~tdata$Distance,xlab="Distance",ylab ="Price")
abline(lin_dist)


plot(tdata$Price~tdata$Convenience,xlab="Convenience",ylab ="Price")
abline(lin_conv)


plot(tdata$Price~tdata$Latitude,xlab="Latitude",ylab ="Price")
abline(lin_lat)


plot(tdata$Price~tdata$Longitude,xlab="Longitude",ylab ="Price")
abline(lin_long)




#Calculate MSE for distance (log transformation)
lin_dist_1<-lm(Price~log(Distance),data=tdata)
View(lin_dist_1)

#Prediction on train
lin_train_1<-predict(lin_dist_1,tdata)
lin_train_1
#Prediction on test
lin_pred_1<-predict(lin_dist_1,vdata)
lin_pred_1
#Calculate MSE 
train_mse_1=mse(tdata$Price,lin_train_1)
print(train_mse_1)

test_mse_1=mse(vdata$Price,lin_pred_1)
print(test_mse_1)
#Graph of test vs train mse
plotter<-c(train_mse_1,test_mse_1)
barplot(plotter,width = 0.02,xlab="data",names.arg = c("Train MSE","Test MSE"),ylab="error",main="Error")




#Correlation(Subset Selection Method)
res <- cor(tdata)
print(res)

lin_gen<-lm(Price~Convenience+Latitude+Longitude,data=tdata)
print(lin_gen)
#Prediction on train
lin_train<-predict(lin_gen,tdata)
lin_train
#Prediction on test
lin_pred<-predict(lin_gen,vdata)
lin_pred

#Calculate MSE on subset
train_mse=mse(tdata$Price,lin_train)
print(train_mse)

test_mse=mse(vdata$Price,lin_pred)
print(test_mse)



#Graph of test vs train mse for subset
plotter<-c(train_mse,test_mse)
barplot(plotter,width = 0.02,xlab="data",names.arg = c("Train MSE","Test MSE"),ylab="error",main="Error")


#K fold cross validation
model1=cv.lm(df,(Price~Convenience+Latitude+Longitude),m=5)