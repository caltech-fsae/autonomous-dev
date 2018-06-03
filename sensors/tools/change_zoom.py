import glob
import os
import itertools

path = ''

for filename in glob.glob(os.path.join(path, '*.pcd')):
    lines = []
    with open(filename, 'r') as f:
        for line in itertools.islice(f, 11, None):
            lines.append(line.strip())
    with open('new_' + filename, 'w+') as f:
        for line in lines:
            if len(line) != 0:
                nums = line.split()
                for num in nums:
                    f.write(str(float(num) / 10) + ' ')
            f.write('\n')
