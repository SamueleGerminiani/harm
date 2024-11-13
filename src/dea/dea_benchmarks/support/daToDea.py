import csv
import json
import sys
import argparse

# Set up argument parser
parser = argparse.ArgumentParser(description="Translate transformations in CSV based on mappings from a text file.")
parser.add_argument('--csv', required=True, help="Path to the input CSV file")
parser.add_argument('--txt', required=True, help="Path to the input TXT file containing component mappings")
parser.add_argument('--out', help="Path to the output CSV file (optional). If not provided, output will be printed to stdout")
parser.add_argument('--row', type=int, default=0, help="Row number to process in the CSV file (0-indexed, default is the first row)")

# Parse arguments
args = parser.parse_args()
csv_file_path = args.csv
txt_file_path = args.txt
output_file_path = args.out
row_index = args.row

# Load component transformation categories from the text file
component_category_map = {}
with open(txt_file_path, 'r') as txt_file:
    lines = txt_file.read().split('---')[1].strip().splitlines()
    for line in lines:
        component, category = line.split(':')
        component_category_map[component.strip()] = category.strip()

# Process CSV and handle row selection
try:
    with open(csv_file_path, 'r') as csv_file:
        reader = csv.DictReader(csv_file, delimiter=';')
        reader.fieldnames = [name.strip() for name in reader.fieldnames]  # Strip whitespace from headers
        rows = list(reader)

        # Check if the row index exists
        if row_index >= len(rows) or row_index < 0:
            print("Error: Specified row does not exist in the CSV file.")
            sys.exit(1)

        row = rows[row_index]

        if 'transform_map' not in row:
            print("Error: The CSV file does not contain a 'transform_map' column.")
            sys.exit(1)

        transform_map = row['transform_map']
        transformations = json.loads(transform_map)

        # Translate each transformation
        translated_transformations = []
        for component, target in transformations.items():
            category = component_category_map.get(component, 'unknown')
            translated_transformations.append(f"{component}#{category}#{target}")

        # Join transformations with ";"
        row['translated_transform_map'] = ';'.join(translated_transformations)

        # Output to file or stdout
        if output_file_path:
            with open(output_file_path, 'w', newline='') as output_file:
                fieldnames = reader.fieldnames + ['translated_transform_map']
                writer = csv.DictWriter(output_file, fieldnames=fieldnames)
                writer.writeheader()
                writer.writerow(row)
            print("Transformation complete. Check the output file for results.")
        else:
            print(f"{';'.join(translated_transformations)}")

except FileNotFoundError:
    print("Error: CSV or TXT file not found.")
    sys.exit(1)
except json.JSONDecodeError:
    print("Error: 'transform_map' column contains invalid JSON.")
    sys.exit(1)

