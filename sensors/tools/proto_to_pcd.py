import glob
import os

path = ''

for filename in glob.glob(os.path.join(path, '*.proto')):
    ''' Take a batch of proto files and gather relevant info in a single /
    file. '''
    lines = []
    with open(filename, 'r') as f:
        for i, line in enumerate(f):
            if i > 3 and i < 7:
                lines.append(line.strip())
            else:
                break
    with open('points.pcd', 'w+') as f:
        for line in lines:
            if len(line) != 0:
                chars = line.split()
                for i in chars:
                    # Remove the last character which is ";"
                    f.write(int(i[4][:-1]) + ' ')
        f.write('\n')
