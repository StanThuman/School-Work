#Stanley Lim 50441072
#Homework 3 - build a decision tree with classify, then apply model to treeNode
#it should run correct, I've outputted some of the processing while building the tree
#at the end I print out the records after applying the tree to the model
#python 3.5

from math import pow
from decimal import Decimal

#my classes
from DecisionTree import  DecisionTree
from DecisionTreeNode import  DecisionTreeNode

# true = 1, false = 0
#data set to use on decision tree
dataSet = [
    ('id', 'refund', 'Marital Status', 'Income', 'Cheat'),
    (1, 1,'Single', 125000, 0 ),
    (2, 0,'Married', 100000, 0 ),
    (3, 0, 'Single', 70000, 0 ),
    (4, 1, 'Married', 120000, 0 ),
    (5, 0, 'Divorced', 95000, 1 ),
    (6, 0, 'Married', 60000, 0 ),
    (7, 1, 'Divorced', 220000, 0 ),
    (8, 0, 'Single', 85000, 1 ),
    (9, 0, 'Married', 75000, 0 ),
    (10, 0, 'Single', 90000, 1 )]

# finds best split based on gini index
def findBestSplit( data, attribSet ):
    #set default values
    attribSetIndex = 0
    lowestGiniIndex = 9999
    attributeToSplitBy = ""
    yesCounter = 0
    noCounter = 0
    indexOfSplit = 9999

    for column in range(0, 4):
        #loop through colums until found
        if data[0][column] == attribSet[attribSetIndex]:
            #when column found, loops through its attribute values
            for row in range(len(data) - 1):
                #counts number of attributes for calculating gini index
                if data[row + 1][column] in ('Single', 'Divorced', 1):
                    yesCounter += 1
                if data[row + 1][column] in ('Married', 0):
                    noCounter += 1

                if data[row + 1][column] not in (1, 0, 'Single', 'Divorced', 'Married'):
                    if data[row + 1][column] > 80000:
                        yesCounter += 1
                    else:
                        noCounter += 1
            #end for
            #calculate lowest Gini Index and attribute name
            if yesCounter != 0 and noCounter != 0:
                totalSum = yesCounter + noCounter
                giniIndex = round(1 - (pow(yesCounter/totalSum, 2)) - (pow(noCounter/totalSum,2)), 3)
                if giniIndex < lowestGiniIndex: #if < previous gini Index, save values
                    lowestGiniIndex = giniIndex
                    attributeToSplitBy = attribSet[attribSetIndex]
                    indexOfSplit = column
                    s = "lowest gini index: " + str(lowestGiniIndex)  + " " + "attributeToSplitBy: " + str(attributeToSplitBy)
                    print(s)

            #reset variables
            giniIndex = 0
            yesCounter = 0
            noCounter = 0
            attribSetIndex += 1
        #end if
    s = "final gini index before return: " + str(lowestGiniIndex) + " " + "attributeToSplitBy: " + str(attributeToSplitBy)
    print(s)
    return attributeToSplitBy, indexOfSplit
#end function findBestSplit()

#splits data into two groups, yes and no, singe/divorced and married, > or < 80000
def splitDataIntoGroups( data, attributeToSplit):
    #find column
    yesList = []
    noList = []
    totalYesNoList = []

    attributeColumnIndex = 9999
    for index in range(0, 5):
        if data[0][index] == attributeToSplit: # get column index to loop through
            attributeColumnIndex = index

    if attributeColumnIndex != 9999:

        for row in range(len(data) -1): #only loops through one column
            #print(data[row+1][attributeColumnIndex])

            #only runs one set of if's per funciton call
            if data[row+1][attributeColumnIndex] in ('Single', 'Divorced', 1):
                yesList.append(data[row+1])
            if data[row+1][attributeColumnIndex] in ('Married', 0):
                noList.append(data[row+1])

            #second if set
            if data[row+1][attributeColumnIndex] not in (1, 0, 'Single', 'Married', 'Divorced'):
                if data[row+1][attributeColumnIndex] > 80000:
                    yesList.append(data[row+1])
                if data[row+1][attributeColumnIndex] < 80000:
                    noList.append(data[row+1])
    else:
        print("could not find attribute: error")

    yesList = [data[0]] + yesList
    noList = [data[0]] + noList
    totalYesNoList.append(yesList)
    totalYesNoList.append(noList)
    #print(yesList)
    #print(totalYesNoList)
    return totalYesNoList

