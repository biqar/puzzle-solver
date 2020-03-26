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
    success_count = 0
    success_iteration = 0
    failure_count = 0
    failure_iteration = 0

    while(1):
        if line_it >= len(lines):
            break

        line = lines[line_it]
        line_it += 1
        if line.startswith("[failure]"):
            failure_count += 1
            failure_iteration += int(line.split(' ')[-1].strip())
        elif line.startswith("[success]"):
            success_count += 1
            success_iteration += int(line.split(' ')[-1].strip())

    print("success count:", success_count)
    print("success iteration:", success_iteration)
    print("failure count:", failure_count)
    print("failure iteration:", failure_iteration)

if __name__ == '__main__':
    main()