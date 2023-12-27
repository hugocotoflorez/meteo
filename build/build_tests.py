import os

'''
This program creates the tests executables and save it in the folder tests
'''

def build_print(msg, *args, **kwargs):
    print('[BUILD]:', msg, *args, **kwargs) 

build_print('Starting', end='...');

path_list = os.path.abspath(__file__).split('/')[:-2]+['tests'];
test_path = '/'.join(path_list);
build_path = os.path.dirname(__file__)
os.chdir(build_path);

print('Done');

build_print('Creating CMakeLists.txt:');

c_files = [f.removesuffix(".c") for f in filter(lambda f: f[-2:] == '.c', os.listdir(test_path))];

build_print('Files to compile:', *c_files);
build_print('Creating file', end='...')

with open('CMakeLists.txt', 'w') as f:
    f.writelines(
    ["cmake_minimum_required(VERSION 3.25)\n",
    "project(meteo C)\n",
    "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../build)\n",
    "set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)\n",
    "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)\n",
    "set(CMAKE_C_STANDARD 11)\n",
    "link_directories(../build)\n",
    "link_directories(../src)\n",
    "link_libraries(libmeteo.a)\n"] +
    [f"add_executable({a} ../tests/{a}.c)\n" for a in c_files]
    )

print('Done')

os.system('cmake CMakeLists.txt')
os.system('make all')