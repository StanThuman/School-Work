# week 1 homework
# Stanley Lim
# Data Mining
# Everything should work correctly



tuple1 = (1, 2, 3, 4, 5)
list1 = [6,7,8,9,10]

print ("tuple1: ", tuple1)
print ("list1: ", list1)

print("adding tuple[0] to list1[4]")
list1[4] = list1[4] + tuple1[0]
print ("new list1: ", list1)

# convert tuple to list in order to add to list1
tuple1 = list(tuple1)

print("adding tuple1 to list1")
list1 = list1 + tuple1


print ("new list1: ", list1)
