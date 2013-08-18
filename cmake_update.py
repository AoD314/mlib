#!/usr/bin/env python3 

import os
import random
import tempfile
import shutil

def run(cmd):
    print(cmd)
    os.system(cmd)

def get_rnd_dir():
    a = []
    for i in range(26): 
        a += [chr(i + ord('a'))]
    for i in range(10): 
        a += [chr(i + ord('0'))]
    ch = ''.join(a)

    name = ''.join(random.choice(ch) for x in range(16))
    name = tempfile.gettempdir() + '/' + name
    while os.path.exists(name):
        name = ''.join(random.choice(ch) for x in range(16))
        name = tempfile.gettempdir() + '/' + name
    return name

def copy_files(src, dst):
    for f in os.listdir(src):
        s = os.path.join(src, f)
        if os.path.isfile(s):
            d = os.path.join(dst, f)
            print('cp ' + s + ' -> '+ d)
            shutil.copy(s, d)
    pass

# create tmp directory 
tmp = get_rnd_dir()
print("creating " + tmp + ' directory')
os.makedirs(tmp)

# cloning project 
print("cloning repo")
run("git clone --depth=1 https://github.com/AoD314/fcmake.git " + tmp)

# copy files
print("coping files")
s = os.path.join(tmp, 'cmake')
d = os.path.join(os.getcwd(), 'cmake')
try:
    os.makedirs(d)
except:
    pass
copy_files(s, d)

#delete tmp directory
print("remove " + tmp)
shutil.rmtree(tmp)
