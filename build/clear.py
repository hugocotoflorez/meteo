import os

'''
This program clears build folder to default files
'''

def build_print(msg, *args, **kwargs):
    print('[BUILD]:', msg, *args, **kwargs) 

build_print('Starting', end='...');

_path = os.path.dirname(__file__)
os.chdir(_path);

print('Done');


files = [f for f in filter(lambda f: f[-3:] != '.py', os.listdir(_path))];

if (not input(f'[!] You are going to delete {", ".join(files)}. Enter to continue: ')):
    build_print('Deleting files', end='...');
    os.system(f'rm -rf {" ".join(files)}')
    print('done')

else: build_print('End')

