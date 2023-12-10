# pip install subprocess.run
# pip install scipy
# pip install os-sys
# pip install lib-platform

import subprocess
import pandas as pd
import numpy as np
import platform
from subprocess import Popen, PIPE, check_output
import os
from scipy import stats
import matplotlib.pyplot as plt

debug = False


def laplace_mech(v, sensitivity, epsilon):
    return v + np.random.laplace(loc=0, scale=sensitivity / epsilon)


def laplace_mech_vec(vec, sensitivity, epsilon):
    return [v + np.random.laplace(loc=0, scale=sensitivity / epsilon) for v in vec]


def pct_error(orig, priv):
    return np.abs(orig - priv) / orig * 100.0


adult = pd.read_csv('https://github.com/jnear/cs3110-data-privacy/raw/main/homework/adult_with_pii.csv')

true_answer = len(adult[adult['Age'] > 50])
laplace_answers = [laplace_mech(true_answer, 1, 1) for _ in range(200)]

# Mish Function call
mish_answers = []
try:
    subprocess.check_output("g++ -std=c++1y mwilsoRandomizer.cpp", stdin=None, stderr=subprocess.STDOUT, shell=True)
except subprocess.CalledProcessError as e:
    print("<p>", e.output, "</p>")
    raise SystemExit

# Depending on your OS, different executable files will be produced. Run the executable.
if platform.system() == 'Windows':
    p = Popen(f'a.exe {true_answer} {1.0}', shell=True, stdout=PIPE, stdin=PIPE)
    if debug:
        print(p.stdout.read())
    mish_answers = p.stdout.read().decode("utf-8").split(" ")
    mish_answers = [float(a) for a in mish_answers[:-1]]
    print(mish_answers)
    os.remove("a.exe")
else:  # Mac and Linux case
    p = Popen([f'./a.out {true_answer} {1.0}'], shell=True, stdout=PIPE, stdin=PIPE)
    if debug:
        print(p.stdout.read())
    mish_answers = p.stdout.read().decode("utf-8").split(" ")
    mish_answers = [float(a) for a in mish_answers[:-1]]
    os.remove("a.out")

laplace_error = [pct_error(true_answer, a) for a in laplace_answers]
mish_error = [pct_error(true_answer, a) for a in mish_answers]

_, bins, _ = plt.hist(laplace_error, bins=20, label='Laplace')
plt.hist(mish_error, bins=bins, label='Mish_Random', alpha=0.5)
plt.legend()

plt.show()
