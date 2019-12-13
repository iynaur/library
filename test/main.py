import glob
import math
import os
import hashlib
import pathlib
import shlex
import subprocess
import time
import resource
from typing import *

import onlinejudge
import utils


def exec_command(command: List[str]):
    subprocess.check_call(shlex.split(' '.join(command)))


def main(paths: List[pathlib.Path], *, timeout: float = math.inf) -> None:
    compilers = []
    if 'CXX' in os.environ:
        compilers.append(os.environ.get('CXX'))
    else:
        compilers.append('g++')
        compilers.append('clang++')

    cxxflags = os.environ.get('CXXFLAGS', '-std=c++17 -O2 -Wall -g')

    start = time.time()
    for path in paths:
        if utils.is_verified(path, compiler=compilers[0]):
            continue

        verified = False
        for cxx in compilers:
            print(cxx)
            macros = utils.list_defined_macros(path, compiler=cxx)
            print(macros)

            assert ('PROBLEM' in macros)
            url = macros['PROBLEM']
            directory = pathlib.Path('.verify-helper') / hashlib.md5(
                url.encode()).hexdigest()
            subprocess.check_call(['mkdir', '-p', str(directory)])

            print(url)
            if 'IGNORE' in macros:
                continue

            print("$ $CXX $CXXFLAGS -I . $file")
            exec_command([
                cxx, cxxflags, '-I', '.', '-o',
                str(directory / 'a.out'),
                str(path)
            ])
            exec_command(['sleep', '2'])
            exec_command([
                'oj', 'download', '--system', url, '-d',
                str(directory / 'test')
            ])

            if 'judge.yosupo.jp' in url:
                checker = onlinejudge.dispatch.problem_from_url(
                    url).download_checker_cpp()
                with open(directory / "checker.cpp", "wb") as f:
                    f.write(checker)

                exec_command([
                    'curl'
                    'https://raw.githubusercontent.com/MikeMirzayanov/testlib/master/testlib.h',
                    '>',
                    str(directory / 'testlib.h')
                ])

                exec_command([
                    cxx, cxxflags, '-I', '.', '-o',
                    str(directory / 'checker.out'),
                    str(directory / 'checker.cpp')
                ])
                exec_command([
                    'oj', 'test', '--judge-command',
                    str(directory / 'checker.out'), '-c',
                    str(directory / 'a.out'), '-d',
                    str(directory / 'test')
                ])
            elif 'ERROR' in macros:
                error = macros['ERROR']
                exec_command([
                    'oj', 'test', '-e', error, '-c',
                    str(directory / 'a.out'), '-d',
                    str(directory / 'test')
                ])
            else:
                exec_command([
                    'oj', 'test', '-c',
                    str(directory / 'a.out'), '-d',
                    str(directory / 'test')
                ])
            verified = True

        if verified:
            utils.mark_verified(path, compilers[0])

        # to prevent taking too long; we may fail to use the results of verification due to expired tokens
        if timeout is not None and time.time() - start > timeout:
            break

    utils.save_timestamps()
