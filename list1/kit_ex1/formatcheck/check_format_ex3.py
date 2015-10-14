import re
import os
import sys
import argparse
import subprocess


def run(alg, infile, row, col, basedir):
    '''
    Runs 'avalia_script.sh' in basedir directory and returns
    whether the output is in the desired format
    :param initial_state:
    :param basedir:
    :return:
    '''

    os.chdir(basedir)
    script_name = 'avalia_%s.sh' % alg
    subprocess.call('chmod +x %s' % script_name, shell=True)
    subprocess.call('./%s %s %d %d > result.txt' % (script_name, infile, row, col), shell=True)

    answer = open('result.txt').read().strip()

    print 'Your answer:\n%s\n' % answer
    valid_actions = ['acima', 'abaixo', 'esquerda', 'direita', 'up', 'down', 'left', 'right']

    if re.match(r'([a-z]+)( [a-z]+)*$', answer) is not None:
        print 'Correct format. Now will check the names of the actions.'
        found_actions = answer.split(' ')

        for a in found_actions:
            if a not in valid_actions:
                print 'Unrecognized action "%s"' % a +\
                    '\nAllowed values: %s' % ', '.join(valid_actions)

        print 'Done. Note that this script checks only format, not validity.'

    else:
        print 'Incorrect format. Correct format consists of actions separated by spaces.\nExample:\n' +\
              ' '.join(valid_actions)
              #'\nFound output:\n' + answer

    os.remove(os.path.join(basedir, 'result.txt'))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Assignment 1 - Exercise 3 format checker.')
    parser.add_argument('algorithm', type=str, choices=['bfs', 'dfs', 'astar'],
                        help='Algorithm to evaluate: bfs, dfs or astar')

    parser.add_argument('world_file', type=str,
                        help='Path to file with world description')

    parser.add_argument('row', type=int,
                        help='Row of the query state')

    parser.add_argument('col', metavar='column', type=int,
                        help='Column of the query state')

    parser.add_argument('-b', '--basedir', type=str, default='.',
                        help='Directory where the avalia_expande.sh is located')

    args = parser.parse_args()

    run(args.algorithm, args.world_file, args.row, args.col, args.basedir)

