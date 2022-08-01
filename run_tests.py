#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import subprocess

SAMPLE_SIZES = [10, 25, 50, 75, 100, 150, 200, 250, 300, 400, 500, 650, 800, 1000, 1500]
INPUT_FILES  = [f'data/Entrada {x}.txt' for x in SAMPLE_SIZES]
OUTPUT_FILES = [f'results/{x}.csv' for x in SAMPLE_SIZES]

EXEC = './bin/release/t4'
# EXEC = './bin/debug/t4'
# EXEC = 'echo'
RUNS = '11'

for i, (input_file, output_file) in enumerate(zip(INPUT_FILES, OUTPUT_FILES)):
    print('------------------------------------------------------------------------')
    print(f'Running batch [{i+1}/{len(SAMPLE_SIZES)}]')
    print('$',EXEC, input_file, "-r", RUNS, "-o", output_file)
    print('------------------------------------------------------------------------')

    subprocess.run(args=[
        EXEC, input_file, "-r", RUNS, "-o", output_file
    ])
    #break

print('------------------------------------------------------------------------')
print('Done.')
