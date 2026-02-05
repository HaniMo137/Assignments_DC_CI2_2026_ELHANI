import re

import matplotlib.pyplot as plt

# Read and parse the benchmark results
threads = []
cpu_times = []

with open('benchmark_results.txt', 'r') as f:
    content = f.read()
    
    # Extract thread counts and CPU times
    thread_matches = re.findall(r'Threads: (\d+)', content)
    time_matches = re.findall(r'CPU time: ([\d.]+) seconds', content)
    
    threads = [int(t) for t in thread_matches]
    cpu_times = [float(t) for t in time_matches]

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(threads, cpu_times, marker='o', linewidth=2, markersize=8, color='#2E86AB')
plt.xlabel('Number of Threads', fontsize=12, fontweight='bold')
plt.ylabel('CPU Time (seconds)', fontsize=12, fontweight='bold')
plt.title('Matrix Multiplication Performance - STATIC Scheduling', fontsize=14, fontweight='bold')
plt.grid(True, alpha=0.3)
plt.xticks(threads)

import matplotlib.pyplot as plt

# Read and parse the benchmark results
scheduling_methods = {}

with open('benchmark_results.txt', 'r') as f:
    content = f.read()
    
    # Split by scheduling method
    sections = re.split(r'Testing (\w+) scheduling:', content)[1:]
    
    for i in range(0, len(sections), 2):
        method = sections[i]
        section_content = sections[i + 1]
        
        thread_matches = re.findall(r'Threads: (\d+)', section_content)
        time_matches = re.findall(r'CPU time: ([\d.]+) seconds', section_content)
        
        scheduling_methods[method] = {
            'threads': [int(t) for t in thread_matches],
            'cpu_times': [float(t) for t in time_matches]
        }

# Create the plot
plt.figure(figsize=(12, 7))

colors = {'STATIC': '#2E86AB', 'DYNAMIC': '#A23B72', 'GUIDED': '#F18F01'}

for method, data in scheduling_methods.items():
    plt.plot(data['threads'], data['cpu_times'], marker='o', linewidth=2, 
             markersize=8, label=method, color=colors.get(method, '#000000'))

plt.xlabel('Number of Threads', fontsize=12, fontweight='bold')
plt.ylabel('CPU Time (seconds)', fontsize=12, fontweight='bold')
plt.title('Matrix Multiplication Performance Comparison', fontsize=14, fontweight='bold')
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)
plt.xticks(scheduling_methods['STATIC']['threads'])

plt.tight_layout()
plt.savefig('benchmark_plot.png', dpi=300, bbox_inches='tight')
plt.show()

print("Plot saved as 'benchmark_plot.png'")
for x, y in zip(threads, cpu_times):
    plt.text(x, y + 0.02, f'{y:.3f}s', ha='center', va='bottom', fontsize=10)

plt.tight_layout()
plt.savefig('benchmark_plot.png', dpi=300, bbox_inches='tight')
plt.show()

print("Plot saved as 'benchmark_plot.png'")
print(f"Threads: {threads}")
print(f"CPU Times: {cpu_times}")