def classify(classLabel, indexOfClass): #assigns new leafNode
    newLeaf = DecisionTreeNode()
    newLeaf.testCondition = "Cheat"
    newLeaf.setIndex(indexOfClass)
    return newLeaf


def buildTree ( data , attributeSet, targetClassAttribute):
    #calcStoppingCondition(data, 'Cheat')
    print("\nbuilding TreeNode....\n")
    if (len(data) <= 4):
        print("create leaf node because <= 4")
        leafNode = classify(targetClassAttribute, 4) #create leaf node
        return leafNode
    else:
        #calc best split
        #create node
        newNode = DecisionTreeNode()
        test_condition, index = findBestSplit(data, attribSet)
        newNode.setTestCondition(test_condition)
        newNode.setIndex(index)
        print("Splitting data on: ", newNode.testCondition)
        if len(attributeSet) > 0:
            attributeSet.remove(newNode.testCondition)

        yesNoList = splitDataIntoGroups(data, newNode.testCondition)
        #divide into two separate lists for yes's and nows
        #foreach setin list
        setLeftOrRight = 0
        for eachSet in yesNoList:
            #print("SET: ", eachSet)
            child = buildTree(eachSet, attribSet, "cheat")

            #all yes records go left
            if setLeftOrRight == 0:
                print("left node created")
                newNode.setLeft(child)

            #all no records go right
            if setLeftOrRight == 1:
                print("right node created")
                newNode.setRight(child)

            setLeftOrRight += 1

        return newNode
#end buildTree()

#used recursively
#sends data through the decision tree that was built
def applyModel(data, rootNode):
    print("Test condition: ", rootNode.getTestCondition())
    if(rootNode.testCondition == "Cheat"): #runs when cheat node is reached
        yesNoList = splitDataIntoGroups(data, rootNode.testCondition)
        setLeftOrRight = 0

        for eachSet in yesNoList: #prints yes and now records for cheat
            if setLeftOrRight == 0:
                    print("\nCheat Node Yes: ")
                    if len(eachSet) > 1:
                        for eachRecord in range(len(eachSet) - 1):
                            print(eachSet[eachRecord +1])
                    else:
                        print("No Records")

            if setLeftOrRight == 1:
                print("\nCheat Node No: ")
                if len(eachSet) > 1:
                    for eachRecord in range(len(eachSet) - 1):
                        print(eachSet[eachRecord +1])
                else:
                    print("No Records")
            setLeftOrRight += 1
        return

    else: #goes through each node until cheat is reach
        yesNoList = splitDataIntoGroups(data, rootNode.testCondition)
        for eachSet in yesNoList:
            for eachRecord in range(len(eachSet) - 1):
                print(eachSet[eachRecord +1])

        setLeftOrRight = 0
        for eachSet in yesNoList:
            #all yes records go left
            if setLeftOrRight == 0:
                print("\ngoing left: ", rootNode.getTestCondition())
                applyModel(eachSet, rootNode.getLeft())

            #all no records go right
            if setLeftOrRight == 1:
                print("\ngoing right: ", rootNode.getTestCondition())
                applyModel(eachSet, rootNode.getRight())

            setLeftOrRight += 1

        return
#####################################################
#####################################################
###Main Code Execution
#####################################################
#####################################################

#attribSet is used for iteration  when calculating gini index
attribSet = ['refund', 'Marital Status', 'Income']

#start building tree
print("\nBuilding Decision Tree\n")
decisionTree = DecisionTree(buildTree(dataSet, attribSet, "cheat"))
#decisionTree.printTree()

print("\nApplying model to Decision Tree\n")
applyModel(dataSet, decisionTree.getRoot())
