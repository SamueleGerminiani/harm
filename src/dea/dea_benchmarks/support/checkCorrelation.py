import numpy as np
import pandas as pd
from scipy.stats import pearsonr, spearmanr
from sklearn.linear_model import LinearRegression
import argparse
import os

# Set up argument parsing
parser = argparse.ArgumentParser(description="Calculate correlation and perform linear regression on damage and error data from a CSV file.")
parser.add_argument("--file", type=str, required=True, help="Path to the CSV file containing 'damage' and 'metric' columns.")
parser.add_argument("--output", type=str, default="correlation.csv", help="Optional output file name for results. Defaults to 'correlation.csv'.")
args = parser.parse_args()

# Read the CSV file
data = pd.read_csv(args.file)

# Check if the required columns are present
if 'damage' not in data.columns or 'metric' not in data.columns:
    print("Error: The CSV file must contain 'damage' and 'metric' columns.")
    exit(1)

# Extract damage and error values
damage = data['damage'].values.reshape(-1, 1)
error = data['metric'].values

# Calculate Pearson correlation coefficient
pearson_corr, pearson_p_value = pearsonr(damage.flatten(), error)

# Calculate Spearman's rank correlation coefficient
spearman_corr, spearman_p_value = spearmanr(damage.flatten(), error)

# Print the correlation coefficients and the p-values
print(f"Pearson correlation coefficient: {pearson_corr:.4f}")
print(f"Pearson p-value: {pearson_p_value:.8f}")
print(f"Spearman rank correlation coefficient: {spearman_corr:.4f}")
print(f"Spearman p-value: {spearman_p_value:.8f}")

# Perform linear regression
model = LinearRegression()
model.fit(damage, error)

# Get the R-squared value
r_squared = model.score(damage, error)

# Print regression results
print(f"R-squared: {r_squared:.4f}")

# Prepare the output data
output_data = {
    "Pearson Correlation": [round(pearson_corr, 4)],
    "Pearson P-value": [round(pearson_p_value, 4)],
    "Spearman Correlation": [round(spearman_corr, 4)],
    "Spearman P-value": [round(spearman_p_value, 4)],
    "R-squared": [round(r_squared, 4)]
}
output_df = pd.DataFrame(output_data)

# Append to the specified output file (create if it doesn't exist)
output_file = args.output
if os.path.exists(output_file):
    # If the file exists, append without writing the header
    output_df.to_csv(output_file, mode='a', header=False, index=False)
else:
    # If the file does not exist, create it and write the header
    output_df.to_csv(output_file, mode='w', header=True, index=False)

print(f"Results have been appended to {output_file}")

