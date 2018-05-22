from lib.list import List

original = List("Test1", "Test2", "Test3", "Test4")

#set arbitrary links
original[0].ref = original[3]
original[1].ref = original[1]
original[2].ref = original[1]
original[3].ref = original[0]

copy = original.copy()

print("original list")
for idx, item in enumerate(original):
    print("link ({}): {}".format(idx, item.value))

print("copy list")
for idx, item in enumerate(copy):
    print("link ({}): {}".format(idx, item.value))


