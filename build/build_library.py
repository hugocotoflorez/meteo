import os

'''
This program creates a library based on .c files and .h files under src directory. The library will be saven in the same folder as this file.
'''

def build_print(msg, *args, **kwargs):
    print('[BUILD]:', msg, *args, **kwargs) 

build_print('Starting', end='...');

path_list = os.path.abspath(__file__).split('/')[:-2]+['src'];
path = '/'.join(path_list);
os.chdir(path);

print('Done');

libname = f'lib{path_list[-2]}';
build_print('Libname:', libname);
c_files = [f.removesuffix(".c") for f in filter(lambda f: f[-2:] == '.c', os.listdir(path))];

build_print('Files to include:', *c_files);
build_print('Creating library', end='...')

for file in c_files:
    os.system(f'gcc -c -o {file}.o {file}.c');

os.system(f'ar rs {libname}.a {" ".join(["../src/"+a+".o" for a in c_files])}  2> /dev/null');
os.chdir(path)

print('Done')
build_print('Removing temp files', end='...');

os.system(f'rm {" ".join([a+".o" for a in c_files])}');

print('Done')