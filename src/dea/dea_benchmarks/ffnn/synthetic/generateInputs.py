import numpy as np
import subprocess
import os
import pandas as pd
import argparse
import itertools
from tqdm import tqdm
from collections import defaultdict
import random

def generate_balanced_data(n_to_generate, input_dir, output_dir, num_range=(1, 35), random_sampling=False):
    # Number of classes
    num_classes = 3
    all_data = {'A': [], 'B': [], 'C': [], 'D': [], 'Result': []}
    class_data = defaultdict(list)

    # Default ranges for the features
    ranges = {
        'A': num_range,
        'B': num_range,
        'C': num_range,
        'D': num_range
    }

    # Ensure the output directory exists
    os.makedirs(output_dir, exist_ok=True)

    if random_sampling:
        # Keep the original random sampling part unchanged
        batch_size = 1000000
        while True:
            samples = [
                (
                    np.random.randint(ranges['A'][0], ranges['A'][1] + 1),
                    np.random.randint(ranges['B'][0], ranges['B'][1] + 1),
                    np.random.randint(ranges['C'][0], ranges['C'][1] + 1),
                    np.random.randint(ranges['D'][0], ranges['D'][1] + 1)
                )
                for _ in range(batch_size)
            ]

            # Save the batch of samples to text files
            save_multiple_samples_to_files(samples, input_dir)

            # Run the simulation and get the predicted classes for the batch
            predicted_classes = run_simulation_and_get_result(batch_size, input_dir, output_dir)

            # Update data based on the predicted classes
            for (a, b, c, d), predicted_class in zip(samples, predicted_classes):
                # Collect the generated data with the current predicted class
                all_data['A'].append(a)
                all_data['B'].append(b)
                all_data['C'].append(c)
                all_data['D'].append(d)
                all_data['Result'].append(predicted_class)

                # Group data by class for later balanced sampling
                class_data[predicted_class].append((a, b, c, d))

            # Print the current total samples collected
            print(f"Current total samples: {len(all_data['A'])}")
            # Exit if we have enough data
            if len(all_data['A']) >= n_to_generate * num_classes:
                break
    else:

        # Generate all combinations mode
        all_combinations = list(itertools.product(
            range(ranges['A'][0], ranges['A'][1] + 1),
            range(ranges['B'][0], ranges['B'][1] + 1),
            range(ranges['C'][0], ranges['C'][1] + 1),
            range(ranges['D'][0], ranges['D'][1] + 1)
        ))

        # Save all combinations to text files in a single batch
        save_multiple_samples_to_files(all_combinations, input_dir)

        # Run the simulation and get the predicted classes for all combinations
        predicted_classes = run_simulation_and_get_result(len(all_combinations), input_dir, output_dir)

        # Update data based on the predicted classes with a progress bar
        with tqdm(total=len(all_combinations), desc="Processing combinations") as pbar:
            for (a, b, c, d), predicted_class in zip(all_combinations, predicted_classes):
                # Collect the generated data with the current predicted class
                all_data['A'].append(a)
                all_data['B'].append(b)
                all_data['C'].append(c)
                all_data['D'].append(d)
                all_data['Result'].append(predicted_class)

                # Group data by class for later balanced sampling
                class_data[predicted_class].append((a, b, c, d))

                # Update the progress bar
                pbar.update(1)

    #Print class sizes
    for class_label, samples in class_data.items():
        print(f"Class {class_label}: {len(samples)} samples")

    # Sample the final set of results while keeping the classes balanced
    final_data = sample_balanced_data(class_data, n_to_generate, num_classes)

    return final_data

