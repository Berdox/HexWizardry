#pragma once;

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

class HexEditor {
    public:
	    std::vector<uint8_t> hexData;

        HexEditor() {}

	    void loadFile(const std::string filePath) {
            // Open file in binary mode
            std::ifstream file(filePath, std::ios::binary);

            if (!file) {
                std::cerr << "Error opening file: " << filePath << std::endl;
                return;
            }

            // Read the file byte by byte and store each byte in the vector
            unsigned char byte;
            while (file.read(reinterpret_cast<char*>(&byte), 1)) {
                hexData.push_back(byte);
            }

            file.close();
	    }

	    void displayHexData() {
            size_t offset = 0;

            // Display the hex data in readable format
            for (size_t i = 0; i < hexData.size(); ++i) {
                if (i % 16 == 0) {
                    // Print address offset at the start of each line
                    if (i != 0) {
                        std::cout << std::endl;
                    }
                    std::cout << std::setw(8) << std::setfill('0') << std::hex << i << ": ";
                }

                // Print the byte in hex format
                std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)hexData[i] << " ";
            }

            std::cout << std::endl;
	    }
};