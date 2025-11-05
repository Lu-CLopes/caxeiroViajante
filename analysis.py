import numpy as np
import matplotlib.pyplot as plt

# --- EDIT THESE ---
group_labels = ['23', '42', '28657']            # group names
series1_label = 'w/ inversion'                 # label for first bar in each group
series2_label = 'wo/ inversion'                 # label for second bar in each group

# Provide the values for each group: [A, B, C]
series1 = [3814, 4853, 4432]    # first bar of each group
series2 = [3814, 4047, 3364]    # second bar of each group
# --------------------

x = np.arange(len(group_labels))
width = 0.35

fig, ax = plt.subplots(figsize=(7, 4))
bars1 = ax.bar(x - width/2, series1, width, label=series1_label, color='#4C72B0')
bars2 = ax.bar(x + width/2, series2, width, label=series2_label, color='#55A868')

# Labels and title
ax.set_xlabel('Seed')
ax.set_ylabel('Value')
ax.set_title('Grouped bar chart (2 bars per group)')
ax.set_xticks(x)
ax.set_xticklabels(group_labels)
ax.legend()

# Add value labels on top of each bar
def autolabel(bars):
    for bar in bars:
        height = bar.get_height()
        ax.annotate(f'{height}',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom', fontsize=9)

autolabel(bars1)
autolabel(bars2)

plt.tight_layout()
plt.show()