#Stanley Lim 50441072
#Homework 5 - build a decision tree with classify, then apply model to treeNode
#to calculate possible prediction values, then apply a new dataset to predict its class label
#it should run correct, I've outputted some of the processing while building the tree
#I printed out the records after applying the tree to the model
#at the end I passed a new dataset to predict its value according to the built decision tree
#python 3.5

from math import pow
from decimal import Decimal

#my classes
from DecisionTree import  DecisionTree
#from DecisionTreeNode import  DecisionTreeNode

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



#used recursively
#sends data through the decision tree that was built

#####################################################
#####################################################
###Main Code Execution
#####################################################
#####################################################

#attribSet is used for iteration  when calculating gini index
attribSet = ['refund', 'Marital Status', 'Income']

#start building tree
print("\nBuilding Decision Tree\n")
decisionTree = DecisionTree()
decisionTree.setupTree(dataSet, attribSet, "cheat")



#id number, refund, marital status,
newDataset = (123, 0, "single", 100000)
decisionTree.identifyNewData(newDataset)


#applyModel(dataSet, decisionTree.getRoot())
