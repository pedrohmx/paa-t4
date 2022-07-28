#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import subprocess

SAMPLE_SIZES = [10,]
INPUT_FILES  = [f'data/{x}.txt' for x in SAMPLE_SIZES]
OUTPUT_FILES = [f'results/{x}.txt' for x in SAMPLE_SIZES]

#EXEC = './bin/release/t4'
EXEC = './bin/debug/t4'
RUNS = '11'

for i, (input_file, output_file) in enumerate(zip(INPUT_FILES, OUTPUT_FILES)):
    print('------------------------------------------------------------------------')
    print(f'Running batch [{i+1}/{len(SAMPLE_SIZES)}]')
    print('$',EXEC, input_file, "-r", RUNS, "-o", output_file)
    print('------------------------------------------------------------------------')

    subprocess.run(args=[
        EXEC, input_file, "-r", RUNS, "-o", output_file
    ])

print('------------------------------------------------------------------------')
print('Done.')
