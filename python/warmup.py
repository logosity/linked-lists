def search(ary, target):
    for i,a in enumerate(ary):
        if a == target:
            return i
    return -1



print(search([1,2,3,4,5,6], 2))
print(search([1,2,3,4,5,6], 6))
print(search([1,2,3,4,5,6], 0))