def sample_balanced_data(class_data, n_to_generate, num_classes):
    # Calculate the number of samples needed per class
    samples_per_class = n_to_generate // num_classes
    final_data = {'A': [], 'B': [], 'C': [], 'D': [], 'Result': []}

    # Randomly sample the required number of samples for each class
    for class_label, samples in class_data.items():
        if len(samples) < samples_per_class:
            raise ValueError(f"Class {class_label} has insufficient samples for balanced sampling. Only {len(samples)} samples available.")
        selected_samples = random.sample(samples, samples_per_class)

        # Append the sampled data to the final data set
        for a, b, c, d in selected_samples:
            final_data['A'].append(a)
            final_data['B'].append(b)
            final_data['C'].append(c)
            final_data['D'].append(d)
            final_data['Result'].append(class_label)

    return final_data

def save_multiple_samples_to_files(samples, input_dir):
    os.makedirs(input_dir, exist_ok=True)
    with open(f"{input_dir}/iris_test_input_feature1.txt", 'w') as f1, \
         open(f"{input_dir}/iris_test_input_feature2.txt", 'w') as f2, \
         open(f"{input_dir}/iris_test_input_feature3.txt", 'w') as f3, \
         open(f"{input_dir}/iris_test_input_feature4.txt", 'w') as f4:
        for a, b, c, d in samples:
            f1.write(f"{a}\n")
            f2.write(f"{b}\n")
            f3.write(f"{c}\n")
            f4.write(f"{d}\n")

def run_simulation_and_get_result(num_samples, input_dir, output_dir):
    trace_length_macro = f"+define+TRACE_LENGTH={num_samples}" if num_samples > 0 else ""
    compile_macros = (
        f"{trace_length_macro} "
        f"+define+IN_PATH=\"{input_dir}\" "
        f"+define+OUT_PATH=\"{output_dir}\""
    )

    commands = [
        "rm -rf work",
        "vlib work",
        f"vlog {compile_macros} -sv ./components.v ./ffnn_original.v ./ffnn_original_tb.v > /dev/null",
        "vsim -c -voptargs='+acc' -do \"vcd file sim.vcd; vcd add /*;run -all; vcd flush; quit\" work.ffnn_tb > /dev/null"
    ]
    for cmd in commands:
        subprocess.run(cmd, shell=True)

    return parse_results_csv(os.path.join(output_dir, "results.csv"))

def parse_results_csv(csv_file):
    df = pd.read_csv(csv_file)
    if df.empty:
        raise ValueError("The results CSV file is empty.")
    return df['Result'].tolist()

def save_to_files(data, output_dir):
    os.makedirs(output_dir, exist_ok=True)
    feature_files = [
        ('iris_test_input_feature1.txt', data['A']),
        ('iris_test_input_feature2.txt', data['B']),
        ('iris_test_input_feature3.txt', data['C']),
        ('iris_test_input_feature4.txt', data['D']),
        ('iris_test_output_result.txt', data['Result'])
    ]

    for filename, values in feature_files:
        with open(f"{output_dir}/{filename}", 'w') as f:
            for value in values:
                f.write(f"{value}\n")

def parse_range(range_str):
    try:
        min_val, max_val = map(int, range_str.split(","))
        return min_val, max_val
    except ValueError:
        raise argparse.ArgumentTypeError("Range must be in the format 'min,max'.")

def main():
    parser = argparse.ArgumentParser(description="Generate synthetic data for the neural network.")
    parser.add_argument("--input", type=str, required=True, help="Input directory for generated inputs.")
    parser.add_argument("--output", type=str, required=True, help="Output directory for simulation results.")
    parser.add_argument("--length", type=int, required=True, help="Total number of synthetic inputs to generate.")
    parser.add_argument("--range", type=parse_range, default="1,35", help="Range of numbers for each feature as 'min,max' (default: '1,35').")
    parser.add_argument("--random", action='store_true', help="Enable random sampling mode.")
    args = parser.parse_args()

    num_range = args.range

    synthetic_data = generate_balanced_data(
        n_to_generate=args.length,
        input_dir=args.input,
        output_dir=args.output,
        num_range=num_range,
        random_sampling=args.random
    )

    save_to_files(synthetic_data, args.output)

if __name__ == "__main__":
    main()

