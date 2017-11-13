
class DecisionTreeNode:

    #constructor
    def __init__(self, testCondition=""):
        self.testCondition = testCondition
        self.left = None
        self.right = None
        self.index = 9999

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

    

    def printInfo (self):
        print("inside decisionTreeNode ", self.testCondition )
        print("inside decisionTreeNode ", self.left.testCondition )
        print("inside decisionTreeNode ", self.right.testCondition )
        return
