#include <fstream>
#include <vector>
#include <string>
#include <cstdint> // for uint8_t
#include <iostream> // for std::cout

std::vector<std::string> ReadLines(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
      if (!line.empty()){
        lines.push_back(line);
      }
    }
    return lines;
}

std::vector<uint16_t> ReadRaw(const std::string &filename, int img_height, int img_width) {
    std::ifstream file(filename, std::ios::binary);
    std::vector<uint16_t> image(img_height * img_width);

    file.read(reinterpret_cast<char*>(image.data()), image.size() * sizeof(uint16_t));

    return image;
}



std::vector<std::vector<uint8_t>> ProcessImages(const std::string &list_filename, int img_height, int img_width) {
    auto filenames = ReadLines(list_filename);
    std::vector<std::vector<uint8_t>> images;
    int img_count = 0;
    for (const auto &filename : filenames) {
        auto image = ReadRaw(filename, img_height, img_width);

        // auto processed_image = ImageTrans(image, img_height, img_width);
        // images.push_back(processed_image);
        std::cout << "Processed image: " << filename 
                  << ", pixel count: " << image.size() << std::endl;

        // Save the processed image as a RAW file
        std::string output_filename = "output_" + filename + ".raw";
        std::ofstream outfile(output_filename, std::ios::out | std::ios::binary);
        outfile.write(reinterpret_cast<char*>(image.data()), image.size());
        outfile.close();

        img_count++;
    }

    std::cout << "Total images processed: " << images.size() << std::endl;

    return images;
}


int main() {
    int img_height = 640; // Replace with the actual height
    int img_width = 640;  // Replace with the actual width
    std::string list_filename = "img_raw.txt"; 

    auto images = ProcessImages(list_filename, img_height, img_width);

    // Now you can do something with the images...

    return 0;
}