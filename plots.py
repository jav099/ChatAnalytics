#Python file to use matplotlib and create graphs for the generated csv file from main.cpp
import matplotlib.pyplot as plt


def daySorting(daysList):
    #Days will initially be ordered as Friday, Monday, Saturday, Sunday, Thursday, Tuesday, Wednesday
    orderedList = []
    orderedList.append(daysList[1])
    orderedList.append(daysList[5])
    orderedList.append(daysList[6])
    orderedList.append(daysList[4])
    orderedList.append(daysList[0])
    orderedList.append(daysList[2])
    orderedList.append(daysList[3])
    return orderedList


# Get current size
fig_size = plt.rcParams["figure.figsize"]

# Prints: [8.0, 6.0]
print("Current size:", fig_size)

fig_size[0] = 12
fig_size[1] = 9
plt.rcParams["figure.figsize"] = fig_size
# Get current size
fig_size = plt.rcParams["figure.figsize"]

# Prints: [8.0, 6.0]
print("New size:", fig_size)

#making the font size smaller
plt.rcParams.update({'font.size': 9})

data = open("csvData.txt","r")

label1 = "Messages Per Month"
Name1 = data.readline()
axes1 = data.readline()
axesSplit = axes1.split(",")
xAxis = axesSplit[0]
yAxis = axesSplit[1]
x = []
y = []
y2 = []
plt.title(label1)
plt.xlabel("Month")
plt.ylabel("Messages")
for i in range(12):
    labels = data.readline()
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))
#This will read the % signs
trash = data.readline()
Name2 = data.readline()
axes = data.readline()
nameSplit = Name1.split(":")
correctName1 = nameSplit[0]
nameSplit = Name2.split(":")
correctName2 = nameSplit[0]

while(True):
    labels = data.readline()
    if (labels[0] == "%"):
        break
    lbSplit = labels.split(",")
    y2.append(float(lbSplit[1]))
plt.plot(x, y)
plt.plot(x, y2)
plt.legend([correctName1,correctName2])
plt.savefig("MessagesPerMonth.png")

#Here the first graph ends. The next line is used to clear the plot
plt.clf()
x.clear()
y.clear()
y2.clear()

Name1 = data.readline()
axes = data.readline()
while(True):
    labels = data.readline()
    if (labels[0] == "%"):
        break
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))
#sorts both lists so that the ordering is monday-sunday
x = daySorting(x)
y = daySorting(y)

Name2 = data.readline()
axes = data.readline()

while(True):
    labels = data.readline()
    if (labels[0] == "%"):
        break
    lbSplit = labels.split(",")
    y2.append(float(lbSplit[1]))

y2 = daySorting(y2)

plt.title("Messages Per Day of Week")
plt.xlabel(axes.split(",")[0])
plt.ylabel(axes.split(",")[1])

plt.plot(x,y)
plt.plot(x,y2)
plt.legend([correctName1,correctName2])
plt.savefig("MessagesPerDay.png")

#Here the second graph ends. The next line is used to clear the plot
plt.clf()
x.clear()
y.clear()
y2.clear()

Name1 = data.readline()
axes = data.readline()
while(True):
    labels = data.readline()
    if(labels[0] == "%"):
        break
    print(labels)
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))

Name2 = data.readline()
axes = data.readline()

while(True):
    labels = data.readline()
    if (labels[0] == "%"):
        break
    lbSplit = labels.split(",")
    y2.append(float(lbSplit[1]))

plt.title("Messages per year")
plt.xlabel(axes.split(",")[0])
plt.ylabel(axes.split(",")[1])

plt.plot(x,y)
plt.plot(x,y2)
plt.legend([correctName1,correctName2])
plt.savefig("MessagesPerYear.png")

#Here the third graph ends. The next line is used to clear the plot
plt.clf()
x.clear()
y.clear()
y2.clear()

Name1 = data.readline()
axes = data.readline()
for i in range(20):
    labels = data.readline()
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))

plt.title("Word Frequency" + " " + correctName1)
plt.xlabel(axes.split(",")[0])
plt.ylabel(axes.split(",")[1])
plt.bar(x,y)
plt.savefig("wordFrequency" + correctName1)

#Here the fourth graph ends. The next line is used to clear the plot
plt.clf()
x.clear()
y.clear()
y2.clear()
trash = data.readline()
Name2 = data.readline()
axes = data.readline()
for i in range(20):
    labels = data.readline()
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))


plt.title("Word Frequency" + " " + correctName2)
plt.xlabel(axes.split(",")[0])
plt.ylabel(axes.split(",")[1])
plt.bar(x,y,color = "g")
plt.savefig("wordFrequency" + correctName2)

#Here the fifth graph ends. The next line is used to clear the plot
plt.clf()
x.clear()
y.clear()
y2.clear()
trash = data.readline()
Name1 = data.readline()
axes = data.readline()
for i in range(20):
    labels = data.readline()
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))



plt.title("Word Frequency (raw)" + " " + correctName1)
plt.xlabel(axes.split(",")[0])
plt.ylabel(axes.split(",")[1])
plt.bar(x,y)
plt.savefig("wordFrequency (raw)" + correctName1)

#Here the sixtg graph ends. The next line is used to clear the plot
plt.clf()
x.clear()
y.clear()
y2.clear()

trash = data.readline()
Name2 = data.readline()
axes = data.readline()
for i in range(20):
    labels = data.readline()
    lbSplit = labels.split(",")
    x.append(lbSplit[0])
    y.append(float(lbSplit[1]))



plt.title("Word Frequency (raw)" + " " + correctName2)
plt.xlabel(axes.split(",")[0])
plt.ylabel(axes.split(",")[1])

plt.bar(x,y,color = "g")


plt.savefig("wordFrequency (raw)" + correctName2)

plt.clf()
x.clear()
y.clear()
y2.clear()

#end of seventh graph

#trash = data.readline()
#trash = data.readline()
#duration = float(data.readline())
#ylabel = "days"
#title = "Chat duration"
#y.append(duration)
#x.append("duration")
#plt.title(title)
#plt.ylabel(ylabel)
#plt.bar(x,y, width=0.000001)
#plt.savefig("chatDuration")

#plt.clf()
#x.clear()
#y.clear()

#end of graph




