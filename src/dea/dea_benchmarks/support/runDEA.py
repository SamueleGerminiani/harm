import csv
import sys
import argparse

# Set up argument parser
parser = argparse.ArgumentParser(description="Generate a list of tokenIDs for a specified or the first cluster in the CSV file.")
parser.add_argument('--csv', required=True, help="Path to the input CSV file")
parser.add_argument('--id', help="ClusterID to filter on. If not provided, the first cluster in the file is used.")

# Parse arguments
args = parser.parse_args()
csv_file_path = args.csv
specified_cluster_id = args.id

# Initialize storage for selected cluster's tokenIDs and track if the cluster is found
token_ids = []
cluster_found = False

#check if input file exists
try:
    open(csv_file_path, 'r')
except FileNotFoundError:
    print(f"Error: File '{csv_file_path}' not found.")
    exit(1)

# Process the CSV to gather tokenIDs for the specified or first cluster
with open(csv_file_path, 'r') as csv_file:
    reader = csv.DictReader(csv_file)

    # Get the first clusterID if no --id is provided
    first_cluster_id = specified_cluster_id or None

    for row in reader:
        cluster_id = row['clusterID']

        # Determine the cluster to use (if not provided)
        if first_cluster_id is None:
            first_cluster_id = cluster_id

        # Only gather tokenIDs if this matches the target cluster
        if cluster_id == first_cluster_id:
            token_ids.append(row['tokenID'])
            cluster_found = True
        elif specified_cluster_id is None:
            break  # Stop processing after the first cluster if no --id was specified

# Check if the specified cluster was found and output results or error message
if cluster_found:
    result = ';'.join(token_ids)
    print(result)
else:
    print(f"Error: ClusterID '{specified_cluster_id}' not found in the file.")
    exit(1)

