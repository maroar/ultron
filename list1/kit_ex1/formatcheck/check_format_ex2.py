import re
import os
import sys
import argparse
import subprocess


def run(infile, row, col, cost, basedir):
    '''
    Runs 'avalia_expande.sh' in basedir directory and returns
    whether the output is in the desired format
    :param initial_state:
    :param basedir:
    :return:
    '''

    os.chdir(basedir)

    subprocess.call('chmod +x avalia_expande.sh', shell=True)
    subprocess.call('./avalia_expande.sh %s %d %d %d > result.txt' % (infile, row, col, cost), shell=True)

    answer = open('result.txt').read().strip()

    print 'Your answer:\n%s' % answer

    if re.match(r'(\([a-z]+;\d+,\d+;\d+;\d+,\d+\))( \([a-z]+;\d+,\d+;\d+;\d+,\d+\))*$', answer) is not None:
        print 'Correct format. Now will check the names of the actions.'
        #removes parentheses and split in spaces
        str_tuples = answer.replace('(', '').replace(')', '').split(' ')

        actions_array = ['acima', 'abaixo', 'esquerda', 'direita', 'up', 'down', 'left', 'right']
        for t in str_tuples:
            action = t.split(';')[0]
            if action not in actions_array:
                print 'Unrecognized action "%s"' % action +\
                    '\nAllowed values: %s' % ', '.join(actions_array)

        print 'Done. Note that this script checks only format, not validity.'

    else:
        print 'Incorrect format. Correct format consists of tuples of:\n' +\
              '(string;int,int;int;int,int) separated by space. Example:\n' +\
              '(acima;4,2;%s;5,2) (left;5,1;%s;5,2) (direita;5,3;%s;5,2)\n' % (cost+1, cost+1, cost+1) +\
              'Found output:\n' + answer

    os.remove(os.path.join(basedir, 'result.txt'))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Assignment 1 - Exercise 2 format checker.')
    parser.add_argument('world_file', type=str,
                        help='Path to file with world description')

    parser.add_argument('row', type=int,
                        help='Row of the query state')

    parser.add_argument('col', metavar='column', type=int,
                        help='Column of the query state')

    parser.add_argument('cost', metavar='cost', type=int,
                        help='Cost of the queried state')

    parser.add_argument('-b', '--basedir', type=str, default='.',
                        help='Directory where the avalia_expande.sh is located')

    args = parser.parse_args()

    run(args.world_file, args.row, args.col, args.cost, args.basedir)

