> df2 <- read.csv("/home/rootnova/Desktop/DSBDA/Assignment 8/dataset_Facebook.csv",sep=";")
> print(df2.head())
Error in df2.head() : could not find function "df2.head"
> head(df2)
Page.total.likes   Type Category Post.Month
1           139441  Photo        2         12
2           139441 Status        2         12
3           139441  Photo        3         12
4           139441  Photo        2         12
5           139441  Photo        2         12
6           139441 Status        2         12
Post.Weekday Post.Hour Paid
1            4         3    0
2            3        10    0
3            3         3    0
4            2        10    1
5            2         3    0
6            1         9    0
Lifetime.Post.Total.Reach
1                      2752
2                     10460
3                      2413
4                     50128
5                      7244
6                     10472
Lifetime.Post.Total.Impressions
1                            5091
2                           19057
3                            4373
4                           87991
5                           13594
6                           20849
Lifetime.Engaged.Users Lifetime.Post.Consumers
1                    178                     109
2                   1457                    1361
3                    177                     113
4                   2211                     790
5                    671                     410
6                   1191                    1073
Lifetime.Post.Consumptions
1                        159
2                       1674
3                        154
4                       1119
5                        580
6                       1389
Lifetime.Post.Impressions.by.people.who.have.liked.your.Page
1                                                         3078
2                                                        11710
3                                                         2812
4                                                        61027
5                                                         6228
6                                                        16034
Lifetime.Post.reach.by.people.who.like.your.Page
1                                             1640
2                                             6112
3                                             1503
4                                            32048
5                                             3200
6                                             7852
Lifetime.People.who.have.liked.your.Page.and.engaged.with.your.post
1                                                                 119
2                                                                1108
3                                                                 132
4                                                                1386
5                                                                 396
6                                                                1016
comment like share Total.Interactions
1       4   79    17                100
2       5  130    29                164
3       0   66    14                 80
4      58 1572   147               1777
5      19  325    49                393
6       1  152    33                186
> plot(df2$like~df2$Type,xlab="Type",ylab="Like",col="blue",main=" Type vs Like",pch=16)#Scatterplot
> hist(df2$Post.Month,xlab ="Post",main="Post Frequency",col="green")
> hist(df2$Page.total.likes,xlab = "Pages like",main="Distribution of Pages liked",col="blue")
> boxplot(df2$Post.Weekday~df2$Page.total.likes,xlab="Total Likes",ylab="Post on Weekday")
> library(ggplot2)
> library(dplyr)

Attaching package: ‘dplyr’

The following objects are masked from ‘package:stats’:
  
  filter, lag

The following objects are masked from ‘package:base’:
  
  intersect, setdiff, setequal, union

> 
  > ggplot(df2)
> ggplot(df2,aes(y=like,x=type,col=target))+geom_point()
Error in FUN(X[[i]], ...) : object 'type' not found
> ggplot(df2,aes(y=like,x=Type,col=target))+geom_point()
Error in FUN(X[[i]], ...) : object 'target' not found
> ggplot(df2,aes(y=like,x=Type,col=Page.total.likes))+geom_point()
Warning message:
  Removed 1 rows containing missing values (geom_point). 
> ggplot(df2,aes(x=like))+geom_histogram(bins=20,fill="green",col="red")
> View(df2)
> ggplot(df2,aes(x=share))+geom_bar()
> ggplot(data =df2,aes(x=share,col=factor(Type)))+geom_freqpoly(bins=10)
