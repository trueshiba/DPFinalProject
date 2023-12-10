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

debug = True


# Joe Near Functions
def laplace_mech(v, sensitivity, epsilon):
    return v + np.random.laplace(loc=0, scale=sensitivity / epsilon)


def laplace_mech_vec(vec, sensitivity, epsilon):
    return [v + np.random.laplace(loc=0, scale=sensitivity / epsilon) for v in vec]


def pct_error(orig, priv):
    return np.abs(orig - priv) / orig * 100.0


# Laplace Calls
adult = pd.read_csv('https://github.com/jnear/cs3110-data-privacy/raw/main/homework/adult_with_pii.csv')

true_answer = len(adult[adult['Age'] > 50])
laplace_answers = [laplace_mech(true_answer, 1, 1) for _ in range(200)]

# C++ Calls
mish_answers = []
cooper_answers = []
alison_answers = []
try:
    subprocess.check_output("g++ mwilsoRandomizer.cpp -o mishFile", stdin=None, stderr=subprocess.STDOUT, shell=True)
    subprocess.check_output("g++ cooperDist.cpp -o cooperFile", stdin=None, stderr=subprocess.STDOUT, shell=True)
    subprocess.check_output("g++ agilRandomizer.cpp -o alisonFile", stdin=None, stderr=subprocess.STDOUT, shell=True)


except subprocess.CalledProcessError as e:
    print("<p>", e.output, "</p>")
    raise SystemExit

# Depending on your OS, different executable files will be produced. Run the executable.
if platform.system() == 'Windows':
    # Mish Function call
    p = Popen(f'mishFile.exe {true_answer} {9} {1.0}', shell=True, stdout=PIPE, stdin=PIPE)

    mish_answers = p.stdout.read().decode("utf-8").split(" ")
    mish_answers = [float(a) for a in mish_answers[:-1]]
    os.remove("mishFile.exe")

    # Cooper Function call
    p = Popen(f'cooperFile.exe {true_answer}', shell=True, stdout=PIPE, stdin=PIPE)

    cooper_answers = p.stdout.read().decode("utf-8").split(" ")
    cooper_answers = [float(a) for a in cooper_answers[:-1]]
    os.remove("cooperFile.exe")

    p = Popen(f'alisonFile.exe {true_answer} {1000}', shell=True, stdout=PIPE, stdin=PIPE)

    alison_answers = p.stdout.read().decode("utf-8").split(" ")
    alison_answers = [float(a) for a in alison_answers[:-1]]
    os.remove("alisonFile.exe")

else:  # Mac and Linux case
    p = Popen([f'./mishFile.out {true_answer} {9} {1.0}'], shell=True, stdout=PIPE, stdin=PIPE)
    mish_answers = p.stdout.read().decode("utf-8").split(" ")
    mish_answers = [float(a) for a in mish_answers[:-1]]
    os.remove("mishFile.out")

    p = Popen([f'./cooperFile.out {true_answer}'], shell=True, stdout=PIPE, stdin=PIPE)
    cooper_answers = p.stdout.read().decode("utf-8").split(" ")
    cooper_answers = [float(a) for a in cooper_answers[:-1]]
    os.remove("cooperFile.out")

    p = Popen([f'./alisonFile.out {true_answer} {1000}'], shell=True, stdout=PIPE, stdin=PIPE)
    alison_answers = p.stdout.read().decode("utf-8").split(" ")
    alison_answers = [float(a) for a in alison_answers[:-1]]
    os.remove("alisonFile.out")

#Calculate error
laplace_error = [pct_error(true_answer, a) for a in laplace_answers]
mish_error = [pct_error(true_answer, a) for a in mish_answers]
cooper_error = [pct_error(true_answer, a) for a in cooper_answers]
alison_error = [pct_error(true_answer, a) for a in alison_answers]

#Plot the graphs
plt.suptitle('Noisy Plots')

plt.subplot(131)
_, bins, _ = plt.hist(laplace_error, bins=20, label='Laplace')
plt.hist(mish_error, bins=bins, label='Mish_Random', alpha=0.25)
plt.legend()
plt.xlabel("MishMec vs LaplaceMec")

plt.subplot(132)
_, bins, _ = plt.hist(laplace_error, bins=20, label='Laplace')
plt.hist(cooper_error, bins=bins, label='Cooper_Random', alpha=0.25)
plt.legend()
plt.xlabel("CooperMec vs LaplaceMec")

plt.subplot(133)
_, bins, _ = plt.hist(laplace_error, bins=20, label='Laplace')
plt.hist(alison_error, bins=bins, label='Alison_Random', alpha=0.25)
plt.legend()
plt.xlabel("AlisonMec vs LaplaceMec")

plt.show()
