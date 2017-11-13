
class DecisionTreeNode:

    #constructor
    def __init__(self, testCondition=""):
        self.testCondition = testCondition
        self.left = None
        self.right = None
        self.index = 9999
        self.predictionValue = "none"

    #setters and getters
    def setRight (self, newRight):
        self.right = newRight
        return

    def getRight(self):
        return self.right

    def setLeft (self, newLeft):
        self.left = newLeft
        return

    def getLeft(self):
        return self.left

    def setIndex (self, newIndex):
        self.index = newIndex
        return

    def getIndex (self):
        return self.index

    def setTestCondition(self, newTestCondition):
        self.testCondition = newTestCondition
        return

    def getTestCondition(self):
        return self.testCondition


    def printDetails(self):
        print("\nTest condition: ", self.testCondition)
        print("Index: ", self.index)
        print("left Node Test condition: ", self.left.testCondition)
        print("right Node Test condition: ", self.right.testCondition)
        return

    def printInfo (self):
        print("starting print inside test condition ", self.testCondition )
        print("inside left test condition ", self.left.testCondition )
        print("inside right test condition ", self.right.testCondition )
        return
