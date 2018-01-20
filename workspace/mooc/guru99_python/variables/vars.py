#Variables in Python

a = 3
print (a)

a = "Ameya\n"
print (a)

b = 4
print b
#print (a + b) #Error

#Concatenate Varables
print (a + str(b) + "\n")

#Global and local variables
c = 3
print "Global c = " + str(c)

def func():
	c = 2
	print "Local c = "  + str(c)

func()
print "Global c = " + str(c)

#Global variables contd
d = 5
print " Global d = " + str(d)

def fun2():
	global d
	d = "Modified in func2"
	print "From fun2 d = " + str(d)

fun2()
print "Outside fun2 d = " + str(d)

#Deleting a variable
del d
print "d = " + str (d)


 


