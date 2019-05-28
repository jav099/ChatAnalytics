#Python file to use matplotlib and create graphs for the generated csv file from main.cpp
import matplotlib.pyplot as plt

data = open("csvData.txt","r")


label1 = data.readline()
xandy = data.readline()
str = xandy.split(",")


print(label1)
print(str[0])