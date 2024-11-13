import argparse
from PIL import Image

def convert_grayscale_list_to_bmp(input_text_path, output_image_path):
    # Read grayscale values from the text file
    with open(input_text_path, 'r') as file:
        pixel_values = [int(line.strip()) for line in file]

    # Determine the image dimensions based on the number of grayscale values
    if len(pixel_values) == 512 * 512:
        size = (512, 512)
    elif len(pixel_values) == 128 * 128:
        size = (128, 128)
    else:
        raise ValueError("The grayscale list must contain either 262144 (512x512) or 16384 (128x128) values.")

    # Create a new grayscale image with the determined dimensions
    img = Image.new("L", size)

    # Put the pixel values into the image
    img.putdata(pixel_values)

    # Save the image as a BMP file
    img.save(output_image_path)

if __name__ == "__main__":
    # Set up command-line argument parsing
    parser = argparse.ArgumentParser(description="Convert a list of grayscale values to a BMP image (512x512 or 128x128).")
    parser.add_argument("--gs-list", required=True, help="Path to the input text file with grayscale values.")
    parser.add_argument("--bmp", required=True, help="Path to the output BMP image file.")

    # Parse arguments
    args = parser.parse_args()

    # Run the conversion function with parsed arguments
    convert_grayscale_list_to_bmp(args.gs_list, args.bmp)

