import os

f = open("./output")
line = f.readline()

dict_produce = {}
dict_consume = {}

while line:
    a = line.split()
    key = a[0]
    if key == "produce":
        val = int(a[1])
        if dict_produce.get(val, 0) == 1 or dict_consume.get(val, 0) == 1:
            print("Mutex error: ", key, val)
            exit()
        dict_produce[val] = 1
    elif key == "consume":
        val = int(a[1])
        if dict_produce.get(val, 1) == 0 or dict_consume.get(val, 0) == 1:
            print("Mutex error: ", key, val)
            exit()
        dict_consume[val] = 1
    line = f.readline()
f.close()

print("============================")
print("Mutex correctness test pass!")
print("============================")
