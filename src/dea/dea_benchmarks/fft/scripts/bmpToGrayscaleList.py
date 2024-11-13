import argparse
from PIL import Image

def convert_bmp_to_grayscale_list(input_image_path, output_text_path):
    # Open the image file
    with Image.open(input_image_path) as img:
        # Ensure the image is in grayscale mode
        grayscale_img = img.convert("L")

        # Check if image dimensions are either 512x512 or 128x128
        if grayscale_img.size not in [(512, 512), (128, 128)]:
            raise ValueError("The image must be either 512x512 or 128x128 pixels.")

        # Get pixel values and flatten to a single list
        pixel_values = list(grayscale_img.getdata())

        # Write grayscale values to the output file
        with open(output_text_path, 'w') as file:
            for value in pixel_values:
                file.write(f"{value}\n")

if __name__ == "__main__":
    # Set up command-line argument parsing
    parser = argparse.ArgumentParser(description="Convert a BMP image (512x512 or 128x128) to a list of grayscale values.")
    parser.add_argument("--bmp", required=True, help="Path to the input BMP image file.")
    parser.add_argument("--gs-list", required=True, help="Path to the output text file for grayscale values.")

    # Parse arguments
    args = parser.parse_args()

    # Run the conversion function with parsed arguments
    convert_bmp_to_grayscale_list(args.bmp, args.gs_list)

