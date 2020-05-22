#!/bin/env python3
# Evan Widloski - 2020-04-15
# Automated testing for alarm/algorithm.h

# Build alarm/algorithm.so with:
   # gcc -g -o algorithm.so -shared -fPIC algorithm.h

from cffi import FFI
import argparse
import logging
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys
from rapidalarm.build_algorithm import build


def load_dataset(datafile):
    """Read a rapidalarm dataset into a Pandas dataframe

    Args:
        datafile (str): path to datafile

    Returns:
        DataFrame: has columns 't', 'pip', 'peep', 'pressure', 'flow'
            and attribute 'sample_rate'
    """

    f = open(datafile, 'r')
    # read sample_rate from first line
    sample_rate = int(f.readline().split(',')[1])

    x = pd.read_csv(f)
    x.sample_rate = sample_rate
    x['t'] = np.linspace(0, len(x) / sample_rate, len(x))

    return x


def load_pandas(dataset, rebuild=False, end=None):
    """Run algorithm with recorded data and return pandas DataFrame with result

    Args:
        data (str): path to dataset

    Returns:
        pandas.DataFrame: dataframe containing alg. input and results
    """
    global lib

    df = load_dataset(dataset)

    if rebuild:
        build()

    from rapidalarm.algorithm import lib

    lib.init_algorithm(df.sample_rate)

    pip, peep, rr, v_high, v_low, alarm_raised = [], [], [], [], [], []

    # build dict from enums
    alarms = [
        'ALARM_HP', 'ALARM_HR', 'ALARM_LP', 'ALARM_LR', 'ALARM_NC', 'ALARM_NONE'
    ]
    alarms = {getattr(lib, s):s for s in alarms}

    for p in df.pressure[:end]:
        lib.run_algorithm(p)

        pip.append(lib.pip)
        peep.append(lib.peep)
        rr.append(lib.respiration_rate)
        v_high.append(lib.v_high)
        v_low.append(lib.v_low)
        alarm_raised.append(alarms[lib.alarm_raised])

    df['pip'] = pip
    df['peep'] = peep
    df['rr'] = rr
    df['v_high'] = v_high
    df['v_low'] = v_low
    df['alarm_raised'] = pd.Categorical(alarm_raised, categories=alarms.values())

    return df


def csv(args):

    df = load_pandas(args.dataset, args.rebuild)

    df.to_csv(sys.stdout, index=False)

def plot(args):

    df = load_pandas(args.dataset, args.rebuild)

    plt.figure(figsize=(12, 4))
    plt.subplot(2, 1, 1)
    plt.plot(df.t[args.s:args.e], df.pressure[args.s:args.e], 'k', linewidth=0.5)
    plt.plot(df.t[args.s:args.e], df.v_high[args.s:args.e], 'r', linewidth=0.5)
    plt.plot(df.t[args.s:args.e], df.v_low[args.s:args.e], 'b', linewidth=0.5)
    plt.legend(['Pressure', 'v_high', 'v_low'])

    plt.subplot(2, 1, 2)
    plt.plot(df.t[args.s:args.e], df.pip[args.s:args.e])
    plt.plot(df.t[args.s:args.e], df.peep[args.s:args.e])
    plt.plot(df.t[args.s:args.e], df.rr[args.s:args.e])
    plt.grid(True)

    plt.legend(['PIP', 'PEEP', 'RR'])
    plt.xlabel('time (s)')
    plt.show()

# def build():
#     # build .c and return FFI library

#     ffi = FFI()

#     source_file = '../firmware/algorithm.c'
#     include_dir = '../firmware/'
#     types = 'algorithm.cdef'

#     # read in variable datatypes
#     ffi.cdef(open(types, 'r').read())

#     # build shared object
#     ffi.set_source(
#         "algorithm",
#         open(source_file, 'r').read(),
#         include_dirs=[include_dir],
#     )
#     ffi.compile(verbose=True)

#     from algorithm import lib

#     return lib


def main():

    parser = argparse.ArgumentParser(description="Algorithm Tester")

    parser.add_argument('--rebuild', action='store_true', default=False, help="rebuild algorithm.c")
    parser.add_argument('--debug', action='store_true', default=False, help="enable debugging")

    subparsers = parser.add_subparsers()
    subparsers.required = True

    csv_parser = subparsers.add_parser('csv', help="generate csv output")
    # csv_parser.add_argument('start', type=int, help="simulation start sample #")
    # csv_parser.add_argument('end', type=int, help="simulation end sample #")
    csv_parser.set_defaults(func=csv)

    plot_parser = subparsers.add_parser('plot', help="plot input waveform along with estimated parameters")
    plot_parser.add_argument('dataset', type=str, help="path to dataset")
    plot_parser.add_argument('-s', metavar='START', type=int, default=0, help="simulation start sample num")
    plot_parser.add_argument('-e', metavar='END', type=int, default=None, help="simulation end sample num")
    plot_parser.set_defaults(func=plot)

    args = parser.parse_args()

    if args.debug:
        log.setLevel(logging.DEBUG)
        log.debug("Debugging enabled")

    args.func(args)


if __name__ == '__main__':
    main()