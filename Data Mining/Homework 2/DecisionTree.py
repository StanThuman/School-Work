from DecisionTreeNode import DecisionTreeNode

class DecisionTree:
    def __init__(self, root):
        self.root = root

    def getRoot(self):
        return self.root

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
