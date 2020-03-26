#!/usr/bin/python

import sys

def main():
    file_name = str(sys.argv[1])
    text_file = open(file_name, "r")
    lines = text_file.readlines()
    print(">>", file_name)
    print("# of lines: ", len(lines))
    text_file.close()

    line_it = 0
    count = 0
    iteration = 0
    restart_required = 0

    while(1):
        if line_it >= len(lines):
            break

        line = lines[line_it]
        line_it += 1
        count += 1
        iteration += int(line.split(' ')[-1].strip())
        restart_required += int(line.split(' ')[-2].strip())

    print("count:", count)
    print("iteration:", iteration)
    print("restart required:", restart_required)

if __name__ == '__main__':
    main()