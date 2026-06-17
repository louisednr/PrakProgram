# AI- generated plot + comparison

import re
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

# 1. Run Python Benchmarks and track function evaluations via 'full_output=1'
# SciPy quad returns (y, abserr, infodict) when full_output=1. infodict['neval'] is number of evaluations.

# Integral 1: 1/sqrt(x) from 0 to 1
_, _, info1 = quad(lambda x: 1.0/np.sqrt(x) if x > 0 else 0.0, 0, 1, epsabs=1e-6, epsrel=1e-6, full_output=1)
scipy_calls1 = info1['neval']

# Integral 2: ln(x)/sqrt(x) from 0 to 1
_, _, info2 = quad(lambda x: np.log(x)/np.sqrt(x) if x > 0 else 0.0, 0, 1, epsabs=1e-6, epsrel=1e-6, full_output=1)
scipy_calls2 = info2['neval']

# Integral 3: exp(-x^2) from -inf to inf
_, _, info3 = quad(lambda x: np.exp(-x**2), -np.inf, np.inf, epsabs=1e-6, epsrel=1e-6, full_output=1)
scipy_calls3 = info3['neval']

# Integral 4: x^2 * exp(-x) from 0 to inf (using the Gamma example)
_, _, info4 = quad(lambda x: (x**2) * np.exp(-x), 0, np.inf, epsabs=1e-6, epsrel=1e-6, full_output=1)
scipy_calls4 = info4['neval']

cpp_data = {"int1_ord": 0, "int1_cc": 0, "int2_ord": 0, "int2_cc": 0, "int3_cc": 0, "int4_cc": 0}

try:
    with open("Out.txt", "r") as f:
        lines = f.readlines()
        
        ord_counts = []
        cc_counts = []
        inf_counts = []
        
        for line in lines:
            # Explicitly match digits following the evaluations keyword label
            match = re.search(r'(?:Evaluations:|# Evaluations:)\s*(\d+)', line)
            if match:
                val = int(match.group(1))
                if "Ordinary:" in line:
                    ord_counts.append(val)
                elif "C-Curtis:" in line:
                    cc_counts.append(val)
                elif "Calculated:" in line or "Evaluations:" in line:
                    inf_counts.append(val)

        if len(ord_counts) >= 2:
            cpp_data["int1_ord"], cpp_data["int2_ord"] = ord_counts[0], ord_counts[1]
        if len(cc_counts) >= 2:
            cpp_data["int1_cc"], cpp_data["int2_cc"] = cc_counts[0], cc_counts[1]
        if len(inf_counts) >= 2:
            cpp_data["int3_cc"], cpp_data["int4_cc"] = inf_counts[-2], inf_counts[-1]

except Exception as e:
    print(f"[Warning] Error parsing Out.txt: {e}")

# 3. Create Comparative Grouped Bar Charts
labels = [
    '1/sqrt(x)\n(Endpoint Sing.)', 
    'ln(x)/sqrt(x)\n(Endpoint Sing.)', 
    'exp(-x²)\n(-inf to inf)', 
    'x²*exp(-x)\n(0 to inf)'
]

# Consolidate datasets
ordinary_calls = [cpp_data["int1_ord"], cpp_data["int2_ord"], 0, 0] # Ordinary can't do infinite limits
cc_calls = [cpp_data["int1_cc"], cpp_data["int2_cc"], cpp_data["int3_cc"], cpp_data["int4_cc"]]
scipy_calls = [scipy_calls1, scipy_calls2, scipy_calls3, scipy_calls4]

x = np.arange(len(labels))
width = 0.25

fig, ax = plt.subplots(figsize=(10, 6))

# Generate Bars
rects1 = ax.bar(x - width, ordinary_calls, width, label='C++ Ordinary Integrator', color='#ff7f0e', alpha=0.85)
rects2 = ax.bar(x, cc_calls, width, label='C++ Clenshaw-Curtis', color='#1f77b4', alpha=0.9)
rects3 = ax.bar(x + width, scipy_calls, width, label='Python SciPy (quad)', color='#2ca02c', alpha=0.85)

# Style choices
ax.set_ylabel('Number of Integrand Evaluations', fontsize=12)
ax.set_title('Integrator Performance Comparison: Function Evaluation Counts', fontsize=14, fontweight='bold')
ax.set_xticks(x)
ax.set_xticklabels(labels, fontsize=10)
ax.legend(fontsize=11)
ax.grid(axis='y', linestyle='--', alpha=0.5)

# Value Labels atop bars
def autolabel(rects):
    for rect in rects:
        height = rect.get_height()
        if height > 0:
            ax.annotate(f'{int(height)}',
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom', fontsize=9)

autolabel(rects1)
autolabel(rects2)
autolabel(rects3)

plt.tight_layout()
plt.savefig('comparison.svg')
print("Successfully generated 'comparison.svg'")

# End AI- generated plot + comparison