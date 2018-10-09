from time import time,ctime
import py_bridge as cmp

print('Today is',ctime(time()))

print('This was added after compiling')

print(cmp.hi())

print(cmp.bye())
