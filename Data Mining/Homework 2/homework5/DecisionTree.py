from DecisionTreeNode import DecisionTreeNode

class DecisionTree:
    def __init__(self, root = 0):
        self.root = root

    def getRoot(self):
        return self.root

    def calculateGiniIndex(self, yesCounter, noCounter, totalSum):
        giniIndex = round(1 - (pow(yesCounter/totalSum, 2)) - (pow(noCounter/totalSum,2)), 3)
        return giniIndex

    def calculateIncomeSplit(self, data):
        print("inside calc income")
        highestIncome = 0
        lowestIncome = 99999999

        #find lowest and highest Income
        for eachIncomeValue in range(len(data)-1):
            print(data[eachIncomeValue+1][3])
            if data[eachIncomeValue+1][3] > highestIncome:
                highestIncome = data[eachIncomeValue+1][3]

            if data[eachIncomeValue+1][3] < lowestIncome:
                lowestIncome = data[eachIncomeValue+1][3]
        #end for

        #calculating gini index for income by incrementing 20000 to find best split
        currentIncome = lowestIncome + 20000
        finalIncomeForSplit = 0
        finalGiniIndex = 9999

        #loops through range of income values to decide best gini index
        while currentIncome < highestIncome:
            #set values for each new loop iteration
            incomeGiniIndex = 99999
            aboveIncomeSplit = []
            aboveIncomeYesCounter = 0
            aboveIncomeNoCounter = 0

            belowIncomeSplit = []
            belowIncomeYesCounter = 0
            belowIncomeNoCounter = 0

            tempGiniIndex = 0

            #split income above and below current split into lists
            for row in range(len(data)-1):
                print(data[row+1][3])
                if data[row+1][3] > currentIncome:
                    aboveIncomeSplit.append(data[row+1])
                else:
                    belowIncomeSplit.append(data[row+1])

            print("\n")
            #increment cheat values to find amount of yes and no in aboveIncomeSplit
            for row in range(len(aboveIncomeSplit)):
                print(aboveIncomeSplit[row][4])
                if aboveIncomeSplit[row][4] == 1:
                    aboveIncomeYesCounter += 1
                else:
                    aboveIncomeNoCounter += 1
                #yesno of abovesplit

            print("\n")
            #increment cheat values to find amount of yes and no in belowIncomeSplit
            for row in range(len(belowIncomeSplit)):
                print(belowIncomeSplit[row][3])
                #yesno of belowSplit
                if belowIncomeSplit[row][4] == 1:
                    belowIncomeYesCounter += 1
                else:
                    belowIncomeNoCounter +=1

            #calc individual gini index
            aboveIncomeGiniIndex = self.calculateGiniIndex(aboveIncomeYesCounter, aboveIncomeNoCounter, len(aboveIncomeSplit))
            belowIncomeGiniIndex = self.calculateGiniIndex(belowIncomeYesCounter, belowIncomeNoCounter, len(belowIncomeSplit))


            #calculate total index
            tempGiniIndex = ((len(aboveIncomeSplit)/10) * aboveIncomeGiniIndex) + ((len(belowIncomeSplit)/10) * belowIncomeGiniIndex)

            #saves lowest total gini index
            if tempGiniIndex < finalGiniIndex:
                finalGiniIndex = tempGiniIndex
                finalIncomeForSplit = currentIncome

            currentIncome = currentIncome + 20000

        #return best income to split on
        return finalIncomeForSplit

    # finds best split based on gini index
    def findBestSplit( self, data, incomeToSplitBy, attribSet ):
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

                    #for income calculation
                    if data[row + 1][column] not in (1, 0, 'Single', 'Divorced', 'Married'):
                        if data[row + 1][column] > incomeToSplitBy:
                            yesCounter += 1
                        else:
                            noCounter += 1
                #end for

                #calculate lowest Gini Index and attribute name
                #looking for least gini index for best split
                if yesCounter != 0 and noCounter != 0:
                    totalSum = yesCounter + noCounter
                    giniIndex = self.calculateGiniIndex(yesCounter, noCounter, totalSum)
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
    def splitDataIntoGroups( self, data, incomeToSplitBy, attributeToSplit):
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
                    if data[row+1][attributeColumnIndex] > incomeToSplitBy:
                        yesList.append(data[row+1])
                    if data[row+1][attributeColumnIndex] < incomeToSplitBy:
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

    def classify(self, classLabel, indexOfClass): #assigns new leafNode
        newLeaf = DecisionTreeNode()
        newLeaf.testCondition = "Cheat"
        newLeaf.setIndex(indexOfClass)
        return newLeaf


    def buildTree (self, data , attribSet, incomeToSplitBy, targetClassAttribute):
        #calcStoppingCondition(data, 'Cheat')
        print("\nbuilding TreeNode....\n")
        if (len(data) <= 4):
            print("create leaf node because <= 4")
            leafNode = self.classify(targetClassAttribute, 4) #create leaf node
            return leafNode
        else:
            #calc best split
            #create node
            newNode = DecisionTreeNode()
            test_condition, index = self.findBestSplit(data, incomeToSplitBy, attribSet)
            print("non leaf test_condition", test_condition)
            newNode.setTestCondition(test_condition)
            newNode.setIndex(index)
            print("Splitting data on: ", newNode.testCondition)
            if len(attribSet) > 0:
                attribSet.remove(newNode.testCondition)

            yesNoList = self.splitDataIntoGroups(data, incomeToSplitBy, newNode.testCondition)
            #divide into two separate lists for yes's and nows
            #foreach setin list
            setLeftOrRight = 0
            for eachSet in yesNoList:
                #print("SET: ", eachSet)
                child = self.buildTree(eachSet, attribSet, incomeToSplitBy, "cheat")

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

    def setupTree(self, dataset, attribSet, targetClassAttribute):

        #calculate gini for Income
        incomeToSplit = self.calculateIncomeSplit(dataset)
        print("INCOME TO SPLIT BY: ", incomeToSplit)
        newRoot = self.buildTree(dataset, attribSet, incomeToSplit, targetClassAttribute)
        self.root = newRoot
        print("\nApplying model to Decision Tree\n")
        self.applyModel(dataset, incomeToSplit, self.root)
        return

    #calculates possible predictions for labels based on the model
    def applyModel(self, data, incomeToSplitBy, rootNode):
        print("Test condition: ", rootNode.getTestCondition())

        if(rootNode.testCondition == "Cheat"): #runs when cheat node is reached
            yesNoList = self.splitDataIntoGroups(data, incomeToSplitBy, rootNode.testCondition)
            setLeftOrRight = 0

            yesCounter = 0
            noCounter = 0

            #calculates number of yes and no answers for cheat
            for eachSet in yesNoList: #prints yes and now records for cheat
                if setLeftOrRight == 0:
                    print("\nCheat Node Yes: ")
                    if len(eachSet) > 1:
                        yesCounter = len(eachSet)
                        for eachRecord in range(len(eachSet) - 1):
                            print(eachSet[eachRecord +1])
                    else:
                        print("No Records")

                if setLeftOrRight == 1:
                    print("\nCheat Node No: ")
                    if len(eachSet) > 1:
                        noCounter = len(eachSet)
                        for eachRecord in range(len(eachSet) - 1):
                            print(eachSet[eachRecord +1])
                    else:
                        print("No Records")

                setLeftOrRight += 1

            #uses yes no counters to decide if cheat is yes or no for new dataset
            if noCounter > yesCounter:
                print("SET NO")
                rootNode.predictionValue = "no"

            if yesCounter > noCounter:
                rootNode.predictionValue = "yes"
                print("SET YES")

            if noCounter == yesCounter:
                print("SET FIFTYFIFTY")
                rootNode.predictionValue = "50/50"

            yesCounter = 0
            noCounter = 0

            return

        else: #goes through each node until cheat is reach
            yesNoList = self.splitDataIntoGroups(data, incomeToSplitBy, rootNode.testCondition)
            for eachSet in yesNoList:
                for eachRecord in range(len(eachSet) - 1):
                    print(eachSet[eachRecord +1])

            setLeftOrRight = 0
            for eachSet in yesNoList:
                #all yes records go left
                if setLeftOrRight == 0:
                    print("\ngoing left of ", rootNode.getTestCondition(), " node")
                    self.applyModel(eachSet, incomeToSplitBy, rootNode.getLeft())

                #all no records go right
                if setLeftOrRight == 1:
                    print("\ngoing right of ", rootNode.getTestCondition(), " node")
                    self.applyModel(eachSet, incomeToSplitBy, rootNode.getRight())

                setLeftOrRight += 1

            return

    #predict what label the new data set will have
    #used after building the tree at applying model
    def identifyNewData(self, newDataSet):
        print("\ncalculating new dataset")

        #0 for no
        #1 for yes
        current = self.root

        #if refund is yes,  go left and finish
        if newDataSet[current.index] == 1:
            current = current.left
            print("cheat = ", current.predictionValue)
            return

        current = current.right

        #traverse right side of first node
        if newDataSet[current.index] in ('single', 'divorced'):

            current = current.left
            if newDataSet[current.index] < 80000:
                current = current.left
            else:
                current = current.right


        else:
            if newDataSet[current.index] in ('married'):
                current = current.right

        print("cheat = ", current.predictionValue)
        return
    #end function

    def printTree(self):
        print("\n")
        print("root: ", self.root.testCondition)
        print("root index: ", self.root.index)
        print("left: ", self.root.left.testCondition)
        print("right: ", self.root.right.testCondition)
        print("\n")
        maritalStatusNode = self.root.getRight()

        print("maritalStatusNode: ", maritalStatusNode.testCondition)
        print("maritalStatusNode index: ", maritalStatusNode.index)
        print("left: ", maritalStatusNode.left.testCondition)
        print("right: ", maritalStatusNode.right.testCondition)
        print("\n")
        incomeNode = maritalStatusNode.getLeft()

        print("incomeNode: ", incomeNode.testCondition)
        print("incomeNode index: ", incomeNode.index)
        print("left: ", incomeNode.left.testCondition)
        print("right: ", incomeNode.right.testCondition)
        print("\n")
