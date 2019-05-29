#Python file to use matplotlib and create graphs for the generated csv file from main.cpp
import matplotlib.pyplot as plt

data = open("csvData.txt","r")

label1 = "Messages Per Month"
Name1 = data.readline()
axes1 = data.readline();
axesSplit = axes1.split(",")
xAxis = axesSplit[0]
yAxis = axesSplit[1]
PersonOneMessagesMonthX = []
PersonOneMessagesMonthY = []
PersonTwoMessagesMonthY = []
plt.title(label1)
plt.xlabel("Month")
plt.ylabel("Messages")
for i in range(12):
    labels = data.readline()
    lbSplit = labels.split(",")
    PersonOneMessagesMonthX.append(lbSplit[0])
    PersonOneMessagesMonthY.append(float(lbSplit[1]))

trash = data.readline()
trash = data.readline()
Name2 = data.readline()
axes1 = data.readline()
nameSplit = Name1.split(":")
correctName1 = nameSplit[0]
nameSplit = Name2.split(":")
correctName2 = nameSplit[0]

for i in range(12):
    labels = data.readline()
    lbSplit = labels.split(",")
    PersonTwoMessagesMonthY.append(float(lbSplit[1]))
plt.plot(PersonOneMessagesMonthX,PersonOneMessagesMonthY)
plt.plot(PersonOneMessagesMonthX,PersonTwoMessagesMonthY)
plt.legend([correctName1,correctName2])
plt.savefig("MessagesPerMonth.png")

