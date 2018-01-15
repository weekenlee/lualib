print "helloworld in lua"
a = "ima"
b = "imb"
print("from cpp value "..valueCPP)
fun()
c,d = addandsub(100,50)
print(c)
print(d)


function oneretone(one)
	print(one)
	return "lua return "..one
end

function tworettwo(one, two)
	print(one)
	print(two)
	return one+two,one*two
end

table = {
	a = 123,
	b = 456,
}

